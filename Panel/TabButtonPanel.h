#pragma once

#include "NxFramework.h"

class TabButtonPanel : public Panel, public Button::Listener
{
public:
	TabButtonPanel();
	virtual ~TabButtonPanel();

	void InitPanel();
	void InitImage();
	void initButton();

	virtual void onClicked(const string& name);

	void SetButtonListener(Button::Listener* _ptr);
	void SetButtonText(string _text);

	void SetBtnOnOff(bool _on);
public:
	Button* m_Button;

	Nx::Label* m_OnText;
	Nx::Label* m_OffText;

};
