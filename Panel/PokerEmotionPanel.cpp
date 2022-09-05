#include "pch.h"
#include "PokerEmotionPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "PokerBackgroundPanel.h"
#include "PokerRankHelper.h"

PokerEmotionPanel::PokerEmotionPanel(int _panelType)
{
	m_PanelType = _panelType;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);

}

PokerEmotionPanel::~PokerEmotionPanel()
{
	//destruct();
}

void PokerEmotionPanel::InitPanel()
{
	if (m_PanelType == PANEL_TYPE_LEFT_ONE || m_PanelType == PANEL_TYPE_LEFT_TWO)
	{
		construct(getMxmlPath() + "dmy_userinfo_board.mxml");
	}
	else if (m_PanelType == PANEL_TYPE_RIGHT_ONE || m_PanelType == PANEL_TYPE_RIGHT_TWO)
	{
		construct(getMxmlPath() + "dmy_userinfo_board.mxml");
	}
}

void PokerEmotionPanel::InitImage()
{
	mRankIcon = getSkel("skel_rank_icon");	
	PokerRankHelper::setRankIcon(mRankIcon, 0);

	PokerBackgroundPanel* _pBackPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetBackgroundPanel();

	if (!_pBackPanel)
		return;

	switch (m_PanelType)
	{
	case PANEL_TYPE_LEFT_TWO:
	{
		CCRect _checkRect = _pBackPanel->getDummy("dmy_userinfo_board2");
		CCPoint _checkPanelPos = ccp(_checkRect.origin.x + 160.f, 45.f - _checkRect.origin.y);
		setContentSize(_checkRect.size);
		setRotation(-25.f);
		setPosition(_checkPanelPos);		
		break;
	}
	case PANEL_TYPE_LEFT_ONE:
	{
		CCRect _checkRect = _pBackPanel->getDummy("dmy_userinfo_board4");	//확정
		CCPoint _checkPanelPos = ccp(_checkRect.origin.x + 160.f, 45.f - _checkRect.origin.y);
		setContentSize(_checkRect.size);
		setRotation(-25.f);
		setPosition(_checkPanelPos);		
		break;
	}
	case PANEL_TYPE_RIGHT_ONE:
	{
		CCRect _checkRect = _pBackPanel->getDummy("dmy_userinfo_board5");
		CCPoint _checkPanelPos = ccp(_checkRect.origin.x - 160.f, 45.f - _checkRect.origin.y);
		setContentSize(_checkRect.size);
		setRotation(25.f);
		setPosition(_checkPanelPos);		
		break;
	}
	case PANEL_TYPE_RIGHT_TWO:
	{
		CCRect _checkRect = _pBackPanel->getDummy("dmy_userinfo_board3");	//확정
		CCPoint _checkPanelPos = ccp(_checkRect.origin.x - 160.f, 45.f - _checkRect.origin.y);
		setContentSize(_checkRect.size);
		setRotation(25.f);
		setPosition(_checkPanelPos);		
		break;
	}
	}	
}

void PokerEmotionPanel::initButton()
{
	getButton("sbtn_check_box_brown")->setListener(this);
}


bool PokerEmotionPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (isVisible() == true)
	{
		if (getButton("sbtn_check_box_brown")->hasCollided(getButton("sbtn_check_box_brown")->convertToNodeSpace(pTouch->getLocation())) == false)
		{
			setVisible(false);
		}
	}
	return false;
}


void PokerEmotionPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void PokerEmotionPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void PokerEmotionPanel::resume()
{
}

void PokerEmotionPanel::onClicked(const string& name)
{
	if (name == "sbtn_check_box_brown")
	{
		if (m_bBlockEmotion == true)
		{
			m_bBlockEmotion = false;
			int _clientIndex = m_PanelType;
			int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_clientIndex);
			RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);

			if (_pPlayer)
			{
				_pPlayer->m_bEmotionBlock = false;
			}
		}
		else
		{
			m_bBlockEmotion = true;
			int _clientIndex = m_PanelType;
			int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_clientIndex);
			RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);

			if (_pPlayer)
			{
				_pPlayer->m_bEmotionBlock = true;
			}
				
		}
	}
}

void PokerEmotionPanel::update(float dt)
{
}

bool PokerEmotionPanel::handling(STCMD &stCmd)
{
	return false;
}

void PokerEmotionPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}