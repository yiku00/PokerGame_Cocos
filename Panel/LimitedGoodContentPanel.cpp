#include "pch.h"
#include "LimitedGoodContentPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"


LimitedGoodContentPanel::LimitedGoodContentPanel(GOODS_TYPE type)
{
	mType = type;
	initPanel();
	setData();
}

LimitedGoodContentPanel::~LimitedGoodContentPanel()
{

}

void LimitedGoodContentPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_limited_goods_slot.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);
	
	mWindowBg = mMainPanel->getImage("img_limited_goods1_8888");

	CCPoint _btnPos = mMainPanel->getDummy("dmy_button_shop").origin;
	mButtonPanel = new Panel();
	mButtonPanel->construct(getMxmlPath() + "dmy_button_shop.mxml");
	mButtonPanel->setPositionX(_btnPos.x);
	mButtonPanel->setPositionY(-_btnPos.y);
	mMainPanel->addChild(mButtonPanel);
	mButtonPanel->release();

	mSelectBtn = mButtonPanel->getButton("sbtn_button");
	mSelectBtnLabel = mButtonPanel->getLabel("txt_price1");
	mSelectBtnUnderLabel = mButtonPanel->getLabel("txt_price1_under");
	mSelectBtn->setListener(this);
	mButtonPanel->getImage("skel_icon")->setVisible(false);
	mButtonPanel->getLabel("txt_price2_under")->setVisible(false);
	mButtonPanel->getLabel("txt_price2")->setVisible(false);	
	mSelectBtn->setName("select");
}

void LimitedGoodContentPanel::onClicked(const string& buttonName)
{
	if (buttonName == getButtonName(mSelectBtn)) {
		if (mType == GRAND_NORMAL) {
			fireMessage("GRAND_NORMAL");
		}
		else if (mType == GRAND_RANDOM) {
			fireMessage("GRAND_RANDOM");
		}
		else {
			fireMessage("LIMITED_SHOP_ID_" + StringConverter::toString(mLimitShopData.id()));
		}
		
	}	
}

void LimitedGoodContentPanel::setData()
{
	if (mType == GRAND_NORMAL) {
		mWindowBg->setSpriteFrameWithFile("ui/time_reward1_8888.png");
		setVisibleButton();
	}
	else if (mType == GRAND_RANDOM) {
		mWindowBg->setSpriteFrameWithFile("ui/time_reward2_8888.png");
		setVisibleButton();
	}
	else if (mType == LIMITED_JACKPOT_1) {
		mWindowBg->setSpriteFrameWithFile("ui/limited_goods1_8888.png");
	}
	else if (mType == LIMITED_JACKPOT_2) {
		mWindowBg->setSpriteFrameWithFile("ui/limited_goods2_8888.png");
	}
	else if (mType == LIMITED_MADE_1) {
		mWindowBg->setSpriteFrameWithFile("ui/limited_goods3_8888.png");
	}
	else if (mType == LIMITED_MADE_2) {
		mWindowBg->setSpriteFrameWithFile("ui/limited_goods4_8888.png");
	}
	else if (mType == LIMITED_ALLIN_1) {
		mWindowBg->setSpriteFrameWithFile("ui/limited_goods5_8888.png");
	}
	else if (mType == LIMITED_ALLIN_2) {
		mWindowBg->setSpriteFrameWithFile("ui/limited_goods6_8888.png");
	}
}

void LimitedGoodContentPanel::setVisibleButton()
{
	CCPoint point = ccpSub(mMainPanel->getImage("img_limited_goods1_8888")->getPosition(), mMainPanel->getImage("dmy_button_shop")->getPosition());
	mSelectBtn->setVisible(false);
	mSelectBtnLabel->setVisible(false);
	mSelectBtnUnderLabel->setVisible(false);
	mButtonPanel->setPositionY(mButtonPanel->getPositionY() + point.y);
	mSelectBtn->setButtonBounding(mWindowBg->getContentSize());
}

void LimitedGoodContentPanel::setLimitShopData(W_LimitShopData shopData)
{
	mLimitShopData.CopyFrom(shopData);
	refreshPrice();
}

void LimitedGoodContentPanel::refreshPrice()
{
	int price = mLimitShopData.price();
	string txtPrice = StringConverter::toString(price) + GameStringDepot::getSingleton().getString("TXT_COUNT_MONEY");
	mSelectBtnLabel->setString(txtPrice.c_str());
	mSelectBtnUnderLabel->setString(txtPrice.c_str());
}

