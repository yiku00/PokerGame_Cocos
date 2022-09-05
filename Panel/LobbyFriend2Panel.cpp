#include "pch.h"
#include "LobbyFriend2Panel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "SimplePopupPanel.h"
#include "Web/WebService.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"
#include "LobbyTopUiPanel.h"
#include "LobbyUIPanel.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/FacebookManager.h"
#include "android/AndroidUtilManager.h"
#endif
#include "FriendHelper.h"
#include "PokerResourceHelper.h"

LobbyFriend2Panel::LobbyFriend2Panel()
{
	InitPanel();	
}

LobbyFriend2Panel::~LobbyFriend2Panel()
{
}

void LobbyFriend2Panel::InitPanel()
{
	construct(getMxmlPath() + "dmy_friend2_1.mxml");
	mFriendAcceptPanel = new LobbyFriendAcceptPanel();
	addChild(mFriendAcceptPanel);
	mFriendAcceptPanel->release();
	mFriendAcceptPanel->setPosition(getImage("dmy_friend_request1")->getPosition());

	mFriendRequestPanel = new LobbyFriendRequestPanel();
	addChild(mFriendRequestPanel);
	mFriendRequestPanel->release();
	mFriendRequestPanel->setPosition(getImage("dmy_friend_request2")->getPosition());
}

void LobbyFriend2Panel::ShowFriendInfoPanel(int _index)
{
	CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::FRIEND_INFO_TYPE, _index, 3);
	if (panel)
	{
		LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
	}
}

void LobbyFriend2Panel::onClicked(const string& name)
{	
}

void LobbyFriend2Panel::update(float dt)
{
	
}

bool LobbyFriend2Panel::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK>(&stCmd))
	{
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK res = *pstIt;
		CCLog("res.param = %d", res.param);
		if (res.param == RECOMMEND_PHOTO || res.param == FRIEND_PHOTO)
		{
			if (!res.imagePath.empty())
			{
				int _index = res.dParam;
				if (res.param == RECOMMEND_PHOTO) {									
					if (mFriendRequestPanel)
						mFriendRequestPanel->refreshPhoto(_index);
					
				}
				else if (res.param == FRIEND_PHOTO) {
					if (mFriendAcceptPanel)
						mFriendAcceptPanel->refreshPhoto(_index);
				}
			}
			return true;
		}		
	}

	return false;
}

void LobbyFriend2Panel::ClearRequestList()
{	
}

void LobbyFriend2Panel::ClearRecommendlList()
{
	
}


void LobbyFriend2Panel::SetRequestFriendList()
{
	ClearRequestList();
	if (mFriendAcceptPanel)
		mFriendAcceptPanel->refreshTableView();
}

void LobbyFriend2Panel::SetRecommendFriendList()
{
	ClearRecommendlList();
	if (mFriendRequestPanel)
		mFriendRequestPanel->refreshTableView();
}

void LobbyFriend2Panel::SetButtonPause(bool _pause)
{
	
}

void LobbyFriend2Panel::refreshTableView()
{
	if (mFriendAcceptPanel)
		mFriendAcceptPanel->refreshTableView();

	if (mFriendRequestPanel)
		mFriendRequestPanel->refreshTableView();
}

void LobbyFriend2Panel::setActivate(bool activate)
{
	if (activate) {
		setVisible(true);
		if (getPositionX() < 0) {
			setPositionX(getPositionX() + DESIGN_WIDTH);
		}
	}
	else {
		setVisible(false);
		if (getPositionX() > 0) {
			setPositionX(getPositionX() - DESIGN_WIDTH);
		}
	}
}
