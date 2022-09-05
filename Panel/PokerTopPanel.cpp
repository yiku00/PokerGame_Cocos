#include "pch.h"
#include "PokerTopPanel.h"
#include "GameDataManager.h"
#include "HeroUtil.h"
#include "NxUtil.h"
#include "PokerChipWidget.h"
#include "JackpotPanel.h"
#include "ReplayGameManager.h"
#include "socket/TCPService.h"
#include "PokerPlayerInfoCommonPanel.h"
#include "PokerPlayerInfoPanel.h"
#include "BadugiSelectCardPanel.h"
#include "PokerPlayerInfoMyPanel.h"
#include "PokerBackgroundPanel.h"
#include "GameStringDepot.h"
#include "LobbyScene.h"
#include "PanelHelper.h"
#include "PokerShopHelper.h"
#include <Panel/LobbyFriendRequestPanel.h>

PokerTopPanel::PokerTopPanel()
{
	m_FadeBlackbox = nullptr;
	mParentPanel = nullptr;
	m_HiddenTouchPanel = nullptr;
	m_bTouchHiddenCard = false;
	m_bMoveHiddenCard = false;
	mIsOutButtonClick = false;

	initPanel();
}

PokerTopPanel::~PokerTopPanel()
{
	removeAllChildren();
}

void PokerTopPanel::initPanel()
{
	_setParentPanel();
	construct(getMxmlPath() + "top_button.mxml");
	m_HiddenTouchPanel = new Panel();
	m_HiddenTouchPanel->construct(getMxmlPath() + "dmy_hidden_card.mxml");
	addChild(m_HiddenTouchPanel);
	m_HiddenTouchPanel->release();
	//init
	CCSize _contentsize = getDummy("dmy_hidden_card").size;
	CCPoint _pos = getDummy("dmy_hidden_card").origin;
	_pos.y = -_pos.y;

	m_posStartHiddenPanel = _pos - ccp(150.f, 0.f);
	m_posMoveHiddenPanel = _pos;
	m_posStartHiddenCard = m_HiddenTouchPanel->getButton("sbtn_hiddenback")->getPosition();

	m_HiddenTouchPanel->getSkel("skel_hiddenfront")->playAnimation("hiddenfront_start");
	m_HiddenTouchPanel->getSkel("skel_hidden_card_start")->playAnimation("hidden_card_start");
	m_HiddenTouchPanel->getButton("sbtn_hiddenback")->getButtonSkelObject()->playAnimation("hiddenback_start");
	m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setType(Button::NoPressImg);
	m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setListener(this);
	m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setPaused(true);
	m_HiddenTouchPanel->setPosition(m_posStartHiddenPanel);
	//enable setting
	m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setEnable(false);
	m_HiddenTouchPanel->setTouchable(false);
	m_HiddenTouchPanel->setVisible(false);
	
	mHiddenBigTouchPanel = new Panel();
	mHiddenBigTouchPanel->construct(getMxmlPath() + "dmy_hidden_card_big.mxml");
	addChild(mHiddenBigTouchPanel);
	mHiddenBigTouchPanel->release();
	//init
	_contentsize = getDummy("dmy_hidden_card_big").size;
	_pos = getDummy("dmy_hidden_card_big").origin;
	_pos.y = -_pos.y;

	mBigPosStartHiddenPanel = _pos - ccp(150.f, 0.f);
	mBigPosMoveHiddenPanel = _pos;
	mBigPosStartHiddenCard = mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->getPosition();

	mHiddenBigTouchPanel->getSkel("skel_hiddenfront_big")->playAnimation("hiddenfront_big_start");
	mHiddenBigTouchPanel->getSkel("skel_hidden_card_start")->playAnimation("hidden_card_start");
	mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->getButtonSkelObject()->playAnimation("hiddenback_big_start");
	mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setType(Button::NoPressImg);
	mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setListener(this);
	mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setPaused(true);
	mHiddenBigTouchPanel->setPosition(mBigPosStartHiddenPanel);
	//enable setting
	mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setEnable(false);
	mHiddenBigTouchPanel->setTouchable(false);
	mHiddenBigTouchPanel->setVisible(false);

	mCharacterEffectLabel = getLabel("txt_chrackter_bonus");
	mOriginCharactgerEffectPos = mCharacterEffectLabel->getPosition();
	mCharacterEffectLabel->setVisible(false);
	_initImage();
}

void PokerTopPanel::UpdateMoveLabelString()
{
	if (GameDataManager::getSingletonPtr()->IsCustum)
		mMoveBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_INVITE").c_str());
	else
		mMoveBtnLabel->setString(GameStringDepot::getSingleton().getString("MOVE_ROOM").c_str());

	
}

void PokerTopPanel::_initImage()
{
	//임시 시작 버튼 설정.
	m_StartButton = getButton("sbtn_gamestart");
	m_StartButton->setListener(this);
	mStartButtonLabel = getLabel("txt_gamestart");
	mStartButtonLabel->setString(GameStringDepot::getSingletonPtr()->getString("PokerTopPanel_START").c_str());
	//비활성화.
	m_StartButton->setEnable(false);
	m_StartButton->setVisible(false);
	mStartButtonLabel->setVisible(false);
	m_StartButton->setType(Button::Touching);
	m_StartButton->setSkelAnimation("gamestart_stay");

	m_ExitBtn = getButton("sbtn_gameout");
	m_ExitBtn->setListener(this);
	m_ExitBtn->setType(Button::Touching);
	m_ExitBtn->setSkelAnimation("gameout_stay");

	m_MoveBtn = getButton("sbtn_tablemove");
	m_MoveBtn->setEnable(true);
	m_MoveBtn->setVisible(true);
	m_MoveBtn->setType(Button::Touching);
	m_MoveBtn->setSkelAnimation("tablemove_stay");

	mExitBtnLabel = getLabel("txt_gameout");
	mMoveBtnLabel = getLabel("txt_tablemove");

	mExitBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_OUT").c_str());
	mMoveBtnLabel->setString(GameStringDepot::getSingleton().getString("MOVE_ROOM").c_str());

	getButton("sbtn_tablemove")->setListener(this);

	/*
	m_ReplayBtn = getButton("sbtn_replay_button");
	m_ReplayBtn->setListener(this);
	m_ReplayBtn->setEnable(false);
	m_ReplayBtn->setVisible(false);
	m_ReplayBtn->setType(Button::Touching);
	m_ReplayBtn->setSkelAnimation("replay_stay");
	*/

	m_light = getSkel("skel_centerblack");
	m_light->setListener(this);
	m_light->setVisible(false);

	getSkel("skel_potmoney")->setVisible(false);
	getSkel("skel_potmoney")->readyAnimation("potmoney_start");
	getSkel("skel_potmoney")->setListener(this);

	m_LastRound = getSkel("skel_last_round");
	m_LastRound->setVisible(false);
	m_LastRound->playAnimation("last_round_normal");

	m_BadugiEffect = getSkel("skel_badugi_effect");
	m_BadugiEffect->setVisible(false);
	m_BadugiEffect->playAnimation("morning");

	m_Chip = getSkel("skel_getchip");
	m_Chip->setVisible(false);
	m_Chip->setListener(this);

	m_LevelupEffect = getSkel("skel_level_up");
	m_LevelupEffect->setVisible(false);
	m_LevelupEffect->playAnimation("level_up", false);

	m_MadeBonusEffect = getSkel("skel_made_bonus");
	m_MadeBonusEffect->setVisible(false);
	m_MadeBonusEffect->playAnimation("made_bonus", false);

	m_AutoRefillEffect = getSkel("skel_autorefill_start");
	m_AutoRefillEffect->setVisible(false);
	m_AutoRefillEffect->playAnimation("autorefill_start", false);

	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
	{
		PokerBackgroundPanel* _pPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetBackgroundPanel();
		if (_pPanel)
		{
			_pPanel->m_HoldemCommunityCardButton->setListener(this);
		}
	}

	Panel* tormentResultPanel = new Panel();
	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)	{
		tormentResultPanel->construct(getMxmlPath() + "dmy_panelrank_texas.mxml");
	}
	else {
		tormentResultPanel->construct(getMxmlPath() + "dmy_panelrank.mxml");
	}
	addChild(tormentResultPanel);
	tormentResultPanel->release();


	m_GameRankBack[0] = tormentResultPanel->getSkel("skel_panelrank1");
	m_GameRankBack[1] = tormentResultPanel->getSkel("skel_panelrank2");
	m_GameRankBack[2] = tormentResultPanel->getSkel("skel_panelrank4");
	m_GameRankBack[3] = tormentResultPanel->getSkel("skel_panelrank5");
	m_GameRankBack[4] = tormentResultPanel->getSkel("skel_panelrank3");

	m_GameRank[0] = tormentResultPanel->getLabel("txt_gamerank1");
	m_GameRank[1] = tormentResultPanel->getLabel("txt_gamerank2");
	m_GameRank[2] = tormentResultPanel->getLabel("txt_gamerank4");
	m_GameRank[3] = tormentResultPanel->getLabel("txt_gamerank5");
	m_GameRank[4] = tormentResultPanel->getLabel("txt_gamerank3");

	string myOtherStr = "panelrank_others_start";
	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)	{
		string myOtherStr = "panelrank_texas_start";
	}

	m_GameRankBack[0]->playAnimation("panelrank_my_start");
	m_GameRankBack[1]->playAnimation(myOtherStr);
	m_GameRankBack[2]->playAnimation(myOtherStr);
	m_GameRankBack[3]->playAnimation(myOtherStr);
	m_GameRankBack[4]->playAnimation(myOtherStr);

	mGameRankUnder[0] = tormentResultPanel->getLabel("txt_gamerank1_under");
	mGameRankUnder[1] = tormentResultPanel->getLabel("txt_gamerank2_under");
	mGameRankUnder[2] = tormentResultPanel->getLabel("txt_gamerank4_under");
	mGameRankUnder[3] = tormentResultPanel->getLabel("txt_gamerank5_under");
	mGameRankUnder[4] = tormentResultPanel->getLabel("txt_gamerank3_under");

	for (int _i = 0; _i < 5; _i++)
	{
		mGameRankUnder[_i]->setVisible(false);
		m_GameRankBack[_i]->setVisible(false);
		m_GameRank[_i]->setVisible(false);
	}

	mPlayCountBg = tormentResultPanel->getImage("skel_roomnumber_panel");
	m_PlayerCountBack = tormentResultPanel->getSkel("skel_panelrank1");
	m_PlayerCount = tormentResultPanel->getLabel("txt_peoplenumber");
	m_PlayerCount->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TotalPlayerCount = tormentResultPanel->getLabel("txt_peoplenumber_sum");
	m_TotalPlayerCount->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	mPlayCountBg->setVisible(false);
	m_PlayerCountBack->setVisible(false);
	m_PlayerCount->setVisible(false);
	m_TotalPlayerCount->setVisible(false);

// 	for (int _i = 0; _i < 10; _i++)
// 	{
// 		string _skelName = "skel_fire_work" + StringConverter::toString(_i + 1);
// 		m_Firework[_i] = getSkel(_skelName);
// 		m_Firework[_i]->playAnimation("fire_work1");
// 		m_Firework[_i]->setVisible(false);
// 	}

	if (m_FadeBlackbox == nullptr)
	{
		m_FadeBlackbox = new SkelObject();
		m_FadeBlackbox->setSkelAnim("ui/smallbutton_8888.json");
		m_FadeBlackbox->playAnimation("centerblack_stay");
		m_FadeBlackbox->setPosition(ccp(DESIGN_WIDTH / 2.f, DESIGN_HEIGHT * 2.f));
		addChild(m_FadeBlackbox, ZODER_BLACKBOX);
		m_FadeBlackbox->release();
	}
}

void PokerTopPanel::ReSetResultPlayerRank()
{
	for (int _i = 0; _i < 5; _i++)
	{
		m_GameRankBack[_i]->setVisible(false);
		m_GameRank[_i]->setVisible(false);
		mGameRankUnder[_i]->setVisible(false);
	}
}

void PokerTopPanel::SetResultPlayerRank(int _po, bool _visible, int _rank)
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr() == NULL)
		return;

	RoomUserData* _pUser = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_po);
	if (_pUser)
	{
		int _clientIndex = GameDataManager::getSingletonPtr()->ServerToClientIndex(_po);

		if (_visible == false)
		{
			m_GameRankBack[_clientIndex]->setVisible(false);
			m_GameRank[_clientIndex]->setVisible(false);
			mGameRankUnder[_clientIndex]->setVisible(false);
		}
		else
		{
			if (_rank == 10000000)
			{
				m_GameRank[_clientIndex]->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GIVEUP_LOSE").c_str());
				mGameRankUnder[_clientIndex]->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GIVEUP_LOSE").c_str());
			}
			else
			{
				string _rankstr = StringConverter::toString(_rank) + GameStringDepot::getSingletonPtr()->getString("TXT_RANK");
				m_GameRank[_clientIndex]->setString(_rankstr.c_str());
				mGameRankUnder[_clientIndex]->setString(_rankstr.c_str());
			}
			
			mGameRankUnder[_clientIndex]->setVisible(true);
			m_GameRankBack[_clientIndex]->setVisible(true);
			m_GameRank[_clientIndex]->setVisible(true);
		}
	}
}

void PokerTopPanel::SetGameMode(GameMode _mode)
{
	if (_mode == GameMode::MODE_NORMAL)
	{
		mPlayCountBg->setVisible(false);
		m_PlayerCountBack->setVisible(false);
		m_PlayerCount->setVisible(false);
		m_TotalPlayerCount->setVisible(false);
	}
	else
	{
		m_MoveBtn->setVisible(false);
		m_MoveBtn->setEnable(false);
		mMoveBtnLabel->setVisible(false);

		if (_mode == GameMode::MODE_SURVIVAL_TOURNAMENT)
		{
			m_PlayerCount->setString(GameStringDepot::getSingletonPtr()->getString("TXT_PLAYERCOUNT_LABEL").c_str());
			m_TotalPlayerCount->setString("000/000");
			mPlayCountBg->setVisible(true);
			m_PlayerCountBack->setVisible(false);
			m_PlayerCount->setVisible(true);
			m_TotalPlayerCount->setVisible(true);
		}
		else
		{
			mPlayCountBg->setVisible(false);
			m_PlayerCountBack->setVisible(false);
			m_PlayerCount->setVisible(false);
			m_TotalPlayerCount->setVisible(false);
		}
		
	}
}

void PokerTopPanel::SetPLayerCount(int _count, int _totalCount)
{
	string _playerCount = StringConverter::toString(_count) + "/" + StringConverter::toString(_totalCount);
	m_TotalPlayerCount->setString(_playerCount.c_str());
}

void PokerTopPanel::setPlayerInfoUserOptionPanel(int _id, bool _visible)
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
		return;

	PokerPlayerInfoPanel* _pInfoPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel();
	if (_pInfoPanel == nullptr)
		return;

	for (int _i = 0; _i < 5; _i++)
	{
		int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_i);
		PokerPlayerInfoCommonPanel* _pPanel = _pInfoPanel->GetPlayerCommonPanelWithIndex(_i);
		if (_pPanel == nullptr)
			continue;
	
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex) == nullptr)
			continue;

		if (_id == _i)
		{
			if (_pPanel->m_pUserInfoPanel)
			{
				_pPanel->m_pUserInfoPanel->setEmotionActivate(false);
				_pPanel->m_pUserInfoPanel->SetTimerShow();
			}
				
		}
		else
		{
			if (_pPanel->m_pUserInfoPanel)
			{
				_pPanel->m_pUserInfoPanel->cleanup();
				_pPanel->m_pUserInfoPanel->setVisible(false);
			}
				
		}
	}
	
}

void PokerTopPanel::onClicked(const string& buttonName)
{
	if (buttonName == "sbtn_cardtouch")
	{
		bool _isBig = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isBigCommunityCard;
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->ShowCommnityBig(!_isBig);
	}
	else if (buttonName == "sbtn_tablemove") 
	{
	}
	else if (buttonName == "sbtn_hiddenback")
	{
		
	}
	else if (buttonName == "sbtn_play_stay") {
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			ReplayGameManager::getSingletonPtr()->ResetTextField();
			ReplayGameManager::getSingletonPtr()->ReplayPause();
		}
	}
	else if (buttonName == "sbtn_reset_stay") {
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			ReplayGameManager::getSingletonPtr()->ResetTextField();
			ReplayGameManager::getSingletonPtr()->ReplayReset();
		}
	}
	else if (buttonName == "sbtn_chat_stay") {
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true
			&& ReplayGameManager::getSingletonPtr()->GetIsPublish() == true)
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			ReplayGameManager::getSingletonPtr()->ResetTextField();
			ReplayGameManager::getSingletonPtr()->InputChat();
		}
	}
	else if (buttonName == "sbtn_recommend_stay") {
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true
			&& ReplayGameManager::getSingletonPtr()->GetIsPublish() == true)
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			ReplayGameManager::getSingletonPtr()->ResetTextField();
			int64 _seq = ReplayGameManager::getSingletonPtr()->GetReplaySeq();
			WebService::getSingletonPtr()->_sendReplayLikeReq(ReplayGameManager::getSingletonPtr()->GetType(), _seq);
		}
	}
	else if (buttonName == "sbtn_chatarrow_up") {
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			ReplayGameManager::getSingletonPtr()->ResetTextField();
			ReplayGameManager::getSingletonPtr()->ClickBoardSetButton();
		}
	}
	else if (buttonName == "sbtn_gamestart") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameStart();
	}
	else if (buttonName == "MyPlayerInfo_Btn")
	{
		//if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel"))
		//{
		//	BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
		//	if (_pSelectCardPanel->isVisible())
		//		return;
		//}
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameMode() != GameMode::MODE_NORMAL)
			return;

		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(0);
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex)->m_IsStatcsUpdated == true)
		{
			setPlayerInfoUserOptionPanel(0, true);
		}
		else
		{
			int _socketId = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex)->m_pPlayerData->m_UID;
			TCPService::getSingletonPtr()->SendPlayerPlayStatcsReq(_serverIndex, _socketId);
		}
	}
	else if (buttonName == "LeftOnePlayerInfo_Btn")
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameMode() != GameMode::MODE_NORMAL)
			return;

		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(2);
		RoomUserData* _user = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
		if (_user == nullptr)
			return;
		if (_user->m_IsStatcsUpdated == true)
		{
			setPlayerInfoUserOptionPanel(2, true);
		}
		else
		{
			int _socketId = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex)->m_pPlayerData->m_UID;
			TCPService::getSingletonPtr()->SendPlayerPlayStatcsReq(_serverIndex, _socketId);
		}
	}
	else if (buttonName == "LeftTwoPlayerInfo_Btn")
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameMode() != GameMode::MODE_NORMAL)
			return;

		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(1);
		RoomUserData* _user = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
		if (_user == nullptr)
			return;
		if (_user->m_IsStatcsUpdated == true)
		{
			setPlayerInfoUserOptionPanel(1, true);
		}
		else
		{
			int _socketId = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex)->m_pPlayerData->m_UID;
			TCPService::getSingletonPtr()->SendPlayerPlayStatcsReq(_serverIndex, _socketId);
		}
	}
	else if (buttonName == "RightOnePlayerInfo_Btn")
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameMode() != GameMode::MODE_NORMAL)
			return;

		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(3);
		RoomUserData* _user = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
		if (_user == nullptr)
			return;
		if (_user->m_IsStatcsUpdated == true)
		{
			setPlayerInfoUserOptionPanel(3, true);
		}
		else
		{
			int _socketId = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex)->m_pPlayerData->m_UID;
			TCPService::getSingletonPtr()->SendPlayerPlayStatcsReq(_serverIndex, _socketId);
		}
	}
	else if (buttonName == "RightTwoPlayerInfo_Btn")
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameMode() != GameMode::MODE_NORMAL)
			return;

		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(4);
		RoomUserData* _user = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
		if (_user == nullptr)
			return;
		if (_user->m_IsStatcsUpdated == true)
		{
			setPlayerInfoUserOptionPanel(4, true);
		}
		else
		{
			int _socketId = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex)->m_pPlayerData->m_UID;
			TCPService::getSingletonPtr()->SendPlayerPlayStatcsReq(_serverIndex, _socketId);
		}
	}
	else
	{
		//BettingKind kind;
		int po = 0;
		if (buttonName.find("touchEnd") != string::npos)
		{
			string realName = nxReplace(buttonName, "touchEnd", "");
			if (realName == "sbtn_gameout")
			{
				GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_EXIT);
				if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
				{
					ReplayGameManager::getSingletonPtr()->CloseReplay();
					return;
				}					
				if (!mIsOutButtonClick)
					return;
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SetExit(true);
			}
			else if (realName == "sbtn_gamestart")
			{
				GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
				m_StartButton->setSkelAnimation("gamestart_out", false);
			}
			else if (realName == "sbtn_tablemove")
			{
				GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_EXIT);
				GameRoomInfo * roomInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
				if (roomInfo == nullptr || roomInfo->m_isReplayData == true)
					return;
				if (roomInfo->CanExit()) {
					GameDataManager::getSingleton().setPassward("");
					//notidata
					if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
						NotiFocusPanel* pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
						LayerManager::getSingleton().popLayer(pPanel);
					}

					TCPService::getSingletonPtr()->SendMoveRoomReq(GameDataManager::getSingletonPtr()->GetConnChannelId());
					//로딩창 보여준다.
					PanelHelper::pushLoadingPanel(GameStringDepot::getSingleton().getString("LOBBY_TABLE_MOVE_LOADING_DESC"));
				}
				else {
					//테이들...
					//창을 보여줘야 하나
					PanelHelper::pushAnnounceNotiPanel(GameStringDepot::getSingleton().getString("LOBBY_Table_CANT_MOVE_DESC"));
				}

			}

			return;
		}
		else if (buttonName.find("touch") != string::npos)
		{
			string realName = nxReplace(buttonName, "touch", "");
			if (realName == "sbtn_gameout")
			{
				GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_EXIT);
				if (mIsOutButtonClick)
					return;
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SetExit(false);
			}
			else if (realName == "sbtn_tablemove")
			{
				GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_EXIT);
				SetMoveStartButton();
			}
			else if (realName == "sbtn_gamestart")
			{
				GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
				m_StartButton->setSkelAnimation("gamestart_in", false);
			}

			return;
		}
	}
}

void PokerTopPanel::_setParentPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("Background"));
	assert(mParentPanel);
}

void PokerTopPanel::SetPressExitStartButton()
{
	m_ExitBtn->setSkelAnimation("gameout_in", false);
	mExitBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_OUT").c_str());
	mExitBtnLabel->setColor(StringConverter::parseColor3B("a47650"));
}

void PokerTopPanel::SetPressExitFailButton()
{
	m_ExitBtn->setSkelAnimation("gameout_fail", false);
	mExitBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_OUT").c_str());
	mExitBtnLabel->setColor(StringConverter::parseColor3B("a47650"));
}

void PokerTopPanel::SetPressExitReserveButton()
{
	//녹색 상태
	m_ExitBtn->setSkelAnimation("gameout_loop", false);
	mExitBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_OUT_RSV").c_str());
	mExitBtnLabel->setColor(StringConverter::parseColor3B("edf7c8"));
}

void PokerTopPanel::SetPressExitReserveCancelButton()
{
	//일반 나가기
	m_ExitBtn->setSkelAnimation("gameout_cancel", false);
	mExitBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_OUT").c_str());
	mExitBtnLabel->setColor(StringConverter::parseColor3B("a47650"));
}

void PokerTopPanel::SetReleaseExitButton()
{
	//녹색 상태
	m_ExitBtn->setSkelAnimation("gameout_loop", false);
	mExitBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_OUT_RSV").c_str());
	mExitBtnLabel->setColor(StringConverter::parseColor3B("edf7c8"));
}

void PokerTopPanel::SetMoveStartButton()
{
	m_MoveBtn->setSkelAnimation("tablemove_in", false);
	m_MoveBtn->setSkelAppendAnimation("tablemove_fail", false);
	m_MoveBtn->setSkelAppendAnimation("tablemove_stay", false);
}

void PokerTopPanel::SetTurnOnLight()
{
	//if (m_light)
	//{
	//	m_light->setVisible(true);
	//	m_light->playAnimation("centerblack_stay");
	//}
}

void PokerTopPanel::SetTurnOffLight()
{
	//if (m_light)
	//{
	//	m_light->playAnimation("centerblack_end", true);
	//}
}

void PokerTopPanel::SetTurnOnGameStartButton()
{
	m_StartButton->setEnable(true);
	m_StartButton->setVisible(true);
	mStartButtonLabel->setVisible(true);
	m_StartButton->setSkelAnimation("gamestart_stay");
}

void PokerTopPanel::SetTurnOffGameStartButton()
{
	mStartButtonLabel->setVisible(false);
	m_StartButton->setEnable(false);
	m_StartButton->setVisible(false);
}

/*
void PokerTopPanel::SetTurnOnReplayButton()
{
	m_ReplayBtn->setEnable(true);
	m_ReplayBtn->setVisible(true);
	m_ReplayBtn->setSkelAnimation("replay_start");
	m_ReplayBtn->setSkelAnimation("replay_stay");
}

void PokerTopPanel::SetTurnOffReplayButton()
{
	m_ReplayBtn->setEnable(false);
	m_ReplayBtn->setVisible(false);
}
*/


void PokerTopPanel::onAnimationEnded(const string& ani)
{
	if (ani.find("potmoney_end") != string::npos)
	{
		getSkel("skel_potmoney")->setVisible(false);
	}
	else if (ani.find("centerblack_end") != string::npos)
	{
		m_light->setVisible(false);
	}

	if (ani.find("getchip_end") != string::npos)
	{
		m_Chip->setVisible(false);
	}
}

void PokerTopPanel::GameStart()
{
	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->StartGameReq();
	CCLOG("I send Game Start %d", GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_UID);
	
	//비활성화.
	SetTurnOffGameStartButton();
	SetTurnOffLight();
}


void PokerTopPanel::onDetached()
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
	{
		ReplayGameManager::getSingletonPtr()->SendCommentData();
	}
}

bool PokerTopPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel"))
	{
		BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
		if (_pSelectCardPanel->TouchStart(pTouch) == true)
		{
			return true;
		}
	}

	if (m_HiddenTouchPanel == nullptr || mHiddenBigTouchPanel == nullptr)
		return false;

	if (m_HiddenTouchPanel->isVisible() == true && m_HiddenTouchPanel->getButton("sbtn_hiddenback")->isEnabled() == true)
	{
		Button* _pBtn = m_HiddenTouchPanel->getButton("sbtn_hiddenback");
		if (_pBtn->hasCollided(_pBtn->convertToNodeSpace(pTouch->getLocation())))
		{
			m_bTouchHiddenCard = true;
			m_bMoveHiddenCard = false;
			return true;
		}
	}
	else if (mHiddenBigTouchPanel->isVisible() == true && mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->isEnabled() == true)
	{
		Button* _pBtn = mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big");
		if (_pBtn->hasCollided(_pBtn->convertToNodeSpace(pTouch->getLocation())))
		{
			m_bTouchHiddenCard = true;
			m_bMoveHiddenCard = false;
			return true;
		}
	}
	return false;
}

void PokerTopPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel"))
	{
		BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
		_pSelectCardPanel->TouchMove(pTouch);
	}

	if (m_bTouchHiddenCard == false)
		return;

	float _moveX = pTouch->getLocation().x - pTouch->getStartLocation().x;
	if (_moveX > 0)
	{
		if (_moveX >= 80.f * 2)
		{
			_moveX = 80.f * 2;
			TouchHiddenCardEventStart(1.f);
		}
		else
		{
			if (m_HiddenTouchPanel->isVisible())
				m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setPositionX(m_posStartHiddenCard.x + _moveX * 0.5f);
			else if (mHiddenBigTouchPanel->isVisible()) {
				mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setPositionX(mBigPosStartHiddenCard.x + _moveX * 0.5f);

				float percenRatio = (100.f - 20.f ) / 80.f;
				float brightRatio = (20.f + percenRatio * _moveX * 0.5f) * 0.01f;

				CCLOG("opeercity = %f , percenRatio = %f , _moveX = %f ", brightRatio, percenRatio, _moveX);
				mHiddenBigTouchPanel->getSkel("skel_hidden_light")->setOpacity(255 * brightRatio);
				mHiddenBigTouchPanel->getSkel("skel_hidden_black")->setOpacity(255 * brightRatio);

				float scaleRatio = 1.0f + (percenRatio * _moveX * 0.5f) * 0.3f * 0.01f;
				CCLOG("scaleRatio = %f", scaleRatio);
				mHiddenBigTouchPanel->getSkel("skel_hidden_light")->setScale(scaleRatio);
			}
		}
	}
}
void PokerTopPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel"))
	{
		BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
		if (_pSelectCardPanel->isVisible() == true)
		{
			_pSelectCardPanel->TouchEnd(pTouch);
		}
	}

	if (m_bTouchHiddenCard == false)
		return;

	float _moveX = pTouch->getLocation().x - pTouch->getStartLocation().x;
	if (_moveX > 50)
	{
		TouchHiddenCardEventStart(1.f);
	}
	else
	{
		if (m_HiddenTouchPanel->isVisible())
			m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setPositionX(m_posStartHiddenCard.x);
		else if (mHiddenBigTouchPanel->isVisible())
			mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setPositionX(mBigPosStartHiddenCard.x);
	}
}

void PokerTopPanel::ShowLastRoundEffect(int _bigType)
{
	if (_bigType == 1)
	{
		m_LastRound->setVisible(true);
		m_LastRound->playAnimation("last_round_normal");
	}
	else if (_bigType == 2)
	{
		m_LastRound->setVisible(true);
		m_LastRound->playAnimation("last_round_big");
	}
}

void PokerTopPanel::ShowBadugiEffect(int _type)
{
	if (_type == DAY_TYPE_MORNING)
	{
		m_BadugiEffect->setVisible(true);
		m_BadugiEffect->playAnimation("morning");
	}
	else if (_type == DAY_TYPE_AFTERNOON)
	{
		m_BadugiEffect->setVisible(true);
		m_BadugiEffect->playAnimation("afternoon");
	}
	else if (_type == DAY_TYPE_NIGHT)
	{
		m_BadugiEffect->setVisible(true);
		m_BadugiEffect->playAnimation("night");
	}
}

void PokerTopPanel::TouchHiddenCardEventStart(float _delay)
{
	if (m_HiddenTouchPanel->isVisible()) {
		m_HiddenTouchPanel->getSkel("skel_hidden_card_start")->playAnimation("hidden_card_end");
		m_HiddenTouchPanel->getButton("sbtn_hiddenback")->getButtonSkelObject()->playAnimation("hiddenback_end");
		m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setEnable(false);
		m_HiddenTouchPanel->setTouchable(false);

		CCPoint _moveTo = m_posStartHiddenCard + ccp(100.f, 0.f);
		m_HiddenTouchPanel->getButton("sbtn_hiddenback")->runAction(CCSequence::create(
			CCDelayTime::create(_delay),
			CCCallFunc::create(this, callfunc_selector(PokerTopPanel::TouchHiddenCardEvent)),
			NULL));
	}
	else if (mHiddenBigTouchPanel->isVisible()) {
		mHiddenBigTouchPanel->getSkel("skel_hidden_card_start")->playAnimation("hidden_card_end");
		mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->getButtonSkelObject()->playAnimation("hiddenback_end");
		mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setEnable(false);
		mHiddenBigTouchPanel->setTouchable(false);

		CCPoint _moveTo = mBigPosStartHiddenCard + ccp(100.f, 0.f);
		mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->runAction(CCSequence::create(
			CCDelayTime::create(_delay),
			CCCallFunc::create(this, callfunc_selector(PokerTopPanel::TouchHiddenCardEvent)),
			NULL));
	}

	m_bTouchHiddenCard = false;	
}

void PokerTopPanel::TouchHiddenCardEvent()
{
	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->TouchHiddenCard();
}

void PokerTopPanel::TopButtonesEnable(bool isEnable)
{
	if (isEnable)
	{
		m_ExitBtn->setEnable(true);
		m_ExitBtn->setVisible(true);

		m_MoveBtn->setEnable(true);
		m_MoveBtn->setVisible(true);

		mExitBtnLabel->setVisible(true);
		mMoveBtnLabel->setVisible(true);

	}
	else
	{
		m_ExitBtn->setEnable(false);
		m_ExitBtn->setVisible(false);

		m_MoveBtn->setEnable(false);
		m_MoveBtn->setVisible(false);

		mExitBtnLabel->setVisible(false);
		mMoveBtnLabel->setVisible(false);
	}
}

void PokerTopPanel::TurnOnGetChip()
{
	if (!m_Chip)
		return;

	m_Chip->playAnimation("getchip_start");
	m_Chip->appendAnimation("getchip_loop");
	m_Chip->appendAnimation("getchip_end");
	m_Chip->setVisible(true);
}

void PokerTopPanel::ShowLevelUpEffect()
{
	m_LevelupEffect->setVisible(true);
	m_LevelupEffect->playAnimation("level_up", false);
}

void PokerTopPanel::ShowMadeBonusEffect()
{
	m_MadeBonusEffect->setVisible(true);
	m_MadeBonusEffect->playAnimation("made_bonus", false);
}

void PokerTopPanel::ShowAutoRefillEffect()
{
	m_AutoRefillEffect->setVisible(true);
	m_AutoRefillEffect->playAnimation("autorefill_start", false);
	m_AutoRefillEffect->appendAnimation("autorefill_loop", false);
	m_AutoRefillEffect->appendAnimation("autorefill_end", false);
}

void PokerTopPanel::SetActionFirework(int _count, float _delay)
{
	m_fireworkIndex = rand()%10;
	for (int _i = 0; _i < _count; _i++)
	{
		runAction(CCSequence::createWithTwoActions(
			CCDelayTime::create(_delay * (float)_i),
			CCCallFunc::create(this, callfunc_selector(PokerTopPanel::ActionFirework))
			));
	}
}

void PokerTopPanel::ActionFirework()
{
// 	if (m_fireworkIndex >= 10)
// 	{
// 		m_fireworkIndex -= 10;
// 	}
// 
// 	int _kind = rand() % 10;
// 	
// 	string _aniName = "fire_work" + StringConverter::toString(_kind+1);
// 	m_Firework[m_fireworkIndex]->playAnimation(_aniName);
// 	m_Firework[m_fireworkIndex]->setVisible(true);
// 	m_fireworkIndex += rand()%5;
}

void PokerTopPanel::ShowCurtainClose()
{
	/*m_FadeBlackbox->runAction(CCJumpTo::create(0.4f, ccp(DESIGN_WIDTH / 2.f, DESIGN_HEIGHT / 2.f), 100.f, 1));*/
	if (m_pCurtain)
	{
		m_pCurtain->closePanel();
	}

	m_pCurtain = nullptr;
	m_pCurtain = new TournamentWaitingPanel();
	LayerManager::getSingleton().pushDynamicLayer(m_pCurtain, DYNAMIC_PUSH_LAYER);
	m_pCurtain->setDesc(GameStringDepot::getSingleton().getString("TXT_ROOM_REARRANGE"));
}

void PokerTopPanel::ShowCurtainOpen()
{
	/*m_FadeBlackbox->runAction(CCMoveTo::create(0.4f, ccp(DESIGN_WIDTH / 2.f, DESIGN_HEIGHT * 2.f)));*/
	if (m_pCurtain)
	{
		m_pCurtain->closePanel();
	}
	m_pCurtain = nullptr;
}

void PokerTopPanel::SetCutainClose()
{
	//m_FadeBlackbox->setPosition(ccp(DESIGN_WIDTH / 2.f, DESIGN_HEIGHT / 2.f));
}

void PokerTopPanel::SetCutainOpen()
{
	//m_FadeBlackbox->setPosition(ccp(DESIGN_WIDTH / 2.f, DESIGN_HEIGHT * 2.f));
}

void PokerTopPanel::ShowLastTable()
{
	//TODO : Show LastTable Animation

	PokerBackgroundPanel* _pPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetBackgroundPanel();
	if (_pPanel)
	{
		_pPanel->SetLastTableBoard();
	}
}

void PokerTopPanel::showCharacterEffect(int characterId, bool hasMadeMoney)
{
	//내 캐릭터가 무엇인가.
	//characterId;
	string _sDesc = "";
	const W_CharacterData characterData = PokerShopHelper::getCharacterData(characterId);
	int _size = characterData.effect_size();
	int realEffectSize = 0;
	for (int _i = 0; _i < _size; _i++)
	{
		W_CharacterData_CharacterEffect _dataEff = characterData.effect(_i);
		//경험치 증가
		if (_dataEff.type() == W_CharacterData_eEffectType_ExpPerUp) {
			if (realEffectSize != 0)
				_sDesc += "\n";
			_sDesc += _dataEff.desc();
			realEffectSize++;
		}
		//무료 리필 증가
		else if (_dataEff.type() == W_CharacterData_eEffectType_DealerFeePerDown) {
			if (realEffectSize != 0)
				_sDesc += "\n";
			_sDesc += _dataEff.desc();
			realEffectSize++;
		}
		//메이드 보너스
		else if (_dataEff.type() == W_CharacterData_eEffectType_MadeBonus) {
			if (hasMadeMoney) {
				if (realEffectSize != 0)
					_sDesc += "\n";
				_sDesc += _dataEff.desc();
				realEffectSize++;
			}
		}
	}

	if (realEffectSize > 0) {
		mCharacterEffectLabel->setString(_sDesc.c_str());
		mCharacterEffectLabel->setVisible(true);

		CCFiniteTimeAction* move = CCMoveBy::create(2.f, ccp(0,62.f));
		CCFiniteTimeAction* closeAction = CCFadeTo::create(2.0f, 64);
		CCFiniteTimeAction* restoreAction = CCFadeTo::create(0.1f, 255);
		CCFiniteTimeAction* callback = CCCallFunc::create(this, callfunc_selector(PokerTopPanel::initCharacterEffect));
		CCAction* disAppearAction = CCSequence::create(move, callback, restoreAction, NULL);
		CCAction* fadeAction = CCSequence::create(closeAction, NULL);
		mCharacterEffectLabel->runAction(disAppearAction);
		mCharacterEffectLabel->runAction(fadeAction);
	}
}

void PokerTopPanel::initCharacterEffect()
{
	mCharacterEffectLabel->setVisible(false);
	mCharacterEffectLabel->setOpacity(255.f);
	mCharacterEffectLabel->setPosition(mOriginCharactgerEffectPos);
}

void PokerTopPanel::setUseRoomMoveBtn(bool use)
{
	m_MoveBtn->setVisible(false);
	m_MoveBtn->setEnable(false);
	mMoveBtnLabel->setVisible(false);
}

void PokerTopPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}