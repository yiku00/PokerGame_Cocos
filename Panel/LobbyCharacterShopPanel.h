/********************************************************************
filename: 	LobbyCharacterShopPanel.h

purpose:	로비에서 캐릭터 구매창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "GoodsPanel.h"

#define LOBBY_CHARACTER_CELL_MAX 7
#define CHARACTER_CELL_WIDTH 240.f
#define CHARACTER_CELL_HEIGHT 386.f

class LobbyCharacterShopPanel : public Panel, public Button::Listener
{
public:
	LobbyCharacterShopPanel();
	virtual ~LobbyCharacterShopPanel();

	void InitPanel();
	void InitImage();
	void initButton();
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
    void resume();
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);

	void InitCharacterList();
	void CreateCharacterCell(int _count);
	void UpdateCharacterCell(int _toIdx, int _dstIdx);
	void RemoveCharacterCellList();

	void UpdateCellMoveBy(float _move);
	void UpdateCell();
private:
	void setTapOn(int _index);
	void SetBuyPopup(int _index);
public:
	bool mLoginProcess;
	int m_tapIndex;

	Panel* m_TapBtnPanel[2];
	Button* m_TapButton[2];

	CCLayer* m_pListContainer;
	CCScrollView* m_pListView;
	GoodsPanel* m_ListCell[LOBBY_CHARACTER_CELL_MAX];

	int m_curChannelIndex;
	int m_totalDataCount;
	CCPoint m_offset;
private:
	bool m_bCancelTouch;
	bool m_bTouchEnd;
	bool m_bMoveAccel;
	float m_moveG;
	float m_MovePoint;

};