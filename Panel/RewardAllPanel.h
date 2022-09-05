/********************************************************************
file name:	RewardAllPanel.h

purpose:	전체 보상
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "SmallBtnPanel.h"
#include "W_RewardInfo.pb.h"

class RewardAllPanel : public Panel, public Button::Listener, public CCTableViewDelegate, public CCTableViewDataSource
{	
public:
	RewardAllPanel();
	virtual ~RewardAllPanel();

public:
	virtual void onClicked(const string& name);

public:
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);

	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view) {};
	virtual void scrollViewDidZoom(CCScrollView* view){}

public:
	void setRewardInfo(W_RewardInfo rewardInfo);	
	void setTitle(string title);
	void setDesc(string desc);
	void setItemDesc(string itemDesc);

private:
	void initPanel();	
	void drawTableView();
	void drawEachReward();
	void drawReward(int idx, int posIdx);		//총 몇개중 몇번째

private:	
	Nx::Label* mTitle;
	Nx::Label* mTitleUnder;
	Nx::Label* mDesc;
	SmallBtnPanel* mCancelBtn;
	W_RewardInfo mRewardInfo;
	Nx::TableView* mTableView;
	CCSize mCellSize;
	Nx::Label* mItemName;
	Nx::Label* mItemDesc;
};
