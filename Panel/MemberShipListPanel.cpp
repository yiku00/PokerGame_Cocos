#include "pch.h"
#include "MemberShipListPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GoodsPanel.h"
#include "GameStringDepot.h"
#include "LobbyScene.h"
#include "LobbyUIPanel.h"
#include "PanelHelper.h"

MemberShipListPanel::MemberShipListPanel()
{
	initPanel();
}

MemberShipListPanel::~MemberShipListPanel()
{

}

void MemberShipListPanel::initPanel()
{
	/*
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	//mMainPanel->construct(getMxmlPath() + "dmy_inventory2.mxml");
	mMainPanel->construct(getMxmlPath() + "dmy_inventory4.mxml");
	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);	

	CCPoint _shop1Pos = mMainPanel->getDummy("dmy_membership1").origin;
	_shop1Pos.y = -_shop1Pos.y;
	mSilverPanel = new MemberShipContentPanel(MemberShipContentPanel::MEMBER_SILVER);
	mSilverPanel->setPosition(_shop1Pos);
	mMainPanel->addChild(mSilverPanel);
	mSilverPanel->release();
	mSilverPanel->setListener(this);

	_shop1Pos = mMainPanel->getDummy("dmy_membership2").origin;
	_shop1Pos.y = -_shop1Pos.y;
	mGoldPanel = new MemberShipContentPanel(MemberShipContentPanel::MEMBER_GOLD);
	mGoldPanel->setPosition(_shop1Pos);
	mMainPanel->addChild(mGoldPanel);
	mGoldPanel->release();
	mGoldPanel->setListener(this);
	*/
}

void MemberShipListPanel::onClicked(const string& buttonName)
{
	
}

void MemberShipListPanel::setActivate(bool activate)
{
	if (activate) {
		setVisible(true);		
		if (getPositionX() < 0) {
			setPositionX(getPositionX() + DESIGN_WIDTH);
		}		
	}
	else {
		setVisible(false);
		if (getPositionX() > 0) {
			setPositionX(getPositionX() - DESIGN_WIDTH);
		}
	}
}

void MemberShipListPanel::onLayerMessage(const string& msg)
{
	if (msg.find("SELECT_MEMBERSHIP") != string::npos){
		if (LayerManager::getSingleton().hasLayerType<LobbyShopPanel>()) {
			Layer* layer = LayerManager::getSingleton().getLayerType<LobbyShopPanel>();
			LayerManager::getSingleton().popLayer(layer);
		}
		PanelHelper::pushShopPanel();
	}	
}
