#include "pch.h"
#include "WaitingPanel.h"
#include "HeroApp.h"
#include "HeroUtil.h"

#define ICON_RATATION_ANGLE_PER_SEC 360.f
#define WAITING_DISPLAY 2.f
#define WAITING_TIMEOUT 15.f

WaitingPanel::WaitingPanel()
{
	// 닫힐때 하위 레이어를 갱신하지 않도록 만든다.
	setSeparate();
	mWaitingTime = 0;

	Panel* pPanel = new Panel();
	pPanel->makeColored(ccc4(0x55, 0x55, 0x55, 0x55));
	addChild(pPanel);
	pPanel->release();


	construct(getMxmlPath() + "dmy_loading_icon.mxml");
	setVisible(false);
}


WaitingPanel::~WaitingPanel()
{
	removeAllChildrenWithCleanup(true);
}

void WaitingPanel::update(float dt)
{
	mWaitingTime += dt;
	if (!isVisible() && mWaitingTime > WAITING_DISPLAY) {
		setVisible(true);
	}
	if (mWaitingTime > WAITING_TIMEOUT) {

	}
}

bool WaitingPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//HttpManager::getSingleton().stop();

	return true;
}

void WaitingPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}
