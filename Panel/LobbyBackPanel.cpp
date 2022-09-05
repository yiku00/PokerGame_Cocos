#include "pch.h"
#include "LobbyBackPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "SimplePopupPanel.h"
#include "PokerPlayerInfoPanel.h"
#include "PokerResourceHelper.h"

LobbyBackPanel::LobbyBackPanel()
{
	
	InitPanel();
	InitImage();
}

LobbyBackPanel::~LobbyBackPanel()
{
	//destruct();
}

void LobbyBackPanel::InitPanel()
{
	construct(getMxmlPath() + "lobby_back.mxml");
}

void LobbyBackPanel::InitImage()
{
	
}

void LobbyBackPanel::resume()
{
}

void LobbyBackPanel::update(float dt)
{
	if (GameDataManager::getSingletonPtr()->m_pChannelListPanel != nullptr)
		return;	
}

bool LobbyBackPanel::handling(STCMD &stCmd)
{
//	if (!mLoginProcess)
//		return false;
//
//	if (auto *pstIt = castCMD<STCMD_ILOVEGAME_LOGINWITHTOKEN_RESULT>(&stCmd))
//	{
//		STCMD_ILOVEGAME_LOGINWITHTOKEN_RESULT res = *pstIt;
//		if (res.success) {
//
//			if (res.isSimple) {
//				string id = *mIdField->getInputText();
//				string pw = *mPassField->getInputText();
//				SocialManager::getSingleton().getInterface()->loginId(id, pw);
//			}
//			else {
//				SocialManager::getSingleton().getInterface()->login();
//			}
//
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
//			if (LayerManager::getSingleton().getCurrentLayer() == this)
//				LayerManager::getSingleton().popLayer();
//#endif
//		}		
//		else {
//			mLoginProcess = false;
//
//			CSJson::Reader reader;
//			CSJson::Value params;
//			reader.parse(res.result, params);
//			string msg = "";
//			string notice = "";
//			if (params.isMember("error"))
//				msg = params["error"].asString();
//			else
//				msg = "LOGINWITHTOKEN Failed.";
//
//			//HeroApp::getSingleton().notiServerErrorMessage(msg, "", notice);
//
//			return true;
//		}
//	}
	return false;
}

void LobbyBackPanel::MakeCharacter(int friendIdx, int _chracterId)
{
	
}

void LobbyBackPanel::CharacterIdleAction(int _idx)
{
	
}

void LobbyBackPanel::CharacterAction(int _idx)
{
	
}

bool LobbyBackPanel::CharacterCollisionCheck(CCPoint _touchPoint)
{
	return false;
}

void LobbyBackPanel::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
		HeroApp::getSingleton().exit();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_F9) {
		Director::getInstance()->setAnimationInterval(1.0 / 5);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_F8) {
		Director::getInstance()->setAnimationInterval(1.0 / 60);
	}
}
void LobbyBackPanel::onEnter()
{
	Panel::onEnter();

	setKeypadEnabled(true);
	scheduleUpdate();
}