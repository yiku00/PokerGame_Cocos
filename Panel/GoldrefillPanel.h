/********************************************************************
filename: 	GoldrefillPanel.h

purpose:	돈이 없을때 돈 리필하는 방법 선택하는 창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "LongButtonPanel.h"

class GoldrefillPanel : public Panel, public Button::Listener
{
public:
	GoldrefillPanel();
	virtual ~GoldrefillPanel();

	void InitPanel();
	void InitImage();
	void initButton();

	virtual void onClicked(const string& name);

	void SetButtonStyle();
public:
	Button* m_cancelBtn;
	LongButtonPanel* m_ButtonPanel[5];
};
