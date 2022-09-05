#include "pch.h"
#include "NotiTalkListPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"


NotiTalkListPanel::NotiTalkListPanel(TALK_LIST_TYPE type)
{
	mType = type;
	initPanel();
}

NotiTalkListPanel::~NotiTalkListPanel()
{

}

void NotiTalkListPanel::initPanel()
{
	mMainPanel = new Panel();
	if (mType == TALK_POKER_BTN_LIST) {
		mMainPanel->construct(getMxmlPath() + "dmy_pan_info1.mxml");
		mMainPanel->getLabel("txt_info6")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_1").c_str());
		mMainPanel->getLabel("txt_info5")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_2").c_str());
		mMainPanel->getLabel("txt_info4")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_3").c_str());
		mMainPanel->getLabel("txt_info3")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_4").c_str());				
	}
	else if (mType == TALK_HIGHLOW_BTN_LIST) {
		mMainPanel->construct(getMxmlPath() + "dmy_pan_info2.mxml");		
		mMainPanel->getLabel("txt_info1")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC16_1").c_str());
		mMainPanel->getLabel("txt_info2")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC16_2").c_str());
		mMainPanel->getLabel("txt_info3")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC16_3").c_str());
	}
	else if (mType == TALK_BADUKI_BTN_LIST) {
		mMainPanel->construct(getMxmlPath() + "dmy_pan_info3.mxml");
		mMainPanel->getLabel("txt_info1")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC17_1").c_str());
		mMainPanel->getLabel("txt_info2")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC17_2").c_str());
		mMainPanel->getLabel("txt_info3")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC17_3").c_str());
	}
	else if (mType == TALK_HOLDEM_BTN_LIST) {
		mMainPanel->construct(getMxmlPath() + "dmy_pan_info4.mxml");
		mMainPanel->getLabel("txt_info6")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_1").c_str());
		mMainPanel->getLabel("txt_info5")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_2").c_str());
		mMainPanel->getLabel("txt_info4")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_3").c_str());
		mMainPanel->getLabel("txt_info3")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_4").c_str());
		mMainPanel->getLabel("txt_info7")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC18").c_str());
	}
	else if (mType == TALK_HOLDEM_COMMUNITY) {
		mMainPanel->construct(getMxmlPath() + "dmy_pan_info5.mxml");
		mMainPanel->getLabel("txt_info")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC19").c_str());
	}
	addChild(mMainPanel);
	mMainPanel->release();
	CCSize _contentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(_contentSize.height - DESIGN_HEIGHT - _contentSize.height / 2.f);
	mMainPanel->setPositionX(-_contentSize.width / 2.f);
	mMainPanel->setContentSize(_contentSize);
	this->setContentSize(_contentSize);
	this->setPositionX(DESIGN_WIDTH / 2);
	this->setPositionY(DESIGN_HEIGHT / 2);
}

void NotiTalkListPanel::setHalfMoney(string halfMoneyStr)
{
	useBigBtnDesc(false);
	if (mType == TALK_HIGHLOW_BTN_LIST || mType == TALK_BADUKI_BTN_LIST)
		return;

	if (mMainPanel->hasElement("txt_info1"))
		mMainPanel->getLabel("txt_info1")->setString(halfMoneyStr.c_str());
	if (mMainPanel->hasElement("txt_batt1"))
		mMainPanel->getLabel("txt_batt1")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_6").c_str());	
}

void NotiTalkListPanel::setQuarterMoney(string quarterMoneyStr)
{
	if (mType == TALK_HIGHLOW_BTN_LIST || mType == TALK_BADUKI_BTN_LIST)
		return;
	if (mMainPanel->hasElement("txt_info2"))
		mMainPanel->getLabel("txt_info2")->setString(quarterMoneyStr.c_str());
	if (mMainPanel->hasElement("txt_batt2"))
		mMainPanel->getLabel("txt_batt2")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_POPUP_DESC15_5").c_str());	
}

void NotiTalkListPanel::setMaxMoney(string maxMoneyStr)
{
	if (mType == TALK_HIGHLOW_BTN_LIST || mType == TALK_BADUKI_BTN_LIST)
		return;

	useBigBtnDesc(true);

	if (mMainPanel->hasElement("txt_batt7"))
		mMainPanel->getLabel("txt_batt7")->setString(maxMoneyStr.c_str());
}

void NotiTalkListPanel::setBettingCall()
{
	useBigBtnDesc(false);
}

void NotiTalkListPanel::useBigBtnDesc(bool visible)
{
	if (mMainPanel->hasElement("skel_pan7"))
		mMainPanel->getImage("skel_pan7")->setVisible(visible);

	if (mMainPanel->hasElement("txt_batt7"))
		mMainPanel->getLabel("txt_batt7")->setVisible(visible);

	if (mMainPanel->hasElement("txt_info7"))
		mMainPanel->getLabel("txt_info7")->setVisible(visible);

}
