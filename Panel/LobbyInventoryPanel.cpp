#include "pch.h"
#include "LobbyInventoryPanel.h"

#include "HeroUtil.h"
#include "LobbyTopUiPanel.h"
#include "LobbyUIPanel.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PanelHelper.h"
#include "NotiDataManager.h"

#include "ModelListPartPanel.h"


//#define USE_ONE_STORE

#define TAB_SIZE 5

LobbyInventoryPanel::LobbyInventoryPanel()
{
	mLetterPanel = nullptr;
	mCharacterListPanel = nullptr;
	mItemListPanel = nullptr;
	mCardListPanel = nullptr;
	mModelTabPanel = nullptr;
	_init();
}

LobbyInventoryPanel::~LobbyInventoryPanel()
{
	//destruct();
}

void LobbyInventoryPanel::onClicked(const string& name)
{
	if (name.find("TAP_BUTTON") != string::npos){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
		int idx = nxExtractInt(name, "TAP_BUTTON") - 1;
		mInvenState = (INVEN_STATE)idx;
		refresh();
	}
	else if (name == mGoShop->getName()) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
		LayerManager::getSingleton().popLayer(this);
		if (LayerManager::getSingleton().hasLayerType<LobbyShopPanel>()) {
			Layer* layer = LayerManager::getSingleton().getLayerType<LobbyShopPanel>();
			LayerManager::getSingleton().popLayer(layer);
		}
		PanelHelper::pushShopPanel();		
	}
}

bool LobbyInventoryPanel::handling(STCMD &stCmd)
{
	return false;
}

void LobbyInventoryPanel::_init()
{
	Panel* panel = addMouseBlockPanel(this, true);
	panel->setContentSize(CCSize(DESIGN_WIDTH, DESIGN_HEIGHT - 72));

	construct(getMxmlPath() + "dmy_inventory.mxml");	
	_initTab();
	_initPanel();
	setActivate();
}

void LobbyInventoryPanel::_initTopPanel()
{
	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_INVEN);
		}
	}
}

void LobbyInventoryPanel::_initTab()
{
	for (int _i = 0; _i < TAB_SIZE; _i++)
	{
		CCPoint _tapBtnPos = getDummy("dmy_button_tab" + StringConverter::toString(_i + 1)).origin;
		TabButtonPanel* tapButtonPanel = new TabButtonPanel();
		tapButtonPanel->setPositionX(_tapBtnPos.x);
		tapButtonPanel->setPositionY(-_tapBtnPos.y);
		addChild(tapButtonPanel);
		tapButtonPanel->release();
		tapButtonPanel->SetButtonListener(this);
		tapButtonPanel->m_Button->setName("TAP_BUTTON" + StringConverter::toString(_i + 1));
		mTabButtons.push_back(tapButtonPanel);
	}
	if (TAB_SIZE > 0)
		mTabButtons[0]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_INVEN_TAB_LETTER"));
	
	if (TAB_SIZE > 1)
		mTabButtons[1]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_INVEN_TAB_CHARACTER"));

	if (TAB_SIZE > 2)
		mTabButtons[2]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_INVEN_TAB_ITEM"));

	if (TAB_SIZE > 3)
		mTabButtons[3]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_INVEN_TAB_MEMBERSHIP"));

    if (TAB_SIZE > 4)
        mTabButtons[4]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_INVEN_TAB_COLLECTION"));

	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_INVEN_LETTER);
		mTabButtons[0]->addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(mTabButtons[0]->getImage("dmy_notification_icon")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}

	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_INVEN_CHARACTER);
		mTabButtons[1]->addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(mTabButtons[1]->getImage("dmy_notification_icon")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}

    {
        NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_INVEN_TICKET);
        mTabButtons[2]->addChild(notiWidget);
        notiWidget->release();
        notiWidget->setPosition(mTabButtons[2]->getImage("dmy_notification_icon")->getPosition());
        mNotiWidgets.push_back(notiWidget);
    }
}

void LobbyInventoryPanel::_initPanel()
{
	mGoShop = getButton("sbtn_tab_out");
	getLabel("txt_tab_out")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GO_SHOP").c_str());
	setButtonListener(this);
}

void LobbyInventoryPanel::setActivate()
{
	_initTopPanel();
	mInvenState = INVEN_LETTER;
	refresh();
}

void LobbyInventoryPanel::refreshTabBtn()
{
	for (int i = 0; i < mTabButtons.size(); i++)
	{
		if (i == mInvenState) {
			mTabButtons[i]->SetBtnOnOff(true);
		}
		else {
			mTabButtons[i]->SetBtnOnOff(false);
		}
	}
}

void LobbyInventoryPanel::refreshPanel()
{
	if (mInvenState == INVEN_LETTER) {
		if (mLetterPanel == nullptr) {
			addLetterPanel();
		}
		mLetterPanel->setActivate(true);

		if (mCharacterListPanel) {
			mCharacterListPanel->setActivate(false);
		}
		if (mItemListPanel) {
			mItemListPanel->setActivate(false);
		}
		if (mCardListPanel) {
			mCardListPanel->setActivate(false);
		}
        if (mModelTabPanel) {
			mModelTabPanel->setActivate(false);
        }
	}
	else if (mInvenState == INVEN_CHARACTER) {
		NotiDataManager::getSingleton().setEnterInvenCharacter(false);

		if (mLetterPanel) {
			mLetterPanel->setActivate(false);
		}

		if (mCharacterListPanel == nullptr) {
			addCharacterListPanel();
		}		
		mCharacterListPanel->setActivate(true);

		if (mItemListPanel) {
			mItemListPanel->setActivate(false);
		}
		if (mCardListPanel) {
			mCardListPanel->setActivate(false);
		}
        if (mModelTabPanel) {
			mModelTabPanel->setActivate(false);
        }
	}
	else if (mInvenState == INVEN_ITEM) {
		NotiDataManager::getSingleton().setEnterInvenTicket(false);

		if (mLetterPanel) {
			mLetterPanel->setActivate(false);
		}


		if (mItemListPanel == nullptr) {
			addItemListPanel();
		}
		mItemListPanel->setActivate(true);

		if (mCharacterListPanel) {
			mCharacterListPanel->setActivate(false);
		}
		if (mCardListPanel) {
			mCardListPanel->setActivate(false);
		}
        if (mModelTabPanel) {
			mModelTabPanel->setActivate(false);
        }
	}
	else if (mInvenState == INVEN_CARD) {

		if (mLetterPanel) {
			mLetterPanel->setActivate(false);
		}

		if (mCardListPanel) {
			mCardListPanel->setActivate(true);
		}
		else {
			addCardListPanel();
		}	

		if (mItemListPanel) {
			mItemListPanel->setActivate(false);
		}
		if (mCharacterListPanel) {
			mCharacterListPanel->setActivate(false);
		}
        if (mModelTabPanel) {
			mModelTabPanel->setActivate(false);
        }
	}
    else if (mInvenState == INVEN_MODEL) {

        if (mLetterPanel) {
            mLetterPanel->setActivate(false);
        }
        if (mCardListPanel) {
            mCardListPanel->setActivate(false);
        }
        if (mItemListPanel) {
            mItemListPanel->setActivate(false);
        }
        if (mCharacterListPanel) {
            mCharacterListPanel->setActivate(false);
        }

        if (mModelTabPanel) {
			mModelTabPanel->setActivate(true);
        }
        else {
            addModelListPanel();
        }
    }
}

void LobbyInventoryPanel::refresh()
{
	refreshTabBtn();
	refreshPanel();
}

void LobbyInventoryPanel::addCharacterListPanel()
{
	CCPoint _shop3Pos = getImage("dmy_inventory2")->getPosition();
	mCharacterListPanel = new CharacterListPartPanel(CharacterListPartPanel::CHARACTER_INVEN);
	CCSize size = mCharacterListPanel->getContentSize();
	mCharacterListPanel->setPosition(_shop3Pos);
	addChild(mCharacterListPanel);
	mCharacterListPanel->release();
	mCharacterListPanel->setActivate(false);
}

void LobbyInventoryPanel::UpdateCell()
{
	if (mCharacterListPanel)
		mCharacterListPanel->UpdateCell();
 	if (mLetterPanel)
		mLetterPanel->SetLetterlList();
	if (mItemListPanel)
		mItemListPanel->refreshData();
	if (mCardListPanel)
		mCardListPanel->UpdateCell();
    if (mModelTabPanel)
		mModelTabPanel->UpdateCell();
}

void LobbyInventoryPanel::addItemListPanel()
{
	CCPoint _shop3Pos = getImage("dmy_inventory3")->getPosition();
	mItemListPanel = new ItemPartListPanel();
	CCSize size = mItemListPanel->getContentSize();
	mItemListPanel->setPosition(_shop3Pos);
	addChild(mItemListPanel);
	mItemListPanel->release();
	mItemListPanel->setActivate(false);
}

void LobbyInventoryPanel::addCardListPanel()
{
 	CCPoint _shop3Pos = getImage("dmy_inventory2")->getPosition();
 	mCardListPanel = new CardListPartPanel(CardListPartPanel::CARD_INVEN);
	CCSize size = mCardListPanel->getContentSize();
	mCardListPanel->setPosition(_shop3Pos);
	addChild(mCardListPanel);
	mCardListPanel->release();
}

void LobbyInventoryPanel::addLetterPanel()
{
	CCPoint _shop3Pos = getImage("dmy_inventory1")->getPosition();
	mLetterPanel = new LobbyLetterBoxPanel();
	CCSize size = mLetterPanel->getContentSize();
	mLetterPanel->setPosition(_shop3Pos);
	addChild(mLetterPanel);
	mLetterPanel->release();
	mLetterPanel->setActivate(false);
}

void LobbyInventoryPanel::addModelListPanel()
{
    CCPoint pos = getImage("dmy_inventory4")->getPosition();
	mModelTabPanel = new ModelListPartPanel(MODEL_INVEN);
    CCSize size = mModelTabPanel->getContentSize();
	mModelTabPanel->setPosition(pos);
    addChild(mModelTabPanel);
	mModelTabPanel->release();
}

//void LobbyInventoryPanel::addModelListPanel()
//{
//	CCPoint panelPos = getImage("dmy_record1")->getPosition();
//	mModelTabPanel = new ModelListPartPanel(ModelListPartPanel::MODEL_INVEN);
//	CCSize size = mModelTabPanel->getContentSize();
//	mModelTabPanel->setPosition(panelPos);
//	addChild(mModelTabPanel);
//	mModelTabPanel->release();
//}


void LobbyInventoryPanel::HideShopPanel()
{
	
}

void LobbyInventoryPanel::setCharacterSelect(int characterId)
{
	if (mCharacterListPanel) {
		string sendStr = "INFO_CHOICE" + StringConverter::toString(characterId);
		mCharacterListPanel->onLayerMessage(sendStr);
	}
}

void LobbyInventoryPanel::updateNotiWidget()
{
	for (int i = 0; i < mNotiWidgets.size(); i++)
	{
		mNotiWidgets[i]->refresh();
	}
}

void LobbyInventoryPanel::update(float delta)
{
	updateNotiWidget();
}
void LobbyInventoryPanel::onEnter()
{
	Panel::onEnter();

	scheduleUpdate();
}
