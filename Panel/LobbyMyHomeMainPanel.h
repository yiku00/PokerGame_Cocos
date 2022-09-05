/********************************************************************
file name:	LobbyMyHomeMainPanel.h

purpose:	로비 기본 버튼 UI ( 상점 , 우편함 , 등등 버튼 UI + 카지노입장 시즌 토너먼트 버튼
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "LobbyMyHomeTap1.h"
#include "LobbyMyHomeTap2.h"
#include "LobbyMyHomeTap3.h"

class LobbyMyHomeMainPanel : public Panel, public Button::Listener
{
public:
	LobbyMyHomeMainPanel();
	virtual ~LobbyMyHomeMainPanel();

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
	
	void ShowMyHomePanel();
	void HideMyHomePanel();
	void unVisibleHomePanel();
	void ShowHomeTitle();
	void HideHomeTitle();

	void SetTapPanel(int _idx);

	void SetBasicInfoTap();
	void SetRecordInfoTap();
	void SetVipClassInfoTap();
	void SetEnableTap(int _index);

	void ReleaseBasicInfoTap();
	void ReleaseRecordInfoTap();
	void ReleaseVipClassInfoTap();

	void GotoShop(int _tapIndex);
	void refreshUserName();
public:
	bool mLoginProcess;

	CCScrollView* m_pTapView[3];
	CCLayer* m_pTapViewContainer[3];

	bool m_bTouchCancel;

	float m_ButtonPosX;
	float m_ButtonMaxPosX;
	CCPoint m_ButtonStartPosition;

	Button* m_DailyCheckButton;

	CCPoint m_HidePos;
	CCPoint m_ShowPos;

	int m_nTapIndex;
	Panel* mTapButtonPanel[3];
	//Button* mTapButton[3];

	//Panel* m_pCharacterSelectPanel;

	LobbyMyHomeTap1* _pBasicPanel;
	LobbyMyHomeTap2* _pRecordPanel;
	LobbyMyHomeTap3* _pVipClassPanel;

};
