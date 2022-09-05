/********************************************************************
file name:	NotiFocusTalkContentPanel.h

purpose:	노티창에 뜨는 말창..
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "NotiData.pb.h"

class NotiFocusTalkContentPanel : public Panel
{
public:
	NotiFocusTalkContentPanel();
	virtual ~NotiFocusTalkContentPanel();

public:
	void setTalkStr(NotiData_eNotiType notiType);

private:
	void initPanel();
	
	
private:	
	Panel* mMainPanel;	
	Nx::Label* mTalkLabel;
	SkelObject* mWindowBg;
};
