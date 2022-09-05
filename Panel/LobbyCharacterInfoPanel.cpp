#include "pch.h"
#include "LobbyCharacterInfoPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SimplePopupPanel.h"
#include "GameStringDepot.h"

LobbyCharacterInfoPanel::LobbyCharacterInfoPanel()
{
	mLoginProcess = false;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);
}

LobbyCharacterInfoPanel::~LobbyCharacterInfoPanel()
{
	//destruct();
}

void LobbyCharacterInfoPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_characterinfo.mxml");
}

void LobbyCharacterInfoPanel::InitImage()
{
	getLabel("txt_character_name")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
}

void LobbyCharacterInfoPanel::initButton()
{

}


bool LobbyCharacterInfoPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}

void LobbyCharacterInfoPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void LobbyCharacterInfoPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void LobbyCharacterInfoPanel::onClicked(const string& name)
{

}

void LobbyCharacterInfoPanel::resume()
{

}

bool LobbyCharacterInfoPanel::handling(STCMD &stCmd)
{
	return false;
}

void LobbyCharacterInfoPanel::update(float dt)
{

}
