#pragma once

#include "NxFramework.h"

class PokerEmotionPanel : public Panel, public Button::Listener
{
public:
	PokerEmotionPanel(int _panelType);
	virtual ~PokerEmotionPanel();

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
	int m_PanelType;

	bool m_bBlockEmotion;

	Button* m_KickOutButton;
	Button* m_CheckButton;
	SkelObject* mRankIcon;
};
