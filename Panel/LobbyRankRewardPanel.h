/********************************************************************
file name:	LobbyRankRewardPanel.h

purpose:	주간 랭킹 보상
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "LobbyRankRewardContentPanel.h"

typedef vector<LobbyRankRewardContentPanel*> RewardContentPanelContainer;

class LobbyRankRewardPanel : public Panel, public Button::Listener
{	
public:
	LobbyRankRewardPanel();
	virtual ~LobbyRankRewardPanel();

public:
	virtual void onClicked(const string& buttonName);
	virtual void update(float delta);
	virtual void onEnter() override;
private:
	void _init();	

private:
	Nx::Label* mLeftTimeLabel;
	Button* mCloseBtn;
	RewardContentPanelContainer mContents;
	Nx::Label* mTimeLimitLabel;

	Nx::Label* mTitle;
	Nx::Label* mTitleUnder;
};