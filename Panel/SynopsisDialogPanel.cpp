#include "pch.h"
#include "SynopsisDialogPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "SynopsisUiPanel.h"
#include "GameStringDepot.h"
#include "SceneUtil.h"
#include "SynopsisMainPanel.h"
#include "SynopsisCharacterInfoPanel.h"
#include "SynopsisUiTutorial.h"

SynopsisDialogPanel::SynopsisDialogPanel()
{
	mLoginProcess = false;
	m_TextIdx = 0;
	m_SynopsisEnd = false;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);

	ShowText(m_TextIdx);
	m_TextIdx = 1;
}

SynopsisDialogPanel::~SynopsisDialogPanel()
{
	//destruct();
}

void SynopsisDialogPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_dialogue.mxml");
	m_contentSize = getDummy("dmy_dialogue").size;

	if (LayerManager::getSingletonPtr()->hasLayer("MainUi"))
	{
		SynopsisUiPanel* _pPanel = dynamic_cast<SynopsisUiPanel*>(LayerManager::getSingletonPtr()->getLayer("MainUi"));
		setPositionX(_pPanel->m_dialogueRect.origin.x);
		setPositionY(-_pPanel->m_dialogueRect.origin.y);
	}
}

void SynopsisDialogPanel::InitImage()
{
	m_Dialogue = getSkel("skel_image_dialogue");
	m_Dialogue->playAnimation("image_dialogue_start");

	m_Name = getLabel("txt_dialogue_name");
	m_Name->setString("");
	m_Name->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	m_Text = getLabel("txt_dialogue_content");
	m_Text->setString("");
	m_Text->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	mTouchLabel = getLabel("txt_touch");
	mTouchUnderLabel = getLabel("txt_touch_under");
}

void SynopsisDialogPanel::initButton()
{
	m_TouchButton = getButton("sbtn_button_touch_stay");
	m_TouchButton->setType(Button::NoPressImg);
	m_TouchButton->setListener(this);

	m_TouchButton->getButtonSkelObject()->playAnimation("button_touch_loop", true);
}


bool SynopsisDialogPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_TouchButton->isEnabled() == false)
		return false;

	else
		return true;

}


void SynopsisDialogPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void SynopsisDialogPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (m_TextIdx == 6)
	{
		ShowDialog(false);
		ShowSelectCharacer();
		return;
	}

	if (m_TextIdx == 7)
	{
		ShowDialog(false);
		ShowTutorial();
		return;
	}

	if (m_SynopsisEnd == true)
	{
		WebService::getSingletonPtr()->LoginEnterLobby();
		//SceneUtil::changeScene(SceneUtil::SceneTitle);
		return;
	}

	ShowText(m_TextIdx);
	m_TextIdx++;

	if (m_TextIdx >= 9)
	{
		m_SynopsisEnd = true;
	}
}

void SynopsisDialogPanel::resume()
{
}

void SynopsisDialogPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (name == "sbtn_button_touch_stay")
	{
		if (m_TextIdx == 6)
		{
			ShowDialog(false);
			ShowSelectCharacer();
			return;
		}

		if (m_TextIdx == 7)
		{
			ShowDialog(false);
			ShowTutorial();
			return;
		}

		if (m_SynopsisEnd == true)
		{
			WebService::getSingletonPtr()->LoginEnterLobby();
			//SceneUtil::changeScene(SceneUtil::SceneTitle);
			return;
		}

		ShowText(m_TextIdx);
		m_TextIdx++;

		if (m_TextIdx >= 9)
		{
			m_SynopsisEnd = true;
		}
	}
}


void SynopsisDialogPanel::update(float dt)
{
}

bool SynopsisDialogPanel::handling(STCMD &stCmd)
{
	return false;
}

void SynopsisDialogPanel::ShowText(int _idx)
{
	string _textName = "TXT_SYNOPSIS_SUB_" + StringConverter::toString(_idx + 1);
	string _DialogText = GameStringDepot::getSingletonPtr()->getString(_textName);

	m_Text->setString(_DialogText.c_str());

	m_Text->setOpacity(0);
	m_Text->setScaleY(0.f);
	m_Text->runAction(CCFadeIn::create(0.2f));
	m_Text->runAction(CCScaleTo::create(0.2f, 1.f, 1.f));

}

void SynopsisDialogPanel::ShowDialog(bool _visible)
{
	setVisible(_visible);

	m_Dialogue->setVisible(_visible);
	m_TouchButton->setVisible(_visible);
	m_TouchButton->setEnable(_visible);
	m_Name->setVisible(_visible);
	m_Text->setVisible(_visible);
	mTouchLabel->setVisible(_visible);
	mTouchUnderLabel->setVisible(_visible);
}

void SynopsisDialogPanel::ShowSelectCharacer()
{
	if (LayerManager::getSingletonPtr()->hasLayer("Main") && 
		LayerManager::getSingletonPtr()->hasLayer("Information") &&
		LayerManager::getSingletonPtr()->hasLayer("MainUi"))
	{
		SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
		SynopsisUiPanel* _pUiPanel = dynamic_cast<SynopsisUiPanel*>(LayerManager::getSingletonPtr()->getLayer("MainUi"));
		SynopsisCharacterInfoPanel* _pInfoPanel = dynamic_cast<SynopsisCharacterInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("Information"));

		int _id = _pMainPanel->m_characterId[_pMainPanel->m_selectId];

		_pMainPanel->ShowDealer(false);
		_pMainPanel->ShowCharacter(true);
		_pMainPanel->setBackGroundStart();
		_pUiPanel->ShowTitle(true);
		_pUiPanel->ShowPlayerSelectPanel(true);
		_pUiPanel->setLightUse(true);
		_pInfoPanel->ShowInfo(true, _id);

		//
	}
}

void SynopsisDialogPanel::ShowTutorial()
{
	if (LayerManager::getSingletonPtr()->hasLayer("Main") && LayerManager::getSingletonPtr()->hasLayer("Tutorial"))
	{
		SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
		SynopsisUiPanel* _pUiPanel = dynamic_cast<SynopsisUiPanel*>(LayerManager::getSingletonPtr()->getLayer("MainUi"));
		//SynopsisUiTutorial* _pTutorial = dynamic_cast<SynopsisUiTutorial*>(LayerManager::getSingletonPtr()->getLayer("Tutorial"));

		setTouchable(false);
		_pUiPanel->setTouchable(false);
		_pMainPanel->ShowDealer(false);
		
		//_pTutorial->AppearUi();
		//_pTutorial->setTouchable(true);
	}
	else if(LayerManager::getSingletonPtr()->hasLayer("Main") &&
		LayerManager::getSingletonPtr()->hasLayer("Information") &&
		LayerManager::getSingletonPtr()->hasLayer("Dialog"))
	{
		SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
		SynopsisCharacterInfoPanel* _pInfoPanel = dynamic_cast<SynopsisCharacterInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("Information"));

		_pMainPanel->ShowDealer(true);
		_pMainPanel->ShowCharacter(false);
		_pInfoPanel->ShowInfo(false);
		setTouchable(true);
		ShowDialog(true);
		ShowText(7);
		m_TextIdx = 8;
	}
}


void SynopsisDialogPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}