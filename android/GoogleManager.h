#pragma once
//#include "NxDefine.h"
//#include "pch.h"

//#include "NxSingleton.h"
#include "NxFramework.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif


struct UserData
{
public:
	std::string _id;
	std::string _name;
	std::string _email;
	std::string _photoUrl;
};

#define GOOGLE_JAVA_OBJECT "com/newzensoft/social/GoogleManager"

class GoogleManager : public Singleton < GoogleManager >
{
public:
	GoogleManager();
	~GoogleManager();

public:	
	void googleInit();
	void googleLogin();	//로그인
	void googleLogOut();	//로그아웃
	void OnLoginConnected();	//구글 연결 됐다.
	void OnGameConnected();
	void OnGameConnectionFailed();
	void OnLoginResult(bool result, string googleID, string googleName, string googleEmail, string  googlePhotoUrl);		//로그인 결과값
	void googleRevokeAccess();	//처음에 시작할때 최근에 접속한 로그인 정보 가지고 있는데 guest 로 들어갈땐 돌린다.

	void setGoogleResult(bool result);
	bool getGoogleResult() { return mIsResult; }

	void setGoogleUserId(string userId) { mGoogleId = userId; }
	string getGoogleUserId() { return mGoogleId; }

	void setGoogleName(string userId) { mGoogleName = userId; }
	string getGoogleName() { return mGoogleName; }

	void setGoogleEmail(string userId) { mGoogleEmail = userId; }
	string getGoogleEmail() { return mGoogleEmail; }

	void setGooglePhotoUrl(string userId) { mPhotoUrl = userId; }
	string getGooglePhotoUrl() { return mPhotoUrl; }

	void logOutResult(bool result);

	//달성 
	void achieveUnlock();
	void achieveIncrement();
	void showAchieve();

	//리더 보드
	void submitLeaderBoard(int score);
	void showLeaderBoard();

	bool isConnected() { return mConnected; }
	bool isGameConnected() { return mGameConnected; }
	bool isGameResulted() { return mGameResulted; }

private:
	void initGoogleLoginData();
private:	
	bool mIsResult;
	std::string mGoogleId;
	std::string mGoogleName;
	std::string mGoogleEmail;
	std::string mPhotoUrl;
	bool mConnected;		//접속 됬는가.
	bool mGameConnected;	//로그인한 후에 게임에 로그인했나 실패헀나
	bool mGameResulted;		//결과값 왔나.
};
