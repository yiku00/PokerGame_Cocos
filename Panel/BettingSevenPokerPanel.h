/********************************************************************
file name:	BettingSevenPokerPanel.h

purpose:	세븐포커 하단 다이 , 삥 등을 고르는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "TypeDefine.pb.h"
#include "GameRoomInfo.h"
#include "NotiFocusPanel.h"

class Game;
class FightScene;
class BettingSevenPokerPanel : public Panel, public Button::Listener//, public SkelObject::Listener
{
public:
	BettingSevenPokerPanel();
	virtual ~BettingSevenPokerPanel();

public:
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	/*
	virtual void onAnimationStarted(const string& ani);
	virtual void onAnimationEnded(const string& ani);
	*/
	
	virtual void onClicked(const string& name);
	

public:
	void showPanel();
	void hidePanel();

	void Init();
	void InitCanBetting();
	void SetCanBetting(int kind, bool isCan);
	void SetBettingMoney(int64 quarterMoney, int64 halfMoney, int64 maxMoney);

	void SetEnableButton(int kind, bool isEnable, bool isSelect);
	void SetPressButton(int kind);
	void MovePanel(bool _isShow);

private:
	void _initData();
	void _initPanel();
	void _setParentPanel();

	BettingKind GetBettingKind(const string& name);
	void SetBetting(int number);
	
	

private:
	Panel* mParentPanel;
	Panel* mMainPanel;
	FightScene* mCurrentScene;

	Button * mBettingButton[BETTING_KIND_CNT];
	Nx::Label* m_BettingBtnText[BETTING_KIND_CNT];

	Nx::Label* mLabelHalfMoney;
	Nx::Label* mLabelQuarterMoney;
	Nx::Label* mLabelMaxBetMoney;
	SkelObject * mSkelHalfMoney;
	SkelObject * mSkelQuarterMoney;
	SkelObject * mSkelMaxBetMoney;

	CCPoint m_ShowPos;
	CCPoint m_HidePos;

	bool mTouchEnable;	
	string mNotiQuarterMoney;
	string mNotiHalfMoney;
	string mNotiMaxMoney;
};