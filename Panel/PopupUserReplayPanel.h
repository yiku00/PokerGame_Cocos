#pragma once

#include "NxFramework.h"

#define USER_REPLAY_CELL_MAX 8
#define USER_REPLAY_CELL_HEIGHT 88.f

class PopupUserReplayPanel : public Panel, public Button::Listener
{
public:
	PopupUserReplayPanel();
	virtual ~PopupUserReplayPanel();

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
	void ClickTapButton(int _idx);
	virtual bool handling(STCMD &stCmd);
	void update(float dt);

	void SetReplayList();
	void ClearReplayList();
	void SetUserReplyBoxTitle(string _title);

private:
	void ScrollViewOffsetProcess(float _dt);

	bool cellTouchStart(const CCPoint& tableTouchPoint);
	bool cellTouchCancel(const CCPoint& tableTouchPoint);
	bool cellTouch(const CCPoint& tableTouchPoint);
	void cellTouchEnd(CCNode* node);
	void CreateReplayCell(int _size);
	void UpdateReplayCell(int _toIdx, int _dstIdx);
	void ShowReplayInfoPanel(int _idx, int _type);

public:
	bool mLoginProcess;

	int m_ViewDataIndex;
	CCScrollView* m_pReplayListView;
	CCLayer* m_pReplayListContainer;

	bool m_bTouchCancel;

	CCPoint m_ShowPosition;
	CCPoint m_HidePosition;

	Panel* m_ListCell[USER_REPLAY_CELL_MAX];
	CCLabelBMFont* m_ReplayRankLabel[USER_REPLAY_CELL_MAX];

	int m_TapIndex;
	Button* m_TapButton[3];

	Button* m_ReplayGiftBtn;

	//TextField* m_pTextField;
	//int m_SelectItem;

	//SkelObject* m_pShadowBg;
	Button* m_WeekGiftBtn;

	int m_CellIndex;
	bool m_bMovingCell;
	float m_fMoveG;
};
