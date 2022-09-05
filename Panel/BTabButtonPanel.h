#pragma once

#include "NxFramework.h"

#define COLOR_TAP_ON	ccc3(69.f, 47.f, 27.f)
#define COLOR_TAP_OFF	ccc3(158.f, 113.f, 72.f)

class BTabButtonPanel : public Panel, public Button::Listener
{
public:
	BTabButtonPanel();
	virtual ~BTabButtonPanel();

	void InitPanel();
	void InitImage();
	void initButton();

	virtual void onClicked(const string& name);

	void SetButtonListener(Button::Listener* _ptr);
public:
	Button* m_LeftButton;
	Button* m_RightButton;

	Nx::Label* m_LeftText;
	Nx::Label* m_RightText;

};
