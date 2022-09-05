#include "pch.h"
#include "ChannelRoomUiPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"

#include "Web/WebService.h"
#include "LobbyScene.h"
#include "GameStringDepot.h"
#include "ChannelRoomListCellPanelCell.h"

ChannelRoomUiPanel::ChannelRoomUiPanel()
{
	InitPanel();
	InitImage();
	InitButton();	
	setButtonListener(this);	
}

ChannelRoomUiPanel::~ChannelRoomUiPanel()
{
	//destruct();
}

void ChannelRoomUiPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_room_list_panels.mxml");
	mCellSize = getDummy("dmy_room_list_panel1").size;
	CCRect tableViewRect = getDummyUI("dmy_room_list_panels");
	mTableView = Nx::TableView::create(this, tableViewRect.size);
	addChild(mTableView);
	mTableView->setDirection(ScrollView::Direction::VERTICAL);
	mTableView->setVerticalFillOrder(Nx::TableView::VerticalFillOrder::TOP_DOWN);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setDelegate(this);
	mTableView->reloadData();
	mTableView->setBounceable(false);
}

void ChannelRoomUiPanel::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void ChannelRoomUiPanel::onClicked(const string& name)
{
	if (mLodingProcess)
		return;

}

void ChannelRoomUiPanel::update(float dt)
{

}

bool ChannelRoomUiPanel::handling(STCMD &stCmd)
{
	if (!mLodingProcess)
		return false;

	return false;
}

void ChannelRoomUiPanel::InitImage()
{	
}

void ChannelRoomUiPanel::InitButton()
{
	
}



void ChannelRoomUiPanel::UpdateChannelPage()
{
	mTableView->reloadData();
}

CCSize ChannelRoomUiPanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* ChannelRoomUiPanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CCTableViewCell* cell = table->dequeueCell();

	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		ChannelRoomListCellPanelCell* pPanel = new ChannelRoomListCellPanelCell();
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);
		pPanel->setPosition(ccp(pPanel->getContentSize().width / 2.f, pPanel->getContentSize().height / 2.f));
		pPanel->setCellIndex(idx);
	}
	else {
		ChannelRoomListCellPanelCell* pPanel = dynamic_cast<ChannelRoomListCellPanelCell*>(cell->getChildByTag(1));
		if (pPanel) {
			pPanel->setCellIndex(idx);
		}
	}
	return cell;
}

ssize_t ChannelRoomUiPanel::numberOfCellsInTableView(CCTableView *table)
{
	int cellSize = GameDataManager::getSingletonPtr()->m_TotalDataCount / 4 + 1;
	if (GameDataManager::getSingletonPtr()->m_TotalDataCount % 4 == 0)
		cellSize--;

	if (cellSize < 3)
		cellSize = 2;

	return cellSize;
}

void ChannelRoomUiPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	
}

bool ChannelRoomUiPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (pTouch->getLocation().y >= DESIGN_HEIGHT - 72.f)
		return false;

	return true;
}
