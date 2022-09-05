#pragma once 

#define GAME_USER_MAX			5
#define BETTING_KIND_CNT		8
#define HIGHLOW_KIND_CNT		3

#define POT_EFFECT_TIME			0.4f
#define WIN_TEXT_EFFFECT_TIME	1.2f

#include "NxFramework.h"
#include "TypeDefine.pb.h"
#include "RoomPlayerInfo.pb.h"
#include "EnterRoomSuccess.pb.h"
#include "PlayerPoInfo.pb.h"
#include "RoomUserData.h"
#include "BettingSevenPokerPanel.h"
#include "PokerPlayerInfoCommonPanel.h"
#include "PokerResultPanel.h"
#include "BettingHighLowPanel.h"
#include "GamePlayData.pb.h"
#include "PokerUnderImoticonPanel.h"
#include "CardInfo.pb.h"
#include "SimplePopupPanel.h"
#include "TournamentWaitingPanel.h"

class BettingSevenPokerPanel;
class PokerPlayerInfoCommonPanel;
class PokerResultPanel;
class BettingHighLowPanel;
class PokerBackgroundPanel;
class PokerPlayerInfoPanel;
class PokerTopPanel;
class SimplePopupPanel;

enum PlayStatus {
	PLAY_NO = -1,										// �����
	PLAY_READY = 0,										// ����� ���� �غ� ��ٸ��� ��
	PLAY_BETTING_SEED_INIT = 1,							// �ʱ� ���ñ� ����
	PLAY_SHARE_CARD = 2,								// ī�� �����ֱ�
	PLAY_SHARE_CARD_WAIT = 3,							// ī�� ������ �� ��ٸ���
	PLAY_CARD_CHOICE = 4, 								// ������, �¸��� ����		//TODO : Ȯ�� �ʿ�
	PLAY_BETTING_WAIT = 5,								// ���� ���
	PLAY_BETTING = 6,									// ����						//TODO : Ȯ�� �ʿ�
	PLAY_HAZZ_UP = 7,
	PLAY_JOKBO_CHOICE = 8,								// ���� ����(���̷ο츸....) 
	PLAY_RESULT_CHECK = 9,								// ��� �Ѿ�� �� ��..
	PLAY_RESULT_PAE_SHOW = 10,							// �к���
	PLAY_RESULT = 11,									// ��� ȭ��
	PLAY_NEXT_READY = 12,								// ������ �Ѿ�� �� ���
	PLAY_SHARE_COMMUNITY_CARD = 13,						// �йи� ī�� ������
	PLAY_CHANGE_CARD = 14,								// ī�� �ٲٱ� ���� (�ٵ���)
	CHANGE_CARD_WAIT = 15,					// ī�� �ٲٱ� ��� ����
	ROOM_REARRANGE = 16,					// �����̹� ��ʸ�Ʈ �� ��迭 ��� ����
	PLAY_SURVIVAL_LAST_TABLE = 17,
	PLAY_BETTING_BLIND = 18,							// �ʱ� ���ñ� ����
	PLAY_BETTING_END = 19,								// �ʱ� ���ñ� ����
};

enum DealerAniKind
{
	DEALER_ACT1,
	DEALER_ACT2,
	DEALER_DEALING_READY,
	DEALER_DEALING_SHOOT,
	DEALER_GESTURE_BAD,
	DEALER_GESTURE_GOOD,
	DEALER_HURRY,
	DEALER_IDLE,
	DEALER_REACT_ALLIN_L,
	DEALER_REACT_ALLIN_R,
	DEALER_REACT_BANKRUPT,
	DEALER_REACT_BIGPOT,
	DEALER_REACT_MADE,
	DEALER_REACT_SMALLBET,
	DEALER_REACT_SMALLOPEN,
	DEALER_REACT_TIP,
	DEALER_SHUFFLING,
	DEALER_MaxDealerAniKind
};

enum DealerEfxKind
{
	EFX_DEALER_BACKSTRAIGHT,
	EFX_DEALER_BANKRUPT,
	EFX_DEALER_BIGPOT1,
	EFX_DEALER_BIGPOT2,
	EFX_DEALER_BIGPOT3,
	EFX_DEALER_CELEBRATE,
	EFX_DEALER_DIE,
	EFX_DEALER_FLUSH,
	EFX_DEALER_FOURCARD,
	EFX_DEALER_FULLHOUSE,
	EFX_DEALER_GAMESTART1,
	EFX_DEALER_GAMESTART2,
	EFX_DEALER_GAMESTART3,
	EFX_DEALER_HIGH,
	EFX_DEALER_INCOME1,
	EFX_DEALER_INCOME2,
	EFX_DEALER_INCOME3,
	EFX_DEALER_LOW,
	EFX_DEALER_MOUNTAIN,
	EFX_DEALER_ONEPAIR,
	EFX_DEALER_ROYALFLUSH,
	EFX_DEALER_SHOWDOWN,
	EFX_DEALER_SORRY,
	EFX_DEALER_STRAIGHT,
	EFX_DEALER_STRAIGHTFLUSH,
	EFX_DEALER_SWING,
	EFX_DEALER_TOP,
	EFX_DEALER_TRIPLE,
	EFX_DEALER_TURN,
	EFX_DEALER_TWOPAIR,
	EFX_DEALER_5TOP,
	EFX_DEALER_6TOP,
	EFX_DEALER_7TOP,
	EFX_DEALER_8TOP,
	EFX_DEALER_9TOP,
	EFX_DEALER_10TOP,
	EFX_DEALER_BASE,
	EFX_DEALER_DAY,
	EFX_DEALER_GOLF,
	EFX_DEALER_JTOP,
	EFX_DEALER_KTOP,
	EFX_DEALER_MORNING,
	EFX_DEALER_NIGHT,
	EFX_DEALER_NOTHING,
	EFX_DEALER_QTOP,
	EFX_DEALER_SECOND,
	EFX_DEALER_THIRD,
	EFX_DEALER_TWOBASE,
	EFX_DEALER_NOVOICE,
};

enum PotMoneyState
{
	POT_NONE = 0,
	POT_READY,
	POT_START,
	POT_UPDATE,
	POT_END
};

class GameRoomInfo : public SkelObject::EventListener
{
public:
	GameRoomInfo();
	~GameRoomInfo();
	bool OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void OnError(int protocol, int errorCode);
	int GetRoomId();

	void InitData();
	void Update(float dt);

	void SetUserData(RoomUserData* _ptr, int _idx);
	void SetData(EnterRoomSuccess * resData);
	void SetReplayData(GamePlayData* _resData);
	void ResetReplayData(GamePlayData* _resData);
	void AddUser(RoomPlayerInfo * playerInfo);
	void DeleteUser(int _po, int bossPo);
	
	RoomUserData* GetUserDataPtr(int _idx = -1);
	PokerResultPanel * GetPokerResultPanel();
	PokerBackgroundPanel * GetBackgroundPanel();
	PokerTopPanel * GetPokerTopPanel();
	void ShowStartButton();
	void HideStartButton();

	void SetCallAmount(int64 _money);
	void SetBettingAmount(int64 _money);
	virtual void onEvent(int trackIdx, spEvent* event);
public:
	GameLogKind GetGameState();
	int GetRoomIdx() { return m_RoomIdx; }
	int GetMyPo() { return m_MyPo;  }
	int GetMasterPo() { return m_MasterPo; }
	int GetBossPo() { return m_BossPo; }
	GameKind GetGameKind() { return m_GameKind; }
	GameMode GetGameMode() { return m_GameMode; }

	void SetUserPo();
	CCPoint GetUserPosition(int _index);

	void SetDealer();
	void SetHoldemDealer(int _userIdx);
	void DealerAnimation(DealerAniKind _kind);
	void DealerSound(DealerEfxKind _kind);

	void RemoveDealer();
	void RemovePotMoney();

	void StartGameReq();										//������ ���� ���� ��ȣ�� ������ ������.
	void ResourceLoadEndReq();									//��� ���ҽ��� �ε� �Ǿ����� ������ ������.

	void SetCardChoicePanel(bool _visible = true);				//������, ������ ����â ǥ�� ����.
	void CardChoiceREQ(int _eraseCardIdx, int _openCardIdx);	//������ ������, �������� ������ ������.
	
	//void SetGameReady();										//���ӷ� ���� ���� ����

	void SetMarker(int kind, int _userIdx);						// ������ ���� ǥ�����ִ� �Լ�
	void SetMaster(int _userIdx);								//�������� ���� ������ ��ġ ������ ����.
	void SetBoss(int _userIdx);									//�������� ���� ���� ��ġ ������ ����.
	void SetUser(int _userIdx);									//�������� ���� ���� ��ġ ������ ����.
	//void SetShareCard(int _userIdx, int _cardIdx, int _index);	//�������� ���� ī�� ������ ����.
	//void ShareCardEndReq();										//������ ī�� �й谡 �������� �˸�.

	void SetBettingSeedMoney(char * data, int size);			// ���� ���� �ݾ� ����
	void SetBetWait(int _bossIdx);								//���� ��� ���·� ��ȯ.

	void SetEndGame(int _winner, int _money);					//�������� ���� ���� ������ ����.
	void SetStartGame();										//�������� ���� ���� ���� �޼����� ó���Ѵ�.

	void InitGame();											//������ �ʱ�ȭ�Ѵ�.

	void KickPlayerREQ(int po, int socketId);
	void PlayerOutREQ(int po, int socketId);

	void KickPlayerRES(int po, int socketId, PlayerOutResrvKind _kind);	
	void PlayerOutRES(int po, int socketId, PlayerOutResrvKind _kind);

	void SetStatus(PlayStatus status);							// �÷��� ���� ����
	void AddCard(char * data, int size);						// ���ο� ī�带 �߰�
	void ChangeCards(char * data, int size);					// ���� ī�带 �� ������ ���� ī��� ����
	void SetBettingState(char * data, int size);				// ���� ���� ����
	void SetCardChoice();										// ī�� ���� ���·� ����.

	void SetHighLowChoice(bool isOn);							// ���̷ο� ���� ��ȯ
	
	void InitCanMyBettingKind();								// ���� ���� ���� �ʱ�ȭ
	void InitCanBettingPanel();									// ���� �ǳ� �ʱ�ȭ
	void SetCanMyBettingKind(char * data, int size);			// ���� ���� ���� ����
	
	void SetPrepareEnd(char * data, int size);					// �ε� �Ϸ� ����
	void SetPlayerOutReserve(char * data, int size);			// ������ ���� ���

	void BettingChoice(BettingKind _kind);
	void HighLowBettingChoice(HighLowBettingKind _kind);

	void SetMyHighJokbo(HighJokboKind _kind);					//�÷��̾� ���� ����.
	void SetMyLowJokbo(LowJokboKind _kind);						//�÷��̾� ���� ����.
	void SetMyBadugiJokbo(LowJokboKind _kind);
	void SetMyHoldemJokbo(HighJokboKind _kind);

	void Show7PokerPae(char * data, int size);					// ��ü ī�� ����
	void ShowHighLowPae(char * data, int size);					// ���̷ο� ī�� ����
	void ShowBadukiPae(char * data, int size);					// �ٵα� ī�� ����

	bool MoveRoom(char * data, int size);						// ���̵�

	void RearrangeComplete(char * data, int size);

	bool PlayerInProcess(char * msg, int size);
	
	void SetResult(char * data, int size);						// ��� ����
	void SortCard();								//��ü ī�� ����
	void SetHighLow(char * data, int size);						// ���̷ο� ����
	void SetHighLow(int po, HighLowBettingKind _kind);			// ���̷ο� ����
	bool SetGameIngInfo(char * msg, int size);					// ���� ���� ���� ����

	bool IsExitReserve() { return m_ExitReserve; }				// ������ �����̳�.
	void SetExit(bool isExe);									// ������ ����(isExe�� false�̸� �ִϸ��̼Ǹ�, true�� ������ ����)

	void SetRoomRearrange();

	PokerPlayerInfoCommonPanel * GetPlayerCommonPanel(int po);
	PokerPlayerInfoPanel * GetPlayerInfoPanel();
	PokerTopPanel * GetTopPanel();
	Panel* GetChracterPanel();
	Panel* GetCardPanel();

	float GetRefreshTime() { return m_Dtime;  }

	void MakeJokboInfoAndOtherInfo();
	void MakeMade();

	void GameStartCheck();
	void SetVisibleLight(bool isView);
	void SetGameMoney(int po, int64 gameMoney);
	bool ChangeManager(char * msg, int size);

	bool IsGameLoaded();
	void SetResultExceptPanelOff();
	void SetAfterResultUserInfo(char * msg, int size);
	void SetGamePlaySaveSeq(char * data, int size);	// ���� ����
	void SetSaveGamePlayData(char * data, int size);	// ���� ����
	void SetAdditionalResult(char * data, int size);
	int GetGamePlaySeq() { return m_GamePlaySeq; }
	void SetBettingRes(char * data, int size);
	void SetPlayerEmotion(char* data, int size);
	void ShowPlayGameStates(char* data, int size);
	void ShowPlayerStates(char* data, int size);
	void ShowLastLound();
	void ShowLastTableEffect();

	void SetIsSelectedCard() { m_isSelectedCard = true; }
	bool GetIsCardSelected() { return m_isSelectedCard; }

	void UpdateWinnerTextEffect(float dt);
	void UpdateDealer(float dt);
	void UpdatePotMoneyEffect(float dt);
	void SetPotMoneyUpdate(PotMoneyState _state);

	void ShowLastCardAnimation(int _po);
	bool CanExit(int _idx = -1);

	int64 GetSeedMoney() { return m_SeedMoney; }
	BettingRule GetBettingRule() { return m_BettingRule; }

	void SetHiddenCheck(bool _hidden);
 	bool isHiddenCheck() { return m_IsHiddenCheck; }
	int IsBigGame();
	bool isBigAnimation();	//ī�� ������ �ִϸ��̼�
	int getHiddenCardState();
	int64 GetMaxBetMoney() { return m_BettingMaxMoney; }

	int GetSurvivalUserCount() { return m_SurvivalCurUserCount; }
	int GetSurvivalTotalUserCount() { return m_SurvivalTotalUserCount; }
	void UpdateStayTime(std::string _time);
	void playJackpotBonusPanel();

	void refreshRoomNo();

private:
	void actionPopLoadingPanel();
	void popLoadingPanel();	// ���̺� �̵��� �ε�â ������ �ð�
	void _initDealerfee(); //���������� �ʱ�ȭ
private:
	bool m_IsHiddenCheck;
	bool m_bBigGameAction;
	BettingSevenPokerPanel * GetBettingSevenPokerPanel();
	BettingHighLowPanel * GetHighLowPanel();
	PokerUnderImoticonPanel* GetResultImoticonPanel();


	int64 CalcMyBettingMoney(int64 myMoney, int64 addMoney);
	void SetBettingInfoInit(bool isAll);	

	int64 GetBettingMoney(BettingKind betKind, int64 potMoney);	// ���� ������ ���� ���øӴ�
	int64 GetTotalBettingMoney(int po, BettingKind betKind, bool isReal);		// �ش� ������ �ش��ϴ� ���� �Ӵ� ���

	void SetPotMoney(int64 potMoney, int64 betMoney = 0);
	void SetMyCallMoney();

	void InitOldBetting();
	void NextReadyProcess();

	BettingKind GetPreviousBattingKind(int _idx);

	int GetCanPlayerCnt();
	void ExeAfterResultUserInfoUI();

	TournamentWaitingPanel* m_pStayPopup;
	TournamentWaitingPanel* m_pCurtain;


private:
	float m_Dtime;
	float m_UpdateTime;
	float m_DealerTime;

	int64 m_GameTime;

	int64 Dealerfee;
	float DealerPercent;

	bool ShouldDisplayDealerfee = false;

	int m_RoomIdx;
	int m_CurrentUser;
	int m_MaxUser;
	int64 m_SeedMoney;
	GameKind m_GameKind;
	GameMode m_GameMode;
	BettingRule m_BettingRule;

	int64 m_bigGameMoney1;
	int64 m_bigGameMoney2;

	int64 m_BettingMaxMoney;
	int64 m_LossMaxMoneyPerDay;

	
	bool m_isShareCardEnd;											// �������� ī�带 �� ��������� ����
	bool m_isSelectedCard;											// ó�� ī�� ���� �κ��� �������� ����.

	bool m_isBettingCount;

	bool m_isInitGame;

	int	m_GamePlaySeq;

	int m_SurvivalCurUserCount;
	int m_SurvivalTotalUserCount;

public:
	int m_MasterPo;
	int m_BossPo;
	int m_MyPo;
	int m_BetPo;

	int m_BigBlindPo;		// �����ε� ��ġ
	int m_DealerPo;			// ���� ��ġ

	int64 m_avgPotMoney;
	
	int64 m_BetMoney;					// �����Ͽ����� �� ���øӴ�
	int64 m_preUserBetMoney;			// �ջ���� ���øӴ�
	
	int64 m_PotMoney;

	int64 m_UpdatePotMoney;
	int64 m_PrePotMoney;

	vector<int64> m_PotMoneyUpdateList;
	vector<int64> m_PreMoneyUpdateList;

	float m_fPotMoneyEffectTime;
	float m_fPotMoneyUpdateTime;
	PotMoneyState m_PotMoneyEffectState;

	bool m_ExitReserve;					// ������ ����
	//bool m_IsGetChip;					// Ĩ ȹ�� ����
	bool m_IsLevelUp;					// ���� �� ����
	int64 m_RefillMoney;				// refill money
	bool m_IsCompleteQuest;				// �޼��� ����Ʈ�� �ִ��� ����
	int64 m_madeMoney;					// ���̵�Ӵ� �߰� ����
	int32  m_rank;						// ��ʸ�Ʈ ��ŷ
	
	RoomUserData * m_UserList[GAME_USER_MAX];
	int m_Message;

	GameLogKind m_GameState;
	PlayStatus m_PlayStatus;
	ChangeCardKind m_changeCardKind;

	bool m_CanMyBettingKind[BETTING_KIND_CNT];					// �� ���ú� ���� ����

	SkelObject* m_pDealer;
	SkelObject* m_pDealerUnder;
	bool m_DealerShoot;
	Panel*  m_pDealerTextBubble;

	CCLabelBMFont* m_pLabelWinnerMoney;
	bool m_bWinnerMonnyEffectUpdate;
	float m_fWinnerMoneyEfxTime;
	int64 m_EffectMoney;
	string m_WinnerMoneyStr;

	bool m_isReplayData;
	//SkelObject* m_pWinnerText[GAME_USER_MAX];

	void SetWinnerMoneyString(int64 _money);
	void Action_WinnerText(int _po, int64 _money);
	//void Remove_WinnerText();
	void SetBettingReApply(char * data, int size);

	//My JokboCheck
	bool m_myMadeCheck;
	float m_myMadeCheckDelay;
	int mMadeJokbo;

	//baduki sortcard 
	bool m_badugiSortedCard;
	float m_badugiSortDelay;
	
	void SetBadugiSortTime(float _delay);
	void UpdateBadugiSortCheck(float _dt);

	void SetMyMadeCheckTime(float _delay);
	void UpdateMyMadeCheck(float _dt);
	void MyMadeCheck();
	void MyHoldemCheck();
	
	//void StartCardMadeEffect();
	void SetReplayOtherData(int _kind, int _grade);
	void ShowBigGameEffect();
	void ShowStartGameInfomation();
	void HideStartGameInfomation();
	void TouchHiddenCard();
	void SetHiddenTouch();

	float m_fSoundDelayTime;
	int m_soundType;
	void SetDealerSoundDelayPlay(float _delay, int _type);

	bool m_bShowDown;
	void PlayShowDownEfx();
	void StopDealerTextBubble();
	void initHiddenTouchPanel();
	void ShowHiddenCardAnimaion(bool _action = true);

	//Babugi
	bool m_bSendWait;
	bool m_bSendChanageRequest;
	bool m_bSendPassRequest;
	int m_dayState;
	bool m_SelectedNumber[4];
	void MyBadugiMadeCheck();
	void SetBadugiSelectState(int _kind);
	void ShowBadugiSelectCard(char* data, int size);
	void ChangeBadugiSelectCard(char* data, int size);

	void ResetBadugiSelectNumber();
	void BadugiShareCard(char * data, int size);
	void SetChangeCardKind(ChangeCardKind kind);
	void SetShareCardEnd();
	void ShowLastBadugiAnimation(int _po);
	void ShowChangeCardSeletPanel(char * data, int size);

	void SetChangeBoss(char * data, int size);
	void SendBadugiChangeCardReq();
	void SendBadugiChangePassReq();

	//Holdem
	bool m_isBigCommunityCard;

	bool m_bCommunityCardProcessing;
	float m_fProcessTime;
	vector<CardData*> m_CommunityCardList;
	CCRect m_CommunityCardRect[5];
	CCRect m_CommunityCardRectBig[5];
	SkelObject* m_CommunityCardBackBoard;
	void InitCommunityCard();
	void ReleaseCommunityCard();
	void SetCommunityCard(char* data, int size);
	void AddCommunityCard(int _number, int _kind, bool _showBack, bool _action = true);
	void ActionMoveCommunityCard(int _idx, CCPoint _moveto);

	void ShowCommnityBig(bool _big);

	void ResetCommunityCard();
	void ShowHoldemPae(char * data, int size);
	void SetPlayersStatus(char * data, int size);

	void SetCommunityCardProcessTime(float _time);
	void UpdateComminityProcess(float _dt);

	//Player Animation
	void Action_EnterRoomCharacter(int _po);
	void SetChangeSeedMoney(char * data, int size);

	//Effect
	void MoveRoomEffect();
	void SetBettingBlindMoney(char * data, int size);
	void SetBigBlind(int _userIdx);
	void SetBettingBackMoney(char * data, int size);
	void ShowDownState(char* data, int size);

	int mChipCount;
	bool isCharacterEffect;
	int64 mJackPotRewardGameMoney;
	bool mShowTouchPanel;
};