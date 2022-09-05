#pragma once

#include "NxFramework.h"
#include "ChannelCell.h"

#define CHANNEL_CELL_MAX 7
#define CHANNEL_CELL_WIDTH 192.f
#define CHANNEL_CELL_HIGHT 244.f
#define CHANNEL_CELL_INIT_WIDTH ((DESIGN_WIDTH / 2.f) - (CHANNEL_CELL_WIDTH / 2.f))

class ChannelBottomUiPannel : public Panel, public Button::Listener
{
public:
	ChannelBottomUiPannel();
	virtual ~ChannelBottomUiPannel();

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

	void refreshNotiEffect();

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

	ChannelCell* m_pChannel[CHANNEL_CELL_MAX];

	void UpdateChannelCell();
	void UpdateCellScale();
	void SetCenterCell();
	void ReleseCenterCell();
	void UpdateCenterCell();

	void InitChannelList();
	void ReleaseChannelList();
	W_ChannelInfo* getChannelInfo(int _cellIndex);

private:
	float getCellMetrics(float _per);
	Button* mReplayBtn;	//리플레이
	Nx::Label* mReplayLabel;
};
