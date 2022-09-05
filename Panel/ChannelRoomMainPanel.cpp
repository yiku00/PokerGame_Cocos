#include "pch.h"
#include "ChannelRoomMainPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
//#include "SimplePopupPanel.h"
//#include "HeroApp.h"

#include "Web/WebService.h"
#include "ChannelRoomCell.h"
#include "GameStringDepot.h"

ChannelRoomMainPanel::ChannelRoomMainPanel()
{
	mLoginProcess = false;
	InitPanel();		
}

ChannelRoomMainPanel::~ChannelRoomMainPanel()
{
	//destruct();
}

void ChannelRoomMainPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_room_list_under.mxml");
	setButtonListener(this);
	m_ContentRect = getDummy("dmy_room_list_under");
	m_pTitle = getLabel("txt_room_title");
	m_pTitleUnder = getLabel("txt_room_title_under");
	m_searchField = getTextField("fld_room_search");	
	m_pRoomMakeBtn = getButton("sbtn_button_make");
	m_pRoomJoinBtn = getButton("sbtn_button_enter");
	m_pSearchBtn = getButton("sbtn_search");
	m_pRoomInputBtn = getButton("sbtn_touchsize_search");
	m_pRoomInputBtn->setVisible(false);
	string bgStr = "";
	string makeRoomStr = "";
	string buttonStr = "";
	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_7POKER) {
		buttonStr = "button_seven";
		bgStr = "chpanel_seven";
		makeRoomStr = "button_make_seven";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HIGH_LOW) {
		buttonStr = "button_highlow";
		bgStr = "chpanel_highlow";
		makeRoomStr = "button_make_highlow";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_BADUKI) {
		buttonStr = "button_badugi";
		bgStr = "chpanel_badugi";
		makeRoomStr = "button_make_badugi";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM) {
		buttonStr = "button_texas";
		bgStr = "chpanel_texas";
		makeRoomStr = "button_make_texas";
	}

	m_pRoomMakeBtn->setSkelAnimation(makeRoomStr);
	m_pRoomJoinBtn->setSkelAnimation(buttonStr);
	getSkel("skel_chpanel")->playAnimation(bgStr);

	string _infoText = "[";
	switch (GameDataManager::getSingletonPtr()->m_BettingRule)
	{
	case BettingRule::RULE_FOUR_CARD:
		_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_RULE_FOUR_CARD");
		break;
	case BettingRule::RULE_FIVE_CARD:
		_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_RULE_FIVE_CARD");
		break;
	case BettingRule::RULE_SIX_CARD:
		_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_RULE_SIX_CARD");
		break;
	}
	//SeedMoney
	_infoText += "/" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(GameDataManager::getSingletonPtr()->m_seedMoney), 1);
	_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT") + "]";

	m_pTitle->setString(_infoText.c_str());
	m_pTitleUnder->setString(_infoText.c_str());

	m_searchField->setPlaceHolder(GameStringDepot::getSingletonPtr()->getString("TXT_INPUT_SEARCHROOM").c_str());
	m_searchField->setString("");


	m_pChannelRoomUi = new ChannelRoomUiPanel();
	addChild(m_pChannelRoomUi);
	m_pChannelRoomUi->release();

	CCPoint rommuiPos = getDummy("dmy_scrollsize").origin;
	m_pChannelRoomUi->setPositionX(rommuiPos.x);
	m_pChannelRoomUi->setPositionY(-rommuiPos.y);	
	//바로입장
	getLabel("txt_enter_under")->setString(GameStringDepot::getSingletonPtr()->getString("ChannelRoomMainPanel_ENTER").c_str());
	getLabel("txt_enter")->setString(GameStringDepot::getSingletonPtr()->getString("ChannelRoomMainPanel_ENTER").c_str());
	//방만들기
	getLabel("txt_make_room")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MAKE_ROOM_UNIT").c_str());
}

void ChannelRoomMainPanel::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void ChannelRoomMainPanel::onClicked(const string& name)
{
	

}

void ChannelRoomMainPanel::update(float dt)
{

}

bool ChannelRoomMainPanel::handling(STCMD &stCmd)
{
	
	return false;
}

void ChannelRoomMainPanel::ShowRoomList(bool _visible)
{
	if (_visible)
	{
		setPosition(m_ShowPosition);
	}
	else
	{
		setPosition(m_HidePosition);
	}

	setVisible(_visible);
	setTouchable(_visible);
	m_pChannelRoomUi->setTouchable(_visible);
}

bool ChannelRoomMainPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (pTouch->getLocation().y >= DESIGN_HEIGHT - 72.f)
		return false;

	return true;
}

void ChannelRoomMainPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}
