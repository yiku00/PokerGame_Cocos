/********************************************************************
file name:	LobbyLetterBoxPanel.h

purpose:	로비씬에서 우편함 버튼 눌렀을때  우편함 관련 구조창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "W_FriendInfo.pb.h"
#include "TockInvtationPanel.h"
#include "W_RewardInfo.pb.h"

#define MAX_LETTER_CELL 8

class LobbyLetterBoxPanel : public Panel, public Button::Listener, public Nx::Layer::Listener
{
public:
	LobbyLetterBoxPanel();
	virtual ~LobbyLetterBoxPanel();

	virtual void onLayerMessage(const string& msg);

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
	void setActivate(bool activate);

public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);
	void ShowLetterPanel();
	void HideLetterPanel();
	void ShowLetterUi();
	void HideLetterUi();
	void ShowLetterTitie();
	void HideLetterTitie();

	void SetLetterlList();
	void ClearLetterList();
	void ShowLetterGetPopup(W_RewardInfo& _pInfo);



private:
	void ScrollViewOffsetProcess(float _dt);

	bool cellTouchStart(const CCPoint& tableTouchPoint);
	void cellTouchCancel(const CCPoint& tableTouchPoint);
	bool cellTouch(const CCPoint& tableTouchPoint);
	void cellTouchEnd(CCNode* node);

	void CreateCell(int _size);
	//Panel* CreateLetterCell(int _i);
	void UpdateLetterCell(int _toIdx, int _dstIdx);
	
public:
	CCSize mContentsSize;
	Panel* mMainPanel;

	bool mLoginProcess;

	int m_ViewDataIndex;
	CCScrollView* m_pLetterListView;
	CCLayer* m_pLetterListContainer;

	bool m_bTouchCancel;

	CCPoint m_ShowPosition;
	CCPoint m_HidePosition;

	Button* m_AllGetBtn;
	Panel* m_BtnPanel;

	Panel* m_ListCell[MAX_LETTER_CELL];
	Panel* m_CellBtnPanel[MAX_LETTER_CELL];

	SkelObject* m_LetterTitleLabel;
	SkelObject* m_LetterTitleMark;
	SkelObject* m_LetterTitleBg;
	SkelObject* m_ShadowBg;

	Nx::Label* m_LetterCount;
	Nx::Label* m_LetterMaxCount;

	int m_CellIndex;

	bool m_bMovingCell;
	float m_fMoveG;
	CCSize mCellSize;
};

