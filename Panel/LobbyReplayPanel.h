/********************************************************************
file name:	LobbyReplayPanel.h

purpose:	로비씬에서 다시보기 버튼 눌렀을때  다시 보기 관련 구조창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "BTabButtonPanel.h"
#include "TabButtonPanel.h"
#include "RpBarPanel.h"

#define REPLAY_CELL_MAX 8

class LobbyReplayPanel : public Panel, public Button::Listener, public TextField::Listener , public Nx::Layer::Listener
{
public:
	LobbyReplayPanel();
	virtual ~LobbyReplayPanel();

	void InitPanel();
	void InitImage();
	void initButton();

public:
	virtual void onLayerMessage(const string& msg);
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onEnter() override;

//TextField::Listener
	virtual void onDetached();
    void resume();
public:
	void ClickTapButton(int _idx);
	virtual bool handling(STCMD &stCmd);
	void update(float dt);
	void ShowReplayPanel();
	void HideReplayPanel();
	void ShowReplayUi();
	void HideReplayUi();
	void ShowReplayTitie();
	void HideReplayTitie();

	void SetReplayList();
	void ClearReplayList();

	void SortReplayData(int _type);

private:
	void ScrollViewOffsetProcess(float _dt);

	bool cellTouchStart(const CCPoint& tableTouchPoint);
	bool cellTouchCancel(const CCPoint& tableTouchPoint);
	bool cellTouch(const CCPoint& tableTouchPoint);
	void cellTouchEnd(CCNode* node);
	//Panel* CreateReplayCell(int _i);

	void CreateCell(int _size);
	void UpdateReplayCell(int _toIdx, int _dstIdx);
	void ShowGiftList();
	void ShowReplayInfoPanel(int _idx, int _type);
public:
	bool mLoginProcess;
	
	int m_nSortType;
	int m_ViewDataIndex;
	CCScrollView* m_pReplayListView;
	CCLayer* m_pReplayListContainer;

	bool m_bTouchCancel;

	//CCPoint m_ShowPosition;
	//CCPoint m_HidePosition;

	RpBarPanel* m_ListCell[REPLAY_CELL_MAX];
	CCLabelBMFont* m_ReplayRankLabel[REPLAY_CELL_MAX];

	int m_TapIndex;	
	TabButtonPanel* m_TapButton[3];

	TextField* m_pTextField;
	int m_SelectItem;

	//SkelObject* m_pShadowBg;
	//Label* m_RankingCount;
	//Label* m_RankingMaxCount;

	Button* m_WeekGiftBtn;

	int m_CellIndex;
	bool m_bMovingCell;
	float m_fMoveG;

	CCSize mCellSize;
};
