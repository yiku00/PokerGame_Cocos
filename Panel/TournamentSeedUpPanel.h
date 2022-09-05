/********************************************************************
	file name:	TournamentSeedUpPanel.h
	
	purpose:	TournamentSeedUpPanel 토너먼트 시드 관련창
*********************************************************************/
#pragma once
#include "NxFramework.h"

class TournamentSeedUpPanel : public Panel
{
public:
	TournamentSeedUpPanel(int64 seedMoney, bool isMax);
	TournamentSeedUpPanel(string ani , string desc);

	~TournamentSeedUpPanel();

private:
	void initPanel();
	void closePanel();
	void addActionClose();

private:	
	SkelObject* mIcon;
	SkelObject* mBg;
	Nx::Label* mDesc;
};