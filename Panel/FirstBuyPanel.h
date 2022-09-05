#pragma once
/********************************************************************
file name:	FirstBuyPanel.h

purpose:	첫 구매창
*********************************************************************/
#include "NxFramework.h"
#include "W_LimitShopData.pb.h"

class FirstBuyPanel : public Panel, public Button::Listener
{
public:
	FirstBuyPanel();
	virtual ~FirstBuyPanel();

public:
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);

private:
	void initPanel();
	void sendPayReserveReq(int cashId);
	void recvWPayReserveRes(HttpMessage* msg);
	void sendW_PayReq(string tID, string txId, string receipt);
	void recvW_PayRes(HttpMessage* msg);

private:
	W_LimitShopData mLimitShopData;
	int mBuyCashId;
	Button* mCloseBtn;	
	Button* mSelectBtn;
	Panel* mButtonPanel;
	Nx::Label* mSelectBtnLabel;
	Nx::Label* mSelectBtnUnderLabel;
	string mGoogleTid;
};
