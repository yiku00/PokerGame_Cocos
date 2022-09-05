/********************************************************************
	filename: 	RetryPanel.h
	
	purpose:	
*********************************************************************/
#pragma once

#include "NxFramework.h"


class RetryPanel : public Panel, public Button::Listener
{
public:
	RetryPanel();
	virtual ~RetryPanel();

public: // Button::Listener
	virtual void onClicked(const string& buttonName) override;
};