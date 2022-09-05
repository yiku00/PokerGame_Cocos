/********************************************************************
	file name:	InGameLoadingPanel.h
	
	purpose:	게임 안에서 로딩할때 창 ( 카드 설명부분)
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "LoadingDef.h"

class InGameLoadingPanel : public Panel , SuperObject::Listener
{
public:
	InGameLoadingPanel(LoadingType type);
	virtual ~InGameLoadingPanel();

public:
	virtual void onAnimationEnded(const string& ani){};
public:
	void setGaugeRatio(float ratio);

private:

private:
	Widget* mGauseBar;	
	SuperObject* mProgressAni;
	float mStartPositionX;
	LoadingType mType;
};
