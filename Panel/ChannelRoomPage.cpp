#include "pch.h"
#include "ChannelRoomPage.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
//#include "SimplePopupPanel.h"
//#include "HeroApp.h"

#include "Web/WebService.h"

ChannelRoomPage::ChannelRoomPage()
{
	InitPanel();

	setTouchable(false);
	setButtonListener(this);

}

ChannelRoomPage::~ChannelRoomPage()
{
}

void ChannelRoomPage::InitPanel()
{
	setContentSize(CCSize(DESIGN_WIDTH, DESIGN_HEIGHT));

	for (int _i = 0; _i < 2; _i++)
	{
		for (int _j = 0; _j < 4; _j++)
		{
			m_pCell[(_i * 4) + _j] = new ChannelRoomCell();
			addChild(m_pCell[(_i*4) + _j]);
			m_pCell[(_i * 4) + _j]->setPositionX(248.f * _j);
			m_pCell[(_i * 4) + _j]->setPositionY(-201.f * _i);
			m_pCell[(_i * 4) + _j]->release();
			string _roomNumber = "Room[" + StringConverter::toString((_i * 4) + _j) + "]";
			m_pCell[(_i * 4) + _j]->setRoomNumber(_roomNumber);
		}
	}
}

void ChannelRoomPage::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void ChannelRoomPage::onClicked(const string& name)
{

}

void ChannelRoomPage::update(float dt)
{

}

bool ChannelRoomPage::handling(STCMD &stCmd)
{
	return false;
}

void ChannelRoomPage::UpdatePageData(int _page)
{
	for (int _i = 0; _i < 2; _i++)
	{
		for (int _j = 0; _j < 4; _j++)
		{
			int _index = (_i * 4) + _j + (_page * 8);
			/*
			// deleted by haimandang 20160315
			if (GameDataManager::getSingletonPtr()->m_RoomInfoList.size() <= _index)
			{
				m_pCell[(_i * 4) + _j]->setVisible(false);
			}
			else
			{
				m_pCell[(_i * 4) + _j]->setVisible(true);
				m_pCell[(_i * 4) + _j]->UpdateRoomInfo(_index);
			}
			*/
			// added by hiamandang 20160315
			m_pCell[(_i * 4) + _j]->setVisible(true);
			m_pCell[(_i * 4) + _j]->UpdateRoomInfo(_index);

		}
	}
}
void ChannelRoomPage::onEnter()
{
	Panel::onEnter();

	scheduleUpdate();
}