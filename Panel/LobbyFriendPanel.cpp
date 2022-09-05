#include "pch.h"
#include "LobbyFriendPanel.h"

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
#endif
#include "LobbyTopUiPanel.h"
#include "LobbyUIPanel.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/FacebookManager.h"
#endif
#include "LobbyFriendInvitePanel.h"

#include "PanelHelper.h"
#define FRIEND_TAB_COUNT 3

#define TEMP_FACEBOOK true

LobbyFriendPanel::LobbyFriendPanel()
{
	mLoginProcess = false;

	InitPanel();
	InitImage();
	initButton();
	
	setButtonListener(this);
	
}

LobbyFriendPanel::~LobbyFriendPanel()
{
}

void LobbyFriendPanel::InitPanel()
{
	Panel* panel = addMouseBlockPanel(this, true);
	panel->setContentSize(CCSize(DESIGN_WIDTH, DESIGN_HEIGHT - 72));

	construct(getMxmlPath() + "friend.mxml");
	
	CCPoint _friendListPos = getDummy("dmy_friend1").origin;
	CCPoint _recommendListPos = getDummy("dmy_friend2").origin;
	//Todo
	CCPoint _facebookListPos = getDummy("dmy_friend2").origin;

	mFriendInvitePanel = nullptr;
	mFriendInvitePanel = new LobbyFriendInvitePanel();
	mFriendInvitePanel->setPosition(getImage("dmy_friend3_2")->getPosition());
	addChild(mFriendInvitePanel);
	mFriendInvitePanel->release();
	mFriendInvitePanel->setVisible(false);

	m_pRecommendPanel = new LobbyFriend2Panel();
	m_pRecommendPanel->setPositionX(_recommendListPos.x);
	m_pRecommendPanel->setPositionY(-_recommendListPos.y);
	addChild(m_pRecommendPanel);
	m_pRecommendPanel->release();
	m_pRecommendPanel->setVisible(false);

	m_pFriendPanel = new LobbyFriend1Panel();
	m_pFriendPanel->setPositionX(_friendListPos.x);
	m_pFriendPanel->setPositionY(-_friendListPos.y);
	addChild(m_pFriendPanel);
	m_pFriendPanel->release();
	m_pFriendPanel->setVisible(false);
	m_pFriendPanel->SetFriendPanelType(TYPE_GAME_FRIEND);
	
}

//void LobbyFriendPanel::InitFriendInfoPanel()
//{
//	if (m_pFrirnfInfoPanel != nullptr)
//		return;
//
//	m_pFrirnfInfoPanel = new Panel();
//	m_pFrirnfInfoPanel->construct(getMxmlPath() + "dmy_friendinfo.mxml");
//	m_pFrirnfInfoPanel->setPosition(ccp(0, 0));//DESIGN_WIDTH / 2.f, DESIGN_HEIGHT / 2.f));
//	addChild(m_pFrirnfInfoPanel, 20);
//
//	m_pFriendPanelRemoveBtn = m_pFrirnfInfoPanel->getButton("sbtn_small_button_4_stay");
//	m_pFriendPanelReplayBtn = m_pFrirnfInfoPanel->getButton("sbtn_small_button_4r_stay");
//	m_pFriendPanelExitBtn = m_pFrirnfInfoPanel->getButton("sbtn_title_cancel_stay");
//
//	m_pFriendPanelReplayBtn->getButtonSkelObject()->setSkin("txt_storage_tray");
//	m_pFriendPanelRemoveBtn->getButtonSkelObject()->setSkin("txt_frienddel");
//	m_pFriendPanelExitBtn->getButtonSkelObject()->setSkin("mark_cancel");
//	m_pFrirnfInfoPanel->getSkel("skel_small_title")->setSkin("title_friendinfo");
//
//	m_pFriendPanelReplayBtn->setName("FriendInfo_Replay");
//	m_pFriendPanelRemoveBtn->setName("FriendInfo_RemoveFriend");
//	m_pFriendPanelExitBtn->setName("FriendInfo_Close");
//
//	m_pFriendPanelReplayBtn->setListener(this);
//	m_pFriendPanelRemoveBtn->setListener(this);
//	m_pFriendPanelExitBtn->setListener(this);
//
//	m_pFriendPanelReplayBtn->setType(Button::NoPressImg);
//	m_pFriendPanelRemoveBtn->setType(Button::NoPressImg);
//	m_pFriendPanelExitBtn->setType(Button::NoPressImg);
//	
//	m_pFrirnfInfoPanel->setVisible(false);
//	m_pFrirnfInfoPanel->setTouchEnabled(false);
//	
//}

//void LobbyFriendPanel::SetFriendInfoData(int _idx)
//{
//	W_FriendInfo* _info = nullptr;
//
//	switch (m_TapIndex)
//	{
//		case 0:
//			_info = GameDataManager::getSingletonPtr()->m_SnsDataList[_idx];
//			break;
//		case 1:
//			_info = GameDataManager::getSingletonPtr()->m_FriendDataList[_idx];
//			break;
//	}
//	
//
//	if (_info == nullptr)
//		return;
//
//	if (_info->has_name())
//	{
//		m_pFrirnfInfoPanel->getLabel("txt_username")->setString(_info->name().c_str());
//	}
//
//	if (_info->has_connecttime())
//	{
// 		m_pFrirnfInfoPanel->getLabel("txt_lastday")->setString(_info->connecttime().c_str());
//	}
//
//	if (m_pFriendPanelRemoveBtn) m_pFriendPanelRemoveBtn->setTag(_idx);
//	if (m_pFriendPanelReplayBtn) m_pFriendPanelReplayBtn->setTag(_idx);
//
//}

void LobbyFriendPanel::ShowFriendInfoPanel(int _index)
{
	CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::FRIEND_INFO_TYPE, _index, m_TapIndex + 1);

	if (panel)
	{
		LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
	}
}


void LobbyFriendPanel::InitImage()
{
}

void LobbyFriendPanel::initButton()
{
	for (int _i = 0; _i < FRIEND_TAB_COUNT; _i++)
	{
		CCPoint _tapBtnPos = getDummy("dmy_button_tab" + StringConverter::toString(_i + 1)).origin;

		m_TapButton[_i] = new TabButtonPanel();
		m_TapButton[_i]->setPositionX(_tapBtnPos.x);
		m_TapButton[_i]->setPositionY(-_tapBtnPos.y);
		addChild(m_TapButton[_i]);
		m_TapButton[_i]->release();
		m_TapButton[_i]->SetButtonListener(this);
		m_TapButton[_i]->m_Button->setName("TAP_BUTTON" + StringConverter::toString(_i + 1));
	}

	m_TapButton[0]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_INVITE_FRIENDS")); 
	m_TapButton[1]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_TAP_RECOMMEND"));
	if (FRIEND_TAB_COUNT > 2)
		m_TapButton[2]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_TAP_FRIEND"));

	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_FRIEND_RECOMMEND_FRIEND);
		m_TapButton[1]->addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(m_TapButton[1]->getImage("dmy_notification_icon")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}	

	if (FRIEND_TAB_COUNT > 2) {
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_FRIEND_GAME_FRIEND);
		m_TapButton[2]->addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(m_TapButton[2]->getImage("dmy_notification_icon")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}

#ifdef NO_USE_CHECK
	m_TapButton[0]->setVisible(false);
	m_TapButton[0]->SetButtonListener(nullptr);

	{
		CCPoint _tapBtnPos = getDummy("dmy_button_tab1").origin;
		m_TapButton[1]->setPositionX(_tapBtnPos.x);
		m_TapButton[1]->setPositionY(-_tapBtnPos.y);
	}

	{
		CCPoint _tapBtnPos = getDummy("dmy_button_tab2").origin;
		m_TapButton[2]->setPositionX(_tapBtnPos.x);
		m_TapButton[2]->setPositionY(-_tapBtnPos.y);
	}
	ClickTapButton(1);
#else
	ClickTapButton(0);
#endif // NO_USE_CHECK



	
}


bool LobbyFriendPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}


void LobbyFriendPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}


void LobbyFriendPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyFriendPanel::resume()
{
}

void LobbyFriendPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (name == "TAP_BUTTON1")
	{
		m_TapIndex = 0;
		//로그인이 되어 있다면
		if(GameDataManager::getSingletonPtr()->m_FacebookUserId == "") {
			CCLog("TAP_BUTTON3 1");
			WebService::getSingletonPtr()->_sendFacebookRequestListReq();
		}
		else {
			CCLog("TAP_BUTTON3 2");
			ClickTapButton(0);
		}

	}
	else if (name == "TAP_BUTTON2")
	{
		m_TapIndex = 1;
		WebService::getSingletonPtr()->_sendFriendRequestListReq();
	}
	else if (name == "TAP_BUTTON3")
	{
		CCLog("TAP_BUTTON3");
		m_TapIndex = 2;		
		WebService::getSingletonPtr()->_sendFriendOfInfoReq();
		
	}
}

void LobbyFriendPanel::ClickTapButton(int _idx)
{
	m_TapIndex = _idx;
	SetFriendlList();
	for (int _i = 0; _i < FRIEND_TAB_COUNT; _i++)
	{
		if (_i == m_TapIndex)
		{
			m_TapButton[_i]->SetBtnOnOff(true);
		}
		else
		{
			m_TapButton[_i]->SetBtnOnOff(false);
		}
	}
	
	switch (m_TapIndex)
	{
	case 0:
		m_pFriendPanel->setActivate(false);
		m_pRecommendPanel->setActivate(false);
		//m_pFriendPanel->SetButtonPause(false);
		//m_pRecommendPanel->SetButtonPause(false);

		if (mFriendInvitePanel) {
			mFriendInvitePanel->setActivate(true);			
		}
		

		break;
	case 2:
		m_pFriendPanel->setActivate(true);
		m_pRecommendPanel->setActivate(false);
		//m_pFriendPanel->SetButtonPause(false);
		//m_pRecommendPanel->SetButtonPause(true);

		if (mFriendInvitePanel) {
			mFriendInvitePanel->setActivate(false);
		}
		break;
	case 1:
		m_pFriendPanel->setActivate(false);
		m_pRecommendPanel->setActivate(true);
		//m_pFriendPanel->SetButtonPause(true);
		//m_pRecommendPanel->SetButtonPause(false);
		if (mFriendInvitePanel) {
			mFriendInvitePanel->setActivate(false);
		}
		break;
	}
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
}

void LobbyFriendPanel::update(float dt)
{
	updateNotiWidget();
}

bool LobbyFriendPanel::handling(STCMD &stCmd)
{
	if (m_pFriendPanel->isVisible()) {
		return m_pFriendPanel->handling(stCmd);
	}
	else if (m_pRecommendPanel->isVisible()) {
		return m_pRecommendPanel->handling(stCmd);
	}	
	else if (mFriendInvitePanel->isVisible()) {
		return mFriendInvitePanel->handling(stCmd);
	}
	return false;
}

void LobbyFriendPanel::ShowFriendPanel()
{
	ShowFriendUi();
	SetFriendlList();
	ShowFriendTitie();
}
void LobbyFriendPanel::HideFriendPanel()
{
	HideFriendTitie();
	HideFriendUi();
}

void LobbyFriendPanel::ShowFriendUi()
{
	scheduleUpdate();
}

void LobbyFriendPanel::HideFriendUi()
{
	unscheduleUpdate();

	LayerManager::getSingleton().popLayer("LobbyFriend");
	GameDataManager::getSingletonPtr()->FreeUiProcess();
}

void LobbyFriendPanel::ShowFriendTitie()
{
	GameDataManager::getSingletonPtr()->FreeUiProcess();

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_FRIEND);
		}
	}
}

void LobbyFriendPanel::HideFriendTitie()
{
	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MAIN);
		}
	}
}

void LobbyFriendPanel::SetFriendlList()
{
	if (m_TapIndex == 0)
	{
		mFriendInvitePanel->SetFriendlList();
	}
	else if (m_TapIndex == 2)
	{
		m_pFriendPanel->SetFriendlList();
	}
	else if (m_TapIndex == 1)
	{
		m_pRecommendPanel->SetRequestFriendList();
		m_pRecommendPanel->SetRecommendFriendList();
	}

}

bool LobbyFriendPanel::cellTouchStart(const CCPoint& tableTouchPoint)
{
	return false;
}

bool LobbyFriendPanel::cellTouchCancel(const CCPoint& tableTouchPoint)
{
	return false;
}

bool LobbyFriendPanel::cellTouch(const CCPoint& tableTouchPoint)
{
	return false;
}

void LobbyFriendPanel::updateNotiWidget()
{
	for (int i = 0; i < mNotiWidgets.size(); i++)
	{
		mNotiWidgets[i]->refresh();
	}
}

void LobbyFriendPanel::refreshFriendPanel()
{
	CCLog("refreshFriendPanel");
 	ClickTapButton(2);
 	if (m_pFriendPanel)
 		m_pFriendPanel->refreshTableView();
}

void LobbyFriendPanel::refreshRecommendPanel()
{
	CCLog("refreshRecommendPanel");
	ClickTapButton(1);
	if (m_pRecommendPanel)
		m_pRecommendPanel->refreshTableView();
}

void LobbyFriendPanel::refreshFaceookPanel()
{
	CCLog("refreshFaceookPanel");
	ClickTapButton(0);
	if (mFriendInvitePanel)
		mFriendInvitePanel->refreshTableView();
}

void LobbyFriendPanel::facebookRefresh()
{
	CCLog("log1");
	WebService::getSingletonPtr()->_sendFacebookRequestListReq();	
	if (mFriendInvitePanel && mFriendInvitePanel->isVisible())
		mFriendInvitePanel->facebookRefresh();
	CCLog("log2");
}
void LobbyFriendPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}