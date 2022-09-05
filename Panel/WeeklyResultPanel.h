#pragma once
/********************************************************************
file name:	WeeklyResultPanel.h

purpose:	WeeklyResultPanel 주중 보여주는 창
*********************************************************************/
#include "NxFramework.h"
#include "SmallButtonPanel.h"
#include "W_TourWeeklyRewardInfo.pb.h"

class WeeklyResultPanel : public Panel, public Button::Listener
{
public:
	WeeklyResultPanel();
	virtual ~WeeklyResultPanel();

public:
	virtual void onClicked(const string& name);
	virtual void onRefresh();
private:
	void initPanel();		
	void refreshResult();
	
private:
	
	SmallButtonPanel* mConfirmBtn;

	Nx::Label* mTitle;
	Nx::Label* mTitleUnder;

	Nx::Label* mDesc;
	//주간 달성 등수
	Nx::Label* mRankTitle;
	
	Nx::Label* mRank;
	
	//보상
	Nx::Label* mRewardTitle;
	
	Nx::Label* mRewardAmount;	

	W_TourWeeklyRewardInfo mWeeklyRewardInfo;
};
