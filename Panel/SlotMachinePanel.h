#pragma once

#include "NxFramework.h"

enum SloMachinetIconType
{
	apple = 1,
	lemon,
	clover,
	diamond,
	bar,
	seven,
	logo,
	SlotMachineIcon_max
};

enum SlotState
{
	SLOT_READY = 0,
	SLOT_ROLL,
	SLOT_STOP,
	SLOT_END,
};

class SlotMachinePanel : public Panel, public Button::Listener, public SkelObject::EventListener
{	
public:
	enum SLOT_TYPE {
		SLOT_NONE,
		SLOT_CHIP_TYPE,
		SLOT_RUBY_TYPE,
	};
	SlotMachinePanel(SLOT_TYPE slotType);
	virtual ~SlotMachinePanel();
	void InitPanel();

// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool handling(STCMD &stCmd);
	virtual void onEnter() override;

// SkelObject::EventListener
	virtual void onEvent(int trackIdx, spEvent* event);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);

	void InitImage();
	void InitButton();

	void PlaySlotMachine();
	void EndSlotMachine();

	void ReturnLever();
	void InitSlotIncon();

	string GetSlotIconName(int _type, bool _move);

	void RollIcon(int _num);
	void UpdateSlotIcon(float dt);

	void StopRollLeft();
	void StopRollCenter();
	void StopRollRight();
	
	void SetSlotMachine();

	void StartGetEvent();
	void UpdateGetEvent(float _dt);

	void SetPlayCount(int recount = 0);
	void SetRewardEffect(int _index);

private:
	void UpdateRandomEffect(float dt);
	void UpdateLeftSlot(float dt);
	void UpdateCenterSlot(float dt);
	void UpdateRightSlot(float dt);
	void SendSlotMachineSeq();
	bool isAllStopSlot();
	void createGoldChip(int _count, float _term, float _delay);

	void setUseSkipBtn(bool use);
public:
	bool mLoginProcess;
	bool m_GamePlaying;
	bool m_bGetEvent;

	float m_RandomEffectCount;

	int m_CanCount;

	Button* m_pLeverBall;
	CCPoint m_LeverBallPosition;

	SkelObject* m_pConnecter;
	CCPoint m_ConnecterPosition;

	SkelObject* m_pLever;
	CCPoint m_LeverPosition;
	float m_fLeverScale;

	CCClippingNode* m_maskImage;
	CCSprite* m_pStencilImage;

	Panel* mMainPanel;

	int m_nRollSlot[3];
	int m_RollStopKind[3];

	SkelObject* m_pSlotIconLeft[4];
	int			m_nLeftIconIdx[4];
	float		m_fLeftIconSpd;

	SkelObject* m_pSlotIconCenter[4];
	int			m_nCenterIconIdx[4];
	float		m_fCenterIconSpd;

	SkelObject* m_pSlotIconRight[4];
	int			m_nRightIconIdx[4];
	float		m_fRightIconSpd;

	CCScrollView* m_pSlotIconView;
	CCLayer* m_pSlotIconContainer;

	Nx::Label* m_MyGold;
	Nx::Label* m_MyChip;
	Nx::Label* mMyCash;
	Nx::Label* m_PlayChip;
	Nx::Label* mPlayCash;
	CCLabelBMFont* m_GetGold;
	CCLabelBMFont* m_CanPlayCount;

	int64 m_CurGold;
	int64 m_TargetGold;
	SkelObject* m_pScoreEffect[7];
	SkelObject* m_pLightEffect[6];
	
	SkelObject* m_pSlotGoldEffect;
	SkelObject* m_pSlotStarEffect;
	SkelObject* mVictoryEffect;

	SkelObject* mStoneEffect1;
	SkelObject* mStoneEffect2;
	SkelObject* mStoneEffect3;

	SkelObject* mSlotLamp;
	Widget* mStartNotiAni;
	SLOT_TYPE mSlotType;

	Button* mTypeSelectBtn;

	Nx::Label* mReward1;	//500억골드
	Nx::Label* mReward2;	//200억골드
	Nx::Label* mReward3;	//100억골드
	Nx::Label* mReward4;	//50억골드
	Nx::Label* mReward5;	//20억골드
	Nx::Label* mReward6;	//10억골드
	Nx::Label* mReward7;	//5억골드

	Button* mSkipBtn;	
	bool mSkip;

	Nx::Label* mGoldTab;
	Nx::Label* mGoldTabUnder;
	Nx::Label* mNeedResoutceTab;
	Nx::Label* mNeedResoutceTabUnder;
	Nx::Label* mGameOppertunity;
	Nx::Label* mGameOppertunityUnder;
	Nx::Label* mGameName;
};
