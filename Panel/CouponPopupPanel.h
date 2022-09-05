/********************************************************************
	file name:	CouponPopupPanel.h
	
	purpose:	쿠폰  팝업창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_LetterInfo.pb.h"
//#include "TypeDefine.pb.h"

class CouponPopupPanel : public Panel, public Button::Listener,public TextField::Listener
{
public:
	CouponPopupPanel();
	~CouponPopupPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);	
	//TextField::Listener
	virtual void onDetached();
	
private:
	void initPanel();	
	void sendW_CouponReq(string coupon);
	void recvW_CouponRes(HttpMessage* msg);
private:	
	Button* mCloseBtn;
	Nx::Label* mTitle;
	Button* mSendBtn;
	Button* mAttachBtn;

	Nx::Label* mButtonNameLabel;
	Nx::Label* mButtonNameUnderLabel;


};
