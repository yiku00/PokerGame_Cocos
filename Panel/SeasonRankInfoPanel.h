/********************************************************************
filename: 	SeasonRankInfoPanel.h

purpose:	시즌 랭킹 정보창
*********************************************************************/
#pragma once

#include "NxFramework.h"

class SeasonRankInfoPanel : public Panel, public Button::Listener
{
public:
	SeasonRankInfoPanel();
	virtual ~SeasonRankInfoPanel();
// Button::Listener
public:
	virtual void onClicked(const string& name);    
private:
	void initPanel();
	void initData();
	int getReputeAmount(int repute);
	
private:
	Button* mCloseBtn;
	Button* mVipInfoBtn;
	Nx::Label* mTitle;
};
