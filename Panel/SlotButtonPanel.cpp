#include "pch.h"
#include "SlotButtonPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

SlotButtonPanel::SlotButtonPanel()
{
	m_TextShadow = nullptr;
	m_Text = nullptr;
	m_Button = nullptr;

	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

SlotButtonPanel::~SlotButtonPanel()
{
	//destruct();
}

void SlotButtonPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_button_slot.mxml");
}

void SlotButtonPanel::InitImage()
{
	m_GetIcon = getSkel("skel_icon");
	
	m_TextShadow = getLabel("txt_button2_under");
	m_Text = getLabel("txt_button2");
	m_GetTextShadow = getLabel("txt_button1_under");
	m_GetText = getLabel("txt_button1");

	m_TextShadow->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_Text->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_GetTextShadow->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_GetText->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	m_TextShadow->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FRIEND_APPLY").c_str());
	m_TextShadow->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FRIEND_APPLY").c_str());
}

void SlotButtonPanel::initButton()
{
	m_Button = getButton("sbtn_button");
	SetBtnType(TYPE_APPLY_FRIEND);
}

void SlotButtonPanel::onClicked(const string& name)
{
	
}

void SlotButtonPanel::SetBtnType(int _type)
{
	m_ButtonType = _type;

	if (_type == TYPE_APPLY_FRIEND)
	{
		m_GetIcon->setVisible(false);
		m_GetTextShadow->setVisible(false);
		m_GetText->setVisible(false);
		m_TextShadow->setVisible(true);
		m_Text->setVisible(true);
	}
	else
	{
		m_GetIcon->setVisible(true);
		m_GetTextShadow->setVisible(true);
		m_GetText->setVisible(true);
		m_TextShadow->setVisible(false);
		m_Text->setVisible(false);
	}

	switch (_type)
	{
	case TYPE_GET_CHIP:
		m_GetIcon->playAnimation("icon_chipget", true);
		SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_GET_GIFT"));
		break;
	case TYPE_GET_CHIP_OFF:
		m_GetIcon->playAnimation("icon_chipget_off", true);
		SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_GET_GIFT"));
		break;
	case TYPE_SEND_CHIP:
		m_GetIcon->playAnimation("icon_chipgive", true);
		SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_SEND_GIFT"));
		break;
	case TYPE_SEND_CHIP_OFF:
		m_GetIcon->playAnimation("icon_chipgive_off", true);
		SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_SEND_GIFT"));
		break;
	case TYPE_GET_GOLD:
		m_GetIcon->playAnimation("icon_goldget", true);
		SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_GET_GIFT"));
		break;
	case TYPE_GET_GOLD_OFF:
		m_GetIcon->playAnimation("icon_goldget_off", true);
		SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_GET_GIFT"));
		break;
	case TYPE_SEND_GOLD:
		m_GetIcon->playAnimation("icon_goldgive", true);
		SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_SEND_GIFT"));
		break;
	case TYPE_SEND_GOLD_OFF:
		m_GetIcon->playAnimation("icon_goldgive_off", true);
		SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_SEND_GIFT"));
		break;
	case TYPE_APPLY_FRIEND:
		SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_FRIEND_APPLY"));
		break;
	}
}

void SlotButtonPanel::SetButtonListener(Button::Listener* _listener)
{
	if (m_Button == nullptr)
		return;

	m_Button->setListener(_listener);
}

void SlotButtonPanel::SetBtnText(string _text)
{
	if (m_ButtonType == TYPE_APPLY_FRIEND)
	{
		m_TextShadow->setString(_text.c_str());
		m_Text->setString(_text.c_str());
	}
	else
	{
		m_GetTextShadow->setString(_text.c_str());
		m_GetText->setString(_text.c_str());
	}
}

