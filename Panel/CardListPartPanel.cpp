#include "pch.h"
#include "CardListPartPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "CardPanel.h"
#include "GameStringDepot.h"
#include "PokerRecordHelper.h"
#include "PanelHelper.h"

CardListPartPanel::CardListPartPanel(CARD_LIST_TYPE type)
{
	mListType = type;
	initPanel();
}

CardListPartPanel::~CardListPartPanel()
{

}

void CardListPartPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mInfoBtn = nullptr;

	if (mListType == CARD_INVEN) {
		mMainPanel->construct(getMxmlPath() + "dmy_inventory2.mxml");
		mMainPanel->getLabel("txt_characterinfo")->setString(GameStringDepot::getSingleton().getString("INVEN_CHARACTER_TAB_TITLE").c_str());
	}
	if (mListType == CARD_SHOP) {
		mMainPanel->construct(getMxmlPath() + "dmy_shopin3.mxml");
		mMainPanel->getLabel("txt_characterinfo")->setString(GameStringDepot::getSingleton().getString("SHOP_CHARACTER_TAB_TITLE").c_str());
		mInfoBtn = mMainPanel->getButton("sbtn_button_info");

		mCharacterIdx.clear();
		for (int i = 0; i < GameDataManager::getSingleton().GetGameDataPtr()->skinshopdata_size(); i++)
		{
			W_SkinShopData _ShopInfo = GameDataManager::getSingleton().GetGameDataPtr()->skinshopdata(i);
			if (_ShopInfo.skinid() != PokerRecordHelper::getBaseSkin()) {
				mCharacterIdx.push_back(i);
			}
		}
	}	
	
	if (mMainPanel->hasElement("txt_tab1_empty"))
		mMainPanel->getLabel("txt_tab1_empty")->setVisible(false);

	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);
	mCellSize = mMainPanel->getDummy("dmy_goods_panel").size;
	mMainPanel->setButtonListener(this);
	
	drawTableView();
}

void CardListPartPanel::onClicked(const string& buttonName)
{
	if (buttonName == getButtonName(mInfoBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_REFUND_TYPE);
	}
}

void CardListPartPanel::onLayerMessage(const string& msg)
{
	CCLog("msg = %s", msg.c_str());
	if (mListType == CARD_SHOP) {
		onShopLayerMessage(msg);
	}
	else if (mListType == CARD_INVEN) {
		onInvenLayerMessage(msg);
	}
}

cocos2d::CCSize CardListPartPanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* CardListPartPanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CCTableViewCell* cell = table->dequeueCell();

	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		CardPanel* pPanel = new CardPanel();
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);
		if (mListType == CARD_SHOP) {
			pPanel->SetGoodsType(CARD_SHOP_TYPE);
			pPanel->setIndex(mCharacterIdx[idx]);
		}
		else {
			pPanel->SetGoodsType(CARD_INVEN_TYPE);
			pPanel->setIndex(idx);
			
		}
		pPanel->setPosition(ccp(0, -pPanel->getContentSize().height / 2.f + 16.f));		
		pPanel->setListener(this);
	}
	else {
		CardPanel* pPanel = dynamic_cast<CardPanel*>(cell->getChildByTag(1));
		if (pPanel) {
			if (mListType == CARD_SHOP) {				
				pPanel->setIndex(mCharacterIdx[idx]);
			}
			else {				
				pPanel->setIndex(idx);
			}
			pPanel->activateSam();
		}


	}
	return cell;
}

ssize_t CardListPartPanel::numberOfCellsInTableView(CCTableView *table)
{

	return getCellCount();
}

void CardListPartPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	CardPanel* pPanel = dynamic_cast<CardPanel*>(cell->getChildByTag(1));
	if (pPanel){
		pPanel->cellTouch(table->getTouchPoint());
	}	
}

int CardListPartPanel::getCellCount()
{
	if (mListType == CARD_SHOP) {
		return mCharacterIdx.size();
	}
	else if (mListType == CARD_INVEN) {
		return GameDataManager::getSingleton().getUserInfo()->skininfo_size();
	}
	return 0;
}

void CardListPartPanel::drawTableView()
{
	CCRect tableViewRect = mMainPanel->getDummyUI("dmy_scrollsize");
	mTableView = Nx::TableView::create(this, tableViewRect.size);
	mMainPanel->addChild(mTableView);
	mTableView->setDirection(ScrollView::Direction::HORIZONTAL);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setDelegate(this); 	
	mTableView->reloadData();	
	mTableView->setBounceable(true);	
}

void CardListPartPanel::setActivate(bool activate)
{
	if (activate) {
		setVisible(true);
		mTableView->reloadData();
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

void CardListPartPanel::onShopLayerMessage(const string& msg)
{
	if (msg.find(BUY_CARD_BTN_SEND_MSG) != string::npos){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int idx = nxExtractInt(msg, BUY_CARD_BTN_SEND_MSG);
		setBuyCardPopup(idx);
	}
}

void CardListPartPanel::onInvenLayerMessage(const string& msg)
{
	if (msg.find(BUY_CARD_BTN_SEND_MSG) != string::npos){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int idx = nxExtractInt(msg, BUY_CARD_BTN_SEND_MSG);
		W_SkinInfo skinInfo = GameDataManager::getSingleton().getUserInfo()->skininfo(idx);
		WebService::getSingletonPtr()->_sendSkinSelectReq(skinInfo.id());
	}
	else if (msg.find("INFO_CHOICE") != string::npos){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int idx = nxExtractInt(msg, "INFO_CHOICE");		
		WebService::getSingletonPtr()->_sendSkinSelectReq(idx);
	}	
}

void CardListPartPanel::UpdateCell()
{
	if (mTableView)
		mTableView->reloadData();
}

void CardListPartPanel::setBuyCardPopup(int _index)
{
	PanelHelper::pushConfirmSkinPanel(_index);
}
