#ifndef __LobbyCharacterInfoPanel_H__
#define __LobbyCharacterInfoPanel_H__

#include "NxFramework.h"

class LobbyCharacterInfoPanel : public Panel, public Button::Listener
{
public:
	LobbyCharacterInfoPanel();
	virtual ~LobbyCharacterInfoPanel();

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
	
public:
	bool mLoginProcess;

};

#endif
