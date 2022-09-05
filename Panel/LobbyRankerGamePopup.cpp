#include "pch.h"
#include "LobbyRankerGamePopup.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "Web/WebService.h"
#include "GameStringDepot.h"
#include "LobbyUIPanel.h"

LobbyRankerGamePopup::LobbyRankerGamePopup()
{
	for (int _i = 0; _i < RANKER_CELL_MAX; _i++)
	{
		m_RankerGameCell[_i] = nullptr;
	}

	m_gameMode = GameMode::MODE_NORMAL_TOURNAMENT;

	InitPanel();
	InitImage();
	InitButton();

	setButtonListener(this);

}

LobbyRankerGamePopup::~LobbyRankerGamePopup()
{
}

void LobbyRankerGamePopup::InitPanel()
{
	construct(getMxmlPath() + "dmy_otherstorage.mxml");

	for (int _i = 0; _i < RANKER_CELL_MAX; _i++)
	{
		if(m_RankerGameCell[_i])
			continue;

		CCPoint _pos = getDummy("dmy_l_bar" + StringConverter::toString(_i+1)).origin;

		CCSize _ButtonPanelSize = m_RankerGameCell[_i]->getDummy("dmy_l_bar").size;
		CCPoint _btnPos = getDummy("dmy_button_small").origin;
		_btnPos.y = -_btnPos.y;
		m_RankerGameCell[_i] = new Panel();
		m_RankerGameCell[_i]->construct(getMxmlPath() + "dmy_button_small.mxml");
		m_RankerGameCell[_i]->setPosition(_btnPos);
		addChild(m_RankerGameCell[_i]);
		m_RankerGameCell[_i]->release();

		Button* _pButton = m_RankerGameCell[_i]->getButton("sbtn_button");
		_pButton->setTag(_i);
		_pButton->setPaused(true);

		Nx::Label* _pBtnShodow = m_RankerGameCell[_i]->getLabel("txt_button_under");
		Nx::Label* _pBtnText = m_RankerGameCell[_i]->getLabel("txt_button");

		Nx::Label* _pLetterName = m_RankerGameCell[_i]->getLabel("txt_letter_name");
		Nx::Label* _pSendUserName = m_RankerGameCell[_i]->getLabel("txt_username");
		Nx::Label* _pTimeLimit = m_RankerGameCell[_i]->getLabel("txt_letter_timelimit");
		Nx::Label* _pNum = m_RankerGameCell[_i]->getLabel("txt_buttonsum");

		_pBtnShodow->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pBtnText->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		_pLetterName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pSendUserName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pTimeLimit->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pNum->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		//m_ListCell[_i]->getLabel("txt_letter_send")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		_pBtnShodow->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTER_GET_UNIT").c_str());
		_pBtnText->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTER_GET_UNIT").c_str());
		_pTimeLimit->setOpacity(175);

		m_RankerGameCell[_i]->setPositionX(_pos.x);
		m_RankerGameCell[_i]->setPositionY(-_pos.y);
		addChild(m_RankerGameCell[_i]);
		m_RankerGameCell[_i]->release();
	}
}

void LobbyRankerGamePopup::InitImage()
{
	//getSkel("skel_backcolor");
	//getSkel("skel_panel");
	//getSkel("skel_titleeffect");

	//getLabel("txt_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//getLabel("txt_title")->setString("");
}

void LobbyRankerGamePopup::InitButton()
{
	//getButton("sbtn_cancel")->setListener(this);
	//getButton("sbtn_cancel")->setType(Button::NoPressImg);
}

void LobbyRankerGamePopup::onClicked(const string& name)
{
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);

	if (name == "sbtn_cancel")
	{
		ShowPanel(false);
	}

	if (strncmp("ReplayButton", name.c_str(), 12) == 0)
	{
		int _index = nxExtractInt(name, "ReplayButton");

		if (GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->has_seq())
		{
			int64 _seq = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->seq();
			if (m_gameMode == GameMode::MODE_NORMAL_TOURNAMENT)
			{
				WebService::getSingletonPtr()->TournamentReplayReq(_seq);
			}
			else if (m_gameMode == GameMode::MODE_SURVIVAL_TOURNAMENT)
			{
				WebService::getSingletonPtr()->SurvivalReplayReq(_seq);
			}
		}
	}
}

bool LobbyRankerGamePopup::handling(STCMD &stCmd)
{
	return false;
}

void LobbyRankerGamePopup::ShowPanel(bool _enable)
{
	if (_enable == true)
	{
		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_RANKER_GAME_POPUP);		
	}
	else
	{
		GameDataManager::getSingletonPtr()->PopUiState();		
	}
}

void LobbyRankerGamePopup::SetData(string &matchName)
{
	int _size = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size();

	getLabel("txt_title")->setString(matchName.c_str());
	getLabel("txt_title_under")->setString(matchName.c_str());


	string titleStr = "";
	string title_idx = "";
	UserSummaryInfo userInfo;
	int count = 0;

	for (int _i = 0; _i < RANKER_CELL_MAX; _i++)
	{
		if (_i < _size)
		{
			W_ReplaySaveInfo* _pInfo = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_i];
			count = 0;
			titleStr = "";
			title_idx = "TXT_SURVIVAL_REPLAY_TITLE_" + StringConverter::toString(_i);
			titleStr = matchName.c_str() + GameStringDepot::getSingletonPtr()->getString(title_idx);

			//m_RankerGameCell[_i]->getButton("sbtn_inpanel_button2_stay")->setEnable(true);
			m_RankerGameCell[_i]->setVisible(true);
			m_RankerGameCell[_i]->getLabel("txt_letter_name")->setString(titleStr.c_str());
			m_RankerGameCell[_i]->getLabel("txt_letter_timelimit")->setString(_pInfo->date().c_str());

			SkelObject* _userphoto = m_RankerGameCell[_i]->getSkel("skel_userphoto");

			switch (_pInfo->gametype())
			{
			case GameKind::GAMEKIND_7POKER:
				_userphoto->playAnimation("symbol_sevenpoker");
				break;
			case GameKind::GAMEKIND_HIGH_LOW:
				_userphoto->playAnimation("symbol_highlow");
				break;
			case GameKind::GAMEKIND_BADUKI:
				_userphoto->playAnimation("symbol_badugi");
				break;
			case GameKind::GAMEKIND_HOLDEM:
				_userphoto->playAnimation("symbol_texasholdem");
				break;
			default:
				_userphoto->playAnimation("symbol_allgame");
				break;
			}
		}
		else
		{
			//m_RankerGameCell[_i]->getButton("sbtn_inpanel_button2_stay")->setEnable(false);
			m_RankerGameCell[_i]->setVisible(false);
		}
	}
}

void LobbyRankerGamePopup::SetType(GameMode _gamemode)
{
	m_gameMode = _gamemode;
}

void LobbyRankerGamePopup::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}