/********************************************************************
file name:	RecordPokerStateContentPanel.h

purpose:	우승 , 준우승 , 쳠여횟수 , 횟수 보여주는 내용창
*********************************************************************/
#pragma once
#include "NxFramework.h"

class RecordPokerStateContentPanel : public Panel
{
public:
	RecordPokerStateContentPanel();
	virtual ~RecordPokerStateContentPanel();

public:
	void setData(int win, int halfWin, int playoff);
private:
	void initPanel();
private:	
	
	Panel* mMainPanel;
	CCSize mContentSize;
	Nx::Label* mVictoryLabel;		//우승
	Nx::Label* mHalfVictoryLabel;	//준우승
	Nx::Label* mPlayoffLabel;		//예선 통과		
	Nx::Label* mPlayoffTitleLabel;
};
