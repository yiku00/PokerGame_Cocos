#include "pch.h"
#include "LobbyChannelSubTopUiPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "LobbyUIPanel.h"
#include "GameStringDepot.h"

LobbyChannelSubTopUiPanel::LobbyChannelSubTopUiPanel()
{
	mLoginProcess = false;

	InitPanel();
	InitImage();
	initButton();

	setTouchable(true);
	setButtonListener(this);
}

LobbyChannelSubTopUiPanel::~LobbyChannelSubTopUiPanel()
{

}

void LobbyChannelSubTopUiPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_channel_subtoppanal.mxml");
}

void LobbyChannelSubTopUiPanel::InitImage()
{
	getSkel("skel_back")->playAnimation("back_seven");

	getLabel("txt_texas")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HOLDEM").c_str());
	getLabel("txt_badugi")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI").c_str());
	getLabel("txt_highlow")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HIGHLOW").c_str());
	getLabel("txt_sevenpoker")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SEVEN_POKER").c_str());

	getLabel("txt_texas")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_badugi")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_highlow")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_sevenpoker")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	getLabel("txt_sevenpoker")->setColor(COLOR_7POKER_OFF);
	getLabel("txt_highlow")->setColor(COLOR_HIGHLOW_OFF);
	getLabel("txt_badugi")->setColor(COLOR_BADUKI_OFF);
	getLabel("txt_texas")->setColor(COLOR_HOLDEM_OFF);

	getSkel("skel_effect1")->setVisible(false);
	getSkel("skel_effect2")->setVisible(false);
	getSkel("skel_effect3")->setVisible(false);
	getSkel("skel_effect4")->setVisible(false);
}

void LobbyChannelSubTopUiPanel::initButton()
{
	getButton("sbtn_button1")->getButtonSkelObject()->playAnimation("button_seven_off");
	getButton("sbtn_button2")->getButtonSkelObject()->playAnimation("button_highlow_off");
	getButton("sbtn_button3")->getButtonSkelObject()->playAnimation("button_badugi_off");
	getButton("sbtn_button4")->getButtonSkelObject()->playAnimation("button_texas_off");

	getButton("sbtn_button1")->setType(Button::ButtonType::NoPressImg);
	getButton("sbtn_button2")->setType(Button::ButtonType::NoPressImg);
	getButton("sbtn_button3")->setType(Button::ButtonType::NoPressImg);
	getButton("sbtn_button4")->setType(Button::ButtonType::NoPressImg);
	getButton("sbtn_buttonl2")->setType(Button::ButtonType::NoPressImg);
}


bool LobbyChannelSubTopUiPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}


void LobbyChannelSubTopUiPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void LobbyChannelSubTopUiPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyChannelSubTopUiPanel::resume()
{
}

void LobbyChannelSubTopUiPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;
	//if (name == "sbtn_button1")
	//{
	//	if (GameDataManager::getSingletonPtr()->GetUiState() == LOBBY_UI_7POKER)
	//		return;
	//	GameDataManager::getSingletonPtr()->FadeoutLobby(0.f);
	//	GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
	//	GameDataManager::getSingletonPtr()->CloseTopCoustomPopup();
	//	GameDataManager::getSingletonPtr()->MoveToUiState(LOBBY_UI_7POKER);
	//}
	//if (name == "sbtn_button2")
	//{
	//	if (GameDataManager::getSingletonPtr()->GetUiState() == LOBBY_UI_HIGHLOW)
	//		return;
	//	GameDataManager::getSingletonPtr()->FadeoutLobby(0.f);
	//	GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
	//	GameDataManager::getSingletonPtr()->CloseTopCoustomPopup();
	//	GameDataManager::getSingletonPtr()->MoveToUiState(LOBBY_UI_HIGHLOW);
	//}
	//if (name == "sbtn_button3")
	//{
	//	if (GameDataManager::getSingletonPtr()->GetUiState() == LOBBY_UI_BADUKI)
	//		return;
	//	GameDataManager::getSingletonPtr()->FadeoutLobby(0.f);
	//	GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
	//	GameDataManager::getSingletonPtr()->CloseTopCoustomPopup();
	//	GameDataManager::getSingletonPtr()->MoveToUiState(LOBBY_UI_BADUKI);
	//}
	//if (name == "sbtn_button4")
	//{
	//	if (GameDataManager::getSingletonPtr()->GetUiState() == LOBBY_UI_HOLDEM)
	//		return;
	//	GameDataManager::getSingletonPtr()->FadeoutLobby(0.f);
	//	GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
	//	GameDataManager::getSingletonPtr()->CloseTopCoustomPopup();
	//	GameDataManager::getSingletonPtr()->MoveToUiState(LOBBY_UI_HOLDEM);
	//}
	
}

void LobbyChannelSubTopUiPanel::update(float dt)
{
}

bool LobbyChannelSubTopUiPanel::handling(STCMD &stCmd)
{
	return false;
}

void LobbyChannelSubTopUiPanel::SetGameChannel(int _gamekind)
{
	switch (_gamekind)
	{
	case GameKind::GAMEKIND_7POKER:
		getButton("sbtn_button1")->getButtonSkelObject()->playAnimation("button_seven_on");
		getSkel("skel_effect1")->setVisible(true);
		getSkel("skel_back")->playAnimation("back_seven");
		getLabel("txt_sevenpoker")->setColor(COLOR_7POKER_ON);

		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		
		getButton("sbtn_button2")->getButtonSkelObject()->playAnimation("button_highlow_on");
		getSkel("skel_effect2")->setVisible(true);
		getSkel("skel_back")->playAnimation("back_highlow");
		getLabel("txt_highlow")->setColor(COLOR_HIGHLOW_ON);
		break;
	case GameKind::GAMEKIND_BADUKI:
		
		getButton("sbtn_button3")->getButtonSkelObject()->playAnimation("button_badugi_on");
		getSkel("skel_effect3")->setVisible(true);
		getSkel("skel_back")->playAnimation("back_badugi");
		getLabel("txt_badugi")->setColor(COLOR_BADUKI_ON);
		break;
	case GameKind::GAMEKIND_HOLDEM:
		
		getButton("sbtn_button4")->getButtonSkelObject()->playAnimation("button_texas_on");
		getSkel("skel_effect4")->setVisible(true);
		getSkel("skel_back")->playAnimation("back_texas");
		getLabel("txt_texas")->setColor(COLOR_HOLDEM_ON);
		break;
	}
}
