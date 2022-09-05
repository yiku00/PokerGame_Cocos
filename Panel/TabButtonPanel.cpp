#include "pch.h"
#include "TabButtonPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

TabButtonPanel::TabButtonPanel()
{
	m_OnText = nullptr;
	m_OffText = nullptr;
	m_Button = nullptr;

	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

TabButtonPanel::~TabButtonPanel()
{
}

void TabButtonPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_button_tab.mxml");
}

void TabButtonPanel::InitImage()
{
	getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	m_OffText = getLabel("txt_off_tab");
	m_OnText = getLabel("txt_on_tab");

	m_OffText->setVisible(false);
}

void TabButtonPanel::initButton()
{
	m_Button = getButton("sbtn_button");
}

void TabButtonPanel::onClicked(const string& name)
{

}

void TabButtonPanel::SetButtonListener(Button::Listener* _listener)
{
	if (m_Button == nullptr)
		return;

	m_Button->setListener(_listener);
}

void TabButtonPanel::SetButtonText(string _text)
{
	m_OnText->setString(_text.c_str());
	m_OffText->setString(_text.c_str());
}

void TabButtonPanel::SetBtnOnOff(bool _on)
{
	if (m_Button == nullptr)
		return;

	if (_on)
	{
		m_Button->setSkelAnimation("tab_on");

		m_OnText->setVisible(true);
		m_OffText->setVisible(false);
	}
	else
	{
		m_Button->setSkelAnimation("tab_off");

		m_OnText->setVisible(false);
		m_OffText->setVisible(true);
	}
}
