#include "pch.h"
#include "BankInOutPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"


BankInOutPanel::BankInOutPanel(bool isInput , string desc)
{
	mDescStr = desc;
	mIsInput = isInput;
	initPanel();
}

BankInOutPanel::~BankInOutPanel()
{
	//destruct();
}

void BankInOutPanel::onClicked(const string& name)
{
	if (name == getButtonName(mCancelBtn->getSmallButton())) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
}

void BankInOutPanel::initPanel()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_bank_board.mxml");
	setButtonListener(this);
	mTitle = getLabel("txt_title");
	mTitleUnder = getLabel("txt_title_under");

	if (isInputType()) {
		mTitle->setString(GameStringDepot::getSingleton().getString("BankInOutPanel_IN_TITLE").c_str());
		mTitleUnder->setString(GameStringDepot::getSingleton().getString("BankInOutPanel_IN_TITLE").c_str());
	}
	else {
		mTitle->setString(GameStringDepot::getSingleton().getString("BankInOutPanel_OUT_TITLE").c_str());
		mTitleUnder->setString(GameStringDepot::getSingleton().getString("BankInOutPanel_OUT_TITLE").c_str());
	}

	getLabel("txt_info")->setString(GameStringDepot::getSingleton().getString("BankInOutPanel_PROCESS").c_str());

	mDesc = getLabel("txt_item_name");	
	mDesc->setString(mDescStr.c_str());
	mCancelBtn = new SmallBtnPanel(this, "cancel");
	addChild(mCancelBtn);
	mCancelBtn->release();
	CCPoint pos = getDummy("dmy_button_small").origin;
	pos.y = -pos.y;
	mCancelBtn->setPosition(pos);
	mCancelBtn->setButtonLabel(GameStringDepot::getSingleton().getString("TXT_OK_LABEL"));

}

bool BankInOutPanel::isInputType()
{
	return mIsInput;
}

