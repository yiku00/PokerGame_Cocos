/********************************************************************
filename: 	LobbyOptionPanel.h

purpose:	로비에서의 옵션창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "LobbyOptionNoticePanel.h"

class LobbyOptionPanel : public Panel, public Button::Listener
{
	enum TAP_BUTTON {
		EN_OPTION,
		EN_ACCOUNT,
		EN_NOTICE,
	};

	struct ACCOUNT_BTN_PARTY
	{
		Button* button;	//연결하시오
		string buttonLabel;
		Nx::Label* connect;	//연결하시오
		Nx::Label* connected;	//연결됨
	};
public:
	

	LobbyOptionPanel();
	virtual ~LobbyOptionPanel();

	void InitPanel();
	void InitImage();
	void initButton();
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onRefresh();
	virtual void onDestroy();
	virtual void onEnter() override;
    void resume();
public:
	virtual bool handling(STCMD &stCmd);
	virtual void update(float dt);

	void ShowOptionStart();
	void HideOptionStart();
	void ShowOptionEnd();
	void HideOptionEnd();

	void SaveOption();
	void beLogOut();	//로그 아웃 되어야 한다.

	void initNotiWidget();
	void updateNotiWidget();

private:
	void initGameOptionPanel();
	void initAccountOptionPanel();
	void initNoticeOptionPanel();
	void refreshFocusPanel(TAP_BUTTON enButton);	//게임옵션 보일때는 계정 옵션창은 안 보이고 화면 밖으로 뺀다.
	void refreshAccountPanel();	//계정 연동시 버튼 on off
	
	void setConnected(ACCOUNT_BTN_PARTY& party);	//연결됨
	void setPossibleConnect(ACCOUNT_BTN_PARTY& party);	// 연결 가능 //Guest 일때
	void setNotConnected(ACCOUNT_BTN_PARTY& party);	//연결 불가( 다른 걸로 연결되어 있다.

	void sendW_PayReq(string tID , string txId, string receipt);
	void recvW_PayRes(HttpMessage* msg);

public:
	bool mLoginProcess;

	CCPoint m_ShowPosition;
	CCPoint m_HiddenPosition;

	int m_ViewDataIndex;
	CCScrollView* m_pReplayListView;
	CCLayer* m_pReplayListContainer;

	bool m_bTouchCancel;

	Panel* m_pBtnPanel[5];
	Panel* m_pTapPanel;
	Panel* m_pTapAccountPanel;
	Panel* m_pTapNoticePanel;

	Button* m_pGameRuleButton;
	Button* m_pCustomerCenterButton;
	Button* m_pTermsButton;
	Button* m_pCouponButton;

	Button* m_MusicButton[2];
	Button* m_EfxButton[2];
	Button* m_VoiceButton[2];
	Button* m_HiddenButton[2];
	Button* m_PopupButton[2];

	SkelObject* m_MusicCheck[2];
	SkelObject* m_EfxCheck[2];
	SkelObject* m_VoiceCheck[2];
	SkelObject* m_HiddenCheck[2];
	SkelObject* m_PopupCheck[2];

	Panel* mGameOptionPanel;	//게임 옵션창
	Panel* mAccountOptionPanel;	//계정 옵션창
	//Panel* mNoticeOptionPanel;		// 공지사항
	
	ACCOUNT_BTN_PARTY mGoogleBtnParty;
	ACCOUNT_BTN_PARTY mFaceBookBtnParty;
	bool mBeLogOut;	//로그 아웃 되어야 한다.	( 구글 로그인 했는데 이미 접속한 연결된 계정이 있다.. 로그아웃을 해야 하는데.. connected 된 후에 logout 해야 한다.

private:
	LobbyOptionNoticePanel* mNoticeOptionPanel;

    typedef vector<class NotiWidget*> NotiWidgetContainer;
    NotiWidgetContainer mNotiWidgets;
};
