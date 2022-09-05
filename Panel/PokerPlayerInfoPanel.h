/********************************************************************
file name:	PokerPlayerInfoPanel.h

purpose:	�κ� �⺻ ��ư UI ( ���� , ������ , ��� ��ư UI + ī�������� ���� ��ʸ�Ʈ ��ư
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

	//���� �ִ� �гε��� ���� ��� �÷��̾���� �ð�������� �־����Եȴ�.
	PlayerInfoContainer mPlayerInfos;
	
	Panel* mParentPanel;
};