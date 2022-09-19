#include "pch.h"
#include "WebService.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "W_FriendAddReq.pb.h"
#include "W_FriendAddRes.pb.h"
#include "W_FriendGiftReceiveReq.pb.h"
#include "W_FriendGiftReceiveRes.pb.h"
#include "W_FriendGiftSendReq.pb.h"
#include "W_FriendGiftSendRes.pb.h"
#include "W_FriendOfInfoReq.pb.h"
#include "W_FriendOfInfoRes.pb.h"
#include "W_FriendReCommendReq.pb.h"
#include "W_FriendReCommendRes.pb.h"
#include "W_FriendRejectReq.pb.h"
#include "W_FriendRejectRes.pb.h"
#include "W_FriendRemoveReq.pb.h"
#include "W_FriendRemoveRes.pb.h"
#include "W_FriendRequestListReq.pb.h"
#include "W_FriendRequestListRes.pb.h"
#include "W_FriendRequestReq.pb.h"
#include "W_FriendRequestRes.pb.h"
#include "W_ReplayListReq.pb.h"
#include "W_ReplayListRes.pb.h"
#include "W_QuestListReq.pb.h"
#include "W_QuestListRes.pb.h"
#include "W_LetterAllUpdateReq.pb.h"
#include "W_LetterAllUpdateRes.pb.h"
#include "W_AdultAuthStartReq.pb.h"
#include "W_AdultAuthStartRes.pb.h"
#include "SimplePopupPanel.h"
#include "LobbyScene.h"
#include "W_CharacterBuyReq.pb.h"
#include "W_CharacterBuyRes.pb.h"
#include "LobbyUIPanel.h"
#include "GameStringDepot.h"
#include "W_ReplayDailyReq.pb.h"
#include "W_ReplayWeeklyReq.pb.h"
#include "W_ReplayDailyRes.pb.h"
#include "W_ReplayWeeklyRes.pb.h"
#include "W_LetterListReq.pb.h"
#include "W_LetterListRes.pb.h"
#include "W_ReplayStartReq.pb.h"
#include "W_ReplayStartRes.pb.h"
#include "ReplayGameManager.h"
#include "W_RankInfoRes.pb.h"
#include "W_ReplayModifyReq.pb.h"
#include "W_ReplayModifyRes.pb.h"
#include "LobbyFriendPanel.h"
#include "W_PlayerInfoReq.pb.h"
#include "W_PlayerInfoRes.pb.h"
#include "AccountPopupPanel.h"
#include "W_CharacterSelectReq.pb.h"
#include "W_CharacterSelectRes.pb.h"
#include "SelectCharacterPanel.h"
#include "W_ReplayCommentReq.pb.h"
#include "W_ReplayLikeReq.pb.h"
#include "W_ReplayLikeRes.pb.h"
#include "W_ReplayCommentRes.pb.h"
#include "W_ReplayDeleteReq.pb.h"
#include "W_ReplayDeleteRes.pb.h"
#include "W_EventListReq.pb.h"
#include "W_EventListRes.pb.h"
#include "W_EventUpdateReq.pb.h"
#include "W_EventUpdateRes.pb.h"
#include "W_FriendFindReq.pb.h"
#include "W_FriendFindRes.pb.h"
#include "SynopsisUiPanel.h"
#include "SceneUtil.h"
#include "W_FreeRefillReq.pb.h"
#include "W_FreeRefillRes.pb.h"
#include "W_NotiData.pb.h"
#include "W_PingReq.pb.h"
#include "W_RefreshReq.pb.h"
#include "W_RefreshRes.pb.h"
#include "LobbyShopPanel.h"
#include "W_TourEnterReq.pb.h"
#include "W_TourEnterRes.pb.h"
#include "W_TourRefreshRes.pb.h"
#include "W_TourRefreshReq.pb.h"
#include "W_TourInfoRes.pb.h"
#include "W_TourInfoReq.pb.h"
#include "W_NoticeInfoReq.pb.h"
#include "W_NoticeInfoRes.pb.h"

#include "W_DeathMatchInfoReq.pb.h"
#include "W_DeathMatchInfoRes.pb.h"
#include "W_DeathMatchRegisterReq.pb.h"
#include "W_DeathMatchRegisterRes.pb.h"
#include "W_DeathMatchRefreshRes.pb.h"
#include "W_DeathMatchRefreshReq.pb.h"
#include "W_DeathMatchEnterRes.pb.h"
#include "W_DeathMatchEnterReq.pb.h"
#include "LobbyRewardPanel.h"
#include "W_TourIDReq.pb.h"
#include "W_TourIDRes.pb.h"
#include "W_DeathMatchIDReq.pb.h"
#include "W_DeathMatchIDRes.pb.h"
#include "W_DeathMatchRankRes.pb.h"
#include "W_DeathMatchRankReq.pb.h"
#include "W_DeathMatchReplayListReq.pb.h"
#include "W_DeathMatchReplayListRes.pb.h"
#include "W_DeathMatchReplayReq.pb.h"
#include "W_DeathMatchReplayRes.pb.h"
#include "W_TourReplayListReq.pb.h"
#include "W_TourReplayListRes.pb.h"
#include "W_TourReplayReq.pb.h"
#include "W_DeathMatchRegisterCancelReq.pb.h"
#include "W_DeathMatchRegisterCancelRes.pb.h"
#include "W_TourReplayRes.pb.h"
#include "W_TourRewardReq.pb.h"
#include "W_TourRewardRes.pb.h"
#include "W_TourGameReq.pb.h"
#include "W_DeathMatchGameReq.pb.h"
#include "W_TourGameRes.pb.h"
#include "W_DeathMatchGameRes.pb.h"
#include "W_VersionReq.pb.h"
#include "W_VersionRes.pb.h"
#include "SynopsisMainPanel.h"
#include "SynopsisCharacterInfoPanel.h"
#include "SynopsisDialogPanel.h"
#include "GlobalDefine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/FacebookManager.h"
#include "android/GoogleManager.h"
#include "android/IGAWorksManager.h"
#include "android/AndroidUtilManager.h"
#endif
#include "W_PlatformReq.pb.h"
#include "W_PlatformRes.pb.h"
#include "W_ReputeRankReq.pb.h"
#include "W_ReputeRankRes.pb.h"
#include "NotiDataManager.h"
#include "NotiDataManager.h"
#include "LobbyOptionPanel.h"
#include "GoldrefillPanel.h"
#include "LobbyRecordPanel.h"
#include "PanelHelper.h"
#include "RefillMoviePanel.h"
#include "W_FreeChargeReq.pb.h"
#include "W_FreeChargeRes.pb.h"
#include "W_GranChanceReq.pb.h"
#include "W_GranChanceRes.pb.h"
#include "W_LimitShopReq.pb.h"
#include "W_LimitShopRes.pb.h"
#include "W_ReplaySeasonReq.pb.h"
#include "W_ReplaySeasonRes.pb.h"
#include "W_ReplayDeathMatchReq.pb.h"
#include "W_ReplayDeathMatchRes.pb.h"
#include "NxUtil.h"
#include "W_SkinBuyReq.pb.h"
#include "W_SkinBuyRes.pb.h"
#include "W_SkinSelectReq.pb.h"
#include "W_SkinSelectRes.pb.h"
#include "W_FaceFriendGiftSendReq.pb.h"
#include "W_FaceFriendGiftSendRes.pb.h"
#include "W_FaceFriendGiftReceiveReq.pb.h"
#include "W_FaceFriendGiftReceiveRes.pb.h"
#include "W_FaceFriendOfInfoReq.pb.h"
#include "W_FaceFriendOfInfoRes.pb.h"
#include "W_PlatformOutReq.pb.h"
#include "W_PlatformOutRes.pb.h"
#include "W_ModelTabInfo.pb.h"
#include "W_ModelTabBuyReq.pb.h"
#include "W_ModelTabBuyRes.pb.h"
#include "W_ModelTabInventoryBuyReq.pb.h"
#include "W_ModelTabInventoryBuyRes.pb.h"
#include "W_ModelPicBuyReq.pb.h"
#include "W_ModelPicBuyRes.pb.h"
#include "GameService.h"
#include "GameDataManager.h"
#include "ModelGoodsPanel.h"


#define USE_ADULT 1


template<> WebService* Singleton<WebService>::msSingleton = 0;

WebService::WebService()
{
	m_bMsgWait = false;
	m_fMsgWaitTime = 0.f;
	LocalIp = "192.168.0.161";
}

WebService::~WebService()
{
}

void WebService::_sendPreloginReq()
{
	PanelHelper::pushLoadingPanel(GameStringDepot::getSingleton().getString("PRELOGIN_CHECK_REQ_DESC"));
	W_PreLoginReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvPreloginRes), this);
	HttpManager::getSingleton().send(msg);

	SetMsgWait(15.f);
}

void WebService::_recvPreloginRes(HttpMessage* _msg)
{
	EndWait();

	if (_msg->hasCode()) {
		return;
	}

	W_PreLoginRes res;
	res.ParseFromArray(_msg->getData(), _msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_iv() == true) {
		mInitialVector = res.iv();
		if (GameDataManager::getSingletonPtr()->m_LoginType == eLoginType::GUEST)
		{
			//Guest Login
			_sendGuestLoginReq();
		}
		else if (GameDataManager::getSingletonPtr()->m_LoginType == eLoginType::FACEBOOK)
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			//Facebook Login
			CCLog("FacebookManager 1");
			FacebookManager::getSingletonPtr()->ConnectFB();
#endif
		}
		else if (GameDataManager::getSingletonPtr()->m_LoginType == eLoginType::GOOGLE)
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			if (GoogleManager::getSingleton().getGoogleResult()) {
				sendGoogleLoginReq(GoogleManager::getSingleton().getGoogleUserId(), GoogleManager::getSingleton().getGooglePhotoUrl());
			}				
			else {
				GoogleManager::getSingletonPtr()->googleLogin();
			}
#endif
		}		
	}
}

void WebService::_sendGuestLoginReq()
{
	PanelHelper::pushLoadingPanel(GameStringDepot::getSingleton().getString("LOGIN_CHECK_REQ_DESC"));
	vector<string> ids;
	nxTokenize(getUUID(), "-", back_inserter(ids));
	W_LoginReq req;

	//	req.set_uuid(getUUID());

#ifdef TEMP_LOGIN
	req.mutable_ilovegameid()->CopyFrom(LoginScene::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_ilovegamename()->CopyFrom(LoginScene::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.set_group(LoginReq_AccountGroup_TESTER);
#else

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef REFERENCE_MODE
	req.mutable_ilovegameid()->CopyFrom(LoginScene::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_ilovegamename()->CopyFrom(LoginScene::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.set_group(LoginReq_AccountGroup_TESTER);
#else
	//req.mutable_ilovegameid()->CopyFrom(LoginScene::getEncryptString(SocialManager::getSingleton().getUserId(), LOGIN_REQ_KEY, mInitialVector));
	//req.mutable_ilovegamename()->CopyFrom(LoginScene::getEncryptString(SocialManager::getSingleton().getUserName(), LOGIN_REQ_KEY, mInitialVector));
	//req.set_group(LoginReq_AccountGroup_USER);
	req.mutable_devicekey()->CopyFrom(GameDataManager::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.set_logintype(GUEST);
#endif

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	req.mutable_ilovegameid()->CopyFrom(LoginScene::getEncryptString(SocialManager::getSingleton().getUserId(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_ilovegamename()->CopyFrom(LoginScene::getEncryptString(SocialManager::getSingleton().getUserName(), LOGIN_REQ_KEY, mInitialVector));
	req.set_group(LoginReq_AccountGroup_TESTER);
#else
	req.mutable_devicekey()->CopyFrom(GameDataManager::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));

	EncryptString string = GameDataManager::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector);
	//req.set_de()->CopyFrom("haimandang");
	//req.mutable_platformkey()->CopyFrom("haimandang");
	req.set_logintype(GUEST);
#endif

#endif
	req.set_market(getMarketType());

	//if (PushManager::getSingleton().isAvailable()) {
	//	req.set_pushtoken(PushManager::getSingleton().getToken());
	//}

	//req.mutable_uid()->CopyFrom(LoginScene::getEncryptString(NxGetFormatString("%s", uid).c_str(), LOGIN_REQ_KEY, mInitialVector));

	HttpMessage msg(req, HttpResponseHandler(WebService::_recvGuestLoginRes), this);
	HttpManager::getSingleton().loadJSessionId();
	HttpManager::getSingleton().send(msg);

	if (LayerManager::getSingletonPtr()->hasLayer("Title"))
	{
		TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
		_panel->showLoginButton(false);
	}
}

void WebService::_recvGuestLoginRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		if (LayerManager::getSingletonPtr()->hasLayer("Title"))
		{
			TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
			_panel->showLoginButton(true);
		}
		PanelHelper::popLoadingPanel();
		return;
	}

	W_LoginRes res; 
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());
	CCLOG("Player UID  = %d!! ", res.uid());
	CCLOG("Player UID 2 = %d!!", GameDataManager::getSingletonPtr()->m_pPlayerData->GetUID());
	CCLOG("Player UID 3 = %d!!", GameDataManager::getSingletonPtr()->m_pPlayerData->m_UID);

	if (res.success() == true) {
		CCLog("Login success.");
		if (!res.isadultcheckwindow()) {
			CCLog("!!!!!!!!!!!!!!!!!!!!!!!!!adult success.");
			//GameData 요청
			_sendGameDataReq();
		}
		else {
			CCLog("!!!!!!!!!!!!!!!!!!!!!!adult fail");
			GameDataManager::getSingletonPtr()->m_pPlayerData->m_UID = res.uid();
			new AccountPopupPanel(AccountPopupPanel::AGREE_TYPE);
			if (LayerManager::getSingletonPtr()->hasLayer("Title"))
			{
				TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
				_panel->showLoginButton(true);
			}

			//_sendGameDataReq();
		}	
	}
	else {
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}

		if (LayerManager::getSingletonPtr()->hasLayer("Title"))
		{
			TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
			_panel->showLoginButton(true);
		}
		PanelHelper::popLoadingPanel();
		return;
	}

	//if (LayerManager::getSingletonPtr()->hasLayer("Title"))
	//{
	//	TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
	//	_panel->m_TestButton->setEnable(true);
	//}
}



void WebService::_sendGameDataReq()
{
	PanelHelper::pushLoadingPanel(GameStringDepot::getSingleton().getString("GAMEDATA_REQ_DESC"));
	W_GameDataReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvGameDataRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvGameDataRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		if (LayerManager::getSingletonPtr()->hasLayer("Title"))
		{
			TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
			_panel->showLoginButton(true);
		}
		PanelHelper::popLoadingPanel();
		return;
	}

	W_GameDataRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	//Save GameData
	if (res.has_gamedata())
		GameDataManager::getSingletonPtr()->InitGameData(res.gamedata());

	_sendUserDataReq();
}

void WebService::_sendUserDataReq()
{
	PanelHelper::pushLoadingPanel(GameStringDepot::getSingleton().getString("USERINFO_REQ_DESC"));
	W_UserInfoReq req;

	HttpMessage msg(req, HttpResponseHandler(WebService::_recvUserDataRes), this);
	HttpManager::getSingleton().send(msg);	
}

void WebService::_recvUserDataRes(HttpMessage* msg)
{
	CCLOG("Userdata Recieved");
	if (msg->hasCode()) {
		if (LayerManager::getSingletonPtr()->hasLayer("Title"))
		{
			TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
			_panel->showLoginButton(true);
		}
		PanelHelper::popLoadingPanel();
		return;
	}

	W_UserInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_userinfo())
	{
		GameDataManager::getSingleton().setUserInfo(res.userinfo());
		GameDataManager::getSingletonPtr()->RemoveUserDataInfo();
		GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->SetData(&(res.userinfo().playerinfo()));
		GameDataManager::getSingletonPtr()->m_pRecordInfo = new W_RecordInfo(res.userinfo().recordinfo());
		int _size = res.userinfo().characterinfo_size();
		GameDataManager::getSingletonPtr()->m_pCharacterInfoList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_CharacterInfo* _pInfo = new W_CharacterInfo(res.userinfo().characterinfo(_i));
			GameDataManager::getSingletonPtr()->m_pCharacterInfoList.push_back(_pInfo);
		}

		_size = res.userinfo().letterinfo_size();
		GameDataManager::getSingletonPtr()->m_pLetterInfoList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_LetterInfo* _pInfo = new W_LetterInfo(res.userinfo().letterinfo(_size - _i - 1));
			GameDataManager::getSingletonPtr()->m_pLetterInfoList.push_back(_pInfo);
		}

		_size = res.userinfo().questinfo_size();
		int _sizeDaily = 0;
		int _sizeWeekly = 0;
		for (int _i = 0; _i < _size; _i++)
		{
			if (W_QuestData_eQuestType::W_QuestData_eQuestType_Daily == res.userinfo().questinfo(_i).questtype())
				_sizeDaily++;
			else
				_sizeWeekly++;
		}
		GameDataManager::getSingletonPtr()->m_pQuestDailyList.reserve(_sizeDaily);
		GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.reserve(_sizeWeekly);
		for (int _i = 0; _i < _size; _i++)
		{
			W_QuestInfo* _pInfo = new W_QuestInfo(res.userinfo().questinfo(_size - _i - 1));
			if (W_QuestData_eQuestType::W_QuestData_eQuestType_Daily == res.userinfo().questinfo(_i).questtype())
				GameDataManager::getSingletonPtr()->m_pQuestInfoList.push_back(_pInfo);
			else
				GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.push_back(_pInfo);
			
		}

		_size = res.userinfo().friendofinfo().friendinfo_size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _pInfo = new W_FriendInfo(res.userinfo().friendofinfo().friendinfo(_size - _i - 1));
			GameDataManager::getSingletonPtr()->m_FriendDataList.push_back(_pInfo);
		}

		_size = res.userinfo().replaysaveinfo_size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ReplaySaveInfo* _pInfo = new W_ReplaySaveInfo(res.userinfo().replaysaveinfo(_size - _i - 1));
			GameDataManager::getSingletonPtr()->m_ReplaySaveList.push_back(_pInfo);
		}

		_size = res.userinfo().eventinfo_size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_EventInfo* _pInfo = new W_EventInfo(res.userinfo().eventinfo(_size - _i - 1));
			GameDataManager::getSingletonPtr()->m_EventList.push_back(_pInfo);
		}

		_size = res.userinfo().lobby_size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ChannelInfo* _pInfo = new W_ChannelInfo(res.userinfo().lobby(_i));
			CheckAndRedirectIP(_pInfo);
			GameDataManager::getSingletonPtr()->m_pLobbyChannelList.push_back(_pInfo);
		}

		_size = res.userinfo().poker7_size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ChannelInfo* _pInfo = new W_ChannelInfo(res.userinfo().poker7(_i));
			CheckAndRedirectIP(_pInfo);
			GameDataManager::getSingletonPtr()->m_p7PokerChannelList.push_back(_pInfo);
		}

		_size = res.userinfo().highlow_size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ChannelInfo* _pInfo = new W_ChannelInfo(res.userinfo().highlow(_i));
			CheckAndRedirectIP(_pInfo);
			GameDataManager::getSingletonPtr()->m_pHighLowChannelList.push_back(_pInfo);
			
		}

		_size = res.userinfo().baduki_size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ChannelInfo* _pInfo = new W_ChannelInfo(res.userinfo().baduki(_i));
			CheckAndRedirectIP(_pInfo);
			GameDataManager::getSingletonPtr()->m_pBadukiChannelList.push_back(_pInfo);
			
		}

		_size = res.userinfo().holdem_size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ChannelInfo* _pInfo = new W_ChannelInfo(res.userinfo().holdem(_i));
			CheckAndRedirectIP(_pInfo);
			GameDataManager::getSingletonPtr()->m_pHoldemChannelList.push_back(_pInfo);
			
		}

		////서버에서 받아온 Player의 모델정보 초기화

		_size = res.userinfo().modeltabinfo().size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ModelTabInfo* _pInfo = new W_ModelTabInfo(res.userinfo().modeltabinfo(_i));
			GameDataManager::getSingletonPtr()->InvenTapInfo_MAXIM.push_back(_pInfo);
			std::vector<int> tmp;
			for (int _j = 0; _j < _pInfo->buylist().size(); _j++)
			{
				tmp.push_back(_pInfo->buylist(_j));
			}
			GameDataManager::getSingletonPtr()->BuyList_MAXIM.push_back(tmp);
		}
		GameDataManager::getSingletonPtr()->InvenTapInfo_RACING = GameDataManager::getSingletonPtr()->InvenTapInfo_MAXIM;
		GameDataManager::getSingletonPtr()->InvenTapInfo_RACING[0]->set_tabinventorycount(3);
		if (res.userinfo().has_tourofinfo())
		{
			GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
			if (GameDataManager::getSingletonPtr()->m_TourOfInfo == nullptr)
			{
				GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.userinfo().tourofinfo());
				if (GameDataManager::getSingletonPtr()->m_TourOfInfo->has_gameinfo())
				{
					GameDataManager::getSingletonPtr()->m_hasTourGameInfo = true;
				}
				if (GameDataManager::getSingletonPtr()->m_TourOfInfo->has_resultinfo())
				{
					GameDataManager::getSingletonPtr()->m_hasTourResultInfo = true;
				}
			}
		}

		if (res.userinfo().has_deathmatchofinfo())
		{
			GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
			if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo == nullptr)
			{
				GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.userinfo().deathmatchofinfo());
				if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo_size() != 0) {
					GameDataManager::getSingletonPtr()->Survival_RegisterableTime = res.userinfo().deathmatchofinfo().matchinfo(0).registerabletime();
					GameDataManager::getSingletonPtr()->Survival_RegisterExpireTime = res.userinfo().deathmatchofinfo().matchinfo(0).registerexpiretime();
					GameDataManager::getSingletonPtr()->Survival_WaitableTime = res.userinfo().deathmatchofinfo().matchinfo(0).waitabletime();
					GameDataManager::getSingletonPtr()->Survival_WaitExpireTime = res.userinfo().deathmatchofinfo().matchinfo(0).waitexpiretime();
					GameDataManager::getSingletonPtr()->Survial_gameexpiretime = res.userinfo().deathmatchofinfo().matchinfo(0).gameexpiretime();
					GameDataManager::getSingletonPtr()->Survival_GameableTime = res.userinfo().deathmatchofinfo().matchinfo(0).gameabletime();
					GameDataManager::getSingletonPtr()->Survival_UserStatus = res.userinfo().deathmatchofinfo().matchinfo(0).userstatus();

					GameDataManager::getSingletonPtr()->m_IsSurvivalReservated = res.userinfo().deathmatchofinfo().matchinfo(0).isregister();
				}
				else
					CCLOG("Matchinfo is null");
				

				if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->has_gameinfo())
				{
					GameDataManager::getSingletonPtr()->m_hasSurvivalGameInfo = true;
				}
				else
				{
					GameDataManager::getSingletonPtr()->m_hasSurvivalGameInfo = false;
				}
			}
		}

		//Open
		if (res.userinfo().has_playerinfo() && res.userinfo().playerinfo().has_basecharacter())
		{
			if (res.userinfo().playerinfo().basecharacter() > 0)
			{
				//_sendChannelReq();
				LoginEnterLobby();
			}
			else
			{
				SceneUtil::changeScene(SceneUtil::SceneSynopsis);
			}
		}

		if (res.userinfo().has_recordseasoninfo()) {
			GameDataManager::getSingleton().setRecordSeasonInfo(res.userinfo().recordseasoninfo());
		}

		if (res.userinfo().has_recorddeathmatchinfo()) {
			GameDataManager::getSingleton().setRecordDeathMatchInfo(res.userinfo().recorddeathmatchinfo());
		}

		if (res.userinfo().has_attendseveninfo()) {
			GameDataManager::getSingleton().setAttendSevenInfo(res.userinfo().attendseveninfo());
		}
		NotiDataManager::getSingleton().initData();
		//playerinfo uid사용하므로 셋팅된 후에 initdata 한다.
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingleton().getScene(SceneUtil::SceneLobby));
		if (_pScene) {
			int _size = res.notidata_size();
			for (int _i = 0; _i < _size; _i++)
			{
				_pScene->addNotidata(res.notidata(_i));
			}
		}

		//접속 다시 하게 처리
		setLobbyIp("");
		setLobbyPort(0);
	}
}

void WebService::LoginEnterLobby()
{
	int lowPeopleIndex = 0;
	int lowPeople = INT_MAX;
	for (int i = 0; i < GameDataManager::getSingletonPtr()->m_pLobbyChannelList.size(); i++)
	{
		W_ChannelInfo* channelInfo = GameDataManager::getSingletonPtr()->m_pLobbyChannelList[i];
		if (channelInfo && channelInfo->usercount() < lowPeople) {
			lowPeopleIndex = i;
			lowPeople = channelInfo->usercount();
		}
	}

	if (GameDataManager::getSingletonPtr()->m_pLobbyChannelList.size() > 0)
	{
		m_LobbyIp = GameDataManager::getSingletonPtr()->m_pLobbyChannelList[lowPeopleIndex]->ip();
		m_LobbyPort = GameDataManager::getSingletonPtr()->m_pLobbyChannelList[lowPeopleIndex]->port();

		TCPService::getSingleton().Connect(GAMBLE_GAME_URL.empty() ? m_LobbyIp : GAMBLE_GAME_URL, m_LobbyPort, false);

		//멀로 저장했는지 저장한다.
		CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyLoginType.c_str(), GameDataManager::getSingletonPtr()->m_LoginType);
		CCUserDefault::sharedUserDefault()->flush();
	}
}

void WebService::SendUserInfoReq()
{
	W_UserInfoReq req;

	HttpMessage msg(req, HttpResponseHandler(WebService::RecvUserInfoRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::RecvUserInfoRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		if (LayerManager::getSingletonPtr()->hasLayer("Title"))
		{
			TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
			_panel->showLoginButton(true);
		}
		return;
	}

	W_UserInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_userinfo())
	{
		GameDataManager::getSingleton().setUserInfo(res.userinfo());
		GameDataManager::getSingletonPtr()->RemoveUserDataInfo();

		GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->SetData(&(res.userinfo().playerinfo()));
		GameDataManager::getSingletonPtr()->m_pRecordInfo = new W_RecordInfo(res.userinfo().recordinfo());
		int _size = res.userinfo().characterinfo_size();
		GameDataManager::getSingletonPtr()->m_pCharacterInfoList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_CharacterInfo* _pInfo = new W_CharacterInfo(res.userinfo().characterinfo(_i));
			GameDataManager::getSingletonPtr()->m_pCharacterInfoList.push_back(_pInfo);
		}

		_size = res.userinfo().letterinfo_size();
		GameDataManager::getSingletonPtr()->m_pLetterInfoList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_LetterInfo* _pInfo = new W_LetterInfo(res.userinfo().letterinfo(_size - _i - 1));
			GameDataManager::getSingletonPtr()->m_pLetterInfoList.push_back(_pInfo);
		}

		_size = res.userinfo().questinfo_size();
		int _sizeDaily = 0;
		int _sizeWeekly = 0;
		for (int _i = 0; _i < _size; _i++)
		{
			if (W_QuestData_eQuestType::W_QuestData_eQuestType_Daily == res.userinfo().questinfo(_i).questtype())
				_sizeDaily++;
			else
				_sizeWeekly++;
		}
		GameDataManager::getSingletonPtr()->m_pQuestDailyList.reserve(_sizeDaily);
		GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.reserve(_sizeWeekly);
		for (int _i = 0; _i < _size; _i++)
		{

			W_QuestInfo* _pInfo = new W_QuestInfo(res.userinfo().questinfo(_size - _i - 1));
			if (W_QuestData_eQuestType::W_QuestData_eQuestType_Daily == res.userinfo().questinfo(_i).questtype())
				GameDataManager::getSingletonPtr()->m_pQuestInfoList.push_back(_pInfo);
			else
				GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.push_back(_pInfo);

		}
		/*_size = res.userinfo().questinfo_size();
		GameDataManager::getSingletonPtr()->m_pQuestInfoList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_QuestInfo* _pInfo = new W_QuestInfo(res.userinfo().questinfo(_size - _i - 1));
			GameDataManager::getSingletonPtr()->m_pQuestInfoList.push_back(_pInfo);
		}*/
				
	}

	if (res.has_freerefill())
	{
		if (res.freerefill())
		{
			PanelHelper::pushAllinPopupPanel();
		}
	}
	
	int _size = res.notidata_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_NotiData _data = res.notidata(_size - 1 - _i);
		SimplePopupPanel* _pNotiPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _data.desc(), _data.title());
		LayerManager::getSingleton().pushDynamicLayer(_pNotiPopup, DYNAMIC_PUSH_LAYER);
	}
	
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_PLAYER_INFO_RES);

	_sendEventListReq();
	SendChannelListUpdateReq();
}

void WebService::_sendChannelReq()
{
	W_ChannelReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvChannelRes), this);
	HttpManager::getSingleton().send(msg);
	std::chrono::system_clock::now().time_since_epoch();
}

void WebService::_recvChannelRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		if (LayerManager::getSingletonPtr()->hasLayer("Title"))
		{
			TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
			_panel->showLoginButton(true);

		}
		return;
	}

	W_ChannelRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	//SaveChanelData and LobbyChannelCheck
	int _size = res.lobby_size();
	GameDataManager::getSingletonPtr()->m_pLobbyChannelList.reserve(_size);

	for (int _i = 0; _i < _size; _i++)
	{
		W_ChannelInfo* _pInfo = new W_ChannelInfo(res.lobby(_i));
		GameDataManager::getSingletonPtr()->m_pLobbyChannelList.push_back(_pInfo);
	}

	//Login
	if (GameDataManager::getSingletonPtr()->m_pLobbyChannelList.size() > 0)
	{
		int _LobbySelect = 0; //_lobbyChannelList[rand() % _lobbyChannelList.size()];
		m_LobbyIp = GameDataManager::getSingletonPtr()->m_pLobbyChannelList[_LobbySelect]->ip();
		m_LobbyPort = GameDataManager::getSingletonPtr()->m_pLobbyChannelList[_LobbySelect]->port();
		
		TCPService::getSingleton().Connect(GAMBLE_GAME_URL.empty() ? m_LobbyIp : GAMBLE_GAME_URL, m_LobbyPort, false);
	}
}

void WebService::SendChannelListReq()
{
	W_ChannelReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::RecvChannelListRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::RecvChannelListRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		GameDataManager::getSingletonPtr()->FreeUiProcess();
		return;
	}

	GameDataManager::getSingletonPtr()->Remove7PokerList();
	GameDataManager::getSingletonPtr()->RemoveHighLowList();
	GameDataManager::getSingletonPtr()->RemoveBadukiList();
	GameDataManager::getSingletonPtr()->RemoveHoldemList();

	W_ChannelRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	//SaveChanelData
	//int _size = res.lobby_size();
	//GameDataManager::getSingletonPtr()->m_pLobbyChannelList.reserve(_size);
	//for (int _i = 0; _i < _size; _i++)
	//{
	//	W_ChannelInfo* _pInfo = new W_ChannelInfo(res.lobby(_i));
	//	GameDataManager::getSingletonPtr()->m_pLobbyChannelList.push_back(_pInfo);
	//}

	int _7PokerSize = res.poker7_size();
	GameDataManager::getSingletonPtr()->m_p7PokerChannelList.reserve(_7PokerSize);
	for (int _i = 0; _i < _7PokerSize; _i++)
	{
		W_ChannelInfo* _pInfo = new W_ChannelInfo(res.poker7(_i));
		CheckAndRedirectIP(_pInfo);
		GameDataManager::getSingletonPtr()->m_p7PokerChannelList.push_back(_pInfo);
	}

	int _HighLowSize = res.highlow_size();
	GameDataManager::getSingletonPtr()->m_pHighLowChannelList.reserve(_HighLowSize);
	for (int _i = 0; _i < _HighLowSize; _i++)
	{
		W_ChannelInfo* _pInfo = new W_ChannelInfo(res.highlow(_i));
		CheckAndRedirectIP(_pInfo);
		GameDataManager::getSingletonPtr()->m_pHighLowChannelList.push_back(_pInfo);
	}

	int _BadukiSize = res.baduki_size();
	GameDataManager::getSingletonPtr()->m_pBadukiChannelList.reserve(_BadukiSize);
	for (int _i = 0; _i < _BadukiSize; _i++)
	{
		W_ChannelInfo* _pInfo = new W_ChannelInfo(res.baduki(_i));
		CheckAndRedirectIP(_pInfo);
		GameDataManager::getSingletonPtr()->m_pBadukiChannelList.push_back(_pInfo);
	}

	int _HoldemiSize = res.holdem_size();
	GameDataManager::getSingletonPtr()->m_pHoldemChannelList.reserve(_HoldemiSize);
	for (int _i = 0; _i < _HoldemiSize; _i++)
	{
		W_ChannelInfo* _pInfo = new W_ChannelInfo(res.holdem(_i));
		CheckAndRedirectIP(_pInfo);
		GameDataManager::getSingletonPtr()->m_pHoldemChannelList.push_back(_pInfo);
	}

	//Show Channel List
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_CHANNEL_LIST_RES);
}

void WebService::SendChannelListUpdateReq()
{
	W_ChannelReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::RecvChannelListUpdateRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::RecvChannelListUpdateRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	GameDataManager::getSingletonPtr()->Remove7PokerList();
	GameDataManager::getSingletonPtr()->RemoveHighLowList();
	GameDataManager::getSingletonPtr()->RemoveBadukiList();
	GameDataManager::getSingletonPtr()->RemoveHoldemList();

	W_ChannelRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	int _7PokerSize = res.poker7_size();
	GameDataManager::getSingletonPtr()->m_p7PokerChannelList.reserve(_7PokerSize);
	for (int _i = 0; _i < _7PokerSize; _i++)
	{
		W_ChannelInfo* _pInfo = new W_ChannelInfo(res.poker7(_i));
		CheckAndRedirectIP(_pInfo);
		GameDataManager::getSingletonPtr()->m_p7PokerChannelList.push_back(_pInfo);
	}

	int _HighLowSize = res.highlow_size();
	GameDataManager::getSingletonPtr()->m_pHighLowChannelList.reserve(_HighLowSize);
	for (int _i = 0; _i < _HighLowSize; _i++)
	{
		W_ChannelInfo* _pInfo = new W_ChannelInfo(res.highlow(_i));
		CheckAndRedirectIP(_pInfo);
		GameDataManager::getSingletonPtr()->m_pHighLowChannelList.push_back(_pInfo);
	}

	int _BadukiSize = res.baduki_size();
	GameDataManager::getSingletonPtr()->m_pBadukiChannelList.reserve(_BadukiSize);
	for (int _i = 0; _i < _BadukiSize; _i++)
	{
		W_ChannelInfo* _pInfo = new W_ChannelInfo(res.baduki(_i));
		CheckAndRedirectIP(_pInfo);
		GameDataManager::getSingletonPtr()->m_pBadukiChannelList.push_back(_pInfo);
	}

	int _HoldemiSize = res.holdem_size();
	GameDataManager::getSingletonPtr()->m_pHoldemChannelList.reserve(_HoldemiSize);
	for (int _i = 0; _i < _HoldemiSize; _i++)
	{
		W_ChannelInfo* _pInfo = new W_ChannelInfo(res.holdem(_i));
		CheckAndRedirectIP(_pInfo);
		GameDataManager::getSingletonPtr()->m_pHoldemChannelList.push_back(_pInfo);
	}

}

void WebService::_sendLetterUpdateReq(int64 seq)
{
	W_LetterUpdateReq req;
	req.set_seq(seq);
	
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvLetterUpdateRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvLetterUpdateRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_LetterUpdateRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_rewardinfo()) {
		PanelHelper::pushLetterRewardPanel(res.rewardinfo());
		//편지를 받을때 처리
		NotiDataManager::getSingleton().setReceiveLetter(res.rewardinfo());
	}


	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	GameDataManager::getSingletonPtr()->RemoveLetterInfoList();

	int _infoSize = res.letterinfo_size();
	GameDataManager::getSingletonPtr()->m_pLetterInfoList.reserve(_infoSize);
	for (int _i = 0; _i < _infoSize; _i++)
	{
		W_LetterInfo* _info = new W_LetterInfo(res.letterinfo(_infoSize-_i-1));

		GameDataManager::getSingletonPtr()->m_pLetterInfoList.push_back(_info);
	}		

	int _size = res.characterinfo_size();
	GameDataManager::getSingletonPtr()->RemoveCharacterInfoList();
	GameDataManager::getSingletonPtr()->m_pCharacterInfoList.reserve(_size);
	for (int _i = 0; _i < _size; _i++)
	{
		W_CharacterInfo* _pInfo = new W_CharacterInfo(res.characterinfo(_i));
		GameDataManager::getSingletonPtr()->m_pCharacterInfoList.push_back(_pInfo);
	}

	GameDataManager::getSingleton().getUserInfo()->clear_skininfo();
	for (int i = 0; i < res.skininfo_size(); i++)
	{
		W_SkinInfo* skinInfo = GameDataManager::getSingleton().getUserInfo()->add_skininfo();
		skinInfo->CopyFrom(res.skininfo(i));
	}

	if (LayerManager::getSingleton().hasLayerType<LobbyInventoryPanel>()) {
		LobbyInventoryPanel* _pPanel = dynamic_cast<LobbyInventoryPanel*>(LayerManager::getSingleton().getLayerType<LobbyInventoryPanel>());
		_pPanel->UpdateCell();
	}

	
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_LETTER_LIST_RES);
}


void WebService::_sendQuestListUpdateReq()
{
	W_QuestListReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvQuestListUpdateRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvQuestListUpdateRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		GameDataManager::getSingletonPtr()->FreeUiProcess();
		return;
	}

	W_QuestListRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveQuestInfoList();
	
	int _infoSize = res.questinfo_size();
	for (int _i = 0; _i < _infoSize; _i++)
	{
		string ee = res.GetTypeName();
		W_QuestInfo* _info = new W_QuestInfo(res.questinfo(_infoSize - _i - 1));
		if (W_QuestData_eQuestType::W_QuestData_eQuestType_Daily == _info->questtype())
			GameDataManager::getSingletonPtr()->m_pQuestDailyList.push_back(_info);
		else
			GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.push_back(_info);
	}

	/*int _infoSize = res.questinfo_size();
	for (int _i = 0; _i < _infoSize; _i++)
	{
		string ee = res.GetTypeName();
		W_QuestInfo* _info = new W_QuestInfo(res.questinfo(_infoSize - _i - 1));

		GameDataManager::getSingletonPtr()->m_pQuestInfoList.push_back(_info);
	}*/
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_OPEN_QUEST_LIST_RES);
}


void WebService::_sendQuestUpdateReq(int64 seq, int _type)
{
	W_QuestUpdateReq req;
	req.set_seq(seq);
	req.set_type(_type);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvQuestUpdateRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvQuestUpdateRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	
	W_QuestUpdateRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());
	}

	int _size = res.characterinfo_size();
	GameDataManager::getSingletonPtr()->m_pCharacterInfoList.reserve(_size);
	for (int _i = 0; _i < _size; _i++)
	{
		W_CharacterInfo* _pInfo = new W_CharacterInfo(res.characterinfo(_i));
		GameDataManager::getSingletonPtr()->m_pCharacterInfoList.push_back(_pInfo);
	}


	GameDataManager::getSingletonPtr()->RemoveQuestInfoList();

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
		

	int _infoSize = res.questinfo_size();
	for (int _i = 0; _i < _infoSize; _i++)
	{
		string ee = res.GetTypeName();
		W_QuestInfo* _info = new W_QuestInfo(res.questinfo(_infoSize - _i - 1));
		if (W_QuestData_eQuestType::W_QuestData_eQuestType_Daily == _info->questtype())
			GameDataManager::getSingletonPtr()->m_pQuestDailyList.push_back(_info);
		else
			GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.push_back(_info);
		W_QuestInfo_eQuestStatus a = _info->queststatus();
	}

	/*int _infoSize = res.questinfo_size();
	for (int _i = 0; _i < _infoSize; _i++)
	{
		W_QuestInfo* _info = new W_QuestInfo(res.questinfo(_infoSize - _i - 1));

		GameDataManager::getSingletonPtr()->m_pQuestInfoList.push_back(_info);
	}*/

	//보상 뿌린다.
	if (res.has_rewardinfo()) {
		PanelHelper::pushEventRewardPanel(res.rewardinfo());
		//편지를 받을때 처리
		NotiDataManager::getSingleton().setReceiveLetter(res.rewardinfo());
	}
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_QUEST_LIST_RES);
}

void WebService::SendModelPicBuyReq(int id)
{
	W_ModelPicBuyReq req;
	int tabid = GameDataManager::getSingletonPtr()->getModelInfo(id, ModelInfo::TAP_ID);
	req.set_tabid(tabid);
	req.set_picid(id); 
	HttpMessage msg(req, HttpResponseHandler(WebService::RecvModelPicBuyRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::RecvModelPicBuyRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
		
	W_ModelPicBuyRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());
	
	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}
	GameDataManager::getSingletonPtr()->BuyList_MAXIM.clear();
	GameDataManager::getSingletonPtr()->InvenTapInfo_MAXIM.clear();

	if (res.modeltabinfo().size() != 0) {
		for (int _i = 0; _i < res.modeltabinfo().size(); _i++)
		{
			W_ModelTabInfo* _pInfo = new W_ModelTabInfo(res.modeltabinfo(_i));
			GameDataManager::getSingletonPtr()->InvenTapInfo_MAXIM.push_back(_pInfo);
			std::vector<int> tmp;
			for (int _j = 0; _j < _pInfo->buylist().size(); _j++)
			{
				tmp.push_back(_pInfo->buylist(_j));
			}
			GameDataManager::getSingletonPtr()->BuyList_MAXIM.push_back(tmp);
		}
	}
	
	GameDataManager::getSingletonPtr()->BuyMessageCaller->getImage("img_model_blur_maxim")->setVisible(false);
	GameDataManager::getSingletonPtr()->setPlayerInfo(res.playerinfo());
	GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney = res.playerinfo().gamemoney();
	LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(
		SimplePopupPanel::SimplePopupType::OKNotice, 
		GameStringDepot::getSingleton().getString("SKIN_CONFIRM_DESC").c_str(),
		GameStringDepot::getSingleton().getString("BuySucessPanel_COMPLETE").c_str()), 
		DYNAMIC_PUSH_LAYER
	);
	
	
}

void WebService::SendBuySlotReq(int tId)
{
	W_ModelTabInventoryBuyReq req;
	req.set_tabid(tId);
	HttpMessage msg(req, HttpResponseHandler(WebService::RecvBuySlotRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::RecvBuySlotRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_ModelTabInventoryBuyRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());
 
	if (res.success() == false)
	{
		if (res.has_errorcode()){
			ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
 
		return;
	}
	GameDataManager::getSingletonPtr()->setPlayerInfo(res.playerinfo());

	GameDataManager::getSingletonPtr()->InvenTapInfo_MAXIM.clear();
	int _size = res.modeltabinfo().size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_ModelTabInfo* _pInfo = new W_ModelTabInfo(res.modeltabinfo(_i));
		GameDataManager::getSingletonPtr()->InvenTapInfo_MAXIM.push_back(_pInfo);
	}
}

void WebService::SendBuyTapReq(int tid)
{
	W_ModelTabBuyReq req;
	req.set_tabid(tid);
	HttpMessage msg(req, HttpResponseHandler(WebService::RecvBuyTapRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::RecvBuyTapRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_ModelTabBuyRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode()) {
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}

		return;
	}

	GameDataManager::getSingletonPtr()->InvenTapInfo_MAXIM.clear();
	int _size = res.modeltabinfo().size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_ModelTabInfo* _pInfo = new W_ModelTabInfo(res.modeltabinfo(_i));
		GameDataManager::getSingletonPtr()->InvenTapInfo_MAXIM.push_back(_pInfo);
		std::vector<int> tmp;
		for (int _j = 0; _j < _pInfo->buylist().size(); _j++)
		{
			tmp.push_back(_pInfo->buylist(_j));
		}
		GameDataManager::getSingletonPtr()->BuyList_MAXIM.push_back(tmp);
	}
}

void WebService::_sendSlotMachineReq(W_SlotMachineReq_eSlotMachineResourceType type)
{
	W_SlotMachineReq req;
	req.set_resourcetype(type);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvSlotMachineRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvSlotMachineRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_SlotMachineRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}

		//에러일때 slotIcon 초기화.
		for (int _i = 0; _i < 3; _i++)
		{
			GameDataManager::getSingletonPtr()->m_SlotMachineIcon[_i] = -1;
		}

		GameDataManager::getSingletonPtr()->SetSlotMachineRewardInfo(nullptr);
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_SLOTMACHINE_INFO_RES);
		return;
	}
	std::vector<int> tmp;
	int _size = res.pattern_size();
	for (int _i = 0; _i < _size; _i++)
	{
		tmp.push_back(res.pattern(_i));
		if (_i >= 3)
			continue;
		
		GameDataManager::getSingletonPtr()->m_SlotMachineIcon[_i] = res.pattern(_i);
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_rewardinfo())
	{
		W_RewardInfo* _pInfo = new W_RewardInfo(res.rewardinfo());
		GameDataManager::getSingletonPtr()->SetSlotMachineRewardInfo(_pInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_SLOTMACHINE_INFO_RES);

}

void WebService::_sendCashBuyReq(int32 id)
{
	W_CashBuyReq req;
	req.set_id(id);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvCashBuyRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvCashBuyRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_CashBuyRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
	{
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
	}	
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_PLAYER_INFO_RES);
}

void WebService::_sendMonthlyClassBuyReq(int32 id)
{
	mMemberShipBuyId = id;
	W_MonthlyClassBuyReq req;
	req.set_id(mMemberShipBuyId);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvMonthlyClassBuyRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvMonthlyClassBuyRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_MonthlyClassBuyRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_rewardinfo()) {
		PanelHelper::pushMemberShipBuySucessPanel(mMemberShipBuyId, res.rewardinfo());
	}

	if (res.has_playerinfo()) {
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_PLAYER_INFO_RES);
}

void WebService::_sendPlayerNameReq(string name)
{
	W_PlayerNameReq req;
	req.set_name(name);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvPlayerNameRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvPlayerNameRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_PlayerNameRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}
	LayerManager::getSingleton().popLayer();

	if (res.has_playerinfo())
	{
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_PLAYER_NAME_RES);
	}	
}

void WebService::_sendBankInReq(int64 gamemoney)
{
	W_BankInReq req;
	req.set_gamemoney(gamemoney);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvBankInRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvBankInRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_BankInRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}		
	}
	else
	{
		int64 _curMoney = GameDataManager::getSingleton().getPlayerInfo().gamemoney();
		int64 _nextMoney = res.playerinfo().gamemoney();
		//bankinres
		PanelHelper::pushBankInResultPanel(_curMoney - _nextMoney);
	}

	if (res.has_playerinfo())
	{
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_BANK_IN_RES);
	}
	
}

void WebService::_sendBankOutReq(int64 gamemoney)
{
	W_BankOutReq req;
	req.set_gamemoney(gamemoney);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvBankOutRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvBankOutRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_BankOutRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}
	else
	{
		int64 _curMoney = GameDataManager::getSingleton().getPlayerInfo().gamemoney();
		int64 _nextMoney = res.playerinfo().gamemoney();
		//bankinres
		PanelHelper::pushBankOutResultPanel(_nextMoney - _curMoney);
	}

	if (res.has_playerinfo())
	{
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_BANK_OUT_RES);
	}
}

void WebService::_sendFriendAddReq(vector<int64>& _uidList)
{
	CCLog("FriendCellMiddle::_sendFriendAddReq");
	W_FriendAddReq req;
	int _size = _uidList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		req.add_uid(_uidList[_i]);
	}
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendAddRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendAddRes(HttpMessage* msg)
{
	CCLog("FriendCellMiddle::_recvFriendAddRes");
	if (msg->hasCode()) {
		return;
	}
	W_FriendAddRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == true) {

		if (res.has_count())
			int32 _count = res.count();

		W_FriendOfInfo _friendOfInfo = res.friendofinfo();

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

		_size = _friendOfInfo.requestinfo_size();
		GameDataManager::getSingletonPtr()->RemoveRequestDataList();
		GameDataManager::getSingletonPtr()->m_RequestDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.requestinfo(_i));
			GameDataManager::getSingletonPtr()->m_RequestDataList.push_back(_info);
		}

		//facebook 리스트 정보
		GameDataManager::getSingletonPtr()->mRewardIds.clear();
		_size = _friendOfInfo.facefriendinviterewardlist_size();
		for (int _i = 0; _i < _size; _i++)
		{
			GameDataManager::getSingletonPtr()->mRewardIds.push_back(_friendOfInfo.facefriendinviterewardlist(_i));
		}

		PanelHelper::pushAnnounceNotiPanel(GameStringDepot::getSingleton().getString("ADD_FRIEND_REQUEST"));

		GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_ADD_FRIEND_LIST_RES);
	}
	else {
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}
}

void WebService::_sendFriendGiftReceiveReq(vector<int64>& _uidList)
{
	W_FriendGiftReceiveReq req;
	
	int _size = _uidList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		req.add_uid(_uidList[_i]);
	}
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendGiftReceiveRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendGiftReceiveRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FriendGiftReceiveRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo()) 
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (!res.has_friendofinfo())
		return;

	W_FriendOfInfo _friendOfInfo = res.friendofinfo();

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

	PanelHelper::pushAnnounceNotiPanel(GameStringDepot::getSingleton().getString("FRIEND_RECV_CHIP"));
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_UPDATE_FRIEND_LIST_RES);
}

void WebService::_sendFriendGiftSendReq(vector<int64>& _uidList)
{
	W_FriendGiftSendReq req;

	int _size = _uidList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		req.add_uid(_uidList[_i]);
	}
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendGiftSendRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendGiftSendRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FriendGiftSendRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (!res.has_friendofinfo())
		return;

	W_FriendOfInfo _friendOfInfo = res.friendofinfo();

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

	PanelHelper::pushAnnounceNotiPanel(GameStringDepot::getSingleton().getString("FRIEND_SEND_CHIP"));

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_UPDATE_FRIEND_LIST_RES);
}

void WebService::_sendFriendOfInfoReq()
{
	W_FriendOfInfoReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendOfInfoRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendOfInfoRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		GameDataManager::getSingletonPtr()->FreeUiProcess();
		return;
	}
	W_FriendOfInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_friendofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveSnsDataList();
		GameDataManager::getSingletonPtr()->RemoveFriendDataList();
		W_FriendOfInfo _friendOfInfo = res.friendofinfo();
		
		int _size = _friendOfInfo.facefriendinfo_size();
		
		GameDataManager::getSingletonPtr()->m_SnsDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.facefriendinfo(_i));
			GameDataManager::getSingletonPtr()->m_SnsDataList.push_back(_info);
		}

		_size = _friendOfInfo.friendinfo_size();
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
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_FRIEND_LIST_RES);
	}
}

void WebService::_sendFriendReCommendReq()
{
	W_FriendReCommendReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendReCommendRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendReCommendRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FriendReCommendRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());
	
	GameDataManager::getSingletonPtr()->RemoveRecommendDataList();
	int _size = res.recommendinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_FriendInfo* _friendInfo = new W_FriendInfo(res.recommendinfo(_i));
		GameDataManager::getSingletonPtr()->m_RecommendDataList.push_back(_friendInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_RECOMMEND_FRIEND_LIST_RES);
}

void WebService::_sendFriendRejectReq(vector<int64>& _uidList)
{
	W_FriendRejectReq req;

	int _size = _uidList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		req.add_uid(_uidList[_i]);
	}
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendRejectdRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendRejectdRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FriendRejectRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveRequestDataList();
	int _size = res.requestinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_FriendInfo* _friendInfo = new W_FriendInfo(res.requestinfo(_i));
		GameDataManager::getSingletonPtr()->m_RequestDataList.push_back(_friendInfo);
	}

	PanelHelper::pushAnnounceNotiPanel(GameStringDepot::getSingleton().getString("REJECT_FRIEND_REQUEST"));
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_RECOMMEND_FRIEND_LIST_RES);
}

void WebService::_sendFriendRemoveReq(int64 _uid)
{
	W_FriendRemoveReq req;
	req.set_uid(_uid);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendRemoveRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendRemoveRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_FriendRemoveRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}
	
	if (res.has_friendofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveSnsDataList();
		GameDataManager::getSingletonPtr()->RemoveFriendDataList();
		GameDataManager::getSingletonPtr()->RemoveRecommendDataList();
		GameDataManager::getSingletonPtr()->RemoveRequestDataList();

		W_FriendOfInfo _friendOfInfo = res.friendofinfo();

		int _size = _friendOfInfo.facefriendinfo_size();

		GameDataManager::getSingletonPtr()->m_SnsDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.facefriendinfo(_i));
			GameDataManager::getSingletonPtr()->m_SnsDataList.push_back(_info);
		}

		_size = _friendOfInfo.friendinfo_size();
		GameDataManager::getSingletonPtr()->m_FriendDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.friendinfo(_i));
			GameDataManager::getSingletonPtr()->m_FriendDataList.push_back(_info);
		}

		_size = _friendOfInfo.recommendinfo_size();
		GameDataManager::getSingletonPtr()->m_RecommendDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.recommendinfo(_i));
			GameDataManager::getSingletonPtr()->m_RecommendDataList.push_back(_info);
		}

		_size = _friendOfInfo.requestinfo_size();
		GameDataManager::getSingletonPtr()->m_RequestDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.requestinfo(_i));
			GameDataManager::getSingletonPtr()->m_RequestDataList.push_back(_info);
		}

		//facebook 리스트 정보
		GameDataManager::getSingletonPtr()->mRewardIds.clear();
		_size = _friendOfInfo.facefriendinviterewardlist_size();
		for (int _i = 0; _i < _size; _i++)
		{
			GameDataManager::getSingletonPtr()->mRewardIds.push_back(_friendOfInfo.facefriendinviterewardlist(_i));
		}

		GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_UPDATE_FRIEND_LIST_RES);
	}

}

void WebService::_sendFriendRequestListReq()
{
	W_FriendRequestListReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendRequestListRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendRequestListRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FriendRequestListRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveRequestDataList();

	int _size = res.requestinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_FriendInfo* _friendInfo = new W_FriendInfo(res.requestinfo(_i));
		GameDataManager::getSingletonPtr()->m_RequestDataList.push_back(_friendInfo);
	}

	_sendFriendReCommendReq();
}

void WebService::_sendFriendRequestReq(vector<int64>& _uidList)
{
	W_FriendRequestReq req;

	int _size = _uidList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		req.add_uid(_uidList[_i]);
	}
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendRequestRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendRequestRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FriendRequestRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	//GameDataManager::getSingletonPtr()->RemoveRecommendDataList();

	
	int _size = res.recommendinfo_size();
	bool isExistRequest = false;
	for (int _i = 0; _i < _size; _i++)
	{
		isExistRequest = false;
		for (W_FriendInfo* _dstInfo : GameDataManager::getSingletonPtr()->m_RecommendDataList)
		{
			if (_dstInfo->uid() == res.recommendinfo(_i).uid())
			{
				_dstInfo->CopyFrom(res.recommendinfo(_i));
				isExistRequest = true;
				break;
			}
		}
		if (!isExistRequest) {
			W_FriendInfo* _pInfo = new W_FriendInfo(res.recommendinfo(_i));
			GameDataManager::getSingletonPtr()->m_RecommendDataList.push_back(_pInfo);
		}
			
	}
	PanelHelper::pushAnnounceNotiPanel(GameStringDepot::getSingleton().getString("SEND_FRIEND_REQUEST"));

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_RECOMMEND_FRIEND_DATA_RES);
}

void WebService::_sendReplayListReq(int64 _uid)
{
	W_ReplayListReq req;
	req.set_uid(_uid);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvReplayListRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvReplayListRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_ReplayListRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveReplayDataList();

	int _size = res.replaysaveinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_ReplaySaveInfo* _pInfo = new W_ReplaySaveInfo(res.replaysaveinfo(_i));
		GameDataManager::getSingletonPtr()->m_ReplaySaveList.push_back(_pInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_REPLAY_INFO_RES);
}

void WebService::_sendLetterAllGetReq(vector<int64>& _seqList)
{
	W_LetterAllUpdateReq req;
	int _size = _seqList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		req.add_seq(_seqList[_i]);
	}
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvLetterAllGetRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvLetterAllGetRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_LetterAllUpdateRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	//띄우기 위해 먼저 실행
	if (res.has_rewardinfo())
	{		//보상창..
		PanelHelper::pushReceiveAllPanel(res.rewardinfo());
		//편지를 받을때 처리
		NotiDataManager::getSingleton().setReceiveLetter(res.rewardinfo());
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());
	}
	
	GameDataManager::getSingletonPtr()->RemoveLetterInfoList();
	int _size = res.letterinfo_size();
	GameDataManager::getSingletonPtr()->m_pLetterInfoList.reserve(_size);
	for (int _i = 0; _i < _size; _i++)
	{
		W_LetterInfo* _info = new W_LetterInfo(res.letterinfo(_size - _i -1));
		GameDataManager::getSingletonPtr()->m_pLetterInfoList.push_back(_info);
	}

	int characterSize = res.characterinfo_size();
	GameDataManager::getSingletonPtr()->RemoveCharacterInfoList();
	GameDataManager::getSingletonPtr()->m_pCharacterInfoList.reserve(characterSize);
	for (int _i = 0; _i < characterSize; _i++)
	{
		W_CharacterInfo* _pInfo = new W_CharacterInfo(res.characterinfo(_i));
		GameDataManager::getSingletonPtr()->m_pCharacterInfoList.push_back(_pInfo);
	}

	GameDataManager::getSingleton().getUserInfo()->clear_skininfo();
	for (int i = 0; i < res.skininfo_size(); i++)
	{
		W_SkinInfo* skinInfo = GameDataManager::getSingleton().getUserInfo()->add_skininfo();
		skinInfo->CopyFrom(res.skininfo(i));
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_LETTER_LIST_RES);
}

void WebService::ShowLetterGetPopup(W_RewardInfo& _pInfo)
{
	return;
}

void WebService::_sendCharacterBuyReq(int32 id)
{
	mCharacterBuyId = id;
	W_CharacterBuyReq req;
	req.set_buyid(mCharacterBuyId);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvCharacterBuyRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvCharacterBuyRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_CharacterBuyRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
	{
		int32 _curRuby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
		int32 _nextRuby = res.playerinfo().cash();
		PanelHelper::pushCharacterBuySucessPanel(mCharacterBuyId, _nextRuby - _curRuby);
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
	}
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_BUY_CHARACTER_RES);
}

void WebService::onLayerMessage(const string& msg)
{
	if (strncmp(msg.c_str(), "Chracter_Shop_Res_", 18) == 0)
	{
		int _index = nxExtractInt(msg, "Chracter_Shop_Res_");
		
		if (GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(_index).has_cash())
		{
			int32 _price = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(_index).cash();
			int32 _value = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash - _price;
			if (_value < 0)
			{
				_value = _price - GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
				GotoRubyShopPopup(_value);
			}
			else
			{
				if (GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(_index).has_id())
				{
					int32 _buyId = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(_index).id();
					_sendCharacterBuyReq(_buyId);
				}
			}
		}
	}
	else if (msg.find("Card_Shop_Res_") != string::npos) {
	
		int _index = nxExtractInt(msg, "Card_Shop_Res_");
		int32 _price = GameDataManager::getSingletonPtr()->GetGameDataPtr()->skinshopdata(_index).cash();
		int32 _value = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash - _price;
		if (_value < 0)
		{
			_value = _price - GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
			GotoRubyShopPopup(_value);
		}
		else
		{
			if (GameDataManager::getSingletonPtr()->GetGameDataPtr()->skinshopdata(_index).has_id())
			{
				int32 _buyId = GameDataManager::getSingletonPtr()->GetGameDataPtr()->skinshopdata(_index).id();
				_sendSkinBuyReq(_buyId);
			}
		}		
	}
	else if (strncmp(msg.c_str(), "MonthlyClass_Shop_Res_", 22) == 0)
	{
		int _index = nxExtractInt(msg, "MonthlyClass_Shop_Res_");
		if (GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(_index).has_cash())
		{
			int32 _price = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(_index).cash();
			int32 _value = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash - _price;
			if (_value < 0)
			{
				_value = _price - GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
				GotoRubyShopPopup(_value);
			}
			else
			{
				if (GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(_index).has_id())
				{
					int32 _buyId = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(_index).id();
					_sendMonthlyClassBuyReq(_buyId);
				}
			}
		}
	}
	else if (strncmp(msg.c_str(), "GOTO_RUBY_SHOP", 14) == 0)
	{
		if (LayerManager::getSingleton().hasLayerType<LobbyShopPanel>()) {
			Layer* layer = LayerManager::getSingleton().getLayerType<LobbyShopPanel>();
			LayerManager::getSingleton().popLayer(layer);
		}
		PanelHelper::pushRubyShopPanel();
	}
	else if (strncmp(msg.c_str(), "MSG_FREE_REFILL", 15) == 0)
	{
		_sendFreeRefillReq();
	}
	else if (strncmp(msg.c_str(), "Update_DeathmatchData", 21) == 0)
	{
		SurvivalMatchUpdateReq(GameDataManager::getSingletonPtr()->m_TournamentId);
	}
	else if (strncmp(msg.c_str(), "GO_GAME_TOURNAMENT", 18) == 0)
	{
		W_TourGameInfo _gameinfo = GameDataManager::getSingletonPtr()->m_TourOfInfo->gameinfo();
		WebService::getSingletonPtr()->TournamentGameReq(_gameinfo.seq());
	}
	else if (strncmp(msg.c_str(), "GO_GAME_SURVIVAL", 16) == 0)
	{
		W_DeathMatchGameInfo _gameinfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->gameinfo();
		GameDataManager::getSingletonPtr()->SurvivalButtonPressed = true;
		WebService::getSingletonPtr()->SurvivalGameReq(_gameinfo.seq());
	}
	else if (strncmp(msg.c_str(), "GO_TO_RUBYSHOP_FROM_TOURNAMENT_SELECT", 37) == 0)
	{
		NXASSERT(false, "GO_TO_RUBYSHOP_FROM_TOURNAMENT_SELECT");
	}
	else if (strncmp(msg.c_str(), "GO_TO_CHARACTER_SHOP_FROM_TOURNAMENT_SELECT", 43) == 0)
	{
		NXASSERT(false, "GO_TO_CHARACTER_SHOP_FROM_TOURNAMENT_SELECT");
	}
	else if (strncmp(msg.c_str(), "OPEN_URL", 8) == 0)
	{
		openURL(m_UpdateUrl);
	}
	else if (strncmp(msg.c_str(), "MSG_LOGOUT", 10) == 0)
	{
		eLoginType beforeLoginType = GameDataManager::getSingletonPtr()->m_LoginType;
		CCLog("MSG_LOGOUT beforeLoginType = %d", beforeLoginType);
		GameDataManager::getSingletonPtr()->SetLoginType(GUEST);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyLoginType.c_str(), 0);		
		CCUserDefault::sharedUserDefault()->flush();

		CSJson::Value params;
		params["MSG_LOGOUT"] = true;
		SceneUtil::changeScene(SceneUtil::SceneTitle , params);
				
	}
	else if (msg == "FACEBOOK_LOGIN_GO_TITLE") {
		//title 이동
		GameDataManager::getSingletonPtr()->SetLoginType(FACEBOOK);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyLoginType.c_str(), FACEBOOK);
		CCUserDefault::sharedUserDefault()->flush();
		CSJson::Value params;
		params["FACEBOOK_LOGIN"] = true;
		SceneUtil::changeScene(SceneUtil::SceneTitle, params);
	}
	else if (msg.find("sendPlayerInfo") != string::npos) {
		string tmp = msg.substr(msg.find("/") + 1, msg.size());

		string nickname = tmp.substr(0, tmp.find("/"));// msg = sendPlayerInfo/닉네임/1
		int32 characterIdx = stoi(tmp.substr(tmp.find("/") + 1 , tmp.size()));
		WebService::getSingletonPtr()->_sendPlayerInfoReq(nickname, characterIdx);
	}
	else if (msg.find("sendPlayerName") != string::npos) {
		string nickname = "";
		nickname = msg.substr(msg.find("/") + 1, msg.size());

		WebService::getSingletonPtr()->_sendPlayerNameReq(nickname);
	}

}

void WebService::GotoRubyShopPopup(int32 _value)
{
	string _title = GameStringDepot::getSingleton().getString("TXT_NEED_RUBY");
	string msg = NxGetFormatString(GameStringDepot::getSingleton().getString("TXT_GOTO_SHOP") , _value);
	SimplePopupPanel* _panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msg, _title);
	if (_panel)
	{
		string _okMsg = "GOTO_RUBY_SHOP";
		_panel->SetOkEventMsg(_okMsg);
		_panel->setListener(WebService::getSingletonPtr());
		LayerManager::getSingleton().pushDynamicLayer(_panel, DYNAMIC_PUSH_LAYER);
	}
}

void WebService::_sendReplaySeasonReq()
{
	W_ReplaySeasonReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvReplaySeasonRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvReplaySeasonRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_ReplaySeasonRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveReplayDataList();

	int _size = res.replaysaveinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_ReplaySaveInfo* _pInfo = new W_ReplaySaveInfo(res.replaysaveinfo(_i));
		GameDataManager::getSingletonPtr()->m_ReplaySaveList.push_back(_pInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_REPLAY_INFO_RES);
}

void WebService::_sendReplayDeathMatchReq()
{
	W_ReplayDeathMatchReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvReplayDeathMatchRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvReplayDeathMatchRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	} 

	W_ReplayDeathMatchRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveReplayDataList();

	int _size = res.replaysaveinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_ReplaySaveInfo* _pInfo = new W_ReplaySaveInfo(res.replaysaveinfo(_i));
		GameDataManager::getSingletonPtr()->m_ReplaySaveList.push_back(_pInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_REPLAY_INFO_RES);
}

void WebService::_sendLetterListReq()
{
	W_LetterListReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvLetterListRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvLetterListRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		GameDataManager::getSingletonPtr()->FreeUiProcess();
		return;
	}

	W_LetterListRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveLetterInfoList();

	int _infoSize = res.letterinfo_size();
	GameDataManager::getSingletonPtr()->m_pLetterInfoList.reserve(_infoSize);
	for (int _i = 0; _i < _infoSize; _i++)
	{
		W_LetterInfo* _info = new W_LetterInfo(res.letterinfo(_infoSize - _i -1));

		GameDataManager::getSingletonPtr()->m_pLetterInfoList.push_back(_info);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_SHOW_LETTER_LIST_RES);
}

void WebService::_sendReplayStartReq(eReplayType _type, int64 _seq)
{
	m_ReplayType = _type;
	ReplayGameManager::getSingletonPtr()->SetReplaySeq(_seq);
	W_ReplayStartReq req;
	req.set_type(_type);
	req.set_seq(_seq);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvReplayStartRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvReplayStartRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_ReplayStartRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_success())
	{
		if (res.success() == false)
		{
			if (res.has_errorcode())
			{
				//ParsingErrorCode(res.errorcode());
			}
			if (res.has_errorstring())
			{
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
			}

			return;
		}
	}

	if (res.has_gamedata())
	{
		ReplayGameManager::getSingletonPtr()->initialize(res.gamedata());
		ReplayGameManager::getSingletonPtr()->SetType(m_ReplayType);
		ReplayGameManager::getSingletonPtr()->SetIsPublish(true);
		GameDataManager::getSingleton().setGameKind(res.gamedata().gamekind());

		int _size = res.commentinfo_size();
		for (int _i = 0; _i < _size; _i++)
		{
			int64 _time = res.commentinfo(_i).time();
			int32 _id = 0;
			string _nick = res.commentinfo(_i).name();
			string _text = res.commentinfo(_i).comment();

			ReplayGameManager::getSingletonPtr()->AddUserCommentData(_time, _id, _nick, _text);
		}

		ReplayGameManager::getSingletonPtr()->StartReplay();
	}
}

void WebService::_sendRankInfoReq(W_RankInfoReq_eRankType _type)
{
	W_RankInfoReq req;
	req.set_type(_type);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvRankInfoRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvRankInfoRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_RankInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_myinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveMyRankData();
		GameDataManager::getSingletonPtr()->m_pMyRankInfo = new W_RankInfo(res.myinfo());
	}

	if (res.has_totalcnt())
	{
		GameDataManager::getSingletonPtr()->m_nTotalRankerCount = res.totalcnt();
	}

	GameDataManager::getSingletonPtr()->RemoveRankDataList();
	int _size = res.rankinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_RankInfo* _rankInfo = new W_RankInfo(res.rankinfo(_size-_i-1));
		GameDataManager::getSingletonPtr()->m_RankInfoList.push_back(_rankInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_RANK_INFO_RES);
}

void WebService::_sendReplayModifyReq(int64 seq, string _name)
{
	W_ReplayModifyReq req;
	req.set_seq(seq);
	req.set_title(_name);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvReplayModifyRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvReplayModifyRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_ReplayModifyRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}

		//reroad
		_sendReplayListReq(GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->GetUID());
		return;
	}

	if (res.has_replaysaveinfo())
	{
		int _size = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size();

		for (int _i = 0; _i < _size; _i++)
		{
			W_ReplaySaveInfo* _info = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_i];
			if (res.replaysaveinfo().seq() == _info->seq())
			{
				_info->set_title(res.replaysaveinfo().title());
				return;
			}
		}
	}
}

void WebService::_sendReplayDeleteReq(int64 seq)
{
	W_ReplayDeleteReq req;
	req.set_seq(seq);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvReplayDeleteRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvReplayDeleteRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_ReplayDeleteRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	int _size = res.replaysaveinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_ReplaySaveInfo* _pInfo = new W_ReplaySaveInfo(res.replaysaveinfo(_i));
		GameDataManager::getSingletonPtr()->m_ReplaySaveList.push_back(_pInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_REPLAY_INFO_RES);
}

void WebService::SendReplayListBoxReq(int64 _uid)
{
	W_ReplayListReq req;
	req.set_uid(_uid);
	HttpMessage msg(req, HttpResponseHandler(WebService::RecvReplayListBoxRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::RecvReplayListBoxRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_ReplayListRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveReplayDataList();

	int _size = res.replaysaveinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_ReplaySaveInfo* _pInfo = new W_ReplaySaveInfo(res.replaysaveinfo(_i));
		GameDataManager::getSingletonPtr()->m_ReplaySaveList.push_back(_pInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_POPUP_REPLAYBOX_LIST_RES);
}

void WebService::_sendPlayerInfoReq(string _name, int32 _characterID, eGenderType _genderType)
{
	W_PlayerInfoReq req;
	req.set_name(_name);
	req.set_characterid(_characterID);
	req.set_gendertype(_genderType);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvPlayerInfoRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvPlayerInfoRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_PlayerInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		new AccountPopupPanel(AccountPopupPanel::AccountPopupType::NICKNAME_TYPE);
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{

			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}

		return;
	}
	LayerManager::getSingleton().popLayer();
	if (res.has_playerinfo()) {
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
		// tutorial 을 끝냈다.
		NotiDataManager::getSingleton().setTutorialEnd();
	}


	int _size = res.characterinfo_size();
	GameDataManager::getSingletonPtr()->RemoveCharacterInfoList();
	GameDataManager::getSingletonPtr()->m_pCharacterInfoList.reserve(_size); 
	for (int _i = 0; _i < _size; _i++)
	{
		W_CharacterInfo* _pInfo = new W_CharacterInfo(res.characterinfo(_i));
		GameDataManager::getSingletonPtr()->m_pCharacterInfoList.push_back(_pInfo);
	}

	//_sendChannelReq();
	//if (LayerManager::getSingletonPtr()->hasLayer("MainUi"))
	//{
	//	SynopsisUiPanel* _pUiPanel = dynamic_cast<SynopsisUiPanel*>(LayerManager::getSingletonPtr()->getLayer("MainUi"));
	//	_pUiPanel->ShowDialog();
	//}

	if (LayerManager::getSingletonPtr()->hasLayer("Main") &&
		LayerManager::getSingletonPtr()->hasLayer("Information") &&
		LayerManager::getSingletonPtr()->hasLayer("Dialog") &&
		LayerManager::getSingletonPtr()->getLayer("MainUi"))
	{
		SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
		SynopsisCharacterInfoPanel* _pInfoPanel = dynamic_cast<SynopsisCharacterInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("Information"));
		SynopsisDialogPanel* _pDialogPanel = dynamic_cast<SynopsisDialogPanel*>(LayerManager::getSingletonPtr()->getLayer("Dialog"));
		SynopsisUiPanel* _pUiPanel = dynamic_cast<SynopsisUiPanel*>(LayerManager::getSingletonPtr()->getLayer("MainUi"));

		_pUiPanel->ShowTitle(false);
		_pUiPanel->ShowPlayerSelectPanel(false);
		_pUiPanel->setLightUse(false);
		_pMainPanel->ShowDealer(true);
		_pMainPanel->ShowCharacter(false);
		_pMainPanel->setBackGroundEnd();

		_pInfoPanel->ShowInfo(false);
		_pDialogPanel->setTouchable(true);
		_pDialogPanel->ShowDialog(true);
		_pDialogPanel->ShowText(7);
		_pDialogPanel->m_TextIdx = 8;
	}
}

void WebService::_sendCharacterSelectReq(int32 _id)
{
	W_CharacterSelectReq req;
	req.set_id(_id);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvCharacterSelectRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvCharacterSelectRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_CharacterSelectRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{

			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());


	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_SELECT_CHARACTER_RES);

	//SelectCharacterPanel * _pPanel = dynamic_cast<SelectCharacterPanel*>(LayerManager::getSingleton().getCurrentLayer());
	//_pPanel->ChangeCharacterCellUse();
}

void WebService::_sendReplayCommentReq(eReplayType _type, int64 _seq, int32 _time, string _comment)
{
	W_ReplayCommentReq req;
	req.set_type(_type);
	req.set_seq(_seq);
	req.set_time(_time);
	req.set_comment(_comment);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvReplayCommentRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvReplayCommentRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_ReplayCommentRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{

			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_commentinfo())
	{
		if (res.commentinfo().has_uid() && res.commentinfo().has_time() && res.commentinfo().has_name() && res.commentinfo().has_comment())
		{
			int64 _uid = res.commentinfo().uid();
			int32 _time = res.commentinfo().time();
			string _name = res.commentinfo().name();
			string _comment = res.commentinfo().comment();

			//add replay comment
			int _index = ReplayGameManager::getSingletonPtr()->GetNowCommentIndex();
			ReplayGameManager::getSingletonPtr()->InsertUserCommentData(_time, _uid, _name, _comment, _index);

			ReplayGameManager::getSingletonPtr()->MakeChatRistScrollPanel();
		}
	}
}

void WebService::_sendReplayLikeReq(eReplayType _type, int64 _seq)
{
	W_ReplayLikeReq req;
	req.set_type(_type);
	req.set_seq(_seq);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvReplayLikeRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvReplayLikeRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_ReplayLikeRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		ReplayGameManager::getSingletonPtr()->m_pRecommendButton->setEnable(false);
		ReplayGameManager::getSingletonPtr()->m_pRecommendButton->setSkelAnimation("recommend_off", false);
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{

			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_replaysaveinfo())
	{
		W_ReplaySaveInfo _info = res.replaysaveinfo();
		GameDataManager::getSingletonPtr()->m_pRecordInfo;
		//Update Replay Scene
		ReplayGameManager::getSingletonPtr()->m_pRecommendButton->setEnable(false);
		ReplayGameManager::getSingletonPtr()->m_pRecommendButton->setSkelAnimation("recommend_off", false);

	}

}


void WebService::ParsingErrorCode(string _errorCode)
{
	W_GameData* _gameData = GameDataManager::getSingletonPtr()->GetGameDataPtr();
	int _size = _gameData->stringdata_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_StringData _ErrorStringData = _gameData->stringdata(_i);
		if (_ErrorStringData.has_key())
		{
			if (_ErrorStringData.key() == _errorCode)
			{
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _ErrorStringData.kor()), DYNAMIC_PUSH_LAYER);
				return;
			}
		}
	}
}

void WebService::_sendEventListReq()
{
	W_EventListReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvEventListRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvEventListRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_EventListRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	int _size = res.eventinfo_size();

	GameDataManager::getSingletonPtr()->RemoveEventList();

	for (int _i = 0; _i < _size; _i++)
	{
		W_EventInfo* _pInfo = new W_EventInfo(res.eventinfo(_i));
		GameDataManager::getSingletonPtr()->m_EventList.push_back(_pInfo);
	}	
	//GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_EVENT_LIST_RES);
}

void WebService::_sendEventListUpdateReq(int32 _id)
{
	W_EventUpdateReq req;
	req.set_id(_id);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvEventListUpdateRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvEventListUpdateRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_EventUpdateRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	//character 추가
	int characterSize = res.characterinfo_size();
	GameDataManager::getSingletonPtr()->m_pCharacterInfoList.reserve(characterSize);
	for (int _i = 0; _i < characterSize; _i++)
	{
		W_CharacterInfo* _pInfo = new W_CharacterInfo(res.characterinfo(_i));
		GameDataManager::getSingletonPtr()->m_pCharacterInfoList.push_back(_pInfo);
	}

	//tourofinfo 추가
	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());
	}

	GameDataManager::getSingletonPtr()->RemoveEventList();

	int _size = res.eventinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_EventInfo* _pInfo = new W_EventInfo(res.eventinfo(_i));
		GameDataManager::getSingletonPtr()->m_EventList.push_back(_pInfo);
	}

	if (res.has_rewardinfo()) {
		PanelHelper::pushEventRewardPanel(res.rewardinfo());
		//편지를 받을때 처리
		NotiDataManager::getSingleton().setReceiveLetter(res.rewardinfo());
	}	
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_EVENT_UPDATE_RES);
}

void WebService::_sendFriendFindReq(string _name)
{
	W_FriendFindReq req;
	req.set_name(_name);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFriendFindRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFriendFindRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_FriendFindRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveRecommendDataList();
	int _size = res.findinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_FriendInfo* _pInfo = new W_FriendInfo(res.findinfo(_i));
		GameDataManager::getSingletonPtr()->m_RecommendDataList.push_back(_pInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_FRIEND_SEARCH_RES);
}

void WebService::_sendFreeRefillReq()
{
	W_FreeRefillReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFreeRefillRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFreeRefillRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_FreeRefillRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_rewardinfo())
	{
		//W_RewardInfo _rewardInfo = res.rewardinfo();
		//ShowLetterGetPopup(_rewardInfo);
		int _size = res.rewardinfo().rewardset_size();
		for(int _i=0; _i<_size; _i++)
		{
			int64 _amount = res.rewardinfo().rewardset(_i).amount();
			if (res.rewardinfo().rewardset(_i).type() == GAMEMONEY)
			{
				string _Gold = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_amount), 1);
				string _msg = _Gold + GameStringDepot::getSingletonPtr()->getString("TXT_FREEREFILL_AMOUNT");
				
				SimplePopupPanel* _pNotiPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _msg); 
				LayerManager::getSingleton().pushDynamicLayer(_pNotiPopup, DYNAMIC_PUSH_LAYER);
			}
		}
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_FreeRefillRes);
}

void WebService::SendPing()
{
	W_PingReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::RecvPing), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::RecvPing(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
}


void WebService::_sendAttendDailyRewardReq()
{
	//W_AttendDailyRewardReq req;
	//HttpMessage msg(req, HttpResponseHandler(WebService::RecvPing), this);
	//HttpManager::getSingleton().send(msg);
}

void WebService::_recvAttendDailyRewardRes(HttpMessage* msg)
{

}

void WebService::SendRefreshReq()
{
	W_RefreshReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::SendRefreshRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SendRefreshRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_RefreshRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	//W_UserInfo _info = res.userinfo();
	if (res.has_userinfo())
	{
		GameDataManager::getSingleton().setUserInfo(res.userinfo());
		GameDataManager::getSingletonPtr()->RemoveUserDataInfo();

		GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->SetData(&(res.userinfo().playerinfo()));
		GameDataManager::getSingletonPtr()->m_pRecordInfo = new W_RecordInfo(res.userinfo().recordinfo());
		int _size = res.userinfo().characterinfo_size();
		GameDataManager::getSingletonPtr()->m_pCharacterInfoList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_CharacterInfo* _pInfo = new W_CharacterInfo(res.userinfo().characterinfo(_i));
			GameDataManager::getSingletonPtr()->m_pCharacterInfoList.push_back(_pInfo);
		}

		_size = res.userinfo().letterinfo_size();
		GameDataManager::getSingletonPtr()->m_pLetterInfoList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_LetterInfo* _pInfo = new W_LetterInfo(res.userinfo().letterinfo(_size - _i - 1));
			GameDataManager::getSingletonPtr()->m_pLetterInfoList.push_back(_pInfo);
		}

		_size = res.userinfo().questinfo_size();
		int _sizeDaily = 0;
		int _sizeWeekly = 0;
		for (int _i = 0; _i < _size; _i++)
		{
			if (W_QuestData_eQuestType::W_QuestData_eQuestType_Daily == res.userinfo().questinfo(_i).questtype())
				_sizeDaily++;
			else
				_sizeWeekly++;
		}
		GameDataManager::getSingletonPtr()->m_pQuestDailyList.reserve(_sizeDaily);
		GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.reserve(_sizeWeekly);
		for (int _i = 0; _i < _size; _i++)
		{

			W_QuestInfo* _pInfo = new W_QuestInfo(res.userinfo().questinfo(_size - _i - 1));
			if (W_QuestData_eQuestType::W_QuestData_eQuestType_Daily == res.userinfo().questinfo(_i).questtype())
				GameDataManager::getSingletonPtr()->m_pQuestInfoList.push_back(_pInfo);
			else
				GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.push_back(_pInfo);

		}

		/*_size = res.userinfo().questinfo_size();
		GameDataManager::getSingletonPtr()->m_pQuestInfoList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_QuestInfo* _pInfo = new W_QuestInfo(res.userinfo().questinfo(_size - _i - 1));
			GameDataManager::getSingletonPtr()->m_pQuestInfoList.push_back(_pInfo);
		}*/

		_size = res.userinfo().eventinfo_size();
		GameDataManager::getSingletonPtr()->m_EventList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_EventInfo* _pInfo = new W_EventInfo(res.userinfo().eventinfo(_size - _i - 1));
			GameDataManager::getSingletonPtr()->m_EventList.push_back(_pInfo);
		}

		W_FriendOfInfo _friendOfInfo = res.userinfo().friendofinfo();
		
		_size = _friendOfInfo.facefriendinfo_size();
		GameDataManager::getSingletonPtr()->m_SnsDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.facefriendinfo(_i));
			GameDataManager::getSingletonPtr()->m_SnsDataList.push_back(_info);
		}

		_size = _friendOfInfo.friendinfo_size();
		GameDataManager::getSingletonPtr()->m_FriendDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.friendinfo(_i));
			GameDataManager::getSingletonPtr()->m_FriendDataList.push_back(_info);
		}

		_size = _friendOfInfo.recommendinfo_size();
		GameDataManager::getSingletonPtr()->m_RecommendDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.recommendinfo(_i));
			GameDataManager::getSingletonPtr()->m_RecommendDataList.push_back(_info);
		}

		_size = _friendOfInfo.requestinfo_size();
		GameDataManager::getSingletonPtr()->m_RequestDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.requestinfo(_i));
			GameDataManager::getSingletonPtr()->m_RequestDataList.push_back(_info);
		}

		//facebook 리스트 정보
		GameDataManager::getSingletonPtr()->mRewardIds.clear();
		_size = _friendOfInfo.facefriendinviterewardlist_size();
		for (int _i = 0; _i < _size; _i++)
		{
			GameDataManager::getSingletonPtr()->mRewardIds.push_back(_friendOfInfo.facefriendinviterewardlist(_i));
		}

	}

	if (res.has_freerefill())
	{
		if (res.freerefill() == true)
		{
			PanelHelper::pushAllinPopupPanel();
		}
	}

	int _size = res.notidata_size();
	int _bankPopCount = 0;
	for (int _i = 0; _i < _size; _i++)
	{
		W_NotiData _data = res.notidata(_size - 1 - _i);
		if (SceneUtil::getCurrentSceneId() != SceneUtil::SceneLobby)
			return;

		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

		if (_pScene == nullptr)
			return;

		if (_pScene->m_LobbyUIPanel == nullptr)
			return;		
		PanelHelper::pushNotiPanel(_data);		
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_RefreshRes);
}

void WebService::TournamentInfoReq()
{
	W_TourInfoReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::TournamentInfoRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::TournamentInfoRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_TourInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());

		//if (GameDataManager::getSingletonPtr()->getGameKind() == -1)
		//	GameDataManager::getSingletonPtr()->m_SelectedGameKind = 0;

		if (res.tourofinfo().seasonid() == 0) {
			PanelHelper::pushSimpleConfirmPopupPanel(GameStringDepot::getSingleton().getString("TournamentInfoRes_NO"), GameStringDepot::getSingleton().getString("TournamentInfoRes_NO_TITLE"));
		}
		else if (res.tourofinfo().gamekind() == GAMEKIND_NO) {
			PanelHelper::pushSimpleConfirmPopupPanel(res.tourofinfo().message(), GameStringDepot::getSingleton().getString("TournamentInfoRes_NO_TITLE"));
		}
		else {
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			if (_pScene->m_LobbyUIPanel == nullptr)
				return;
			_pScene->m_LobbyUIPanel->ShowTournamentUi();
		}
		
	}
	else {
		PanelHelper::pushSimpleConfirmPopupPanel(GameStringDepot::getSingleton().getString("TournamentInfoRes_NO"), GameStringDepot::getSingleton().getString("TournamentInfoRes_NO_TITLE"));
	}
}

void WebService::TournamentEnterReq()
{
	W_TourEnterReq req;
	int32 _tourID = GameDataManager::getSingletonPtr()->m_TournamentId;
	int32 _tourStep = GameDataManager::getSingletonPtr()->m_TournamentStep;
	W_TourStepInfo_eTourStatus _status = (W_TourStepInfo_eTourStatus)GameDataManager::getSingletonPtr()->m_TournamentStatus;
	req.set_tourid(_tourID);
	req.set_tourstep(_tourStep);
	req.set_status(_status);

	HttpMessage msg(req, HttpResponseHandler(WebService::TournamentEnterRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::TournamentEnterRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_TourEnterRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
	}

	if (strcmp(WebService::getSingletonPtr()->getCurIp().c_str(), GameDataManager::getSingletonPtr()->m_TournamentIp.c_str()) == 0 &&
		WebService::getSingletonPtr()->getCurPort() == GameDataManager::getSingletonPtr()->m_TournamentPort)
	{
		TCPService::getSingletonPtr()->SendTournamentPlayerInfoReq();
	}
	else
	{
		WebService::getSingletonPtr()->setLobbyIp(GAMBLE_DEFAULT_URL == "http://192.168.0.161:8200/poker_server/"? 
			LocalIp : GameDataManager::getSingletonPtr()->m_TournamentIp);
		WebService::getSingletonPtr()->setLobbyPort(GameDataManager::getSingletonPtr()->m_TournamentPort);

		TCPService::getSingletonPtr()->Close();
		TCPService::getSingletonPtr()->Start();
		TCPService::getSingletonPtr()->Connect(m_LobbyIp, GameDataManager::getSingletonPtr()->m_TournamentPort, false);
	}
}

void WebService::TournamentRefreshReq()
{
	W_TourRefreshReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::TournamentRefreshRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::TournamentRefreshRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_TourRefreshRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	//TODO : SHOW NOTI WINDOW //DirectTournamentSelectReq
	

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());

		if (res.tourofinfo().seasonid() == 0 || res.tourofinfo().gamekind() == GAMEKIND_NO) {
			//PanelHelper::pushSimpleConfirmPopupPanel(GameStringDepot::getSingleton().getString("TournamentInfoRes_NO_DESC"), GameStringDepot::getSingleton().getString("TournamentInfoRes_NO_TITLE"));
		}
		else {
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			if (_pScene->m_LobbyUIPanel)
				_pScene->m_LobbyUIPanel->ShowTournamentUi();

			LobbyTourSelectPanel* pPanel = new LobbyTourSelectPanel();
			LayerManager::getSingleton().pushDynamicLayer(pPanel);
			pPanel->ShowSelectPanel();
		}	

		W_TourOfInfo* tourofInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo;

		if (tourofInfo->has_noticeinfo() && tourofInfo->noticeinfo().ByteSize() != 0) {
			W_TourNoticeInfo _noti = tourofInfo->noticeinfo();

			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

			if (_pScene->m_LobbyUIPanel == nullptr)
				return;

			//TODO : SHOW NOTI WINDOW 
			LobbyRewardPanel* pPanel = new LobbyRewardPanel(REWARD_TOURNAMENT);
			pPanel->init();
			pPanel->SetType(REWARD_TOURNAMENT);
			LayerManager::getSingletonPtr()->pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
			if (pPanel)
			{
				//TODO : Set RewardPanel

				int64 _gold = 0;
				int _fame = 0;

				int _size = _noti.rewardinfo().rewardset_size();
				for (int _i = 0; _i < _size; _i++)
				{
					W_RewardInfo_RewardSet _rewardset = _noti.rewardinfo().rewardset(_i);
					switch (_rewardset.type())
					{
					case CASH:
						break;
					case GAMEMONEY:
						_gold = _rewardset.amount();
						break;
					case CHIP:
						break;
					case REPUTE:
						_fame = _rewardset.amount();
						break;
					case CHARACTER:
						break;
					case TOUR_TICKET:
						break;
					}
				}

				pPanel->SetTitleText(_noti.title(), GameMode::MODE_NORMAL_TOURNAMENT);
				pPanel->SetMyRank(_noti.rank(), _noti.maxcnt());
				pPanel->SetRewardGold(_gold);
				pPanel->SetRewardFame(_fame);
				pPanel->SetDesc(_noti.desc());
			}			

			tourofInfo->mutable_noticeinfo()->Clear();
		}
				
		if (tourofInfo->has_weeklyrewardinfo() && tourofInfo->weeklyrewardinfo().ByteSize() != 0) {
			Panel* pPanel = PanelHelper::pushWeeklyResultPanel();
			tourofInfo->mutable_weeklyrewardinfo()->Clear();
		}

		//시즌 등급 업 정보		
		if (tourofInfo->has_ratingupinfo() && tourofInfo->ratingupinfo().ByteSize() != 0) {
			Panel* pPanel = PanelHelper::pushRatingUpPanel();
			tourofInfo->mutable_ratingupinfo()->Clear();
		}		
	}

	GameDataManager::getSingletonPtr()->FreeUiProcess();
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_TOURNAMENT_REFREASH_RES);
}




void WebService::TournamentIdReq(int32 _tourId)
{
	W_TourIDReq req;
	req.set_tourid(_tourId);
	HttpMessage msg(req, HttpResponseHandler(WebService::TournamentIdRes), this);
	HttpManager::getSingleton().send(msg);

}

void WebService::TournamentIdRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_TourIDRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());
		LobbyTourSelectPanel* pPanel = new LobbyTourSelectPanel();
		LayerManager::getSingleton().pushDynamicLayer(pPanel);
		pPanel->ShowSelectPanel(GameDataManager::getSingleton().getTicketStepIndex());		
		GameDataManager::getSingleton().setTicketStepIndex(-1);
	}
}


void WebService::TournamentReplayListReq(int64 _uid, int64 _gamekey)
{
	W_TourReplayListReq req;
	req.set_uid(_uid);
	req.set_gamekey(_gamekey);
	HttpMessage msg(req, HttpResponseHandler(WebService::TournamentReplayListRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::TournamentReplayListRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_TourReplayListRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveReplayDataList();

	int _size = res.replayinfo_size();

	if (_size == 0)
	{
		string _errorText = GameStringDepot::getSingletonPtr()->getString("TXT_USERINFO_EMPTY");
		LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _errorText), DYNAMIC_PUSH_LAYER);
		return;
	}

	for (int _i = 0; _i < _size; _i++)
	{
		W_ReplaySaveInfo* _pInfo = new W_ReplaySaveInfo(res.replayinfo(_i));
		GameDataManager::getSingletonPtr()->m_ReplaySaveList.push_back(_pInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_TOURNAMENT_REPLAY_RES);
}

void WebService::TournamentReplayReq(int64 _seq)
{
	ReplayGameManager::getSingletonPtr()->SetReplaySeq(_seq);

	W_TourReplayReq req;
	req.set_seq(_seq);
	HttpMessage msg(req, HttpResponseHandler(WebService::TournamentReplayRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::TournamentReplayRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_TourReplayRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_success())
	{
		if (res.success() == false)
		{
			if (res.has_errorcode())
			{
				//ParsingErrorCode(res.errorcode());
			}
			if (res.has_errorstring())
			{
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
			}

			return;
		}
	}

	if (res.has_gamedata())
	{
		ReplayGameManager::getSingletonPtr()->initialize(res.gamedata());
		//ReplayGameManager::getSingletonPtr()->SetType(m_ReplayType);
		GameDataManager::getSingleton().setGameKind(res.gamedata().gamekind());
		ReplayGameManager::getSingletonPtr()->SetIsPublish(res.ispublish());

		ReplayGameManager::getSingletonPtr()->StartReplay();
	}
}


void WebService::TournamentRewardReq(int32 _tourId)
{
	W_TourRewardReq req;
	req.set_tourid(_tourId);
	HttpMessage msg(req, HttpResponseHandler(WebService::TournamentRewardRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::TournamentRewardRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_TourRewardRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_success())
	{
		if (res.success() == false)
		{
			if (res.has_errorcode())
			{
				//ParsingErrorCode(res.errorcode());
			}
			if (res.has_errorstring())
			{
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
			}

			return;
		}
	}

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_rewardinfo()) {
		PanelHelper::pushTourRewardPanel(res.rewardinfo());
	}
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_TOURNAMENT_REWARD_RES);
}


void WebService::SurvivalInfoReq()
{
	W_DeathMatchInfoReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalInfoRes), this);
	HttpManager::getSingleton().send(msg);

	GameDataManager::getSingletonPtr()->ResetSurvivalLeftTime();
}

void WebService::SurvivalInfoRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_deathmatchofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());

		if (GameDataManager::getSingletonPtr()->SurvivalButtonPressed)
		{
			if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo_size() == 0)
			{
				//string _text = GameStringDepot::getSingletonPtr()->getString("TXT_NO_GAME_LIST");
				if (GameDataManager::getSingletonPtr()->SurvivalButtonPressed) {
					string _alert = GameStringDepot::getSingletonPtr()->getString("TXT_NOT_SURVIVAL_ALERT");
					string _text = GameStringDepot::getSingletonPtr()->getString("TXT_NOT_READY_SURVIVAL");

					SimplePopupPanel* _pPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _text, _alert);
					LayerManager::getSingleton().pushDynamicLayer(_pPopup, DYNAMIC_PUSH_LAYER);
					GameDataManager::getSingletonPtr()->SurvivalButtonPressed = false;
					return;
				}
			}
			else if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo(0).userstatus() == W_DeathMatchInfo_eUserStatus::W_DeathMatchInfo_eUserStatus_eNot)
			{
				string _alert = GameStringDepot::getSingletonPtr()->getString("TXT_NOT_SURVIVAL_ALERT");
				string _text = GameStringDepot::getSingletonPtr()->getString("TXT_NOT_READY_SURVIVAL");

				SimplePopupPanel* _pPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _text, _alert);
				LayerManager::getSingleton().pushDynamicLayer(_pPopup, DYNAMIC_PUSH_LAYER);
				GameDataManager::getSingletonPtr()->SurvivalButtonPressed = false;
				return;
			}
		}
		else if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo_size() == 0) {
			GameDataManager::getSingletonPtr()->SurvivalButtonPressed = false;
			return;
		}

		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		GameDataManager::getSingleton().setGameKind(GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo(0).gamekind());
		GameDataManager::getSingletonPtr()->m_bSurvivalTimeUpdate = true;
		GameDataManager::getSingletonPtr()->Survival_RegisterableTime = res.deathmatchofinfo().matchinfo(0).registerabletime();
		GameDataManager::getSingletonPtr()->Survival_RegisterExpireTime = res.deathmatchofinfo().matchinfo(0).registerexpiretime();
		GameDataManager::getSingletonPtr()->Survival_WaitableTime = res.deathmatchofinfo().matchinfo(0).waitabletime();
		GameDataManager::getSingletonPtr()->Survival_WaitExpireTime = res.deathmatchofinfo().matchinfo(0).waitexpiretime();
		GameDataManager::getSingletonPtr()->Survial_gameexpiretime = res.deathmatchofinfo().matchinfo(0).gameexpiretime();
		GameDataManager::getSingletonPtr()->Survival_GameableTime = res.deathmatchofinfo().matchinfo(0).gameabletime();
		GameDataManager::getSingletonPtr()->Survival_UserStatus = res.deathmatchofinfo().matchinfo(0).userstatus();
		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		

		if(GameDataManager::getSingletonPtr()->SurvivalButtonPressed)
			_pScene->m_LobbyUIPanel->ShowSurvivalUi();

		GameDataManager::getSingletonPtr()->SurvivalButtonPressed = false;

		if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->has_gameinfo())
		{
			GameDataManager::getSingletonPtr()->m_hasSurvivalGameInfo = true;
		}
	}
	
}

void WebService::SurvivalMatchRegistReq(int32 _matchId)
{
	W_DeathMatchRegisterReq req;
	req.set_matchid(_matchId);
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalMatchRegistRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SurvivalMatchRegistRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchRegisterRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_deathmatchofinfo())
	{
		if (res.deathmatchofinfo().matchinfo_size() == 0) {
			GameDataManager::getSingletonPtr()->m_IsSurvivalReservated = false;
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
			return;
		}
		else
			GameDataManager::getSingletonPtr()->m_IsSurvivalReservated = res.deathmatchofinfo().matchinfo(0).isregister();
		
		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());
		CCUserDefault::sharedUserDefault()->setBoolForKey("Survival_Pre_Alarm", true);
		CCUserDefault::sharedUserDefault()->setBoolForKey("Survival_Popup_Alarm", true);

		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		_pScene->m_LobbyUIPanel->UpdateSurvivalUi();
		if (_pScene->m_LobbyUIPanel)
		{
			_pScene->ApplyUserData();
		}
	}
}


void WebService::SurvivalMatchRegistCancelReq(int32 _matchId)
{
	W_DeathMatchRegisterCancelReq req;
	req.set_matchid(_matchId);
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalMatchRegistCancelRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SurvivalMatchRegistCancelRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchRegisterCancelRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());


	if (res.has_deathmatchofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());

		
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_DEATHMATCH_CANCEL_RES);
	
}

void WebService::SurvivalEnterReq(int32 _matchId)
{
	W_DeathMatchEnterReq req;   //서바이벌 입장 프로토콜
	req.set_matchid(_matchId);
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalEnterRes), this);
	HttpManager::getSingleton().send(msg);

	GameDataManager::getSingletonPtr()->ResetSurvivalLeftTime();
}

void WebService::SurvivalEnterRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchEnterRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_deathmatchofinfo()) //받아왔는데 데스매치 인포가 있어
	{
		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());
		GameDataManager::getSingletonPtr()->m_bSurvivalTimeUpdate = true;
	}

	if (strcmp(WebService::getSingletonPtr()->getCurIp().c_str(), GameDataManager::getSingletonPtr()->m_TournamentIp.c_str()) == 0 &&
		WebService::getSingletonPtr()->getCurPort() == GameDataManager::getSingletonPtr()->m_TournamentPort)
	{
		TCPService::getSingletonPtr()->SendTournamentPlayerInfoReq();
	}
	else
	{
		WebService::getSingletonPtr()->setLobbyIp(GAMBLE_DEFAULT_URL == "http://192.168.0.161:8200/poker_server/" ?
			LocalIp : GameDataManager::getSingletonPtr()->m_TournamentIp);
		WebService::getSingletonPtr()->setLobbyPort(GameDataManager::getSingletonPtr()->m_TournamentPort);

		TCPService::getSingletonPtr()->Close();
		TCPService::getSingletonPtr()->Start();
		TCPService::getSingletonPtr()->Connect(m_LobbyIp, GameDataManager::getSingletonPtr()->m_TournamentPort, false);
	}

}

void WebService::SurvivalRefreshReq(int32 _matchId)
{
	W_DeathMatchRefreshReq req;
	req.set_matchid(_matchId);
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalRefreshRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SurvivalRefreshRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchRefreshRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_deathmatchofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());

		
		if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo_size() == 0)
		{
			//string _text = GameStringDepot::getSingletonPtr()->getString("TXT_NO_GAME_LIST");
			string _alert = GameStringDepot::getSingletonPtr()->getString("TXT_NOT_SURVIVAL_ALERT");
			string _text = GameStringDepot::getSingletonPtr()->getString("TXT_NOT_READY_SURVIVAL");

			SimplePopupPanel* _pPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _text, _alert);
			LayerManager::getSingleton().pushDynamicLayer(_pPopup, ZODER_POPUP);
		}
		else
		{
			GameDataManager::getSingletonPtr()->m_bSurvivalTimeUpdate = true;

			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

			if (_pScene->m_LobbyUIPanel)
				_pScene->m_LobbyUIPanel->ShowSurvivalUi();

			LobbySurvivalWindowMain* _pSelectPanel = new LobbySurvivalWindowMain();
			LayerManager::getSingleton().pushDynamicLayer(_pSelectPanel);
			_pSelectPanel->ApplyData();
		}

		//GameDataManager::getSingletonPtr()->FadeinLobby(0.8f);
		
		if (res.deathmatchofinfo().has_noticeinfo())
		{
			W_DeathMatchNoticeInfo _noti = res.deathmatchofinfo().noticeinfo();

			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

			if (_pScene->m_LobbyUIPanel == nullptr)
				return;
			GameDataManager::getSingletonPtr()->SurvivalRewardinfo = _noti.rewardinfo();

			LobbyRewardPanel* pPanel = new LobbyRewardPanel(REWARD_SURVIVAL);
			pPanel->init();
			pPanel->SetType(REWARD_SURVIVAL);
			LayerManager::getSingletonPtr()->pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
			if (pPanel)
			{
				//TODO : Set RewardPanel

				int64 _gold = 0;
				int _fame = 0;

				int _size = _noti.rewardinfo().rewardset_size();
				for (int _i = 0; _i < _size; _i++)
				{
					W_RewardInfo_RewardSet _rewardset = _noti.rewardinfo().rewardset(_i);
					switch (_rewardset.type())
					{
					case CASH:
						break;
					case GAMEMONEY:
						_gold = _rewardset.amount();
						break;
					case CHIP:
						break;
					case REPUTE:
						_fame = _rewardset.amount();
						break;
					case CHARACTER:
						break;
					case TOUR_TICKET:
						break;
					}
				}

				pPanel->SetTitleText(_noti.title(), GameMode::MODE_SURVIVAL_TOURNAMENT);
				pPanel->SetMyRank(_noti.rank(), _noti.maxcnt());
				pPanel->SetRewardGold(_gold);
				pPanel->SetRewardFame(_fame);
				pPanel->SetDesc(_noti.desc());
			}			
		}
	}

	GameDataManager::getSingletonPtr()->FreeUiProcess();
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_DEATHMATCH_REFREASH_RES);
}


void WebService::SurvivalMatchIdReq(int32 _matchId)
{
	W_DeathMatchIDReq req;
	req.set_matchid(_matchId);
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalMatchIdRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SurvivalMatchIdRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchIDRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_deathmatchofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());
		PanelHelper::pushSurvivalWindowMainPanel();		
	}
}


void WebService::SurvivalMatchUpdateReq(int32 _matchId)
{
	W_DeathMatchIDReq req;
	req.set_matchid(_matchId);
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalMatchUpdateRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SurvivalMatchUpdateRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchIDRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_deathmatchofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());

		LobbySurvivalWindowMain* _pSelectPanel = new LobbySurvivalWindowMain();
		LayerManager::getSingleton().pushDynamicLayer(_pSelectPanel);
		_pSelectPanel->ApplyData();
	}
}


void WebService::SurvivalRankReq()
{
	W_DeathMatchRankReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalRankRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SurvivalRankRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchRankRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

}

void WebService::SurvivalReplayListReq(int _matchId)
{
	W_DeathMatchReplayListReq req;
	req.set_matchid(_matchId);
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalReplayListRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SurvivalReplayListRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchReplayListRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	GameDataManager::getSingletonPtr()->RemoveReplayDataList();

	int _size = res.replayinfo_size();

	if (_size == 0)
	{
		string _errorText = GameStringDepot::getSingletonPtr()->getString("TXT_USERINFO_EMPTY");
		LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _errorText), DYNAMIC_PUSH_LAYER);
		return;
	}

	for (int _i = 0; _i < _size; _i++)
	{
		W_ReplaySaveInfo* _pInfo = new W_ReplaySaveInfo(res.replayinfo(_i));
		GameDataManager::getSingletonPtr()->m_ReplaySaveList.push_back(_pInfo);
	}

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_DEATHMATCH_REPLAY_RES);
}

void WebService::SurvivalReplayReq(int64 _seq)
{
	//m_ReplayType = _type;
	ReplayGameManager::getSingletonPtr()->SetReplaySeq(_seq);
	
	W_DeathMatchReplayReq req;
	//req.set_type(_type);
	req.set_seq(_seq);
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalReplayRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SurvivalReplayRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchReplayRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_success())
	{
		if (res.success() == false)
		{
			if (res.has_errorcode())
			{
				//ParsingErrorCode(res.errorcode());
			}
			if (res.has_errorstring())
			{
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
			}

			return;
		}
	}

	if (res.has_gamedata())
	{
		ReplayGameManager::getSingletonPtr()->initialize(res.gamedata());
		//ReplayGameManager::getSingletonPtr()->SetType(m_ReplayType);
		GameDataManager::getSingleton().setGameKind(res.gamedata().gamekind());
	
		ReplayGameManager::getSingletonPtr()->SetIsPublish(res.ispublish());
		ReplayGameManager::getSingletonPtr()->StartReplay();
	}
}

void WebService::TournamentGameReq(int64 _seq)
{
	W_TourGameReq req;
	req.set_seq(_seq);
	HttpMessage msg(req, HttpResponseHandler(WebService::TournamentGameRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::TournamentGameRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_TourGameRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_success())
	{
		if (res.success() == false)
		{
			if (res.has_errorcode())
			{
				//ParsingErrorCode(res.errorcode());
			}
			if (res.has_errorstring())
			{
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
			}

			return;
		}
	}

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());

		W_TourGameInfo _gameinfo = GameDataManager::getSingletonPtr()->m_TourOfInfo->gameinfo();

		GameDataManager::getSingletonPtr()->m_TournamentId = _gameinfo.tourid();

		_gameinfo.tourstep();
		_gameinfo.channelid();
		_gameinfo.roomnumber();

		W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;

		int _tourSize = _pInfoData->tourinfo_size();
		int _index = 0;
		for (int _i = 0; _i < _tourSize; _i++)
		{
			W_TourInfo _tourInfo = _pInfoData->tourinfo(_i);
			if (_tourInfo.tourid() == _gameinfo.tourid())
			{
				GameDataManager::getSingletonPtr()->SetIsDirectTournamentLink();
				//GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_TOURNAMENT);
				//GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_TOURNAMENT_SELECT);

				int _stepIndex = _gameinfo.tourstep() - 1;
				W_TourStepInfo _stepInfo = _tourInfo.stepinfo(_stepIndex);
				W_ChannelInfo _ChannelInfo = _stepInfo.channelinfo();

				GameDataManager::getSingletonPtr()->m_seasonId = _pInfoData->seasonid();

				GameDataManager::getSingletonPtr()->m_TournamentId = _tourInfo.tourid();
				GameDataManager::getSingletonPtr()->m_TournamentStep = _stepInfo.stepid();
				GameDataManager::getSingletonPtr()->m_TournamentStatus = _stepInfo.status();

				GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney1 = _ChannelInfo.bigpot_1();
				GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney2 = _ChannelInfo.bigpot_2();
				GameDataManager::getSingletonPtr()->m_RoomId = _ChannelInfo.id();
				GameDataManager::getSingletonPtr()->m_BettingRule = _ChannelInfo.bettingrule();
				GameDataManager::getSingletonPtr()->m_seedMoney = _ChannelInfo.seedmoney();
				GameDataManager::getSingletonPtr()->m_Grade = _ChannelInfo.grade();
				GameDataManager::getSingletonPtr()->m_EnterGameRoomBettingMaxMoney = _ChannelInfo.bigbettingmaxmoney();
				GameDataManager::getSingletonPtr()->m_GameMode = _ChannelInfo.gamemode();

				GameDataManager::getSingletonPtr()->m_TournamentIp = _ChannelInfo.ip();
				GameDataManager::getSingletonPtr()->m_TournamentPort = _ChannelInfo.port();

				WebService::getSingletonPtr()->TournamentEnterReq();
			}
		}
	}
}

void WebService::SurvivalGameReq(int64 _seq)
{
	W_DeathMatchGameReq req;
	req.set_seq(_seq);
	HttpMessage msg(req, HttpResponseHandler(WebService::SurvivalGameRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::SurvivalGameRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_DeathMatchGameRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_success())
	{
		if (res.success() == false)
		{
			if (res.has_errorcode())
			{
				//ParsingErrorCode(res.errorcode());
			}
			if (res.has_errorstring())
			{
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
			}

			return;
		}
	}

	if (res.has_deathmatchofinfo())
	{
		GameDataManager::getSingletonPtr()->SetIsDirectSurvivalLink();

		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());

		W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
		GameDataManager::getSingletonPtr()->m_TournamentId = _pInfo->gameinfo().matchid();

		int _matchCount = _pInfo->matchinfo_size();
		for (int _i = 0; _i < _matchCount; _i++)
		{
			W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(_i);

			if (_matchInfo.matchid() == GameDataManager::getSingletonPtr()->m_TournamentId)
			{
				W_ChannelInfo _ChannelInfo = _matchInfo.channelinfo();
				GameDataManager::getSingleton().setGameKind(_ChannelInfo.gamekind());
				GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney1 = _ChannelInfo.bigpot_1();
				GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney2 = _ChannelInfo.bigpot_2();
				GameDataManager::getSingletonPtr()->m_RoomId = _ChannelInfo.id();
				GameDataManager::getSingletonPtr()->m_BettingRule = _ChannelInfo.bettingrule();
				GameDataManager::getSingletonPtr()->m_seedMoney = _ChannelInfo.seedmoney();
				GameDataManager::getSingletonPtr()->m_Grade = _ChannelInfo.grade();
				GameDataManager::getSingletonPtr()->m_EnterGameRoomBettingMaxMoney = _ChannelInfo.bigbettingmaxmoney();
				GameDataManager::getSingletonPtr()->m_GameMode = _ChannelInfo.gamemode();

				GameDataManager::getSingletonPtr()->m_seasonId = _matchInfo.matchid();
				GameDataManager::getSingletonPtr()->m_TournamentIp = _ChannelInfo.ip();
				GameDataManager::getSingletonPtr()->m_TournamentPort = _ChannelInfo.port();

				WebService::getSingletonPtr()->SurvivalEnterReq(_matchInfo.matchid());
				return;
			}
		}
	}
}


void WebService::update(float _dt)
{
	if (CheckNotiSend())
		sendNoticeinfoReq();


	if (m_bMsgWait == false)
		return;

	m_fMsgWaitTime -= _dt;
	if (m_fMsgWaitTime <= 0.f)
	{
		m_bMsgWait = false;
		m_fMsgWaitTime = 0.f;

		HeroApp::getSingletonPtr()->stopWaiting();
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(ERROR_MASSGE_WAITING_OVER);
	}


	
}

void WebService::SetMsgWait(float _time)
{
	m_bMsgWait = true;
	m_fMsgWaitTime = _time;
}

void WebService::EndWait()
{
	m_bMsgWait = false;
	m_fMsgWaitTime = 0.f;
}

void WebService::_sendFacebookLoginReq(std::string _id, std::string _photoUrl)
{
	CCLog("_sendFacebookLoginReq");
	PanelHelper::pushLoadingPanel(GameStringDepot::getSingleton().getString("LOGIN_CHECK_REQ_DESC"));
	vector<string> ids;
	nxTokenize(GameDataManager::getSingletonPtr()->GetGAID(), "-", back_inserter(ids));
	W_LoginReq req;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef REFERENCE_MODE
	req.mutable_ilovegameid()->CopyFrom(LoginScene::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_ilovegamename()->CopyFrom(LoginScene::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.set_group(LoginReq_AccountGroup_TESTER);
#else
	req.mutable_devicekey()->CopyFrom(GameDataManager::getEncryptString(GameDataManager::getSingletonPtr()->GetGAID(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString(_id, LOGIN_REQ_KEY, mInitialVector));
	req.set_logintype(FACEBOOK);
	req.set_imageurl(_photoUrl);
#endif

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	req.mutable_ilovegameid()->CopyFrom(LoginScene::getEncryptString(SocialManager::getSingleton().getUserId(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_ilovegamename()->CopyFrom(LoginScene::getEncryptString(SocialManager::getSingleton().getUserName(), LOGIN_REQ_KEY, mInitialVector));
	req.set_group(LoginReq_AccountGroup_TESTER);
#else
	req.mutable_devicekey()->CopyFrom(GameDataManager::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));

	EncryptString string = GameDataManager::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector);
	req.set_logintype(FACEBOOK);
#endif
	req.set_market(getMarketType());

	HttpMessage msg(req, HttpResponseHandler(WebService::_recvGuestLoginRes), this);
	HttpManager::getSingleton().loadJSessionId();
	HttpManager::getSingleton().send(msg);
	
	if (LayerManager::getSingletonPtr()->hasLayer("Title"))
	{
		TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
		_panel->showLoginButton(false);
	}

}

void WebService::sendGoogleLoginReq(std::string _id, std::string _photoUrl)
{
	PanelHelper::pushLoadingPanel(GameStringDepot::getSingleton().getString("LOGIN_CHECK_REQ_DESC"));
	CCLog("GoogleLogin _id = %s", _id.c_str());
	vector<string> ids;
	nxTokenize(getUUID(), "-", back_inserter(ids));

	W_LoginReq req;
	req.mutable_devicekey()->CopyFrom(GameDataManager::getEncryptString(getUUID(), LOGIN_REQ_KEY, mInitialVector));
	req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString(_id, LOGIN_REQ_KEY, mInitialVector));
	req.set_logintype(GOOGLE);
	req.set_imageurl(_photoUrl);
	req.set_market(getMarketType());
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvGuestLoginRes), this);
	HttpManager::getSingleton().loadJSessionId();
	HttpManager::getSingleton().send(msg);

	if (LayerManager::getSingletonPtr()->hasLayer("Title"))
	{
		TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
		_panel->showLoginButton(false);
	}
}

void WebService::DirectTournamentSelectReq()
{
	W_TourInfoReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::DirectTournamentSelectRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::DirectTournamentSelectRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		//GameDataManager::getSingletonPtr()->FadeinLobby(0.f);
		GameDataManager::getSingletonPtr()->FreeUiProcess();
		return;
	}

	W_TourInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		_pScene->m_LobbyUIPanel->ShowTournamentUi();

		W_TourIDReq req;
		req.set_tourid(GameDataManager::getSingletonPtr()->m_TournamentId);
		HttpMessage msg(req, HttpResponseHandler(WebService::DirectTournamentSelectNextRes), this);
		HttpManager::getSingleton().send(msg);
	}
}

void WebService::DirectTournamentSelectNextRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		//GameDataManager::getSingletonPtr()->FadeinLobby(0.f);
		GameDataManager::getSingletonPtr()->FreeUiProcess();
		return;
	}

	W_TourIDRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_tourofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveTournamentOfInfo();
		GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		GameDataManager::getSingleton().setGameKind(res.tourofinfo().gamekind());
		LobbyTourSelectPanel* pPanel = new LobbyTourSelectPanel();
		LayerManager::getSingleton().pushDynamicLayer(pPanel);
		pPanel->ShowSelectPanel();
	}

	//GameDataManager::getSingletonPtr()->FadeinLobby(0.8f);
	GameDataManager::getSingletonPtr()->FreeUiProcess();
}

void WebService::DirectSurvivalSelectReq()
{
	W_DeathMatchInfoReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::DirectSurvivalSelectRes), this);
	HttpManager::getSingleton().send(msg);

	GameDataManager::getSingletonPtr()->ResetSurvivalLeftTime();
}

void WebService::DirectSurvivalSelectRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
		//GameDataManager::getSingletonPtr()->FadeinLobby(0.f);
		GameDataManager::getSingletonPtr()->FreeUiProcess();
	}

	W_DeathMatchInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_deathmatchofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());

		if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo_size() == 0)
		{
			string _alert = GameStringDepot::getSingletonPtr()->getString("TXT_NOT_SURVIVAL_ALERT");
			string _text = GameStringDepot::getSingletonPtr()->getString("TXT_NOT_READY_SURVIVAL");

			SimplePopupPanel* _pPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _text, _alert);
			LayerManager::getSingleton().pushDynamicLayer(_pPopup, DYNAMIC_PUSH_LAYER);
			return;
		}

		GameDataManager::getSingletonPtr()->m_bSurvivalTimeUpdate = true;

		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		_pScene->m_LobbyUIPanel->ShowSurvivalUi();

		W_DeathMatchIDReq req;
		req.set_matchid(GameDataManager::getSingletonPtr()->m_TournamentId);
		HttpMessage msg(req, HttpResponseHandler(WebService::DirectSurvivalSelectNextRes), this);
		HttpManager::getSingleton().send(msg);
	}
}

void WebService::DirectSurvivalSelectNextRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		//GameDataManager::getSingletonPtr()->FadeinLobby(0.f);
		GameDataManager::getSingletonPtr()->FreeUiProcess();
		return;
	}

	W_DeathMatchIDRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_deathmatchofinfo())
	{
		GameDataManager::getSingletonPtr()->RemoveSurvivalOfInfo();
		GameDataManager::getSingletonPtr()->m_SurvivalOfInfo = new W_DeathMatchOfInfo(res.deathmatchofinfo());
		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SURVIVAL_SELECT);
		LobbySurvivalWindowMain* _pSelectPanel = new LobbySurvivalWindowMain();
		LayerManager::getSingleton().pushDynamicLayer(_pSelectPanel);
		_pSelectPanel->ApplyData();					
	}

	//GameDataManager::getSingletonPtr()->FadeinLobby(0.8f);
	GameDataManager::getSingletonPtr()->FreeUiProcess();

}

void WebService::VersionReq()
{
	PanelHelper::pushLoadingPanel(GameStringDepot::getSingleton().getString("VERSION_CHECK_REQ_DESC"));
	W_VersionReq req; //TODO versionreq에 마켓타입 끼워서 보내기
	HttpMessage msg(req, HttpResponseHandler(WebService::VersionRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::VersionRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		if (LayerManager::getSingletonPtr()->hasLayer("Title"))
		{
			TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
			_panel->showLoginButton(true);
		}
		return;
	}

	W_VersionRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());
	wstring str = StringConverter::toWstring(res.checkmessage());
	if (!res.islive())
	{
		//서버 없음 알림.
		string _text = res.checkmessage();
		SimplePopupPanel* _pPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _text);
		LayerManager::getSingleton().pushDynamicLayer(_pPopup, DYNAMIC_PUSH_LAYER);
		if (LayerManager::getSingletonPtr()->hasLayer("Title"))
		{
			TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
			_panel->showLoginButton(true);
		}
		PanelHelper::popLoadingPanel();
		return;
	}



	if (res.majorver() != VERSION_MAJOR || res.minorver() != VERSION_MINOR || res.descver() != VERSION_MAINTENANCE)
	{
		m_UpdateUrl = res.updateurl();

		string _text = GameStringDepot::getSingletonPtr()->getString("TXT_NEW_VERSION_UPDATE");
		SimplePopupPanel* _pPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::VERSION_NOTICE, _text);
		_pPopup->setListener(this);
		string _okMsg = "OPEN_URL";
		_pPopup->SetOkEventMsg(_okMsg);
		LayerManager::getSingleton().pushDynamicLayer(_pPopup, DYNAMIC_PUSH_LAYER);
		PanelHelper::popLoadingPanel();
		return;
	}
	
	_sendPreloginReq();
}

void WebService::sendGooglePlatFormReq()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLog("sendGooglePlatFormReq userd = %s", GoogleManager::getSingleton().getGoogleUserId().c_str());
	W_PlatformReq req;
	req.set_logintype(eLoginType::GOOGLE);
	req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString(GoogleManager::getSingleton().getGoogleUserId(), LOGIN_REQ_KEY, mInitialVector));
	req.set_imageurl(GoogleManager::getSingleton().getGooglePhotoUrl());
	HttpMessage msg(req, HttpResponseHandler(WebService::recvGooglePlatFormRes), this);
	HttpManager::getSingleton().send(msg);
#endif
}

void WebService::recvGooglePlatFormRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_PlatformRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		GameDataManager::getSingleton().getUserInfo()->set_islogingoogle(res.islogingoogle());
		GameDataManager::getSingleton().getUserInfo()->set_isloginfacebook(res.isloginfacebook());

		//faceook 연동이 되어 있으면 loginType 저장은 안한다.
		if (!res.isloginfacebook()) {
			//처리 완료 되면
			GameDataManager::getSingletonPtr()->SetLoginType(eLoginType::GOOGLE);
			//멀로 저장했는지 저장한다.
			CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyLoginType.c_str(), GameDataManager::getSingletonPtr()->m_LoginType);
			CCUserDefault::sharedUserDefault()->flush();
		}
		
		if (LayerManager::getSingleton().hasLayerType<LobbyOptionPanel>()){
			LobbyOptionPanel* lobbyOptionPanel = dynamic_cast<LobbyOptionPanel*>(LayerManager::getSingleton().getLayerType<LobbyOptionPanel>());
			if (lobbyOptionPanel) {
				lobbyOptionPanel->onRefresh();
			}
		}
	}
	else {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//구글 로그 아웃 시켜야 한다.
		CCLog("logout_2!");
		if (LayerManager::getSingleton().hasLayerType<LobbyOptionPanel>()){
			LobbyOptionPanel* lobbyOptionPanel = dynamic_cast<LobbyOptionPanel*>(LayerManager::getSingleton().getLayerType<LobbyOptionPanel>());
			if (lobbyOptionPanel) {				
				lobbyOptionPanel->beLogOut();
			}
		}		
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
#endif
	}
}

void WebService::sendFacebookPlatFormReq()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLog("sendFacebookPlatFormReq userd = %s", GameDataManager::getSingletonPtr()->m_FacebookUserId.c_str());
	W_PlatformReq req;
	req.set_logintype(eLoginType::FACEBOOK);
	req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString(GameDataManager::getSingletonPtr()->m_FacebookUserId, LOGIN_REQ_KEY, mInitialVector));
	req.set_imageurl(GameDataManager::getSingletonPtr()->m_FacebookUserPhotoUrl);
	HttpMessage msg(req, HttpResponseHandler(WebService::recvFacebookPlatFormRes), this);
	HttpManager::getSingleton().send(msg);
#endif
}

void WebService::recvFacebookPlatFormRes(HttpMessage* msg)
{
	if (msg->hasCode()) {		
		return;
	}

	W_PlatformRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		//처리 완료 되면
		//멀로 저장했는지 저장한다.
		GameDataManager::getSingleton().getUserInfo()->set_islogingoogle(res.islogingoogle());
		GameDataManager::getSingleton().getUserInfo()->set_isloginfacebook(res.isloginfacebook());


		GameDataManager::getSingletonPtr()->SetLoginType(eLoginType::FACEBOOK);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyLoginType.c_str(), GameDataManager::getSingletonPtr()->m_LoginType);
		CCUserDefault::sharedUserDefault()->flush();		
		if (LayerManager::getSingleton().hasLayerType<LobbyOptionPanel>()){
			LobbyOptionPanel* lobbyOptionPanel = dynamic_cast<LobbyOptionPanel*>(LayerManager::getSingleton().getLayerType<LobbyOptionPanel>());
			if (lobbyOptionPanel) {
				lobbyOptionPanel->onRefresh();
			}
		}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		FacebookManager::getSingletonPtr()->RequestOriginUserList();
#endif		
	}
	else {
		//이 페이스북 계정은 이미 guest 와 연결되어 있다.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		FacebookManager::getSingleton().LogOut();
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
#endif // DEBUG
	}
}

void WebService::sendReputeRankReq(int index)
{
	W_ReputeRankReq req;
	if (index == 0) {
		req.set_type(W_ReputeRankReq_eRankType_All);
		HttpMessage msg(req, HttpResponseHandler(WebService::recvTotalReputeRankRes), this);
		HttpManager::getSingleton().send(msg);
	}
	else {
		req.set_type(W_ReputeRankReq_eRankType_Friend);
		HttpMessage msg(req, HttpResponseHandler(WebService::recvFriendReputeRankRes), this);
		HttpManager::getSingleton().send(msg);
	}			
}

void WebService::recvTotalReputeRankRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_ReputeRankRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (LayerManager::getSingleton().hasLayerType<LobbyRecordPanel>()){
		LobbyRecordPanel* lobbyRecordPanel = dynamic_cast<LobbyRecordPanel*>(LayerManager::getSingleton().getLayerType<LobbyRecordPanel>());
		lobbyRecordPanel->recvTotalReputeRankRes(res);
	}
}

void WebService::recvFriendReputeRankRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_ReputeRankRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (LayerManager::getSingleton().hasLayerType<LobbyRecordPanel>()){
		LobbyRecordPanel* lobbyRecordPanel = dynamic_cast<LobbyRecordPanel*>(LayerManager::getSingleton().getLayerType<LobbyRecordPanel>());
		lobbyRecordPanel->recvFriendReputeRankRes(res);
	}
}

void WebService::sendFreeChargeReq()
{
	W_FreeChargeReq  req;
	req.set_markettype(getMarketType());
	HttpMessage msg(req, HttpResponseHandler(WebService::recvFreeChargeRes), this);
	HttpManager::getSingleton().send(msg);	
}

void WebService::recvFreeChargeRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FreeChargeRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
}

void WebService::sendW_GranChanceNormalReq()
{
	W_GranChanceReq  req;
	req.set_markettype(getMarketType());

	req.set_chancetype(W_GranChanceReq_eGranChanceType_c_normal);
	HttpMessage msg(req, HttpResponseHandler(WebService::recvW_GranChanceRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::sendW_GranChanceRandomReq()
{
	W_GranChanceReq  req;
	req.set_markettype(getMarketType());
	req.set_chancetype(W_GranChanceReq_eGranChanceType_c_random);
	HttpMessage msg(req, HttpResponseHandler(WebService::recvW_GranChanceRandomRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::recvW_GranChanceRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_GranChanceRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());


	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	int64 rewardGold = 0;
	if (res.has_rewardinfo() && res.rewardinfo().rewardset_size() > 0) {
		rewardGold = res.rewardinfo().rewardset(0).amount();
	}	

	if (res.has_errorstring())
	{
		LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
	}
	else {
		if (res.has_rewardinfo() && res.rewardinfo().rewardset_size() > 0) {
			string resultMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(rewardGold));
			string descStr = NxGetFormatString(GameStringDepot::getSingleton().getString("GranResultDesc"), resultMoney);			
			PanelHelper::pushBigPotRewardPanel(descStr , res.rewardinfo());
		}
	}
}

void WebService::recvW_GranChanceRandomRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_GranChanceRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());


	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	int64 rewardGold = 0;
	if (res.has_rewardinfo() && res.rewardinfo().rewardset_size() > 0) {
		rewardGold = res.rewardinfo().rewardset(0).amount();
	}

	if (res.has_errorstring())
	{
		LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
	}
	else {
		if (res.has_rewardinfo() && res.rewardinfo().rewardset_size() > 0) {
			string resultMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(rewardGold));
			string descStr = NxGetFormatString(GameStringDepot::getSingleton().getString("GranResultRandomDesc"), resultMoney);
			PanelHelper::pushBigPotRewardPanel(descStr, res.rewardinfo());
		}
	}
}

void WebService::sendLimitedReq(vector<W_LimitShopData_eLimitType> types)
{
	W_LimitShopReq  req;
	for (int i = 0; i < types.size(); i++)
	{
		req.add_limittype(types[i]);
	}
	HttpMessage msg(req, HttpResponseHandler(WebService::recvLimitedRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::recvLimitedRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_LimitShopRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	for (int i = 0; i < res.limitshopinfo_size(); i++)
	{
		GameDataManager::getSingleton().setLimitShopInfo(res.limitshopinfo(i));
	}
}


void WebService::sendNoticeinfoReq()
{
	W_NoticeInfoReq req;
	HttpMessage msg(req, HttpResponseHandler(WebService::recvNoticeinfoRes), this);
	LastSendNotiTime = GameDataManager::getSingletonPtr()->GetNowTime();
	HttpManager::getSingleton().send(msg);
}

void WebService::recvNoticeinfoRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_NoticeInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());
	GameDataManager::getSingletonPtr()->AsyncTime(res.nowtime());

	if (res.msg() != "") {
		GameDataManager::getSingletonPtr()->NoticePanelDesc = res.msg();
		SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::AdminNotice, res.msg().c_str());
		if (_popupPanel)
		{
			LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
			_popupPanel->RemainFromEnd = res.remainsec();
			_popupPanel->RegistTurnOffAdminMessage(res.remainsec());
		}
	}

	GameDataManager::getSingletonPtr()->SetSurvivalNotiTimer();
}

void WebService::_sendSkinBuyReq(int32 id)
{
	mCharacterBuyId = id;
	W_SkinBuyReq req;
	req.set_buyid(mCharacterBuyId);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvSkinBuyRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvSkinBuyRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_SkinBuyRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
	{
		int32 _curRuby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
		int32 _nextRuby = res.playerinfo().cash();
		PanelHelper::pushSkinBuySucessPanel(mCharacterBuyId, _nextRuby - _curRuby);
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
	}
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_BUY_CHARACTER_RES);	//갱신이라 공유한다.
}

void WebService::_sendSkinSelectReq(int32 _id)
{
	W_SkinSelectReq req;
	req.set_id(_id);
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvSkinSelectRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvSkinSelectRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_SkinSelectRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{

			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());


	GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_SELECT_CHARACTER_RES);

	//SelectCharacterPanel * _pPanel = dynamic_cast<SelectCharacterPanel*>(LayerManager::getSingleton().getCurrentLayer());
	//_pPanel->ChangeCharacterCellUse();
}

void WebService::_sendFaceFriendGiftSendReq(vector<int64>& _uidList)
{
	W_FaceFriendGiftSendReq req;
	int _size = _uidList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		req.add_uid(_uidList[_i]);
	}
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFaceFriendGiftSendRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFaceFriendGiftSendRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FaceFriendGiftSendRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (!res.has_friendofinfo())
		return;

	W_FriendOfInfo _friendOfInfo = res.friendofinfo();

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

	PanelHelper::pushAnnounceNotiPanel(GameStringDepot::getSingleton().getString("FRIEND_SEND_CHIP"));
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_UPDATE_FRIEND_LIST_RES);
}

void WebService::_sendFaceFriendGiftReceiveReq(vector<int64>& _uidList)
{
	W_FaceFriendGiftReceiveReq req;

	int _size = _uidList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		req.add_uid(_uidList[_i]);
	}
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFaceFriendGiftReceiveRes), this);
	HttpManager::getSingleton().send(msg);
}

void WebService::_recvFaceFriendGiftReceiveRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FaceFriendGiftReceiveRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorcode())
		{
			//ParsingErrorCode(res.errorcode());
		}
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (!res.has_friendofinfo())
		return;

	W_FriendOfInfo _friendOfInfo = res.friendofinfo();

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
	PanelHelper::pushAnnounceNotiPanel(GameStringDepot::getSingleton().getString("FRIEND_RECV_CHIP"));
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_UPDATE_FRIEND_LIST_RES);
}

void WebService::_sendFacebookRequestListReq()
{

	CCLog("_sendFacebookRequestListReq");
	W_FaceFriendOfInfoReq req;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	vector<FaceBookFriendData*> facebookFriends = FacebookManager::getSingletonPtr()->GetAllFacebookFriends();
	for (int i = 0; i < facebookFriends.size(); i++)
	{
		CCLog("add faceuid = %s", facebookFriends[i]->id.c_str());
		req.add_faceuid(facebookFriends[i]->id);
	}
#else
	req.add_faceuid("102644857008878"); 

#endif // DEBUG
	HttpMessage msg(req, HttpResponseHandler(WebService::_recvFacebookRequestListRes), this);
	HttpManager::getSingleton().send(msg);
}


void WebService::_recvFacebookRequestListRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_FaceFriendOfInfoRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());


	W_FriendOfInfo _friendOfInfo = res.friendofinfo();

	int _size = _friendOfInfo.facefriendinfo_size();

	CCLog("_size = %d", _size);
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

	CCLog("_recvFacebookRequestListRes 2");
	GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_UPDATE_FRIEND_LIST_RES);
}

void WebService::sendPlatoformOutReq(eLoginType type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	W_PlatformOutReq req;
 	req.set_logintype(type);
	req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString("", LOGIN_REQ_KEY, mInitialVector));

// 	if (type == GOOGLE) {
// 		CCLog("GoogleManager::getSingleton().getGoogleUserId() = %s" , GoogleManager::getSingleton().getGoogleUserId().c_str());
// 		req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString(GoogleManager::getSingleton().getGoogleUserId(), LOGIN_REQ_KEY, mInitialVector));
// 	}
// 	else if (type == FACEBOOK) {
// 		CCLog("FACEBOOK = %s" , GameDataManager::getSingletonPtr()->m_FacebookUserId.c_str());
// 		req.mutable_platformkey()->CopyFrom(GameDataManager::getEncryptString(GameDataManager::getSingletonPtr()->m_FacebookUserId, LOGIN_REQ_KEY, mInitialVector));
// 	}

	HttpMessage msg(req, HttpResponseHandler(WebService::recvPlatoformOutRes), this);
	HttpManager::getSingleton().send(msg);
#endif
}

void WebService::recvPlatoformOutRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}
	W_PlatformOutRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorstring())
		{

			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}
	CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyLoginType.c_str(), 0);
	CCUserDefault::sharedUserDefault()->flush();

	//
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (GoogleManager::getSingleton().isConnected() && !res.islogingoogle()) {
		GoogleManager::getSingleton().googleLogOut();
	}

	if (GameDataManager::getSingletonPtr()->m_FacebookUserId != "" && !res.isloginfacebook()) {
		FacebookManager::getSingleton().LogOut();
	}
#endif
	GameDataManager::getSingleton().getUserInfo()->set_islogingoogle(res.islogingoogle());
	GameDataManager::getSingleton().getUserInfo()->set_isloginfacebook(res.isloginfacebook());


	//로그인 타입은 guest 로
	GameDataManager::getSingleton().SetLoginType(GUEST);
	if (LayerManager::getSingleton().hasLayerType<LobbyOptionPanel>()){
		LobbyOptionPanel* lobbyOptionPanel = dynamic_cast<LobbyOptionPanel*>(LayerManager::getSingleton().getLayerType<LobbyOptionPanel>());
		if (lobbyOptionPanel) {
			lobbyOptionPanel->onRefresh();
		}
	}

}


bool WebService::CheckNotiSend()
{
	auto Nowtime = GameDataManager::getSingletonPtr()->GetNowTime();
	struct tm Nowtime_tm;
	struct tm LastTime_tm;
	
	localtime_r(&Nowtime , &Nowtime_tm);
	localtime_r(&LastSendNotiTime,&LastTime_tm);

	if (Nowtime < 0)
		return false;

	if (GameDataManager::getSingletonPtr()->ShouldAsyncTime()){
		return true;
	}
		

	bool a = (Nowtime_tm.tm_min != LastTime_tm.tm_min);
	bool b = (Nowtime_tm.tm_min % 10 == 0);
	bool c = (GameDataManager::getSingletonPtr()->getUserInfo() != 0);
	bool d = a && b && c;

	if ((Nowtime_tm.tm_min != LastTime_tm.tm_min) &&
		(Nowtime_tm.tm_min%10 == 0) &&
		(GameDataManager::getSingletonPtr()->getUserInfo() != 0)) {
		return true;
	}
	else
		return false;
}

void WebService::CheckAndRedirectIP(W_ChannelInfo* _param)
{
	if (GAMBLE_DEFAULT_URL == "http://192.168.0.161:8200/poker_server/")
		_param->set_ip("192.168.0.161");
	else if (GAMBLE_DEFAULT_URL == "http://192.168.0.164:8201/poker_server/")
		_param->set_ip("192.168.0.164");
	
	CCLOG("Chanel Name = %s    Chanel ID = %d", _param->name().c_str(), _param->id());
}
