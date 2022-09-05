/********************************************************************
file name:	LobbyTourRewardContentPanel.h

purpose:	내뇽 뿌려주는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"

class LobbyTourRewardContentPanel : public Panel
{

public:
	LobbyTourRewardContentPanel();
	virtual ~LobbyTourRewardContentPanel();

public:
	void setRewardData(int grade, int64 paymoney, int trophy);

private:
	void InitPanel();


private:	
	Nx::Label* mGrade;	//1등
	Nx::Label* mGradeUnder;

	Nx::Label* mPayMoney;
	Nx::Label* mTrophy;

	SkelObject* mWindow;
};
