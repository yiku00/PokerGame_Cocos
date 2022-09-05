#pragma once

#include "NxFramework.h"
#include "LobbyTournamentCell.h"

#define TOURNAMENT_CELL_MAX 7
#define TOURNAMENT_CELL_WIDTH 296.f
#define TOURNAMENT_CELL_HIGHT 240.f
#define TOURNAMENT_CELL_INIT_X  ((DESIGN_WIDTH / 2.f) - (TOURNAMENT_CELL_WIDTH / 2.f))

class LobbyTournamentBottomPannel : public Panel, public Button::Listener
{
public:
	LobbyTournamentBottomPannel();
	virtual ~LobbyTournamentBottomPannel();

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

	LobbyTournamentCell* m_pChannel[TOURNAMENT_CELL_MAX];

	//void CreateChannelCell();
	void UpdateChannelCell();
	//void RemoveChannelCell();

	void UpdateCellScale();
	void SetCenterCell();
	void ReleseCenterCell();
	void UpdateCenterCell();

	void InitChannelList();
	void ReleaseChannelList();
	//W_ChannelInfo* getChannelInfo(int _cellIndex);

private:
	float getCellMetrics(float _per);

private:
	Button* mReplayBtn;	//리플레이
	Nx::Label* mReplayLabel;

	Button* mRuleBtn;
	Nx::Label* mRuleBtnLabel;

	Button* mSeasonRankInfoBtn;
	Nx::Label* mSeasonRankInfoBtnLabel;

};
