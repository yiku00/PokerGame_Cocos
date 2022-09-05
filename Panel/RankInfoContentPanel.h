/********************************************************************
file name:	RankInfoContentPanel.h

purpose:	랭킹 정보 보여주는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"

class RankInfoContentPanel : public Panel, public Button::Listener
{
public:
	enum RANK_INFO_TYPE
	{
		RANK_INFO_NO_GAUGE,
		MEMBER_GOLD,
	};

public:
	RankInfoContentPanel(RANK_INFO_TYPE type);
	virtual ~RankInfoContentPanel();

public:
	virtual void onClicked(const string& name);

private:
	void initPanel();
public:
	void refresh();

private:
	RANK_INFO_TYPE mRankType;
	
	Nx::Label* mRankTitleLabel;
	Nx::Label* mRankLabel;	//현재 상위 몇% 인가
	Nx::Label* mMyRankLabel;	//내 랭크수
	Nx::Label* mMaxRankLabel;	//맥스 랭크수
	Widget* mGaugeBg;
	Widget* mGaugeBar;
	SkelObject* mRankIcon;

	Button* mMoveBtn;
	Nx::Label* mMovebtnLabel;
	Nx::Label* mMovebtnUnderLabel;
};
