/********************************************************************
	file name:	AnnouncePanel.h
	
	purpose:	AnnouncePanel 공지 사항 보여주는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"

class AnnouncePanel : public Panel
{
public:
	AnnouncePanel();
	~AnnouncePanel();
public:
	void setDesc(string desc);

private:
	void initPanel();
	void removeAction();
	void closePanel();
private:
	Nx::Label* mDesc;
};