/********************************************************************
	file name:	AttendPopupPanel.h
	
	purpose:	7일 출석창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "AttendContentPanel.h"

class AttendPopupPanel : public Panel, public Button::Listener
{
	typedef vector<AttendContentPanel*> ContentPanelContainer;
public:
	AttendPopupPanel();
	~AttendPopupPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);	
	virtual void onRefresh();

private:
	void initPanel();
	void initContentPanel();	//1일차 부터 6일차 까지 ..and 7일차.
	void initDesc();
	void refresh();

private:
	int getAttendDay();
	bool isBasicAttend();	//초보자 7일 출석일때

private:		
	Nx::Label* m7TitleLabel;
	Nx::Label* m7RewardLabel;
	SkelObject* m7RewardIcon;
	Button* mCloseBtn;
	ContentPanelContainer mContents;
	SkelObject* mPanelBg;
	SkelObject* mRewardIcon;
	SkelObject* mTitle;
	Widget* mUserPhoto;
};
