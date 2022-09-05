/********************************************************************
	file name:	GoldRefillPopupPanel.h
	
	purpose:	좌절 금지 팝업
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "SmallButtonPanel.h"

class GoldRefillPopupPanel : public Panel, public Button::Listener
{	
public:
	GoldRefillPopupPanel();
	~GoldRefillPopupPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);	
	virtual void onRefresh();

public:
	void refreshData();

private:
	void initPanel();
	void refreshTodayRefill();
	
private:		
	SmallButtonPanel* mRefillGoPanel;

	SmallButtonPanel* mGoBigChancePanel;
	SmallButtonPanel* mFreeRefillPanel;
	SmallButtonPanel* mGoMiniPanel;

	Nx::Label* mRefillDesc;
	Button* mCloseBtn;
};
