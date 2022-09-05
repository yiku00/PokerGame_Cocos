#include "pch.h"
#include "emoticonPanel.h"
#include "GameDataManager.h"
#include "socket\TCPService.h"
#include "GameStringDepot.h"

#define MOVE_POT_MONEY_ANITIME 1.8f
#define DISAPPEAR_ACTION_TAG 255

emoticonPanel::emoticonPanel()
{
	_isVisible = false;
	Init();
}
emoticonPanel::~emoticonPanel()
{
	mMainPanel->removeAllChildren(); 
	removeAllChildren();
}
void emoticonPanel::Init()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		mMainPanel->construct(getMxmlPath() + "dmy_emoticon.mxml");
		addChild(mMainPanel, 10);
		mMainPanel->release();
		CCSize contentsSize = mMainPanel->getDummy("dmy_emoticon").size;
		mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		this->setPosition(mParentPanel->getImage("dmy_emoticon")->getPosition());

		mMainPanel->getLabel("txt_angry")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_anger").c_str());
		mMainPanel->getLabel("txt_compli")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_compliment").c_str());
		mMainPanel->getLabel("txt_congra")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_celebration").c_str());
		mMainPanel->getLabel("txt_haha")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_laugh").c_str());
		mMainPanel->getLabel("txt_happy")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_pleasure").c_str());
		mMainPanel->getLabel("txt_hurry")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_quick").c_str());
		mMainPanel->getLabel("txt_sad")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_sadness").c_str());
		mMainPanel->getLabel("txt_sorry")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_apology").c_str());
		mMainPanel->getLabel("txt_surprise")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_surprised").c_str());
		mMainPanel->getLabel("txt_thanks")->setString(GameStringDepot::getSingleton().getString("emoticonPanel_thank").c_str());		
	}
	InitImage();
}

void emoticonPanel::InitImage()
{
	//init Image
	m_pEmoticonBG = mMainPanel->getSkel("skel_emoti_back");
	m_pEmoticonBG->setVisible(false);
	m_pEmoticonBG->setListener(this);

	for (int _i = 0; _i < 10; _i++)
	{
		string _objName = "sbtn_emoti_button" + StringConverter::toString(_i + 1);
		m_pButton[_i] = mMainPanel->getButton(_objName);
		m_pButton[_i]->setType(Button::NoPressImg);
		m_pButton[_i]->setListener(this);
		m_pButton[_i]->setVisible(false);
		m_pButton[_i]->setEnable(false);
	}

	setVisibleButtonLabel(false);

	m_pEmticonButton = mParentPanel->getButton("sbtn_emoti_position");
	m_pEmticonButton->setVisible(false);
	m_pEmticonButton->setListener(this);

	((sButton*)(m_pButton[0]))->setSkelSkin("angry");
	((sButton*)(m_pButton[1]))->setSkelSkin("compli");
	((sButton*)(m_pButton[2]))->setSkelSkin("congra");
	((sButton*)(m_pButton[3]))->setSkelSkin("haha");
	((sButton*)(m_pButton[4]))->setSkelSkin("happy");
	((sButton*)(m_pButton[5]))->setSkelSkin("hurry");
	((sButton*)(m_pButton[6]))->setSkelSkin("sad");
	((sButton*)(m_pButton[7]))->setSkelSkin("sorry");
	((sButton*)(m_pButton[8]))->setSkelSkin("surprise");
	((sButton*)(m_pButton[9]))->setSkelSkin("thanks");
}

void emoticonPanel::onAnimationStarted(const string& ani)
{
	if (ani.find("emoti_back_stay") != string::npos)
	{
		for (int _i = 0; _i < 10; _i++)
		{
			m_pButton[_i]->setVisible(true);
			m_pButton[_i]->setEnable(true);
		}
		setVisibleButtonLabel(true);
	}	
}

void emoticonPanel::onAnimationEnded(const string& ani)
{
	if (ani.find("emoti_back_end") != string::npos)
	{
		m_pEmoticonBG->setVisible(false);
	}
}

void emoticonPanel::onClicked(const string& buttonName)
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
		return;

	string _name = nxReplace(buttonName, "sbtn_emoti_", "");
	if (_name == "position")
	{
		//big test......................................................//
		//GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->ShowCommnityBig(!GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isBigCommunityCard);
		//..............................................................//
		if (_isVisible == true)
		{
			SetVisiebleEmotiWindow(false);
		}
		else
		{
			SetVisiebleEmotiWindow(true);
		}
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		return;
	}

	_name = nxReplace(buttonName, "sbtn_emoti_button", "");
	int _val = StringConverter::parseInt(_name);
	m_pButton[_val - 1]->setSkelAnimation("emoti_button_in", false);
	m_pButton[_val - 1]->setSkelAppendAnimation("emoti_button_out", false);

	TCPService::getSingletonPtr()->SendEmotionReq(_val);

	//int _myPo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_MyPo;
	//RoomUserData* _userData = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_myPo);
	//switch (_val)
	//{
	//case EMOTION_ANGRY:
	//	_userData->PlayCharacterAnimation(GESTURE_ANGRY);
	//	break;
	//case EMOTION_GOOD:
	//	_userData->PlayCharacterAnimation(GESTURE_GOOD);
	//	break;
	//case EMOTION_CELEBRATE:
	//	_userData->PlayCharacterAnimation(GESTURE_CELEBRATE);
	//	break;
	//case EMOTION_LAUGH:
	//	_userData->PlayCharacterAnimation(GESTURE_LAUGH);
	//	break;
	//case EMOTION_PLEASURE:
	//	_userData->PlayCharacterAnimation(GESTURE_PLEASURE);
	//	break;
	//case EMOTION_HURRY:
	//	_userData->PlayCharacterAnimation(GESTURE_HURRY);
	//	break;
	//case EMOTION_SADNESS:
	//	_userData->PlayCharacterAnimation(GESTURE_SADNESS);
	//	break;
	//case EMOTION_SORRY:
	//	_userData->PlayCharacterAnimation(GESTURE_SORRY);
	//	break;
	//case EMOTION_SURPRIZE:
	//	_userData->PlayCharacterAnimation(GESTURE_SURPRIZE);
	//	break;
	//case EMOTION_THANKS:
	//	_userData->PlayCharacterAnimation(GESTURE_THANKS);
	//	break;
	//default:
	//	break;
	//}
	SetVisiebleEmotiWindow(false);
}

void emoticonPanel::SetVisiebleEmotiWindow(bool _visible)
{
	if (_isVisible == true && _visible == false)
	{
		stopActionByTag(DISAPPEAR_ACTION_TAG);
		for (int _i = 0; _i < 10; _i++)
		{
			m_pButton[_i]->setVisible(false);
			m_pButton[_i]->setEnable(false);
		}
		setVisibleButtonLabel(false);
		m_pEmoticonBG->playAnimation("emoti_back_end");
		_isVisible = false;
	}
	else if (_isVisible == false && _visible == true)
	{
		m_pEmoticonBG->setVisible(true);
		m_pEmoticonBG->playAnimation("emoti_back_start");
		m_pEmoticonBG->appendAnimation("emoti_back_stay");
		_isVisible = true;
		CCDelayTime* delay = CCDelayTime::create(3.0f);
		CCFiniteTimeAction* callback = CCCallFunc::create(this, callfunc_selector(emoticonPanel::onCloseAction));
		CCAction* disAppearAction = CCSequence::create(delay, callback, NULL);
		disAppearAction->setTag(DISAPPEAR_ACTION_TAG);
		runAction(disAppearAction);
	}
}

void emoticonPanel::onCloseAction()
{
	SetVisiebleEmotiWindow(false);
}

void emoticonPanel::setVisibleButtonLabel(bool visible)
{
	mMainPanel->getLabel("txt_angry")->setVisible(visible);
	mMainPanel->getLabel("txt_compli")->setVisible(visible);
	mMainPanel->getLabel("txt_congra")->setVisible(visible);
	mMainPanel->getLabel("txt_haha")->setVisible(visible);
	mMainPanel->getLabel("txt_happy")->setVisible(visible);
	mMainPanel->getLabel("txt_hurry")->setVisible(visible);
	mMainPanel->getLabel("txt_sad")->setVisible(visible);
	mMainPanel->getLabel("txt_sorry")->setVisible(visible);
	mMainPanel->getLabel("txt_surprise")->setVisible(visible);
	mMainPanel->getLabel("txt_thanks")->setVisible(visible);
}
