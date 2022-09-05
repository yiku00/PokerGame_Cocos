/********************************************************************
file name:	LobbyRankRewardContentPanel.h

purpose:	주간 랭킹 보상 선택창 
*********************************************************************/
#pragma once

#include "NxFramework.h"

class LobbyRankRewardContentPanel : public Panel
{	
public:
	LobbyRankRewardContentPanel(int idx);
	virtual ~LobbyRankRewardContentPanel();
		
private:
	void _init();	
	void displayRankData();

private:
	int mDataIndex;
	CCSize mContentSize;
	Panel* mMainPanel;

	SkelObject* mRewardIcon;
	SkelObject* mRankIcon;

	Nx::Label* mClassNumberLabel;		//5등 ~ 6등
	Nx::Label* mClassNumberUnderLabel;
	Nx::Label* mBonusLabel;				//9000억골드
	Nx::Label* mBonusUnderLabel;
};