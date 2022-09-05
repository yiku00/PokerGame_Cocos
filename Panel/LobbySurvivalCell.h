#pragma once

#include "NxFramework.h"
#include "W_ChannelInfo.pb.h"
#include "W_DeathMatchInfo.pb.h"

enum SURVIVAL_BUTTON_KIND
{
	DISABLE = 0,
	ENABLE = 1,
	HIGHLIGHT1 = 2,
	HIGHLIGHT2 = 3,
};

class LobbySurvivalCell : public Panel, public Button::Listener
{
public:
	LobbySurvivalCell();
	virtual ~LobbySurvivalCell();

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
	void SetCellData(int _index);

	void SetButtonString(std::string _txt, SURVIVAL_BUTTON_KIND btnKind);
	void SetTitleString(std::string _txt);
	void SetOffButtonString(std::string _txt);
public:
	W_DeathMatchInfo* m_CellInfo;

	Button* m_btnChannel;

	Nx::Label* m_labelTitle;
	Nx::Label* m_labelGift;
	Nx::Label* m_labelGold;
	Nx::Label* m_labelEnter;
	Nx::Label* m_labelEnterCount;
};
