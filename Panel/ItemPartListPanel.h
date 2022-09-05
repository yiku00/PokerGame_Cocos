/********************************************************************
filename: 	ItemPartListPanel.h 

purpose:	�����Կ��� ������ ������� â ( Ƽ�� �����θ� �����ش�.
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
	void initContentPanel();	//�� ����â ����.
	void makeTickerId();	//ticket id�� �����.
	void moveTourment();
	int getSumTargetIdx(int FromIdx);
	string getExchangefee(int FromIdx);
private:
	CCSize mContentsSize;
	Panel* mMainPanel;	
	TickerIdContainer mIds;
	ContentConatainer mContents;
};

