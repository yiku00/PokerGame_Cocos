#pragma once

#include "NxFramework.h"

class ReplayTutorialPanel : public Panel, public Button::Listener
{
public:
	ReplayTutorialPanel();
	virtual ~ReplayTutorialPanel();

	void InitPanel();
	void InitImage();
	void initButton();
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onEnter() override;

    void resume();
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);
	
	void ShowText(int _page);
	void ShowPage(int _page);
	void UpdateTutorialStep(float _dt);
public:
	vector<SkelObject*> m_page1;
	vector<SkelObject*> m_page2;
	vector<SkelObject*> m_page3;

	vector<Nx::Label*> m_page1Label;
	vector<Nx::Label*> m_page2Label;
	vector<Nx::Label*> m_page3Label;
	
	SkelObject* m_Icon;
	SkelObject* m_bubble;
	Nx::Label* m_DialogeTxt;

	int m_pageIndex;

	float m_TutorialTime;
	int m_TutorialStep;
};
