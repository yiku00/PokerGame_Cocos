/********************************************************************
file name:	LimitedGoodContentPanel.h

purpose:	시즌 토너먼트 보상 리스트 안에 내용창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_LimitShopData.pb.h"

class LimitedGoodContentPanel : public Panel , public Button::Listener
{	
public:
	enum GOODS_TYPE
	{
		GRAND_NORMAL,	//무한정 쏜다.
		GRAND_RANDOM,	//동영상 
		LIMITED_JACKPOT_1,
		LIMITED_JACKPOT_2,
		LIMITED_MADE_1,
		LIMITED_MADE_2,
		LIMITED_ALLIN_1,
		LIMITED_ALLIN_2,
	};
	LimitedGoodContentPanel(GOODS_TYPE type);
	virtual ~LimitedGoodContentPanel();

public:
	virtual void onClicked(const string& buttonName);

public:
	void setLimitShopData(W_LimitShopData shopData);
private:
	void initPanel();		
	void setData();
	void setVisibleButton();
	void refreshPrice();

private:	
	Panel* mMainPanel;
	CCSize mContentSize;		
	Button* mSelectBtn;
	Nx::Label* mSelectBtnLabel;
	Nx::Label* mSelectBtnUnderLabel;
	Widget* mWindowBg;
	GOODS_TYPE mType;
	Panel* mButtonPanel;	
	W_LimitShopData mLimitShopData;
};
