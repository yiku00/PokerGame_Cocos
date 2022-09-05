#pragma once

#include "PlayerData.h"
#include "BettingRes.pb.h"
#include "CardManager.h"

class PokerCardWidget;
class UserJokboInfo;

enum EmotionType
{
	EMOTION_NO = 0,
	EMOTION_ANGRY,
	EMOTION_GOOD,
	EMOTION_CELEBRATE,
	EMOTION_LAUGH,
	EMOTION_PLEASURE,
	EMOTION_HURRY,
	EMOTION_SADNESS,
	EMOTION_SORRY,
	EMOTION_SURPRIZE,
	EMOTION_THANKS,
};


enum CharacterAniKind
{
	RESULT_ALLIN = 0,
	BET_BBING,
	BET_BIGFOLD,
	BET_BIG_RAISE,
	BET_CHECK,
	BET_RAISE,
	DIE_ACT,
	DIE_IDLE,
	GESTURE_ANGRY,
	GESTURE_CELEBRATE,
	GESTURE_GOOD,
	GESTURE_HURRY,
	GESTURE_LAUGH,
	GESTURE_PLEASURE,
	GESTURE_SADNESS,
	GESTURE_SORRY,
	GESTURE_SURPRIZE,
	GESTURE_THANKS,
	IDLE,
	IDLE_ACT1,
	IDLE_ACT2,
	IDLE_STAND,
	IDLE_STAND_ACT1,
	IDLE_STAND_ACT2,
	LOSE_BIG,
	LOSE_SMALL,
	REACT_MADE,
	THINK1,
	THINK2,
	WIN_BIG,
	WIN_SMALL,
	ANI_KIND_MAX
};

enum CharacterEfxKind
{
	EFX_BBING = 0,
	EFX_CALL,
	EFX_CHECK,
	EFX_DDADANG,
	EFX_QUARTER,
	EFX_HALF,
	EFX_DIE,
	EFX_HIGH,
	EFX_LOW,
	EFX_SWING,
	EFX_ALLIN,
	EFX_ANGRY,
	EFX_CHEER,
	EFX_GOOD,
	EFX_HURRY,
	EFX_LAUGH,
	EFX_PLEASURE,
	EFX_SADNESS,
	EFX_SORRY,
	EFX_SURPRIZE,
	EFX_THANKS,
	EFX_MADE,
	EFX_THINK1,
	EFX_THINK2,
	EFX_BOX,
	EFX_ENTER1,
	EFX_ENTER2,
	EFX_LOSEBIG,
	EFX_LOSESMALL,
	EFX_ONECARD,
	EFX_PASS,
	EFX_PR1,
	EFX_PR2,
	EFX_THREECARD,
	EFX_TWOCARD,
	EFX_WINBIG,
	EFX_WINSMALL,
	EFX_CHARACTER_KIND_MAX
};


class RoomUserData : public SkelObject::Listener , public SkelObject::EventListener
{
public:
	PlayerData*		m_pPlayerData;		//�÷��̾� �⺻ ����.
	CardManager*	m_pCardManager;		//���� ī�� ����.
	UserJokboInfo*	m_pJokboInfo;		//ī�� ���� �Ǻ�.

	BettingKind		m_BettingKind;		//���� ����.
	AllBetKind		m_AllBetKind;		// �ù� ����
	HighLowBettingKind m_HighLowBettingKind;		// ���̷ο� ���� ����
	int64			m_BettingMoney;		// �������� ���� �Ӵ�
	int64			m_TotalBettingMoney;	// ���� ������ �� ���� �Ӵ�

	bool			m_KickReady;		//���� ���� �����
	bool			m_OutReady;			//���� ������ ���
	bool			m_isMe;				//
	bool			m_bEmotionBlock;	//�̸�� ��
	PlayerStatus	m_State;
	
	int				m_PlayerOutResrvKind;	//������&���� ����

	int				m_Po;
	SkelObject*		m_pMyCharater;
	SkelObject*		m_pMyCharaterUnder;
	Panel*			m_pMyEmotiBubble;
	float			m_nMyCharacterTime;
	CharacterAniKind m_MyCharacterState;

	int				m_PotMoneyUpdateCount;

	bool			m_IsFriendRequest;
	bool			m_IsStatcsUpdated;
	int32			m_CurWin;
	int32			m_CurLose;
	int32			m_MadeCount;
	int64			m_AcqMoney;
private:
	CCPoint			m_ChipStartPos;
	CCPoint			m_ChipEndPos;
	int64			m_ChipAmount;

public:
	RoomUserData();
	~RoomUserData();
	void Init();

	void SetMe(bool _isMe);
	void Update(float dt);

	virtual void onAnimationStarted(const string& ani) {}
	virtual void onAnimationEnded(const string& ani);
	virtual void onEvent(int trackIdx, spEvent* event);
public:
	void InitData();		//�뿡�� ������ ���� �� ȣ��.

	void AddCard(int _number, int _kind, bool _showBack = false, bool _Action = true, float _delay = 0.f);
	void EraseCard(int _idx);
	void ChangeCard(int _idx, int _number, int _kind, bool isPaeShow);
	void SelectOffCard(int _idx, bool _cancel = false);
	void SelectOnCard(int _offCard, int _onCard);
	void ClearCardList();
	void LastCardCheck(bool _triger);

	void SetGameMoney(int64 gameMoney);
	void SetBetting(BettingRes * res);
	void SetHighLowBettingKind(HighLowBettingKind _kind) { m_HighLowBettingKind = _kind; }
	void SetPlayerStatus(PlayerStatus status);
	
	CardManager* GetCardManager() { return m_pCardManager; }

	int64 GetBettingMoney() { return m_BettingMoney;  }
	int64 GetTotalBettingMoney() { return m_TotalBettingMoney;  }

	PlayerStatus GetPlayerStatus() { return m_State;  }

	void SetBettingChipAmount(int64 _money) { m_ChipAmount = _money; }
	int GetUserTablePosition() { return GetCardManager()->m_UserIdx; }

	void ActionBettingChip(int64 _money);

	void SetBettingInfoInit(bool isAll) 
	{ 
		m_BettingMoney = 0;

		if (isAll)
			m_TotalBettingMoney = 0;
	}
	
	void SetCharacterPtr(SkelObject* _ptr, SkelObject* _ptrUnder, Panel* _pBubble);
	void SetCharacterPosition(CCPoint _position);
	void MoveCharacterPosition(CCPoint _moveTo, float _delay);
	void MoveCharacterAnimation();
	void MoveEndCharacter();
	void PlayCharacterAnimation(CharacterAniKind _kind);
	void CheckBettingAnimaion(CharacterAniKind _kind);
	void PlayCharacterSound(CharacterEfxKind _kind);
	void CharacterText(CharacterEfxKind _kind);
	void HideTextBubble();

	float m_ThinkAniDelay;
	bool m_isPlayThinkAni;

	void PlayThinkAnimation(float _delay, bool _play = true);
	void PlayThink();

	void PresetJokboCard();
	void ShowHighJokboCheck();
	void ShowSwingJokboCheck();

	//void ShowHighJokboEffect();

	//Badugi
	bool m_bBadugiSortWait;
	float m_BadukiSortDelayTime;

	void BadugiAddCard(int _number, int _kind, bool _showBack = false, bool _Action = true, float _delay = 0.f);
	void BadugiSortCard(float _delay = 0.f);
	void SetBadugiSelectedCardEffect(float _delay = 0.f);
	void SelectBadugiRecommendCard();
	void ShowBadugiJokboCheck();
	void PlaySoundBadugiSelectChangeCard(int _count);

	//Holdem
	void ShowHoldemJokboCheck();

	void setMyCharacterVisible(bool visible);


	//InGameRoom
	bool m_bCharacterMoveEnd;
	float m_fDelayMoveEndTime;

	void setActionSpeed();	//�� ���� action ������

	bool isLastCardOpen();	//������ ī�� ����?

private:
	CCPoint m_moveToPosition;
	
};