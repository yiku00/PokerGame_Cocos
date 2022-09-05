/********************************************************************
	file name:	TournamentResultPanel.h
	
	purpose:	TournamentResultPanel 토너먼트 결과창 1등 ~ 4등
*********************************************************************/
#pragma once
#include "NxFramework.h"

class TournamentResultPanel : public Panel
{
public:
	TournamentResultPanel(int rank);
	~TournamentResultPanel();

private:
	void initPanel();
	void initThophyPanel();	//1,2,3등까지는 트로피 보여준다.
	void initEtcPanel();	//기타등등 표현

private:	
	int mRank;
	SkelObject* mBg;
};