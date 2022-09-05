/********************************************************************
file name:	LobbyRecordTourmentPanel.h

purpose:	기록실에서 챔피언쉽 눌렀을때 나오는 창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "RankInfoContentPanel.h"
#include "LobbyLatelybarContentPanel.h"
#include "RecordPokerStateContentPanel.h"

class LobbyRecordTourmentPanel : public Panel, public Button::Listener
{
public:
	LobbyRecordTourmentPanel();
	virtual ~LobbyRecordTourmentPanel();

public:
	virtual void onClicked(const string& buttonName);

public:
	void setActivate(bool activate);

private:
	void _init();	

private:
	CCSize mContentsSize;
	Panel* mMainPanel;
	RankInfoContentPanel* mRankInfoPanel;

	RecordPokerStateContentPanel* mWinInfo_1;
	RecordPokerStateContentPanel* mWinInfo_2;
	RecordPokerStateContentPanel* mWinInfo_3;

	LobbyLatelybarContentPanel* mContentPanel_1;
	LobbyLatelybarContentPanel* mContentPanel_2;
	LobbyLatelybarContentPanel* mContentPanel_3;
};