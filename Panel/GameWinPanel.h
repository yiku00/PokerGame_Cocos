/********************************************************************
	file name:	GameWinPanel.h
	
	purpose:	이겼을때 레이어 때문에 따루 붙이는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"

class GameWinPanel : public Panel
{
public:
	enum PANEL_KINDS{
		PANEL_MY_RESULT,
		PANEL_ENEMY_RESULT,
		PANEL_ENEMY_HOLDEM_RESULT,
	};
	GameWinPanel(PANEL_KINDS type);
	~GameWinPanel();

public: 
	void setResult(string str);
	SkelObject* getWinSkel();

private:
	void initPanel();

private:
	Panel* mMainPanel;
	Nx::Label* mResultLabel;
	SkelObject* mWinImg;
	PANEL_KINDS mKinds;
};