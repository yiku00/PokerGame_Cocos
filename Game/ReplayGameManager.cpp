#include "pch.h"
#include "TypeDefine.pb.h"
#include "ReplayGameManager.h"

#include "HeroUtil.h"
#include "NxUtil.h"
#include "SceneUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "NxDefine.h"
#include "FightScene.h"
#include "GamePlayData.pb.h"
#include "PlayerOutRes.pb.h"
#include "BettingSeedRes.pb.h"
#include "PokerPlayerInfoPanel.h"
#include "ShareCardInfo.pb.h"
#include "UpdatePlayerInfo.pb.h"
#include "PlayerAdditionalResultInfo.pb.h"
#include "ResultInfo.pb.h"
#include "PotMoneyPanel.h"
#include "PokerTopPanel.h"
#include "NxLayerManager.h"

template<> ReplayGameManager* Singleton<ReplayGameManager>::msSingleton = 0;


UserCommentData::UserCommentData()
{
	m_Time = 0;
	m_UID = 0;
	m_UserNickname = "";
	m_Comment = U8("");
	m_BubbleNode = nullptr;
	m_Background[0] = nullptr;
	m_Background[1] = nullptr;
	m_Background[2] = nullptr;
	//m_Icon = nullptr;
	m_IdLabel = nullptr;
	m_TextLabel = nullptr;
	m_Color = ccc4(ccBLACK.r, ccBLACK.g, ccBLACK.b, 0xFF);

	if (!LayerManager::getSingletonPtr()->hasLayer("CharacterLayer"))
		return;

	Layer* _pPanel = LayerManager::getSingletonPtr()->getLayer("CharacterLayer");
	if (_pPanel == nullptr)
		return;

	_pPanel->addChild(this, 100);
	this->release();
}

UserCommentData::UserCommentData(int64 _time, int _id, string _nick, string _text, ccColor4B _color4b)
{
	m_Time = _time;
	m_UID = _id;
	m_UserNickname = _nick;
	m_Comment = _text;
	m_BubbleNode = nullptr;
	m_Background[0] = nullptr;
	m_Background[1] = nullptr;
	m_Background[2] = nullptr;
	//m_Icon = nullptr;
	m_IdLabel = nullptr;
	m_TextLabel = nullptr;
	m_Color = _color4b;
}


UserCommentData::~UserCommentData()
{
	cleanup();
	removeFromParent();
}

void UserCommentData::ShowUserComment()
{
	if (getParent() == nullptr)
	{
		if (!LayerManager::getSingletonPtr()->hasLayer("CharacterLayer"))
			return;

		Layer* _pPanel = LayerManager::getSingletonPtr()->getLayer("CharacterLayer");
		if (_pPanel == nullptr)
			return;

		_pPanel->addChild(this, 100);
		this->release();
	}

	stopAllActions();

	m_BubbleNode = new CCNode();
	addChild(m_BubbleNode);
	m_BubbleNode->release();

	for (int _i = 0; _i < 3; _i++)
	{
		m_Background[_i] = new SkelObject();
		m_Background[_i]->setSkelAnim("ui/replaytool_8888.json");
		m_BubbleNode->addChild(m_Background[_i]);
		m_Background[_i]->release();
	}
	m_Background[0]->playAnimation("speechbubble_left");
	m_Background[1]->playAnimation("speechbubble_center");
	m_Background[2]->playAnimation("speechbubble_right");

	int _posIdx = ReplayGameManager::getSingletonPtr()->getCommentIndex() % 5;

	switch (_posIdx)
	{
	case 0:
		m_BubbleNode->setPosition(ccp(206 + rand() % 200, 155 + rand() % 50));
		break;
	case 1:
		m_BubbleNode->setPosition(ccp(206 + rand() % 200, 325 + rand() % 50));
		break;
	case 2:
		m_BubbleNode->setPosition(ccp(312 + rand() % 400, 225 + rand() % 50));
		break;
	case 3:
		m_BubbleNode->setPosition(ccp(718 + rand() % 200, 155 + rand() % 50));
		break;
	case 4:
		m_BubbleNode->setPosition(ccp(718 + rand() % 200, 325 + rand() % 50));
		break;
	}

	//m_Icon = new SkelObject();
	//m_Icon->setSkelAnim("ui/replaytool_8888.json");
	//m_Icon->setPosition(ccp(-130, 10));
	//m_Icon->playAnimation("usericon_"+StringConverter::toString(m_CharacterID+1));
	//m_Background->addChild(m_Icon);
	//m_Icon->release();

	m_IdLabel = new  Nx::Label();
	m_IdLabel->initWithString(m_UserNickname.c_str(), 15);
	m_IdLabel->setColor(ccc3(50, 50, 50));
	m_IdLabel->setPosition(ccp(-110, 10));
	m_IdLabel->setAnchorPoint(ccp(0.f, 0.5f));
	m_BubbleNode->addChild(m_IdLabel);
	m_IdLabel->release();

	m_TextLabel = new Nx::Label();
	m_TextLabel->initWithString(m_Comment.c_str(), 15);
	m_TextLabel->setColor(ccc3(50, 50, 50));
	m_TextLabel->setPosition(ccp(-130, -10));
	m_TextLabel->setAnchorPoint(ccp(0.f, 0.5f));
	m_BubbleNode->addChild(m_TextLabel);
	m_TextLabel->release();

	int _length = m_TextLabel->getContentSize().width;
	SetTextBubble(_length);
	if (m_BubbleNode->getPositionX() + (_length - 154 + 26) > DESIGN_WIDTH)
	{
		int _posX = DESIGN_WIDTH - (_length - 154 + 26);
		if (_posX < 0)
		{
			_posX = 0;
		}

		m_BubbleNode->setPositionX(_posX);
	}

	//m_Icon->setVisible(true);
	m_IdLabel->setVisible(true);
	m_TextLabel->setVisible(true);

	runAction(CCSequence::create(
		CCDelayTime::create(5.f),
		CCCallFunc::create(this, callfunc_selector(UserCommentData::CloseUserComment)),
		CCDelayTime::create(1.f),
		CCCallFunc::create(this, callfunc_selector(UserCommentData::RemoveUserComment)),
		NULL));
}

void UserCommentData::CloseUserComment()
{
	if (m_BubbleNode == nullptr)
		return;

	m_BubbleNode->setVisible(false);

	//m_Icon->setVisible(false);
	m_IdLabel->setVisible(false);
	m_TextLabel->setVisible(false);
}

void UserCommentData::RemoveUserComment()
{
	//if (m_Icon != nullptr)
	//{
	//	m_Icon->cleanup();
	//	m_Icon->removeFromParent();
	//}

	if (m_IdLabel != nullptr)
	{
		m_IdLabel->cleanup();
		m_IdLabel->removeFromParent();
	}

	if (m_TextLabel != nullptr)
	{
		m_TextLabel->cleanup();
		m_TextLabel->removeFromParent();
	}

	if (m_BubbleNode != nullptr)
	{
		m_BubbleNode->cleanup();
		m_BubbleNode->removeFromParent();
	}

	//m_Icon = nullptr;
	m_IdLabel = nullptr;
	m_TextLabel = nullptr;
	m_BubbleNode = nullptr;
}

void UserCommentData::SetTextBubble(int _size)
{
	int _length = 0;
	if (_size > 154)
	{
		_length = (_size - 154);
	}

	int _scale = (_length + 26) / 2;
	if (_scale <= 0)
	{
		_scale = 1;
	}

	m_Background[0]->setPosition(ccp(-77, 0));
	m_Background[1]->setScaleX(_scale);
	m_Background[1]->setPosition(ccp(_scale, -12));
	m_Background[2]->setPosition(ccp(4 + (_scale * 2), -12));
}

ReplayGameManager::ReplayGameManager()
{
	m_pRePlayGameData = NULL;
	m_IsReplayEnable = false;
	m_ReplayIndex = 0;
	m_ReplayIndexMax = 0;
	m_GameTime = 0;
	m_MaxTime = 0;
	m_ReplayDataReady = false;
	m_GameRoomInfo = nullptr;
	m_isPause = false;

	m_pReplayPanel = nullptr;
	m_pChatTableView = nullptr;
}

ReplayGameManager::~ReplayGameManager()
{
	//if (m_pRePlayGameData)
	//{
	//	delete m_pRePlayGameData;
	//	m_pRePlayGameData = NULL;
	//}

	//if (m_pReplayPanel)
	//{
	//	//m_pReplayPanel->destruct();
	//	m_pReplayPanel->removeFromParentAndCleanup(true);
	//	m_pReplayPanel = nullptr;
	//}

	//if (m_pChatTableView)
	//{
	//	m_pChatTableView->removeFromParentAndCleanup(true);
	//	m_pChatTableView = nullptr;
	//}
}


bool ReplayGameManager::initialize(const GamePlayData& _data)
{
	if (!_data.has_index() || !_data.has_channelid() || !_data.has_channelgrade() ||
		!_data.has_bettingrule() || !_data.has_current() || !_data.has_max() ||
		!_data.has_seedmoney() || !_data.has_gamekind() || !_data.has_masteridx() ||
		!_data.has_bossidx())
	{
		return false;
	}

	int _userCount = _data.userinfo_size();
	for (int _i = 0; _i < _userCount; _i++)
	{
		if (!_data.userinfo(_i).has_po() || !_data.userinfo(_i).has_socketid() || !_data.userinfo(_i).has_dbidx() ||
			!_data.userinfo(_i).has_dbgroup() || !_data.userinfo(_i).has_gamemoney() || !_data.userinfo(_i).has_monthlyclassid() ||
			!_data.userinfo(_i).has_monthlyclassdt() || !_data.userinfo(_i).has_vipidx())
		{
			return false;
		}
	}

	m_ReplayIndexMax = _data.gameact_size();
	for (int _i = 0; _i < m_ReplayIndexMax; _i++)
	{
		if (!_data.gameact(_i).has_gamelogkind() || !_data.gameact(_i).has_data() || !_data.gameact(_i).has_time())
		{
			return false;
		}
	}

	if (m_pRePlayGameData != NULL)
	{
		delete m_pRePlayGameData;
		m_pRePlayGameData = NULL;
	}

	m_pRePlayGameData = new GamePlayData(_data);
	
	m_ReplayIndex = 0;
	m_GameTime = 0;
	m_MaxTime = m_pRePlayGameData->gameact(m_ReplayIndexMax - 1).time() - m_pRePlayGameData->gameact(0).time();

	return true;
}

void ReplayGameManager::AddUserCommentData(int64 _time, int _id, string _nick, string _text)
{
	UserCommentData* _pCommentData = new UserCommentData(_time, _id, _nick, _text);
	m_UserCommetList.push_back(_pCommentData);
}

void ReplayGameManager::InsertUserCommentData(int64 _time, int _id, string _nick, string _text, int _index)
{
	vector<UserCommentData*>::iterator _itor = m_UserCommetList.begin();
	UserCommentData* _pCommentData = new UserCommentData(_time, _id, _nick, _text);
	
	m_UserCommetList.insert(_itor+_index, _pCommentData);
	m_UserCommentIndexMax++;
}

void ReplayGameManager::StartReplay()
{
	GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
	SceneUtil::changeScene(SceneUtil::SceneFight);
	m_ReplayDataReady = true;
	m_IsReplayEnable = false;
}

void ReplayGameManager::Update(float _dt)
{
	if (m_IsReplayEnable == false)
		return;

	int64 _mTime = 1000.f * _dt;
	m_GameTime += _mTime;

	if (m_ReplayIndex >= m_ReplayIndexMax && m_UserCommentIndex >= m_UserCommentIndexMax)
	{
		ReplayEnd();
		return;
	}

	if (m_UserCommentIndex < m_UserCommentIndexMax)
	{
		UpdateUserComment(m_GameTime);
	}

	if (m_ReplayIndex < m_ReplayIndexMax)
	{
		int64 _currentTime = m_MaxTime + m_pRePlayGameData->gameact(m_ReplayIndex).time() - m_pRePlayGameData->gameact(m_ReplayIndexMax - 1).time();
		//cout << " << act : " << StringConverter::toString(_currentTime) << " :: " << StringConverter::toString(m_GameTime) << " >>" << endl;
		if (m_GameTime >= _currentTime)
		{
			//TODO : Play Action
			ParsingLogData(m_ReplayIndex);
			m_ReplayIndex++;
		}
	}
}


void ReplayGameManager::ParsingLogData(int _idx)
{
	if (m_GameRoomInfo == nullptr)
		return;

	GameLogKind _logKind = m_pRePlayGameData->gameact(_idx).gamelogkind();
	const string _data = m_pRePlayGameData->gameact(_idx).data();

	int _size = 0;
	for (char var : _data)
	{
		_size++;
	}
	cout << _idx << " : " << _size << " ==> " << _logKind << " ----------------------------" << endl;
		
	switch (_logKind)
	{
	case STATUS_CHANGE:
	{
		PlayStatusChange _PasingData;
		_PasingData.ParseFromArray(_data.c_str(), _size);
		
		PlayStatus _status = (PlayStatus)_PasingData.playstatus();

		if (_status == PLAY_READY)
		{
			//m_isTurnLight = true;
			//m_GameRoomInfo->SetVisibleLight(false);
		}
		else if (_status == PLAY_CARD_CHOICE )
		{
			if (m_GameRoomInfo->m_DealerShoot == true)
			{
				m_GameRoomInfo->m_DealerShoot = false;
				//m_GameRoomInfo->m_pDealer->appendAnimation("dealing_ready");
				m_GameRoomInfo->m_pDealer->appendAnimation("idle", true);
				m_GameRoomInfo->m_pDealerUnder->appendAnimation("idle", true);
			}

			for (int _i = 0; _i < GAME_USER_MAX; _i++)
			{
				RoomUserData* _pUserData = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_i);
				if (_pUserData != nullptr)
				{
					if (_pUserData->GetPlayerStatus() != PLAYER_INIT)
						continue;

					if (_pUserData->m_pMyCharater != nullptr)
					{
						_pUserData->PlayThinkAnimation(5.f);
					}
					int _po = _pUserData->m_Po;
					PokerPlayerInfoCommonPanel* _pPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(_po);

					if (_pPanel) _pPanel->turnOnTimeGauge();
				}
			}

			m_GameRoomInfo->SetIsSelectedCard();
			m_GameRoomInfo->SortCard();
		}
		else if (_status == PLAY_HAZZ_UP)
		{
			m_GameRoomInfo->ShowLastLound();
		}
		else if (_status != PLAY_BETTING && _status != PLAY_JOKBO_CHOICE)
		{
			//if (m_isTurnLight == false)
			//{
			//	m_isTurnLight = true;
			//	m_GameRoomInfo->SetVisibleLight(false);
			//}
			m_GameRoomInfo->SetStatus(_status);
		}
		break;
	}		
	case PLAYER_OUT:
	{
		PlayerOutRes _PasingData;
		_PasingData.ParseFromArray(_data.c_str(), _size);

		PlayerPoInfo poInfo = _PasingData.playerpoinfo();

		PokerPlayerInfoPanel* _pPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("PlayerInfo"));
		if (_pPanel != nullptr)
		{
			m_GameRoomInfo->GetUserDataPtr(poInfo.po())->m_pMyCharater->setVisible(false);
			_pPanel->SetUserInfoPanelInit(poInfo.po());
		}
		break;
	}		
	case BETTING_SEED:
	{
		m_GameRoomInfo->SetBettingSeedMoney((char*)_data.c_str(), _size);
		break;
	}
	case CARD_CHOICE:
	{
		if (m_GameRoomInfo->m_DealerShoot == true)
		{
			m_GameRoomInfo->m_DealerShoot = false;
			//m_GameRoomInfo->m_pDealer->appendAnimation("dealing_ready");
			m_GameRoomInfo->m_pDealer->appendAnimation("idle", true);
			m_GameRoomInfo->m_pDealerUnder->appendAnimation("idle", true);
		}

		ShareCardInfo _PasingData;
		_PasingData.ParseFromArray(_data.c_str(), _size);

		RoomUserData * userData = m_GameRoomInfo->GetUserDataPtr(_PasingData.po());

		if (userData == nullptr)
			return;

		userData->ClearCardList();
		userData->PlayCharacterAnimation(IDLE);
		userData->PlayThinkAnimation(0.f, false);
		m_GameRoomInfo->GetPlayerCommonPanel(userData->m_Po)->turnOffTimeGauge();

		CardInfo cardInfo;
		for (int i = 0, j = _PasingData.cardinfo_size(); i < j; i++)
		{
			cardInfo = _PasingData.cardinfo(i);

			if (cardInfo.cardnumber() != -1)
				userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind());
		}
		break;
	}
	case BETTING:
	{
		m_GameRoomInfo->SetBettingRes((char*)_data.c_str(), _size);
		break;
	}
	case HIGHLOW_CHOICE:
	{
		m_GameRoomInfo->SetHighLow((char*)_data.c_str(), _size);
		break;
	}
	case RESULT_TO_CLIENT:
	{
		m_GameRoomInfo->SetResult((char*)_data.c_str(), _size);
		break;
	}
	case ENFORCE_EXE:
	{
		EnforceExe _PasingData;
		_PasingData.ParseFromArray(_data.c_str(), _size);
		//PASS
		break;
	}
	case SHARE_FAMILY_CARD:
	{
		m_GameRoomInfo->SetCommunityCard((char*)_data.c_str(), _size);
		//ShareCardInfo _PasingData;
		//_PasingData.ParseFromArray(_data.c_str(), _size);
		////PASS
		break;
	}
	case AFTER_RESULT_USERINFO:
	{
		UpdatePlayerInfo _PasingData;
		_PasingData.ParseFromArray(_data.c_str(), _size);
		//PASS
		break;
	}
	case ADDITIONAL_RESULT_INFO:
	{
		m_GameRoomInfo->SetAdditionalResult((char*)_data.c_str(), _size);
		break;
	}
	case SHARE_CARD:
	{
		m_GameRoomInfo->m_DealerShoot = false;
		if (m_GameRoomInfo->GetGameKind() == GAMEKIND_BADUKI || m_GameRoomInfo->GetGameKind() == GAMEKIND_HOLDEM)
		{
			m_GameRoomInfo->BadugiShareCard((char*)_data.c_str(), _size);
		}
		else
		{
			m_GameRoomInfo->AddCard((char*)_data.c_str(), _size);
		}
		break;
	}
	case SEVEN_POKER_CARD_SHOW:
	{
		if (m_GameRoomInfo->GetGameKind() == GAMEKIND_7POKER)
		{
			m_GameRoomInfo->Show7PokerPae((char*)_data.c_str(), _size);
		}
		else if (m_GameRoomInfo->GetGameKind() == GAMEKIND_BADUKI)
		{
			m_GameRoomInfo->ShowBadukiPae((char*)_data.c_str(), _size);
		}
		else if (m_GameRoomInfo->GetGameKind() == GAMEKIND_HOLDEM)
		{
			m_GameRoomInfo->ShowHoldemPae((char*)_data.c_str(), _size);
		}
		break;
	}
	case HIGHLOW_CARD_SHOW:
	{
		m_GameRoomInfo->ShowHighLowPae((char*)_data.c_str(), _size);
		break;
	}
	case CUR_BETTING_INFO:
	{
		if (m_GameRoomInfo->m_DealerShoot == true)
		{
			m_GameRoomInfo->m_DealerShoot = false;
			//m_GameRoomInfo->m_pDealer->appendAnimation("dealing_ready");
			m_GameRoomInfo->m_pDealer->appendAnimation("idle", true);
			m_GameRoomInfo->m_pDealerUnder->appendAnimation("idle", true);
		}
		m_GameRoomInfo->SetCanMyBettingKind((char*)_data.c_str(), _size);
		break;
	}
	case BETTING_STATE:
	{
		m_GameRoomInfo->SetBettingState((char*)_data.c_str(), _size);
		break;
	}
	case CHANGE_CARD_STATE:
	{
		m_GameRoomInfo->ShowBadugiSelectCard((char*)_data.c_str(), _size);
		break;
	}
	case CHANGE_CARD:
	{
		m_GameRoomInfo->ChangeBadugiSelectCard((char*)_data.c_str(), _size);
		break;
	}
	case CUR_CHANGE_CARD_INFO:
	{
		m_GameRoomInfo->ShowChangeCardSeletPanel((char*)_data.c_str(), _size);
		break;
	}
	case CHANGE_BOSS:
	{
		m_GameRoomInfo->SetChangeBoss((char*)_data.c_str(), _size);
		break;
	}
	case PLAYERS_STATUS:
	{
		m_GameRoomInfo->SetPlayersStatus((char*)_data.c_str(), _size);
		break;
	}
	case EMOTICON_ROOM:
	{
		m_GameRoomInfo->SetPlayerEmotion((char*)_data.c_str(), _size);
		break;
	}
	default:
		break;
	}
}

void ReplayGameManager::ReplayEnd()
{
	m_IsReplayEnable = false;
}

void ReplayGameManager::CloseReplay()
{
	//m_ReplayIndex = 0;
	//m_GameTime = 0;
	//m_MaxTime = 0;
	//m_ReplayDataReady = false;
	if (!m_isPause)
	{
		CCDirector::sharedDirector()->pause();
		m_isPause = true;
	}

	m_IsReplayEnable = false;

	PokerPlayerInfoPanel* _pPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("PlayerInfo"));
	if (_pPanel != nullptr)
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_TENSION, false);
		_pPanel->RemoveAllCharacter();
	}
	m_GameRoomInfo->RemoveDealer();
	m_GameRoomInfo->RemovePotMoney();
	RemoveCommentData();

	m_pChatTableView->removeFromParent();
	m_pChatTableView->release();
	m_pChatTableView = nullptr;

	GameDataManager::getSingletonPtr()->DestroyRoom();
	SoundManager::getSingletonPtr()->stopEffects();

	CSJson::Value params;
	params["REPLAY"] = true;
	SceneUtil::changeScene(SceneUtil::SceneLobby, params);	

	if (m_isPause)
	{
		CCDirector::sharedDirector()->resume();
		m_isPause = false;
	}

	if (m_pRePlayGameData)
	{
		delete m_pRePlayGameData;
		m_pRePlayGameData = NULL;
	}

}

void ReplayGameManager::MakeReplayRoom()
{
	m_isTextInput = false;
	m_bChatBoardShow = false;
	m_isTurnLight = false;

	m_GameRoomInfo = new GameRoomInfo();
	GameDataManager::getSingletonPtr()->SetGameRoomInfo(m_GameRoomInfo);

	for (int _i = 0; _i < 5; _i++)
	{
		RoomUserData* _pUserData = m_GameRoomInfo->GetUserDataPtr(_i);
		if (_pUserData == NULL)
			continue;

		_pUserData->SetPlayerStatus(PlayerStatus::PLAYER_PREPARE);
	}
	
	m_ReplayDataReady = false;
	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SetReplayData(m_pRePlayGameData);
	m_IsReplayEnable = true;

	FightScene * scene = dynamic_cast<FightScene*>(SceneManager::getSingletonPtr()->getScene(SceneUtil::SceneFight));
	if (scene != nullptr)
		scene->FirstGameStateSetting();
	
	if (!LayerManager::getSingletonPtr()->hasLayer("CharacterLayer"))
		return;
	
	Nx::Layer* _pPanel = LayerManager::getSingletonPtr()->getLayer("CharacterLayer");
	if (_pPanel == nullptr)
		return;

	PokerTopPanel* _pTopPanel = m_GameRoomInfo->GetTopPanel();
	if (_pTopPanel == nullptr)
		return;

	//make ReplayPanel
	m_pReplayPanel = new Panel();
	m_pReplayPanel->construct(getMxmlPath() + "dmy_replay_watch.mxml");
	_pPanel->addChild(m_pReplayPanel, 99);
	m_pReplayPanel->release();

	m_pChatPanel = new Panel();
	m_pChatPanel->construct(getMxmlPath() + "dmy_rpchat_board.mxml");
	_pTopPanel->addChild(m_pChatPanel, 99);
	m_pChatPanel->release();

	MakeChatRistScrollPanel();

	CCPoint _boardOrigin = m_pReplayPanel->getDummy("dmy_rpchat_board").origin;
	m_ChatBoardShowPos = ccp(_boardOrigin.x, -_boardOrigin.y);
	m_pChatPanel->setPosition(ccp(_boardOrigin.x, 25.f -_boardOrigin.y - m_pReplayPanel->getDummy("dmy_rpchat_board").size.height));
	m_ChatBoardHidePos = m_pChatPanel->getPosition();

	//set button
	m_pPlayButton = m_pReplayPanel->getButton("sbtn_play_stay");
	m_pPlayButton->setListener(_pTopPanel);
	m_pPlayButton->setEnable(true);
	m_pPlayButton->setType(Button::NoPressImg);
	m_pPlayButton->setSkelAnimation("stop_stay", false);

	m_pResetButton = m_pReplayPanel->getButton("sbtn_reset_stay");
	m_pResetButton->setListener(_pTopPanel);
	m_pResetButton->setEnable(true);
	m_pResetButton->setType(Button::NoPressImg);
	m_pResetButton->setSkelAnimation("reset_stay", false);

	m_pChatBoardButton = m_pChatPanel->getButton("sbtn_chatarrow_up");
	m_pChatBoardButton->setListener(_pTopPanel);
	m_pChatBoardButton->setEnable(true);
	m_pChatBoardButton->setType(Button::NoPressImg);
	m_pChatBoardButton->setSkelAnimation("chatarrow_up", false);

	m_pChatTextField = m_pChatPanel->getTextField("fld_chat_tcontent");
	m_pChatTextField->setListener(_pTopPanel);
	m_pChatTextField->setPlaceHolder("");
	m_pChatTextField->setString("");
	m_pChatTextField->setMultiLineEnabled(false);

	if (ReplayGameManager::getSingletonPtr()->GetIsPublish() == true)
	{
		m_pChattButton = m_pReplayPanel->getButton("sbtn_chat_stay");
		m_pChattButton->setListener(_pTopPanel);
		m_pChattButton->setEnable(true);
		m_pChattButton->setType(Button::NoPressImg);
		m_pChattButton->setSkelAnimation("chat_stay", false);

		m_pRecommendButton = m_pReplayPanel->getButton("sbtn_recommend_stay");
		m_pRecommendButton->setListener(_pTopPanel);
		m_pRecommendButton->setEnable(true);
		m_pRecommendButton->setType(Button::NoPressImg);
		m_pRecommendButton->setSkelAnimation("recommend_stay", false);
	}
	else
	{
		m_pReplayPanel->getButton("sbtn_chat_stay")->setVisible(false);
		m_pReplayPanel->getButton("sbtn_chat_stay")->setEnable(false);

		m_pReplayPanel->getButton("sbtn_recommend_stay")->setVisible(false);
		m_pReplayPanel->getButton("sbtn_recommend_stay")->setEnable(false);

		m_pChatBoardButton->setVisible(false);
		m_pChatBoardButton->setEnable(false);
		m_pChatTextField->setVisible(false);
	}

	
	
	
	m_pChatPanel->getTextField("fld_chat_content")->setString("");
	m_pChatPanel->getTextField("fld_chat_content")->setPlaceHolder("");
	m_pChatPanel->getTextField("fld_chat_content")->setVisible(false);


	//{
	//	m_pPlayButton = new Button("play_replay", Button::ButtonType::NoPressImg);
	//	m_pPlayButton->setSkel("ui/replaytool_8888", "stop_stay", CCSize(42, 41));
	//	m_pPlayButton->setPosition(ccp(512, 25));
	//	_pPanel->addChild(m_pPlayButton, 99);
	//	m_pPlayButton->release();
	//	m_pPlayButton->setListener(_pTopPanel);
	//	m_pPlayButton->setEnable(true);
	//	m_pPlayButton->setSkelAnimation("stop_stay", false);

	//	m_pResetButton = new Button("reset_replay", Button::ButtonType::NoPressImg);
	//	m_pResetButton->setSkel("ui/replaytool_8888", "reset_stay", CCSize(42, 41));
	//	m_pResetButton->setPosition(ccp(512 + 84, 25));
	//	_pPanel->addChild(m_pResetButton, 99);
	//	m_pResetButton->release();
	//	m_pResetButton->setListener(_pTopPanel);
	//	m_pResetButton->setEnable(true);
	//	m_pResetButton->setSkelAnimation("reset_stay", false);

	//	m_pChattButton = new Button("chat_replay", Button::ButtonType::NoPressImg);
	//	m_pChattButton->setSkel("ui/replaytool_8888", "chat_stay", CCSize(42, 41));
	//	m_pChattButton->setPosition(ccp(512 - 84, 25));
	//	_pPanel->addChild(m_pChattButton, 99);
	//	m_pChattButton->release();
	//	m_pChattButton->setListener(_pTopPanel);
	//	m_pChattButton->setEnable(true);
	//	m_pChattButton->setSkelAnimation("chat_stay", false);

	//	m_pButtonBack = new SkelObject();
	//	m_pButtonBack->setSkelAnim("ui/replaytool_8888.json");
	//	m_pButtonBack->setPosition(ccp(512, 13));
	//	m_pButtonBack->playAnimation("buttonback");
	//	_pPanel->addChild(m_pButtonBack, 99);
	//}

	//UserComment
	m_UserCommentIndex = 0;
	m_UserCommentIndexMax = m_UserCommetList.size();
}

void ReplayGameManager::ResetTextField()
{
	m_isTextInput = false;
	m_pChatTextField->setString("");
	m_pChatTextField->detachWithIME();
}

void ReplayGameManager::ReplayResume()
{
	if (m_isPause)
	{
		m_pPlayButton->setSkelAnimation("stop_stay");
		CCDirector::sharedDirector()->resume();
		m_isPause = false;
	}
}

void ReplayGameManager::ReplayPause()
{
	if (m_isPause)
	{
		m_pPlayButton->setSkelAnimation("stop_stay");
		CCDirector::sharedDirector()->resume();
		m_isPause = false;
	}
	else
	{
		m_pPlayButton->setSkelAnimation("play_stay");
		CCDirector::sharedDirector()->pause();
		m_isPause = true;
	}
}

void ReplayGameManager::ReplayReset()
{
	if (m_isPause == false)
	{
		m_pPlayButton->setSkelAnimation("play_stay");
		CCDirector::sharedDirector()->pause();
		m_isPause = true;
	}

	PotMoneyPanel* _potMoneyPanel = dynamic_cast<PotMoneyPanel*>(LayerManager::getSingletonPtr()->getLayer("PotMoney"));
	if (_potMoneyPanel)
	{
		_potMoneyPanel->ClearPotMoney();
	}

	if (LayerManager::getSingleton().hasLayer("JackpotPanel"))
	{
		if (LayerManager::getSingleton().getLayer("JackpotPanel"))
		{
			LayerManager::getSingleton().getLayer("JackpotPanel")->setVisible(false);
		}
	}

	m_GameRoomInfo->InitGame();

	m_ReplayIndex = 0;
	m_UserCommentIndex = 0;
	m_GameTime = 0;
	m_GameRoomInfo->ResetReplayData(m_pRePlayGameData);
	ResetUserComment();
	m_IsReplayEnable = true;

	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		RoomUserData* _pUserData = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_i);
		if (_pUserData != nullptr)
		{
			if (_pUserData->m_pMyCharater != nullptr)
			{
				_pUserData->m_pMyCharater->setVisible(true);
				_pUserData->PlayCharacterAnimation(IDLE);
			}
			int _po = _pUserData->m_Po;
			PokerPlayerInfoCommonPanel* _pPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(_po);

			if (_pPanel) {
				_pPanel->turnOffTimeGauge();
				_pPanel->setGameStartPlayerInfo();
				_pPanel->turnOnUserInfoBack();
			}
		}
	}

	//족보 초기화
	if (m_GameRoomInfo->GetGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		m_GameRoomInfo->SetMyBadugiJokbo(LowJokboKind::LOW_NO);
	}
	else
	{
		m_GameRoomInfo->SetMyHighJokbo(HighJokboKind::HIGH_NO);
		if (m_GameRoomInfo->GetGameKind() == GameKind::GAMEKIND_HIGH_LOW)
			m_GameRoomInfo->SetMyLowJokbo(LowJokboKind::LOW_NO);
	}
}

void ReplayGameManager::UpdateUserComment(int64 _time)
{
	if (m_UserCommentIndexMax <= m_UserCommentIndex)
	{
		return;
	}

	int64 _currentTime = m_UserCommetList[m_UserCommentIndex]->m_Time;
	if (m_GameTime >= _currentTime)
	{
		//TODO : 게임에서 적용해야함.
		//if (m_pChatTableView)
		//{
		//	if (m_UserCommentIndex - 1 >= 0)
		//	{
		//		m_pChatTableView->SetColorAtIndex(m_UserCommentIndex - 1, ccc4(ccWHITE.r, ccWHITE.g, ccWHITE.b, 0xFF));
		//	}
		//	m_pChatTableView->SetColorAtIndex(m_UserCommentIndex, ccc4(ccGREEN.r, ccGREEN.g, ccGREEN.b, 0xFF));
		//}

		m_UserCommetList[m_UserCommentIndex]->ShowUserComment();
		m_UserCommentIndex++;
	}
}

void ReplayGameManager::RemoveCommentData()
{
	UserCommentData* _pData;
	while (!m_UserCommetList.empty())
	{
		_pData = *(m_UserCommetList.begin());
		_pData->RemoveUserComment();
		_pData->removeFromParent();
		m_UserCommetList.erase(m_UserCommetList.begin());
	}
	m_UserCommetList.clear();
}

void ReplayGameManager::ResetUserComment()
{
	for (UserCommentData* _pData : m_UserCommetList)
	{
		_pData->RemoveUserComment();
	}
}

void ReplayGameManager::ClickBoardSetButton()
{
	if (m_bChatBoardShow == true)
	{
		m_bChatBoardShow = false;
		m_pChatBoardButton->setSkelAnimation("chatarrow_up", false);
		m_pChatPanel->setPosition(m_ChatBoardHidePos);
	}
	else
	{
		m_bChatBoardShow = true;
		m_pChatBoardButton->setSkelAnimation("chatarrow_down", false);
		m_pChatPanel->setPosition(m_ChatBoardShowPos);
	}
}


void ReplayGameManager::MakeChatRistScrollPanel()
{
	//int _size = m_UserCommetList.size();
	//m_UserCommetList.reserve(_size);
	//string _name = "";
	//string _text = "";	
	//for (int _i = 0; _i < _size; _i++)
	//{
	//	_name += m_UserCommetList[_i]->m_UserNickname + ">";
	//	_name += "[nl]";
	//	_text += m_UserCommetList[_i]->m_Comment;
	//	_text += "[nl]";
	//}

	if (m_pChatTableView)
	{
		m_pChatTableView->removeFromParent();
		m_pChatTableView = nullptr;
	}

	//m_pChatTableView = CustomTextView::create(_name, _text, CHAT_BOARD_SIZE, 14);
	m_pChatTableView = CustomTextView::create(CHAT_BOARD_SIZE, 14);
	m_pChatTableView->setPosition(ccp(20, 50));
	m_pChatPanel->addChild(m_pChatTableView);
	//m_pChatTableView->release();
}

void ReplayGameManager::InputChat()
{
	if (m_isTextInput)
		return;

	m_bChatBoardShow = true;
	m_pChatBoardButton->setSkelAnimation("chatarrow_down", false);
	m_pChatPanel->setPosition(m_ChatBoardShowPos);

	m_isTextInput = true;
	if (!m_isPause)
	{
		m_pPlayButton->setSkelAnimation("play_stay");
		CCDirector::sharedDirector()->pause();
		m_isPause = true;
	}
	m_pChatTextField->setString("");
	m_pChatTextField->attachWithIME();
}

void ReplayGameManager::SendCommentData()
{
	m_isTextInput = false;

	int64 _seq = GetReplaySeq();
	int64 _time = GetGameTime();
	string _chatText = m_pChatTextField->getString();
	
	if (_chatText == "")
		return;

	int isCheck = GameDataManager::getSingletonPtr()->CheckNickname(_chatText, 20);

	string msgText;
	SimplePopupPanel* _pPopup = nullptr;
	bool _isError = false;
	switch (isCheck)
	{
	case NCE_SUCCESS:
	{
		WebService::getSingletonPtr()->_sendReplayCommentReq(ReplayGameManager::getSingletonPtr()->GetType(), _seq, _time, _chatText);

		m_bChatBoardShow = false;
		m_pChatBoardButton->setSkelAnimation("chatarrow_up", false);
		m_pChatPanel->setPosition(m_ChatBoardHidePos);

		m_pChatTextField->setString("");

		if (m_isPause)
		{
			m_pPlayButton->setSkelAnimation("stop_stay");
			CCDirector::sharedDirector()->resume();
			m_isPause = false;
		}
		break;
	}
	case NCE_LENGTH_ERROR:
		_isError = true;
		msgText = GameStringDepot::getSingleton().getString("TXT_CHATMSG_LENGTH_ERROR");
		break;
	case NCE_SPECIAL_LETTER_ERROR:
		_isError = true;
		msgText = GameStringDepot::getSingleton().getString("TXT_NICKNAME_SPECIAL_LETTER_ERROR");
		break;
	case NCE_SPACE_ERROR:
		_isError = true;
		msgText = GameStringDepot::getSingleton().getString("TXT_NICKNAME_SPACE_LETTER_ERROR");
		break;
	}

	if (_isError)
	{
		_pPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText);
		string _okMsg = "CHAT_ERROR_PROCESS";
		_pPopup->SetOkEventMsg(_okMsg);
		_pPopup->setListener(this);
		LayerManager::getSingleton().pushDynamicLayer(_pPopup, DYNAMIC_PUSH_LAYER);
		if (m_isPause)
		{
			m_pPlayButton->setSkelAnimation("stop_stay");
			CCDirector::sharedDirector()->resume();
			m_isPause = false;
		}
	}
	
}

std::string ReplayGameManager::GetCommentData(int _idx, int _type)
{
	if (m_UserCommetList.size() <= _idx)
		return "";

	switch (_type)
	{
	case COMMENT_NAME:
		return m_UserCommetList[_idx]->m_UserNickname;
		break;
	case COMMENT_TEXT:
		return m_UserCommetList[_idx]->m_Comment;
		break;
	}
	return "";
}

ccColor4B ReplayGameManager::GetCommentColor(int _idx)
{
	if (m_UserCommetList.size() <= _idx)
		return ccc4(ccWHITE.r, ccWHITE.g, ccWHITE.b, 0XFF);

	return m_UserCommetList[_idx]->m_Color;
}

void ReplayGameManager::onLayerMessage(const string& msg)
{
	if (msg == "CHAT_ERROR_PROCESS")
	{
		if (!m_isPause)
		{
			m_pPlayButton->setSkelAnimation("play_stay");
			CCDirector::sharedDirector()->pause();
			m_isPause = true;
		}

		m_pChatTextField->attachWithIME();
	}
}
