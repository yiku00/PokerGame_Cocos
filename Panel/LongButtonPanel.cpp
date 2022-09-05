#include "pch.h"
#include "LongButtonPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

LongButtonPanel::LongButtonPanel()
{
	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

LongButtonPanel::~LongButtonPanel()
{
}

void LongButtonPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_long_button.mxml");
}

void LongButtonPanel::InitImage()
{
	getLabel("txt_refill_content_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_refill_content")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_refill_limit_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_refill_limit")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
}

void LongButtonPanel::initButton()
{
	m_Button = getButton("sbtn_long_button");
}

void LongButtonPanel::onClicked(const string& name)
{

}

void LongButtonPanel::SetLeftText(string _text)
{
	getLabel("txt_refill_content_under")->setString(_text.c_str());
	getLabel("txt_refill_content")->setString(_text.c_str());
}

void LongButtonPanel::SetRightText(string _text)
{
	getLabel("txt_refill_limit_under")->setString(_text.c_str());
	getLabel("txt_refill_limit")->setString(_text.c_str());
}

void LongButtonPanel::SetEnableButton(bool _enable)
{
	getButton("sbtn_long_button")->setPaused(!_enable);
	getButton("sbtn_long_button")->setEnable(_enable);

	if (_enable == true)
	{
		getButton("sbtn_long_button")->getButtonSkelObject()->playAnimation("button_long_o");
	}
	else
	{
		getButton("sbtn_long_button")->getButtonSkelObject()->playAnimation("button_long_off");
	}
}
