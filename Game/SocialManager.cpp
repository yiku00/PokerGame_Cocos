#include "pch.h"
#include "SocialManager.h"
#include "android/ILoveGameImpl.h"
#include "NxUtil.h"
#include "NxStringConverter.h"
#include "MetaDataMgr.h"
#include "CmdList.h"
#include "CurlMgr.h"
#include "CmdQueue.h"
#include "NxSceneManager.h"

static const string ProfileImageExt[] = {
	".jpg",
	".jpeg",
	".png",
};

static const string ProfileImageExtDefault = ".jpg";

template<> SocialManager* Singleton<SocialManager>::msSingleton = nullptr;
static string sImageCachePath;

SocialManager::SocialManager()
{
	mInterface = new ILoveGameImpl;
	mGameFriendsInit = false;
	mSocialFriendsInit = false;
	mRefreshFriendTarget = nullptr;
	mRefreshFriendListener = nullptr;
	mRefreshInviteTarget = nullptr;
	mRefreshInviteListener = nullptr;

	sImageCachePath = CCFileUtils::sharedFileUtils()->getWritablePath();

	mMessageBlock = false;
}

SocialManager::~SocialManager()
{
	delete mInterface;
}

void SocialManager::initialize()
{
	mNickname = mInterface->getNickname();
	mUserName = mInterface->getName();
	mUserId = mInterface->getId();
	mProifleImageUrl = mInterface->getProfileImageUrl();

	critterSetUsername(mUserName);
}

void SocialManager::release()
{
	mGameFriendsInit = false;
	mSocialFriendsInit = false;
}

void SocialManager::fetchFriends()
{
	if (!mGameFriendsInit)
		mInterface->getFriendList();
	if (!mSocialFriendsInit)
		mInterface->getInviteList();
}

void SocialManager::refreshFriendList(CCObject* target /*= nullptr*/, ObjectListener listener /*= nullptr*/)
{
	mInterface->getFriendList();

	CC_SAFE_RELEASE_NULL(mRefreshFriendTarget);

	if (target && listener) {
		mRefreshFriendTarget = target;
		CC_SAFE_RETAIN(mRefreshFriendTarget);
		mRefreshFriendListener = listener;
	}
}

void SocialManager::refreshInviteList(CCObject* target /*= nullptr*/, ObjectListener listener /*= nullptr*/)
{
	mInterface->getInviteList();
	mRefreshInviteTarget = target;
	mRefreshInviteListener = listener;
}

void SocialManager::onRecvFriendResult(const int count, const string& result)
{
	CCLOG("FriendList result : %s", result.c_str());

	mGameFriends.clear();

	CSJson::Reader reader;
	CSJson::Value friends;
	if (count && reader.parse(result, friends)) {
		CCLOG("Game Friends Count : %d", friends.size());

		for (uint i = 0; i < friends.size(); ++i)
		{
			CCLOG("Nickname: %s, Username: %s, UserID: %s, URL : %s\n", friends[i]["nickname"].asCString(), friends[i]["username"].asCString(), friends[i]["user_id"].asCString(), friends[i]["imageurl"].asCString());

			SocialEntity entity;
			entity.nickName = friends[i]["nickname"].asString();
			entity.userName = friends[i]["username"].asString();
			entity.userId = friends[i]["user_id"].asString();
			entity.imageUrl = friends[i]["imageurl"].asString();
			entity.visible = StringConverter::parseInt(friends[i]["is_visible"].asString()) != 0;

			if (entity.userId != mUserId)
				mGameFriends.push_back(entity);
			else {
				mMessageBlock = !entity.visible;
			}

			// 				if (!SocialManager::hasProfileImage(entity.imageUrl)) {
			// 					STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ *pReq = newCMD<STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ>();
			// 					pReq->userId = entity.userId;
			// 					pReq->downloadUrl = entity.imageUrl;
			// 					CCUrlMgr::getSingleton().pushBack(pReq);
			// 				}
		}
	}

	mGameFriendsInit = true;

	if (mRefreshFriendTarget && mRefreshFriendListener) {
		(mRefreshFriendTarget->*mRefreshFriendListener)("friendRefreshed");
		CC_SAFE_RELEASE_NULL(mRefreshFriendTarget);
		mRefreshFriendListener = nullptr;
	}
}

void SocialManager::onRecvInviteResult(const int count, const string& result)
{
	CCLOG("InviteList result : %s", result.c_str());

	mSocialFriends.clear();

	CSJson::Reader reader;
	CSJson::Value friends;
	if (count && reader.parse(result, friends)) {
		CCLOG("Invite Friends Count : %d", friends.size());

		for (uint i = 0; i < friends.size(); ++i)
		{
			CCLOG("InviteList result : %s", friends[i].toStyledString().c_str());

			if (friends[i]["user_id"].isString()) {
				CCLOG("Nickname: %s, UserID: %s, URL : %s\n", friends[i]["nickname"].asCString(), friends[i]["user_id"].asCString(), friends[i]["profile_image_url"].asCString());
			}
			else if (friends[i]["user_id"].isInt()) {
				CCLOG("Nickname: %s, UserID: %lld, URL : %s\n", friends[i]["nickname"].asCString(), friends[i]["user_id"].asInt64(), friends[i]["profile_image_url"].asCString());
			}

			SocialEntity entity;
			entity.nickName = friends[i]["nickname"].asString();
			entity.userId = friends[i]["user_id"].isInt() ?
				StringConverter::toString(friends[i]["user_id"].asInt64()) : friends[i]["user_id"].asString();
			entity.imageUrl = friends[i]["profile_image_url"].asString();

			entity.visible = StringConverter::parseInt(friends[i]["is_visible"].asString()) != 0;
			entity.osSupported = StringConverter::parseInt(friends[i]["supported_device"].asString()) != 0;

			CCLOG("DOODOO : %s, %d", entity.userId.c_str(), entity.visible);

			mSocialFriends.push_back(entity);
		}
	}

	mSocialFriendsInit = true;

	if (mRefreshInviteTarget && mRefreshInviteListener) {
		(mRefreshInviteTarget->*mRefreshInviteListener)("inviteRefreshed");
		mRefreshInviteTarget = nullptr;
		mRefreshInviteListener = nullptr;
	}
}

bool SocialManager::isSocialFriend(const string& gameId)
{
	if (gameId == "")
		return false;

	for (auto it = mSocialFriends.begin(); it != mSocialFriends.end(); ++it)
	{
		if (it->userId == gameId)
			return true;
	}

	return false;
}

SocialEntity* SocialManager::getSocialEntity(const string& gameId)
{
	NXASSERT(isSocialFriend(gameId));
	for (auto it = mSocialFriends.begin(); it != mSocialFriends.end(); ++it)
	{
		if (it->userId == gameId)
			return &(*it);
	}

	return NULL;

}


std::string SocialManager::getProfileImageName(const string& url)
{
	std::string profileImagename = "ilg_";

	profileImagename += StringConverter::toString(CMetaMgr::generateX65599(url.c_str()));

	//std::string::size_type findIndex = url.rfind('.');
	//if (std::string::npos != findIndex)
	//{
	//	profileImagename += url.substr(findIndex);
	//}

	profileImagename += _getProfileImageExt(url);

	return profileImagename;
}

std::string SocialManager::getProfileImagePath(const string& url, const string& folder)
{
	//NXASSERT(isValidProfileImage(url));

	std::string path = sImageCachePath;
	if (folder != "")
	{
		path.append(folder + "\\");
	}
	path.append(getProfileImageName(url));
	return path;
}


bool SocialManager::isValidProfileImage(const string& url)
{
	bool valid = false;
	for (size_t i = 0; i < nxArraySize(ProfileImageExt); ++i)
	{
		const string& ext = ProfileImageExt[i];
		auto it = std::search(url.begin(), url.end(), ext.begin(), ext.end(), [](char a, char b) {
			return std::tolower(a) == std::tolower(b);
		});
		valid = it != url.end();
		if (valid)
			break;
	}
	return valid;
}

bool SocialManager::hasProfileImage(const string& url)
{
	return CCFileUtils::sharedFileUtils()->isFileExist(getProfileImagePath(url));
	//return isValidProfileImage(url) && CCFileUtils::sharedFileUtils()->isFileExist(getProfileImagePath(url));
}

bool SocialManager::isGameFriend(const string& gameId)
{
	if (gameId == "")
		return false;

	for (auto it = mGameFriends.begin(); it != mGameFriends.end(); ++it)
	{
		if (it->userId == gameId)
			return true;
	}

	return false;
}

SocialEntity* SocialManager::getGameEntity(const string& gameId)
{
	NXASSERT(isGameFriend(gameId));
	for (auto it = mGameFriends.begin(); it != mGameFriends.end(); ++it)
	{
		if (it->userId == gameId)
			return &(*it);
	}

	return NULL;
}

void SocialManager::fetchServerList(bool refresh /*= false*/)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (refresh) {
		STCMD_ILOVEGAME_SERVER_RESULT result;
		result.success = true;
		CCmdQueue::getSingleton().pushQueue(result);
		return;
	}
#endif
	if (mInterface)
		mInterface->getServerList("");
}

void SocialManager::onRecvServerList(const string& result)
{
	if (result.empty())
		return;

	mServerList.clear();

	CSJson::Reader reader;
	CSJson::Value root;
	reader.parse(result, root);
	CSJson::Value servers = root["serverlist"];
	for (uint i = 0; i < servers.size(); ++i)
	{
		ServerInfo info;
		info.id = servers[i]["server"].asString();
		info.name = servers[i]["name"].asString();
		info.addr = servers[i]["addr"].asString();
		info.port = servers[i]["port"].asString();
		info.vers = servers[i]["vers"].asString();
		info.md5 = servers[i]["md5"].asString();
		info.status = servers[i]["status"].asInt();
		info.info = servers[i]["info"].asString();

		mServerList.push_back(info);
	}
}

const ServerInfo* SocialManager::getServerInfo(const string& serverId)
{
	auto it = find_if(mServerList.begin(), mServerList.end(), [&serverId](const ServerInfo& info)->bool {
		if (info.id == serverId)
			return true;
		return false;
	});

	if (it != mServerList.end())
		return &*it;
	else
		return nullptr;
}

const ServerInfo* SocialManager::getRecommendedServerInfo()
{
	auto it = find_if(mServerList.begin(), mServerList.end(), [](const ServerInfo& info)->bool {
		if (info.status == 2)
			return true;
		return false;
	});

	if (it != mServerList.end())
		return &*it;
	else
		return nullptr;
}

const string& SocialManager::_getProfileImageExt(const string& url)
{
	for (size_t i = 0; i < nxArraySize(ProfileImageExt); ++i)
	{
		const string& ext = ProfileImageExt[i];
		auto it = std::search(url.begin(), url.end(), ext.begin(), ext.end(), [](char a, char b) {
			return std::tolower(a) == std::tolower(b);
		});

		if (it != url.end()) {
			return ext;
		}
	}

	return ProfileImageExtDefault;
}
