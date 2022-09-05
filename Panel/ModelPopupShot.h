#pragma once
#include "NxFramework.h"
#include "W_LetterInfo.pb.h"

class ModelPopupShot : public Panel, public Button::Listener
{
public:
	ModelPopupShot(int tIdx,int idx);
	~ModelPopupShot();

public:
	virtual void onClicked(const string& name);	

private:
	void initPanel();	
	int mIdx;
	int tIdx;
};
