/********************************************************************
file name:	BettingHighLowPanel.h

purpose:	하이 로우 하단 버튽 ( 로우 , 스윙 , 하이 )
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "TypeDefine.pb.h"
#include "GameRoomInfo.h"

class Game;
class FightScene;
class BettingHighLowPanel : public Panel, public Button::Listener
{
public:
	BettingHighLowPanel();
	virtual ~BettingHighLowPanel();

public:
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onClicked(const string& name);
	

public:
	void showPanel();
	void hidePanel();

	void Init();

	void InitHighLowButton();
	void ShowHighLowButton();
	void DisableHighLowButton(int idx);

private:
	void _initData();
	void _initPanel();
	void _setParentPanel();

	HighLowBettingKind GetHighLowKind(const string& name);
	void SetPressButton(int kind);
	void SetReleaseButton(int kind);

private:
	Panel* mParentPanel;
	Panel* mMainPanel;
	FightScene* mCurrentScene;

	Button * mHighLowButton[HIGHLOW_KIND_CNT];

	bool mTouchEnable;
};