#pragma once

#include "NxFramework.h"

class LobbyLeftUiPanel : public Panel, public Button::Listener
{
public:
	LobbyLeftUiPanel();
	virtual ~LobbyLeftUiPanel();

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

	void PlayButtonEffect(int _idx);
	void UpdateNotiData();
	virtual void onEnter() override;
public:
	bool mLoginProcess;
	SkelObject* m_LetterNoti;
	SkelObject* m_MissionNoti;
	Nx::Label* m_pLetterCount;
	Nx::Label* m_pMissionCount;
};
