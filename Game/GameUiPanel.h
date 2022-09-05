/********************************************************************
	file name:	GameUiPanel.h
	
	purpose:	실시간 갱신이 필요한 게임 UI 창
*********************************************************************/
#pragma once

class GameUiPanel : public Panel
{
public:
	GameUiPanel(const string& name = "") : Panel(name) {}

public:
	virtual void refresh() = 0;
};