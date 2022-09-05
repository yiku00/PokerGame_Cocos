#include "pch.h"
#include "PokerResultPanel.h"
#include "GameDataManager.h"
#include "HeroUtil.h"
#include "NxUtil.h"
#include "PokerTopPanel.h"
#include "socket\TCPService.h"
#include "GameStringDepot.h"

PokerResultPanel::PokerResultPanel()
{
	mParentPanel = nullptr;
	m_Background = nullptr;
	mMadeResult = -1;
	m_isReplayLoad = false;
	initPanel();
}

PokerResultPanel::~PokerResultPanel()
{
	mMainPanel->removeAllChildren();

	removeAllChildren();
}

void PokerResultPanel::initPanel()
{
	_setParentPanel();
	if (mParentPanel) 
	{
		//setPosition(mParentPanel->getDummy("dmy_result_board").origin);
		mMainPanel = new Panel();
		mMainPanel->construct(getMxmlPath() + "dmy_result_board.mxml");

		CCSize contentsSize = mMainPanel->getDummy("dmy_result_board").size;
		mMainPanel->setPositionY(contentsSize.height - DESIGN_HEIGHT - contentsSize.height / 2.f);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		this->setPosition(mParentPanel->getImage("dmy_result_board")->getPosition());
		addChild(mMainPanel);
		mMainPanel->release();

		mMainPanel->getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("PokerResultPanel_TITLE").c_str());
	}
	addPlayerResultPanel();	
}

/*
void PokerResultPanel::SetPlayerPanel()
{
	GameRoomInfo* _pRoomInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
	for (int _i = 1; _i < GAME_USER_MAX; _i++)
	{
		int _UserIdx = (_pRoomInfo->GetMyPo() + _i) % GAME_USER_MAX;

		if (_pRoomInfo->m_UserList[_UserIdx] == nullptr)
		{
			ShowPlayerPanel(_i, false);
		}
		else
		{
			ShowPlayerPanel(_i, true);
		}
	}
}
*/

void PokerResultPanel::addPlayerResultPanel()
{
	if (!mParentPanel)
		return;

	string path;
	for (int i = 0; i < GAME_USER_MAX; i++)
	{
		mPlayerResultPanel[i] = new PokerPlayerResultPanel();
		path = "dmy_result_board_slot";
		path += StringConverter::toString(i + 1);

		//mPlayerResultPanel[i]->setPositionX(mMainPanel->getImage(path.c_str())->getPositionX() - mMainPanel->getDummy(path.c_str()).size.width / 2.0f + 1);
		//mPlayerResultPanel[i]->setPositionY(mMainPanel->getImage(path.c_str())->getPositionY() - mMainPanel->getDummy(path.c_str()).size.height / 2.0f);

		mPlayerResultPanel[i]->setPosition(mMainPanel->getImage(path.c_str())->getPosition());
		mPlayerResultPanel[i]->initPanel(mMainPanel);
		mMainPanel->addChild(mPlayerResultPanel[i]);
		mPlayerResultPanel[i]->release();
		//mPlayerResultPanel[i]->HidePanel();
		mPlayerResultPanel[i]->setVisible(true);

	}

	m_Background = mMainPanel->getSkel("skel_result_board");
	m_Background->playAnimation("result_board_loop");
	m_Background->setListener(this);
}

void PokerResultPanel::ShowPlayerResultPanel(int _index, bool _visible)
{
	mPlayerResultPanel[_index]->setVisible(_visible);
}

void PokerResultPanel::_setParentPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("Background"));
	assert(mParentPanel);
}

void PokerResultPanel::SetData(int _index, GameKind gameKind, WinKind winKind, string& nickname, bool isMine, int highJokboKind, int lowJokboKind, int64 inoutGameMoney)
{
	if (mPlayerResultPanel[_index] == nullptr)
		return;

	mPlayerResultPanel[_index]->SetData(gameKind, winKind, nickname, isMine, highJokboKind, lowJokboKind, inoutGameMoney);
}

void PokerResultPanel::SetPlayerResultPaenlVisible(int _index, bool isVisible)
{
	if (mPlayerResultPanel[_index] == nullptr)
		return;

	mPlayerResultPanel[_index]->setVisible(isVisible);
}

void PokerResultPanel::SetPlayerResultPanelAllInit()
{
	for (int i = 0; i < GAME_USER_MAX; i++)
	{
		if (mPlayerResultPanel[i] == nullptr)
			return;
		mPlayerResultPanel[i]->InitData();
		mPlayerResultPanel[i]->HidePanel();
	}
}

void PokerResultPanel::SetPlayerResultPaenlAllVisible(bool isVisible)
{
	for (int i = 0; i < GAME_USER_MAX; i++)
	{
		if (mPlayerResultPanel[i] == nullptr)
			return;

		if (isVisible)
			mPlayerResultPanel[i]->ShowPanel();
		else
		{
			mPlayerResultPanel[i]->HidePanel();
		}
	}
}

void PokerResultPanel::ShowPanel()
{
	setVisible(true);
	m_Background->playAnimation("result_board_start");
	m_Background->appendAnimation("result_board_loop");
	SetPlayerResultPaenlAllVisible(false);
}


void PokerResultPanel::onAnimationEnded(const string& ani)
{
	if (!isVisible())
		return;

	if (ani.find("result_board_start") != string::npos)
	{

		SetPlayerResultPaenlAllVisible(true);
		SetTurnOnReplayButton();
	}
}

void PokerResultPanel::onClicked(const string& buttonName)
{
	if (buttonName == "sbtn_replay_button") 
	{
		SaveReplay();
	}
	else
	{
		if (buttonName.find("touchEnd") != string::npos)
		{
			string realName = nxReplace(buttonName, "touchEnd", "");
			if (realName == "sbtn_replay_button")
			{
				//m_ReplayBtn->setSkelAnimation("replay_out", false);
			}
		}
		else if (buttonName.find("touch") != string::npos)
		{

			string realName = nxReplace(buttonName, "touch", "");
			if (realName == "sbtn_replay_button")
			{
				//m_ReplayBtn->setSkelAnimation("replay_in", false);
			}

			return;
		}
	}
}

void PokerResultPanel::SetTurnOnReplayButton()
{
	if (m_isReplayLoad)
	{
// 		m_ReplayBtn->setEnable(true);
// 		m_ReplayBtn->setVisible(true);
// 		m_ReplayBtn->setSkelAnimation("replay_start");
// 		m_ReplayBtn->setSkelAnimation("replay_stay");
	}
	else
		m_isReplayLoad = true;

}

void PokerResultPanel::SetTurnOffReplayButton()
{
// 	m_ReplayBtn->setEnable(false);
// 	m_ReplayBtn->setVisible(false);
	m_isReplayLoad = false;
}

void PokerResultPanel::SaveReplay()
{
	//GameDataManager::getSingletonPtr()->SetReplayID(GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGamePlaySeq());
	TCPService::getSingletonPtr()->SendSaveGamePlayDataReq();
	SetTurnOffReplayButton();
}

void PokerResultPanel::setMadeResult(int madeJokbo)
{
	mMadeResult = madeJokbo;
	if (mMadeResult != -1) {
		GameDataManager::getSingleton().pokerResultMade(mMadeResult);
	}
}

