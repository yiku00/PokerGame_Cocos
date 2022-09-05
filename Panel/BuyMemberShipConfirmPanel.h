/********************************************************************
file name:	BuyMemberShipConfirmPanel.h

purpose:	멤버쉽 구매 확인창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "SmallButtonPanel.h"

class BuyMemberShipConfirmPanel : public Panel, public Button::Listener
{	
public:
	BuyMemberShipConfirmPanel();
	BuyMemberShipConfirmPanel(string okMessage);
	virtual ~BuyMemberShipConfirmPanel();

public:
	virtual void onClicked(const string& name);

public:
	void setMemberConfirm(int memberShipId);
	
private:
	void initPanel();	
	void confirmPanel();	//맴버쉽 사시겠습니까? 메시지

private:	
	Nx::Label* mTitle;
	Nx::Label* mTitleUnder;

	Button* mCancelBtn;

	Widget* mMemberShipImg;	// 멤버쉽 이미지
	Nx::Label* mItemName;		//아이템 이름
	
	CCLabelBMFont* mTerm;
	
	SmallButtonPanel* mBuyBtn;
	string mEventStr;	//이벤트로 보낼명	

};
