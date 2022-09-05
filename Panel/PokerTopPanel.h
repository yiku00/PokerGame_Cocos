/********************************************************************
file name:	PokerTopPanel.h

purpose:	게임시작 , 게임 리필 , 나가기 버튼 등 젤 상단에 위치
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "GameRoomInfo.h"

class PokerTopPanel : public Panel, public Button::Listener, public SkelObject::Listener, public TextField::Listener
{
	
public:
	PokerTopPanel();
	virtual ~PokerTopPanel();
	
public:
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onClicked(const string& buttonName);
	virtual void onEnter() override;

	virtual void onAnimationEnded(const string& ani);

	//TextField::Listener
	virtual void onDetached();
public:
	void initPanel();
	void _initImage();

	void ShowPlayerResultPanel(int _index, bool _visible);
	void SetData(int _index, GameKind gameKind, WinKind winKind, string& nickname, bool isMine, int highJokboKind, int lowJokboKind, int64 inoutGameMoney);
	void SetPlayerResultPaenlVisible(int _index, bool isVisible);
	void SetPlayerResultPaenlAllVisible(bool isVisible);

	void ShowPanel();

	void SetPressExitButton();
	void SetReleaseExitButton();
	void SetPressExitStartButton();
	void SetPressExitFailButton();
	void SetPressExitReserveButton();
	void SetPressExitReserveCancelButton();
	void SetTurnOnLight();
	void SetTurnOffLight();
	void SetTurnOnGameStartButton();
	void SetTurnOffGameStartButton();

	void SetMoveStartButton();
	
	void GameStart();

	void SetOutButtonClick(bool value) { mIsOutButtonClick = value; }

	bool IsOutButtonClick() { return mIsOutButtonClick; }

	Button * GetStartButton() { return m_StartButton; }
	Button * GetExitButton() { return m_ExitBtn;  }
	
	void setPlayerInfoUserOptionPanel(int _id, bool _visible);
	void PlayerInfoPanelHide();

	void ShowLastRoundEffect(int _bigType);
	void ShowBadugiEffect(int _type);

	void TouchHiddenCardEventStart(float _delay);
	void TouchHiddenCardEvent();

	void TopButtonesEnable(bool isEnable);

	bool m_bTouchHiddenCard;
	bool m_bMoveHiddenCard;
	Button * m_HiddenTouchButton;
	Panel* m_HiddenTouchPanel;
	CCPoint m_posStartHiddenPanel;
	CCPoint m_posMoveHiddenPanel;
	CCPoint m_posStartHiddenCard;

	Panel* mHiddenBigTouchPanel;	//터치 패널 긴거
	CCPoint mBigPosStartHiddenPanel;
	CCPoint mBigPosMoveHiddenPanel;
	CCPoint mBigPosStartHiddenCard;


	void TurnOnGetChip();
	void ShowLevelUpEffect();
	void ShowMadeBonusEffect();
	void ShowAutoRefillEffect();
	void showCharacterEffect(int characterId , bool hasMadeMoney);
	void SetGameMode(GameMode _mode);
	void SetPLayerCount(int _count, int _totalCount);

	void ReSetResultPlayerRank();
	void SetResultPlayerRank(int _po, bool _visible, int _rank = 0);

	void SetActionFirework(int _count, float _delay);
	void ActionFirework();

	void ShowCurtainClose();
	void ShowCurtainOpen();
	void SetCutainClose();
	void SetCutainOpen();
	void ShowLastTable();
	void UpdateMoveLabelString();
	void initCharacterEffect();
	void setUseRoomMoveBtn(bool use);
private:
	void _initData();
	void _setParentPanel();
private:
	Panel* mParentPanel;
	Panel* mMainPanel;

	Button* m_StartButton;
	Button * m_ExitBtn;
	Nx::Label* mExitBtnLabel;
	Button * m_MoveBtn;
	Nx::Label* mMoveBtnLabel;
	Nx::Label* mStartButtonLabel;
	//Button * m_ReplayBtn;
	

	SkelObject * m_light;
	SkelObject* m_LastRound;
	SkelObject* m_BadugiEffect;

	bool	mIsOutButtonClick;

	SkelObject* m_Chip;
	SkelObject* m_LevelupEffect;
	SkelObject* m_MadeBonusEffect;
	SkelObject* m_AutoRefillEffect;
	SkelObject* m_PlayerCountBack;
	
	int m_fireworkIndex;
//	SkelObject* m_Firework[10];

	Widget* mPlayCountBg;
	SkelObject* m_GameRankBack[5];
	Nx::Label* m_GameRank[5];
	Nx::Label* mGameRankUnder[5];

	Nx::Label* m_PlayerCount;
	Nx::Label* m_TotalPlayerCount;

	SkelObject* m_FadeBlackbox;

	Nx::Label* mCharacterEffectLabel;
	CCPoint mOriginCharactgerEffectPos;

	TournamentWaitingPanel* m_pCurtain;
};
