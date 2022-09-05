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
	PLAY_NO = -1,										// 대기중
	PLAY_READY = 0,										// 사람들 시작 준비 기다리는 중
	PLAY_BETTING_SEED_INIT = 1,							// 초기 배팅금 세팅
	PLAY_SHARE_CARD = 2,								// 카드 나눠주기
	PLAY_SHARE_CARD_WAIT = 3,							// 카드 나눠준 후 기다리기
	PLAY_CARD_CHOICE = 4, 								// 버릴패, 승리패 선택		//TODO : 확인 필요
	PLAY_BETTING_WAIT = 5,								// 배팅 대기
	PLAY_BETTING = 6,									// 배팅						//TODO : 확인 필요
	PLAY_HAZZ_UP = 7,
	PLAY_JOKBO_CHOICE = 8,								// 족보 선택(하이로우만....) 
	PLAY_RESULT_CHECK = 9,								// 결과 넘어가기 전 텀..
	PLAY_RESULT_PAE_SHOW = 10,							// 패보기
	PLAY_RESULT = 11,									// 결과 화면
	PLAY_NEXT_READY = 12,								// 다음판 넘어가기 전 대기
	PLAY_SHARE_COMMUNITY_CARD = 13,						// 패밀리 카드 나누기
	PLAY_CHANGE_CARD = 14,								// 카드 바꾸기 상태 (바둑이)
	CHANGE_CARD_WAIT = 15,					// 카드 바꾸기 대기 상태
	ROOM_REARRANGE = 16,					// 서바이벌 토너먼트 방 재배열 대기 상태
	PLAY_SURVIVAL_LAST_TABLE = 17,
	PLAY_BETTING_BLIND = 18,							// 초기 배팅금 세팅
	PLAY_BETTING_END = 19,								// 초기 배팅금 세팅
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

	void StartGameReq();										//방장이 게임 시작 신호를 서버에 보낸다.
	void ResourceLoadEndReq();									//모든 리소스가 로드 되었음을 서버에 보낸다.

	void SetCardChoicePanel(bool _visible = true);				//오픈패, 버릴패 선택창 표시 여부.
	void CardChoiceREQ(int _eraseCardIdx, int _openCardIdx);	//서버에 오픈패, 버릴패의 정보를 보낸다.
	
	//void SetGameReady();										//게임룸 시작 정보 적용

	void SetMarker(int kind, int _userIdx);						// 보스나 방장 표시해주는 함수
	void SetMaster(int _userIdx);								//서버에서 받은 마서터 위치 정보를 적용.
	void SetBoss(int _userIdx);									//서버에서 받은 보스 위치 정보를 적용.
	void SetUser(int _userIdx);									//서버에서 받은 유저 위치 정보를 적용.
	//void SetShareCard(int _userIdx, int _cardIdx, int _index);	//서버에서 받은 카드 정보를 적용.
	//void ShareCardEndReq();										//서버에 카드 분배가 끝났음을 알림.

	void SetBettingSeedMoney(char * data, int size);			// 서버 배팅 금액 설정
	void SetBetWait(int _bossIdx);								//배팅 대기 상태로 전환.

	void SetEndGame(int _winner, int _money);					//서버에서 받은 승자 정보를 적용.
	void SetStartGame();										//서버에서 받은 게임 시작 메세지를 처리한다.

	void InitGame();											//게임을 초기화한다.

	void KickPlayerREQ(int po, int socketId);
	void PlayerOutREQ(int po, int socketId);

	void KickPlayerRES(int po, int socketId, PlayerOutResrvKind _kind);	
	void PlayerOutRES(int po, int socketId, PlayerOutResrvKind _kind);

	void SetStatus(PlayStatus status);							// 플레이 상태 세팅
	void AddCard(char * data, int size);						// 새로운 카드를 추가
	void ChangeCards(char * data, int size);					// 이전 카드를 다 날리고 현재 카드로 세팅
	void SetBettingState(char * data, int size);				// 배팅 상태 세팅
	void SetCardChoice();										// 카드 선택 상태로 돌림.

	void SetHighLowChoice(bool isOn);							// 하이로우 상태 전환
	
	void InitCanMyBettingKind();								// 나의 배팅 정보 초기화
	void InitCanBettingPanel();									// 배팅 판넬 초기화
	void SetCanMyBettingKind(char * data, int size);			// 나의 배팅 정보 세팅
	
	void SetPrepareEnd(char * data, int size);					// 로딩 완료 여부
	void SetPlayerOutReserve(char * data, int size);			// 나가기 예약 결과

	void BettingChoice(BettingKind _kind);
	void HighLowBettingChoice(HighLowBettingKind _kind);

	void SetMyHighJokbo(HighJokboKind _kind);					//플레이어 족보 셋팅.
	void SetMyLowJokbo(LowJokboKind _kind);						//플레이어 족보 셋팅.
	void SetMyBadugiJokbo(LowJokboKind _kind);
	void SetMyHoldemJokbo(HighJokboKind _kind);

	void Show7PokerPae(char * data, int size);					// 전체 카드 오픈
	void ShowHighLowPae(char * data, int size);					// 하이로우 카드 오픈
	void ShowBadukiPae(char * data, int size);					// 바두기 카드 오픈

	bool MoveRoom(char * data, int size);						// 방이동

	void RearrangeComplete(char * data, int size);

	bool PlayerInProcess(char * msg, int size);
	
	void SetResult(char * data, int size);						// 결과 세팅
	void SortCard();								//전체 카드 정리
	void SetHighLow(char * data, int size);						// 하이로우 선택
	void SetHighLow(int po, HighLowBettingKind _kind);			// 하이로우 선택
	bool SetGameIngInfo(char * msg, int size);					// 게임 진행 정보 세팅

	bool IsExitReserve() { return m_ExitReserve; }				// 나가기 예약이냐.
	void SetExit(bool isExe);									// 나가기 실행(isExe가 false이면 애니메이션만, true는 나가기 실행)

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
	void SetGamePlaySaveSeq(char * data, int size);	// 이전 버전
	void SetSaveGamePlayData(char * data, int size);	// 현재 버전
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
	bool isBigAnimation();	//카드 뒤집는 애니메이션
	int getHiddenCardState();
	int64 GetMaxBetMoney() { return m_BettingMaxMoney; }

	int GetSurvivalUserCount() { return m_SurvivalCurUserCount; }
	int GetSurvivalTotalUserCount() { return m_SurvivalTotalUserCount; }
	void UpdateStayTime(std::string _time);
	void playJackpotBonusPanel();

	void refreshRoomNo();

private:
	void actionPopLoadingPanel();
	void popLoadingPanel();	// 테이블 이동중 로딩창 꺼질때 시간
	void _initDealerfee(); //딜러수수료 초기화
private:
	bool m_IsHiddenCheck;
	bool m_bBigGameAction;
	BettingSevenPokerPanel * GetBettingSevenPokerPanel();
	BettingHighLowPanel * GetHighLowPanel();
	PokerUnderImoticonPanel* GetResultImoticonPanel();


	int64 CalcMyBettingMoney(int64 myMoney, int64 addMoney);
	void SetBettingInfoInit(bool isAll);	

	int64 GetBettingMoney(BettingKind betKind, int64 potMoney);	// 배팅 종류에 따른 배팅머니
	int64 GetTotalBettingMoney(int po, BettingKind betKind, bool isReal);		// 해당 유저에 해당하는 배팅 머니 계산

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

	
	bool m_isShareCardEnd;											// 서버에서 카드를 다 나눠줬는지 여부
	bool m_isSelectedCard;											// 처음 카드 고르는 부분이 끝났는지 여부.

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

	int m_BigBlindPo;		// 빅블라인드 위치
	int m_DealerPo;			// 딜러 위치

	int64 m_avgPotMoney;
	
	int64 m_BetMoney;					// 현재턴에서의 총 배팅머니
	int64 m_preUserBetMoney;			// 앞사람의 배팅머니
	
	int64 m_PotMoney;

	int64 m_UpdatePotMoney;
	int64 m_PrePotMoney;

	vector<int64> m_PotMoneyUpdateList;
	vector<int64> m_PreMoneyUpdateList;

	float m_fPotMoneyEffectTime;
	float m_fPotMoneyUpdateTime;
	PotMoneyState m_PotMoneyEffectState;

	bool m_ExitReserve;					// 나가기 예약
	//bool m_IsGetChip;					// 칩 획득 여부
	bool m_IsLevelUp;					// 레벨 업 여부
	int64 m_RefillMoney;				// refill money
	bool m_IsCompleteQuest;				// 달성한 퀘스트가 있는지 여부
	int64 m_madeMoney;					// 메이드머니 추가 보상
	int32  m_rank;						// 토너먼트 랭킹
	
	RoomUserData * m_UserList[GAME_USER_MAX];
	int m_Message;

	GameLogKind m_GameState;
	PlayStatus m_PlayStatus;
	ChangeCardKind m_changeCardKind;

	bool m_CanMyBettingKind[BETTING_KIND_CNT];					// 각 배팅별 가능 여부

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