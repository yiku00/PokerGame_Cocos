/********************************************************************
file name:	LobbyFriendPanel.h

purpose:	로비씬에서 친구 버튼 눌렀을때 친구 관련 구조창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "W_FriendInfo.pb.h"
#include "TockInvtationPanel.h"
#include "TabButtonPanel.h"
#include "LobbyFriend1Panel.h"
#include "LobbyFriend2Panel.h"
#include "LobbyFriendInvitePanel.h"
#include "NotiWidget.h"

#define FRIEND_MAX_COUNT 50
#define RECOMMEND_TAG 1000

class LobbyFriendPanel : public Panel, public Button::Listener
{
	typedef vector<NotiWidget*> NotiWidgetContainer;
public:
	LobbyFriendPanel();
	virtual ~LobbyFriendPanel();

	void InitPanel();
	void InitImage();
	void initButton();
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);	
    void resume();
	virtual void onEnter() override;
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);
	void ShowFriendPanel();
	void HideFriendPanel();
	void ShowFriendUi();
	void HideFriendUi();
	void ShowFriendTitie();
	void HideFriendTitie();
	void ClickTapButton(int _idx);

	void SetFriendlList();

public:
	void refreshFriendPanel();
	void refreshRecommendPanel();	
	void refreshFaceookPanel();
	void facebookRefresh();

private:
	bool cellTouchStart(const CCPoint& tableTouchPoint);
	bool cellTouchCancel(const CCPoint& tableTouchPoint);
	bool cellTouch(const CCPoint& tableTouchPoint);

	void ShowFriendInfoPanel(int _index);
	void updateNotiWidget();
public:
	bool mLoginProcess;

	LobbyFriend1Panel* m_pFriendPanel;
	LobbyFriend2Panel* m_pRecommendPanel;
	LobbyFriendInvitePanel* mFriendInvitePanel;

	TabButtonPanel* m_TapButton[3];
	int m_TapIndex;

	//TockInvtationPanel* m_pTockInvtationPanel;
	CCSize mCellSize;
	NotiWidgetContainer mNotiWidgets;
};