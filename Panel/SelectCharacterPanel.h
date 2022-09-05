#pragma once

#include "NxFramework.h"

#define CHARACTER_CELL_SIZE 255.f
#define CHARACTER_CELL_MAX 12

class SelectCharacterPanel : public Panel, public Button::Listener
{
public:
	SelectCharacterPanel();
	virtual ~SelectCharacterPanel();

	void InitPanel();
	void InitImage();
	void initButton();
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onEnter() override;

    void resume();
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);

	void SetSelectList();
	void ClearSelectList();

	void CreateCharacterCell(int _count);
	void UpdateCharacterCell(int _cellIndex, int _dataIndex);
	void DrawCharacterCell(Panel * chpanel, int idx, bool isAllDraw);
	Panel * GetMainPanel();
	void clearThisPanel();
	void ShowPanel(bool isVisible);
	void SetCharacterCellUse(Panel * chpanel, int charIdx);
	void ChangeCharacterCellUse();
	void ScrollViewOffsetProcess();
public:
	bool mLoginProcess;

	int m_ViewDataIndex;
	CCScrollView* m_pReplayListView;
	CCLayer* m_pReplayListContainer;

	bool m_bTouchCancel;

	float m_ButtonPosX;
	float m_ButtonMaxPosX;
	CCPoint m_ButtonStartPosition;

	Button* m_bankButton;
	Button* m_CheckButton;

	CCScrollView* m_pSelectListView;
	CCLayer* m_pSelectListContainer;
	Panel* m_pListCell[CHARACTER_CELL_MAX];

	Panel  * mMainPanel;

	int mSelectIdx;
};
