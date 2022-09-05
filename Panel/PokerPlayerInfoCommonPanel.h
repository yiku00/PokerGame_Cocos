#pragma once
#include "NxFramework.h"
#include "PokerCardHelper.h"
#include "TypeDefine.pb.h"
#include "PlayerData.h"
//#include "PokerEmotionPanel.h"
#include "PokerUserInfoPanel.h"
#include "GameWinPanel.h"

class Player;
class PokerPlayerInfoCommonPanel : public Panel, public SkelObject::Listener, public SkelObject::EventListener
{
public:
	// 유저 상태 종류
	enum UserLoadKind
	{
		USER_LOAD_ENTER = 0,	// 유저 입장중 상태
		USER_LOAD_WAIT = 1,	// 유저 대기중 상태
	};


	PokerPlayerInfoCommonPanel();
	virtual ~PokerPlayerInfoCommonPanel();

private:
	void _initData();
	void refreshMyMoney();
	void refreshLimited();

public:
	virtual void onAnimationEnded(const string& ani);
	virtual void onEvent(int trackIdx, spEvent* event);

	virtual void turnOnTimeGauge(bool _pause = false) = 0;
	virtual void turnOffTimeGauge() = 0;

	virtual void setWinner(bool isWinner) = 0;
	virtual void setSeed(bool isSeed) = 0;

	virtual void refreshCardSet() = 0;
	virtual void refreshAllCardSet() = 0;
	virtual void refreshInitCardSet() = 0;
	virtual void clearAllCards() = 0;

	virtual void setPlayer(Player* player) { mPlayer = player; }
	
	virtual void update(float dt) = 0;
	virtual void addCard(int cardId) = 0;
	virtual void addInitCard(int cardId) = 0;

	virtual void SetBetting(BettingKind kind, bool isMe, int64 betMoney);
		
	virtual void ShowMade(int gameKind, int highJokbo, int lowJokbo) = 0;

	virtual void setEmptyPlayerInfo() = 0;
	virtual void setGameStartPlayerInfo() = 0;

	virtual void turnOnUserInfoBack() = 0;
	virtual void turnOffUserInfoBack() = 0;

	virtual void SetBadukiNumber(int _idx, int _num, bool _visible) = 0;


	void turnOnWaitMark(UserLoadKind kind);
	void turnOffWaitMark();

	Player* getPlayer() { return mPlayer; }

	void TurnOnHighLowChoice();
	void TurnOffHighLowChoice();
	virtual void SetHighLowChoice(HighLowBettingKind betKind, bool isMe);

	void SetMasterMark(bool isView, bool isMe);
	void SetBossMark(bool isView, bool isMe);

	void SetAllBet(AllBetKind kind);
	void SetAllIn(bool isAllin);

	virtual void ShowAllBet(bool _show) = 0;
	virtual void ShowSideBet(bool _show) = 0;
	virtual void ShowAllIn(bool _show) = 0;
	virtual void ShowMaxBet(bool _show) = 0;

	void SetBasicInfo(PlayerData * data);
	void SetDetailInfo(PlayerData * data);

	void SetBettingAmount(int64 betMoney);
	void ClearBettingAmount();

	void TurnOnGameOut(int kind);
	void TurnOffGameOut();

	void TurnOnJokboInfo(string jokbo);
	void TurnOffJokboInfo();
	void InitJokboInfo();
	void MoveCardJokboInfoPo(int kind);

	void InitAllBetImage();
	void InitWaitImage();
	virtual void InitMadeImage() = 0;

	virtual void InitWinnerText() = 0;
	virtual void SetWinnerText(int64 getMoney) = 0;
	virtual void EndWinnerText() = 0;
	virtual void InitRoomManager(bool isBig) = 0;
	void TurnOffWinnerText();

	void SetGoldAmount(int64 gameMoney);

	void SetShareEndCard();
	void CallBackShareEndCard();

	void SetMadeJokbo(int kind);
	void TurnOnPlayerRank(int _rank, bool _isComplete = true);
	void TurnOffPlayerRank();
	void TurnOnPlayerDisconnect(int _leftgame);
	void TurnOffPlayerDisconnect();
	
	//내 창인지를 셋팅한다.
	void setMyInfo();
	void addLimitedError();	//돈 리미티드가 넘으면 표시한다.

protected:
	float _getPercentage(float currentValue, float maxValue);
	void _initHighLowImage();

private:
	Player* mPlayer;
protected:
	CardContainer mCardContainer;
	CardContainer mBackCardContainer;
	CardContainer mInitCardContainer;
	CardNumberContainer mCardNumbers;

public:
	SkelObject * mBettingImage;
	SkelObject * mHighLowImage;

	Nx::Label* mPlayerName;
	Nx::Label* mGoldAmount;
	Nx::Label* mBettingAmount;

	SkelObject * mRoomManager;

	SkelObject * mCardJokboInfo;
	Nx::Label *		mCardJokboLabel;
	
	Panel* mParentPanel;
	Panel* mMainPanel;

	SkelObject * m_pWinnerText;
	//Label * m_pWinnerMoneyLabel;

	SkelObject* m_AllInImage;
	SkelObject* m_AllBetImage;
	SkelObject* m_SideBetImage;

	SkelObject* m_WaitImage;
	SkelObject* m_EnterImage;
	SkelObject * mMadeImage;

	Button* m_pUserPanelBtn;
	
	int m_MadeKind;

	int m_AllBetKind;

	//PokerEmotionPanel* m_pEmotionPanel;
	PokerUserInfoPanel* m_pUserInfoPanel;
	GameWinPanel* mWinPanel;
	bool mMyInfo;
	int64 mNowGameMoney;
};