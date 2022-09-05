#pragma once

#include "NxFramework.h"

class LongButtonPanel : public Panel, public Button::Listener
{
public:
	LongButtonPanel();
	virtual ~LongButtonPanel();

	void InitPanel();
	void InitImage();
	void initButton();

	virtual void onClicked(const string& name);

	void SetLeftText(string _text);
	void SetRightText(string _text);

	void SetEnableButton(bool _enable);
public:
	Button* m_Button;
};
