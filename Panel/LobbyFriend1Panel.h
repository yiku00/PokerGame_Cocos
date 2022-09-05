#pragma once

#include "NxFramework.h"
#include "W_FriendInfo.pb.h"
#include "TockInvtationPanel.h"
#include "BTabButtonPanel.h"
#include "SmallButtonPanel.h"
#include "FriendCell.h"

#define GAME_FRIEND_CELL_MAX 100

enum TypeFriendPanel
{
	TYPE_SNS_FRIEND = 0,
	TYPE_GAME_FRIEND = 1
};

class LobbyFriend1Panel : public Panel, public Button::Listener, public CCTableViewDelegate, public CCTableViewDataSource, public Nx::Layer::Listener
{
	typedef vector<FriendCell*> FriendContainer;
public:
	LobbyFriend1Panel();
	virtual ~LobbyFriend1Panel();

public:
	virtual void onClicked(const string& name);
public:
	virtual void onLayerMessage(const string& msg);
public:
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view){};
	virtual void scrollViewDidZoom(CCScrollView* view){}

private:
	void InitPanel();
	void InitImage();
	void initButton();
    
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);
	void refreshTableView();


	void SetFriendlList();
	void ClearFriendlList();
	void ClearRequestList();
	void ClearRecommendlList();

	void ShowEmptyText(bool _visible);

	void SetButtonPause(bool _pause);
	void SetFriendPanelType(TypeFriendPanel _type);

	void setActivate(bool activate);

private:
	void drawTableView();
	void ShowFriendInfoPanel(int _index);		
	void refreshFriendState();	// 현재 친구 상태 표시한다.
public:
	bool mLoginProcess;
	int m_nSortType;	
	bool m_bTouchCancel;

	SmallButtonPanel* m_pSmallButton[2];

	FriendCell* m_ListCell[GAME_FRIEND_CELL_MAX];
	Widget* m_pListPhoto[GAME_FRIEND_CELL_MAX];

	int m_TapIndex;

	Nx::Label* m_FriendCount;
	Nx::Label* m_FriendMaxCount;

	TockInvtationPanel* m_pTockInvtationPanel;

	CCSize mCellSize;
	Nx::TableView* mTableView;
	FriendContainer mFriends;

	Nx::Label* mFriendTitleLabel;
	Nx::Label* mMaxFriendLabel;
	Nx::Label* mNowFriendLabel;


};
