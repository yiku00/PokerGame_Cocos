#include "pch.h"
#include "ILoveGameImpl.h"
#include "NxUtil.h"
#include "CmdQueue.h"
#include "CmdList.h"
//#include "FriendTestReq.pb.h"
//#include "FriendTestRes.pb.h"
//#include "ServerListReq.pb.h"
//#include "ServerListRes.pb.h"
//#include "GlobalDefine.h"

#define MARKET_STRING "LOCAL"
#define LOGIN_WIN32_NICKNAME "WIN32"
#define LOGIN_WIN32_NAME "0"
#define LOGIN_WIN32_ID "1"
#define LOGIN_WIN32_PROFILE_IMAGE_URL "http://192.168.0.234:9099/heroes_server/test1.png"
#define AGREEMENT_KEY "agreement"
#define MESSAGE_BLOCK_KEY "message_block"

std::string ILoveGameImpl::getMarket()
{
	return MARKET_STRING;
}

bool ILoveGameImpl::isAgreement()
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey(AGREEMENT_KEY, false);
}

void ILoveGameImpl::setAgreement(bool agree)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey(AGREEMENT_KEY, agree);
}

void ILoveGameImpl::openAgreement()
{
}

bool ILoveGameImpl::isValid()
{
	return false;
}

void ILoveGameImpl::login()
{
	STCMD_ILOVEGAME_LOGIN_RESULT result;
	result.success = true;
	result.code = LOGIN_SUCCESS_CODE;

	CSJson::Value params;
	params["UserName"] = LOGIN_WIN32_NAME;
	params["UserID"] = LOGIN_WIN32_ID;
	result.result = params.toStyledString();

	CCmdQueue::getSingleton().pushQueue(result);
}

void ILoveGameImpl::loginWithToken(bool simple)
{
	STCMD_ILOVEGAME_LOGINWITHTOKEN_RESULT result;
	result.isSimple = simple;
	result.success = true;
	result.code = LOGIN_SUCCESS_CODE;

	CCmdQueue::getSingleton().pushQueue(result);

	mIsSimpleLogin = simple;
}

void ILoveGameImpl::loginId(const string& id, const string& pw)
{
	STCMD_ILOVEGAME_LOGIN_RESULT result;
	result.success = true;
	result.code = LOGIN_SUCCESS_CODE;

	CSJson::Value params;
	params["UserName"] = LOGIN_WIN32_NAME;
	params["UserID"] = LOGIN_WIN32_ID;
	result.result = params.toStyledString();

	CCmdQueue::getSingleton().pushQueue(result);
}

void ILoveGameImpl::registerId(const string& id, const string& pw)
{
	STCMD_ILOVEGAME_REGISTER_RESULT result;
	result.success = true;
	result.code = LOGIN_SUCCESS_CODE;

	CCmdQueue::getSingleton().pushQueue(result);
}

void ILoveGameImpl::logout()
{
	STCMD_ILOVEGAME_LOGOUT_RESULT result;
	result.success = true;
	result.code = 0;

	CCmdQueue::getSingleton().pushQueue(result);
}

void ILoveGameImpl::unregister()
{
	STCMD_ILOVEGAME_UNREGISTER_RESULT result;
	result.success = true;
	result.code = 1000;

	CCmdQueue::getSingleton().pushQueue(result);
}

std::string ILoveGameImpl::getNickname()
{
	return LOGIN_WIN32_NICKNAME;
}

std::string ILoveGameImpl::getName()
{
	return LOGIN_WIN32_NAME;
}

std::string ILoveGameImpl::getId()
{
	return LOGIN_WIN32_ID;
}

std::string ILoveGameImpl::getProfileImageUrl()
{
	return LOGIN_WIN32_PROFILE_IMAGE_URL;
}

void ILoveGameImpl::getServerList(const string& sort)
{
// 	ServerListReq req;
// 	int serverType = CCUserDefault::sharedUserDefault()->getIntegerForKey(USER_DEFAULT_DEVSERVER, 1);
// 	req.set_type((ServerListReq_ServerType)serverType);
// 
// 	HttpMessage msg(req, HttpResponseHandler(ILoveGameImpl::_recvServerListRes), this);
// 	HttpManager::getSingleton().send(msg);
}

void ILoveGameImpl::getFriendList()
{
	//FriendTestReq req;
	//HttpMessage msg(req, HttpResponseHandler(ILoveGameImpl::_recvFriendTestRes), this);
	//msg.setToWait(false);
	//HttpManager::getSingleton().send(msg);
}

void ILoveGameImpl::getInviteList()
{
	//FriendTestReq req;
	//HttpMessage msg(req, HttpResponseHandler(ILoveGameImpl::_recvInviteTestRes), this);
	//msg.setToWait(false);
	//HttpManager::getSingleton().send(msg);
}

int ILoveGameImpl::getInviteCount()
{
	return 0;
}

void ILoveGameImpl::_recvServerListRes(HttpMessage* msg)
{
// 	if (msg->hasCode()) {
// 		STCMD_ILOVEGAME_SERVER_RESULT result;
// 		result.success = false;
// 		CCmdQueue::getSingleton().pushQueue(result);
// 		return;
// 	}
// 
// 	ServerListRes res;
// 	res.ParseFromArray(msg->getData(), msg->getSize());
// 	NXASSERT(res.IsInitialized());
// 
// 	CSJson::Value root;
// 	CSJson::Value& servers = root["serverlist"];
// 
// 	string version = StringConverter::toString(res.majorver()) + "." + StringConverter::toString(res.minorver()) + "."
// 		+ StringConverter::toString(res.buildver());
// 
// 	for_each(res.list().begin(), res.list().end(), [&servers, &version](const ServerListRes_ServerList& server) {
// 		CSJson::Value info;
// 		info["server"] = server.id();
// 		info["name"] = server.name();
// 		info["addr"] = server.address();
// 		info["port"] = server.port();
// 		info["vers"] = version;
// 		info["md5"] = "checksum";
// 		info["status"] = server.status();
// 		info["info"] = server.info();
// 
// 		servers.append(info);
// 	});
// 
// 	STCMD_ILOVEGAME_SERVER_RESULT result;
// 	result.success = true;
// 	result.result = root.toStyledString();
// 	CCmdQueue::getSingleton().pushQueue(result);
}

void ILoveGameImpl::_recvFriendTestRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	//FriendTestRes res;
	//res.ParseFromArray(msg->getData(), msg->getSize());
	//NXASSERT(res.IsInitialized());

	//CSJson::Value friends;

	//for (int i = 0; i < res.kakaotest_size(); ++i)
	//{
	//	friends[i]["nickname"] = res.kakaotest(i).nickname();
	//	friends[i]["username"] = "ilovegame";
	//	friends[i]["user_id"] = res.kakaotest(i).kakaoid();
	//	friends[i]["imageurl"] = res.kakaotest(i).url();
	//	friends[i]["is_visible"] = res.kakaotest(i).invite();
	//}

	//STCMD_ILOVEGAME_FRIEND_RESULT friendResult;
	//friendResult.count = res.kakaotest_size();
	//friendResult.result = friends.toStyledString();

	//CCmdQueue::getSingleton().pushQueue(friendResult);
}

void ILoveGameImpl::_recvInviteTestRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	//FriendTestRes res;
	//res.ParseFromArray(msg->getData(), msg->getSize());
	//NXASSERT(res.IsInitialized());

	//CSJson::Value friends;

	//for (int i = 0; i < res.kakaotest_size(); ++i)
	//{
	//	friends[i]["nickname"] = res.kakaotest(i).nickname();
	//	friends[i]["user_id"] = res.kakaotest(i).kakaoid();
	//	friends[i]["profile_image_url"] = res.kakaotest(i).url();
	//	friends[i]["is_visible"] = res.kakaotest(i).invite();
	//}

	//STCMD_ILOVEGAME_INVITE_RESULT inviteResult;
	//inviteResult.count = res.kakaotest_size();
	//inviteResult.result = friends.toStyledString();

	//CCmdQueue::getSingleton().pushQueue(inviteResult);
}

void ILoveGameImpl::charge(const string& serverId, const string& productId)
{
	STCMD_ILOVEGAME_CHARGE_RESULT result;
	result.success = true;
	result.code = 0;

	result.serverId = serverId;
	result.productId = productId;

	CCmdQueue::getSingleton().pushQueue(result);
}

void ILoveGameImpl::intro()
{

}

void ILoveGameImpl::openEvent()
{

}

void ILoveGameImpl::openHomepage()
{

}

void ILoveGameImpl::openHelp()
{

}

void ILoveGameImpl::coupon(const string& number)
{
	STCMD_ILOVEGAME_COUPON_RESULT result;
	result.success = true;
	result.code = 0;

	result.number = number;

	CCmdQueue::getSingleton().pushQueue(result);
}

void ILoveGameImpl::sendPlayerInfo(const string& info)
{
	STCMD_ILOVEGAME_SEND_PLAYERINFO_RESULT result;
	result.success = true;
	result.code = 0;

	CCmdQueue::getSingleton().pushQueue(result);
}

void ILoveGameImpl::sendInvite(const string& userId, const string& serverId)
{
	STCMD_ILOVEGAME_SEND_INVITE_RESULT res;
	res.success = true;

	res.userId = userId;
	res.serverId = serverId;

	CCmdQueue::getSingleton().pushQueue(res);
}

void ILoveGameImpl::sendPush(const string& username, const string& message)
{
	STCMD_ILOVEGAME_SEND_PUSH_RESULT res;
	res.success = true;

	res.userName = username;
	res.message = message;

	CCmdQueue::getSingleton().pushQueue(res);
}

void ILoveGameImpl::sendMessage(const string& username, const string& templateId)
{
	STCMD_ILOVEGAME_SEND_MESSAGE_RESULT res;
	res.success = true;

	res.userName = username;
	res.templateId = templateId;

	CCmdQueue::getSingleton().pushQueue(res);
}

void ILoveGameImpl::setMessageBlock(bool enable)
{
	//test °á°ú message
	STCMD_ILOVEGAME_SET_MESSAGE_BLOCK_RESULT res;
	res.success = true;

	res.enable = enable;

	CCmdQueue::getSingleton().pushQueue(res);
}

bool ILoveGameImpl::getMessageBlock()
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey(MESSAGE_BLOCK_KEY, false);
}

void ILoveGameImpl::sendFaceBookPosting(const string& name, const string& caption, const string& description, const string& link, const string& picture, const string& postingcode)
{
	STCMD_ILOVEGAME_SET_FACEBOOK_POSTING_RESULT res;
	res.success = true;
	res.code = 0;
	CCmdQueue::getSingleton().pushQueue(res);
}
