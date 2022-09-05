/********************************************************************
	file name:	RefillMovieContentPanel.h
	
	purpose:	무료 충전소 안에 내용
*********************************************************************/
#pragma once
#include "NxFramework.h"

class RefillMovieContentPanel : public Panel, public Button::Listener
{
public:
	RefillMovieContentPanel(int index);
	~RefillMovieContentPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);	

public:
	void addClearPanel();
	void addReward();

private:
	void initPanel();
	
private:	
	int mIndex;
	CCSize mContentSize;
	Panel* mClearPanel;
	Panel* mMainPanel;
	Nx::Label* mRewardLabel;	//보상
	Nx::Label* mPeriodLabel;	//몇회차
	SkelObject* mTable;
};
