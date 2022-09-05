#include "pch.h"
#include "ChannelMainPannel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"
#include "LobbyLeftUiPanel.h"
#include "LobbyLeftUiPanel.h"
#include "PokerResourceHelper.h"

ChannelMainPannel::ChannelMainPannel()
{
	m_DstAngle = 0.f;
	m_bActionRotate = false;
	m_bAutoMove = false;

	m_bCancelTouch = false;
	m_RootAngle = 0.f;
	m_bMoveAccel = false;
	m_moveG = 0.f;
	m_MovePoint = 0.f;

	m_earth = nullptr;
	m_BottomUi = nullptr;
	for (int _i = 0; _i < 4; _i++)
	{
		m_pTabPanel[_i] = nullptr;
	}

	m_pTabMain = nullptr;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);
}

ChannelMainPannel::~ChannelMainPannel()
{
	//destruct();
}

void ChannelMainPannel::InitPanel()
{
	construct(getMxmlPath() + "dmy_channel_back.mxml");
	setContentSize(CCSize(DESIGN_WIDTH, DESIGN_HEIGHT - 72));
	m_earth = new Panel();
	m_earth->construct(getMxmlPath() + "dmy_channel_earth.mxml");
	addChild(m_earth);
	m_earth->release();
	CCPoint _earthPos = getDummy("dmy_channel_earth").origin;
	m_earth->setPosition(ccp(_earthPos.x, -_earthPos.y));

	m_ObjCenterPos = m_earth->getDummy("dmy_land1").origin;
	m_ObjCenterPos.y = -m_ObjCenterPos.y;

	m_ObjAngle[0] = 0.f - 50.f;
	m_ObjAngle[1] = 44.f - 50.f;
	m_ObjAngle[2] = 88.f - 50.f;
	m_ObjAngle[3] = 126.f - 50.f;
	m_ObjAngle[4] = 154.f - 50.f;
	m_ObjAngle[5] = -28.f - 50.f;
	m_ObjAngle[6] = -45.f - 50.f;
	m_ObjAngle[7] = -164.f - 50.f;
	m_ObjAngle[8] = -125.f - 50.f;
	m_ObjAngle[9] = -86.f - 50.f;

	for (int _i = 0; _i < MAX_EARTH_OBJECT; _i++)
	{
		m_ObjectHeadNode[_i] = new CCNode();
		m_ObjectHeadNode[_i]->setPosition(ccp(m_ObjCenterPos.x, DESIGN_HEIGHT + m_ObjCenterPos.y));
		m_earth->addChild(m_ObjectHeadNode[_i]);
		m_ObjectHeadNode[_i]->release();

		m_Object[_i] = new SkelObject();
		m_Object[_i]->setSkelAnim("ui/channel_earth_8888.json");
		m_Object[_i]->playAnimation("land_"+StringConverter::toString(_i+1));
		m_Object[_i]->setPosition(ccp(0, 331.f));
		m_Object[_i]->setAnchorPoint(ccp(0.5f, 0.5f));
		m_ObjectHeadNode[_i]->addChild(m_Object[_i], 1);
		m_Object[_i]->release();

		m_ObjectHeadNode[_i]->setRotation(m_ObjAngle[_i]);
	}

	m_bIsMoveWave = false;
	m_earth->getSkel("skel_wave_stay")->playAnimation("wave_stay_start");
	m_earth->getSkel("skel_wave_stay")->appendAnimation("wave_stay_loop");
	m_earth->getSkel("skel_wave_move")->playAnimation("wave_move_end");

	//m_TopUi = new LobbyTopUiPanel();
	//m_TopUi->SetTopTitle(GameDataManager::getSingletonPtr()->GetUiState());
	//addChild(m_TopUi);
	//m_TopUi->release();
	//CCPoint _topUiPos = getDummy("dmy_channel_top").origin;
	//m_TopUi->setPosition(ccp(_topUiPos.x, -_topUiPos.y));
	//m_TopUi->UpdatePlayerInfo();
	//m_TopUi->getButton("sbtn_option_button")->getButtonSkelObject()->playAnimation("cancel_stay");

	//m_pTopSubUi = new LobbyChannelSubTopUiPanel();
	//addChild(m_pTopSubUi);
	//m_pTopSubUi->release();
	//m_pTopSubUi->setPosition(ccp(0, -69));
	//m_pTopSubUi->SetGameChannel(GameDataManager::getSingletonPtr()->m_SelectedGameKind);

	//m_LeftUi = new LobbyChannelLeftUiPanel();
	//addChild(m_LeftUi);
	//m_LeftUi->release();
	//m_LeftUi->setPosition(ccp(10.f, -97));

	m_BottomUi = new ChannelBottomUiPannel();
	addChild(m_BottomUi);
	m_BottomUi->release();
	CCPoint _bottomUiPos = getDummy("dmy_channel_position").origin;
	m_BottomUi->setPosition(ccp(_bottomUiPos.x, -_bottomUiPos.y));

	m_pTabMain = new Panel();
	m_pTabMain->construct(getMxmlPath() + "dmy_game_mod.mxml");
	CCPoint _TabUiPos = getDummy("dmy_game_mod").origin;
	m_pTabMain->setPositionX(_TabUiPos.x);
	m_pTabMain->setPositionY(-_TabUiPos.y);
	addChild(m_pTabMain);
	m_pTabMain->release();

	m_pTabMain->getImage("skel_update1")->setZOrder(15);
	m_pTabMain->getImage("skel_update2")->setZOrder(15);
	m_pTabMain->getImage("skel_update3")->setZOrder(15);
	m_pTabMain->getImage("skel_update4")->setZOrder(15);

	m_pTabMain->getImage("skel_update1")->setVisible(false);
	m_pTabMain->getImage("skel_update2")->setVisible(false);
	m_pTabMain->getImage("skel_update3")->setVisible(false);
	m_pTabMain->getImage("skel_update4")->setVisible(false);


	for (int _i = 0; _i < 4; _i++)
	{
		m_pTabPanel[_i] = new Panel();
		string _fileName = "dmy_game_button" + StringConverter::toString(_i + 1);
		m_pTabPanel[_i]->construct(getMxmlPath() + "dmy_game_button.mxml");
		CCPoint _btnPos = m_pTabMain->getDummy(_fileName).origin;
		m_pTabPanel[_i]->setPositionX(_btnPos.x);
		m_pTabPanel[_i]->setPositionY(-_btnPos.y);
		m_pTabMain->addChild(m_pTabPanel[_i]);
		m_pTabPanel[_i]->release();

		m_pTabPanel[_i]->getButton("sbtn_button")->setListener(this);

		m_pTabPanel[_i]->getLabel("txt_game_off_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pTabPanel[_i]->getLabel("txt_game_off")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pTabPanel[_i]->getLabel("txt_game_on_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pTabPanel[_i]->getLabel("txt_game_on")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		string _btnString = "";
		switch (_i)
		{
		case 0:
			_btnString = GameStringDepot::getSingletonPtr()->getString("TXT_SEVEN_POKER");
			m_pTabPanel[_i]->getButton("sbtn_button")->setName("tab_seven");
			break;
		case 1:
			_btnString = GameStringDepot::getSingletonPtr()->getString("TXT_HIGHLOW");
			m_pTabPanel[_i]->getButton("sbtn_button")->setName("tab_highlow");
			break;
		case 2:
			_btnString = GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI");
			m_pTabPanel[_i]->getButton("sbtn_button")->setName("tab_badugi");
			break;
		case 3:
			_btnString = GameStringDepot::getSingletonPtr()->getString("TXT_HOLDEM");
			m_pTabPanel[_i]->getButton("sbtn_button")->setName("tab_holdem");

			// uni\n텍사스홀덤 처리
			// 폰트 줄이고
			/*m_pTabPanel[_i]->getLabel("txt_game_off_under")->setFontSize(20);
			m_pTabPanel[_i]->getLabel("txt_game_off")->setFontSize(20);
			m_pTabPanel[_i]->getLabel("txt_game_on_under")->setFontSize(20);
			m_pTabPanel[_i]->getLabel("txt_game_on")->setFontSize(20);*/
			//// 포지션 올리고
			//m_pTabPanel[_i]->getLabel("txt_game_off_under")->setPositionY(m_pTabPanel[_i]->getLabel("txt_game_off_under")->getPositionY() + 5);
			//m_pTabPanel[_i]->getLabel("txt_game_off")->setPositionY(m_pTabPanel[_i]->getLabel("txt_game_off")->getPositionY() + 5);
			//m_pTabPanel[_i]->getLabel("txt_game_on_under")->setPositionY(m_pTabPanel[_i]->getLabel("txt_game_on_under")->getPositionY() + 5);
			//m_pTabPanel[_i]->getLabel("txt_game_on")->setPositionY(m_pTabPanel[_i]->getLabel("txt_game_on")->getPositionY() + 5);
			break;
		}

		m_pTabPanel[_i]->getLabel("txt_game_off_under")->setString(_btnString.c_str());
		m_pTabPanel[_i]->getLabel("txt_game_off")->setString(_btnString.c_str());
		m_pTabPanel[_i]->getLabel("txt_game_on_under")->setString(_btnString.c_str());
		m_pTabPanel[_i]->getLabel("txt_game_on")->setString(_btnString.c_str());
	}

	SelectGameMode((GameKind)(GameDataManager::getSingletonPtr()->getGameKind()), true);
}

void ChannelMainPannel::InitImage()
{
	SetFirstViewCell();

	m_BottomUi->UpdateCellScale();
	SetCenterCell();

	//float _moveAngle = 360.f / (float)m_BottomUi->m_totalChannelCount;

	//m_RootAngle = -_moveAngle * _index;
	//RotateObject(m_RootAngle);

	//else if (_moveOffset < -CHANNEL_CELL_WIDTH * 2.f)
	//{
	//	int _page = _moveOffset / CHANNEL_CELL_WIDTH;
	//	int _offset = _moveOffset - (CHANNEL_CELL_WIDTH*_page);

	//	m_BottomUi->m_curChannelIndex = _page;
	//	m_BottomUi->UpdateChannelCell();
	//	m_BottomUi->m_pChannelView->setContentOffset(ccp(-_offset, 0.f));
	//}
	//else
	//{
	//	if (_moveOffset == 0)
	//	{
	//		m_BottomUi->m_curChannelIndex = 0;
	//		m_BottomUi->UpdateChannelCell();
	//		m_BottomUi->m_pChannelView->setContentOffset(ccp(0, 0.f));
	//	}
	//	else
	//	{
	//		int _page = _moveOffset / CHANNEL_CELL_WIDTH;
	//		int _offset = _moveOffset - (CHANNEL_CELL_WIDTH*_page);

	//		m_BottomUi->m_curChannelIndex = _page;
	//		m_BottomUi->UpdateChannelCell();
	//		m_BottomUi->m_pChannelView->setContentOffset(ccp(_offset, 0.f));
	//	}
	//}
}

void ChannelMainPannel::SetFirstViewCell()
{
	int _index = GetFristEnableCell();
	float _moveOffset = _index*CHANNEL_CELL_WIDTH;

	if (_moveOffset > 553.f + CHANNEL_CELL_WIDTH)
	{
		int _page = (_moveOffset - (553.f + CHANNEL_CELL_WIDTH)) / CHANNEL_CELL_WIDTH;
		int _offset = _moveOffset - (CHANNEL_CELL_WIDTH * _page);

		m_BottomUi->m_curChannelIndex = _page;
		m_BottomUi->UpdateChannelCell();
		m_BottomUi->m_pChannelView->setContentOffset(ccp(-_offset, 0.f));
	}
	else
	{
		if (_moveOffset == 0)
		{
			m_BottomUi->m_curChannelIndex = 0;
			m_BottomUi->UpdateChannelCell();
			m_BottomUi->m_pChannelView->setContentOffset(ccp(0, 0.f));
		}
		else
		{
			m_BottomUi->m_curChannelIndex = 0;
			m_BottomUi->UpdateChannelCell();
			m_BottomUi->m_pChannelView->setContentOffset(ccp(-_moveOffset, 0.f));
		}
	}

	m_offset = m_BottomUi->m_pChannelView->getContentOffset();

	int _cellIndex = GetSelectedCellIndex();
	SetDestination(GetCityId(_cellIndex));
}

void ChannelMainPannel::initButton()
{
	
}


bool ChannelMainPannel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCRect boudning = CCRectMake(0,0,
		getContentSize().width, getContentSize().height);
	CCPoint point = convertTouchToNodeSpace(pTouch);
	if (boudning.containsPoint(point)) {
		m_bCancelTouch = false;
		m_bAutoMove = false;
		m_bTouchEnd = false;
		m_moveG = 0.f;
		m_bMoveAccel = false;
		m_MovePoint = 0.f;
		return true;
	}

	return false;
}


void ChannelMainPannel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//if (pTouch->getLocation().y > 260 || pTouch->getLocation().y < 10)
	//{
	//	SetMoveShipWave(false);
	//	return;
	//}

	if (m_bTouchEnd == true)
		return;

	m_moveG = pTouch->getPreviousLocation().x - pTouch->getLocation().x;
	
	if (m_moveG > CHANNEL_CELL_WIDTH)
		m_moveG = CHANNEL_CELL_WIDTH;
	if (m_moveG < -CHANNEL_CELL_WIDTH)
		m_moveG = -CHANNEL_CELL_WIDTH;
	
	float _moveLen = pTouch->getStartLocation().x - pTouch->getLocation().x;

	int _cellCount = m_BottomUi->m_totalChannelCount;
	if (_cellCount > CHANNEL_CELL_MAX)
		_cellCount = CHANNEL_CELL_MAX;

	float _maxOffset = -CHANNEL_CELL_WIDTH * (_cellCount - 1);

	//if ((m_offset.x == 0 && m_moveG < 0) || (m_offset.x <= _maxOffset && m_moveG > 0))
	//{
	//	return;
	//}

	if (abs(_moveLen) > 10.f)
	{
		m_bCancelTouch = true;
	}

	//if (abs(m_moveG) > CHANNEL_CELL_WIDTH / 5.f)
	//{
	//	UpdateChannelCellMoveBy(m_moveG/4.f);

	//	m_bMoveAccel = true;
	//	m_MovePoint = 0.f;
	//	m_bTouchEnd = true;
	//	return;
	//}

	//if (abs(_moveLen) > CHANNEL_CELL_WIDTH / 2)
	//{
	//	m_bTouchEnd = true;

	//	int _i = -m_offset.x / CHANNEL_CELL_WIDTH;
	//	if (_moveLen < 0)
	//	{
	//		if (m_BottomUi->m_catchCenterIndex == 0)
	//			return;

	//		m_MovePoint = CHANNEL_CELL_WIDTH * (_i - 1) + m_offset.x;
	//	}
	//	else
	//	{
	//		m_MovePoint = CHANNEL_CELL_WIDTH * (_i + 1) + m_offset.x;
	//	}		

	//	m_bAutoMove = true;
	//	return;
	//}

	UpdateChannelCellMoveBy(m_moveG);
}


void ChannelMainPannel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bTouchEnd == true)
		return;

	m_bTouchEnd = true;
	
	float _moveLen = pTouch->getStartLocation().x - pTouch->getLocation().x;

	//CheckAutoMove(_moveLen);
	UpdateChannelCellMoveBy(m_moveG);
	m_bMoveAccel = true;
	m_MovePoint = 0.f;
	m_bTouchEnd = true;

	if (m_bCancelTouch == true)
	{
		return;
	}
	
	for (int _i = 0; _i < CHANNEL_CELL_MAX; _i++)
	{
		if (m_BottomUi->m_totalChannelCount <= _i)
			continue;

		ChannelCell* _pCell = m_BottomUi->m_pChannel[_i];
		if (_pCell == nullptr)
			continue;

		if (_pCell->m_btnChannel->hasCollided(_pCell->m_btnChannel->convertToNodeSpace(pTouch->getLocation())))
		{
			W_ChannelInfo* _pInfo = m_BottomUi->getChannelInfo(_i);
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
			return;

		}
	}

	//if (_moveLen == 0)
	//	return;

	//if (m_offset.x >= 0.f && _moveLen <= 0)
	//{
	//	return;
	//}

	//if (m_BottomUi->m_totalChannelCount == 1)
	//{
	//	m_bAutoMove = false;
	//	SetCenterCell();
	//}
	//else
	//{
	//	CheckAutoMove(_moveLen);
	//}
}

void ChannelMainPannel::CheckAutoMove(float _moveLen)
{
	m_bTouchEnd = true;
	m_bMoveAccel = false;

	if (abs(_moveLen) <= 10.f)
		return;

	int _i = -m_offset.x / CHANNEL_CELL_WIDTH;
	if (_moveLen >= 0)
	{
		if (m_BottomUi->m_catchCenterIndex == 0)
			return;

		m_MovePoint = CHANNEL_CELL_WIDTH * (_i - 1) + m_offset.x;
	}
	else
	{
		m_MovePoint = CHANNEL_CELL_WIDTH * (_i + 1) + m_offset.x;
	}

	m_bAutoMove = true;
}

void ChannelMainPannel::UpdateChannelCellMoveBy(float _moveX)
{
	if (m_BottomUi->m_totalChannelCount == 0)
	{
		return;
	}

	m_offset = m_BottomUi->m_pChannelView->getContentOffset();

	if (_moveX < 0 && m_offset.x == 0)
	{
		return;
	}

	float _maxMoveX = (CHANNEL_CELL_WIDTH * m_BottomUi->m_totalChannelCount);
	
	if (m_offset.x >= _moveX && _moveX < 0.f)
	{
		m_offset.x = 0.f;
	}
	else
	{
		m_offset.x -= _moveX;
	}
	
	if (m_offset.x < -553 - CHANNEL_CELL_WIDTH && _moveX > 0 && m_BottomUi->m_curChannelIndex + CHANNEL_CELL_MAX < m_BottomUi->m_totalChannelCount)
	{
		m_BottomUi->m_curChannelIndex ++;
		m_offset.x += CHANNEL_CELL_WIDTH;
		m_BottomUi->UpdateChannelCell();
	}

	if (m_offset.x > -318 - CHANNEL_CELL_WIDTH && _moveX < 0 && m_BottomUi->m_curChannelIndex >= 1)
	{
		m_BottomUi->m_curChannelIndex--;
		m_offset.x -= CHANNEL_CELL_WIDTH;
		m_BottomUi->UpdateChannelCell();
	}
	
	
	m_BottomUi->m_pChannelView->setContentOffset(m_offset, false);
	//int _index = GetSelectedCellIndex();
	//SetDestination(GetCityId(_index), true);

	m_BottomUi->UpdateCellScale();
}

void ChannelMainPannel::resume()
{
}

void ChannelMainPannel::onClicked(const string& name)
{
	if (name == "tab_seven")
	{
		SelectGameMode(GAMEKIND_7POKER);
	}

	if (name == "tab_highlow")
	{
		SelectGameMode(GAMEKIND_HIGH_LOW);
	}

	if (name == "tab_badugi")
	{
		SelectGameMode(GAMEKIND_BADUKI);
	}

	if (name == "tab_holdem")
	{
		SelectGameMode(GAMEKIND_HOLDEM);
	}
}

void ChannelMainPannel::update(float dt)
{
	if (m_bActionRotate)
	{
		//float _moveG = (m_DstAngle - m_RootAngle) * dt * 4.f;
		
		float _moveG = 180.f * dt;
		if (m_DstAngle < m_RootAngle)
			_moveG = -180.f * dt;

		float _moveAngle = m_RootAngle + _moveG;

		if (m_RootAngle > m_DstAngle)
		{
			if (_moveAngle <= m_DstAngle)
			{
				_moveAngle = m_DstAngle;
				m_bActionRotate = false;

				//m_BottomUi->getSkel("skel_light")->setVisible(true);
			}
		}
		else
		{
			if (_moveAngle >= m_DstAngle)
			{
				_moveAngle = m_DstAngle;
				m_bActionRotate = false;

				//m_BottomUi->getSkel("skel_light")->setVisible(true);
			}
		}

		m_earth->getSkel("skel_cruise")->setFlipX(_moveG < 0.f);
		m_earth->getSkel("skel_wave_stay")->setFlipX(_moveG < 0.f);
		m_earth->getSkel("skel_wave_move")->setFlipX(_moveG < 0.f);

		if (_moveG > 1.f || _moveG < -1.f)
		{
			SetMoveShipWave(true);
		}
		else
		{
			SetMoveShipWave(false);
		}

		RotateObject(_moveAngle);
		m_RootAngle = _moveAngle;

	}

	if (m_bMoveAccel == true)
	{
		int _cellCount = m_BottomUi->m_totalChannelCount;
		if (_cellCount > CHANNEL_CELL_MAX)
			_cellCount = CHANNEL_CELL_MAX;

		float _maxOffset = -CHANNEL_CELL_WIDTH * (_cellCount - 1);

		if ((m_offset.x == 0 && m_moveG < 0) || (m_offset.x <= _maxOffset && m_moveG > 0))
		{
			SetMoveStop();
			m_bAutoMove = true;
			m_MovePoint = 0;
			return;
		}

		float _endMove = m_moveG * 20.f;
		if (_endMove == 0.f)
		{
			SetMoveStop();
			AutoMoveUpdate();
			return;
		}

		float _move = m_moveG * dt * (1.f - (m_MovePoint / _endMove)) * 20.f;
		int _nMove = _move * 100.f;
		_move = (float)_nMove / 100.f;

		if (_nMove == 0)
		{
			SetMoveStop();
			AutoMoveUpdate();
			SetMoveShipWave(false);
			return;
		}

		m_MovePoint += _move;

	
		if (m_moveG < 0)
		{
			if (m_MovePoint <= _endMove)
			{
				_move = m_MovePoint - _endMove;
				SetMoveStop();
			}
		}
		else
		{
			if (m_MovePoint >= _endMove)
			{
				_move = m_MovePoint - _endMove;
				SetMoveStop();
			}
		}

		if (m_offset.x > 0)
		{
			SetMoveStop();
		}

		int _totalcount = m_BottomUi->m_totalChannelCount;
		if (CHANNEL_CELL_MAX <= _totalcount)
		{
			_totalcount = CHANNEL_CELL_MAX;
		}

		//if (m_offset.x <= (-CHANNEL_CELL_WIDTH * _totalcount) + 4))
		//{
		//	SetMoveStop();
		//}

		if (abs(_move) < CHANNEL_CELL_WIDTH * 2.f * dt || m_bAutoMove)
		{
			SetMoveStop();
			AutoMoveUpdate();

			//if (_move >= 0)
			//{
			//	if (m_BottomUi->m_catchCenterIndex == 0)
			//		return;
			//	m_MovePoint = CHANNEL_CELL_WIDTH * _i + m_offset.x;
			//}
			//else
			//{
			//	m_MovePoint = CHANNEL_CELL_WIDTH * (_i + 1) + m_offset.x;
			//}

			//m_bAutoMove = true;
			return;
		}

		UpdateChannelCellMoveBy(_move);

		return;
	}

	if (m_bAutoMove == true)
	{
		float _autoMove = 0.f;
		if (m_MovePoint > 0)
		{
			_autoMove = CHANNEL_CELL_WIDTH * 10.f * dt;
			if (m_MovePoint - _autoMove < 0)
			{
				_autoMove = m_MovePoint;
				m_MovePoint = 0;
			}
			else
			{
				m_MovePoint -= _autoMove;
			}
		}
		else
		{
			_autoMove = -CHANNEL_CELL_WIDTH * 10.f * dt;
			if (m_MovePoint - _autoMove > 0)
			{
				_autoMove = m_MovePoint;
				m_MovePoint = 0;
			}
			else
			{
				m_MovePoint -= _autoMove;
			}
		}

		UpdateChannelCellMoveBy(_autoMove);

		if (m_MovePoint == 0)
		{
			m_bAutoMove = false;
			SetCenterCell();
		}

	}
}

void ChannelMainPannel::AutoMoveUpdate()
{
	int _i = -m_offset.x / CHANNEL_CELL_WIDTH;

	int _diff = (int)m_offset.x % (int)CHANNEL_CELL_WIDTH;

	if (abs(_diff) < CHANNEL_CELL_WIDTH / 2.f)
	{
		/*_move = -abs(_move);*/
		m_MovePoint = CHANNEL_CELL_WIDTH * _i + m_offset.x;
	}
	else
	{
		m_MovePoint = CHANNEL_CELL_WIDTH * (_i + 1) + m_offset.x;
	}
}

void ChannelMainPannel::SetCenterCell()
{
	if (m_BottomUi->m_catchCenterIndex == -1 || m_BottomUi->m_catchCenterIndex >= CHANNEL_CELL_MAX)
		return;

	m_BottomUi->SetCenterCell();

	int _index = m_BottomUi->m_catchCenterIndex;
	SetDestination(GetCityId(_index), true);
}

void ChannelMainPannel::ReleaseCenterCell()
{
	m_BottomUi->ReleseCenterCell();
}


void ChannelMainPannel::SetMoveStop()
{
	m_bMoveAccel = false;
	m_moveG = 0.f;
	m_MovePoint = 0.f;
	m_bAutoMove = true;
}

bool ChannelMainPannel::handling(STCMD &stCmd)
{
	return false;
}

void ChannelMainPannel::RotateObject(float _angle)
{
	for (int _i = 0; _i < MAX_EARTH_OBJECT; _i++)
	{
		float _ChangeAngle = _angle + m_ObjAngle[_i];
		m_ObjectHeadNode[_i]->setRotation(_ChangeAngle);
	}
}

int ChannelMainPannel::GetFristEnableCell()
{
	if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_7POKER)
	{
		int _size = GameDataManager::getSingletonPtr()->m_p7PokerChannelList.size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ChannelInfo* _pInfo = GameDataManager::getSingletonPtr()->m_p7PokerChannelList[_i];
			if (_pInfo->overmoney() == 0)
			{
				if (_pInfo->undermoney() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
				{
					return _i;
				}

			}
			else if (_pInfo->undermoney() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney
				&& _pInfo->overmoney() >= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
			{
				return _i;
			}
		}
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW)
	{
		int _size = GameDataManager::getSingletonPtr()->m_pHighLowChannelList.size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ChannelInfo* _pInfo = GameDataManager::getSingletonPtr()->m_pHighLowChannelList[_i];
			if (_pInfo->overmoney() == 0)
			{
				if (_pInfo->undermoney() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
				{
					return _i;
				}

			}
			else if (_pInfo->undermoney() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney
				&& _pInfo->overmoney() >= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
			{
				return _i;
			}
		}
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		int _size = GameDataManager::getSingletonPtr()->m_pBadukiChannelList.size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ChannelInfo* _pInfo = GameDataManager::getSingletonPtr()->m_pBadukiChannelList[_i];
			if (_pInfo->overmoney() == 0)
			{
				if (_pInfo->undermoney() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
				{
					return _i;
				}

			}
			else if (_pInfo->undermoney() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney
				&& _pInfo->overmoney() >= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
			{
				return _i;
			}
		}
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM)
	{
		int _size = GameDataManager::getSingletonPtr()->m_pHoldemChannelList.size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_ChannelInfo* _pInfo = GameDataManager::getSingletonPtr()->m_pHoldemChannelList[_i];
			if (_pInfo->overmoney() == 0)
			{
				if (_pInfo->undermoney() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
				{
					return _i;
				}

			}
			else if (_pInfo->undermoney() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney
				&& _pInfo->overmoney() >= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
			{
				return _i;
			}
		}
	}


	return 0;
}

void ChannelMainPannel::SetMoveShipWave(bool _visible)
{

	if (m_bIsMoveWave == _visible)
		return;

	if (m_bIsMoveWave == false && _visible == true)
	{
		m_bIsMoveWave = true;
		m_earth->getSkel("skel_wave_move")->playAnimation("wave_move_start");
		m_earth->getSkel("skel_wave_move")->appendAnimation("wave_move_loop");
		m_earth->getSkel("skel_wave_stay")->playAnimation("wave_stay_end");

	}
	
	if (m_bIsMoveWave == true && _visible == false)
	{
		m_bIsMoveWave = false;
		m_earth->getSkel("skel_wave_stay")->playAnimation("wave_stay_start");
		m_earth->getSkel("skel_wave_stay")->appendAnimation("wave_stay_loop");
		m_earth->getSkel("skel_wave_move")->playAnimation("wave_move_end");
	}
		

}

int ChannelMainPannel::GetCityId(int _cellIndex)
{
	int _cityId = CityName::FREE;

	if (m_BottomUi == nullptr)
		return _cityId;

	ChannelCell* _pCell = m_BottomUi->m_pChannel[_cellIndex];
	if (_pCell == nullptr)
		return _cityId;

	int _grade = _pCell->m_CellInfo->grade() % 20;
	
	switch (_grade)
	{
	case 1:
		_cityId = CityName::KANGWOON;
		break;
	case 2:
	case 3:
		_cityId = CityName::SYDNEY;
		break;
	case 4:
	case 5:
		_cityId = CityName::ATLANTA;
		break;
	case 6:
	case 7:
		_cityId = CityName::PARIS;
		break;
	case 8:
	case 9:
		_cityId = CityName::MAKAO;
		break;
	case 10:
		_cityId = CityName::LASVEGAS;
		break;
	case 18:
	case 19:
		_cityId = CityName::FRIEND;
		break;
	case 20:
		_cityId = CityName::FREE;
		break;
	}

	return _cityId;
}


void ChannelMainPannel::SetDestination(int _cityName, bool _action)
{
	float _angle = 0.f;
	switch (_cityName)
	{
	case CityName::FREE:
		_angle = m_ObjAngle[7];
		break;
	case CityName::KANGWOON:
		_angle = m_ObjAngle[2];
		break;
	case CityName::SYDNEY:
		_angle = m_ObjAngle[1];
		break;
	case CityName::ATLANTA:
		_angle = m_ObjAngle[0];
		break;
	case CityName::PARIS:
		_angle = m_ObjAngle[6];
		break;
	case CityName::MAKAO:
		_angle = m_ObjAngle[9];
		break;
	case CityName::LASVEGAS:
		_angle = m_ObjAngle[8];
		break;
	case CityName::FRIEND:
		_angle = m_ObjAngle[7];
		break;
	}

	if (_action == true)
	{
		if (m_DstAngle != _angle)
		{
			m_DstAngle = _angle;
			m_bActionRotate = true;
		}
		else
		{
			//m_BottomUi->getSkel("skel_light")->setVisible(true);
		}
	}
	else
	{
		RotateObject(_angle);
		m_RootAngle = _angle;
		m_DstAngle = _angle;
		//m_BottomUi->getSkel("skel_light")->setVisible(true);
	}

}

int ChannelMainPannel::GetSelectedCellIndex()
{
	int _index = m_offset.x / CHANNEL_CELL_WIDTH;
	_index = -_index;

	if (_index < 0)
		_index = 0;

	if (_index > CHANNEL_CELL_MAX - 1)
		_index = CHANNEL_CELL_MAX - 1;

	return _index;
}

void ChannelMainPannel::UpdateChannelState()
{
	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		getSkel("skel_space_point")->playAnimation("space_seven");
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		getSkel("skel_space_point")->playAnimation("space_highlow");
		break;
	case GameKind::GAMEKIND_BADUKI:
		getSkel("skel_space_point")->playAnimation("space_badugi");
		break;
	case GameKind::GAMEKIND_HOLDEM:
		getSkel("skel_space_point")->playAnimation("space_texas");
		break;
	}
}


void ChannelMainPannel::SetTabButtonActivation(int _index, bool _active, int _zoder)
{
	string _frameName = "";
	bool isPossible = true;
	switch (_index)
	{
	case 0:
		_frameName = "button_seven_";
		isPossible = isPossibleOpen(GAMEKIND_7POKER);
		break;
	case 1:
		_frameName = "button_highlow_";
		isPossible = isPossibleOpen(GAMEKIND_HIGH_LOW);
		break;
	case 2:
		_frameName = "button_badugi_";
		isPossible = isPossibleOpen(GAMEKIND_BADUKI);
		break;
	case 3:
		_frameName = "button_texas_";
		isPossible = isPossibleOpen(GAMEKIND_HOLDEM);
		break;
	}

	if (_active)
		_frameName += "on";
	else
		_frameName += "off";

	m_pTabPanel[_index]->getButton("sbtn_button")->getButtonSkelObject()->playAnimation(_frameName);
	m_pTabPanel[_index]->setZOrder(_zoder);

	m_pTabPanel[_index]->getLabel("txt_game_off_under")->setVisible(_active == false);
	m_pTabPanel[_index]->getLabel("txt_game_off")->setVisible(_active == false);
	m_pTabPanel[_index]->getLabel("txt_game_on_under")->setVisible(_active == true);
	m_pTabPanel[_index]->getLabel("txt_game_on")->setVisible(_active == true);


	if (!isPossible) {
		m_pTabPanel[_index]->getButton("sbtn_button")->setGrayscale(true);
		m_pTabPanel[_index]->getButton("sbtn_button")->setEnable(false);
		string updateLabel = "skel_update" + StringConverter::toString(_index + 1);
		m_pTabMain->getImage(updateLabel)->setVisible(true);
	}
}

void ChannelMainPannel::SelectGameMode(GameKind _gameKind, bool _action)
{
	if (m_gameKind == _gameKind && m_gameKind == GameDataManager::getSingletonPtr()->getGameKind() && _action == false)
		return;

	m_gameKind = _gameKind;
	GameDataManager::getSingleton().setGameKind(m_gameKind);	
	switch (_gameKind)
	{
	case GAMEKIND_NO:
		break;
	case GAMEKIND_7POKER:
		SetTabButtonActivation(0, true, 3);
		SetTabButtonActivation(1, false, 2);
		SetTabButtonActivation(2, false, 1);
		SetTabButtonActivation(3, false, 0);
		break;
	case GAMEKIND_HIGH_LOW:
		SetTabButtonActivation(0, false, 2);
		SetTabButtonActivation(1, true, 3);
		SetTabButtonActivation(2, false, 2);
		SetTabButtonActivation(3, false, 1);
		break;
	case GAMEKIND_BADUKI:
		SetTabButtonActivation(0, false, 1);
		SetTabButtonActivation(1, false, 2);
		SetTabButtonActivation(2, true, 3);
		SetTabButtonActivation(3, false, 2);
		break;
	case GAMEKIND_HOLDEM:
		SetTabButtonActivation(0, false, 0);
		SetTabButtonActivation(1, false, 1);
		SetTabButtonActivation(2, false, 2);
		SetTabButtonActivation(3, true, 3);
		break;
	case GAMEKIND_ORIGINAL_HOLDEM:
		break;
	case GAMEKIND_3POKER:
		break;
	default:
		break;
	}

	m_BottomUi->InitChannelList();
	InitImage();

	UpdateChannelState();
}

void ChannelMainPannel::UpdateGameMode()
{
	if (m_gameKind < GameKind::GAMEKIND_7POKER)
		m_gameKind = GameKind::GAMEKIND_7POKER;

	if (m_gameKind > GameKind::GAMEKIND_HOLDEM)
		m_gameKind = GameKind::GAMEKIND_HOLDEM;

	SelectGameMode((GameKind)m_gameKind, true);
}

void ChannelMainPannel::onRefresh()
{
	UpdateGameMode();
	setVisibleChannelCell(true);
}

void ChannelMainPannel::setVisibleChannelCell(bool visible)
{
	if (m_BottomUi)
		m_BottomUi->setVisible(visible);

	if (m_pTabMain)
		m_pTabMain->setVisible(visible);
}

bool ChannelMainPannel::isPossibleOpen(GameKind gameKind)
{
	for (int i = 0; GameDataManager::getSingleton().GetGameDataPtr()->gamekinddata_size(); i++)
	{
		if (GameDataManager::getSingleton().GetGameDataPtr()->gamekinddata(i).gamekind() == gameKind)
			return GameDataManager::getSingleton().GetGameDataPtr()->gamekinddata(i).isopen();
	}
	return false;
}

void ChannelMainPannel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}