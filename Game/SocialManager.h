/********************************************************************
	file name:	NxSocialManager.h

	purpose:	소셜 플랫폼 관리자
	*********************************************************************/
#pragma once

#include "SocialInterface.h"

//struct ServerInfo
//{
//	string id;
//	string name;
//	string addr;
//	string port;
//	string vers;
//	string md5;
//	int status;
//	string info;
//};

struct SocialEntity
{
	string nickName;
	string userName;
	string userId;
	string imageUrl;
	bool visible;
	bool osSupported;
};

struct SocialFriend
{
	SocialEntity entity;

};

struct SocialInvite
{
	SocialEntity entity;
};

typedef vector<ServerInfo> ServerList;
typedef vector<SocialEntity> SocialEntities;

class SocialManager : public Singleton < SocialManager >
{
public:
	SocialManager();
	virtual ~SocialManager();

public:
	SocialInterface* getInterface() { return mInterface; }

	void initialize();
	void release();

	void fetchServerList(bool refresh = false);
	void onRecvServerList(const string& result);
	const ServerList& getServerList() { return mServerList; }
	const ServerInfo* getServerInfo(const string& serverId);
	const ServerInfo* getRecommendedServerInfo();

	void fetchFriends();
	void refreshFriendList(CCObject* target = nullptr, ObjectListener listener = nullptr);
	void refreshInviteList(CCObject* target = nullptr, ObjectListener listener = nullptr);

	const string& getNickname() { return mNickname; }
	const string& getUserName() { return mUserName; }
	const string& getUserId() { return mUserId; }
	const string& getProfileImageUrl() { return mProifleImageUrl; }
	bool getMessageBlock() { return mMessageBlock; }
	void setMessageBlock(bool block) { mMessageBlock = block; }

	void onRecvFriendResult(const int count, const string& result);
	void onRecvInviteResult(const int count, const string& result);

	SocialEntities& getGameFriends() { return mGameFriends; }		//게임하고 있는 사람
	SocialEntities& getSocialFriends() { return mSocialFriends; }	//게임 안 하고 있는 사람

	bool isSocialFriend(const string& gameId);
	SocialEntity* getSocialEntity(const string& gameId);

	bool isGameFriend(const string& gameId);
	SocialEntity* getGameEntity(const string& gameId);

	static string getProfileImageName(const string& url);
	static string getProfileImagePath(const string& url, const string& folder = "");
	static bool isValidProfileImage(const string& url);
	static bool hasProfileImage(const string& url);

	bool isIosHandleOpenUrl() { return mIosHandleOpenUrl; }
	void setIosOpenUrl(bool flag) { mIosHandleOpenUrl = flag; }

private:
	static const string& _getProfileImageExt(const string& url);

private:
	SocialInterface* mInterface;

	ServerList mServerList;

	bool mGameFriendsInit;
	bool mSocialFriendsInit;
	SocialEntities mGameFriends;
	SocialEntities mSocialFriends;

	string mNickname;
	string mUserName;
	string mUserId;
	string mProifleImageUrl;
	bool mMessageBlock;
	bool mIosHandleOpenUrl;

	CCObject* mRefreshFriendTarget;
	ObjectListener mRefreshFriendListener;
	CCObject* mRefreshInviteTarget;
	ObjectListener mRefreshInviteListener;
};
