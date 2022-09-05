#pragma once
/********************************************************************
file name:	VipInfoPanel.h

purpose:	VIP 정보 보여주는 창
*********************************************************************/
#include "NxFramework.h"
#include "W_VipData.pb.h"

class VipInfoPanel : public Panel, public Button::Listener
{
public:
	VipInfoPanel();
	virtual ~VipInfoPanel();

public:
	virtual void onClicked(const string& name);

private:
	void initPanel();
	void refreshVipData();
	void refreshBtnState();
	void setVipBonus();
	void SetVipOption(W_VipData_VipOption _data);

private:
	Button* mCloseBtn;
	Button* mLeftArrowBtn;
	Button* mRightArrowBtn;
	int mVipIndex;

	Nx::Label* mNowMyVipLabel;
	Nx::Label* mTitleLabel;			//vip 혜택
	Nx::Label* mTitleUnderLabel;	//vip 혜택
	Nx::Label* mSeasonTitleLabel;	//다음 시즌
	Nx::Label* mSeasonLabel;
	Nx::Label* mVipDescLabel;		//진행되는 시즌동안 얻은 랭킹은 시즌 종료 후 VIP 로 전환됩니다.
	Nx::Label* mVipAmountLabel;
	Nx::Label* mBenefitLabel;	// 혜택 ( vip %d 혜택)
	Nx::Label* mNextSeasonDescLabel;	// 다음시즌 동안 아래와 같은 효과가 적용됩니다.
	SkelObject* mRankIcon;


};
