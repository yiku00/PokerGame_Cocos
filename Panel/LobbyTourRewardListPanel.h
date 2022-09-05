/********************************************************************
file name:	LobbyTourRewardListPanel.h

purpose:	시즌 토너먼트 보상 리스트창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_TourStepInfo.pb.h"
#include "LobbyTourRewardContentPanel.h"

class LobbyTourRewardListPanel : public Panel
{
	typedef vector<LobbyTourRewardContentPanel*> PanelContainer;
public:
	LobbyTourRewardListPanel();
	virtual ~LobbyTourRewardListPanel();

public:
	void setTourStepInfo(W_TourStepInfo tourStepInfo);

private:
	void InitPanel();	

private:	
	Nx::Label* mGameName;
	Nx::Label* mSeedMoney;
	Nx::Label* mBasicMoney;

	LobbyTourRewardContentPanel* mReward1;
	LobbyTourRewardContentPanel* mReward2;
	LobbyTourRewardContentPanel* mReward3;
	PanelContainer mRewards;
	
};
