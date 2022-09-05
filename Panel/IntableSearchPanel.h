#pragma once

#include "NxFramework.h"
#include "SlotButtonPanel.h"

class IntableSearchPanel : public Panel, public Button::Listener
{
public:
	IntableSearchPanel();
	virtual ~IntableSearchPanel();

	void InitPanel();
	void InitImage();
	void initButton();

	virtual void onClicked(const string& name);

public:
	Button* m_inputTouch;
	Button* m_searchBtn;

	TextField* m_TextField;
};
