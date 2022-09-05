#include "pch.h"
#include "LobbySurvivalBottomPannel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"

LobbySurvivalBottomPannel::LobbySurvivalBottomPannel()
{
	m_catchCenterIndex = -1;
	m_totalChannelCount = 0;
	m_curChannelIndex = 0;

	m_pChannelView = nullptr;
	m_pChannelContainer = nullptr;

	for (int _i = 0; _i < SURVIVAL_CELL_MAX; _i++)
	{
		m_pChannel[_i] = nullptr;
	}

	InitPanel();
	InitImage();
	initButton();

	setTouchable(false);
	setButtonListener(this);	
}

LobbySurvivalBottomPannel::~LobbySurvivalBottomPannel()
{
	//destruct();
}

void LobbySurvivalBottomPannel::InitPanel()
{
	construct(getMxmlPath() + "dmy_channel_position.mxml");
	
	InitChannelList();
	//m_curChannelIndex = 0;
	//CreateChannelCell();
}

void LobbySurvivalBottomPannel::InitImage()
{
	InitCenterPanel();
}

void LobbySurvivalBottomPannel::initButton()
{
	mReplayBtn = getButton("sbtn_replay");
	mReplayLabel = getLabel("txt_replay");
	mReplayLabel->setVisible(false);
	setVislbleButton(mReplayBtn, false);
}


bool LobbySurvivalBottomPannel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}


void LobbySurvivalBottomPannel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbySurvivalBottomPannel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbySurvivalBottomPannel::resume()
{
}

void LobbySurvivalBottomPannel::onClicked(const string& name)
{
	if (name == "sbtn_button_enter")
	{
		LobbySurvivalCell* _pCell = m_pChannel[m_catchCenterIndex];
		if (_pCell == nullptr)
			return;

		if (_pCell->m_btnChannel->isEnabled() == true)
		{
			int _matchId = _pCell->m_CellInfo->matchid();
			GameDataManager::getSingletonPtr()->m_TournamentId = _matchId;
			WebService::getSingletonPtr()->SurvivalMatchIdReq(_matchId);
		}
	}
}

void LobbySurvivalBottomPannel::update(float dt)
{
}

bool LobbySurvivalBottomPannel::handling(STCMD &stCmd)
{
	return false;
}

//void LobbySurvivalBottomPannel::CreateChannelCell()
//{
//	if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo == nullptr)
//		return;
//
//	CCSize _contentSize = getDummy("dmy_channel_position").size;
//	
//	m_totalChannelCount = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo_size();
//	
//	m_pChannelContainer = CCLayer::create();
//	if ((SURVIVAL_CELL_INIT_X * 2) + (m_totalChannelCount * SURVIVAL_CELL_WIDTH) > DESIGN_WIDTH)
//	{
//		if (m_totalChannelCount > SURVIVAL_CELL_MAX)
//		{
//			m_pChannelContainer->setContentSize(CCSizeMake((SURVIVAL_CELL_INIT_X * 2) + (SURVIVAL_CELL_MAX * SURVIVAL_CELL_WIDTH), SURVIVAL_CELL_HIGHT));
//		}
//		else
//		{
//			m_pChannelContainer->setContentSize(CCSizeMake((SURVIVAL_CELL_INIT_X * 2) + (m_totalChannelCount * SURVIVAL_CELL_WIDTH), SURVIVAL_CELL_HIGHT));
//		}
//	}
//	else
//	{
//		m_pChannelContainer->setContentSize(CCSizeMake(DESIGN_WIDTH, SURVIVAL_CELL_HIGHT));
//	}
//
//
//	for (int _i = 0; _i < SURVIVAL_CELL_MAX; _i++)
//	{
//		if (m_totalChannelCount <= _i)
//			continue;
//
//		m_pChannel[_i] = new LobbySurvivalCell();
//		m_pChannelContainer->addChild(m_pChannel[_i], 1);
//		m_pChannel[_i]->setPositionX(SURVIVAL_CELL_WIDTH * _i + SURVIVAL_CELL_INIT_X);
//		m_pChannel[_i]->setPositionY(SURVIVAL_CELL_HIGHT - DESIGN_HEIGHT);
//		m_pChannel[_i]->release();
//	}
//
//	UpdateChannelCell();
//
//	m_pChannelView = extension::CCScrollView::create(_contentSize, m_pChannelContainer);
//	m_pChannelView->setDirection(extension::kCCScrollViewDirectionHorizontal);
//	m_pChannelView->setBounceable(false);
//	m_pChannelView->setContentOffset(ccp(0, 0), false);
//	m_pChannelView->setTouchEnabled(false);
//
//	m_pChannelView->setPosition(ccp(0.f, DESIGN_HEIGHT - _contentSize.height - 20.f));
//	addChild(m_pChannelView);
//}

void LobbySurvivalBottomPannel::UpdateChannelCell()
{
	if (m_pChannelView == NULL)
		return;

	for (int _i = 0; _i < SURVIVAL_CELL_MAX; _i++)
	{
		if (m_totalChannelCount <= _i)
			continue;

		int _index = _i + m_curChannelIndex;
		if (m_totalChannelCount <= _index)
		{
			_index = _index % m_totalChannelCount;
		}

		if (_index < 0)
		{
			_index = m_totalChannelCount + (_index % m_totalChannelCount);
			if (_index == m_totalChannelCount)
			{
				_index = 0;
			}
		}

		m_pChannel[_i]->SetCellData(_index);
	}
}

//void LobbySurvivalBottomPannel::RemoveChannelCell()
//{
//	if (m_pChannelView)
//	{
//		m_pChannelView->removeFromParentAndCleanup(true);
//		m_pChannelView = nullptr;
//	}
//}

void LobbySurvivalBottomPannel::UpdateCellScale()
{
	if (m_pChannelView == NULL)
		return;

	ReleseCenterCell();
	m_catchCenterIndex = -1;

	for (int _i = 0; _i < SURVIVAL_CELL_MAX; _i++)
	{
		if (m_totalChannelCount <= _i)
			continue;

		float _initScale = 0.5f;
		float _weightScale = 0.5f;
		//float _weightX = SURVIVAL_CELL_WIDTH * 6.f;
		float _startRange = SURVIVAL_CELL_WIDTH * 0.5f;
		float _endRange = DESIGN_WIDTH;

		int _cellX = SURVIVAL_CELL_WIDTH * (_i)+SURVIVAL_CELL_INIT_X;
		int _cellY = SURVIVAL_CELL_HIGHT - DESIGN_HEIGHT + 20.f;
		int _offset = m_pChannelView->getContentOffset().x;
		int _diffCellX = _cellX + _offset - _startRange + SURVIVAL_CELL_WIDTH;
		int _cellScaleX = _cellX + _offset - (SURVIVAL_CELL_WIDTH * 0.5f) + SURVIVAL_CELL_WIDTH;

		int _diffX = 0;
		int _diffY = 0;
		float _diffScale = ((float)_diffCellX) / _endRange;
		float _diffcellScale = ((float)_cellScaleX) / DESIGN_WIDTH;

		if (_diffScale > 0.49f && _diffScale < 0.51f)
		{
			m_catchCenterIndex = _i;
		}

		if (_diffCellX < _endRange / 2.f && _diffCellX >= 0)
		{
			float _cellScale = _initScale + (_weightScale * _diffcellScale * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = getCellMetrics(_diffScale);//_weightX * ((0.5f - (0.5f - _diffScale)) * (0.5f - _diffScale));
			_diffY = _cellY * (0.9f - _cellScale);
		}
		else if (_diffCellX < _endRange && _diffCellX >= _endRange / 2.f)
		{
			float _cellScale = _initScale + (_weightScale * (1.f - _diffcellScale) * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = getCellMetrics(_diffScale);// -_weightX *((0.5f - (_diffScale - 0.5f)) * (_diffScale - 0.5f));// ((_diffScale - 0.5f) * 1.6f);
			_diffY = _cellY * (0.9f - _cellScale);
		}
		else if (_diffCellX < 0)
		{
			float _cellScale = _initScale + (_weightScale * _diffcellScale * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = _cellX;
			_diffY = _cellY * (0.9f - _cellScale);
		}
		else
		{
			float _cellScale = _initScale + (_weightScale * (1.f - _diffcellScale) * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = _cellX;
			_diffY = _cellY * (0.9f - _cellScale);
		}

		m_pChannel[_i]->setPositionX(_diffX);
		m_pChannel[_i]->setPositionY(_cellY - _diffY);
	}
}

void LobbySurvivalBottomPannel::SetCenterCell()
{
	if (m_catchCenterIndex == -1 || m_catchCenterIndex >= SURVIVAL_CELL_MAX)
		return;

	Button* _btn = m_pChannel[m_catchCenterIndex]->m_btnChannel;

	int _infoIndex = m_catchCenterIndex + m_curChannelIndex;

	W_DeathMatchInfo _info = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo(_infoIndex);

	int _gameKind = _info.gamekind();

	string _frameName = "";
	if (_gameKind == GameKind::GAMEKIND_7POKER)
	{
		_frameName = "tone_seven";
	}
	else if (_gameKind == GameKind::GAMEKIND_HIGH_LOW)
	{
		_frameName = "tone_highlow";
	}
	else if (_gameKind == GameKind::GAMEKIND_BADUKI)
	{
		_frameName = "tone_badugi";
	}
	else if (_gameKind == GameKind::GAMEKIND_HOLDEM)
	{
		_frameName = "tone_texas";
	}

	getSkel("skel_uitone")->playAnimation(_frameName.c_str());

	string _frameName1 = "";
	string _frameName2 = "";

	switch (_gameKind)
	{
	case GameKind::GAMEKIND_7POKER:
		_frameName1 = "seven_";
		_frameName2 = "seven_";
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_frameName1 = "highlow_";
		_frameName2 = "highlow_";
		break;
	case GameKind::GAMEKIND_BADUKI:
		_frameName1 = "badugi_";
		_frameName2 = "badugi_";
		break;
	case GameKind::GAMEKIND_HOLDEM:
		_frameName1 = "texas_";
		_frameName2 = "texas_";
		break;
	}

	if (_btn->isEnabled())
	{
		_frameName1 += "change";
		_frameName2 += "center";
	}
	else
	{
		_frameName1 += "stayoff";
		_frameName2 += "changeoff";
	}

	_btn->getButtonSkelObject()->playAnimation(_frameName1);
	_btn->getButtonSkelObject()->appendAnimation(_frameName2, _btn->isEnabled());

	
	//getSkel("skel_light")->setVisible(true);


	m_pChannel[m_catchCenterIndex]->m_labelTitle->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelGift->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelGold->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelEnter->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelEnterCount->setVisible(false);
	m_pChannel[m_catchCenterIndex]->getSkel("skel_lock")->setVisible(false);

	UpdateCenterCell();
	m_pCenterPanel->setVisible(true);
}

void LobbySurvivalBottomPannel::ReleseCenterCell()
{
	if (m_catchCenterIndex == -1 || m_catchCenterIndex >= SURVIVAL_CELL_MAX)
		return;

	int _infoIndex = m_catchCenterIndex + m_curChannelIndex;
	W_DeathMatchInfo _info = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo(_infoIndex);
	int _gameKind = _info.gamekind();

	Button* _btn = m_pChannel[m_catchCenterIndex]->m_btnChannel;
	string _frameName1 = "";

	switch (_gameKind)
	{
	case GameKind::GAMEKIND_7POKER:
		_frameName1 = "seven_";
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_frameName1 = "highlow_";
		break;
	case GameKind::GAMEKIND_BADUKI:
		_frameName1 = "badugi_";
		break;
	case GameKind::GAMEKIND_HOLDEM:
		_frameName1 = "texas_";
		break;
	}

	if (_btn->isEnabled())
	{
		_frameName1 += "stay";
	}
	else
	{
		_frameName1 += "stayoff";
	}

	_btn->getButtonSkelObject()->playAnimation(_frameName1, true);
	//getSkel("skel_light")->setVisible(false);

	m_pChannel[m_catchCenterIndex]->m_labelTitle->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelGift->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelGold->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelEnter->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelEnterCount->setVisible(true);
	if (m_pChannel[m_catchCenterIndex]->m_btnChannel->isEnabled() == false)
	{
		m_pChannel[m_catchCenterIndex]->getSkel("skel_lock")->setVisible(true);
	}
	m_pCenterPanel->getButton("sbtn_button_enter")->setEnable(false);

	m_pCenterPanel->setVisible(false);
}

void LobbySurvivalBottomPannel::UpdateCenterCell()
{
	int _index = m_catchCenterIndex + m_curChannelIndex;

	W_DeathMatchOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;

	if (_pInfoData == nullptr)
		return;

	W_DeathMatchInfo _matchInfo = _pInfoData->matchinfo(_index);

	if (_matchInfo.has_finalrewardinfo())
	{
		W_RewardInfo _Rewardinfo = _matchInfo.finalrewardinfo();
		int _size = _Rewardinfo.rewardset_size();

		for (int _i = 0; _i < _size; _i++)
		{
			W_RewardInfo_RewardSet _reward = _Rewardinfo.rewardset(_i);
			switch (_reward.type())
			{
			case eResourceType::CASH:
				break;
			case eResourceType::GAMEMONEY:
			{
				std::string _gold = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_reward.amount()), 1);
				m_pCenterPanel->getLabel("txt_gold_sum")->setString(_gold.c_str());
				break;
			}
			case eResourceType::CHIP:
				break;
			}
		}
	}

	std::string _gold = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_matchInfo.joinmoney()), 1);
	m_pCenterPanel->getLabel("txt_gold_sum")->setString(_gold.c_str());
	
	int _registCount = _matchInfo.registercnt();
	int _registMax = _matchInfo.registermax();
	std::string _registTxt = GameStringDepot::getSingletonPtr()->getString("TXT_ENTER_COUNT") + ":" + StringConverter::toString(_registCount);
	_registTxt += "/" + StringConverter::toString(_registMax);
	m_pCenterPanel->getLabel("txt_state_sum")->setString(_registTxt.c_str());

	m_pCenterPanel->getLabel("txt_daysum")->setString("");
	m_pCenterPanel->getLabel("txt_tournament_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_MATCH").c_str());

	string _frameName = "";
	string _btnName = "";
	//ccColor3B _titleColor;
	//ccColor3B _descColor;
	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		_frameName = "lock_saven";
		_btnName = "button_seven";
		//_titleColor = ccc3(255, 241, 233);
		//_descColor = ccc3(235, 122, 122);
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_frameName = "lock_highlow";
		_btnName = "button_highlow";
		//_titleColor = ccc3(233, 246, 255);
		//_descColor = ccc3(111, 151, 224);
		break;
	case GameKind::GAMEKIND_BADUKI:
		_frameName = "lock_badugi";
		_btnName = "button_badugi";
		//_titleColor = ccc3(243, 255, 233);
		//_descColor = ccc3(128, 228, 114);
		break;
	case GameKind::GAMEKIND_HOLDEM:
		_frameName = "lock_texas";
		_btnName = "button_texas";
		//_titleColor = ccc3(233, 255, 255);
		//_descColor = ccc3(105, 228, 212);
		break;
	}

	if (m_pChannel[m_catchCenterIndex]->m_btnChannel->isEnabled())
	{
		m_pCenterPanel->getSkel("skel_lock")->setVisible(false);
		m_pCenterPanel->getButton("sbtn_button_enter")->getButtonSkelObject()->playAnimation(_btnName.c_str());
		m_pCenterPanel->getButton("sbtn_button_enter")->setType(Button::Normal);
		m_pCenterPanel->getButton("sbtn_button_enter")->setEnable(true);
	}
	else
	{
		m_pCenterPanel->getSkel("skel_lock")->playAnimation(_frameName);
		m_pCenterPanel->getSkel("skel_lock")->setVisible(true);

		m_pCenterPanel->getButton("sbtn_button_enter")->getButtonSkelObject()->playAnimation("button_off");
		m_pCenterPanel->getButton("sbtn_button_enter")->setType(Button::NoPressImg);
		m_pCenterPanel->getButton("sbtn_button_enter")->setEnable(false);

		//_titleColor = ccc3(151, 151, 151);
		//_descColor = ccc3(151, 151, 151);
	}
	//m_pCenterPanel->getLabel("txt_channel_title")->setColor(_titleColor);
	//m_pCenterPanel->getLabel("txt_titledeco")->setColor(_titleColor);

	//m_pCenterPanel->getLabel("txt_seed_money")->setColor(_descColor);
	//m_pCenterPanel->getLabel("txt_channel_usernumber")->setColor(_descColor);
	//m_pCenterPanel->getLabel("txt_slash")->setColor(_descColor);
	//m_pCenterPanel->getLabel("txt_game_rule")->setColor(_descColor);
}

void LobbySurvivalBottomPannel::InitChannelList()
{
	if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo == nullptr)
		return;
	
	CCSize _contentSize = getDummy("dmy_channel_position").size;
		
	m_totalChannelCount = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo_size();
	m_curChannelIndex = 0;

	ReleaseChannelList();

	m_pChannelContainer = CCLayer::create();
	if ((m_totalChannelCount * SURVIVAL_CELL_WIDTH) + (SURVIVAL_CELL_INIT_X * 2) > DESIGN_WIDTH)
	{
		if (m_totalChannelCount > SURVIVAL_CELL_MAX)
		{
			m_pChannelContainer->setContentSize(CCSizeMake((SURVIVAL_CELL_MAX * SURVIVAL_CELL_WIDTH) + (SURVIVAL_CELL_INIT_X * 2), SURVIVAL_CELL_HIGHT));
		}
		else
		{
			m_pChannelContainer->setContentSize(CCSizeMake((m_totalChannelCount * SURVIVAL_CELL_WIDTH) + (SURVIVAL_CELL_INIT_X * 2), SURVIVAL_CELL_HIGHT));
		}
	}
	else
	{
		m_pChannelContainer->setContentSize(CCSizeMake(DESIGN_WIDTH, SURVIVAL_CELL_HIGHT));
	}

	for (int _i = 0; _i < SURVIVAL_CELL_MAX; _i++)
	{
		if (m_totalChannelCount <= _i)
			continue;

		m_pChannel[_i] = new LobbySurvivalCell();
		m_pChannelContainer->addChild(m_pChannel[_i], 1);
		m_pChannel[_i]->setPositionX(SURVIVAL_CELL_WIDTH * (_i)+SURVIVAL_CELL_INIT_X);
		m_pChannel[_i]->setPositionY(SURVIVAL_CELL_HIGHT - DESIGN_HEIGHT - 61.f);
		m_pChannel[_i]->release();
	}

	UpdateChannelCell();

	m_pChannelView = CCScrollView::create(_contentSize, m_pChannelContainer);
	m_pChannelView->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	m_pChannelView->setBounceable(false);
	m_pChannelView->setContentOffset(ccp(0, 0), false);
	m_pChannelView->setTouchEnabled(false);

	m_pChannelView->setPosition(ccp(0.f, DESIGN_HEIGHT - _contentSize.height - 20.f));
	addChild(m_pChannelView, 2);
}

void LobbySurvivalBottomPannel::ReleaseChannelList()
{
	if (m_pChannelContainer)
	{
		m_pChannelContainer->cleanup();
		m_pChannelContainer->removeFromParent();
	}
	m_pChannelContainer = nullptr;

	if (m_pChannelView)
	{
		m_pChannelView->cleanup();
		m_pChannelView->removeFromParent();

	}
	m_pChannelView = nullptr;

	for (int _i = 0; _i < SURVIVAL_CELL_MAX; _i++)
	{
		m_pChannel[_i] = nullptr;
	}
}

float LobbySurvivalBottomPannel::getCellMetrics(float _per)
{
	if (_per <= 0.5f)
	{
		float _value = DESIGN_WIDTH * 0.5f * 4.f * _per * _per;
		return _value - m_pChannelView->getContentOffset().x - SURVIVAL_CELL_WIDTH * 0.5f;
	}
	else
	{
		float _value = DESIGN_WIDTH - (DESIGN_WIDTH * 0.5f * 4.f * (1.f - _per) * (1.f - _per));
		return _value - m_pChannelView->getContentOffset().x - SURVIVAL_CELL_WIDTH * 0.5f;
	}
}

void LobbySurvivalBottomPannel::InitCenterPanel()
{
	CCPoint _pos = getDummy("dmy_channel_center").origin;
	_pos.y = -_pos.y;

	m_pCenterPanel = new Panel();
	m_pCenterPanel->construct(getMxmlPath() + "dmy_survival_center.mxml");
	m_pCenterPanel->setPosition(_pos);
	addChild(m_pCenterPanel, 10);
	m_pCenterPanel->release();

	m_pCenterPanel->getLabel("txt_enter_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_enter")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_state_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_gold_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_gift")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_daysum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_tournament_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	m_pCenterPanel->getLabel("txt_gift")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REGISTATION_LABEL").c_str());
	m_pCenterPanel->getLabel("txt_gift")->setVisible(false);
	m_pCenterPanel->getLabel("txt_enter_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str());
	m_pCenterPanel->getLabel("txt_enter")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str());

	m_pCenterPanel->getButton("sbtn_button_enter")->setListener(this);

	m_pCenterPanel->setVisible(false);
}
