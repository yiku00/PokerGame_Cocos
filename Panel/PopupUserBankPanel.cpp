#include "pch.h"
#include "PopupUserBankPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "ReplayGameManager.h"

PopupUserBankPanel::PopupUserBankPanel()
{
	mLoginProcess = false;

	m_pReplayListView = nullptr;
	m_pReplayListContainer = nullptr;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);
	
	m_ViewDataIndex = 10;
}


PopupUserBankPanel::~PopupUserBankPanel()
{
	//destruct();
}

void PopupUserBankPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_up_panel.mxml");
}

void PopupUserBankPanel::InitImage()
{
	getSkel("skel_level_crack")->setVisible(false);
	getLabel("txt_level_gift")->setVisible(false);
	getLabel("txt_level_next")->setVisible(false);

	getLabel("txt_bank_outgold")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_bank_ingold")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_bank_slash")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
}

void PopupUserBankPanel::initButton()
{
	m_bankButton = getButton("sbtn_bank_button");
	m_bankButton->getButtonSkelObject()->setSkin("mark_cancel");
	m_bankButton->setType(Button::NoPressImg);
	m_bankButton->setPaused(true);
	m_bankButton->setEnable(true);
	/*getButton("sbtn_title_cancel_stay")->setListener(this);*/

	m_ButtonPosX = m_bankButton->getPositionX();
	m_ButtonMaxPosX = m_ButtonPosX + getImage("skel_bankl_bar")->getBounding().size.width;

	m_CheckButton = getButton("sbtn_bank_check");
	m_CheckButton->setSkelAnimation("grange_on_stay");
	m_CheckButton->setType(Button::NoPressImg);
	m_CheckButton->setPaused(true);
	m_CheckButton->setEnable(true);
}


bool PopupUserBankPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pTouchPoint = pTouch->getLocation();

	if (m_bankButton)
	{
		if (m_bankButton->hasCollided(m_bankButton->convertToNodeSpace(pTouchPoint))){
			if (m_bankButton->isEnabled()){
				//_bankButton->setSkelAnimation("inpanel_button_in", false);
				m_ButtonStartPosition = m_bankButton->getPosition();
				return true;
			}
		}
	}
	return false;
}


void PopupUserBankPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pTouchPoint = pTouch->getLocation();

	if (m_bankButton)
	{
		if (m_bankButton->isEnabled()){
			CCPoint StartPos = pTouch->getStartLocation();
			float MovePosX = pTouchPoint.x - StartPos.x;

			if (m_ButtonStartPosition.x + MovePosX < m_ButtonPosX)
				return;

			if (m_ButtonStartPosition.x + MovePosX > m_ButtonMaxPosX)
				return;

			m_bankButton->setPositionX(m_ButtonStartPosition.x + MovePosX);
		}
	}
}


void PopupUserBankPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pTouchPoint = pTouch->getLocation();

	if (m_bankButton)
	{
		if (m_bankButton->hasCollided(m_bankButton->convertToNodeSpace(pTouchPoint))){
			if (m_bankButton->isEnabled()){

				return;
			}
		}

	}
}

void PopupUserBankPanel::resume()
{
}

void PopupUserBankPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (strncmp("ReplayButton", name.c_str(), 12) == 0)
	{
		int _index = nxExtractInt(name, "ReplayButton");
		
		if (GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->has_seq())
		{
			int64 _seq = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->seq();
			bool _isLike = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->islike();
			ReplayGameManager::getSingletonPtr()->SetIsLike(_isLike);
			eReplayType _type = eReplayType::Person;

			WebService::getSingletonPtr()->_sendReplayStartReq(_type, _seq);
		}
	}

	if (name == "sbtn_grange_on_stay1")
	{

	}

	if (name == "sbtn_grange_on_stay2")
	{

	}

}

void PopupUserBankPanel::update(float dt)
{
}

bool PopupUserBankPanel::handling(STCMD &stCmd)
{
	return false;
}

void PopupUserBankPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}
