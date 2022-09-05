#pragma once
/********************************************************************
file name:	BuyMemberNoticePanel.h

purpose:	BuyMemberNoticePanel 멤버쉽을 구매해야 알림창
*********************************************************************/
#include "NxFramework.h"
#include "SmallButtonPanel.h"

class BuyMemberNoticePanel : public Panel, public Button::Listener
{
public:
	BuyMemberNoticePanel();
	virtual ~BuyMemberNoticePanel();

public:
	virtual void onClicked(const string& name);	
private:
	void initPanel();		

private:
	SmallButtonPanel* mMemberBtn;		//맴버쉽 보러가기
	Button* mCloseBtn;
};
