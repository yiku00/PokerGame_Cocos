#include "pch.h"
#include "CharacterListPartPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GoodsPanel.h"
#include "GameStringDepot.h"
#include "PokerRecordHelper.h"
#include "PanelHelper.h"

CharacterListPartPanel::CharacterListPartPanel(LIST_TYPE type)
{
	mListType = type;
	initPanel();
}

CharacterListPartPanel::~CharacterListPartPanel()
{

}

void CharacterListPartPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mInfoBtn = nullptr;

	if (mListType == CHARACTER_INVEN) {
		mMainPanel->construct(getMxmlPath() + "dmy_inventory2.mxml");
		mMainPanel->getLabel("txt_characterinfo")->setString(GameStringDepot::getSingleton().getString("INVEN_CHARACTER_TAB_TITLE").c_str());
	}
	if (mListType == CHARACTER_SHOP) {
		mMainPanel->construct(getMxmlPath() + "dmy_shopin3.mxml");
		mMainPanel->getLabel("txt_characterinfo")->setString(GameStringDepot::getSingleton().getString("SHOP_CHARACTER_TAB_TITLE").c_str());
		mInfoBtn = mMainPanel->getButton("sbtn_button_info");

		mCharacterIdx.clear();
		for (int i = 0; i < GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size(); i++)
		{
			W_CharacterShopData _ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(i);
			if (_ShopInfo.characterid() != PokerRecordHelper::getBaseCharactId()) {
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

void CharacterListPartPanel::onClicked(const string& buttonName)
{
	if (buttonName == getButtonName(mInfoBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_REFUND_TYPE);
	}
}

void CharacterListPartPanel::onLayerMessage(const string& msg)
{
	CCLog("msg = %s", msg.c_str());
	if (mListType == CHARACTER_SHOP) {
		onShopLayerMessage(msg);
	}
	else if (mListType == CHARACTER_INVEN) {
		onInvenLayerMessage(msg);
	}
}

cocos2d::CCSize CharacterListPartPanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* CharacterListPartPanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	// 여긴 9, 10, 0, 1, 2, 3 이렇게 들어 오고 3개까지 보이고 4번째 보이고 5번째가 나오려고 할 때 4 ~ 넘어옴
	CCTableViewCell* cell = table->dequeueCell();

	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		GoodsPanel* pPanel = new GoodsPanel();
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);
		if (mListType == CHARACTER_SHOP) {
			pPanel->SetGoodsType(TYPE_RUBY_GOODS);
			pPanel->setIndex(mCharacterIdx[idx]);
		}
		else {
			pPanel->setIndex(idx);
			pPanel->SetGoodsType(TYPE_NO_RUBY_GOODS);
		}
		pPanel->setPosition(ccp(0, -pPanel->getContentSize().height / 2.f + 16.f));		
		pPanel->setListener(this);
	}
	else {
		GoodsPanel* pPanel = dynamic_cast<GoodsPanel*>(cell->getChildByTag(1));		
		if (pPanel) {
			if (mListType == CHARACTER_SHOP) {				
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

ssize_t CharacterListPartPanel::numberOfCellsInTableView(CCTableView *table)
{
	return getCellCount();
}

void CharacterListPartPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	GoodsPanel* pPanel = dynamic_cast<GoodsPanel*>(cell->getChildByTag(1));
	if (pPanel){
		pPanel->cellTouch(table->getTouchPoint());
	}	
}

int CharacterListPartPanel::getCellCount()
{
	if (mListType == CHARACTER_SHOP) {
		return mCharacterIdx.size();
	}
	else if (mListType == CHARACTER_INVEN) {
		return GameDataManager::getSingletonPtr()->m_pCharacterInfoList.size();
	}
	return 0;
}

void CharacterListPartPanel::drawTableView()
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

void CharacterListPartPanel::setActivate(bool activate)
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

void CharacterListPartPanel::SetBuyPopup(int _index)
{
	//캐릭터 idx 
	PanelHelper::pushConfirmCharacterPanel(_index);
}

void CharacterListPartPanel::onShopLayerMessage(const string& msg)
{
	if (msg.find(BUY_BTN_SEND_MSG) != string::npos){
		int idx = nxExtractInt(msg, BUY_BTN_SEND_MSG);
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		SetBuyPopup(idx);
	}
	else if (msg.find(INFO_BTN_SEND_MSG) != string::npos){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int idx = nxExtractInt(msg, INFO_BTN_SEND_MSG);
		W_CharacterShopData _infoData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(idx);
		CustomPopupPanel* _popupPanel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::CHAR_INFO_TYPE, _infoData.characterid());
		LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
		for (int _i = 0; _i < GameDataManager::getSingletonPtr()->m_pCharacterInfoList.size(); _i++)
		{
			W_CharacterInfo* _Charainfo = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[_i];
			if (_Charainfo->id() == _infoData.characterid())
			{
				if (_Charainfo->isbase() || _Charainfo->expirelefttime() > 0)
				{
					_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_HOLD_ITEM);
				}
				else if (_Charainfo->expirelefttime() == 0)
				{
					_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_EXPIRED_ITEM);
				}
				else
				{
					_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_NONE_ITEM);
				}
				return;
			}
		}
		_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_NONE_ITEM);			
	}
}

void CharacterListPartPanel::onInvenLayerMessage(const string& msg)
{
	if (msg.find(BUY_BTN_SEND_MSG) != string::npos){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int idx = nxExtractInt(msg, BUY_BTN_SEND_MSG);				
		W_CharacterInfo* characterInfo = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[idx];
		WebService::getSingletonPtr()->_sendCharacterSelectReq(characterInfo->id());
	}
	else if (msg.find("INFO_CHOICE") != string::npos){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int idx = nxExtractInt(msg, "INFO_CHOICE");		
		WebService::getSingletonPtr()->_sendCharacterSelectReq(idx);
	}
	else if (msg.find(INFO_BTN_SEND_MSG) != string::npos){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int idx = nxExtractInt(msg, INFO_BTN_SEND_MSG);
		W_CharacterInfo* characterInfo = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[idx];
		W_CharacterShopData _infoData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(idx);
		CustomPopupPanel* _popupPanel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::CHAR_INFO_INVEN_TYPE, characterInfo->id());
		LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);

		for (int _i = 0; _i < GameDataManager::getSingletonPtr()->m_pCharacterInfoList.size(); _i++)
		{
			W_CharacterInfo* _Charainfo = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[_i];
			if (_Charainfo->id() == _infoData.characterid())
			{
				if (_Charainfo->isbase() || _Charainfo->expirelefttime() > 0)
				{
					_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_HOLD_ITEM);
				}
				else if (_Charainfo->expirelefttime() == 0)
				{
					_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_EXPIRED_ITEM);
				}
				else
				{
					_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_NONE_ITEM);
				}
				return;
			}
		}
		_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_NONE_ITEM);	
	}
}

void CharacterListPartPanel::UpdateCell()
{
	if (mTableView)
		mTableView->reloadData();
}
