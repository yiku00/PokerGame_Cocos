#include "pch.h"
#include "ChannelBottomUiPannel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"
#include <random>

ChannelBottomUiPannel::ChannelBottomUiPannel()
{
	m_catchCenterIndex = -1;
	m_totalChannelCount = 0;
	m_curChannelIndex = 0;

	m_pChannelView = nullptr;
	m_pChannelContainer = nullptr;

	for (int _i = 0; _i < CHANNEL_CELL_MAX; _i++)
	{
		m_pChannel[_i] = nullptr;
	}

	InitPanel();
	InitImage();
	initButton();
	refreshNotiEffect();
	setTouchable(false);
	setButtonListener(this);	
}

ChannelBottomUiPannel::~ChannelBottomUiPannel()
{
	//destruct();
}

void ChannelBottomUiPannel::InitPanel()
{
	construct(getMxmlPath() + "dmy_channel_position.mxml");

	InitChannelList();
}

void ChannelBottomUiPannel::InitImage()
{
	InitCenterPanel();
}

void ChannelBottomUiPannel::initButton()
{
	mReplayBtn = getButton("sbtn_replay");
	mReplayLabel = getLabel("txt_replay");
	mReplayLabel->setVisible(false);
	setVislbleButton(mReplayBtn, false);
}

void ChannelBottomUiPannel::InitChannelList()
{
	CCSize _contentSize = getDummy("dmy_scroll_size").size;

	string _frameName = "";
	if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_7POKER)
	{
		m_totalChannelCount = GameDataManager::getSingletonPtr()->m_p7PokerChannelList.size();
		_frameName = "tone_seven";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW)
	{
		m_totalChannelCount = GameDataManager::getSingletonPtr()->m_pHighLowChannelList.size();
		_frameName = "tone_highlow";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		m_totalChannelCount = GameDataManager::getSingletonPtr()->m_pBadukiChannelList.size();
		_frameName = "tone_badugi";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM)
	{
		m_totalChannelCount = GameDataManager::getSingletonPtr()->m_pHoldemChannelList.size();
		_frameName = "tone_texas";
	}

	//기덕 추가 버그
	if (m_catchCenterIndex >= m_totalChannelCount)
		m_catchCenterIndex = m_totalChannelCount - 1;

	getSkel("skel_uitone")->playAnimation(_frameName.c_str());

	m_curChannelIndex = 0;

	ReleaseChannelList();

	m_pChannelContainer = CCLayer::create();
	if ((m_totalChannelCount * CHANNEL_CELL_WIDTH) + (CHANNEL_CELL_INIT_WIDTH * 2) > DESIGN_WIDTH)
	{
		if (m_totalChannelCount > CHANNEL_CELL_MAX)
		{
			m_pChannelContainer->setContentSize(CCSizeMake((CHANNEL_CELL_MAX * CHANNEL_CELL_WIDTH) + (CHANNEL_CELL_INIT_WIDTH * 2), CHANNEL_CELL_HIGHT));
		}
		else
		{
			m_pChannelContainer->setContentSize(CCSizeMake((m_totalChannelCount * CHANNEL_CELL_WIDTH) + (CHANNEL_CELL_INIT_WIDTH * 2), CHANNEL_CELL_HIGHT));
		}
	}
	else
	{
		m_pChannelContainer->setContentSize(CCSizeMake(DESIGN_WIDTH, CHANNEL_CELL_HIGHT));
	}

	for (int _i = 0; _i < CHANNEL_CELL_MAX; _i++)
	{
		if (m_totalChannelCount <= _i)
			continue;

		m_pChannel[_i] = new ChannelCell();
		m_pChannelContainer->addChild(m_pChannel[_i], 1);
		m_pChannel[_i]->setPositionX(CHANNEL_CELL_WIDTH * (_i)+CHANNEL_CELL_INIT_WIDTH);
		m_pChannel[_i]->setPositionY(CHANNEL_CELL_HIGHT - DESIGN_HEIGHT - 61.f);
		m_pChannel[_i]->release();
	}

	UpdateChannelCell();

	m_pChannelView = CCScrollView::create(_contentSize, m_pChannelContainer);
	m_pChannelView->setDirection(ScrollView::Direction::HORIZONTAL);
	m_pChannelView->setBounceable(false);
	m_pChannelView->setContentOffset(ccp(0, 0), false);
	m_pChannelView->setTouchEnabled(false);

	m_pChannelView->setPosition(ccp(0.f, DESIGN_HEIGHT - _contentSize.height - 20.f));
	addChild(m_pChannelView, 2);
}

void ChannelBottomUiPannel::ReleaseChannelList()
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

	for (int _i = 0; _i < CHANNEL_CELL_MAX; _i++)
	{
		m_pChannel[_i] = nullptr;
	}

}

void ChannelBottomUiPannel::InitCenterPanel()
{
	CCPoint _pos = getDummy("dmy_channel_center").origin;
	_pos.y = -_pos.y;

	m_pCenterPanel = new Panel();
	m_pCenterPanel->construct(getMxmlPath() + "dmy_channel_center.mxml");
	m_pCenterPanel->setPosition(_pos);
	addChild(m_pCenterPanel, 10);
	m_pCenterPanel->release();

	m_pCenterPanel->getLabel("txt_enter_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_enter")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_seed_money")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_channel_usernumber")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_slash")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_game_rule")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_channel_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_titledeco")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	m_pCenterPanel->getLabel("txt_enter_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str());
	m_pCenterPanel->getLabel("txt_enter")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str());

	m_pCenterPanel->getButton("sbtn_button_enter")->setListener(this);

	m_pCenterPanel->setVisible(false);

}


bool ChannelBottomUiPannel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}


void ChannelBottomUiPannel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void ChannelBottomUiPannel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void ChannelBottomUiPannel::resume()
{
}

void ChannelBottomUiPannel::onClicked(const string& name)
{
	if (name == "sbtn_button_enter")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		ChannelCell* _pCell = m_pChannel[m_catchCenterIndex];
		if (_pCell == nullptr)
			return;

		W_ChannelInfo* _pInfo = getChannelInfo(m_catchCenterIndex);
		if (_pInfo == nullptr)
			return;

		if (_pCell->m_btnChannel->isEnabled() == false)
		{
			string tmpTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CHANNEL_NOTICE_SMALL_MONEY");
			tmpTxt += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_pInfo->undermoney()), 1) + "\n";
			if (_pInfo->overmoney() > 0)
			{
				tmpTxt += GameStringDepot::getSingletonPtr()->getString("TXT_CHANNEL_NOTICE_MAX_MONEY");
				tmpTxt += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_pInfo->overmoney()), 1);
			}
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, tmpTxt), DYNAMIC_PUSH_LAYER);
		}
		else
		{
			GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney1 = _pInfo->bigpot_1();
			GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney2 = _pInfo->bigpot_2();
			GameDataManager::getSingletonPtr()->m_RoomId = _pInfo->id();
			GameDataManager::getSingletonPtr()->m_BettingRule = _pInfo->bettingrule();
			GameDataManager::getSingletonPtr()->m_seedMoney = _pInfo->seedmoney();
			GameDataManager::getSingletonPtr()->m_Grade = _pInfo->grade();
			GameDataManager::getSingletonPtr()->m_EnterGameRoomBettingMaxMoney = _pInfo->bigbettingmaxmoney();
			GameDataManager::getSingletonPtr()->m_GameMode = _pInfo->gamemode();
			GameDataManager::getSingletonPtr()->m_IsSelectRoom = _pInfo->isselectroom();
			//tournament
			GameDataManager::getSingletonPtr()->m_TournamentId = 0;
			GameDataManager::getSingletonPtr()->m_TournamentStep = 0;
			string _ip = _pInfo->ip();
			int32 _port = _pInfo->port();
			//만약 룸을 선택할수 없다면
			if (strcmp(WebService::getSingletonPtr()->getCurIp().c_str(), _ip.c_str()) == 0 && WebService::getSingletonPtr()->getCurPort() == _port)
			{
				if (GameDataManager::getSingletonPtr()->m_GameMode == GameMode::MODE_NORMAL)
				{
					TCPService::getSingletonPtr()->SendUpdatePlayerInfoReq();
				}
				else
				{
					TCPService::getSingletonPtr()->SendTournamentPlayerInfoReq();
				}

			}
			else
			{
				WebService::getSingletonPtr()->setLobbyIp(_ip);
				WebService::getSingletonPtr()->setLobbyPort(_port);

				TCPService::getSingletonPtr()->Close();
				TCPService::getSingletonPtr()->Start();
				TCPService::getSingletonPtr()->Connect(_ip, _port, false);
			}
		}
	}
}

void ChannelBottomUiPannel::update(float dt)
{
}

bool ChannelBottomUiPannel::handling(STCMD &stCmd)
{
	return false;
}

void ChannelBottomUiPannel::UpdateChannelCell()
{
	if (m_pChannelView == NULL)
		return;

	for (int _i = 0; _i < CHANNEL_CELL_MAX; _i++)
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

		W_ChannelInfo* _pInfo = nullptr;
		switch (GameDataManager::getSingletonPtr()->getGameKind())
		{
		case GameKind::GAMEKIND_7POKER:
			_pInfo = GameDataManager::getSingletonPtr()->m_p7PokerChannelList[_index];
			break;
		case GameKind::GAMEKIND_HIGH_LOW:
			_pInfo = GameDataManager::getSingletonPtr()->m_pHighLowChannelList[_index];
			break;
		case GameKind::GAMEKIND_BADUKI:
			_pInfo = GameDataManager::getSingletonPtr()->m_pBadukiChannelList[_index];
			break;
		case GameKind::GAMEKIND_HOLDEM:
			_pInfo = GameDataManager::getSingletonPtr()->m_pHoldemChannelList[_index];
			break;
		}
		m_pChannel[_i]->SetCellData(_pInfo);
	}
}

void ChannelBottomUiPannel::UpdateCellScale()
{
	if (m_pChannelView == NULL)
		return;

	ReleseCenterCell();
	m_catchCenterIndex = -1;

	for (int _i = 0; _i < CHANNEL_CELL_MAX; _i++)
	{
		if (m_totalChannelCount <= _i)
			continue;

		float _initScale = 0.5f;
		float _weightScale = 0.5f;
		//float _weightX = CHANNEL_CELL_WIDTH * 6.f;
		float _startRange = CHANNEL_CELL_WIDTH * 0.5f;
		float _endRange = DESIGN_WIDTH;

		int _cellX = CHANNEL_CELL_WIDTH * (_i) + CHANNEL_CELL_INIT_WIDTH;
		int _cellY = CHANNEL_CELL_HIGHT - DESIGN_HEIGHT + 20.f;
		int _offset = m_pChannelView->getContentOffset().x;
		int _diffCellX = _cellX + _offset - _startRange + CHANNEL_CELL_WIDTH;
		int _cellScaleX = _cellX + _offset - (CHANNEL_CELL_WIDTH * 0.5f) + CHANNEL_CELL_WIDTH;

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
			float _cellScale = _initScale +(_weightScale * _diffcellScale * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = _cellX;
			_diffY = _cellY * (0.9f - _cellScale);
		}
		else
		{
			float _cellScale = _initScale +(_weightScale * (1.f - _diffcellScale) * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = _cellX;
			_diffY = _cellY * (0.9f - _cellScale);
		}

		m_pChannel[_i]->setPositionX(_diffX);
		m_pChannel[_i]->setPositionY(_cellY - _diffY);
	}
}

float ChannelBottomUiPannel::getCellMetrics(float _per)
{
	if (_per <= 0.5f)
	{
		float _value = DESIGN_WIDTH * 0.5f * 4.f * _per * _per;
		return _value - m_pChannelView->getContentOffset().x - CHANNEL_CELL_WIDTH * 0.5f;
	}
	else
	{
		float _value = DESIGN_WIDTH - (DESIGN_WIDTH * 0.5f * 4.f * (1.f - _per) * (1.f - _per));
		return _value - m_pChannelView->getContentOffset().x - CHANNEL_CELL_WIDTH * 0.5f;
	}
}

void ChannelBottomUiPannel::SetCenterCell()
{
	if (m_catchCenterIndex == -1 || m_catchCenterIndex >= CHANNEL_CELL_MAX)
		return;

	Button* _btn =  m_pChannel[m_catchCenterIndex]->getButton("sbtn_channel_button");

	string _frameName1 = "";
	string _frameName2 = "";
	
	switch (GameDataManager::getSingletonPtr()->getGameKind())
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

	/*getSkel("skel_light")->setVisible(true);*/

	m_pChannel[m_catchCenterIndex]->m_labelTitle->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelSeedmoney->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelUserCount->setVisible(false);
	m_pChannel[m_catchCenterIndex]->getSkel("skel_lock")->setVisible(false);

	UpdateCenterCell();
	m_pCenterPanel->setVisible(true);


	//m_pChannel[m_catchCenterIndex]->runAction(CCFadeOut::create(0.3f));

	//if (m_BottomUi->m_catchCenterIndex != -1 && _moveX < 5.f && _moveX > -5.f)
	//{
	//	SetMoveStop();
	//	if (m_BottomUi->m_catchCenterIndex != -1)
	//	{
	//		int _index = m_BottomUi->m_catchCenterIndex;
	//		Button* _btn = m_BottomUi->m_pChannel[_index]->getButton("sbtn_channel_button");
	//		_btn->getButtonSkelObject()->playAnimation("highlow_change");
	//		_btn->getButtonSkelObject()->appendAnimation("highlow_center");
	//	}
	//}
}

void ChannelBottomUiPannel::ReleseCenterCell()
{
	if (m_catchCenterIndex == -1 || m_catchCenterIndex >= CHANNEL_CELL_MAX)
		return;

	Button* _btn = m_pChannel[m_catchCenterIndex]->getButton("sbtn_channel_button");

	string _frameName1 = "";

	switch (GameDataManager::getSingletonPtr()->getGameKind())
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
	m_pChannel[m_catchCenterIndex]->m_labelSeedmoney->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelUserCount->setVisible(true);
	if (m_pChannel[m_catchCenterIndex]->m_btnChannel->isEnabled() == false)
	{
		m_pChannel[m_catchCenterIndex]->getSkel("skel_lock")->setVisible(true);
	}
	m_pCenterPanel->getButton("sbtn_button_enter")->setEnable(false);

	m_pCenterPanel->setVisible(false);
	//m_pChannel[m_catchCenterIndex]->setOpacity(255);
}

W_ChannelInfo* ChannelBottomUiPannel::getChannelInfo(int _cellIndex)
{
	int _index = _cellIndex + m_curChannelIndex;
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

	W_ChannelInfo* _pInfo = nullptr;

	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		_pInfo = GameDataManager::getSingletonPtr()->m_p7PokerChannelList[_index];
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_pInfo = GameDataManager::getSingletonPtr()->m_pHighLowChannelList[_index];
		break;
	case GameKind::GAMEKIND_BADUKI:
		_pInfo = GameDataManager::getSingletonPtr()->m_pBadukiChannelList[_index];
		break;
	case GameKind::GAMEKIND_HOLDEM:
		_pInfo = GameDataManager::getSingletonPtr()->m_pHoldemChannelList[_index];
		break;
	}

	return _pInfo;
}

void ChannelBottomUiPannel::UpdateCenterCell()
{
	W_ChannelInfo* _pInfo = getChannelInfo(m_catchCenterIndex);

	if (_pInfo == nullptr)
		return;

	string _seedText = GameStringDepot::getSingletonPtr()->getString("TXT_SEED_UNITS");
	_seedText += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_pInfo->seedmoney()), 1);
	
	string _userCountText = StringConverter::toString(_pInfo->usercount()) + GameStringDepot::getSingletonPtr()->getString("TXT_PEOPLE_COUNT");
	_userCountText += GameStringDepot::getSingletonPtr()->getString("TXT_GAME_ENTER_LABEL");

	string _ruleText = "";
	switch (_pInfo->bettingrule())
	{
	case BettingRule::RULE_FOUR_CARD:
		_ruleText += GameStringDepot::getSingletonPtr()->getString("TXT_RULE_FOUR_CARD") + "/";
		break;
	case BettingRule::RULE_FIVE_CARD:
		_ruleText += GameStringDepot::getSingletonPtr()->getString("TXT_RULE_FIVE_CARD") + "/";
		break;
	case BettingRule::RULE_SIX_CARD:
		_ruleText += GameStringDepot::getSingletonPtr()->getString("TXT_RULE_SIX_CARD") + "/";
		break;
	}

	_ruleText += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_pInfo->undermoney()), 2);
	if (_pInfo->overmoney() > 0)
	{
		_ruleText += GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT") + "~";
		_ruleText += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_pInfo->overmoney()), 2);
		_ruleText += GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT");
	}
	else
	{
		_ruleText += GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT") + " ";
		_ruleText += GameStringDepot::getSingletonPtr()->getString("TXT_BIGGER_THAN");
	}

	m_pCenterPanel->getLabel("txt_seed_money")->setString(_seedText.c_str());
	m_pCenterPanel->getLabel("txt_channel_usernumber")->setString(_userCountText.c_str());
	//m_pCenterPanel->getLabel("txt_slash")->setString("");
	m_pCenterPanel->getLabel("txt_game_rule")->setString(_ruleText.c_str());


	string _frameName = "";
	string _btnName = "";
	ccColor3B _titleColor;
	ccColor3B _descColor;
	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		_frameName = "lock_saven";
		_btnName = "button_seven";
		_titleColor = ccc3(255, 241, 233);
		_descColor = ccc3(235, 122, 122);
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_frameName = "lock_highlow";
		_btnName = "button_highlow";
		_titleColor = ccc3(233, 246, 255);
		_descColor = ccc3(111, 151, 224);
		break;
	case GameKind::GAMEKIND_BADUKI:
		_frameName = "lock_badugi";
		_btnName = "button_badugi";
		_titleColor = ccc3(243, 255, 233);
		_descColor = ccc3(128, 228, 114);
		break;
	case GameKind::GAMEKIND_HOLDEM:
		_frameName = "lock_texas";
		_btnName = "button_texas";
		_titleColor = ccc3(233, 255, 255);
		_descColor = ccc3(105, 228, 212);
		break;
	}

	if (m_pChannel[m_catchCenterIndex]->m_btnChannel->isEnabled())
	{
		m_pCenterPanel->getSkel("skel_lock")->setVisible(false);
		m_pCenterPanel->getButton("sbtn_button_enter")->getButtonSkelObject()->playAnimation(_btnName.c_str());
		m_pCenterPanel->getButton("sbtn_button_enter")->setType(Button::Normal);
		m_pCenterPanel->getButton("sbtn_button_enter")->setEnable(true);

		_titleColor = ccc3(255, 255, 255);
		_descColor = ccc3(255, 255, 255);
	}
	else
	{
		m_pCenterPanel->getSkel("skel_lock")->playAnimation(_frameName);
		m_pCenterPanel->getSkel("skel_lock")->setVisible(true);

		m_pCenterPanel->getButton("sbtn_button_enter")->getButtonSkelObject()->playAnimation("button_off");
		m_pCenterPanel->getButton("sbtn_button_enter")->setType(Button::NoPressImg);
		m_pCenterPanel->getButton("sbtn_button_enter")->setEnable(false);

		_titleColor = ccc3(151, 151, 151);
		_descColor = ccc3(151, 151, 151);
	}
	m_pCenterPanel->getLabel("txt_channel_title")->setColor(_titleColor);
	m_pCenterPanel->getLabel("txt_titledeco")->setColor(_titleColor);

	m_pCenterPanel->getLabel("txt_seed_money")->setColor(_descColor);
	m_pCenterPanel->getLabel("txt_channel_usernumber")->setColor(_descColor);
	m_pCenterPanel->getLabel("txt_slash")->setColor(_descColor);
	m_pCenterPanel->getLabel("txt_game_rule")->setColor(_descColor);

	if (_pInfo->has_name())
	{
		string _title = _pInfo->name();
		m_pCenterPanel->getLabel("txt_channel_title")->setString(_title.c_str());

		
		m_pCenterPanel->getLabel("txt_titledeco")->setString("");
	}
}

void ChannelBottomUiPannel::refreshNotiEffect()
{	
}