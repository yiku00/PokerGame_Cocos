#include "pch.h"
#include "GoldrefillPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "LobbyUIPanel.h"
#include "SceneUtil.h"
#include "PanelHelper.h"

GoldrefillPanel::GoldrefillPanel()
{
	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

GoldrefillPanel::~GoldrefillPanel()
{
	//destruct();
}

void GoldrefillPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_gold_refill.mxml");

	for (int _i = 0; _i < 5; _i++)
	{
		CCPoint _panelPos = getDummy("dmy_long_button" + StringConverter::toString(_i + 1)).origin;
		m_ButtonPanel[_i] = new LongButtonPanel();
		m_ButtonPanel[_i]->setPositionX(_panelPos.x);
		m_ButtonPanel[_i]->setPositionY(-_panelPos.y);
		addChild(m_ButtonPanel[_i]);
		m_ButtonPanel[_i]->release();
		m_ButtonPanel[_i]->m_Button->setListener(this);
	}
}

void GoldrefillPanel::InitImage()
{
	getLabel("txt_gold_refill_guide")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	
	getLabel("txt_gold_refill_guide")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REFILL_GOLD_DESC").c_str());
	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REFILL_GOLD_TITLE").c_str());
	getLabel("txt_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REFILL_GOLD_TITLE").c_str());
}	

void GoldrefillPanel::initButton()
{
	m_cancelBtn = getButton("sbtn_cancel");
	m_cancelBtn->setListener(this);

	m_ButtonPanel[0]->m_Button->setName("BTN_FREE_REFILL");
	m_ButtonPanel[1]->m_Button->setName("BTN_FREE_CHARGE");
	m_ButtonPanel[2]->m_Button->setName("BTN_VIEW_AD");
	m_ButtonPanel[3]->m_Button->setName("BTN_GOTO_CHARACTER_SHOP");
	m_ButtonPanel[4]->m_Button->setName("BTN_GOTO_MINIGAME");
}

void GoldrefillPanel::onClicked(const string& name)
{
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (name == "sbtn_cancel")
	{
		LayerManager::getSingletonPtr()->popLayer(this);
	}
	else if (name == "BTN_FREE_REFILL") 
	{
		WebService::getSingletonPtr()->_sendFreeRefillReq();	
		LayerManager::getSingletonPtr()->popLayer(this);
	}
	else if (name == "BTN_FREE_CHARGE") 
	{
		LayerManager::getSingletonPtr()->popLayer(this);
		PanelHelper::pushFreeMoviePanel();
	}
	else if (name == "BTN_VIEW_AD") 
	{
		NXASSERT(false, "NO AD");
		LayerManager::getSingletonPtr()->popLayer(this);
	}
	else if (name == "BTN_GOTO_CHARACTER_SHOP") 
	{
		LayerManager::getSingletonPtr()->popLayer(this);
		PanelHelper::pushCharacterShopPanel();
	}
	else if (name == "BTN_GOTO_MINIGAME") 
	{
		LayerManager::getSingletonPtr()->popLayer(this);
		SceneUtil::changeScene(SceneUtil::SceneMinigame);
	}

	return;
}

void GoldrefillPanel::SetButtonStyle()
{
	//무료리필
	int32 _RefillCount = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_FreeRefillCount;
	string _freeRefillText = GameStringDepot::getSingletonPtr()->getString("TXT_FREE_REFILL") + " ";
	string _refillCountText = "(" + GameStringDepot::getSingletonPtr()->getString("TXT_REFILL_LEFT_COUNT") + ":";
	_refillCountText += StringConverter::toString(_RefillCount);
	_refillCountText += GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT") + " " + GameStringDepot::getSingleton().getString("TXT_TIMELEFT") + ")";
	m_ButtonPanel[0]->SetLeftText(_freeRefillText);
	m_ButtonPanel[0]->SetRightText(_refillCountText);

	if (_RefillCount <= 0)
		m_ButtonPanel[0]->SetEnableButton(false);
	else
		m_ButtonPanel[0]->SetEnableButton(true);

	
	//무료충전소
	string _goToFreeCharge = GameStringDepot::getSingletonPtr()->getString("TXT_GOTO_FREE_CHARGE");
	m_ButtonPanel[1]->SetLeftText(_goToFreeCharge);
	m_ButtonPanel[1]->SetRightText("");
	
	//광고보기
	string _viewAD = GameStringDepot::getSingletonPtr()->getString("TXT_VIEW_AD");
	m_ButtonPanel[2]->SetLeftText(_viewAD);
	m_ButtonPanel[2]->SetRightText("");
	
	//캐릭터구입
	string _buyCharacter = GameStringDepot::getSingletonPtr()->getString("TXT_BUY_CHARACTER");
	m_ButtonPanel[3]->SetLeftText(_buyCharacter);
	m_ButtonPanel[3]->SetRightText("");
	
	//미니게임
	int64 _chipCount = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	string _gotoMinigame = GameStringDepot::getSingletonPtr()->getString("TXT_MINIGAME_UNIT");
	string _chipText = "(" + GameStringDepot::getSingletonPtr()->getString("TXT_HAVE_CHIP");
	_chipText += " : " + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_chipCount), 1) + ")";
	m_ButtonPanel[4]->SetLeftText(_gotoMinigame);
	m_ButtonPanel[4]->SetRightText(_chipText);

	if (_chipCount > 0 && GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_SlotMachineCount < 10)
		m_ButtonPanel[4]->SetEnableButton(true);
	else
		m_ButtonPanel[4]->SetEnableButton(false);
}
