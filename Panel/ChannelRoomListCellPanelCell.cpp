#include "pch.h"
#include "ChannelRoomListCellPanelCell.h"
#include "HeroUtil.h"
#include "GameDataManager.h"

#define CELL_COUNT 4

ChannelRoomListCellPanelCell::ChannelRoomListCellPanelCell()
{
	InitPanel();
}

ChannelRoomListCellPanelCell::~ChannelRoomListCellPanelCell()
{

}

void ChannelRoomListCellPanelCell::InitPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_room_list_content_panels.mxml");
	CCSize contentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(contentSize.height - DESIGN_HEIGHT - contentSize.height / 2.f);
	mMainPanel->setPositionX(-contentSize.width / 2.f);
	mMainPanel->setContentSize(contentSize);
	this->setContentSize(contentSize);

	for (int i = 0; i < CELL_COUNT; i++)
	{
		string dmyStr = "dmy_room_list_panel" + StringConverter::toString(i + 1);
		ChannelRoomCell* roomPage = new ChannelRoomCell();
		mMainPanel->addChild(roomPage);
		roomPage->release();
		roomPage->setPosition(mMainPanel->getImage(dmyStr)->getPosition());		
		roomPage->setActivate(false);
		mContainer.push_back(roomPage);
	}
}


void ChannelRoomListCellPanelCell::setCellIndex(int index)
{
	int maxSize = GameDataManager::getSingletonPtr()->m_TotalDataCount;
	int startIndex = index * CELL_COUNT;
	
	//초기화
	for (int i = 0; i < CELL_COUNT; i++)
	{
		mContainer[i]->setActivate(false);
		if (startIndex + i < maxSize) {
			mContainer[i]->setActivate(true);
			string _roomNumber = "Room[" + StringConverter::toString(startIndex + i) + "]";
			mContainer[i]->setRoomNumber(_roomNumber);
			mContainer[i]->UpdateRoomInfo(startIndex + i);
		}
	}
}
