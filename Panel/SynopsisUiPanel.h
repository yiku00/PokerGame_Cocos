#pragma once

#include "NxFramework.h"

class SynopsisUiPanel : public Panel, public Button::Listener
{
public:
	SynopsisUiPanel();
	virtual ~SynopsisUiPanel();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onClicked(const string& name);
	//virtual void keyBackClicked();
	virtual bool handling(STCMD &stCmd);
	virtual void onEnter() override;

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	void ShowPlayerSelectPanel(bool _visible);
	void ShowTitle(bool _show);
	void ShowDialog();
	void EnableButton(bool _enable);
	void setLightUse(bool use);
public:
	bool mLoginProcess;

	bool m_GamePlaying;

	Button* m_SelectButton;
	Button* m_LeftButton;
	Button* m_RightButton;

	SkelObject* m_TitleBar;
	SkelObject* m_ButtonBack;
	SkelObject* m_BottomStone[4];

	Nx::Label* m_TitleLabel;

	CCSize m_contentSize;
	CCRect m_characterInfoRect;
	CCRect m_dialogueRect;

private:
	bool m_bSelectCharacter;
	bool m_bMoveing;
	Nx::Label* mSelectBtnLabel;
	Nx::Label* mSelectBtnUnderLabel;
	Widget* mLight;
};
