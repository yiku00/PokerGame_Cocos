#pragma once

#include "NxFramework.h"

#define COLOR_7POKER_ON ccc3(255, 146, 118)
#define COLOR_HIGHLOW_ON ccc3(24, 205, 255)
#define COLOR_BADUKI_ON ccc3(147, 255, 100)
#define COLOR_HOLDEM_ON ccc3(91, 255, 215)

#define COLOR_7POKER_OFF ccc3(154, 64, 59)
#define COLOR_HIGHLOW_OFF ccc3(19, 121, 163)
#define COLOR_BADUKI_OFF ccc3(76, 163, 44)
#define COLOR_HOLDEM_OFF ccc3(42, 131, 118)


class LobbyChannelSubTopUiPanel : public Panel, public Button::Listener
{
public:
	LobbyChannelSubTopUiPanel();
	virtual ~LobbyChannelSubTopUiPanel();

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
	virtual bool handling(STCMD &stCmd);
	void update(float dt);

	void SetGameChannel(int _gamekind);
public:
	bool mLoginProcess;
	CCPoint m_ExpStartPos;
};
