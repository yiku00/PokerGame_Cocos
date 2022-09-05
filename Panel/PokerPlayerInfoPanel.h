/********************************************************************
file name:	PokerPlayerInfoPanel.h

purpose:	로비 기본 버튼 UI ( 상점 , 우편함 , 등등 버튼 UI + 카지노입장 시즌 토너먼트 버튼
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "PokerPlayerInfoHelper.h"
#include "GameRoomInfo.h"

class PokerPlayerInfoMyPanel;
class PokerPlayerInfoRightPanel;
class PokerPlayerInfoLeftPanel;
class PokerPlayerInfoCommonPanel;

class PokerPlayerInfoPanel : public Panel
{
	
public:
	PokerPlayerInfoPanel();
	virtual ~PokerPlayerInfoPanel(); 
	
public:
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

public:
	void initPanel();
	void drawPlayerInfo();

	void addMyPanel();
	
	void addLeftOnePanel();
	void addLeftTwoPanel();

	void addRigthOnePanel();
	void addRigthTwoPanel();

	void SetPlayerPanel();
	void ShowPlayerPanel(int _index, bool _visible);

	void setBettingPanel();

	Panel* GetPlayerPanel(int _po);
	PokerPlayerInfoCommonPanel* GetPlayerCommonPanel(int _po);
	PokerPlayerInfoPanel * GetPlayerInfoPanel();

	void SetCharacter(int _index, int _charaId, bool _visible = true);
	//void ChangeCharacterMotion(int _index, int _AniIndex);
	void RemoveCharacter(int _index);
	void RemoveAllCharacter();

	void SetUserInfoPanelUpdate(int po, RoomUserData * data);
	void SetUserInfoPanelInit(int po);
	void SetAllUserGameStartPlayerInfo();

	void SetAllUserBettingAmountInit();

	PokerPlayerInfoCommonPanel * GetPlayerCommonPanelWithIndex(int idx);
	Panel* GetPlayTextBubblePanel(int _po);
	void HideTextBubblePanel(int _po);
	void ClearAllPanelAction();
	void HideTextBubble(CCNode* _node);

public:
	PlayerInfoContainer& getPlayerInfos() { return mPlayerInfos; }
	
private:
	void _initData();
	void _setParentPanel();
	void _collectPlayerInfos();

private:
	PokerPlayerInfoMyPanel* mPlayerInfoPanelMy;
	PokerPlayerInfoLeftPanel* mPlayerLeftPanelOne;
	PokerPlayerInfoLeftPanel* mPlayerLeftPanelTwo;
	PokerPlayerInfoRightPanel* mPlayerRightPanelOne;
	PokerPlayerInfoRightPanel* mPlayerRightPanelTwo;

	SkelObject* m_pCharacter[GAME_USER_MAX];
	SkelObject* m_pCharacterUnder[GAME_USER_MAX];
	Panel*		m_pEmotiBubble[GAME_USER_MAX];

	//위에 있는 패널들이 우측 상단 플레이어부터 시계방향으로 넣어지게된다.
	PlayerInfoContainer mPlayerInfos;
	
	Panel* mParentPanel;
};