#include "pch.h"
#include "PokerUnderImoticonPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "Web/WebService.h"
#include "RoomUserData.h"
#include "GameStringDepot.h"

PokerUnderImoticonPanel::PokerUnderImoticonPanel()
{
	InitPanel();
	InitImage();
	InitButton();

	setTouchable(false);
	setButtonListener(this);

}

PokerUnderImoticonPanel::~PokerUnderImoticonPanel()
{
	removeAllChildren();
}

void PokerUnderImoticonPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_underborad_emoticon.mxml");
	setContentSize(getDummy("dmy_underborad_emoticon").size);

	setPositionY(getContentSize().height - DESIGN_HEIGHT);
}

void PokerUnderImoticonPanel::InitImage()
{
	getLabel("txt_emoti_sad")->setString(GameStringDepot::getSingletonPtr()->getString("PokerUnderImoticonPanel_1").c_str());
	getLabel("txt_emoti_angry")->setString(GameStringDepot::getSingletonPtr()->getString("PokerUnderImoticonPanel_2").c_str());
	getLabel("txt_emoti_sorry")->setString(GameStringDepot::getSingletonPtr()->getString("PokerUnderImoticonPanel_3").c_str());
	getLabel("txt_emoti_compli")->setString(GameStringDepot::getSingletonPtr()->getString("PokerUnderImoticonPanel_4").c_str());
	getLabel("txt_emoti_surprise")->setString(GameStringDepot::getSingletonPtr()->getString("PokerUnderImoticonPanel_5").c_str());
	getLabel("txt_emoti_thanks")->setString(GameStringDepot::getSingletonPtr()->getString("PokerUnderImoticonPanel_6").c_str());
}

void PokerUnderImoticonPanel::InitButton()
{
	m_imotiButton[0] = getButton("sbtn_emoti_sad");
	m_imotiButton[1] = getButton("sbtn_emoti_angry");
	m_imotiButton[2] = getButton("sbtn_emoti_sorry");
	m_imotiButton[3] = getButton("sbtn_emoti_compli");
	m_imotiButton[4] = getButton("sbtn_emoti_surprise");
	m_imotiButton[5] = getButton("sbtn_emoti_thanks");
}


void PokerUnderImoticonPanel::onClicked(const string& name)
{
	for (int _i = 0; _i < 6; _i++)
	{
		if (name == m_imotiButton[_i]->getName())
		{
			SetCharacterEmotion(_i);
			return;
		}
	}
}

void PokerUnderImoticonPanel::ShowResultImoticon(bool _visible)
{
	setVisible(_visible);
	for (int _i = 0; _i < 6; _i++)
	{
		m_imotiButton[_i]->setEnable(_visible);
	}
}

void PokerUnderImoticonPanel::SetCharacterEmotion(int _imotiType)
{
	EmotionType _type = EMOTION_NO;

	switch (_imotiType)
	{
	case EMOTI_SAD:
		_type = EMOTION_SADNESS;
		break;
	case EMOTI_ANGRY:
		_type = EMOTION_ANGRY;
		break;
	case EMOTI_SORRY:
		_type = EMOTION_SORRY;
		break;
	case EMOTI_COMPLI:
		_type = EMOTION_CELEBRATE;
		break;
	case EMOTI_SURPRISE:
		_type = EMOTION_SURPRIZE;
		break;
	case EMOTI_THANK:
		_type = EMOTION_THANKS;
		break;
	default:
		break;
	}
	ShowResultImoticon(false);
	TCPService::getSingletonPtr()->SendEmotionReq(_type);
}

void PokerUnderImoticonPanel::update(float dt)
{

}

bool PokerUnderImoticonPanel::handling(STCMD &stCmd)
{
	return false;
}
void PokerUnderImoticonPanel::onEnter()
{
	Panel::onEnter();

	scheduleUpdate();
}