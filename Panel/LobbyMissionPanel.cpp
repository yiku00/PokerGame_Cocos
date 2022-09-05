#include "pch.h"
#include "LobbyMissionPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "SimplePopupPanel.h"
#include "GameStringDepot.h"
#include "PokerChipWidget.h"
#include "LobbyUIPanel.h"
#include "PokerChipWidget.h"
#include "LobbyUIPanel.h"
#include "PokerShopHelper.h"
#include "PokerResourceHelper.h"

LobbyMissionPanel::LobbyMissionPanel()
{
	m_TapIndex = 0;
	m_CellIndex = 0;
	mLoginProcess = false;

	m_pMissionListView = nullptr;
	m_pMissionListContainer = nullptr;

	for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
	{
		m_ListCell[_i] = nullptr;
		m_CellBtnPanel[_i] = nullptr;
	}

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);

	m_ViewDataIndex = 10;
}

LobbyMissionPanel::~LobbyMissionPanel()
{
	//destruct();
}

void LobbyMissionPanel::InitPanel()
{
//	Panel* panel = addMouseBlockPanel(this, true);
//	panel->setContentSize(CCSize(DESIGN_WIDTH, DESIGN_HEIGHT - 72));
	construct(getMxmlPath() + "dmy_mission.mxml");
	
	mCellSize = getDummy("dmy_m_bar1").size;

	//m_ShowPosition = getPosition();
	//m_HidePosition = m_ShowPosition - ccp(0, getDummy("dmy_mission").size.height);

	//setPosition(m_HidePosition);
}

void LobbyMissionPanel::InitImage()
{
	getLabel("txt_tab1_empty")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_tab1_mission")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_tab1_mission_now")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_tab1_mission_max")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_mission_info")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//m_MissionTitleLabel = getSkel("skel_mission_title");
	//m_MissionTitleMark = getSkel("skel_mission_mark");
	//m_MissionTitleBg = getSkel("skel_title_back");
	//m_ShadowBg = getSkel("skel_mission_title_black");
	
	//m_MissionTitleLabel->setVisible(false);
	//m_MissionTitleMark->setVisible(false);
	//m_MissionTitleBg->setVisible(false);
	//m_ShadowBg->setVisible(false);

	m_MissionCount = getLabel("txt_tab1_mission_now");
	m_MissionMaxCount = getLabel("txt_tab1_mission_max");
	getLabel("txt_tab1_mission")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_COMPLETE_MISSION_UNIT").c_str());
	getLabel("txt_tab1_empty")->setString(GameStringDepot::getSingletonPtr()->getString("NO_MISSION_DESC").c_str());
}

void LobbyMissionPanel::initButton()
{
	CCPoint _tapPos[2];
	_tapPos[0] = getDummy("dmy_button_tab1").origin;
	_tapPos[1] = getDummy("dmy_button_tab2").origin;
	string _tapTxt[2];
	_tapTxt[0] = GameStringDepot::getSingletonPtr()->getString("TXT_DAILY_MISSION_UNIT");
	_tapTxt[1] = GameStringDepot::getSingletonPtr()->getString("TXT_EVENT_MISSION_UNIT");

	for (int _i = 0; _i < 2; _i++)
	{
		m_TapBtnPanel[_i] = new Panel();
		m_TapBtnPanel[_i]->construct(getMxmlPath() + "dmy_button_tab.mxml");
		m_TapBtnPanel[_i]->setPositionX(_tapPos[_i].x);
		m_TapBtnPanel[_i]->setPositionY(-_tapPos[_i].y);
		addChild(m_TapBtnPanel[_i]);
		m_TapBtnPanel[_i]->release();

		Button* _TapBtn = m_TapBtnPanel[_i]->getButton("sbtn_button");
		_TapBtn->setListener(this);
		_TapBtn->setName("btn_tap" + StringConverter::toString(_i + 1));

		m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setString(_tapTxt[_i].c_str());
		m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setString(_tapTxt[_i].c_str());
		if (_i == 0)
		{
			_TapBtn->setSkelAnimation("tab_on");
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setVisible(false);
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setVisible(true);
		}
		else
		{
			_TapBtn->setSkelAnimation("tab_off");
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setVisible(true);
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setVisible(false);
		}
	}

	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_MISSION_DAILY);
		m_TapBtnPanel[0]->addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(m_TapBtnPanel[0]->getImage("dmy_notification_icon")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}

	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_MISSION_EVENT);
		m_TapBtnPanel[1]->addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(m_TapBtnPanel[1]->getImage("dmy_notification_icon")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}	
}


bool LobbyMissionPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (pTouch->getLocation().y >= DESIGN_HEIGHT - 72.f)
		return false;

	if (pTouch->getLocation().x < 175.f)
		return false;

	m_bMovingCell = false;
	m_fMoveG = 0.f;	
	m_bTouchCancel = false;
	cellTouchStart(pTouch->getLocation());
	return true;	
}


void LobbyMissionPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	Panel::ccTouchMoved(pTouch, pEvent);

	CCPoint _startTouch = pTouch->getStartLocationInView();
	CCPoint _moveTouch = pTouch->getLocationInView();

	float _defPos = abs(_startTouch.y - _moveTouch.y);

	if (_defPos > 10.f && m_bTouchCancel == false)
	{
		m_bTouchCancel = true;
		cellTouchCancel(pTouch->getLocation());
	}

	if (m_pMissionListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pMissionListView->getContentOffset();
	int _size = 0;
	if (m_TapIndex == 0)
	{
		_size = GameDataManager::getSingletonPtr()->m_pQuestDailyList.size();
	}
	else
	{
		_size = GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.size();
		//_size = GameDataManager::getSingletonPtr()->m_EventList.size();
	}
	int _moveV = pTouch->getPreviousLocation().y - pTouch->getLocation().y;
	m_fMoveG = _moveV;
	if (_moveV > 0)
	{
		if (m_fMoveG > mCellSize.height)
		{
			m_fMoveG = mCellSize.height;
		}
	}
	else if (_moveV < 0)
	{
		if (m_fMoveG < -mCellSize.height)
		{
			m_fMoveG = -mCellSize.height;
		}
	}

	if (_size <= MISSION_CELL_MAX)	//셀 수가 MAX보다 많고
	{
		m_pMissionListView->setContentOffset(_offSetPoint - ccp(0, _moveV));
		return;
	}

	bool _bMove = false;
	if (_moveV > 0)
	{
		float _maxMove = -mCellSize.height * 2.5f;
		if (_offSetPoint.y <= _maxMove)
		{
			if (m_CellIndex > 0)
			{
				m_CellIndex--;
				m_pMissionListView->setContentOffset(_offSetPoint + ccp(0, mCellSize.height));
				for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
				{
					if (m_TapIndex == 0)
						UpdateMissionCell(_i, _size - MISSION_CELL_MAX - m_CellIndex + _i);
					else if (m_TapIndex == 1)
						UpdateEventCell(_i, _size - MISSION_CELL_MAX - m_CellIndex + _i);
				}
				_bMove = true;
			}
		}
	}
	else if (_moveV < 0)
	{
		float _minMove = -mCellSize.height;
		if (_offSetPoint.y >= _minMove)
		{
			if (m_CellIndex + MISSION_CELL_MAX < _size)
			{
				m_CellIndex++;
				m_pMissionListView->setContentOffset(_offSetPoint - ccp(0, mCellSize.height));
				for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
				{
					if (m_TapIndex == 0)
						UpdateMissionCell(_i, _size - MISSION_CELL_MAX - m_CellIndex + _i);
					else if (m_TapIndex == 1)
						UpdateEventCell(_i, _size - MISSION_CELL_MAX - m_CellIndex + _i);
				}
				_bMove = true;
			}
		}
	}

	if (_bMove == false)
	{
		m_pMissionListView->setContentOffset(_offSetPoint - ccp(0, _moveV));
	}
}


void LobbyMissionPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	Panel::ccTouchEnded(pTouch, pEvent);

	if (m_bTouchCancel == true)
	{
		m_bMovingCell = true;
		return;
	}
	m_fMoveG = 0.f;

	CCPoint _startTouch = pTouch->getStartLocationInView();
	CCPoint _EndTouch = pTouch->getLocationInView();

	float _defPos = abs(_startTouch.y - _EndTouch.y);

	if (_defPos <= 10.f)
	{
		cellTouch(pTouch->getLocation());
	}
}

void LobbyMissionPanel::resume()
{
}

void LobbyMissionPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (strncmp("GetBonusButton", name.c_str(), 14) == 0)
	{
		int _index = nxExtractInt(name, "GetBonusButton");
		if (GameDataManager::getSingletonPtr()->m_pQuestDailyList[_index]->has_seq())
		{
			int64 _questSeq = GameDataManager::getSingletonPtr()->m_pQuestDailyList[_index]->seq();
			int _type = GameDataManager::getSingletonPtr()->m_pQuestDailyList[_index]->questtype();
			// 아래 함수에 타입 값 추가해야 겠구만
			WebService::getSingletonPtr()->_sendQuestUpdateReq(_questSeq, _type);
		}
	}

	if (strncmp("GetEventBonusButton", name.c_str(), 19) == 0)
	{
		int _index = nxExtractInt(name, "GetEventBonusButton");
		if (GameDataManager::getSingletonPtr()->m_pQuestWeeklyList[_index]->has_seq())
		{
			int64 _questSeq = GameDataManager::getSingletonPtr()->m_pQuestWeeklyList[_index]->seq();
			int _type = GameDataManager::getSingletonPtr()->m_pQuestWeeklyList[_index]->questtype();
			// 아래 함수에 타입 값 추가해야 겠구만
			WebService::getSingletonPtr()->_sendQuestUpdateReq(_questSeq, _type);
		}
	}
	/*if (strncmp("GetEventBonusButton", name.c_str(), 19) == 0)
	{
		int _index = nxExtractInt(name, "GetEventBonusButton");
		if (GameDataManager::getSingletonPtr()->m_EventList[_index]->has_eventid())
		{
			int32 _eventId = GameDataManager::getSingletonPtr()->m_EventList[_index]->eventid();
			WebService::getSingletonPtr()->_sendEventListUpdateReq(_eventId);
		}
	}*/
	

	if (name == "btn_tap1" || name == "btn_tap2")
	{
		int _index = nxExtractInt(name, "btn_tap");
		m_TapIndex = _index - 1;
		ClickTapButton(m_TapIndex);
	}
}

void LobbyMissionPanel::ClickTapButton(int _idx)
{
	SetMissionlList();

	for (int _i = 0; _i < 2; _i++)
	{
		if (_i == _idx)
		{
			m_TapBtnPanel[_i]->getButton("sbtn_button")->setSkelAnimation("tab_on");
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setVisible(false);
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setVisible(true);
		}
		else
		{
			m_TapBtnPanel[_i]->getButton("sbtn_button")->setSkelAnimation("tab_off");
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setVisible(true);
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setVisible(false);
		}
	}
	
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
}

void LobbyMissionPanel::update(float dt)
{
	//ScrollViewOffsetProcess(dt);
	updateNotiWidget();
}

bool LobbyMissionPanel::handling(STCMD &stCmd)
{
	return false;
}
void LobbyMissionPanel::ShowMissionPanel()
{
	m_CellIndex = 0;
	m_bMovingCell = false;

	ShowMissionUi();
	SetMissionlList();
	ShowMissionTitie();

	//runAction(CCSequence::create(
	//	CCDelayTime::create(0.5f),
	//	CCMoveTo::create(0.3f, m_ShowPosition),
	//	CCCallFunc::create(this, callfunc_selector(LobbyMissionPanel::ShowMissionTitie)),
	//	NULL));
}
void LobbyMissionPanel::HideMissionPanel()
{
	HideMissionTitie();
	HideMissionUi();

	//runAction(CCSequence::create(
	//	CCCallFunc::create(this, callfunc_selector(LobbyMissionPanel::HideMissionTitie)),
	//	CCMoveTo::create(0.3f, m_HidePosition),
	//	CCCallFunc::create(this, callfunc_selector(LobbyMissionPanel::HideMissionUi)),
	//	NULL));
}

void LobbyMissionPanel::ShowMissionUi()
{
	scheduleUpdate();
}

void LobbyMissionPanel::HideMissionUi()
{
	//기덕개발
	return;
	unscheduleUpdate();
	ClearMissionList();
	GameDataManager::getSingletonPtr()->FreeUiProcess();
	LayerManager::getSingleton().popLayer("LobbyMission");
	//LayerManager::getSingleton().popLayer("LobbyTopUI");
}

void LobbyMissionPanel::ShowMissionTitie()
{
	//m_MissionTitleLabel->setVisible(true);
	//m_MissionTitleMark->setVisible(true);
	//m_MissionTitleBg->setVisible(true);

	//for (Button* _btn : m_TapBtn)
	//{
	//	_btn->setEnable(true);
	//}

	//m_TapBtn[0]->setEnable(true);
	//m_TapBtn[1]->setEnable(true);
	setTouchable(true);
	GameDataManager::getSingletonPtr()->FreeUiProcess();

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MISSION);
		}
	}
}

void LobbyMissionPanel::HideMissionTitie()
{
	//m_MissionTitleLabel->setVisible(false);
	//m_MissionTitleMark->setVisible(false);
	//m_MissionTitleBg->setVisible(false);

	//for (Button* _btn : m_TapBtn)
	//{
	//	_btn->setEnable(false);
	//}

	//m_TapBtn[0]->setEnable(false);
	//m_TapBtn[1]->setEnable(false);
	setTouchable(false);

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MAIN);
		}
	}

}

void LobbyMissionPanel::SetMissionlList()
{
	ClearMissionList();

	m_pMissionListContainer = CCLayer::create();
	CCSize _contentSize = getDummy("dmy_tab1_scrollsize_1").size;

	int _size = 0;

	if (m_TapIndex == 0)
	{
		_size = GameDataManager::getSingletonPtr()->m_pQuestDailyList.size();
		CreateCell(_size);

		int _dstIdx = _size - MISSION_CELL_MAX - m_CellIndex;
		if (_dstIdx < 1)
		{
			m_CellIndex += _dstIdx;
			if (m_CellIndex < 0)
				m_CellIndex = 0;
			_dstIdx = 0;
		}

		for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
		{
			if (_i < _size)
			{
				UpdateMissionCell(_i, _dstIdx + _i);
			}
		}

		m_CompleteCount = 0;
		for (int _i = 0; _i < _size; _i++)
		{
			W_QuestInfo* _info = GameDataManager::getSingletonPtr()->m_pQuestDailyList[_i];
			if (_info->queststatus() == W_QuestInfo_eQuestStatus_Complete || _info->queststatus() == W_QuestInfo_eQuestStatus_Finish)
			{
				m_CompleteCount++;
			}
		}
		getLabel("txt_mission_info")->setString(GameStringDepot::getSingleton().getString("TXT_DAILY_MISSION_DESC").c_str());
	}
	else
	{
		_size = GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.size();
		CreateCell(_size);

		int _dstIdx = _size - MISSION_CELL_MAX - m_CellIndex;
		if (_dstIdx < 1)
		{
			m_CellIndex += _dstIdx;
			if (m_CellIndex < 0)
				m_CellIndex = 0;
			_dstIdx = 0;
		}

		for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
		{
			if (_i < _size)
			{
				UpdateEventCell(_i, _dstIdx + _i);
				//UpdateMissionCell(_i, _dstIdx + _i);
			}
		}

		m_CompleteCount = 0;
		for (int _i = 0; _i < _size; _i++)
		{
			W_QuestInfo* _info = GameDataManager::getSingletonPtr()->m_pQuestWeeklyList[_i];
			if (_info->queststatus() == W_QuestInfo_eQuestStatus_Complete || _info->queststatus() == W_QuestInfo_eQuestStatus_Finish)
			{
				m_CompleteCount++;
			}
		}
		getLabel("txt_mission_info")->setString(GameStringDepot::getSingleton().getString("TXT_DAILY_MISSION_DESC").c_str());
		/*_size = GameDataManager::getSingletonPtr()->m_EventList.size();
		CreateCell(_size);

		int _dstIdx = _size - MISSION_CELL_MAX - m_CellIndex;
		if (_dstIdx < 0)
		{
			m_CellIndex += _dstIdx;
			if (m_CellIndex < 0)
				m_CellIndex = 0;
			_dstIdx = 0;
		}

		for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
		{
			if (_i < _size)
			{
				UpdateEventCell(_i, _dstIdx + _i);
			}
		}

		m_CompleteCount = 0;
		for (int _i = 0; _i < _size; _i++)
		{
			W_EventInfo* _info = GameDataManager::getSingletonPtr()->m_EventList[_i];
			if (_info->status() == W_QuestInfo_eQuestStatus_Complete || _info->status() == W_QuestInfo_eQuestStatus_Finish)
			{
				m_CompleteCount++;
			}
		}
		getLabel("txt_mission_info")->setString(GameStringDepot::getSingleton().getString("TXT_EVENT_MISSION_DESC").c_str());*/
	}

	string _count = StringConverter::toString(m_CompleteCount);
	string _maxCount = " / " + StringConverter::toString(_size);

	m_MissionCount->setString(_count.c_str());
	m_MissionMaxCount->setString(_maxCount.c_str());

	if (_size > 0)
	{
		getLabel("txt_tab1_empty")->setVisible(false);		
		int _listSize = _size;
		if (_listSize > MISSION_CELL_MAX)
			_listSize = MISSION_CELL_MAX;

		m_pMissionListContainer->setContentSize(CCSizeMake(_contentSize.width, mCellSize.height*_listSize));
	}
	else
	{
		getLabel("txt_tab1_empty")->setVisible(true);
		getLabel("txt_tab1_empty")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pMissionListContainer->setContentSize(_contentSize);

		if (m_TapIndex == 0)
			getLabel("txt_tab1_empty")->setString(GameStringDepot::getSingletonPtr()->getString("NO_MISSION_DESC").c_str());
		else
			getLabel("txt_tab1_empty")->setString(GameStringDepot::getSingletonPtr()->getString("NO_EVENTMISSION_DESC").c_str());
	}

	m_pMissionListView = CCScrollView::create(_contentSize, m_pMissionListContainer);
	m_pMissionListView->setDirection(extension::ScrollView::Direction::VERTICAL);
	m_pMissionListView->setBounceable(false);
	//가장 상단으로 올리기.
	//m_pMissionListView->setContentOffset(ccp(0, 0), false);
	m_pMissionListView->setContentOffset(ccp(0, _contentSize.height - (mCellSize.height*_size)), false);

	CCPoint _ListPos = getDummy("dmy_tab1_scrollsize_1").origin;
	m_pMissionListView->setPositionX(_ListPos.x);
	m_pMissionListView->setPositionY(DESIGN_HEIGHT - _ListPos.y - _contentSize.height);
	addChild(m_pMissionListView, 10);
	m_pMissionListView->setTouchEnabled(false);
	
}

void LobbyMissionPanel::ClearMissionList()
{
	for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
	{
		if (m_CellBtnPanel[_i])
		{
			m_CellBtnPanel[_i]->cleanup();
			m_CellBtnPanel[_i]->removeFromParent();
			m_CellBtnPanel[_i] = nullptr;
		}
	}

	if (m_pMissionListContainer)
	{
		m_pMissionListContainer->cleanup();
		m_pMissionListContainer->removeFromParent();
	}
	m_pMissionListContainer = nullptr;

	if (m_pMissionListView)
	{
		m_pMissionListView->cleanup();
		m_pMissionListView->removeFromParent();
	}
	m_pMissionListView = nullptr;

	for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
	{
		m_ListCell[_i] = nullptr;
	}
}


bool LobbyMissionPanel::cellTouchStart(const CCPoint& tableTouchPoint)
{
	if (m_pMissionListContainer == nullptr)
		return false;

	//CCObject* _node;
	//CCArray* panelNodes = m_pMissionListContainer->getChildren();
	//CCARRAY_FOREACH(panelNodes, _node)
	//{
	//	Panel* _panel = dynamic_cast<Panel*>(_node);
	//	Button* btn1 = _panel->getButton("sbtn_inpanel_button1_stay");
	//	if (btn1) {
	//		if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
	//			if (btn1->isEnabled()){
	//				btn1->setSkelAnimation("inpanel_button_in", false);
	//				return true;
	//			}
	//		}
	//	}
	//}

	return false;
}

bool LobbyMissionPanel::cellTouchCancel(const CCPoint& tableTouchPoint)
{
	if (m_pMissionListContainer == nullptr)
		return false;

	//CCObject* _node;
	//CCArray* panelNodes = m_pMissionListContainer->getChildren();
	//CCARRAY_FOREACH(panelNodes, _node)
	//{
	//	Panel* _panel = dynamic_cast<Panel*>(_node);
	//	Button* btn1 = _panel->getButton("sbtn_inpanel_button1_stay");
	//	if (btn1) {
	//		if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
	//			if (btn1->isEnabled()){
	//				btn1->setSkelAnimation("inpanel_button_out", false);
	//				btn1->setSkelAppendAnimation("inpanel_button_stay");
	//			}
	//		}
	//	}
	//}
	return false;
}

bool LobbyMissionPanel::cellTouch(const CCPoint& tableTouchPoint)
{
	LobbyTopUiPanel* _pTopPanel = nullptr;
	CCPoint _diffPos;
	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		_pTopPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));

		CCPoint _thisPos = getPosition();
		CCPoint _TopPos = _pTopPanel->getPosition();

		_diffPos = _TopPos - _thisPos;
	}

	for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
	{
		if (m_CellBtnPanel[_i] == nullptr)
			continue;

		Button* _btn = m_CellBtnPanel[_i]->getButton("sbtn_button");
		if (_btn)
		{
			if (_btn->hasCollided(_btn->convertToNodeSpace(tableTouchPoint))){
				if (_btn->isEnabled()){
					if (m_TapIndex == 0)
					{
						int _idx = _btn->getTag();
						int _id = GameDataManager::getSingletonPtr()->m_pQuestDailyList[_idx]->questid();
						W_GameData* _pGameData = GameDataManager::getSingletonPtr()->GetGameDataPtr();
						int _questSize = GameDataManager::getSingletonPtr()->GetGameDataPtr()->questdata_size();
						for (int _index = 0; _index < _questSize; _index++)
						{
							if (_pGameData->questdata(_index).id() == _id)
							{
								int _kind = _pGameData->questdata(_index).rewardinfo().rewardset(0).type();
								for (int _i = 0; _i < 8; _i++)
								{
// 									PokerChipWidget* _pEffect = PokerChipWidget::createBonus(_kind, tableTouchPoint + _diffPos, 0.2f + _i*0.05f);
// 									if (_pEffect && _pTopPanel)
// 									{
// 										_pTopPanel->addChild(_pEffect);
// 										_pEffect->release();
// 
// 									}
								}
								break;
							}
						}

						string _BtnName = "GetBonusButton" + StringConverter::toString(_idx);
						onClicked(_BtnName);
					}
					else if (m_TapIndex == 1)
					{
						int _idx = _btn->getTag();
						//int _id = GameDataManager::getSingletonPtr()->m_pQuestDailyList[_idx]->questid();
						
//						eResourceType _kind = GameDataManager::getSingletonPtr()->m_EventList[_btn->getTag()]->rewardinfo().rewardset(0).type();
//// 						for (int _i = 0; _i < 8; _i++)
//// 						{
//// 							PokerChipWidget* _pEffect = PokerChipWidget::createBonus(_kind, tableTouchPoint + _diffPos, 0.2f + _i*0.05f);
//// 							if (_pEffect && _pTopPanel)
//// 							{
//// 								_pTopPanel->addChild(_pEffect);
//// 								_pEffect->release();
//// 							}
//// 						}

						string _BtnName = "GetEventBonusButton" + StringConverter::toString(_idx);
						onClicked(_BtnName);
					}
				}
			}
		}
	}
	return false;
}

void LobbyMissionPanel::cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}

void LobbyMissionPanel::ScrollViewOffsetProcess(float _dt)
{
	if (m_bMovingCell == false)
		return;

	if (m_pMissionListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pMissionListView->getContentOffset();
	int _size = 0;
	if (m_TapIndex == 0)
	{
		_size = GameDataManager::getSingletonPtr()->m_pQuestDailyList.size();
	}
	else
	{
		_size = GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.size();
	}

	if (m_fMoveG < 0)
	{
		m_fMoveG += mCellSize.height * 0.5f * _dt;
		if (m_fMoveG > -5.f)
		{
			m_bMovingCell = false;
			m_fMoveG = 0.f;
			return;
		}

		float _minMove = -mCellSize.height;
		if (_offSetPoint.y >= _minMove && m_CellIndex + MISSION_CELL_MAX < _size)
		{
			m_CellIndex++;
			m_pMissionListView->setContentOffset(_offSetPoint - ccp(0, mCellSize.height - m_fMoveG));
			for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
			{
				if (m_TapIndex == 0)
					UpdateMissionCell(_i, _size - MISSION_CELL_MAX - m_CellIndex + _i);
				else if (m_TapIndex == 1)
					UpdateEventCell(_i, _size - MISSION_CELL_MAX - m_CellIndex + _i);
			}
		}
		else
			m_pMissionListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
	}
	else
	{
		m_fMoveG -= mCellSize.height * 0.5f * _dt;

		if (m_fMoveG < 5.f)
		{
			m_bMovingCell = false;
			m_fMoveG = 0.f;
			return;
		}

		float _maxMove = -mCellSize.height * 2.5f;
		if (_offSetPoint.y <= _maxMove && m_CellIndex > 0)
		{
			m_CellIndex--;
			m_pMissionListView->setContentOffset(_offSetPoint + ccp(0, mCellSize.height - m_fMoveG));
			for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
			{
				if (m_TapIndex == 0)
					UpdateMissionCell(_i, _size - MISSION_CELL_MAX - m_CellIndex + _i);
				else if (m_TapIndex == 1)
					UpdateEventCell(_i, _size - MISSION_CELL_MAX - m_CellIndex + _i);
			}
		}
		else
			m_pMissionListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
	}
}

void LobbyMissionPanel::CreateCell(int _size)
{
	int _MakeCellSize = _size;
	if (_MakeCellSize > MISSION_CELL_MAX)
		_MakeCellSize = MISSION_CELL_MAX;

	for (int _i = 0; _i < MISSION_CELL_MAX; _i++)
	{
		if (_i >= _size)
			continue;

		m_ListCell[_i] = new Panel();
		m_ListCell[_i]->construct(getMxmlPath() + "dmy_m_bar_ex.mxml");
		m_ListCell[_i]->setTag(-1);
		m_ListCell[_i]->getSkel("skel_clear")->pauseAnimation();
		m_ListCell[_i]->getSkel("skel_clear")->setVisible(false);
		m_ListCell[_i]->getSkel("skel_clear")->setZOrder(1);
		m_ListCell[_i]->getSkel("skel_clear")->setZOrder(1);
		m_ListCell[_i]->getImage("skel_gauge")->setAnchorPoint(ccp(0.f, 0.5f));
		m_ListCell[_i]->getImage("skel_gauge")->setPositionX(m_ListCell[_i]->getImage("skel_gauge")->getPositionX() - m_ListCell[_i]->getDummy("skel_gauge").size.width / 2.0f);

		m_ListCell[_i]->getImage("ticket_101")->setVisible(false);
		m_ListCell[_i]->getImage("ticket_101")->setScale(0.7);
		m_ListCell[_i]->getImage("ticket_101")->setZOrder(2);
		m_ListCell[_i]->getImage("ticket_102")->setVisible(false);
		m_ListCell[_i]->getImage("ticket_102")->setScale(0.7);
		m_ListCell[_i]->getImage("ticket_102")->setZOrder(2);


		CCSize _ButtonPanelSize = m_ListCell[_i]->getDummy("dmy_m_bar").size;

		//Button* _pButton = m_ListCell[_i]->getButton("sbtn_inpanel_button1_stay");
		//_pButton->setType(Button::NoPressImg);
		//_pButton->setTag(_i);
		//_pButton->setListener(this);
		//_pButton->setPaused(true);

		//m_ListCell[_i]->getButton("sbtn_scroll_panel")->setType(Button::NoPressImg);
		//m_ListCell[_i]->getButton("sbtn_scroll_panel")->setPaused(true);
		CCPoint _btnPos = m_ListCell[_i]->getDummy("dmy_button_small").origin;
		_btnPos.y = -_btnPos.y;
		m_CellBtnPanel[_i] = new Panel();
		m_CellBtnPanel[_i]->construct(getMxmlPath() + "dmy_button_small.mxml");
		m_CellBtnPanel[_i]->setPosition(_btnPos);
		m_ListCell[_i]->addChild(m_CellBtnPanel[_i]);
		m_CellBtnPanel[_i]->release();

		Button* _pButton = m_CellBtnPanel[_i]->getButton("sbtn_button");
		_pButton->setTag(_i);
		_pButton->setPaused(true);

		Nx::Label* _pBtnShodow = m_CellBtnPanel[_i]->getLabel("txt_button_under");
		Nx::Label* _pBtnText = m_CellBtnPanel[_i]->getLabel("txt_button");

		Nx::Label* _pMissionName = m_ListCell[_i]->getLabel("txt_mission_name");
		Nx::Label* _pMissionRule = m_ListCell[_i]->getLabel("txt_mission_rule");
		Nx::Label* _pTimeLimit = m_ListCell[_i]->getLabel("txt_letter_timelimit");
		Nx::Label* _pBonuscont = m_ListCell[_i]->getLabel("txt_buttonsum");
		Nx::Label* _pComplete = m_ListCell[_i]->getLabel("txt_complete");

		_pBtnShodow->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pBtnText->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		_pMissionName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pMissionRule->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pTimeLimit->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pBonuscont->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pComplete->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		_pBtnShodow->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTER_GET_UNIT").c_str());
		_pBtnText->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTER_GET_UNIT").c_str());
		_pTimeLimit->setVisible(false);

		m_ListCell[_i]->setPosition(ccp(0.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (mCellSize.height * _i)));
		m_pMissionListContainer->addChild(m_ListCell[_i]);
		m_ListCell[_i]->release();
	}	
}

void LobbyMissionPanel::UpdateMissionCell(int _toIdx, int _dstIdx)
{
	if (_dstIdx >= GameDataManager::getSingletonPtr()->m_pQuestDailyList.size())
	{
		return;
	}

	if (m_ListCell[_toIdx]->getTag() == _dstIdx)
		return;

	m_ListCell[_toIdx]->setTag(_dstIdx);

	CCSize _ButtonPanelSize = m_ListCell[_toIdx]->getDummy("dmy_m_bar").size;
	//m_ListCell[_toIdx]->setPosition(ccp(10.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (MISSION_CELL_HEIGHT * _dstIdx)));

	int _questCount = GameDataManager::getSingletonPtr()->m_pQuestDailyList.size();

	if (_dstIdx % 2 != _questCount % 2)
	{
		m_ListCell[_toIdx]->getSkel("skel_bar")->playAnimation("bar_longa");
	}
	else
	{
		m_ListCell[_toIdx]->getSkel("skel_bar")->playAnimation("bar_longb");
	}

	Nx::Label* _pMissionName = m_ListCell[_toIdx]->getLabel("txt_mission_name");
	Nx::Label* _pMissionRule = m_ListCell[_toIdx]->getLabel("txt_mission_rule");
	//Label* _pTimeLimit = m_ListCell[_toIdx]->getLabel("txt_letter_timelimit");
	Nx::Label* _pBonuscont = m_ListCell[_toIdx]->getLabel("txt_buttonsum");
	Nx::Label* _pComplete = m_ListCell[_toIdx]->getLabel("txt_complete");
	SkelObject* iconSkelObject = m_ListCell[_toIdx]->getSkel("skel_symbol");
	Nx::Label* _pBtnShodow = m_CellBtnPanel[_toIdx]->getLabel("txt_button_under");
	Nx::Label* _pBtnText = m_CellBtnPanel[_toIdx]->getLabel("txt_button");
	
	W_GameData* _pGameData = GameDataManager::getSingletonPtr()->GetGameDataPtr();

	if (_pGameData == nullptr || GameDataManager::getSingletonPtr()->m_pQuestDailyList.size() <= 0)
	{
		return;
	}

	W_QuestInfo* _questInfo = GameDataManager::getSingletonPtr()->m_pQuestDailyList[_dstIdx];

	if (_questInfo->has_questid())
	{
		Button* _pButton = m_CellBtnPanel[_toIdx]->getButton("sbtn_button");
		_pButton->setTag(_dstIdx);

		int _id = _questInfo->questid();
		int _questSize = _pGameData->questdata_size();
		for (int _index = 0; _index < _questSize; _index++)
		{
			if (_pGameData->questdata(_index).id() != _id)
				continue;

			_pMissionName->setString(_pGameData->questdata(_index).title().c_str());
			_pMissionRule->setString(_pGameData->questdata(_index).content().c_str());
			iconSkelObject->playAnimation(_pGameData->questdata(_index).icon());

			eResourceType _bonusType = _pGameData->questdata(_index).rewardinfo().rewardset(0).type();
			int64 _bonusAmount = _pGameData->questdata(_index).rewardinfo().rewardset(0).amount();
			int rewardID = _pGameData->questdata(_index).rewardinfo().rewardset(0).id();

			switch (_bonusType)
			{
			case CASH:
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation("icon_rubby");
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(true);
				break;
			case GAMEMONEY:
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation("icon_gold");
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(true);
				break;
			case CHIP:
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation("icon_chip");
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(true);
				break;
			case REPUTE:
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation("icon_trophy");
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(true);
				break;
			case TOUR_TICKET:
				if (rewardID == 101)
					m_ListCell[_toIdx]->getImage("ticket_101")->setVisible(true);
				else if (rewardID == 201)
					m_ListCell[_toIdx]->getImage("ticket_102")->setVisible(true);
				else
					CCLOG("unkown rewardID");
				break;
			default:
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(false);
				break;
			}

			switch (_questInfo->queststatus())
			{
			case W_QuestInfo_eQuestStatus_Process:
			{
				_pButton->setEnable(false);
				_pButton->setGrayscale(true);
				string _bonus = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_bonusAmount), 1);
				_pBonuscont->setString(_bonus.c_str());
				string _progressText = StringConverter::toString(_questInfo->amount()) + "/" + StringConverter::toString(_questInfo->maxamount());
				_pComplete->setString(_progressText.c_str());
				break;
			}
			case W_QuestInfo_eQuestStatus_Complete:
			{
				_pButton->setEnable(true);
				_pButton->setGrayscale(false);
				string _bonus = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_bonusAmount), 1);
				_pBonuscont->setString(_bonus.c_str());
				_pComplete->setString("");
				break;
			}
			case W_QuestInfo_eQuestStatus_Finish:
			{
				_pButton->setVisible(false);
				_pButton->setEnable(false);
				string _bonus = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_bonusAmount), 1);
				_pBonuscont->setString(_bonus.c_str());

				string competeStr = GameStringDepot::getSingleton().getString("TXT_COMPLATE");
				_pComplete->setString("");
				_pBtnText->setString(competeStr.c_str());
				_pBtnShodow->setString(competeStr.c_str());
				m_ListCell[_toIdx]->getSkel("skel_clear")->setVisible(true);
				m_ListCell[_toIdx]->getSkel("skel_clear")->playAnimation("mark_clear_stay");
				
				break;
			}
			
			}

			float _per = (float)(_questInfo->amount()) / (float)(_questInfo->maxamount());
			SetProgressBar(_toIdx, _per);
		}
	}
}

void LobbyMissionPanel::UpdateEventCell(int _toIdx, int _dstIdx)
{
	if (_dstIdx >= GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.size())
	{
		return;
	}

	if (m_ListCell[_toIdx]->getTag() == _dstIdx)
		return;

	m_ListCell[_toIdx]->setTag(_dstIdx);

	CCSize _ButtonPanelSize = m_ListCell[_toIdx]->getDummy("dmy_m_bar").size;
	//m_ListCell[_toIdx]->setPosition(ccp(10.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (MISSION_CELL_HEIGHT * _dstIdx)));

	int _questCount = GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.size();

	if (_dstIdx % 2 != _questCount % 2)
	{
		m_ListCell[_toIdx]->getSkel("skel_bar")->playAnimation("bar_longa");
	}
	else
	{
		m_ListCell[_toIdx]->getSkel("skel_bar")->playAnimation("bar_longb");
	}

	Nx::Label* _pMissionName = m_ListCell[_toIdx]->getLabel("txt_mission_name");
	Nx::Label* _pMissionRule = m_ListCell[_toIdx]->getLabel("txt_mission_rule");
	//Label* _pTimeLimit = m_ListCell[_toIdx]->getLabel("txt_letter_timelimit");
	Nx::Label* _pBonuscont = m_ListCell[_toIdx]->getLabel("txt_buttonsum");
	Nx::Label* _pComplete = m_ListCell[_toIdx]->getLabel("txt_complete");
	SkelObject* iconSkelObject = m_ListCell[_toIdx]->getSkel("skel_symbol");
	Nx::Label* _pBtnShodow = m_CellBtnPanel[_toIdx]->getLabel("txt_button_under");
	Nx::Label* _pBtnText = m_CellBtnPanel[_toIdx]->getLabel("txt_button");

	W_GameData* _pGameData = GameDataManager::getSingletonPtr()->GetGameDataPtr();

	if (_pGameData == nullptr || GameDataManager::getSingletonPtr()->m_pQuestWeeklyList.size() <= 0)
	{
		return;
	}

	W_QuestInfo* _questInfo = GameDataManager::getSingletonPtr()->m_pQuestWeeklyList[_dstIdx];

	if (_questInfo->has_questid())
	{
		Button* _pButton = m_CellBtnPanel[_toIdx]->getButton("sbtn_button");
		_pButton->setTag(_dstIdx);

		int _id = _questInfo->questid();
		int _questSize = _pGameData->weeklyquestdata_size();
		for (int _index = 0; _index < _questSize; _index++)
		{
			if (_pGameData->weeklyquestdata(_index).id() != _id)
				continue;

			_pMissionName->setString(_pGameData->weeklyquestdata(_index).title().c_str());
			_pMissionRule->setString(_pGameData->weeklyquestdata(_index).content().c_str());
			if(_pGameData->weeklyquestdata(_index).icon() == "tournament")
				iconSkelObject->playAnimation("symbol_allgame");
			else
				iconSkelObject->playAnimation(_pGameData->weeklyquestdata(_index).icon());
			
		
			eResourceType _bonusType = _pGameData->weeklyquestdata(_index).rewardinfo().rewardset(0).type();
			int64 _bonusAmount = _pGameData->weeklyquestdata(_index).rewardinfo().rewardset(0).amount();
			int rewardID = _pGameData->weeklyquestdata(_index).rewardinfo().rewardset(0).id();

			switch (_bonusType)
			{
			case CASH:
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation("icon_rubby");
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(true);
				break;
			case GAMEMONEY:
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation("icon_gold");
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(true);
				break;
			case CHIP:
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation("icon_chip");
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(true);
				break;
			case REPUTE:
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation("icon_trophy");
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(true);
				break;
			case TOUR_TICKET:
				if (rewardID == 101)
					m_ListCell[_toIdx]->getImage("ticket_101")->setVisible(true);
				else if (rewardID == 201)
					m_ListCell[_toIdx]->getImage("ticket_102")->setVisible(true);
				else
					CCLOG("unkown rewardID");
				break;
			default:
				m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(false);
				break;
			}

			switch (_questInfo->queststatus())
			{
			case W_QuestInfo_eQuestStatus_Process:
			{
				_pButton->setEnable(false);
				_pButton->setGrayscale(true);
				string _bonus = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_bonusAmount), 1);
				_pBonuscont->setString(_bonus.c_str());
				string _progressText = StringConverter::toString(_questInfo->amount()) + "/" + StringConverter::toString(_questInfo->maxamount());
				_pComplete->setString(_progressText.c_str());
				break;
			}
			case W_QuestInfo_eQuestStatus_Complete:
			{
				_pButton->setEnable(true);
				_pButton->setGrayscale(false);
				string _bonus = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_bonusAmount), 1);
				_pBonuscont->setString(_bonus.c_str());
				_pComplete->setString("");
				break;
			}
			case W_QuestInfo_eQuestStatus_Finish:
			{
				_pButton->setVisible(false);
				_pButton->setEnable(false);
				string _bonus = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_bonusAmount), 1);
				_pBonuscont->setString(_bonus.c_str());

				string competeStr = GameStringDepot::getSingleton().getString("TXT_COMPLATE");
				_pComplete->setString("");
				_pBtnText->setString(competeStr.c_str());
				_pBtnShodow->setString(competeStr.c_str());
				m_ListCell[_toIdx]->getSkel("skel_clear")->setVisible(true);
				m_ListCell[_toIdx]->getSkel("skel_clear")->playAnimation("mark_clear_stay");

				break;
			}

			}

			float _per = (float)(_questInfo->amount()) / (float)(_questInfo->maxamount());
			SetProgressBar(_toIdx, _per);
		}
	}
}

void LobbyMissionPanel::SetProgressBar(int _cellIdx, float _per)
{
	SkelObject* _center = m_ListCell[_cellIdx]->getSkel("skel_gauge");
	_center->setScaleX(_per);
}

void LobbyMissionPanel::onCloseRewardPopupPanel()
{

}

void LobbyMissionPanel::updateNotiWidget()
{
	for (int i = 0; i < mNotiWidgets.size(); i++)
	{
		mNotiWidgets[i]->refresh();
	}
}

void LobbyMissionPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}