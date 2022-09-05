/********************************************************************
file name:	LobbyFriendRequestPanel.h

purpose:	친구 요청창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "IntableSearchPanel.h"
#include "FriendCellMiddle.h"
#include "SmallButtonPanel.h"

class LobbyFriendRequestPanel : public Panel, public Button::Listener, public CCTableViewDataSource, public CCTableViewDelegate , public Nx::Layer::Listener
{
	typedef vector<FriendCellMiddle*> FriendCellContainer;
public:
	LobbyFriendRequestPanel();
	virtual ~LobbyFriendRequestPanel();

public:
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);

	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view){}
	virtual void scrollViewDidZoom(CCScrollView* view){}

public:
	virtual void onClicked(const string& buttonName);
	virtual void onLayerMessage(const string& msg);

public:
	void refreshTableView();
	void refreshPhoto(int index);

private:
	void initPanel();
	void drawTableView();

private:
	Nx::TableView* mTableView;
	CCSize mCellSize;
	Panel* mMainPanel;
	CCSize mContentSize;
	IntableSearchPanel* m_TextFieldPanel;
	TextField* m_pFriendName;

	SmallButtonPanel* m_smallButton[2];
	FriendCellContainer mFriends;
	Nx::Label* mTitleLabel;
	Nx::Label* mTitleUnderLabel;
};