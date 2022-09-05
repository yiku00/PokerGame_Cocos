#include "pch.h"
#include "LobbyLeftUiPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"
#include "LobbyUIPanel.h"

LobbyLeftUiPanel::LobbyLeftUiPanel()
{
	mLoginProcess = false;
	m_LetterNoti = nullptr;
	m_MissionNoti = nullptr;
	m_pLetterCount = nullptr;
	m_pMissionCount = nullptr;

	InitPanel();
	InitImage();
	initButton();

	
	setButtonListener(this);
}

LobbyLeftUiPanel::~LobbyLeftUiPanel()
{
}

void LobbyLeftUiPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_lobby_left_button.mxml");
}

void LobbyLeftUiPanel::InitImage()
{
	getSkel("skel_leftback")->setVisible(false);
	for (int _i = 0; _i < 5; _i++)
	{
		string _skelName = "skel_emphasis" + StringConverter::toString(_i + 1);
		getSkel(_skelName)->setVisible(false);
		getSkel(_skelName)->playAnimation("emphasis_end");
	}

	getLabel("txt_myroom_back")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_myroom")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_letter_back")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_letter")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_friend_back")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_friend")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_mission_back")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_mission")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_shop_back")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_shop")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	getLabel("txt_myroom_back")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYROOM_BUTTON").c_str());
	getLabel("txt_myroom")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYROOM_BUTTON").c_str());
	getLabel("txt_letter_back")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTERBOX_BUTTON").c_str());
	getLabel("txt_letter")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTERBOX_BUTTON").c_str());
	getLabel("txt_friend_back")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FRIEND_BUTTON").c_str());
	getLabel("txt_friend")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FRIEND_BUTTON").c_str());
	getLabel("txt_mission_back")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MISSION_BUTTON").c_str());
	getLabel("txt_mission")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MISSION_BUTTON").c_str());
	getLabel("txt_shop_back")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SHOP_BUTTON").c_str());
	getLabel("txt_shop")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SHOP_BUTTON").c_str());
}

void LobbyLeftUiPanel::initButton()
{
	for (int _i = 0; _i < 5; _i++)
	{
		string _btnlName = "sbtn_lobbyleft_button" + StringConverter::toString(_i + 1);
		getButton(_btnlName)->setSkelAnimation("lobbyleft_off_stay");
		getButton(_btnlName)->setType(Button::ButtonType::NoPressImg);
		getButton(_btnlName)->setListener(this);
	}
	getButton("sbtn_lobbyleft_button1")->getButtonSkelObject()->setSkin("myroom");
	getButton("sbtn_lobbyleft_button2")->getButtonSkelObject()->setSkin("letter");
	getButton("sbtn_lobbyleft_button3")->getButtonSkelObject()->setSkin("friend");
	getButton("sbtn_lobbyleft_button4")->getButtonSkelObject()->setSkin("mission");
	getButton("sbtn_lobbyleft_button5")->getButtonSkelObject()->setSkin("shop");

	CCPoint _NotiPos = getDummy("dmy_notification_icon1").origin;
	_NotiPos.x = _NotiPos.x - getButton("sbtn_lobbyleft_button1")->getPositionX();
	_NotiPos.y = (DESIGN_HEIGHT - _NotiPos.y) - getButton("sbtn_lobbyleft_button1")->getPositionY();

	if (m_LetterNoti == nullptr)
	{
		m_LetterNoti = new SkelObject();
		m_LetterNoti->setSkelAnim("ui/lobby_button_8888.json");
		m_LetterNoti->setPosition(_NotiPos);
		m_LetterNoti->playAnimation("notification_back");
		getButton("sbtn_lobbyleft_button2")->addChild(m_LetterNoti);
		m_LetterNoti->release();

		m_pLetterCount = new Nx::Label();
		m_pLetterCount->initWithString("99+", 13);
		m_pLetterCount->setColor(ccc3(250, 183, 96));
		m_pLetterCount->setPosition(ccp(0, 2));
		m_pLetterCount->setAnchorPoint(ccp(0.5f, 0.5f));
		m_LetterNoti->addChild(m_pLetterCount);
		m_pLetterCount->release();
	}

	if (m_MissionNoti == nullptr)
	{
		m_MissionNoti = new SkelObject();
		m_MissionNoti->setSkelAnim("ui/lobby_button_8888.json");
		m_MissionNoti->setPosition(_NotiPos);
		m_MissionNoti->playAnimation("notification_back");
		getButton("sbtn_lobbyleft_button4")->addChild(m_MissionNoti);
		m_MissionNoti->release();

		m_pMissionCount = new Nx::Label();
		m_pMissionCount->initWithString("99+", 13);
		m_pMissionCount->setColor(ccc3(250, 183, 96));
		m_pMissionCount->setPosition(ccp(0, 2));
		m_pMissionCount->setAnchorPoint(ccp(0.5f, 0.5f));
		m_MissionNoti->addChild(m_pMissionCount);
		m_pMissionCount->release();
	}
}

void LobbyLeftUiPanel::UpdateNotiData()
{
	if (GameDataManager::getSingletonPtr() == nullptr)
		return;

	if (m_LetterNoti)
	{
		int _size = GameDataManager::getSingletonPtr()->m_pLetterInfoList.size();
		if (_size == 0)
		{
			m_LetterNoti->setVisible(false);
		}
		else
		{
			m_LetterNoti->setVisible(true);
			if (_size > 99)
			{
				m_pLetterCount->setString("99+");
			}
			else
			{
				string _count = StringConverter::toString(_size);
				m_pLetterCount->setString(_count.c_str());
			}
		}
	}

	if (m_MissionNoti)
	{
		int _size = 0;
		for (W_QuestInfo* _pInfo : GameDataManager::getSingletonPtr()->m_pQuestInfoList)
		{
			if (_pInfo->queststatus() == W_QuestInfo_eQuestStatus_Complete)
			{
				_size++;
			}
		}

		for (W_EventInfo* _pInfo : GameDataManager::getSingletonPtr()->m_EventList)
		{
			if (_pInfo->status() == W_QuestInfo_eQuestStatus_Complete)
			{
				_size++;
			}
		}


		if (_size == 0)
		{
			m_MissionNoti->setVisible(false);
		}
		else
		{
			if (_size > 99)
			{
				m_pMissionCount->setString("99+");
			}
			else
			{
				string _count = StringConverter::toString(_size);
				m_pMissionCount->setString(_count.c_str());
			}
		}
	}
}


bool LobbyLeftUiPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}


void LobbyLeftUiPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void LobbyLeftUiPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyLeftUiPanel::resume()
{
}

void LobbyLeftUiPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	LobbyUIPanel* _pLobbyUiPanel = dynamic_cast<LobbyUIPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyUI"));
	_pLobbyUiPanel->onClicked(name);

	//for (int _i = 0; _i < 5; _i++)
	//{
	//	string _btnlName = "sbtn_lobbyleft_button" + StringConverter::toString(_i + 1);
	//	if (name == _btnlName)
	//	{
	//		PlayButtonEffect(_i);
	//	}
	//}
}

void LobbyLeftUiPanel::update(float dt)
{
}

bool LobbyLeftUiPanel::handling(STCMD &stCmd)
{
	return false;
}

void LobbyLeftUiPanel::PlayButtonEffect(int _idx)
{
	if (_idx < 0 || _idx >= 5)
		return;

	string _skelName = "skel_emphasis" + StringConverter::toString(_idx + 1);
	getSkel(_skelName)->setVisible(true);
	getSkel(_skelName)->playAnimation("emphasis_start");
	getSkel(_skelName)->appendAnimation("emphasis_loop");
	getSkel(_skelName)->appendAnimation("emphasis_end");
}
void LobbyLeftUiPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}
