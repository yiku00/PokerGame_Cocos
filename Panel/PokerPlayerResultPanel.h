#pragma once

#include "NxFramework.h"
#include "GameRoomInfo.h"

class PokerPlayerResultPanel : public Panel
{
	
public:
	PokerPlayerResultPanel();
	virtual ~PokerPlayerResultPanel();
	
public:
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	

public:
	void initPanel();
	void initPanel(Panel * mParent);
	void HidePanel();
	void ShowPanel();

	void SetWin(GameKind gameKind, WinKind winKind);
	void SetJokbo(WinKind winKind, int highJokboKind, int lowJokboKind, int _gamekind);
	void SetMoney(int64 inoutGameMoney);
	void InitData();
	void SetData(GameKind gameKind, WinKind winKind, string& nickname, bool isMine, int highJokboKind, int lowJokboKind, int64 inoutGameMoney);
private:
	void _initData();
	
	void _setParentPanel();

private:
	SkelObject  * mMyBar;
	Nx::Label		* mPlayerName;
	Nx::Label		* mJokbo;
	Nx::Label		* mGold;

	Panel		* mMainPanel;
	Panel		* mParentPanel;

	bool		m_IsDataInit;
};