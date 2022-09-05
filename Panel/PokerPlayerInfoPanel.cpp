#include "pch.h"
#include "PokerPlayerInfoPanel.h"
#include "PokerPlayerInfoMyPanel.h"
#include "PokerPlayerInfoRightPanel.h"
#include "PokerPlayerInfoLeftPanel.h"
#include "PokerPlayerInfoCommonPanel.h"
#include "RefDefine.h"
#include "HeroUtil.h"

#include "GameDataManager.h"
#include "PokerTopPanel.h"
#include "PokerEmotionPanel.h"
#include "PokerUserInfoPanel.h"
#include "PokerResourceHelper.h"

PokerPlayerInfoPanel::PokerPlayerInfoPanel()
{
	_initData();
	drawPlayerInfo();
}

PokerPlayerInfoPanel::~PokerPlayerInfoPanel()
{
	removeAllChildren();
}

void PokerPlayerInfoPanel::initPanel()
{

}

void PokerPlayerInfoPanel::drawPlayerInfo()
{
	_setParentPanel();

	addMyPanel();	
	addLeftOnePanel();
	addLeftTwoPanel();
	addRigthOnePanel();
	addRigthTwoPanel();

	//_collectPlayerInfos();
}

void PokerPlayerInfoPanel::SetPlayerPanel()
{
	GameRoomInfo* _pRoomInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		int _UserIdx = GameDataManager::getSingletonPtr()->ClientToServerIndex(_i);	// 서버 인덱스
		if (_pRoomInfo->m_UserList[_UserIdx] == nullptr)
		{
			RemoveCharacter(_UserIdx);
			SetUserInfoPanelInit(_UserIdx);
		}
		else
		{
			int _CharacterId = _pRoomInfo->m_UserList[_UserIdx]->m_pPlayerData->m_CharacterIdx;
			SetCharacter(_UserIdx, _CharacterId, true);
			SetUserInfoPanelUpdate(_UserIdx, _pRoomInfo->m_UserList[_UserIdx]);
		}
	}
}

void PokerPlayerInfoPanel::SetAllUserGameStartPlayerInfo()
{
	GameRoomInfo* _pRoomInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		int _UserIdx = GameDataManager::getSingletonPtr()->ServerToClientIndex(_i);
		if (_pRoomInfo->m_UserList[_i] == nullptr)
			continue;
		else
		{
			_pRoomInfo->m_UserList[_i]->PlayCharacterAnimation(IDLE);
			PokerPlayerInfoCommonPanel * _panel = GetPlayerCommonPanel(_i);

			if (_panel != nullptr)
			{
				_panel->SetBetting(BETTING_NO, false, 0);
				_panel->setGameStartPlayerInfo();
				_panel->EndWinnerText();
			}
		}
	}
}


void PokerPlayerInfoPanel::SetAllUserBettingAmountInit()
{
	GameRoomInfo* _pRoomInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		int _UserIdx = GameDataManager::getSingletonPtr()->ServerToClientIndex(_i);
		if (_pRoomInfo->m_UserList[_i] == nullptr)
			continue;
		else
		{
			PokerPlayerInfoCommonPanel * _panel = GetPlayerCommonPanel(_i);

			if (_panel != nullptr)
				_panel->ClearBettingAmount();
		}
	}
}

void PokerPlayerInfoPanel::SetUserInfoPanelUpdate(int po, RoomUserData * data)
{
	PokerPlayerInfoCommonPanel * _panel = GetPlayerCommonPanel(po);

	if (_panel != nullptr)
	{
		_panel->turnOnUserInfoBack();
		_panel->SetBasicInfo(data->m_pPlayerData);
		if (data->m_State == PlayerStatus::PLAYER_SEE)
			_panel->turnOnWaitMark(PokerPlayerInfoCommonPanel::UserLoadKind::USER_LOAD_WAIT);
		else if (data->m_State == PlayerStatus::PLAYER_PREPARE)
			_panel->turnOnWaitMark(PokerPlayerInfoCommonPanel::UserLoadKind::USER_LOAD_ENTER);
		else
			_panel->turnOffWaitMark();
	}
}

void PokerPlayerInfoPanel::SetUserInfoPanelInit(int po)
{
	PokerPlayerInfoCommonPanel * _panel = GetPlayerCommonPanel(po);

	if (_panel != nullptr)
		_panel->setEmptyPlayerInfo();
}

void PokerPlayerInfoPanel::addMyPanel()
{
	if (mParentPanel) {
		mPlayerInfoPanelMy = new PokerPlayerInfoMyPanel();
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
		{
			mPlayerInfoPanelMy->setPosition(mParentPanel->getImage("dmy_my_texasholdempanel")->getPosition());
		}
		else
		{
			mPlayerInfoPanelMy->setPosition(mParentPanel->getImage("dmy_my_panel")->getPosition());
		}
		addChild(mPlayerInfoPanelMy);
		mPlayerInfoPanelMy->release();
		mPlayerInfoPanelMy->InitRoomManager(false);

		if (!LayerManager::getSingleton().hasLayer("TopLayer"))
			return;

		PokerTopPanel* _pPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetTopPanel();
		
		if (_pPanel)
		{
			mPlayerInfoPanelMy->m_pUserPanelBtn->setListener(_pPanel);

			mPlayerInfoPanelMy->m_pUserInfoPanel = new PokerUserInfoPanel(PANEL_TYPE_MY);
			_pPanel->addChild(mPlayerInfoPanelMy->m_pUserInfoPanel);
			mPlayerInfoPanelMy->m_pUserInfoPanel->release();

			//개발해야 할 부분
			//visible 은 하는데 true 는 없다..
			mPlayerInfoPanelMy->m_pUserInfoPanel->setVisible(false);			
		}
	}
}
void PokerPlayerInfoPanel::addLeftOnePanel()
{
	if (mParentPanel) {
		mPlayerLeftPanelOne = new PokerPlayerInfoLeftPanel();
		
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
			mPlayerLeftPanelOne->setPosition(mParentPanel->getImage("dmy_leftuser_texasholdempanel2")->getPosition());
		else
			mPlayerLeftPanelOne->setPosition(mParentPanel->getImage("dmy_leftuser_panel2")->getPosition());

		addChild(mPlayerLeftPanelOne);
		mPlayerLeftPanelOne->release();
		mPlayerLeftPanelOne->InitRoomManager(false);

		if (!LayerManager::getSingleton().hasLayer("TopLayer"))
			return;

		PokerTopPanel* _pTopPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetTopPanel();
			
		mPlayerLeftPanelOne->m_pUserPanelBtn->setListener(_pTopPanel);
		mPlayerLeftPanelOne->m_pUserPanelBtn->setName("LeftOnePlayerInfo_Btn");
		mPlayerLeftPanelOne->m_pUserPanelBtn->setPaused(true);

		Panel* _pPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("TopLayer"));

		if (_pPanel)
		{
//			개발해야 할 부분
// 			PokerEmotionPanel* _pEmotiBlock = new PokerEmotionPanel(PANEL_TYPE_LEFT_ONE);
// 			mPlayerLeftPanelOne->m_pEmotionPanel = _pEmotiBlock;
// 			_pPanel->addChild(_pEmotiBlock);
// 			_pEmotiBlock->release();
//			_pEmotiBlock->setVisible(false);
			PokerUserInfoPanel* _pinfoPanel = new PokerUserInfoPanel(PANEL_TYPE_LEFT_ONE);
			mPlayerLeftPanelOne->m_pUserInfoPanel = _pinfoPanel;
			_pPanel->addChild(_pinfoPanel);
			_pinfoPanel->release();
			_pinfoPanel->setActivatePanel(false);
		}
	}
}
void PokerPlayerInfoPanel::addLeftTwoPanel()
{
	if (mParentPanel) {
		mPlayerLeftPanelTwo = new PokerPlayerInfoLeftPanel();
		
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
			mPlayerLeftPanelTwo->setPosition(mParentPanel->getImage("dmy_leftuser_texasholdempanel1")->getPosition());
		else
			mPlayerLeftPanelTwo->setPosition(mParentPanel->getImage("dmy_leftuser_panel1")->getPosition());

		addChild(mPlayerLeftPanelTwo);
		mPlayerLeftPanelTwo->release();
		mPlayerLeftPanelTwo->InitRoomManager(true);

		if (!LayerManager::getSingleton().hasLayer("TopLayer"))
			return;

		mPlayerLeftPanelTwo->m_pUserPanelBtn->setName("LeftTwoPlayerInfo_Btn");
		mPlayerLeftPanelTwo->m_pUserPanelBtn->setPaused(true);
		PokerTopPanel* _pTopPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetTopPanel();
		mPlayerLeftPanelTwo->m_pUserPanelBtn->setListener(_pTopPanel);


		Panel* _pPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("TopLayer"));

		if (_pPanel)
		{
//			개발해야 할 부분
// 			PokerEmotionPanel* _pEmotiBlock = new PokerEmotionPanel(PANEL_TYPE_LEFT_TWO);
// 			mPlayerLeftPanelTwo->m_pEmotionPanel = _pEmotiBlock;
// 			_pPanel->addChild(_pEmotiBlock);
// 			_pEmotiBlock->release();
			//_pEmotiBlock->setVisible(false);

			PokerUserInfoPanel* _pinfoPanel = new PokerUserInfoPanel(PANEL_TYPE_LEFT_TWO);
			mPlayerLeftPanelTwo->m_pUserInfoPanel = _pinfoPanel;
			_pPanel->addChild(_pinfoPanel);
			_pinfoPanel->release();
			
			
			_pinfoPanel->setActivatePanel(false);

		}
	}
}

void PokerPlayerInfoPanel::addRigthOnePanel()
{
	if (mParentPanel) {
		mPlayerRightPanelOne = new PokerPlayerInfoRightPanel();
		
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
			mPlayerRightPanelOne->setPosition(mParentPanel->getImage("dmy_rightuser_texasholdempanel2")->getPosition());
		else
			mPlayerRightPanelOne->setPosition(mParentPanel->getImage("dmy_rightuser_panel2")->getPosition());

		addChild(mPlayerRightPanelOne);
		mPlayerRightPanelOne->release();
		mPlayerRightPanelOne->InitRoomManager(false);

		if (!LayerManager::getSingleton().hasLayer("TopLayer"))
			return;

		mPlayerRightPanelOne->m_pUserPanelBtn->setName("RightOnePlayerInfo_Btn");
		mPlayerRightPanelOne->m_pUserPanelBtn->setPaused(true);
		PokerTopPanel* _pTopPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetTopPanel();
		mPlayerRightPanelOne->m_pUserPanelBtn->setListener(_pTopPanel);

		Panel* _pPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("TopLayer"));

		if (_pPanel)
		{
			//개발해야할 부분
// 			PokerEmotionPanel* _pEmotiBlock = new PokerEmotionPanel(PANEL_TYPE_RIGHT_ONE);
// 			mPlayerRightPanelOne->m_pEmotionPanel = _pEmotiBlock;
// 			_pPanel->addChild(_pEmotiBlock);
// 			_pEmotiBlock->release();
			//_pEmotiBlock->setVisible(false);

			PokerUserInfoPanel* _pinfoPanel = new PokerUserInfoPanel(PANEL_TYPE_RIGHT_ONE);
			mPlayerRightPanelOne->m_pUserInfoPanel = _pinfoPanel;
			_pPanel->addChild(_pinfoPanel);
			_pinfoPanel->release();			
			_pinfoPanel->setActivatePanel(false);
		}
		
	}
}
void PokerPlayerInfoPanel::addRigthTwoPanel()
{
	if (mParentPanel) {
		mPlayerRightPanelTwo = new PokerPlayerInfoRightPanel();

		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
			mPlayerRightPanelTwo->setPosition(mParentPanel->getImage("dmy_rightuser_texasholdempanel1")->getPosition());
		else
			mPlayerRightPanelTwo->setPosition(mParentPanel->getImage("dmy_rightuser_panel1")->getPosition());

		addChild(mPlayerRightPanelTwo);
		mPlayerRightPanelTwo->release();
		mPlayerRightPanelTwo->InitRoomManager(true);

		if (!LayerManager::getSingleton().hasLayer("TopLayer"))
			return;

		mPlayerRightPanelTwo->m_pUserPanelBtn->setName("RightTwoPlayerInfo_Btn");
		mPlayerRightPanelTwo->m_pUserPanelBtn->setPaused(true);
		PokerTopPanel* _pTopPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetTopPanel();
		mPlayerRightPanelTwo->m_pUserPanelBtn->setListener(_pTopPanel);
		
		Panel* _pPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("TopLayer"));

		if (_pPanel)
		{
			//개발해야할 부분
// 			PokerEmotionPanel* _pEmotiBlock = new PokerEmotionPanel(PANEL_TYPE_RIGHT_TWO);
// 			mPlayerRightPanelTwo->m_pEmotionPanel = _pEmotiBlock;
// 			_pPanel->addChild(_pEmotiBlock);
// 			_pEmotiBlock->release();
//			_pEmotiBlock->setVisible(false);

			PokerUserInfoPanel* _pinfoPanel = new PokerUserInfoPanel(PANEL_TYPE_RIGHT_TWO);
			mPlayerRightPanelTwo->m_pUserInfoPanel = _pinfoPanel;
			_pPanel->addChild(_pinfoPanel);
			_pinfoPanel->release();
			_pinfoPanel->setActivatePanel(false);
		}
	}
}

void PokerPlayerInfoPanel::ShowPlayerPanel(int _index, bool _visible)
{
	switch (_index)
	{
	case 0:
		mPlayerInfoPanelMy->setVisible(_visible);
		break;
	case 1:
		mPlayerLeftPanelTwo->setVisible(_visible);
		break;
	case 2:
		mPlayerLeftPanelOne->setVisible(_visible);
		break;
	case 3:
		mPlayerRightPanelOne->setVisible(_visible);
		break;
	case 4:
		mPlayerRightPanelTwo->setVisible(_visible);
		break;
	default:
		break;
	}
}

void PokerPlayerInfoPanel::SetCharacter(int _index, int _charaId, bool _visible)
{
	RemoveCharacter(_index);

	if (_visible == false)
		return;

	int _clientIndex = GameDataManager::getSingletonPtr()->ServerToClientIndex(_index);

	if (m_pCharacter[_clientIndex] == nullptr)
	{ 
		m_pCharacter[_clientIndex] = new SkelObject();
	}

	if (m_pCharacterUnder[_clientIndex] == nullptr)
	{
		m_pCharacterUnder[_clientIndex] = new SkelObject();
	}
	
	m_pCharacter[_clientIndex]->setSkelAnim(PokerResourceHelper::getCharacterOverSpineName(_charaId));
	m_pCharacterUnder[_clientIndex]->setSkelAnim(PokerResourceHelper::getCharacterUnderSpineName(_charaId));	
	if (m_pCharacter[_clientIndex] == nullptr && m_pCharacterUnder[_clientIndex] == nullptr)
		return;

	int _BubbleIndex = 0;
	int _characterZoder = -1;
	string _dmyName = "";

	switch (_clientIndex)
	{
	case 0:
		_BubbleIndex = 1;
		_dmyName = "dmy_character" + StringConverter::toString(1);
		m_pCharacter[_clientIndex]->setFlipX(false);

		m_pCharacter[_clientIndex]->setZOrder(3);
		m_pCharacter[_clientIndex]->setScale(0.89f);

		m_pCharacterUnder[_clientIndex]->setFlipX(false);

		m_pCharacterUnder[_clientIndex]->setZOrder(3);
		m_pCharacterUnder[_clientIndex]->setScale(0.89f);
		_characterZoder = 1;
		break;
	case 1:
		_BubbleIndex = 3;
		_dmyName = "dmy_character" + StringConverter::toString(2);
		m_pCharacter[_clientIndex]->setFlipX(false);

		m_pCharacter[_clientIndex]->setZOrder(2);
		m_pCharacter[_clientIndex]->setScale(0.8f);

		m_pCharacterUnder[_clientIndex]->setFlipX(false);

		m_pCharacterUnder[_clientIndex]->setZOrder(2);
		m_pCharacterUnder[_clientIndex]->setScale(0.8f);
		break;
	case 2:
		_BubbleIndex = 5;
		_dmyName = "dmy_character" + StringConverter::toString(4);
		m_pCharacter[_clientIndex]->setFlipX(false);

		m_pCharacter[_clientIndex]->setZOrder(1);
		m_pCharacter[_clientIndex]->setScale(0.75f);

		m_pCharacterUnder[_clientIndex]->setFlipX(false);

		m_pCharacterUnder[_clientIndex]->setZOrder(1);
		m_pCharacterUnder[_clientIndex]->setScale(0.75f);
		break;
	case 3:
		_BubbleIndex = 4;
		_dmyName = "dmy_character" + StringConverter::toString(5);
		m_pCharacter[_clientIndex]->setFlipX(true);

		m_pCharacter[_clientIndex]->setZOrder(1);
		m_pCharacter[_clientIndex]->setScale(0.75f);

		m_pCharacterUnder[_clientIndex]->setFlipX(true);

		m_pCharacterUnder[_clientIndex]->setZOrder(1);
		m_pCharacterUnder[_clientIndex]->setScale(0.75f);
		break;
	case 4:
		_BubbleIndex = 2;
		_dmyName = "dmy_character" + StringConverter::toString(3);
		m_pCharacter[_clientIndex]->setFlipX(true);

		m_pCharacter[_clientIndex]->setZOrder(2);
		m_pCharacter[_clientIndex]->setScale(0.8f);

		m_pCharacterUnder[_clientIndex]->setFlipX(true);

		m_pCharacterUnder[_clientIndex]->setZOrder(2);
		m_pCharacterUnder[_clientIndex]->setScale(0.8f);
		break;
	default:
		break;
	}
	//CCRect _CharaRect = mParentPanel->getDummy(_dmyName);

	

	m_pCharacterUnder[_clientIndex]->setPosition(mParentPanel->getImage(_dmyName)->getPosition());
	m_pCharacterUnder[_clientIndex]->playAnimation("idle", true);
	LayerManager::getSingletonPtr()->getLayer("Background")->addChild(m_pCharacterUnder[_clientIndex], _characterZoder);
	m_pCharacterUnder[_clientIndex]->release();
	m_pCharacterUnder[_clientIndex]->setVisible(_visible);

	m_pCharacter[_clientIndex]->setPosition(mParentPanel->getImage(_dmyName)->getPosition());
	m_pCharacter[_clientIndex]->playAnimation("idle", true);
	LayerManager::getSingletonPtr()->getLayer("CharacterLayer")->addChild(m_pCharacter[_clientIndex]);
	m_pCharacter[_clientIndex]->release();
	m_pCharacter[_clientIndex]->setVisible(_visible);

	//EmotiBubble
	string _emotiDmyName = "dmy_emoticon_bubblel" + StringConverter::toString(_BubbleIndex);
	m_pEmotiBubble[_clientIndex] = new Panel();
	m_pEmotiBubble[_clientIndex]->construct(getMxmlPath() + "dmy_emoticon_bubblel.mxml");
	m_pEmotiBubble[_clientIndex]->setTouchable(false);
	LayerManager::getSingletonPtr()->getLayer("CharacterLayer")->addChild(m_pEmotiBubble[_clientIndex], 5);
	m_pEmotiBubble[_clientIndex]->release();
	m_pEmotiBubble[_clientIndex]->getLabel("txt_emoticon_dialogue")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	if (_clientIndex == 1 || _clientIndex == 2)
	{
		m_pEmotiBubble[_clientIndex]->getSkel("skel_emoticon_bubblel")->setFlipX(true);
	}
	else
	{
		m_pEmotiBubble[_clientIndex]->getSkel("skel_emoticon_bubblel")->setFlipX(false);
	}
	m_pEmotiBubble[_clientIndex]->setPosition(mParentPanel->getImage(_emotiDmyName)->getPosition() - ccp(50.f, 550.f));
	m_pEmotiBubble[_clientIndex]->getSkel("skel_emoticon_bubblel")->playAnimation("emoticon_bubblel_stay");
	m_pEmotiBubble[_clientIndex]->setVisible(false);

	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_UserList[_index]->SetCharacterPtr(m_pCharacter[_clientIndex], m_pCharacterUnder[_clientIndex], m_pEmotiBubble[_clientIndex]);
}

Panel* PokerPlayerInfoPanel::GetPlayTextBubblePanel(int _po)
{
	int _clientIndex = GameDataManager::getSingletonPtr()->ServerToClientIndex(_po);
	return m_pEmotiBubble[_clientIndex];
}

void PokerPlayerInfoPanel::HideTextBubblePanel(int _po)
{
	Panel* _pPanel = GetPlayTextBubblePanel(_po);
	_pPanel->runAction(CCSequence::create(
		CCDelayTime::create(1.5f),
		CCCallFuncN::create(_pPanel, callfuncN_selector(PokerPlayerInfoPanel::HideTextBubble)),
		NULL));
}

void PokerPlayerInfoPanel::HideTextBubble(CCNode* _node)
{
	Panel* _pTextBubble = dynamic_cast<Panel*>(_node);

	if (_pTextBubble == nullptr)
		return;

	_pTextBubble->getLabel("txt_emoticon_dialogue")->runAction(CCFadeOut::create(0.1f));
	_pTextBubble->getSkel("skel_emoticon_bubblel")->playAnimation("emoticon_bubblel_end");
}

void PokerPlayerInfoPanel::RemoveCharacter(int _index)
{
	int _clientIndex = GameDataManager::getSingletonPtr()->ServerToClientIndex(_index);
	RoomUserData* _pListenr = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_index);

	if (_pListenr == NULL)
		return;

	if (m_pCharacter[_clientIndex] != nullptr)
	{
		//m_pCharacter[_clientIndex]->cleanup();
		m_pCharacter[_clientIndex]->setListener(nullptr);
		if (_pListenr)
		{
			if (m_pCharacter[_clientIndex]->hasEventListener(_pListenr))
			{
				m_pCharacter[_clientIndex]->subEventListener(_pListenr);
			}
		}

		m_pCharacter[_clientIndex]->removeFromParentAndCleanup(true);
	}
	m_pCharacter[_clientIndex] = nullptr;

	if (m_pCharacterUnder[_clientIndex] != nullptr)
	{
		//m_pCharacterUnder[_clientIndex]->cleanup();
		m_pCharacterUnder[_clientIndex]->removeFromParentAndCleanup(true);
	}
	m_pCharacterUnder[_clientIndex] = nullptr;

	if (m_pEmotiBubble[_clientIndex] != nullptr)
	{
		//m_pEmotiBubble[_clientIndex]->destruct();
		//m_pEmotiBubble[_clientIndex]->cleanup();
		m_pEmotiBubble[_clientIndex]->removeFromParentAndCleanup(true);
	}
	m_pEmotiBubble[_clientIndex] = nullptr;

	//개발해야할 부분 나갈때 이리로 온다.
	PokerPlayerInfoCommonPanel * playerInfoCommonPanel = GetPlayerCommonPanelWithIndex(_index);
	if (playerInfoCommonPanel && playerInfoCommonPanel->m_pUserInfoPanel) {
		playerInfoCommonPanel->m_pUserInfoPanel->setActivatePanel(false);
		playerInfoCommonPanel->m_pUserInfoPanel->initButtonState();
	}	
}

void PokerPlayerInfoPanel::RemoveAllCharacter()
{
	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		RemoveCharacter(_i);
	}
}

void PokerPlayerInfoPanel::setBettingPanel()
{
	mPlayerInfoPanelMy->setBettingPanel();
}

void PokerPlayerInfoPanel::_initData()
{
	mPlayerInfoPanelMy = nullptr;
	mParentPanel = nullptr;

	mPlayerInfos.clear();

	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		m_pCharacter[_i] = nullptr;
		m_pCharacterUnder[_i] = nullptr;
		m_pEmotiBubble[_i] = nullptr;
	}
	
}

void PokerPlayerInfoPanel::_setParentPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("Background"));
	assert(mParentPanel);
}

void PokerPlayerInfoPanel::_collectPlayerInfos()
{
	mPlayerInfos.clear();
	mPlayerInfos.push_back(mPlayerRightPanelOne);
	mPlayerInfos.push_back(mPlayerRightPanelTwo);
	mPlayerInfos.push_back(mPlayerInfoPanelMy);
	mPlayerInfos.push_back(mPlayerLeftPanelTwo);
	mPlayerInfos.push_back(mPlayerLeftPanelOne);
}

PokerPlayerInfoCommonPanel * PokerPlayerInfoPanel::GetPlayerCommonPanelWithIndex(int idx)
{
	switch (idx)
	{
	case 0:
		return mPlayerInfoPanelMy;
		break;
	case 1:
		return mPlayerLeftPanelTwo;
		break;
	case 2:
		return mPlayerLeftPanelOne;
		break;
	case 3:
		return mPlayerRightPanelOne;
		break;
	case 4:
		return mPlayerRightPanelTwo;
		break;
	default:
		break;
	}

	return nullptr;
}

Panel* PokerPlayerInfoPanel::GetPlayerPanel(int _po)
{
	RoomUserData* _pUserDate = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_po);
	if (_pUserDate == nullptr)
		return nullptr;
	
	int _userIdx = _pUserDate->m_pCardManager->m_UserIdx;
	switch (_userIdx)
	{
	case 0:
		return mPlayerInfoPanelMy->mMainPanel;
		break;
	case 1:
		return mPlayerLeftPanelTwo->mMainPanel;
		break;
	case 2:
		return mPlayerLeftPanelOne->mMainPanel;
		break;
	case 3:
		return mPlayerRightPanelOne->mMainPanel;
		break;
	case 4:
		return mPlayerRightPanelTwo->mMainPanel;
		break;
	default:
		break;
	}
	return nullptr;
}

PokerPlayerInfoCommonPanel* PokerPlayerInfoPanel::GetPlayerCommonPanel(int _po)
{
	RoomUserData* _pUserDate = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_po);
	if (_pUserDate == nullptr)
		return nullptr;

	int _userIdx = _pUserDate->m_pCardManager->m_UserIdx;
	switch (_userIdx)
	{
	case 0:
		return mPlayerInfoPanelMy;
		break;
	case 1:
		return mPlayerLeftPanelTwo;
		break;
	case 2:
		return mPlayerLeftPanelOne;
		break;
	case 3:
		return mPlayerRightPanelOne;
		break;
	case 4:
		return mPlayerRightPanelTwo;
		break;
	default:
		break;
	}
	return nullptr;
}

void PokerPlayerInfoPanel::ClearAllPanelAction()
{
	mPlayerInfoPanelMy->turnOffTimeGauge();
	mPlayerLeftPanelTwo->turnOffTimeGauge();
	mPlayerLeftPanelOne->turnOffTimeGauge();
	mPlayerRightPanelOne->turnOffTimeGauge();
	mPlayerRightPanelTwo->turnOffTimeGauge();
}
//
//void PokerPlayerInfoPanel::onClicked(const string& buttonName)
//{
//
//	if (buttonName == "MyPlayerInfo_Btn")
//	{
//		
//	}
//	if (buttonName == "LeftOnePlayerInfo_Btn")
//	{
//		mPlayerLeftPanelOne->m_pEmotionLeftPanel->setVisible(true);
//		mPlayerLeftPanelOne->m_pLeftUserInfoPanel->setVisible(true);
//	}
//	if (buttonName == "LeftTwoPlayerInfo_Btn")
//	{
//		mPlayerLeftPanelTwo->m_pEmotionLeftPanel->setVisible(true);
//		mPlayerLeftPanelTwo->m_pLeftUserInfoPanel->setVisible(true);
//	}
//	if (buttonName == "RightOnePlayerInfo_Btn")
//	{
//		mPlayerRightPanelOne->m_pEmotionRightPanel->setVisible(true);
//		mPlayerRightPanelOne->m_pRightUserInfoPanel->setVisible(true);
//	}
//	if (buttonName == "RightTwoPlayerInfo_Btn")
//	{
//		mPlayerRightPanelTwo->m_pEmotionRightPanel->setVisible(true);
//		mPlayerRightPanelTwo->m_pRightUserInfoPanel->setVisible(true);
//	}
//}
