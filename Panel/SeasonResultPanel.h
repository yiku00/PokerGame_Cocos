#pragma once
/********************************************************************
file name:	SeasonResultPanel.h

purpose:	SeasonResult 정보 보여주는 창
*********************************************************************/
#include "NxFramework.h"
#include "W_VipData.pb.h"
#include "W_TourResultInfo.pb.h"
#include "SmallButtonPanel.h"

class SeasonResultPanel : public Panel, public Button::Listener
{
public:
	SeasonResultPanel();
	virtual ~SeasonResultPanel();

public:
	virtual void onClicked(const string& name);
	virtual void onRefresh();
private:
	void initPanel();
	
	void refreshIcon();
	void refreshVipData();
	void refreshResult();
	void setVipBonus();
	void SetVipOption(W_VipData_VipOption _data);
private:
	Button* mCloseBtn;
	int mVipIndex;
	Nx::Label* mVipAmountLabel;
	
	Nx::Label* mNextSeasonDesc;
	W_TourResultInfo mResultInfo;
	
	SkelObject* mRankIcon;
	Nx::Label* mRankTitle;
	SmallButtonPanel* mConfirmBtn;
};
