#include "pch.h"
#include "HttpImpl.h"
#include "HeroApp.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "SceneUtil.h"

#include "W_ExtraRes.pb.h"
#include "GlobalDefine.h"
#include "Common.pb.h"

#define DEFAULT_SIGNATURE "nosig"
#define DEFAULT_TICKET 0
#define ALL_RETRY_NOTY
#define RETRY_COUNT 1	//ó������ 6�� �õ��Ѵ�.
#define CONFIRM_RETRY 1		//�˾�â�� ���� �ȵ˴ϴ�. �ϰ� �ٽ� �õ��ϱ� �ϸ� �׶� 3���� ����.
#define RETRY_DELAY_TIME 10.f

//#define DEBUG_CCLOG

HttpImpl::HttpImpl() :
mRetryCount(0),
mRetryDelay(0.f),
mUID(0),
mSignature(DEFAULT_SIGNATURE),
mTicket(DEFAULT_TICKET),
mMsgTransferRetryAuto(false),
mRetryMsg(nullptr)
{
}

void HttpImpl::postSend(const HttpMessage& msgSent)
{
	mRetryMaxCount = RETRY_COUNT;
	if (msgSent.hasToWait())
		HeroApp::getSingleton().startWaiting();

	HeroApp::getSingleton().resetPing();
}

void HttpImpl::postReSend(const HttpMessage& msgSent)
{
	mRetryMaxCount = CONFIRM_RETRY;
	if (msgSent.hasToWait())
		HeroApp::getSingleton().startWaiting();

	HeroApp::getSingleton().resetPing();
}


void HttpImpl::buildProtocol(HttpMessage* msg, MessageBuffer& sendBuffer)
{
	// Common message
	Common common;
	common.set_pid(msg->getType());
	common.set_uid(mUID);
	common.set_sig(mSignature);
	common.set_ticket(mTicket); 
	common.set_datahash(GameDataManager::getSingletonPtr()->getHash());
 	common.set_majorver(VERSION_MAJOR);	
 	common.set_minorver(VERSION_MINOR);
 	common.set_buildver(VERSION_MAINTENANCE);
	common.set_connecttime(GameDataManager::getSingletonPtr()->getPlayingTime());	
	NXASSERT(common.IsInitialized());
	string type = common.GetTypeName();
	MessageSize commonSize = common.ByteSize();
	char* temp = new char[sizeof(commonSize) + common.ByteSize()];
	MessageSize reversedCommonSize = SWAP_ENDIAN_32(commonSize);
	memcpy(temp, &reversedCommonSize, sizeof(reversedCommonSize));
	common.SerializeToArray(temp+sizeof(commonSize), common.ByteSize());
	sendBuffer.insert(sendBuffer.end(), temp, temp+sizeof(commonSize)+common.ByteSize());
	delete [] temp;
	// Custom message.
	MessageSize customSize = msg->getSize();
	MessageSize reversedCustomSize = SWAP_ENDIAN_32(customSize);
	sendBuffer.insert(sendBuffer.end(), reinterpret_cast<char*>(&reversedCustomSize), reinterpret_cast<char*>(&reversedCustomSize)+sizeof(reversedCustomSize));
	sendBuffer.insert(sendBuffer.end(), msg->getData(), msg->getData()+customSize);
}

void HttpImpl::parseProtocol(HttpMessage* msg, const MessageBuffer& recvBuffer)
{
	if (!recvBuffer.empty()) {

		const char* buffer = &recvBuffer.front();

		Protocol commonProto(buffer, recvBuffer.size());
		Common common;
		common.ParsePartialFromArray(commonProto.getContent(), commonProto.getSize());
		NXASSERT(common.IsInitialized() && "Common message is wrong.");

		if (common.code() != Common::COMMON_OK) {
			if (msg->hasToWait()) {
				HeroApp::getSingleton().stopWaiting();
				msg->setToWait(false);
			}

			NxCode code = NxCode_Unknown;
			if (common.code() == Common::COMMON_INVALID_SESSION) {
				code = NxCode_InvalidSession;
			}
			else if (common.code() == Common::COMMON_INVALID_SIG) {
				code = NxCode_InvalidSignature;
			}
			else if (common.code() == Common::COMMON_INVALID_TICKET) {
				code = NxCode_InvalidTicket;
			}
			else if (common.code() == Common::COMMON_INVALID_REQUEST) {
				code = NxCode_InvalidProtocol;
			}
			else if (common.code() == Common::COMMON_INVALID_DATAHASH) {
				code = NxCode_InvalidDataHash;
			}			
 			else if (common.code() == Common::COMMON_INVAILD_VERSION) {
 				code = NxCode_InvalidVersion;
 			}
 			else if (common.code() == Common::COMMON_INVAILD_LIVE) {
 				code = NxCode_InvalidLive;
 			}
			//if (!handleNxCode(code)) {
			_recv(new HttpMessage(msg, code));
			//}
			return;
		}

		mUID = common.uid();
		mSignature = common.sig();
		mTicket = common.ticket() + 1;
		checkMsg = common.checkmsg();

		Protocol customProto(buffer, recvBuffer.size() - commonProto.getPackedSize());
		Protocol extraProto(buffer, recvBuffer.size() - commonProto.getPackedSize() - customProto.getPackedSize());

		if (extraProto.getSize()) {
			_recv(new HttpMessage(msg, customProto.getContent(), customProto.getSize()),
				new HttpMessage(msg, extraProto.getContent(), extraProto.getSize()));
		}
		else {
			_recv(new HttpMessage(msg, customProto.getContent(), customProto.getSize()));
		}
	}
	else {
		//handleNxCode(NxCode_EmptyResponse);
		//mMsgRecvBuffer.push(new HttpMessage(msg, NxCode_EmptyResponse));
		_recv(new HttpMessage(msg, NxCode_EmptyResponse));
	}
}


void HttpImpl::curlError(HttpMessage* msg)
{
	_recv(msg);
}


void HttpImpl::_recv(HttpMessage* msg, HttpMessage* quest /*= nullptr*/)
{
	NXASSERT(msg);

	ScopedLock locker(mMsgRecvMutex);	
	mMsgRecvBuffer.push_back(msg);

	if (quest) {
		mExtraRecvBuffer.push_back(quest);
	}
}

void HttpImpl::process()
{
	ScopedLock locker(mMsgRecvMutex);	
	
	while (!mExtraRecvBuffer.empty())
	{
		HttpMessage* msg = mExtraRecvBuffer.front();
		W_ExtraRes* res = new W_ExtraRes();
		res->ParseFromArray(msg->getData(), msg->getSize());
		NXASSERT(res->IsInitialized());
		mExtraRecvBuffer.pop_front();
		
		if (GameDataManager::getSingleton().getUserInfo() != nullptr) {
			if (res->has_notiinfo()) {
				GameDataManager::getSingleton().setNotiInfo(res->notiinfo());
			}

			if (res->has_friendofinfo()) {
				W_FriendOfInfo _friendOfInfo = res->friendofinfo();

				int _size = _friendOfInfo.facefriendinfo_size();
				GameDataManager::getSingletonPtr()->RemoveSnsDataList();
				GameDataManager::getSingletonPtr()->m_SnsDataList.reserve(_size);
				for (int _i = 0; _i < _size; _i++)
				{
					W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.facefriendinfo(_i));
					GameDataManager::getSingletonPtr()->m_SnsDataList.push_back(_info);
				}

				_size = _friendOfInfo.friendinfo_size();
				GameDataManager::getSingletonPtr()->RemoveFriendDataList();
				GameDataManager::getSingletonPtr()->m_FriendDataList.reserve(_size);
				for (int _i = 0; _i < _size; _i++)
				{
					W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.friendinfo(_i));
					GameDataManager::getSingletonPtr()->m_FriendDataList.push_back(_info);
				}

				//facebook 리스트 정보
				GameDataManager::getSingletonPtr()->mRewardIds.clear();
				_size = _friendOfInfo.facefriendinviterewardlist_size();
				for (int _i = 0; _i < _size; _i++)
				{
					GameDataManager::getSingletonPtr()->mRewardIds.push_back(_friendOfInfo.facefriendinviterewardlist(_i));
				}

			}

		}
		delete msg;
		delete res;
	}

	while (!mMsgRecvBuffer.empty())
	{
		HttpMessage* msg = mMsgRecvBuffer.front();		
		mMsgRecvBuffer.pop_front();		
		bool relogin = false;
		bool retry = false;
		bool exit = false;
		bool isLiveError = false;
		mMsgTransferRetryAuto = false;
#ifdef ALL_RETRY_NOTY
		retry = true;
		mRetryMsg = msg;
#endif // ALL_RETRY_NOTY
		if (msg->getCode() != NxCode_OK) {
			std::string errorString;
			string notice;
			switch (msg->getCode())
			{
			case NxCode_InvalidSession:
				errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_SESSION");
				notice = "NxCode_InvalidSession";
				break;
			case NxCode_InvalidSignature:
				errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_SIGNATURE");
				notice = "NxCode_InvalidSignature";		
				exit = true;
				break;
			case NxCode_InvalidTicket:
				errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_TICKET");
				notice = "NxCode_InvalidTicket";
				break;
			case NxCode_EmptyResponse:
				errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_RESPONSE");
				notice = "NxCode_EmptyResponse";
				mMsgTransferRetryAuto = true;
				break;
			case NxCode_InvalidProtocol:
				errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_PROTOCOL");
				notice = "NxCode_InvalidProtocol";
				break;
			case NxCode_InvalidDataHash:
				errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_DATA");
				notice = "NxCode_InvalidDataHash";
				break;
			case NxCode_InvalidVersion:
				errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_VERSION");
				notice = "NxCode_InvalidVersion";
				break;
			case NxCode_InvalidLive:
				errorString = checkMsg;
				notice = "NxCode_InvalidLive";
				isLiveError = true;
				retry = true;
				break;
			case NxCode_HttpError:
				errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_HTTP");
				notice = "HttpState_" + StringConverter::toString(msg->getState());
				mMsgTransferRetryAuto = true;
				break;
			case NxCode_CurlError:				
				if (msg->getState() == CURLE_OPERATION_TIMEDOUT) {
					errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_CURL_RETRY");
					notice = "Error_" + StringConverter::toString(msg->getState());
					mMsgTransferRetryAuto = true;
					mRetryMsg = msg;
					break;
				}
				else {
					errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_CURL");
					notice = "Error_" + StringConverter::toString(msg->getState());
					mMsgTransferRetryAuto = true;
					break;
				}
			default:
				errorString = GameStringDepot::getSingleton().getString("SERVER_ERROR_NETWORK");
				notice = "Network Error";
				break;
			}

			// ��α��� ó��
			if (relogin) {
				HeroApp::getSingleton().showServerErrorMessage(errorString, "", notice, this,
					GeneralObjectListener(HttpImpl::_onRelogin), MessagePanel::OK);
			}
			else {
				// ������ ó��
#ifdef DEBUG_CCLOG
				CCLOG("httpimpal retry = %d, mMsgTransferRetryAuto = %d, mRetryCount = %d , mRetryMaxCount = %d", retry, mMsgTransferRetryAuto, mRetryCount, mRetryMaxCount);
#endif
				if (retry) {
					if (mMsgTransferRetryAuto) {
						if (mRetryCount < mRetryMaxCount) {
							++mRetryCount;							
							mRetryDelay = RETRY_DELAY_TIME;		
							stopWaitingPanel(true);
							_onRetry(MessagePanel::BTN_YES);
							//CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(HttpImpl::update), this, 0, false);
						}
						else {
							mRetryCount = 0;							
							stopWaitingPanel(msg->hasToWait());														
							HeroApp::getSingleton().showServerErrorMessage(GameStringDepot::getSingleton().getString("SERVER_ERROR_CURL_RETRY"), "", notice, this,
								GeneralObjectListener(HttpImpl::_onRetry), MessagePanel::OK);
						}
					}
					else {
						stopWaitingPanel(msg->hasToWait());
						msg->response();
						msg->getTarget()->release();
						delete msg;
						if (exit) {
							HeroApp::getSingleton().showServerErrorMessage(errorString, "", notice, this,
								GeneralObjectListener(HttpImpl::_exit), MessagePanel::OK);
						}
						else {
							if (isLiveError)
								HeroApp::getSingleton().showServerErrorMessage(errorString, "", notice, this, GeneralObjectListener(HttpImpl::_onServerList), MessagePanel::OK);
							else
								HeroApp::getSingleton().showServerErrorMessage(errorString, "", notice, this,GeneralObjectListener(HttpImpl::_onClose), MessagePanel::OK);
						}						
					}
				}	
				else {
					stopWaitingPanel(msg->hasToWait()); 
					msg->response();
					msg->getTarget()->release();
					delete msg;
				}
			}
		}
		else {
			mRetryCount = 0;
			stopWaitingPanel(msg->hasToWait());
			msg->response();
			msg->getTarget()->release();
			delete msg;
		}

		if (!retry) {
			msg->getTarget()->release();
			delete msg;
		}
	}
}

void HttpImpl::postStop()
{
	mTicket = DEFAULT_TICKET;

	_clearRetry();
}

void HttpImpl::_onRetry(const string& msg)
{
	NXASSERT(mRetryMsg);	
	HttpManager::getSingleton().resend(*mRetryMsg);	
	mRetryMsg = nullptr;
	//_onClose(msg);	
}

void HttpImpl::_clearRetry()
{
	if (mRetryMsg) {
		mRetryMsg->getTarget()->release();

		delete mRetryMsg;
		mRetryMsg = nullptr;
	}
}

void HttpImpl::_onClose(const string& msg)
{
	//SceneManager::getSingleton().getScene(SceneUtil::SceneVillage)->onMessage("Reset");
	HeroApp::getSingleton().setConnected(false); 
	HttpManager::getSingleton().close();
	HttpManager::getSingleton().reset();	
	CSJson::Value params;
	params["Reconnect"] = true;
	SceneUtil::changeScene(SceneUtil::SceneTitle, params);
	//SceneManager::getSingleton().changeScene(SceneUtil::SceneLogin, params);
}

void HttpImpl::_onRelogin(const string& msg)
{
	
}

void HttpImpl::timeOut()
{
	//SceneManager::getSingleton().changeScene(SceneUtil::SceneLogin);
}

void HttpImpl::stopWaitingPanel(bool wait)
{
	if (wait)
		HeroApp::getSingleton().stopWaiting();
}

void HttpImpl::_exit(const string& msg)
{
	CCDirector::sharedDirector()->end();
}

void HttpImpl::_onServerList(const string& msg)
{
// 	HeroApp::getSingleton().setConnected(false);
// 	HttpManager::getSingleton().close();
// 	HttpManager::getSingleton().reset();	
// 	SceneUtil::changeScene(SceneUtil::SceneLogin);	
}
