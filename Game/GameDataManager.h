#pragma once

#include "NxFramework.h"
#include "NxSingleton.h"
#include "NxDefine.h"
#include "RoomPlayerInfo.pb.h"
#include "PlayerData.h"
#include "GameRoomInfo.h"
#include "BettingRes.pb.h"
#include "Web/WebService.h"
#include "W_RankInfo.pb.h"
#include "RoomListReq.pb.h"
#include "CustomPopupPanel.h"
#include "W_DeathMatchOfInfo.pb.h"
#include "CmdList.h"
#include "W_PlayerInfo.pb.h"
#include "W_UserInfo.pb.h"
#include "W_SkinData.pb.h"
#include "W_ModelData.pb.h"
#include "W_DisplayModelData.pb.h"

class PokerCardWidget;
class RoomPlayerInfo;

#define GAME_START_WAIT_TIME			15		// ���� ���� ��� �ð�(10��)
#define GAME_BETTING_SEED_WAIT_TIME		1		// ���� �õ� ���� �� ��� �ð� (1��)
#define GAME_SHARE_CARD_MEMBER_TIME		0.5f			// �� ����� ī�� �����ֱ� �ð�
#define GAME_SHARE_CARD_WAIT_TIME		10		// ī�� �� �����ְ� ��� �ð�
#define GAME_CARD_CHOICE_TIME			10		// ī�� ���� �ð�
#define GAME_BETTING_WAIT_TIME			30		// ���� ��� �ð�
#define GAME_REUSLT_CHECK_TIME			2			// ����� �Ѿ�� �� ��� ���� �ð�
#define GAME_REUSLT_TIME				5		// ��� ȭ��
#define GAME_NEXT_READY_TIME			1			// ���� ���� �ϱ��� ��� ��� �ð�.
#define GAME_JOKBO_CHOICE_TIME			10		// ���� ���� �ð�
#define GAME_RESULT_PAE_SHOW_TIME		2			// JOKBO SEE TIME
#define COUNT_CHANNEL_ROOM_REQ			16		//�������� ���� ��û ��

#define GAME_KIND_COUNT			2
#define ROOM_LIST_COUNT			8

#define STORE_KIND						1		// ��Ż� ��ȣ

#define DEFAULT_MODEL_SUBLIST_UNIT 60;
#define DEFAULT_MODEL_INDEX_HEAD_NUMBER 10000;
#define DEFAULT_MODEL_INDEX_MIDDLE_NUMBER 100;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#define LABEL_ANCHOR_OFFSET				1.0f	// ����	
#else
	#define LABEL_ANCHOR_OFFSET				1.0f	// ����	
#endif

enum GameEfxKind
{
	EFX_GAME_BBING = 100,
	EFX_GAME_BET,
	EFX_GAME_BIGBET,
	EFX_GAME_CARDDEAL,
	EFX_GAME_CARDDOWN,
	EFX_GAME_CARDFLOP,
	EFX_GAME_CARDOPEN,
	EFX_GAME_CHEER,
	EFX_GAME_CROWD,
	EFX_GAME_EXIT,
	EFX_GAME_WIN,
	EFX_GAME_LOSE,
	EFX_GAME_TENSION,
	EFX_GAME_TIMER,
	EFX_GAME_TAKECHIP,
	EFX_GAME_BTN,
	EFX_GAME_CHECK,
	EFX_GAME_ENTERGAME,
	EFX_GAME_PAGE,
	EFX_GAME_POPUPOPEN,
	EFX_GAME_MADE,
	EFX_GAME_SLOTCOIN,
	EFX_GAME_SLOTLEVER,
	EFX_GAME_SLOTSPIN,
	EFX_GAME_SLOTSTOP,
	EFX_GAME_SLOTJACKPOT,
	EFX_GAME_SLOTWIN,
	EFX_GAME_KIND_MAX
};

enum GameSceneLoadeStatus
{
	GAME_SCENE_NOT_LOAD		= 0,
	GAME_SCENE_LOADING		= 1,
	GAME_SCENE_LOADED		= 2,
};

enum UpdateUserEndStatus
{
	UPDATE_USER_END_LOBBY,
	UPDATE_USER_END_MAKEROOM,
	UPDATE_NEW_USER_END_MAKEROOM,
};

enum REPLAY_OWN
{
	OWN_SOMEONE = 0,
	OWN_MINE = 1
};

enum NICKNAME_CHECK_ERROR
{
	NCE_SUCCESS		= 1,
	NCE_LENGTH_ERROR = 2,
	NCE_SPECIAL_LETTER_ERROR = 3,
	NCE_SPACE_ERROR = 4,
};

enum MODEL_TYPE {
	MODEL_SHOP,
	MODEL_SHOP_SUB,
	MODEL_INVEN,
	MODEL_INVEN_SUB,
};
struct AccountCreateInfo
{
	int		characterIdx;	// ĳ���� ��ȣ
	string	nickname;	// �г���	

};

enum CharaterType
{
	SANTIAGO = 1,
	CHRISTINA,
	ALEXANDER,
	BLACKROSE,
	JENIPER,
	MARTIN,
	SANTIAGO2,
	CHRISTINA2,
	ALEXANDER2,
	BLACKROSE2,
	JENIPER2,
	MARTIN2,
};


enum DataSortType
{
	SORT_TYPE_SCORE = 0,
	SORT_TYPE_DATE, 
	SORT_TYPE_LEVEL,
	SORT_TYPE_KILL,
};

enum FriendDataType
{
	FRIEND_DATA_SNS = 0,
	FRIEND_DATA_GAME,
	FRIEND_DATA_REQUEST,
	FRIEND_DATA_RECOMMEND,
};

enum eOptionIndex
{
	eOption_BGM = 0,
	eOption_EFX,
	eOption_VOICE,
	eOption_HIDDEN,
	eOption_POPUP,
	eOption_CNT
};

enum GameInfoPanelType
{
	PANEL_TYPE_MY = 0,
	PANEL_TYPE_LEFT_TWO,
	PANEL_TYPE_LEFT_ONE,
	PANEL_TYPE_RIGHT_ONE,
	PANEL_TYPE_RIGHT_TWO,
	
};

enum GamePutOutType
{
	PUTOUT_NO				= 0,
	PUTOUT_LOSS_MONEY_DAY	= 1,
	PUTOUT_PLAY_MIN_MONEY	= 2
};

//static const char gSynopsisKey[32] = "PlaySynopsis";
//static const char gTutorialKey[32] = "PlayTutorial";
enum WebPageType
{
	WEB_HELP_TYPE			= 1,
	WEB_ASK_TYPE			= 2,
	WEB_POLICY_TYPE			= 3,
	WEB_TERM_TYPE			= 4,
	WEB_SILVER_MEMBER_TYPE	= 5,
	WEB_GOLD_MEMBER_TYPE	= 6,
	WEB_ADULT				= 7,
	WEB_TOURNAMENT_TYPE		= 8,
	WEB_REFUND_TYPE			= 9,
	WEB_CAMPAIGN_TYPE		= 10,
	WEB_MOBLIE_USAGE = 11,
};

enum TimeShowType
{
	SHOW_TIME_DAY,
	SHOW_TIME_HOUR,
	SHOW_TIME_MIN,
	SHOW_TIME_ALL,
};

enum BadukiDayType
{
	DAY_TYPE_MORNING,
	DAY_TYPE_AFTERNOON,
	DAY_TYPE_NIGHT,
	DAY_TYPE_END,
	DAY_TYPE_ALL_CLOSE,
};

enum CityName
{
	FREE = 0,
	KANGWOON,
	SYDNEY,
	ATLANTA,
	PARIS,
	MAKAO,
	LASVEGAS,
	FRIEND,
};

enum ModelInfo
{
	TAP_ID =0,
	TAP_INDEX,
	MODEL_INDEX,
};

enum TAB_TYPE {
	MAXIM_TAB = 0,
	RACING_TAB,
};
static const char gRankingTutorialKey[32] = "RankingTutorial";
static const char gReplayTutorialKey[32] = "ReplayTutorial";

static const char gOptionKey[eOption_CNT][32] =
{
	"GameOptionBGM",
	"GameOptionEFX",
	"GameOptionVOICE",
	"GameOptionHIDEN",
	"GameOptionPOPUP"
};


class OptionDefineValue
{
public:
	OptionDefineValue()
	{
		m_music = true;
		m_effect = true;
		m_voice = true;
		m_hiddenCard = true;
		m_popupAlram = true;
	}

	bool m_music;
	bool m_effect;
	bool m_voice;
	bool m_hiddenCard;
	bool m_popupAlram;
};

class GameDataManager : public Singleton < GameDataManager >, public Node
{
public:
	GameDataManager();
	~GameDataManager();

	void update(float dt);

	bool OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);

	PlayerData* GetPlayerDataPtr();
	void SetPlayerData(PlayerData* _ptr);

	GameRoomInfo* GetGameRoomInfoPtr();
	void SetGameRoomInfo(GameRoomInfo* _ptr);

	string GetJokboFrameName(int _kind, bool _on);
	string GetBadukiJokboFrameName(int _kind, bool _on);
	string GetJokboStr(int _kind);
	string GetFullJokboStr(int _kind);
	string GetBadugiJokboStr(int _kind);

	string GetCardNumStr(int number);
	string GetKoreanLiteral(string number, int unit = 10);
	string GetU8SubStr(string str, int size);
	string strtoupper(string str);
	int GetConnChannelId() { return m_ConnChannelId; }

	void PlayGameSound(GameEfxKind _kind, bool _play = true, bool _loop = false);
	float GetRefreshTime() { return GetGameRoomInfoPtr()->GetRefreshTime(); }

	int ClientToServerIndex(int _idx);
	int ServerToClientIndex(int _idx);

	void SetGameSceneLoaded(int loadStatus) { m_GameSceneLoadStatus = loadStatus; }

	int GetGameSceneLoaded() { return m_GameSceneLoadStatus; }

	bool MakeRoom(char * data, int size);
	void PlayerOutResourceProcess(int po, int bossIdx = -1, bool isDisconnect = false, int _disconnectCnt = -1);
	void DestroyRoom();

	//WebService
	static EncryptString getEncryptString(const string& in, const string& key, const string& iv);
	W_GameData* InitGameData(const W_GameData& data);
	void RemoveUserDataInfo();

	void RemoveCharacterInfoList();
	void RemoveLetterInfoList();
	void RemoveQuestInfoList();
	void RemoveEventList();

	void RemoveChannelList();
	void RemoveLobbyList();
	void Remove7PokerList();
	void RemoveHighLowList();
	void RemoveBadukiList();
	void RemoveHoldemList();

	void RemoveFriendList();
	void RemoveSnsDataList();
	void RemoveFriendDataList();
	void RemoveRecommendDataList();
	void RemoveRequestDataList();

	void RemoveReplayDataList();
	void RemoveRankDataList();
	void RemoveMyRankData();

	void ReomveChannelRoomInfoList();

	void SetSlotMachineRewardInfo(W_RewardInfo* _pInfo);

	int GetReplayID() { return m_ReplaySeqID; }
	void SetReplayID(int id) { m_ReplaySeqID = id; }

	W_GameData* GetGameDataPtr() { return mGameData; }

	void OnWebserviceMassage(int _type);
	
	string GetRemainWeeklyBonusTime(int _type = SHOW_TIME_ALL);

	void SortReplayData(int _type);
	void SortRankingData(int _type);
	void SortFriendData(int _type, int _ndataType);

	void FreeUiProcess();
	
	//History
	void SetUiState(int _state);
	int GetUiState();
	int PopUiState();
	void ClearUiState();
	bool hasUiHistoryState(int _state);

	void SetBadugiDayKind(int _kind) { m_kindBadugiDay = _kind; }
	ChangeCardKind GetBadugiDayKind();

	void SetLoginType(eLoginType _type) { m_LoginType = _type; }
	
	void SetIsDirectTournamentLink() { m_isDirectTournamentLink = true; }
	void SetIsDirectSurvivalLink() { m_isDirectSurvivalLink = true; }
	bool canUpdateSurvival();
	void SetEdittextString(std::string _editText);

	const W_CharacterData* getCharacterData(int id);

	void setPayFirstInfo(int payInfo);

	void setNotiInfo(const W_NotiInfo& notiInfo);

	void setFightSceneEnd();

	const W_SkinData* getSkinData(int id);

	void SetSurvivalNotiTimer();
	void MakeRegularAdminPopup();
	bool ShouldAsyncTime();
public:
	bool m_bEditTextField;
	TextField* m_onFocusTextFeild;
	std::string m_eidtText;
	std::list<W_NoticeData> mNotidata;
	std::list<W_NoticeData> mValidNotidata;
	bool m_isDirectTournamentLink;
	bool m_isDirectSurvivalLink;
	int64 LastSendTimeUpdateSurvival;
	bool SurvivalButtonPressed;

	double Survival_RegisterableTime;
	double Survival_RegisterExpireTime;
	double Survival_WaitableTime;
	double Survival_WaitExpireTime;
	double Survival_GameableTime;
	double Survial_gameexpiretime;
	W_DeathMatchInfo_eUserStatus Survival_UserStatus;
	bool m_bGamePlayLater;
	int m_kindBadugiDay;
	int SurvivalUpdateRate;
	int m_LobbyUiState;
	vector<int> m_LobbyUiHistory;

	OptionDefineValue* m_pOptionValue;
	//bool m_bTutorial;
	//bool m_bSynopsis;

	bool m_RakingTutotial;
	bool m_ReplayTutotial;

	PlayerData*		m_pPlayerData;
	W_RecordInfo*	m_pRecordInfo;
	vector<W_CharacterInfo*>	m_pCharacterInfoList;
	vector<W_LetterInfo*>		m_pLetterInfoList;
	vector<W_QuestInfo*>		m_pQuestInfoList;
	vector<W_QuestInfo*>		m_pQuestDailyList;
	vector<W_QuestInfo*>		m_pQuestWeeklyList;
	vector<W_EventInfo*>		m_EventList;

	vector<W_ChannelInfo*>		m_pLobbyChannelList;
	vector<W_ChannelInfo*>		m_p7PokerChannelList;
	vector<W_ChannelInfo*>		m_pHighLowChannelList;
	vector<W_ChannelInfo*>		m_pBadukiChannelList;
	vector<W_ChannelInfo*>		m_pHoldemChannelList;

	vector<W_FriendInfo*>		m_SnsDataList;
	vector<W_FriendInfo*>		m_FriendDataList;
	vector<W_FriendInfo*>		m_RecommendDataList;
	vector<W_FriendInfo*>		m_RequestDataList;
	vector<int>					mRewardIds;

	vector<W_ReplaySaveInfo*>	m_ReplaySaveList;
	string						m_ReplayUserName;

	bool						m_hasTourGameInfo;
	bool						m_hasTourResultInfo;
	bool						m_hasSurvivalGameInfo;
	bool						m_IsSurvivalReservated;
	
	W_TourOfInfo*				m_TourOfInfo;

	bool						m_bSurvivalTimeUpdate;
	W_DeathMatchOfInfo*			m_SurvivalOfInfo;

	int64						m_nTotalRankerCount;
	W_RankInfo*					m_pMyRankInfo;
	vector<W_RankInfo*>			m_RankInfoList;

	vector<RoomInfo*>			m_RoomInfoList;
	int32						m_curPage;
	int32						m_curCount;
	int32						m_TotalDataCount;
	int32						m_TotalPage;

	int32	m_SlotMachineIcon[3];
	W_RewardInfo* m_SlotMachineRewardInfo;
	W_RewardInfo SurvivalRewardinfo;
	int64 m_EnterGameRoomBigPotMoney1;
	int64 m_EnterGameRoomBigPotMoney2;
	int64 m_EnterGameRoomBettingMaxMoney;
	int32 m_RoomId;
	int32 m_Grade;
	int32 m_BettingRule;
	int64 m_seedMoney;

	bool m_IsSelectRoom;
	int32 m_GameMode;
	int m_seasonId;
	int m_TournamentId;		//Deathmatch & Tournament ����
	int m_TournamentStep;
	int m_TournamentStatus;
	int mTourSelectIndex;
	int mTourStep;
	string m_TournamentIp;
	int32 m_TournamentPort;

	GameRoomInfo* m_GameRoomInfo;
	
	int m_GameSceneLoadStatus;
	int m_UpdateUserEndProcess;
	AccountCreateInfo			m_accountCreateInfo;
	CustomPopupPanel * m_pChannelListPanel;

	eLoginType m_LoginType;

	// temp variable. Please delete after traditional holdem complete!!!
	bool m_isTraditionalHoldem;

	bool IsCustum = false;
private :
	bool _checkFile(const string& path);
	void _readFile(const string& path);
	void _writeFile(const string& path);
	void _makeHash();

	
	int	m_ConnChannelId = -1;			// ������ ä��
	int m_ConnRoomId;					// ������ �� ��ȣ
	std::string m_Hash;
	std::string m_Path;
	W_GameData* mGameData;

	double m_PlayingTime;

	int64	m_ReplaySeqID;			// ���÷��� ������ ���̵�

	GamePutOutType mPutOutType;		// ���� ����

	
public:
	std::string getHash() { return m_Hash; }
	double getPlayingTime() { return m_PlayingTime; }
	std::string GetChannelGradeName(int grade);
	//void SetLobbyUIState(int _state);
	int CheckNickname(string str, int size);
	void CheckSurvivalPopup();
	void CheckSurvivalPreAlert();
	void InitAccountCreateInfo() {
		m_accountCreateInfo.nickname = "";
		m_accountCreateInfo.characterIdx = -1;
	}

	void SetAccountNickname(std::string nickname)
	{
		m_accountCreateInfo.nickname = nickname;
	}

	void SetAccountCharacter(int idx)
	{
		m_accountCreateInfo.characterIdx = idx;
	}

	AccountCreateInfo * GetAccountCreateInfo()
	{
		return &m_accountCreateInfo;
	}

	void SetPutOut(GamePutOutType value) { mPutOutType = value; }
	GamePutOutType getPutOut() { return mPutOutType; }
	
	std::string GetTimeString(int64 _remain, bool _noSec = true);
	std::string GetShortTimeString(int64 _remain);
	std::string GetRemainTime(int64 _remainTime, bool isFull, bool useSec = true , bool useRemainText = true);
	
	int GetConnRoomId() { return m_ConnRoomId;  }
	void SetConnRoomId(int roomidx) { m_ConnRoomId = roomidx; }
	//void SaveSynopsisStep();
	int CheckText(string str, int size);
	//void ShowChannelRoomList();

	
	Panel * BuyMessageCaller;
	Panel * m_WebViewPanel;
	string NoticePanelDesc = "";
public:
	bool m_bHistoryProcess;
	std::vector<int> m_uiHistoryList;

	void RemoveHistoryState();
	void HistoryStatePush(int _state);
	int HistoryPop();
	bool IsFriendsChannel();
	void OpenUrl(string url);
	void openAdultUrl(string token_version_id, string enc_data, string integrity_value);
	void CloseUrl();
	void HideUrl();
	void ShowUrl();
	std::string GetParamUrl(std::string& url);
	void ShowCustomWebview(WebPageType type);
	bool IsPushCustomWebview();
	void closeCustomView();
	void SaveRankingTutorialComplate();
	void SaveReplayTutorialComplate();
	void CloseTopSimplePopup();
	void CloseTopCoustomPopup();
	void CloseTopAccountPopup();
	
	void CloseSelectCharactePopup();
	void MoveToHistoryState(int _state);
	void MoveToUiState(int _state);
	void RemoveTournamentOfInfo();
	void RemoveSurvivalOfInfo();

	void RemoveGameRoomInfo();


	//tournament
	bool m_bTournamentEnd;
	bool m_bDeathmatchEnd;

	void CheckTournamentEnd();
	void CheckDeathmatchEnd();
	//void FadeoutLobby(float _delay);
	//void FadeinLobby(float _delay);

	bool LoadFileImage(std::string _userId, std::string _url, DOWNLOAD_FILE_TYPE imgType, Widget * _image, bool isDownload = true, std::string _folderName = "", int _index = -1);
	time_t GetNowTime();
	void AsyncTime(int64 ServerTime);
	int64 NowTime = -1;
	int64 Async_ServerTime = -1;
	int64 Async_ClientTime = -1;
	int AsyncDiff = -1;
	float AsyncDelta = -1;
public:
	std::string m_FacebookUserName;
	std::string m_FacebookUserId;
	std::string m_FacebookUserEmail;
	std::string m_FacebookUserPhotoUrl;

	typedef std::vector<std::vector<W_ModelData>> ModelShopList;
	ModelShopList				m_ModelShopList_MAXIM; 
	ModelShopList				m_ModelShopList_RACING;

	std::vector<W_ModelTabInfo*> InvenTapInfo_MAXIM; //
	std::vector<W_ModelTabInfo*> InvenTapInfo_RACING; //
	std::vector<W_DisplayModelData>	TitleModel_MAXIM;
	std::vector<W_DisplayModelData>	TitleModel_RACING;
	std::vector<W_InvenModelData>ModelInvenTableData;
	std::vector<std::vector<int>> BuyList_MAXIM;
	std::vector<std::vector<int>> BuyList_RACING;
	int64 mSlotEXNeedGold = 0;
	int64 mTapEXNeedGold = 0;
	int mMaxSlotIndex = 0;
	

	void SetFacebookUesrName(std::string _name);
	void SetFacebookUesrId(std::string _id);
	void SetFacebookUesrEmail(std::string _email);
	void SetFacebookUesrPhotoUrl(std::string _url);

	void ResetSurvivalLeftTime();
	void UpdateSurvivalLeftTime(float _dt);
	void SetSelectedLeftGameTime(double _second);
	void SetSelectedGameEnterTime(double _second);
	int64 GetSuvivalGameEntertimeLeft();
	int64 GetSuvivalLefttime();
	std::string GetStringSuvivalLefttime();
	int getTicketCount(int _ticketId);
	W_DisplayModelData FindTitleModel(int idx, TAB_TYPE tapType = MAXIM_TAB);
	W_ModelData FindShopModel(int modelId, TAB_TYPE tapType = MAXIM_TAB);
	W_ModelData FindShopModel(int tid, int subidx, TAB_TYPE tapType = MAXIM_TAB);
	void setModel(); //init Player Model Data , no more needed anymore
	bool hasModel(int tIdx,int id, TAB_TYPE tapType = MAXIM_TAB); //check that whether player has model, need to edit
	std::vector<std::vector<int>> getModelList(TAB_TYPE tabtype); //get Player Model Data pointer;
	bool hasSlot(int tapIdx,int idx = -1, TAB_TYPE tapType = MAXIM_TAB); //check does player has enough slot to purchase
	bool hasTap(int idx = -1, TAB_TYPE tapType = MAXIM_TAB);
	int getModelInfo(int id, ModelInfo val);
private:
	float m_fTimeSecond;
	int64 m_PastTime;
	double m_selectedGameTime;
	double m_selectedGameEnterTime;

	void DeleteImageFolder();
	void DeleteStaticImage();
	void createImageFolder();


public:
	W_RecordSeasonInfo* getRecordSeasonInfo();
	void setRecordSeasonInfo(const W_RecordSeasonInfo& recordSeasonInfo);
	W_RecordDeathMatchInfo* getRecordDeathMatchInfo();
	void setRecordDeathMatchInfo(const W_RecordDeathMatchInfo& recordDeathMatchInfo);
	W_AttendSevenInfo* getAttendSevenInfo();
	void setAttendSevenInfo(const W_AttendSevenInfo& attendSevenInfo);

	const W_PlayerInfo& getPlayerInfo();
	void setPlayerInfo(const W_PlayerInfo& playerInfo);

	W_UserInfo* getUserInfo();
	void setUserInfo(const W_UserInfo& userInfo);

	W_AttendSevenData getAttendSevenData(int idx);

	//���� ��ǰ ����
	double getJackPotLimitedTime();
	double getMadeLimitedTime();
	bool isActivateLimitedTime(W_LimitShopData_eLimitType limitType);
	bool isActivateShopInfo(W_LimitShopData_eLimitType limitType);
	void setLimitShopInfo(const W_LimitShopInfo limitShopInfo);
	//��Ŀ ���
	void pokerResultMade(int madeResult);
	void updateLimitedShop(float dt);

	bool isActivateLimitedBuffer(W_LimitShopData_eLimitType limitType);	//���� ���ൿ�� ������ �ִٰ�
	void initLimitedBuffer();	//�κ�ȭ�� ������ â�� �Ѹ���.

	void setTicketStackIndex(int index) {
		mTicketStackIndex = index;
	}

	int getTicketStackIndex() { return mTicketStackIndex; }

	void setTicketStepIndex(int index) {
		mTicketStepIndex = index;
	}

	int getTicketStepIndex() { return mTicketStepIndex; }

	float getBeforeReputeRatio() { return mBeforeRatioRepute; }
	void setBeforeReputeRatio(float ratio){
		mBeforeRatioRepute = ratio;
	}

	int getBeforeRepute() { return mBeforeRepute; }
	void setBeforeRepute(int repute) {
		mBeforeRepute = repute;
	}

	bool isDisplayTimeAni() { return mPlayTimeAni; }
	void setDisplayTimeAni(bool play) {
		mPlayTimeAni = play;
	}

	int getPlayTime() { return mPlayTimeHour; }

	void setPlayerOut(bool flag) {
		mFightSceneChange_PlayerOut = flag;
	}

	bool isPlayerOut() {
		return mFightSceneChange_PlayerOut;
	}

	void setPassward(string passwd) {
		mGamePassward = passwd;
	}

	string getPassward() {
		return mGamePassward;
	}

	int getGameKind() {
		return m_SelectedGameKind;
	}

	string GetGAID();

	void setGameKind(int kind);
	bool CanDisplay(string StartDt, string EndDt);
	tm StringToTime(string timeStr);
	bool isLaterThanCurrent(tm Current, tm Target);
private:
	W_RecordSeasonInfo* mRecordSeasonInfo;
	W_RecordDeathMatchInfo* mRecordDeathMatchInfo;
	W_AttendSevenInfo* mAttendSevenInfo;	
	W_UserInfo* mUserInfo;

	bool mActivateJackpot;
	bool mActivateMade;
	int mTicketStackIndex;
	int mTicketStepIndex;
	int mBeforeRepute;
	float mBeforeRatioRepute;
	string GAID;
	double mPlayTime;	//������ �ð�
	bool mPlayTimeAni;	//�ִ� ������� �Ѵ�.
	int mPlayTimeHour;

	bool mFightSceneChange_PlayerOut;

	string mGamePassward;
	int m_SelectedGameKind;
	
};