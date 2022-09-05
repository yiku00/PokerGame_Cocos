/********************************************************************
filename: 	ItemPartListPanel.h 

purpose:	보관함에서 아이템 골랐을때 창 ( 티켓 종류로만 보여준다.
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "TicketContentPanel.h"

class ItemPartListPanel : public Panel, public Nx::Layer::Listener
{
	typedef vector<int> TickerIdContainer;
	typedef vector<TicketContentPanel*> ContentConatainer;
public:	
	ItemPartListPanel();
	~ItemPartListPanel();

public:
	virtual void onLayerMessage(const string& msg);

public:
	void setActivate(bool activate);
	void refreshData();

private:
	void initPanel();
	void initContentPanel();	//각 내용창 띄운다.
	void makeTickerId();	//ticket id를 만든다.
	void moveTourment();
	int getSumTargetIdx(int FromIdx);
	string getExchangefee(int FromIdx);
private:
	CCSize mContentsSize;
	Panel* mMainPanel;	
	TickerIdContainer mIds;
	ContentConatainer mContents;
};

