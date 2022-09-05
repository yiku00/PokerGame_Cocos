#pragma once

#include "NxFramework.h"
#include "PokerPlayerInfoCommonPanel.h"
#include "PokerCardWidget.h"
#include "GameWinPanel.h"

class PokerPlayerInfoLeftPanel : public PokerPlayerInfoCommonPanel
{
public:
	PokerPlayerInfoLeftPanel();
	virtual ~PokerPlayerInfoLeftPanel();


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

	virtual void SetHighLowChoice(HighLowBettingKind betKind);

	virtual void setEmptyPlayerInfo();
	virtual void setGameStartPlayerInfo();
	virtual void turnOnUserInfoBack();
	virtual void turnOffUserInfoBack();

	virtual void InitMadeImage() {};

	virtual void InitWinnerText();
	virtual void SetWinnerText(int64 getMoney);
	virtual void EndWinnerText();
	virtual void InitRoomManager(bool isBig);

	virtual void ShowAllBet(bool _show);
	virtual void ShowSideBet(bool _show);
	virtual void ShowAllIn(bool _show);

	virtual void SetBadukiNumber(int _idx, int _num, bool _visible = true);
public:
	void _initPanel();
	void _initText();
	void _initImage();
	void _initGageBar();
	void _initBettingMark();
	void _initHighLowImage();
	
	void _makeTimeGaugeFull();
	void _makeSelectBox();
	void ShowMaxBet(bool _show);
	
private:
	float mElapsedTime;
	bool mIsTurn;	
	//플레이어 안으로 넣자.	
};
