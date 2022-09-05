#include "pch.h"
#include "SynopsisUiPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
//#include "SimplePopupPanel.h"
//#include "HeroApp.h"

#include "Web/WebService.h"
#include "SynopsisMainPanel.h"
#include "SynopsisCharacterInfoPanel.h"
#include "SynopsisDialogPanel.h"
#include "AccountPopupPanel.h"
#include "GameStringDepot.h"
#include "SynopsisUiTutorial.h"

SynopsisUiPanel::SynopsisUiPanel()
{
	mLoginProcess = false;
	m_bSelectCharacter = false;
	InitPanel();
	InitImage();
	InitButton();

	ShowPlayerSelectPanel(false);

	
	setButtonListener(this);
}

SynopsisUiPanel::~SynopsisUiPanel()
{
	//destruct();
}

void SynopsisUiPanel::InitPanel()
{
	construct(getMxmlPath() + "synopsis.mxml");

	m_contentSize = getDummy("dmy_synopsis").size;
	m_characterInfoRect = getDummy("dmy_synopsis_character_info");
	m_dialogueRect = getDummy("dmy_dialogue");
	mSelectBtnLabel = getLabel("txt_choice");
	mSelectBtnUnderLabel = getLabel("txt_choice_under");

	//캐릭터 선택
	mSelectBtnLabel->setString(GameStringDepot::getSingletonPtr()->getString("SynopsisUiPanel_CHOICE").c_str());
	mSelectBtnUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("SynopsisUiPanel_CHOICE").c_str());

	mLight = getImage("skel_light");
	setLightUse(false);
}

void SynopsisUiPanel::InitImage()
{
	m_BottomStone[0] = getSkel("skel_buttonback1");
	m_BottomStone[0]->setVisible(false);
	m_BottomStone[1] = getSkel("skel_buttonback2");
	m_BottomStone[1]->setVisible(false);
	m_BottomStone[2] = getSkel("skel_buttonback3");
	m_BottomStone[2]->setVisible(false);
	m_BottomStone[3] = getSkel("skel_buttonback4");
	m_BottomStone[3]->setVisible(false);

	m_ButtonBack = getSkel("skel_button_select_frame");
	m_ButtonBack->setVisible(false);
	
	m_TitleBar = getSkel("skel_toasttitle_start");
	m_TitleBar->playAnimation("toasttitle_end");
	m_TitleBar->setVisible(false);

	m_TitleLabel = getLabel("txt_synopsis_title");
	m_TitleLabel->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TitleLabel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SYNOPSIS_SELECT_TITLE").c_str());
	m_TitleLabel->setVisible(false);
	
}

void SynopsisUiPanel::InitButton()
{
	m_LeftButton = getButton("sbtn_change_move_left");
	m_LeftButton->setVisible(false);
	m_LeftButton->setType(Button::NoPressImg);
	m_LeftButton->setListener(this);

	m_RightButton = getButton("sbtn_change_move_right");
	m_RightButton->setVisible(false);
	m_RightButton->setType(Button::NoPressImg);
	m_RightButton->setListener(this);

	m_SelectButton = getButton("sbtn_button_select");
	m_SelectButton->setVisible(false);
	m_SelectButton->setType(Button::NoPressImg);
	m_SelectButton->setListener(this);
}

void SynopsisUiPanel::EnableButton(bool _enable)
{
	m_LeftButton->setEnable(_enable);
	m_RightButton->setEnable(_enable);
	m_SelectButton->setEnable(_enable);

	m_bSelectCharacter = _enable;
}

void SynopsisUiPanel::ShowPlayerSelectPanel(bool _visible)
{
	m_BottomStone[0]->setVisible(_visible);
	m_BottomStone[1]->setVisible(_visible);
	m_BottomStone[2]->setVisible(_visible);
	m_BottomStone[3]->setVisible(_visible);
	m_ButtonBack->setVisible(_visible);
	m_TitleBar->setVisible(_visible);

	m_LeftButton->setVisible(_visible);
	m_RightButton->setVisible(_visible);
	m_SelectButton->setVisible(_visible);

	EnableButton(_visible);

	mSelectBtnLabel->setVisible(_visible);
	mSelectBtnUnderLabel->setVisible(_visible);
}


void SynopsisUiPanel::ShowTitle(bool _show)
{
	if (_show == true)
	{
		m_TitleBar->playAnimation("toasttitle_start");
		m_TitleBar->appendAnimation("toasttitle_stay");

		m_TitleLabel->setVisible(true);
		m_TitleLabel->setOpacity(0);
		m_TitleLabel->runAction(CCFadeIn::create(0.2f));
	}
	else
	{
		m_TitleBar->playAnimation("toasttitle_end");
		m_TitleLabel->setVisible(false);
	}
}


void SynopsisUiPanel::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void SynopsisUiPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (name == "sbtn_change_move_left")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (LayerManager::getSingletonPtr()->hasLayer("Main"))
		{
			SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
			_pMainPanel->CharacterLeftMove();
		}

	}
	else if (name == "sbtn_change_move_right")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (LayerManager::getSingletonPtr()->hasLayer("Main"))
		{
			SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
			_pMainPanel->CharacterRightMove();
		}
	}
	else if (name == "sbtn_button_select")
	{
		//ShowDialog();
		SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
		int _id = _pMainPanel->m_characterId[_pMainPanel->m_selectId];
		GameDataManager::getSingletonPtr()->SetAccountCharacter(_id);
		new AccountPopupPanel(AccountPopupPanel::NICKNAME_TYPE);
	}
}

void SynopsisUiPanel::update(float dt)
{

}

bool SynopsisUiPanel::handling(STCMD &stCmd)
{
	if (!mLoginProcess)
		return false;

	return false;
}


void SynopsisUiPanel::ShowDialog()
{
	ShowTitle(false);
	ShowPlayerSelectPanel(false);

	if (LayerManager::getSingletonPtr()->hasLayer("Main") &&
		LayerManager::getSingletonPtr()->hasLayer("Information") &&
		LayerManager::getSingletonPtr()->hasLayer("Dialog") 
		//&& LayerManager::getSingletonPtr()->hasLayer("Tutorial")
		)
	{
		SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
		SynopsisCharacterInfoPanel* _pInfoPanel = dynamic_cast<SynopsisCharacterInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("Information"));
		SynopsisDialogPanel* _pDialogPanel = dynamic_cast<SynopsisDialogPanel*>(LayerManager::getSingletonPtr()->getLayer("Dialog"));
		//SynopsisUiTutorial* _pTutorial = dynamic_cast<SynopsisUiTutorial*>(LayerManager::getSingletonPtr()->getLayer("Tutorial"));

		_pMainPanel->ShowDealer(true);
		_pMainPanel->ShowCharacter(false);
		_pInfoPanel->ShowInfo(false);
		_pDialogPanel->ShowDialog(true);
		_pDialogPanel->ShowText(6);
		_pDialogPanel->m_TextIdx = 7;

		//_pTutorial->applyUserData();
	}
}

bool SynopsisUiPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bSelectCharacter == true)
	{
		m_bMoveing = false;
		return true;
	}

	return false;
}

void SynopsisUiPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bMoveing == true)
		return;

	if (LayerManager::getSingletonPtr()->hasLayer("Main"))
	{
		SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
		float _move = pTouch->getLocation().x - pTouch->getStartLocation().x;
		if (_move > 0.f)
		{
			if (_move < 80.f)
			{
				_pMainPanel->CharacterMove(_move);
			}
			else
			{
				m_bMoveing = true;
				_pMainPanel->CharacterRightMove();
			}

		}

		if (_move < 0.f)
		{
			if (_move > -80.f)
			{
				_pMainPanel->CharacterMove(_move);
			}
			else
			{
				m_bMoveing = true;
				_pMainPanel->CharacterLeftMove();
			}
		}

		
	}
}

void SynopsisUiPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bMoveing == true)
		return;

	if (LayerManager::getSingletonPtr()->hasLayer("Main"))
	{
		SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
		_pMainPanel->CharacterMove(0);
	}
}

void SynopsisUiPanel::setLightUse(bool use)
{
	mLight->setVisible(use);
}


void SynopsisUiPanel::onEnter()
{
	Panel::onEnter();

	setKeypadEnabled(true);
	setTouchable(true);
	scheduleUpdate();
}