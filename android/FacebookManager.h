#pragma once
//#include "NxDefine.h"
//#include "pch.h"
//
//#include "NxSingleton.h"
#include "NxFramework.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif


struct FacebookUserData
{
public:
	std::string fb_id;
	std::string fb_name;
	std::string fb_email;
	std::string fb_photoUrl;
};

#define FACEBOOK_OBJECT "com/newzensoft/social/FacebookMgr"

enum FacebookResultCode
{
	FB_ERROR			= 0,
	FB_LOGIN_START		= 1,
	FB_LOGIN_SUCCESS	= 2,
	FB_LOGIN_CANCEL		= 3,
	FB_LOGIN_FAIL		= 4,
	FB_LOGOUT			= 5,
	FB_FRIENDLIST_REQUEST_SUCCESS		= 6,
	FB_FRIENDLIST_REQUEST_FAIL			= 7,
	FB_FRIEND_INVITE_REQUEST_SUCCESS	= 8,
	FB_FRIEND_INVITE_REQUEST_ERROR		= 9,
	FB_FRIEND_INVITE_REQUEST_CANCEL		= 10,
	FB_SEND_EMAIL_SUCCESS				= 11,
	FB_SEND_EMAIL_FAIL					= 12,
	FB_ALREADY_LOGOUT					= 13,
	FB_LOGOUT_FAIL						= 14,
};


struct FaceBookFriendData
{
	string	id;
	string	name;
	string	pictureUrl;

	FaceBookFriendData()
	{
	}


	~FaceBookFriendData()
	{
	}

};


class FacebookManager : public Nx::Singleton < FacebookManager >
{
public:
	class Listener
	{
		public:
			// 팝업이 로딩되었을 때
			virtual void onFacebookEvent(const int resultCode, const std::string paramStr) = 0;
	};	

	FacebookManager();
	~FacebookManager();

	

	//void FacebookUserId();
	//void FacebookUserName();
	//void FacebookUserEmail();
	//void FacebookUserPhotoUrl();

public:
	/* my user info data*/
	FacebookUserData m_UserData;

	/* The function registering facebook manager listener which returns result that java facebookManager execute. */
	void SetListener(FacebookManager::Listener * facebookListener) { listener = facebookListener;  }

	/* The function tring to log-in on Facebook*/
	void ConnectFB();
	
	/* The function which returns result that java facebookManager executes. */
	void OnFacebookEvent(int _event, std::string &paramData);

	/* The function which requests invitable user's friend list */
	void RequestInvitableUserList(bool isNext);
	void RequestOriginUserList();

	/* The function returning friend information that Caller wants to get */
	FaceBookFriendData * GetFacebookFriend(int idx);

	/* The function returning friend information that Caller wants to get */
	vector<FaceBookFriendData*> GetAllFacebookFriends();

	/* The function which try to invite user */
	/* ** WARNING ** */
	/*
	 * Below function, user_id_token is not user_id!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * It is token value that is equivalent to user id!!
	 * So, If Invitation succeed, it is returned not user_id_token but user_id!!!
	 * Don't confuse!!
	*/
	void RequestInviteUser(std::string user_id_token, std::string message);

	std::string GetRecentInviteUserId() { return m_inviteSuccessUser; }

	/* The function that makes a choice if it is printed debug information during progressing facebook interlock */
	void SetPrint(bool isPrint);

	/* The function that returns my facebook user data.*/
	FacebookUserData * GetMyUserData() { return &m_UserData; }
	
	/* The function that is trying to log-out.*/
	void LogOut();

	void appInviteOpenDialog(string applinkurl , string imgurl);	// facebook dptj 앱 초대

	void appLink();	// 앱링크

	string getFacebookFriendName(string id);

private:
	FacebookManager::Listener * listener;

	vector<FaceBookFriendData *> m_friendListData;

	
	std::string m_inviteSuccessUser;

	void clearFriendList();
	void SetFacebookFriendList(string * paramData);

	void SetFacebooUserData();

};
