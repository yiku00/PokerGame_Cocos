/********************************************************************
file name:	LimitedGoodPanel.h

purpose:	한정 상품 구매 표시창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "LimitedGoodContentPanel.h"

class LimitedGoodPanel : public Panel , public Button::Listener , public Nx::Layer::Listener
{	
	typedef vector <W_LimitShopData> DataContainer;
public:
	enum LIMITED_TYPE {
		LIMITED_JACKPOT = 1,	//잭팟 타입
		LIMITED_MADE = 2,		//메이드 타입
		ALLIN = 3,				//올인
	};
	LimitedGoodPanel(LIMITED_TYPE type);
	virtual ~LimitedGoodPanel();

public:
	virtual bool handling(STCMD &stCmd);
	virtual void onLayerMessage(const string& msg);
	virtual void onRefresh();
public:
	virtual void onClicked(const string& name);
	virtual void update(float delta);
	virtual void onEnter() override;
private:
	void initPanel();	
	void refreshTitle();
	void refreshTImeDesc();

	void initShopData();

private:
	void sendPayReserveReq(int cashId);
	void recvWPayReserveRes(HttpMessage* msg);
	void sendW_PayReq(string tID, string txId, string receipt);
	void recvW_PayRes(HttpMessage* msg);

private:	
	Nx::Label* mLimitedTimeLabel;	
	Nx::Label* mLimitedTitleLabel;
	Nx::Label* mLimitedTitleUnderLabel;

	Nx::Label* mLimitedDescLabel;
	LimitedGoodContentPanel* mLeftPanel;
	LimitedGoodContentPanel* mRightPanel;
	Button*  mCloseBtn;
	LIMITED_TYPE mLimitedType;
	int mBuyCashId;

	DataContainer mShopDatas;
	string mGoogleTid;
};
