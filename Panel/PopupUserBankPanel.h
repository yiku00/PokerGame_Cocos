#pragma once

#include "NxFramework.h"

class PopupUserBankPanel : public Panel, public Button::Listener
{
public:
	PopupUserBankPanel();
	virtual ~PopupUserBankPanel();

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

	
};
