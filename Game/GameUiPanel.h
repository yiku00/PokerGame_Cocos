/********************************************************************
	file name:	GameUiPanel.h
	
	purpose:	�ǽð� ������ �ʿ��� ���� UI â
*********************************************************************/
#pragma once

class GameUiPanel : public Panel
{
public:
	GameUiPanel(const string& name = "") : Panel(name) {}

public:
	virtual void refresh() = 0;
};