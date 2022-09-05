/********************************************************************
file name:	LobbyRecordSurvivalPanel.h

purpose:	기록실에서  데스매치  눌렀을때 창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "RankInfoContentPanel.h"
#include "LobbyLatelybarContentPanel.h"


class LobbyRecordSurvivalPanel : public Panel, public Button::Listener
{
public:
	LobbyRecordSurvivalPanel();
	virtual ~LobbyRecordSurvivalPanel();

public:
	virtual void onClicked(const string& buttonName);

public:
	void setActivate(bool activate);

private:
	void _init();
	
private:
	CCSize mContentsSize;
	Panel* mMainPanel;
	SkelObject* Trophy;
	RankInfoContentPanel* mRankInfoPanel;

	Nx::Label* mVictoryAmountLabel;
	Nx::Label* mHalfVictoryAmountLabel;
	Nx::Label* mMoneyInAmountLabel;

	Nx::Label* mBestGetMoneyLabel;

	LobbyLatelybarContentPanel* mContentPanel_1;
	LobbyLatelybarContentPanel* mContentPanel_2;
	LobbyLatelybarContentPanel* mContentPanel_3;
};