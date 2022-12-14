#pragma once

#include "NxFramework.h"
#include "LobbySurvivalCell.h"

#define SURVIVAL_CELL_MAX 7
#define SURVIVAL_CELL_WIDTH 192.f
#define SURVIVAL_CELL_HIGHT 244.f
#define SURVIVAL_CELL_INIT_X  ((DESIGN_WIDTH / 2.f) - (SURVIVAL_CELL_WIDTH / 2.f))

class LobbySurvivalBottomPannel : public Panel, public Button::Listener
{
public:
	LobbySurvivalBottomPannel();
	virtual ~LobbySurvivalBottomPannel();

	void InitPanel();
	void InitImage();
	void initButton();

	void InitCenterPanel();
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
	int m_catchCenterIndex;

	int m_totalChannelCount;
	int m_curChannelIndex;
	
	CCScrollView* m_pChannelView;
	CCLayer* m_pChannelContainer;
	Panel* m_pCenterPanel;

	LobbySurvivalCell* m_pChannel[SURVIVAL_CELL_MAX];

	//void CreateChannelCell();
	void UpdateChannelCell();
	//void RemoveChannelCell();

	void UpdateCellScale();
	void SetCenterCell();
	void ReleseCenterCell();
	void UpdateCenterCell();

	void InitChannelList();
	void ReleaseChannelList();
private:
	Button* mReplayBtn;	//리플레이
	Nx::Label* mReplayLabel;
	float getCellMetrics(float _per);
};
