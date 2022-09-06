#include "pch.h"
#include "ChannelRoomPanel.h"
#include "HeroUtil.h"
#include "SceneUtil.h"
#include "GameDataManager.h"
#include "LobbyScene.h"
#include "CustomPopupPanel.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AndroidUtilManager.h"
#endif

ChannelRoomPanel::ChannelRoomPanel()
{
	m_isSearching = false;
	m_searchIdx = -1;
	initPanel();
}

ChannelRoomPanel::~ChannelRoomPanel()
{
	//destruct();
	CCLOG("~ChannelRoomPanel");
	Layer* temp = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingleton().getCurrentLayer());
	if (temp != nullptr) {
		LayerManager::getSingleton().popLayer();
	}
}

void ChannelRoomPanel::initPanel()
{
	mChannelRoomMainPanel = nullptr;
	construct(getMxmlPath() + "dmy_room_list_top.mxml");
	mChannelRoomMainPanel = new ChannelRoomMainPanel();
	mChannelRoomMainPanel->m_pRoomMakeBtn->setListener(this);
	mChannelRoomMainPanel->m_pRoomJoinBtn->setListener(this);
	mChannelRoomMainPanel->m_pRoomInputBtn->setListener(this);
	mChannelRoomMainPanel->m_pSearchBtn->setListener(this);
	mChannelRoomMainPanel->m_searchField->setListener(this);
	addChild(mChannelRoomMainPanel);
	mChannelRoomMainPanel->release();
	mChannelRoomMainPanel->setVisible(true);
	CCPoint roomPos = getDummy("dmy_room_list_under").origin;
	mChannelRoomMainPanel->setPositionX(roomPos.x);
	mChannelRoomMainPanel->setPositionY(-roomPos.y);

	if (LayerManager::getSingleton().hasLayerType<ChannelMainPannel>()) {
		ChannelMainPannel* pPanel = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingleton().getLayerType<ChannelMainPannel>());
		pPanel->setVisibleChannelCell(false);
	}
	
}

void ChannelRoomPanel::UpdateChannelUiPanel()
{
	if (mChannelRoomMainPanel)
		mChannelRoomMainPanel->m_pChannelRoomUi->UpdateChannelPage();
}

void ChannelRoomPanel::onDetached()
{
	string _searchTxt = mChannelRoomMainPanel->getTextField("fld_room_search")->getString();
	if (_searchTxt == "")
	{
		m_searchIdx = -1;
	}
	else
	{
		m_searchIdx = StringConverter::parseInt(_searchTxt);
	}
}

void ChannelRoomPanel::onClicked(const string& name)
{
	if (mChannelRoomMainPanel == nullptr)
		return;
	
	if (name == getButtonName(mChannelRoomMainPanel->m_pRoomMakeBtn))
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		_pScene->MakeGameRoom("");
		//비밀방 만들기 팝업창 인데, 게등위 기준 위반으로 비밀방의 비번없이 만드는 기능으로 대체 "자유방"
		/*CustomPopupPanel* _panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::MAKE_CHANNEL_ROOM_TYPE);
		if (_panel)
		{
			LayerManager::getSingleton().pushDynamicLayer(_panel, DYNAMIC_PUSH_LAYER);
		}*/
	}
	if (name == getButtonName(mChannelRoomMainPanel->m_pRoomJoinBtn))
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			GameDataManager::getSingleton().setPassward("");
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->EnterGameRoom();
		}
	}
	if (name == getButtonName(mChannelRoomMainPanel->m_pRoomInputBtn))
	{
		//기덕수정
		if (mChannelRoomMainPanel) {
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			GameDataManager::getSingletonPtr()->m_bEditTextField = false;
			GameDataManager::getSingletonPtr()->m_onFocusTextFeild = mChannelRoomMainPanel->getTextField("fld_room_search");
			std::string _fieldText = mChannelRoomMainPanel->getTextField("fld_room_search")->getString();
			//AndroidUtilManager::getSingletonPtr()->ReleaseCustomEditTextField();
			AndroidUtilManager::getSingletonPtr()->InitCustomEditTextField();
			AndroidUtilManager::getSingletonPtr()->ShowCustomEditTextField(_fieldText);
#else
			mChannelRoomMainPanel->getTextField("fld_room_search")->attachWithIME();
#endif
		}
	}
	if (name == getButtonName(mChannelRoomMainPanel->m_pSearchBtn))
	{
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			GameDataManager::getSingletonPtr()->ReomveChannelRoomInfoList();

			string _searchTxt = mChannelRoomMainPanel->getTextField("fld_room_search")->getString();
			if (_searchTxt == "")
			{
				m_searchIdx = -1;
			}
			else
			{
				m_searchIdx = StringConverter::parseInt(_searchTxt);
			}
			// 이미 검색한 상태에서 아무것도 넣지 않은 경우
			if (m_isSearching && m_searchIdx == -1)
			{
				_pScene->RoomList(GameDataManager::getSingletonPtr()->m_curPage, ROOM_LIST_COUNT);
			}
			else if (m_searchIdx > 0)
			{
				_pScene->SerchRoom(m_searchIdx);
			}
			//기덕수정
			if (mChannelRoomMainPanel)
				mChannelRoomMainPanel->m_searchField->setString("");
		}
	}

}

