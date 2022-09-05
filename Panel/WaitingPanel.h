/********************************************************************
	file name:	WaitingPanel.h
	
	purpose:	통신 대기 창 (TODO : 지연된 경우에만 표시하도록 수정)
*********************************************************************/
#ifndef __WaitingPanel_H__
#define __WaitingPanel_H__

#include "NxFramework.h"

class WaitingPanel : public Panel
{
public:
	WaitingPanel();
	~WaitingPanel();

public: // CCOjbect
	virtual void update(float dt);

public: // CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnter() override;

private:
	Panel* mBackground;
	SkelObject* mIcon;
	float mWaitingTime;
};

#endif