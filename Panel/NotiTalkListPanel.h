/********************************************************************
file name:	NotiTalkListPanel.h

purpose:	노티 리스트창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "NotiData.pb.h"

class NotiTalkListPanel : public Panel
{
public:
	enum TALK_LIST_TYPE {
		TALK_POKER_BTN_LIST,
		TALK_HIGHLOW_BTN_LIST,
		TALK_BADUKI_BTN_LIST,
		TALK_HOLDEM_BTN_LIST,
		TALK_HOLDEM_COMMUNITY,
	};

public:
	NotiTalkListPanel(TALK_LIST_TYPE type);
	virtual ~NotiTalkListPanel();

public:
	void setHalfMoney(string halfMoneyStr);
	void setQuarterMoney(string quarterMoneyStr);
	void setMaxMoney(string maxMoneyStr);
	void setBettingCall();
private:
	void initPanel();
	void useBigBtnDesc(bool visible);

private:	
	TALK_LIST_TYPE mType;
	Panel* mMainPanel;
};
