#pragma once

#include "NxFramework.h"
#include "ChannelRoomPage.h"
#include "LobbyRoomTopUiPanel.h"

class ChannelRoomUiPanel : public Panel, public Button::Listener, public CCTableViewDelegate, public CCTableViewDataSource
{
public:
	ChannelRoomUiPanel();
	virtual ~ChannelRoomUiPanel();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual bool handling(STCMD &stCmd);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	void CreatePage(int _totalCellCount);
	void UpdateChannelPage();

public:
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table,  ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view){};
	virtual void scrollViewDidZoom(CCScrollView* view){}

private:
	void drawTableView();
public:
	
	bool mLodingProcess;
	bool m_GamePlaying;

	int m_curPage;
	int m_TotalPage;

	CCSize mCellSize;
	Nx::TableView* mTableView;

	Button* mMakeRoomBtn;
};
