/********************************************************************
	file name:	AttendContentPanel.h
	
	purpose:	출석 보상창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_RewardInfo.pb.h"

class AttendContentPanel : public Panel
{
public:
	AttendContentPanel();
	~AttendContentPanel();

private:
	void initPanel();

public:
	void setRewardData(int day, W_RewardInfo_RewardSet rewardSet , int nowDay);

private:		
	Panel* mMainPanel;

	Nx::Label* mDayTitleLabel;
	Nx::Label* mRewardLabel;
	SkelObject* mPanelBg;
	SkelObject* mRewardIcon;
	Widget* mUserPhoto;
};
