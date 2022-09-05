#include "pch.h"
#include "ModelSubPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "PokerResourceHelper.h"
#include "ModelTempTabel.h"
#include "LobbyScene.h"
#include "PanelHelper.h"
#include "NxUtil.h"

ModelSubPanel::ModelSubPanel()
{
	test = true;
	InitPanel();
	InitImage();
	initButton();
	SetSubModelType(TYPE_MODEL_SUB_SHOP);
}

ModelSubPanel::~ModelSubPanel()
{
	//destruct();
}

void ModelSubPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_model_subpanel.mxml");	
}

void ModelSubPanel::InitImage()
{	
	m_ModelSubPanel = getSkel("skel_goods_penal_1_stay");
	m_Cover = getSkel("skel_cover");
	mCharacter = getImage("img_character_boxer");
	m_Name1 = getLabel("txt_character_name"); // 본판 이름
	m_Name1->setVisible(false);
}

void ModelSubPanel::initButton()
{
    CCPoint _btnPos = getDummy("dmy_button_model").origin;
    m_ButtonPanel = new Panel();
    m_ButtonPanel->construct(getMxmlPath() + "dmy_button_model.mxml");
    m_ButtonPanel->setPositionX(_btnPos.x);
    m_ButtonPanel->setPositionY(-_btnPos.y);
    addChild(m_ButtonPanel);
    m_ButtonPanel->release();
	m_Name2 = m_ButtonPanel->getLabel("txt_character_name"); // 가림 이름
	PanelHelper::setCompactImage(m_ButtonPanel->getImage("img_deco"), m_ButtonPanel->getDummy("img_deco"));
	PanelHelper::setCompactImage(m_ButtonPanel->getImage("sbtn_button"), m_ButtonPanel->getDummy("sbtn_button"));
}

void ModelSubPanel::ModelShot()
{
	PanelHelper::pushModelShotPanel(mIdx);
}

void ModelSubPanel::BuyModel()
{
    string _title = GameStringDepot::getSingleton().getString("TXT_INFORMATION");
    string _content = GameStringDepot::getSingleton().getString("TXT_BUY_MODEL");
    SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ShopYESNONotice, _content, _title);
    if (_popupPanel)
    {
        _popupPanel->SetOkEventMsg("BUY_MODEL");
        _popupPanel->setListener(this);
        LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
    }
}

void ModelSubPanel::UnlockModel()
{
    string _title = GameStringDepot::getSingleton().getString("TXT_INFORMATION");
    string _content = GameStringDepot::getSingleton().getString("TXT_POPUP_MODEL_SLOT");
    SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ShopYESNONotice, _content, _title);
    if (_popupPanel)
    {
        _popupPanel->SetOkEventMsg("BUY_SLOT");
        _popupPanel->setListener(this);
        LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
    }
}

void ModelSubPanel::SetSubModelType(ModelSubPanelType _type)
{
	m_panelType = _type;

	switch (_type)
	{
	case TYPE_MODEL_SUB_INVEN:
		break;
	case TYPE_MODEL_SUB_SHOP:
		break;
	}
}

void ModelSubPanel::SetBtnText(const wstring& _text)
{
	switch (m_panelType)
	{
	case TYPE_MODEL_SUB_INVEN:
		break;
	case TYPE_MODEL_SUB_SHOP:
		break;
	}
	string text = GameStringDepot::getSingletonPtr()->getString("TXT_MODEL_BUY_UNIT");
	string dest = NxGetFormatString(text, StringConverter::toString(_text));
    m_ButtonPanel->getLabel("txt_price1_under")->setString(dest.c_str());
    m_ButtonPanel->getLabel("txt_price1")->setString(dest.c_str());
}

void ModelSubPanel::setIndex(int idx)
{
	mIdx = idx;
	ModelTempTable temp = FindModelTable(idx);
	SetBtnText(temp.goldDesc.c_str());
	m_Cover->setVisible(idx >= 0);
	m_Name1->setString(temp.strName.c_str());
	m_Name2->setString(temp.strName.c_str());
	mCharacter->setVisible(!temp.strImage.empty());
	if (mCharacter->isVisible())
	{
		mCharacter->setSpriteFrameWithFile("model/" + temp.strImage);
		PanelHelper::setCompactImage(mCharacter, getDummy("img_character_boxer"));
	}
	m_ButtonPanel->setVisible(idx >= 0 && !GameDataManager::getSingletonPtr()->hasModel(idx));
	m_Name1->setVisible(!m_ButtonPanel->isVisible());
}

void ModelSubPanel::onLayerMessage(const string& msg)
{
	if (msg == "BUY_MODEL") {
		uint64 money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
		uint64 need = FindModelTable(mIdx).gold;
		if (money >= need)
		{
			GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney -= need;
            LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
            _pScene->ApplyUserData();
			m_ButtonPanel->setVisible(false);
			m_Name1->setVisible(!m_ButtonPanel->isVisible());
			GameDataManager::getSingletonPtr()->addModel(mIdx);
		}
		else
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice,
				GameStringDepot::getSingletonPtr()->getString("TXT_REFILL_GOLD_TITLE")), DYNAMIC_PUSH_LAYER);			
		}
    }
	else if (msg == "BUY_SLOT")
	{
        uint64 money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
        uint64 need = SlotExNeedGold;
        if (money >= need)
        {
            GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney -= need;
            LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
            _pScene->ApplyUserData();
			GameDataManager::getSingletonPtr()->addSlot();
			fireMessage(msg);
        }
        else
        {
            LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice,
                GameStringDepot::getSingletonPtr()->getString("TXT_REFILL_GOLD_TITLE")), DYNAMIC_PUSH_LAYER);
        }
	}
}
