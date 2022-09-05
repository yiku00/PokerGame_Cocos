#include "pch.h"
#include "LobbyRoomTopUiPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"

LobbyRoomTopUiPanel::LobbyRoomTopUiPanel()
{
	mLoginProcess = false;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);
}

LobbyRoomTopUiPanel::~LobbyRoomTopUiPanel()
{
}

void LobbyRoomTopUiPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_room_toppanel.mxml");
}

void LobbyRoomTopUiPanel::InitImage()
{
	//getSkel("skel_toppanal");
	//getSkel("skel_topsearch_panel_center");
	//getSkel("skel_topsearch_panel_leftend");
	//getSkel("skel_topsearch_panel_rightend");
	//getSkel("skel_top_crack1");
	//getSkel("skel_top_crack2");

	getLabel("txt_room_title_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_room_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	getTextField("fld_room_search")->setAnchorPoint(ccp(0.5f, LABEL_ANCHOR_OFFSET));
}

void LobbyRoomTopUiPanel::initButton()
{
	getButton("sbtn_button_room_make_stay")->setType(Button::ButtonType::NoPressImg);
	getButton("sbtn_button_straight_join_stay")->setType(Button::ButtonType::NoPressImg);
	getButton("sbtn_roomsearch_touch_size")->setType(Button::ButtonType::NoPressImg);
	getButton("sbtn_search_stay")->setType(Button::ButtonType::NoPressImg);
	getButton("sbtn_option_button")->setType(Button::ButtonType::NoPressImg);

	getButton("sbtn_option_button")->getButtonSkelObject()->playAnimation("cancel_stay");
}


bool LobbyRoomTopUiPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	
	return false;
}


void LobbyRoomTopUiPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void LobbyRoomTopUiPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyRoomTopUiPanel::resume()
{
}

void LobbyRoomTopUiPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

}

void LobbyRoomTopUiPanel::update(float dt)
{
}

bool LobbyRoomTopUiPanel::handling(STCMD &stCmd)
{
	return false;
}
void LobbyRoomTopUiPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}
