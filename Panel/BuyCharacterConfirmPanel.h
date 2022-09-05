/********************************************************************
file name:	BuyConfirmPanel.h

purpose:	물건을 살껀지 물어보는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "SmallButtonPanel.h"

class BuyCharacterConfirmPanel : public Panel, public Button::Listener
{	
public:
	BuyCharacterConfirmPanel();
	virtual ~BuyCharacterConfirmPanel();

public:
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);

public:
	void setCharacterConfirm(int characterId);
	
private:
	void initPanel();	
	bool isCharacterMoneyType();	//이 캐릭터는 돈으로 사는 캐릭이다.
	
	void sendPayReserveReq(int cashId);
	void recvWPayReserveRes(HttpMessage* msg);
	void sendW_PayReq(string tID, string txId, string receipt);
	void recvW_PayRes(HttpMessage* msg);

private:	
	Nx::Label* mTitle;
	Nx::Label* mTitleUnder;
	
	Button* mCancelBtn;	
	Widget* mCharacterImg;
	Nx::Label* mItemName;		//캐릭터 이름
	
	CCLabelBMFont* mTerm;
	SmallButtonPanel* mBuyBtn;
	string mEventStr;	//이벤트로 보낼명	
	int mCharacterShopId;
	int mCharacterId;
	int mBuyCashId;
	string mGoogleTid;
};
