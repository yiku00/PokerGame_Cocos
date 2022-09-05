/********************************************************************
file name:	PokerResultPanel.h

purpose:	게임 오른쪽 하단에 게임 결과창 , 저장하기 버튼 1등 누가 얼마 등등 나열된 창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "GameRoomInfo.h"
#include "PokerPlayerResultPanel.h"

class PokerPlayerResultPanel;

class PokerResultPanel : public Panel, public SkelObject::Listener, public Button::Listener
{
	
public:
	PokerResultPanel();
	virtual ~PokerResultPanel(); 
	
public:
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onAnimationEnded(const string& ani);

	virtual void onClicked(const string& buttonName);

public:
	void initPanel();

	void addPlayerResultPanel();
	void ShowPlayerResultPanel(int _index, bool _visible);
	void SetData(int _index, GameKind gameKind, WinKind winKind, string& nickname, bool isMine, int highJokboKind, int lowJokboKind, int64 inoutGameMoney);
	void SetPlayerResultPaenlVisible(int _index, bool isVisible);
	void SetPlayerResultPaenlAllVisible(bool isVisible);
	void SetPlayerResultPanelAllInit();

	void SetTurnOnReplayButton();
	void SetTurnOffReplayButton();

	void ShowPanel();

	void setMadeResult(int madeJokbo);
		

private:
	void _initData();
	void _setParentPanel();
	void SaveReplay();
private:
	PokerPlayerResultPanel * mPlayerResultPanel[GAME_USER_MAX];

	SkelObject * m_Background;
	
	Panel* mParentPanel;
	Panel* mMainPanel;

	bool m_isReplayLoad;

	int mMadeResult;	//메이드이다.
};