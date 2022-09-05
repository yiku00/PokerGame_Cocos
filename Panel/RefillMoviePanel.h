/********************************************************************
	file name:	RefillMoviePanel.h
	
	purpose:	동영상 충전 
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "RefillMovieContentPanel.h"

class RefillMoviePanel : public Panel, public Button::Listener
{
	typedef vector<RefillMovieContentPanel*> ContentPanelContainer;
public:
	RefillMoviePanel();
	~RefillMoviePanel();

public: // Button::Listener
	virtual void onClicked(const string& name);	
	virtual bool handling(STCMD &stCmd);

public:
	void addReward();

private:
	void refreshData();
	void initPanel();
	bool isPossibleView();
	void sendReward();

private:		
	ContentPanelContainer mContentPanels;
	Nx::Label* mNowPlayLabel;
	Nx::Label* mMaxPlayLabel;
	Button* mPlayBtn;
	Button* mCloseBtn;
	Nx::Label* mTitleLabel;
	Nx::Label* mTitleUnderLabel;

	Nx::Label* mMovieDescLabel;
	Nx::Label* mMovieDescUnderLabel;

	Nx::Label* mPlayBtnLabel;
	Nx::Label* mPlayBtnUnderLabel;
};
