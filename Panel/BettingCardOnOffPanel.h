/********************************************************************
file name:	BettingCardOnOffPanel.h

purpose:	게임 시작시에 버릴 카드 선택 및 오픈할 카드 선택하는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "PokerCardHelper.h"

#define TIME_LINE_WIDTH 2.f
#define TIME_LINE_WIDTH_MAX 350.f
#define TIME_LINE_INIT_POSX 128.f

class BettingCardOnOffPanel : public Panel , Button::Listener
{
public:
	enum OnOffStep {
		CardOffOff,
		CardOffOn
	};
public:
	BettingCardOnOffPanel();
	virtual ~BettingCardOnOffPanel();

public:
	virtual void onClicked(const string& buttonName);
	void onClickedOff(const string& buttonName);
	void onClickedOn(const string& buttonName);
	void onUpdate(float dt);
	//void setGameInterface(IGamePlay* gameInterface) { mGamePlayInterface = gameInterface; }
	//void setInitCards(CardNumberContainer& cards) { mInitCardNumbers = cards; _refreshCards(); }
	void setTouchEnable(bool touchEnable);
	
	void StartSetting();
	void ClosePanel();
	void _makeCardPosition(bool _state);
	void ShowCancelBtn(int _idx, bool _show);
private:
	void _initData();
	void _initPanel();
	void _initImage();
	void _initLabel();
	void _initTimeGauge();
	
	void _setParentPanel();
	void _makeTimeGaugeFull();
	void setTimeGauge(float _per);
public:
	Panel* mParentPanel;
	Panel* mMainPanel;
	SkelObject* m_pCancelButton;
private:
	float mElapsedTime;
	//IGamePlay* mGamePlayInterface;
	CardNumberContainer mInitCardNumbers;
	CardNumberContainer mArrangedCardNumber;
	//CardContainer mCards;

	bool mTouchEnable;
	OnOffStep mOnOffStep;
	int mOffCardIndex;
	int mOnCardIndex;	
};