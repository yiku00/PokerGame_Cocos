/********************************************************************
filename: 	MemberShipListPanel.h 

purpose:	�����Կ��� �ɹ��� ������� â
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
	void refreshBtnState();	//��Ȳ�� ���� �ǹ� , ��� ��� �ִ��� Ȯ��

private:
	CCSize mContentsSize;	
	Panel* mMainPanel;	
	MemberShipContentPanel* mSilverPanel;
	MemberShipContentPanel* mGoldPanel;
};

