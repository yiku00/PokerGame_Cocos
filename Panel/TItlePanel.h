/********************************************************************
file name:	TitlePanel.h

purpose:	로그인 종류 선택하는 창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "SimplePopupPanel.h"

class TitlePanel : public Panel, public Button::Listener, public Nx::Layer::Listener

//#define USE_FACEBOOK_LOGIN 0
{
public:
	enum TITLE_CMD
	{
		CONNECT_SUCCESS_CMD = 0,		// 접속 성공
	};
	TitlePanel();
	virtual ~TitlePanel();
	void InitPanel();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onKeypadKeyPressed(EventKeyboard::KeyCode  keyCode, Event* /*event*/);
	virtual bool handling(STCMD &stCmd);
	virtual void onEnter() override;

//public Layer::Listener
	virtual void onLayerMessage(const string& msg);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	void showLoginButton(bool visible);
	bool mLoginProcess;

public:
	void autoLogin();	//기존에 접속했던 방법으로 로그인한다. ( 페이스북 or 구글 or 누믹스)
	
private:
	void connectGuest();
	void connectFaceBook();
	void connectGoogle();

	bool _checkIntegrity();

public:
	//Button* m_UserButton[5];
	Button* m_NumixButton1;
	Button* m_NumixButton2;
	Button* m_FaceBookButton1;
	Button* m_FaceBookButton2;
	Button* mGoogleLoginIcon;
	Button* mGoogleLogin;

	//string mName;
	Nx::Label* m_VERSION;
	bool islocal;
	bool m_bShowExitPanel;
	SimplePopupPanel* m_ExitPanel;
	Widget* testImg;

	Nx::Label* mGoogleLoginLabel;
	Nx::Label* mGoogleLoginUnderLabel;
	Nx::Label* mFacebookLoginLabel;
	Nx::Label* mFacebookLoginUnderLabel;
	Nx::Label* mGuestLoginLabel;
	Nx::Label* mGuestLoginUnderLabel;
};
