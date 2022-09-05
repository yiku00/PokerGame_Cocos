/********************************************************************
file name:	LobbyFriendPanel.h

purpose:	로비씬에서 미션 버튼 눌렀을때  미션 관련 구조창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "W_FriendInfo.pb.h"
#include "TockInvtationPanel.h"
#include "NotiWidget.h"

#define MISSION_MAX_COUNT 50

#define  MISSION_CELL_MAX 8

class LobbyMissionPanel : public Panel, public Button::Listener
{
	typedef vector<NotiWidget*> NotiWidgetContainer;
public:
	LobbyMissionPanel();
	virtual ~LobbyMissionPanel();

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
	virtual void onEnter() override;
public:
	void ClickTapButton(int _idx);
	virtual bool handling(STCMD &stCmd);
	void update(float dt);
	void ShowMissionPanel();
	void HideMissionPanel();
	void ShowMissionUi();
	void HideMissionUi();
	void ShowMissionTitie();
	void HideMissionTitie();

	void SetMissionlList();
	void ClearMissionList();

	void onCloseRewardPopupPanel();

private:
	void ScrollViewOffsetProcess(float _dt);

	bool cellTouchStart(const CCPoint& tableTouchPoint);
	bool cellTouchCancel(const CCPoint& tableTouchPoint);
	bool cellTouch(const CCPoint& tableTouchPoint);
	void cellTouchEnd(CCNode* node);


	//Panel* CreateMissionCell(int _i);
	void CreateCell(int _size);
	void UpdateMissionCell(int _toIdx, int _dstIdx);
	void UpdateEventCell(int _toIdx, int _dstIdx);
	
	void SetProgressBar(int _cellIdx, float _per);
	void updateNotiWidget();

public:
	bool mLoginProcess;

	int m_ViewDataIndex;
	CCScrollView* m_pMissionListView;
	CCLayer* m_pMissionListContainer;

	bool m_bTouchCancel;

	//CCPoint m_ShowPosition;
	//CCPoint m_HidePosition;

	//Button* m_TapBtn[3];
	Panel* m_TapBtnPanel[2];
	Panel* m_BtnPanel;

	Panel* m_ListCell[MISSION_CELL_MAX];
	Panel* m_CellBtnPanel[MISSION_CELL_MAX];

	int m_TapIndex;

	SkelObject* m_MissionTitleLabel;
	SkelObject* m_MissionTitleMark;
	SkelObject* m_MissionTitleBg;
	SkelObject* m_ShadowBg;

	int m_CompleteCount;
	Nx::Label* m_MissionCount;
	Nx::Label* m_MissionMaxCount;

	int m_CellIndex;
	bool m_bMovingCell;
	float m_fMoveG;
	CCSize mCellSize;

	NotiWidgetContainer mNotiWidgets;
};