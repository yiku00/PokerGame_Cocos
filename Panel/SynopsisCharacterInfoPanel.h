#pragma once

#include "NxFramework.h"

class SynopsisCharacterInfoPanel : public Panel, public Button::Listener
{
public:
	SynopsisCharacterInfoPanel();
	virtual ~SynopsisCharacterInfoPanel();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	virtual void onEnter() override;
	void ShowInfo(bool _visible, int _infoIdx = -1);
public:
	CCSize m_contentSize;

	Nx::Label* m_AgeLabel;
	Nx::Label* m_JobLabel;
	
	Nx::Label* m_NameText;
	Nx::Label* m_AgeText;
	Nx::Label* m_JobText;
	Nx::Label* m_StoryText;
	Nx::Label* mGenderLabel;
};
