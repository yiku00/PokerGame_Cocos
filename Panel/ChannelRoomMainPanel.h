#pragma once

#include "NxFramework.h"
#include "ChannelRoomUiPanel.h"
#include "ChannelRoomPage.h"

class ChannelRoomMainPanel : public Panel, public Button::Listener
{
public:
	ChannelRoomMainPanel();
	virtual ~ChannelRoomMainPanel();
	void InitPanel();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void keyBackClicked();
	virtual bool handling(STCMD &stCmd);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	void UpdatePageList();
	void ShowRoomList(bool _visible);
	virtual void onEnter() override;
public:
	bool mLoginProcess;
	bool m_GamePlaying;
	CCRect m_ContentRect;

	ChannelRoomUiPanel* m_pChannelRoomUi;

	CCPoint m_ShowPosition;
	CCPoint m_HidePosition;

	Nx::Label* m_pTitle;
	Nx::Label* m_pTitleUnder;
	TextField* m_searchField;
	
	Button* m_pRoomMakeBtn;
	Button* m_pRoomJoinBtn;
	Button* m_pSearchBtn;
	Button* m_pRoomInputBtn;
};
