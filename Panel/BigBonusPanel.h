/********************************************************************
file name:	BigBonusPanel.h

purpose:	30분 빅 보너스
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "LimitedGoodContentPanel.h"

class BigBonusPanel : public Panel, public Button::Listener, public Nx::Layer::Listener
{	
public:
	BigBonusPanel();
	virtual ~BigBonusPanel();

public:
	virtual void onClicked(const string& name);
	virtual void onLayerMessage(const string& msg);
	virtual bool handling(STCMD &stCmd);

private:
	void initPanel();	
	void sendReward();

private:	
	LimitedGoodContentPanel* mLeftPanel;
	LimitedGoodContentPanel* mRightPanel;
	Button*  mCloseBtn;

	Nx::Label* mTitleUnder;
	Nx::Label* mTitle;
	Nx::Label* mTopDesc;
	Nx::Label* mBottomDesc;
};
