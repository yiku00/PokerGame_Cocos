/********************************************************************
filename: 	MemberShipListPanel.h 

purpose:	보관함에서 맴버쉽 골랐을때 창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "MemberShipContentPanel.h"

class MemberShipListPanel : public Panel, public Button::Listener , public Nx::Layer::Listener
{
public:	
	MemberShipListPanel();
	~MemberShipListPanel();

public:
	virtual void onClicked(const string& buttonName);
	virtual void onLayerMessage(const string& msg);

public:
	void setActivate(bool activate);	

private:	
	void initPanel();	
	void refreshBtnState();	//상황에 따라 실버 , 골드 살수 있는지 확인

private:
	CCSize mContentsSize;	
	Panel* mMainPanel;	
	MemberShipContentPanel* mSilverPanel;
	MemberShipContentPanel* mGoldPanel;
};

