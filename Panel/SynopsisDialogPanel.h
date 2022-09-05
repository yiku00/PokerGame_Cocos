#pragma once

#include "NxFramework.h"

class SynopsisDialogPanel : public Panel, public Button::Listener
{
public:
	SynopsisDialogPanel();
	virtual ~SynopsisDialogPanel();

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
	void ShowText(int _idx);
	void ShowDialog(bool _visible);
	void ShowSelectCharacer();

	void ShowTutorial();
public:
	bool mLoginProcess;
	bool m_SynopsisEnd;

	CCSize m_contentSize;

	SkelObject* m_Dialogue;
	Button* m_TouchButton;

	Nx::Label* m_Name;
	Nx::Label* m_Text;

	Nx::Label* mTouchLabel;
	Nx::Label* mTouchUnderLabel;

	int m_TextIdx;
};
