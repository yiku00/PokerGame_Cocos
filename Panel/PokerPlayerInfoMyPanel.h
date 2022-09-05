#pragma once

#include "NxFramework.h"
#include "PokerPlayerInfoCommonPanel.h"
#include "PokerCardWidget.h"
#include "GameWinPanel.h"

class PokerPlayerInfoMyPanel :public PokerPlayerInfoCommonPanel
{
	
public:
	PokerPlayerInfoMyPanel();
	virtual ~PokerPlayerInfoMyPanel();

	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

public:
	virtual void turnOnTimeGauge(bool _pause = false);
	virtual void turnOffTimeGauge();

	virtual void setWinner(bool isWinner);
	virtual void setSeed(bool isSeed);

	virtual void SetBetting(BettingKind kind, bool isMe, int64 betMoney);

	virtual void ShowMade(int gameKind, int highJokbo, int lowJokbo);

	virtual void refreshCardSet();
	virtual void refreshAllCardSet();
	virtual void refreshInitCardSet();

	virtual void clearAllCards();
	
	virtual void update(float dt);

	virtual void addCard(int cardId);
	virtual void addInitCard(int cardId);

	virtual void SetHighLowChoice(HighLowBettingKind betKind, bool isMe);

	virtual void setEmptyPlayerInfo();
	virtual void setGameStartPlayerInfo();
	virtual void turnOnUserInfoBack();
	virtual void turnOffUserInfoBack();

	virtual void InitMadeImage();

	virtual void InitWinnerText();
	virtual void SetWinnerText(int64 getMoney);
	virtual void EndWinnerText();
	virtual void InitRoomManager(bool isBig);

	virtual void ShowAllBet(bool _show);
	virtual void ShowSideBet(bool _show);
	virtual void ShowAllIn(bool _show);
	virtual void ShowMaxBet(bool _show);

	virtual void SetBadukiNumber(int _idx, int _num, bool _visible = true);
public:
	void setBettingPanel();
	bool TouchBadugiCardCheck(CCPoint _touchPosint);
	void TouchBadugiCard(CCPoint _touchPosint);

private:
	void _initPanel();
	void _initText();
	void _initImage();
	void _initTimegauge();
	void _initBettingMark();
	
	void _initHighLowImage();

	void _makeTimeGaugeFull();
	void _makeSelectBox();

public:
	void addCards();
	void PlayTimeSound();
private:
	float mElapsedTime;
	bool mIsTurn;
	bool m_TimeSound;


	Nx::Label* mCardHandOrder;

	Panel* mBettingPanel;
	//SuperObject* mBettingImage;
	/*CardContainer mCardContainer;
	CardContainer mBackCardContainer;*/
	//int mTempCounter;
};
