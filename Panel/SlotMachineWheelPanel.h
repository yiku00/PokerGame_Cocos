#pragma once

#include "NxFramework.h"

class SlotMachineWheelPanel : public Panel, public Button::Listener, public SkelObject::EventListener
{	
public:

	SlotMachineWheelPanel();
	virtual ~SlotMachineWheelPanel();
	void InitPanel();

// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onKeypadKeyPressed(EventKeyboard::KeyCode  keyCode, Event* /*event*/);
	virtual bool handling(STCMD &stCmd);
	virtual void onEnter() override;

// SkelObject::EventListener
	virtual void onEvent(int trackIdx, spEvent* event);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);

	void InitImage();
#ifdef SLOT_WHEEL
	void InitButton();
#endif
	void PlaySlotMachine();
	void EndSlotMachine();
	bool isPossible();
#ifdef SLOT_WHEEL
	
	void InitSlotIncon();

	string GetSlotIconName(int _type, bool _move);
	void RollIcon(int _num);
	void UpdateSlotIcon(float dt);

	void StopRollLeft();
	void StopRollCenter();
	void StopRollRight();
	void SetSlotMachine();
#endif
	void StartGetEvent();
	void UpdateGetEvent(float _dt);

	void SetPlayCount(int recount = 0);
#ifdef SLOT_WHEEL
	void SetRewardEffect(int _index);
#endif
private:
#ifdef SLOT_WHEEL
	void UpdateRandomEffect(float dt);
	void UpdateLeftSlot(float dt);
	void UpdateCenterSlot(float dt);
	void UpdateRightSlot(float dt);
	
	bool isAllStopSlot();
#endif
	void SendSlotMachineSeq();
	void createGoldChip(int _count, float _term, float _delay);

	void setUseSkipBtn(bool use);
public:
	bool mLoginProcess;
	bool m_GamePlaying;
	bool m_bGetEvent;
#ifdef SLOT_WHEEL
	float m_RandomEffectCount;
#endif
	int m_CanCount;
#ifdef SLOT_WHEEL
	Button* m_pLeverBall;
	CCPoint m_LeverBallPosition;

	SkelObject* m_pConnecter;
	CCPoint m_ConnecterPosition;

	SkelObject* m_pLever;
	CCPoint m_LeverPosition;
	float m_fLeverScale;
#endif
	CCClippingNode* m_maskImage;
	CCSprite* m_pStencilImage;

	Panel* mMainPanel;
#ifdef SLOT_WHEEL
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
#endif
	Nx::Label* m_MyGold;
	Nx::Label* m_MyChip;
	Nx::Label* mMyCash;
	Nx::Label* m_PlayChip;
	Nx::Label* mPlayCash;
	CCLabelBMFont* m_GetGold;
	CCLabelBMFont* m_CanPlayCount;

	int64 m_CurGold;
	int64 m_TargetGold;
#ifdef SLOT_WHEEL
	SkelObject* m_pScoreEffect[7];
	SkelObject* m_pLightEffect[6];
#endif
	SkelObject* m_pSlotGoldEffect;
	SkelObject* m_pSlotStarEffect;
	SkelObject* mVictoryEffect;

	SkelObject* mStoneEffect1;
	SkelObject* mStoneEffect2;
	SkelObject* mStoneEffect3;


	SkelObject* mSlotLamp;
	Widget* mStartNotiAni;			// 레버 이펙트

	Button* mTypeSelectBtn;
#ifdef SLOT_WHEEL
	Label* mReward1;	//500억골드
	Label* mReward2;	//200억골드
	Label* mReward3;	//100억골드
	Label* mReward4;	//50억골드
	Label* mReward5;	//20억골드
	Label* mReward6;	//10억골드
	Label* mReward7;	//5억골드
#endif
	Button* mSkipBtn;	
	bool mSkip;

	Nx::Label* mGoldTab;
	Nx::Label* mGoldTabUnder;
	Nx::Label* mNeedResoutceTab;
	Nx::Label* mNeedResoutceTabUnder;
	Nx::Label* mGameOppertunity;
	Nx::Label* mGameOppertunityUnder;
	Nx::Label* mGameName;

	private:
		Widget* m_pWheelSpin;
		Widget* m_pWheelSpinSector;
		Widget* m_pWheelPointer;

		int m_fRewardPoint;

		Button* m_pStartWheelSpinBtn;

		void OnStartWheelSpin();
		void OnEndWheelSpin();
		void OnSelectEvent();
};
