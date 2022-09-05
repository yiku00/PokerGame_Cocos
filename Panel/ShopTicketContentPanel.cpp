#include "pch.h"
#include "ShopTicketContentPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"


ShopTicketContentPanel::ShopTicketContentPanel()
{
	initPanel();		
}

ShopTicketContentPanel::~ShopTicketContentPanel()
{

}

void ShopTicketContentPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_sticker.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);	

	mStickerIcon = mMainPanel->getSkel("skel_sticker");
	mTitieLabel = mMainPanel->getLabel("txt_apply");
	mTitleUnderLabel = mMainPanel->getLabel("txt_apply_under");
	mRemainLabel = mMainPanel->getLabel("txt_limit");
	mRemainUnderLabel = mMainPanel->getLabel("txt_limit_under");
}

void ShopTicketContentPanel::setMemberRamain(int day)
{
	mStickerIcon->playAnimation("sticker_red");
	mTitieLabel->setString(GameStringDepot::getSingleton().getString("STICKER_APPLY_TITLE").c_str());
	mTitleUnderLabel->setString(GameStringDepot::getSingleton().getString("STICKER_APPLY_TITLE").c_str());
	string remainStr = NxGetFormatString(GameStringDepot::getSingleton().getString("STICKER_REMAIN_DAY"), day);
	mRemainLabel->setString(remainStr.c_str());
	mRemainUnderLabel->setString(remainStr.c_str());
}

void ShopTicketContentPanel::setRubyPlusRemain(int day)
{
	mStickerIcon->playAnimation("sticker_yellow");
	mTitieLabel->setString(GameStringDepot::getSingleton().getString("STICKER_APPLY_TITLE").c_str());
	mTitleUnderLabel->setString(GameStringDepot::getSingleton().getString("STICKER_APPLY_TITLE").c_str());
	string remainStr = NxGetFormatString(GameStringDepot::getSingleton().getString("STICKER_REMAIN_DAY"), day);
	mRemainLabel->setString(remainStr.c_str());
	mRemainUnderLabel->setString(remainStr.c_str());

	mStickerIcon->playAnimation("sticker_yellow");
}

void ShopTicketContentPanel::setMemberStop(int day)
{
	mStickerIcon->playAnimation("sticker_gray");
	mTitieLabel->setString(GameStringDepot::getSingleton().getString("STICKER_READY_TITLE").c_str());
	mTitleUnderLabel->setString(GameStringDepot::getSingleton().getString("STICKER_READY_TITLE").c_str());
	string remainStr = NxGetFormatString(GameStringDepot::getSingleton().getString("STICKER_REMAIN_DAY"), day);
	mRemainLabel->setString(remainStr.c_str());
	mRemainUnderLabel->setString(remainStr.c_str());
}

