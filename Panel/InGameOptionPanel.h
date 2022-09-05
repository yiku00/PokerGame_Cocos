/********************************************************************
file name:	InGameOptionPanel.h

purpose:	게임중 옵션창
*********************************************************************/
#pragma once
#include "NxFramework.h"

enum CheckButtonType
{
	CHECK_MUSIC,
	CHECK_EFFECT, 
	CHECK_VOICE,	
	CHECK_HIDDEN
};

class InGameOptionPanel : public Panel, public Button::Listener
{
public:
	InGameOptionPanel();
	virtual ~InGameOptionPanel();

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
	void SetOptionValue();
	virtual void onEnter() override;

public:
	bool m_bBtnTouch;
	Panel* mParentPanel;
	Panel* mMainPanel;

	SkelObject* m_pOptionCheck[4];
	SkelObject* m_pOptionUnCheck[4];

	Button* m_pOptionCheckBtn[4];
	Button* m_pOptionUnCheckBtn[4];
	//Button* m_pCloseButton;

	Nx::Label* m_RoomNumberText;
	Nx::Label* m_RoomInfoLabel;
	Nx::Label* m_RoomInfoText;
	Nx::Label* m_RoomInfoTextUnder;
	Nx::Label* m_PotMoneyLabel;
	Nx::Label* m_PotMoneyTextUnder;
	Nx::Label* m_PotMoneyText;
	Nx::Label* m_OptionLabelMusic;
	Nx::Label* m_OptionLabelVoice;
	Nx::Label* m_OptionLabelEffect;
	Nx::Label* m_OptionLabelHidden;
};
