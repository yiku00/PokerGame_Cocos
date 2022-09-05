/********************************************************************
	file name:	TournamentWaitingPanel.h
	
	purpose:	TournamentWaitingPanel 잠시만 기다려주세요
*********************************************************************/
#pragma once
#include "NxFramework.h"

class TournamentWaitingPanel : public Panel
{
public:
	TournamentWaitingPanel();
	~TournamentWaitingPanel();

public:
	void closePanel(bool isAni = false);
	//void closePanel(int LastRound, bool isAni = false);
	void setDesc(string desc);
private:
	void initPanel();
	void popPanel();

private:	
	SkelObject* mBg;
	SkelObject* mIcon;
	Nx::Label* mDesc;
};