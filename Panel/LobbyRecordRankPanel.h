/********************************************************************
file name:	LobbyRecordRankPanel.h

purpose:	기록실에서 랭킹 눌렀을때 나오는 창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "LobbyRecordRankContentPanel.h"
#include "W_ReputeRankRes.pb.h"
#include "SmallButtonPanel.h"

class LobbyRecordRankPanel : public Panel, public Button::Listener, public CCTableViewDelegate, public CCTableViewDataSource
{
	enum RANK_TYPE {
		RECORD_TOTAL_RANK,
		RECORD_FRIEND_RANK,
	};
public:
	LobbyRecordRankPanel();
	virtual ~LobbyRecordRankPanel();

public:
	virtual void onClicked(const string& buttonName);

public:
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view){};
	virtual void scrollViewDidZoom(CCScrollView* view){};

public:
	void setActivate(bool activate);
	void clearRankData();
	void recvTotalReputeRankRes(W_ReputeRankRes res);
	void recvFriendReputeRankRes(W_ReputeRankRes res);

private:
	void _init();	
	void drawTableView();
	void refresh();
	void refreshTabBtn();

private:
	CCSize mContentsSize;
	Panel* mMainPanel;

	Button* mTabTotalBtn;
	Nx::Label* mTabTotalBtnLabel;
	Nx::Label* mTabTotalBtnUnderLabel;
	
	Button* mTabFriendBtn;
	Nx::Label* mTabFriendBtnLabel;
	Nx::Label* mTabFriendBtnUnderLabel;

	RANK_TYPE mRankType;

	CCSize mCellSize;
	Nx::TableView* mTableView;
	LobbyRecordRankContentPanel* mMyRankPanel;
	//Total
	W_ReputeRankRes* mTotalRanks;
	W_ReputeRankRes* mFriendRanks;
	SmallButtonPanel* mRewardPanel;

	Nx::Label* mMyRankLabel;	
};