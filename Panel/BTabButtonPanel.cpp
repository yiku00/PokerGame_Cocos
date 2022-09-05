#include "pch.h"
#include "BTabButtonPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

BTabButtonPanel::BTabButtonPanel()
{
	m_LeftText = nullptr;
	m_RightText = nullptr;
	m_LeftButton = nullptr;
	m_RightButton = nullptr;

	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

BTabButtonPanel::~BTabButtonPanel()
{
}

void BTabButtonPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_button_btab.mxml");
}

void BTabButtonPanel::InitImage()
{
	getLabel("txt_tab_left")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_tab_right")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	m_LeftText = getLabel("txt_tab_left");
	m_RightText = getLabel("txt_tab_right");
}

void BTabButtonPanel::initButton()
{
	m_LeftButton = getButton("sbtn_tab_left");
	m_RightButton = getButton("sbtn_tab_right");

	m_LeftButton->setType(Button::NoPressImg);
	m_RightButton->setType(Button::NoPressImg);
}

void BTabButtonPanel::onClicked(const string& name)
{
	if (name == m_LeftButton->getName())
	{
		m_LeftButton->setSkelAnimation("tab_bpanell_on", false);
		m_RightButton->setSkelAnimation("tab_bpanelr_off", false);

		m_LeftText->setColor(COLOR_TAP_ON);
		m_RightText->setColor(COLOR_TAP_OFF);
	}
	else if (name == m_RightButton->getName())
	{
		m_LeftButton->setSkelAnimation("tab_bpanell_off", false);
		m_RightButton->setSkelAnimation("tab_bpanelr_on", false);

		m_LeftText->setColor(COLOR_TAP_OFF);
		m_RightText->setColor(COLOR_TAP_ON);
	}

}

void BTabButtonPanel::SetButtonListener(Button::Listener* _listener)
{
	if (m_LeftButton == nullptr || m_RightButton == nullptr)
		return;

	m_LeftButton->setListener(_listener);
	m_RightButton->setListener(_listener);
}
