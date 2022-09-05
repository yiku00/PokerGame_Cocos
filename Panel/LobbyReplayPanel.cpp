#include "pch.h"
#include "LobbyReplayPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "SimplePopupPanel.h"
#include "GameStringDepot.h"
#include "LobbyScene.h"
#include "LobbyUIPanel.h"
#include "CustomPopupPanel.h"
#include "ReplayGameManager.h"

#define TAB_BTN_COUNT 2

#define REPLAY_TYPE_INIT 4	//tapindex 가 0 일대 season 이다.

LobbyReplayPanel::LobbyReplayPanel()
{
	mLoginProcess = false;

	m_pReplayListView = nullptr;
	m_pReplayListContainer = nullptr;
	m_pTextField = nullptr;

	m_CellIndex = 0;
	m_bMovingCell = false;
	m_TapIndex = -1;

	for (int _i = 0; _i < REPLAY_CELL_MAX; _i++)
	{
		m_ListCell[_i] = nullptr;
	}

	m_nSortType = SORT_TYPE_SCORE;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);

	unscheduleUpdate();

	ClickTapButton(0);
	m_ViewDataIndex = 10;	
}

LobbyReplayPanel::~LobbyReplayPanel()
{
	if (m_pReplayListView)
	{
		m_pReplayListView->removeFromParentAndCleanup(true);
		m_pReplayListView = nullptr;
	}
}

void LobbyReplayPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_replay.mxml");
	mCellSize = getDummy("dmy_rp_bar").size;

	getLabel("txt_tab1_empty")->setVisible(false);
}

void LobbyReplayPanel::InitImage()
{
	getLabel("txt_tab1_empty")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LIST_EMPTY").c_str());
	getLabel("str_guide")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GUIDE_REPLAY").c_str());
}

void LobbyReplayPanel::initButton()
{
	m_nSortType = SORT_TYPE_SCORE;	
	for (int _i = 0; _i < TAB_BTN_COUNT; _i++)
	{
		CCPoint _tapBtnPos = getDummy("dmy_button_tab" + StringConverter::toString(_i + 1)).origin;

		m_TapButton[_i] = new TabButtonPanel();
		m_TapButton[_i]->setPositionX(_tapBtnPos.x);
		m_TapButton[_i]->setPositionY(-_tapBtnPos.y);
		addChild(m_TapButton[_i], 20);
		m_TapButton[_i]->release();
		m_TapButton[_i]->SetButtonListener(this);

		string _tapBtnLabel = "TXT_REPLAY_TAP_BUTTON" + StringConverter::toString(_i + 1);
		m_TapButton[_i]->SetButtonText(GameStringDepot::getSingletonPtr()->getString(_tapBtnLabel.c_str()));

		m_TapButton[_i]->m_Button->setName("REPLAY_TAP_BUTTON" + StringConverter::toString(_i + 1));
	}
}


bool LobbyReplayPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
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


void LobbyReplayPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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

	if (m_pReplayListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pReplayListView->getContentOffset();
	int _size = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size();
	
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

	if (_size <= REPLAY_CELL_MAX)	//셀 수가 MAX보다 많고
	{
		m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, _moveV));
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
				m_pReplayListView->setContentOffset(_offSetPoint + ccp(0, mCellSize.height));
				for (int _i = 0; _i < REPLAY_CELL_MAX; _i++)
				{
					UpdateReplayCell(_i, _size - REPLAY_CELL_MAX - m_CellIndex + _i);
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
			if (m_CellIndex + REPLAY_CELL_MAX < _size)
			{
				m_CellIndex++;
				m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, mCellSize.height));
				for (int _i = 0; _i < REPLAY_CELL_MAX; _i++)
				{
					UpdateReplayCell(_i, _size - REPLAY_CELL_MAX - m_CellIndex + _i);
				}
				_bMove = true;
			}
		}
	}

	if (_bMove == false)
	{
		m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, _moveV));
	}
}


void LobbyReplayPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
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



void LobbyReplayPanel::resume()
{
}

void LobbyReplayPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (name == "REPLAY_TAP_BUTTON1")
	{
		ClickTapButton(0);
	}
	if (name == "REPLAY_TAP_BUTTON2")
	{
		ClickTapButton(1);
	}
	if (name == "REPLAY_TAP_BUTTON3")
	{
		ClickTapButton(2);
	}

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (strncmp("ReplayButton", name.c_str(), 12) == 0)
	{
		int _index = nxExtractInt(name, "ReplayButton");
		
		if (GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->has_seq())
		{
			int64 _seq = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->seq();
			bool _isLike = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->islike();
			ReplayGameManager::getSingletonPtr()->SetIsLike(_isLike);
			//season 부터 시작
			eReplayType _type = (eReplayType)(m_TapIndex + REPLAY_TYPE_INIT);
			WebService::getSingletonPtr()->_sendReplayStartReq(_type, _seq);
		}
	}

	if (strncmp("EditBtn", name.c_str(), 7) == 0)
	{
		int _index = nxExtractInt(name, "EditBtn");

		m_pTextField = m_ListCell[_index]->getTextField("fld_my_replaytitle");
		m_pTextField->setListener(this);
		m_pTextField->attachWithIME();
	}
	else if (strncmp("ShowInfoBtn", name.c_str(), 7) == 0)
	{
		int _index = nxExtractInt(name, "ShowInfoBtn");
		if (m_TapIndex == 2)
		{
			ShowReplayInfoPanel(_index, REPLAY_OWN::OWN_MINE);
		}
		else
		{
			ShowReplayInfoPanel(_index, REPLAY_OWN::OWN_SOMEONE);
		}
	}
	
	if (name == "sbtn_title_cancel_stay")
	{
		//m_pShadowBg->setVisible(false);
	}

	if (name == "sbtn_grange_on_stay1")
	{
		if (m_nSortType == SORT_TYPE_SCORE)
			return;

		m_nSortType = SORT_TYPE_SCORE;
		getButton("sbtn_grange_on_stay1")->getButtonSkelObject()->playAnimation("grange_on_start");
		getButton("sbtn_grange_on_stay1")->getButtonSkelObject()->appendAnimation("grange_on_stay", true);
		getButton("sbtn_grange_on_stay2")->getButtonSkelObject()->playAnimation("grange_on_end");
		getButton("sbtn_grange_on_stay2")->getButtonSkelObject()->appendAnimation("grange_off_stay", true);

		SortReplayData(SORT_TYPE_SCORE);
	}

	if (name == "sbtn_grange_on_stay2")
	{
		if (m_nSortType == SORT_TYPE_DATE)
			return;

		m_nSortType = SORT_TYPE_DATE;
		getButton("sbtn_grange_on_stay1")->getButtonSkelObject()->playAnimation("grange_on_end");
		getButton("sbtn_grange_on_stay1")->getButtonSkelObject()->appendAnimation("grange_off_stay", true);
		getButton("sbtn_grange_on_stay2")->getButtonSkelObject()->playAnimation("grange_on_start");
		getButton("sbtn_grange_on_stay2")->getButtonSkelObject()->appendAnimation("grange_on_stay", true);

		SortReplayData(SORT_TYPE_DATE);
	}
}

void LobbyReplayPanel::SortReplayData(int _type)
{
	if (_type == SORT_TYPE_SCORE)
	{
		GameDataManager::getSingletonPtr()->SortReplayData(SORT_TYPE_SCORE);
	}
	else if (_type == SORT_TYPE_DATE)
	{
		GameDataManager::getSingletonPtr()->SortReplayData(SORT_TYPE_DATE);
	}

	int _size = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size();

	for (int _i = 0; _i < _size; _i++)
	{
		if (_i < REPLAY_CELL_MAX)
		{
			int _idx = m_ListCell[_i]->getTag();
			m_ListCell[_i]->setTag(-1);
			UpdateReplayCell(_i, _idx);
		}
	}
}

void LobbyReplayPanel::ClickTapButton(int _idx)
{
	if (m_TapIndex == _idx)
		return;

	m_TapIndex = _idx;

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);

	for (int _i = 0; _i < TAB_BTN_COUNT; _i++)
	{
		if (_i == _idx)
		{
			m_TapButton[_i]->SetBtnOnOff(true);
		}
		else
		{
			m_TapButton[_i]->SetBtnOnOff(false);
		}
	}

	//SetReplayList();
	switch (m_TapIndex)
	{
	case 0:
		WebService::getSingletonPtr()->_sendReplaySeasonReq();
		break;
	case 1:
		WebService::getSingletonPtr()->_sendReplayDeathMatchReq();
		break;
	case 2:
		WebService::getSingletonPtr()->_sendReplayListReq(GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->GetUID());
		break;
	default:
		break;
	}

}

void LobbyReplayPanel::update(float dt)
{
	ScrollViewOffsetProcess(dt);
}

bool LobbyReplayPanel::handling(STCMD &stCmd)
{
	return false;
}
void LobbyReplayPanel::ShowReplayPanel()
{
	m_CellIndex = 0;
	m_bMovingCell = false;

	ShowReplayUi();
	setTouchable(true);
	SetReplayList();
	ShowReplayTitie();
}
void LobbyReplayPanel::HideReplayPanel()
{
	HideReplayTitie();
	HideReplayUi();

}

void LobbyReplayPanel::ShowReplayUi()
{
	scheduleUpdate();
}

void LobbyReplayPanel::HideReplayUi()
{
	unscheduleUpdate();
	ClearReplayList();

	GameDataManager::getSingletonPtr()->FreeUiProcess();

	LayerManager::getSingleton().popLayer("LobbyReplay");
	//LayerManager::getSingleton().popLayer("LobbyTopUI");
}

void LobbyReplayPanel::ShowReplayTitie()
{
	//setTouchable(true);
	//SetReplayList();

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_REPLAY);
		}
	}
}

void LobbyReplayPanel::HideReplayTitie()
{
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

void LobbyReplayPanel::SetReplayList()
{
	ClearReplayList();

	string _subDesc = "";
	switch (m_TapIndex)
	{
	case 0:
		_subDesc = GameStringDepot::getSingletonPtr()->getString("TXT_REPLAY_TAP_SUB_DESC_1");
		//getButton("sbtn_grange_on_stay1")->setVisible(false);
		//getButton("sbtn_grange_on_stay1")->setEnable(false);
		//getButton("sbtn_grange_on_stay2")->setVisible(false);
		//getButton("sbtn_grange_on_stay2")->setEnable(false);

		break;
	case 1:
		_subDesc = GameStringDepot::getSingletonPtr()->getString("TXT_REPLAY_TAP_SUB_DESC_2");
		//getButton("sbtn_grange_on_stay1")->setVisible(false);
		//getButton("sbtn_grange_on_stay1")->setEnable(false);
		//getButton("sbtn_grange_on_stay2")->setVisible(false);
		//getButton("sbtn_grange_on_stay2")->setEnable(false);
		break;
	case 2:
		_subDesc = GameStringDepot::getSingletonPtr()->getString("TXT_REPLAY_TAP_SUB_DESC_3");
		//getButton("sbtn_grange_on_stay1")->setVisible(true);
		//getButton("sbtn_grange_on_stay1")->setEnable(true);
		//getButton("sbtn_grange_on_stay2")->setVisible(true);
		//getButton("sbtn_grange_on_stay2")->setEnable(true);

		//getButton("sbtn_grange_on_stay1")->getButtonSkelObject()->playAnimation("grange_on_start");
		//getButton("sbtn_grange_on_stay1")->getButtonSkelObject()->appendAnimation("grange_on_stay", true);
		//getButton("sbtn_grange_on_stay2")->getButtonSkelObject()->playAnimation("grange_on_end");
		//getButton("sbtn_grange_on_stay2")->getButtonSkelObject()->appendAnimation("grange_off_stay", true);

		m_nSortType = SORT_TYPE_SCORE;
		break;
	}

	getLabel("str_guide")->setString(_subDesc.c_str());

	m_pReplayListContainer = CCLayer::create();
	CCSize _contentSize = getDummy("dmy_tab1_scrollsize").size;

	int _size = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size();
	CreateCell(_size);

	int _dstIdx = _size - REPLAY_CELL_MAX - m_CellIndex;
	if (_dstIdx < 0)
	{
		m_CellIndex += _dstIdx;
		if (m_CellIndex < 0)
			m_CellIndex = 0;
		_dstIdx = 0;
	}

	for (int _i = 0; _i < REPLAY_CELL_MAX; _i++)
	{
		if (_i < _size)
		{
			UpdateReplayCell(_i, _dstIdx + _i);
		}
	}

	if (_size > 0)
	{
		getLabel("txt_tab1_empty")->setVisible(false);
		
		int _listSize = _size;
		if (_listSize > MAX_LETTER_CELL)
			_listSize = MAX_LETTER_CELL;

		m_pReplayListContainer->setContentSize(CCSizeMake(_contentSize.width, mCellSize.height * _listSize));

	}
	else
	{
		getLabel("txt_tab1_empty")->setVisible(true);
		m_pReplayListContainer->setContentSize(_contentSize);

	}

	m_pReplayListView = CCScrollView::create(_contentSize, m_pReplayListContainer);
	m_pReplayListView->setDirection(extension::ScrollView::Direction::VERTICAL);
	m_pReplayListView->setBounceable(false);
	//가장 상단으로 올리기.
	m_pReplayListView->setContentOffset(ccp(0, _contentSize.height - (mCellSize.height*_size)), false);

	CCPoint _ListPos = getDummy("dmy_tab1_scrollsize").origin;
	_ListPos.y = DESIGN_HEIGHT - getDummy("dmy_tab1_scrollsize").size.height - _ListPos.y;
	m_pReplayListView->setPosition(_ListPos);
	m_pReplayListView->setTouchEnabled(false);
	addChild(m_pReplayListView, 10);

	//getSkel("skel_tab1_panel_f1_2_center4")->setVisible(false);
}



void LobbyReplayPanel::ClearReplayList()
{
	for (int _i = 0; _i < REPLAY_CELL_MAX; _i++)
	{
		if (m_ListCell[_i])
		{
			m_ListCell[_i]->removeAllChildren();
			m_ListCell[_i]->removeFromParent();
			m_ListCell[_i] = nullptr;

			if (m_ReplayRankLabel[_i])
			{
				m_ReplayRankLabel[_i] = nullptr;
			}

		}
	}

	if (m_pReplayListContainer)
	{
		m_pReplayListContainer->removeAllChildren();
		m_pReplayListContainer->removeFromParent();
		m_pReplayListContainer = nullptr;
	}

	if (m_pReplayListView)
	{
		m_pReplayListView->removeAllChildren();
		m_pReplayListView->removeFromParent();
		m_pReplayListView = nullptr;
	}

	
}

bool LobbyReplayPanel::cellTouchStart(const CCPoint& tableTouchPoint)
{
	if (m_pReplayListContainer == nullptr)
		return false;


	auto& panelNodes = m_pReplayListContainer->getChildren();
	for(auto _node : panelNodes)
	{
		//Panel* _panel = dynamic_cast<Panel*>(_node);
		//Button* btn1 = _panel->getButton("sbtn_inpanel_button2_stay");
		//Button* btn2 = _panel->getButton("sbtn_my_edit_button");
		//Button* btn3 = _panel->getButton("sbtn_scroll_panel");
		//if (btn1 && btn2 && btn3) {
		//	if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint)) && btn1->isEnabled()){
		//		btn1->setSkelAnimation("inpanel_button_in", false);
		//		return true;
		//	}
		//	else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint)) && btn2->isEnabled()){
		//		return true;
		//	}
		//	else if (btn3->hasCollided(btn3->convertToNodeSpace(tableTouchPoint)) && btn3->isEnabled()){
		//		return true;
		//	}
		//}
	}

	return false;
}

bool LobbyReplayPanel::cellTouchCancel(const CCPoint& tableTouchPoint)
{
	if (m_pReplayListContainer == nullptr)
		return false;

	auto& panelNodes = m_pReplayListContainer->getChildren();
	for (auto _node : panelNodes)
	{
		//Panel* _panel = dynamic_cast<Panel*>(_node);
		//Button* btn1 = _panel->getButton("sbtn_inpanel_button2_stay");
		//Button* btn2 = _panel->getButton("sbtn_my_edit_button");
		//Button* btn3 = _panel->getButton("sbtn_scroll_panel");
		//if (btn1 && btn2 && btn3) {
		//	if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint)) && btn1->isEnabled()){
		//		btn1->setSkelAnimation("inpanel_button_out", false);
		//		btn1->setSkelAppendAnimation("inpanel_button_stay");
		//	}
		//	else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint)) && btn2->isEnabled()){
		//		return true;
		//	}
		//	else if (btn3->hasCollided(btn3->convertToNodeSpace(tableTouchPoint)) && btn3->isEnabled()){
		//		return true;
		//	}
		//}
	}
	return false;
}

bool LobbyReplayPanel::cellTouch(const CCPoint& tableTouchPoint)
{
	if (m_pReplayListContainer != nullptr)
	{
		auto& panelNodes = m_pReplayListContainer->getChildren();
		for (auto _node : panelNodes)
		{
			//Panel* _panel = dynamic_cast<Panel*>(_node);
			//Button* btn1 = _panel->getButton("sbtn_inpanel_button2_stay");
			//Button* btn2 = _panel->getButton("sbtn_my_edit_button");
			//Button* btn3 = _panel->getButton("sbtn_scroll_panel");
			//if (btn1 && btn2 && btn3) {
			//	if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint)) && btn1->isEnabled()){
			//		string _BtnName = "ReplayButton" + StringConverter::toString(btn1->getTag());
			//		onClicked(_BtnName);
			//		btn1->setSkelAnimation("inpanel_button_out", false);
			//		btn1->setSkelAppendAnimation("inpanel_button_stay");
			//	}
			//	else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint)) && btn2->isEnabled()){
			//		if (m_pTextField != nullptr)
			//		{
			//			m_pTextField->detachWithIME();
			//			onDetached();
			//		}

			//		m_SelectItem = btn1->getTag();
			//		string _BtnName = "EditBtn" + StringConverter::toString(btn2->getTag());
			//		onClicked(_BtnName);
			//	}
			//	else if (btn3->hasCollided(btn3->convertToNodeSpace(tableTouchPoint)) && btn3->isEnabled()){
			//		string _BtnName = "ShowInfoBtn" + StringConverter::toString(btn3->getTag());
			//		onClicked(_BtnName);
			//	}
			//}
		}
	}
	return false;
}

void LobbyReplayPanel::cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}

void LobbyReplayPanel::ScrollViewOffsetProcess(float _dt)
{
	if (m_bMovingCell == false)
		return;

	if (m_pReplayListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pReplayListView->getContentOffset();
	int _size = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size();

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
		if (_offSetPoint.y >= _minMove && m_CellIndex + REPLAY_CELL_MAX < _size)
		{
			m_CellIndex++;
			m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, mCellSize.height - m_fMoveG));
			for (int _i = 0; _i < REPLAY_CELL_MAX; _i++)
			{
				UpdateReplayCell(_i, _size - REPLAY_CELL_MAX - m_CellIndex + _i);
			}
		}
		else
			m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
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
			m_pReplayListView->setContentOffset(_offSetPoint + ccp(0, mCellSize.height - m_fMoveG));
			for (int _i = 0; _i < REPLAY_CELL_MAX; _i++)
			{
				UpdateReplayCell(_i, _size - REPLAY_CELL_MAX - m_CellIndex + _i);
			}
		}
		else
			m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
	}
}

void LobbyReplayPanel::CreateCell(int _size)
{
	int _MakeCellSize = _size;
	if (_MakeCellSize > REPLAY_CELL_MAX)
		_MakeCellSize = REPLAY_CELL_MAX;

	for (int _i = 0; _i < _MakeCellSize; _i++)
	{
		m_ListCell[_i] = new RpBarPanel();
		m_ListCell[_i]->setTag(-1);
		CCSize _ButtonPanelSize = m_ListCell[_i]->getDummy("dmy_rp_bar").size;
		m_ListCell[_i]->setPosition(ccp(1.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (mCellSize.height * _i)));
		m_pReplayListContainer->addChild(m_ListCell[_i]);
		m_ListCell[_i]->release();
		m_ListCell[_i]->setListener(this);		
	}
}

void LobbyReplayPanel::UpdateReplayCell(int _toIdx, int _dstIdx)
{
	if (_dstIdx >= GameDataManager::getSingletonPtr()->m_ReplaySaveList.size())
		return;



	int _dataSize = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size() - 1;
	m_ListCell[_toIdx]->setTag(_dataSize - _dstIdx);
	W_ReplaySaveInfo* _pInfo = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_dataSize - _dstIdx];

	if ((_dataSize - _dstIdx) % 2 == 1)	{
		m_ListCell[_toIdx]->getSkel("skel_bar")->playAnimation("bar_relonga");
		m_ListCell[_toIdx]->getSkel("skel_recommend")->playAnimation("recommend_a");
		m_ListCell[_toIdx]->getLabel("txt_recommend")->setColor(ccc3(217, 167, 118));
	}
	else {
		m_ListCell[_toIdx]->getSkel("skel_bar")->playAnimation("bar_relongb");
		m_ListCell[_toIdx]->getSkel("skel_recommend")->playAnimation("recommend_b");
		m_ListCell[_toIdx]->getLabel("txt_recommend")->setColor(ccc3(185, 132, 81));
	}

	if (_pInfo == nullptr)
	{
		return;
	}

	string titleStr = "";

	if (_pInfo->title().length() == 0)
	{
		int count = 0;
		GamePlaySummaryData summaryData = _pInfo->gamesummarydata();
		//titleStr = GameDataManager::getSingletonPtr()->GetChannelGradeName(_pInfo->channelid());
		titleStr = GameDataManager::getSingletonPtr()->GetChannelGradeName(summaryData.channelgrade());
		if (titleStr.length() > 0)
		{
			titleStr = "[" + titleStr + "] ";
		}

		titleStr = "[" + _pInfo->title() + "] ";
		UserSummaryInfo userInfo;
		for (int i = 0, j = summaryData.usersummaryinfo_size(); i < j; i++)
		{
			userInfo = summaryData.usersummaryinfo(i);
			if (userInfo.winkind() >= WinKind::GIVEUP_WIN)
			{
				if (count == 0) {	//기덕 수정 1명만 나오게 수정 					
					titleStr += userInfo.nickname();
				}
				count++;
			}
		}

		if (count >= 1) {
			titleStr = NxGetFormatString(GameStringDepot::getSingleton().getString("TXT_OF_REPLAY"), titleStr);
		}
	}
	else {
		titleStr = _pInfo->title();
	}

	m_ListCell[_toIdx]->SetRank(_dataSize - _dstIdx + 1);
	m_ListCell[_toIdx]->SetString(_pInfo->date(), _pInfo->title(), StringConverter::toString(_pInfo->likecnt()));
	m_ListCell[_toIdx]->SetScore(_pInfo->point());
	m_ListCell[_toIdx]->setGameType(_pInfo->gametype());

// 	SkelObject* _userPhoto = m_ListCell[_toIdx]->m_Photo;
// 
// 	switch (_pInfo->gametype())
// 	{
// 	case GameKind::GAMEKIND_7POKER:
// 		_userPhoto->playAnimation("symbol_sevenpoker");
// 		break;
// 	case GameKind::GAMEKIND_HIGH_LOW:
// 		_userPhoto->playAnimation("symbol_highlow");
// 		break;
// 	case GameKind::GAMEKIND_BADUKI:
// 		_userPhoto->playAnimation("symbol_badugi");
// 		break;
// 	case GameKind::GAMEKIND_HOLDEM:
// 		_userPhoto->playAnimation("symbol_texasholdem");
// 		break;
// 	default:
// 		_userPhoto->playAnimation("symbol_allgame");
// 		break;
// 	}	
}

void LobbyReplayPanel::ShowGiftList()
{

	CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::WEEKLY_REWOARD_TYPE);

	if (panel)
	{
		LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
	}
	
}

void LobbyReplayPanel::ShowReplayInfoPanel(int _idx, int _type)
{
	eReplayType _replaytype = (eReplayType)(m_TapIndex + REPLAY_TYPE_INIT);
	CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::REPLAY_INFO_TYPE, _idx, _type, _replaytype);
	if (panel)
	{
		LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
	}
}

void LobbyReplayPanel::onDetached()
{
	m_pTextField->setListener(nullptr);
	string _field = m_pTextField->getString();

	if (GameDataManager::getSingletonPtr()->m_ReplaySaveList[m_SelectItem]->has_seq())
	{
		int64 _seq = GameDataManager::getSingletonPtr()->m_ReplaySaveList[m_SelectItem]->seq();
		WebService::getSingletonPtr()->_sendReplayModifyReq(_seq, _field);
	}

	m_pTextField = nullptr;
}

void LobbyReplayPanel::onLayerMessage(const string& msg)
{
	onClicked(msg);
}

void LobbyReplayPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}