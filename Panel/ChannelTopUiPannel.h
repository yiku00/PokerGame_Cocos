#pragma once

#include "NxFramework.h"
#include "CustomPopupPanel.h"

class ChannelTopUiPannel : public Panel, public Button::Listener
{
public:
	ChannelTopUiPannel();
	virtual ~ChannelTopUiPannel();

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
	void UpdatePlayerInfo();

public:
	CustomPopupPanel* m_pParentPopup;

	bool m_bProcessing;

	Button* m_btnLetterBox;
	Button* m_btnMission;
	Button* m_btnShop;
	Button* m_btnBank;
	Button* m_btnRubyShop;
	Button* m_btnOption;

	SkelObject* m_TopEfx[3];
	SkelObject* m_LeftEfx[3];

	Nx::Label* m_gold;
	Nx::Label* m_chip;
	Nx::Label* m_rubby;
};
