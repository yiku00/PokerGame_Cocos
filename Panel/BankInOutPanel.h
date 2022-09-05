#pragma once
/********************************************************************
file name:	BankInOutPanel.h

purpose:	BankInOutPanel 결과를 보여주는 창
*********************************************************************/
#include "NxFramework.h"
#include "SmallBtnPanel.h"

class BankInOutPanel : public Panel, public Button::Listener
{
public:
	BankInOutPanel(bool isInput , string desc);
	virtual ~BankInOutPanel();

public:
	virtual void onClicked(const string& name);	
private:
	void initPanel();		
	bool isInputType();
	
private:
	SmallBtnPanel* mCancelBtn;
	Nx::Label* mTitle;
	Nx::Label* mTitleUnder;
	Nx::Label* mDesc;	
	bool mIsInput;
	string mDescStr;
};
