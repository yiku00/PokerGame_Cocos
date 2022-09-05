/********************************************************************
file name:	LobbyRecordWorldTourPanel.h

purpose:	기록실 랭킹 눌렀을때 월드 투어
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "TabButtonPanel.h"
#include "HandsHistoryContentPanel.h"

class LobbyRecordWorldTourPanel : public Panel, public Button::Listener, public CCTableViewDelegate, public CCTableViewDataSource
{
	enum DISPLAY_HISTORY_TYPE{
		DISPLAY_HISTORY_SEVENPOKER,
		DISPLAY_HISTORY_HIGHTLOW,
		DISPLAY_HISTORY_BADDUGI,
		DISPLAY_HISTORY_HOLDEMR,
		DISPLAY_HISTORY_END,
	};
public:
	LobbyRecordWorldTourPanel();
	virtual ~LobbyRecordWorldTourPanel();

public:
	virtual void onClicked(const string& buttonName);

public:
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view){};
	virtual void scrollViewDidZoom(CCScrollView* view){};

public:
	void setActivate(bool activate);

private:
	void _init();	
	void initHistyroPanel();
	void drawTableView();

	void refreshLikeGamePercent();	//게임 선호 게임 관련 %
	void refreshToday();	//오늘 전적
	void refreshTotal();	//누적 전적
	void refreshHistoryPanel();

private:
	CCSize mContentsSize;
	Panel* mMainPanel;
	CCSize mCellSize;
	Nx::TableView* mTableView;

	Panel* mDisplayPanel;
	//선호게임
	Nx::Label* mLikeGameSevenPokerPercentLabel;
	Nx::Label* mLikeGameHighLowPercentLabel;
	Nx::Label* mLikeGameBaddugiPercentLabel;
	Nx::Label* mLikeGameHoldemPercentLabel;
	//오늘의 전적
	Nx::Label* mTodayStateLabel;
	Nx::Label* mBestGetMoneyLabel;
	//누적 전적
	Nx::Label* mAccumulateStateLabel;
	Nx::Label* mAccumulateBestGetMoneyLabel;
	Nx::Label* mAccumulateAllinLabel;
	//족보 전적
	
	HandsHistoryContentPanel* mSevenPokerHistoryPanel;
	HandsHistoryContentPanel* mHighLowHistoryPanel;
	HandsHistoryContentPanel* mBadugiHistoryPanel;
	HandsHistoryContentPanel* mHoldemHistoryPanel;

	DISPLAY_HISTORY_TYPE mHistroyType;

	Button* mLeftBtn;
	Button* mRightBtn;

	Widget* mPokerGaugeBar;
	Widget* mHighLowGaugeBar;
	Widget* mBadukiGaugeBar;
	Widget* mHoldemGaugeBar;

	Nx::Label* mFavorGameTitle;		//선호게임
	Nx::Label* mFavorGameUnderTitle;
	Nx::Label* mTodayGameTitle;		//오늘전적
	Nx::Label* mTodayGameUnderTitle;
	Nx::Label* mAccurTitle;		//누적전적
	Nx::Label* mAccurUnderTitle;
	Nx::Label* mHandTitle;		//족보전적
	Nx::Label* mHandUnderTitle;

	Nx::Label* mBestGetTitle;	//최고 획득 머니
	Nx::Label* mTodayBestGetTitle;	//최고 획득 머니
	Nx::Label* mAllinTitle;	//올인시킨횟수
};