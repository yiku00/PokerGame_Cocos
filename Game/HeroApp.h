/********************************************************************
	file name:	HeroApp.h
	
	purpose:	Hero 앱 클래스
*********************************************************************/
#pragma once 

#include "NxFramework.h"
#include "NxSingleton.h"
#include "MessagePanel.h"
#include "TypeDefine.pb.h"


class HeroApp : public CCObject, private CCApplication, public Singleton<HeroApp>, public Nx::Scene::Listener
{
public:
	HeroApp();
	~HeroApp();

public:
    /**
    @brief	Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

	void end();

public:
	const string& getVersionString() { return mVersion; }

	const CCSize& getDesignSize() { return mDesignSize; }
	const CCPoint& getCenterPoint() { return mCenterPoint; }

	void startWaiting();
	void stopWaiting();

	void showMessagePanel(const string& msg, const string& title = "",
		CCObject* target = NULL, ObjectListener listener = NULL, MessagePanel::MessageType type = MessagePanel::OK);

	void showTopMessagePanel(const string& msg, const string& title = "",
		CCObject* target = NULL, ObjectListener listener = NULL, MessagePanel::MessageType type = MessagePanel::OK);

	void showServerErrorMessage(const string& msg, const string& title = "" , const string& notice = "" ,
		CCObject* target = NULL, ObjectListener listener = NULL, MessagePanel::MessageType type = MessagePanel::OK);

	void showMessageNoticePanel(const string& msg, const string& title = "" , const string& notice = "" ,
		CCObject* target = NULL, ObjectListener listener = NULL, MessagePanel::MessageType type = MessagePanel::OK);

	//debug 모드 일때만 보여준다.
	void showMessagePanel(const wstring& msg, const wstring& title = L"" ,
		CCObject* target = NULL, ObjectListener listener = NULL, MessagePanel::MessageType type = MessagePanel::OK);
	
	//반드시 해야 할 메세지 나중 정리 예정
	void notiServerErrorMessage(const string& msg, const string& title = "" , const string& notice = "" ,
		CCObject* target = NULL, ObjectListener listener = NULL, MessagePanel::MessageType type = MessagePanel::OK);


	void showFunctionClose();
	//void showNoMoneyPanel(GameResourceType type);
	void hideMessagePanel();

	void setConnected(bool login) { mConnected = login; }
	bool isConnected() { return mConnected; }

	int getMajorVersion();
	int getMinorVersion();
	int getBuildNumber();
	const string getBuildName();

	void refresh();
	bool isRefreshing() { return mRefreshing; }

	double getActiveTime() { return mActiveTime; }
	float getElapsedTime() { return mElapsedTime; }

	void resetPing();

	void logOut();
	void exit();
	void setFaceBookUrl(const string& url) { mFaceBookShardUrl = url; }
	const string getFaceBookUrl() {return mFaceBookShardUrl; }
	void connectionInitAni();	//연결이 끊겼을대 해야할 일들

public: // Scene::Listener
	virtual void onFinalized();

private:
	void update(float dt);

	void _sendRefreshReq(bool fresh = false);
	void _recvRefreshRes(HttpMessage* msg);
	void _sendPing();
	void _recvPong(HttpMessage* msg);

	void _onExit(const string& msg);
	
private:
	CCSize mDesignSize;
	CCPoint mCenterPoint;
	string mVersion;
	string mFaceBookShardUrl;
	bool mConnected;
	bool mRefreshTriggerred;
	bool mRefreshing;
	bool mRefreshRequested;
	uint mWaitingCount;
	double mActiveTime;
	float mElapsedTime;
	bool mLogOut;
	float mPingDelay;
	bool mPingPong;
	int mCurTime;
};
