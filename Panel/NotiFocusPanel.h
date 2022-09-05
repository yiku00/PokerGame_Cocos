/********************************************************************
file name:	NotiFocusPanel.h

purpose:	노티가 있을때 설명을 보여주는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "NotiData.pb.h"
#include "NotiFocusTalkContentPanel.h"
#include "NotiTalkListPanel.h"

class NotiFocusPanel : public Panel
{
public:
	NotiFocusPanel(NotiData_eNotiType type);
	virtual ~NotiFocusPanel();

public: // CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnter() override;

public:
	void setHalfMoney(string halfMoneyStr);
	void setQuarterMoney(string quarterMoneyStr);
	void setMaxMoney(string maxMoneyStr);
	bool isShowMoneyType();	//돈 보여주는 타입인가
	void setSubList();
	void setBettingCall();

private:
	void initPanel();
	void setFocus();	//lobbyui 나 다른곳에 noti ani 를 뿌린다.
	void drawText();
	void clearUINoti();
private:	
	NotiData_eNotiType mType;
	NotiFocusTalkContentPanel* mFocusTalkPanel;
	SkelObject* mFocusBg;
	NotiTalkListPanel* mListPanel;
	NotiTalkListPanel* mListSubPanel;
};
