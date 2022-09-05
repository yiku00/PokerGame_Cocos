#include "pch.h"
#include "PopupUserReplayPanel.h"

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

PopupUserReplayPanel::PopupUserReplayPanel()
{
	mLoginProcess = false;

	m_pReplayListView = nullptr;
	m_pReplayListContainer = nullptr;

	InitPanel();
	InitImage();
	initButton();

	setTouchable(true, 0, false);
	setButtonListener(this);

	unscheduleUpdate();

	m_ViewDataIndex = 10;
}

PopupUserReplayPanel::~PopupUserReplayPanel()
{
	unscheduleUpdate();
	//destruct();
}

void PopupUserReplayPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_otherstorage.mxml");
}

void PopupUserReplayPanel::InitImage()
{
	getSkel("skel_small_title")->setSkin("title_otherstorage");

	getLabel("txt_tab1_empty")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_othername")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_othername_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
}

void PopupUserReplayPanel::SetUserReplyBoxTitle(string _title)
{
	getLabel("txt_othername")->setString(_title.c_str());
	getLabel("txt_othername_under")->setString(_title.c_str());
}

void PopupUserReplayPanel::initButton()
{
	getButton("sbtn_title_cancel_stay")->getButtonSkelObject()->setSkin("mark_cancel");
	getButton("sbtn_title_cancel_stay")->setType(Button::NoPressImg);
	/*getButton("sbtn_title_cancel_stay")->setListener(this);*/

	getButton("sbtn_grange_on_stay1")->setSkelAnimation("grange_on_stay");
	getButton("sbtn_grange_on_stay1")->setType(Button::NoPressImg);
	getButton("sbtn_grange_on_stay1")->setListener(this);

	getButton("sbtn_grange_on_stay2")->setSkelAnimation("grange_off_stay");
	getButton("sbtn_grange_on_stay2")->setType(Button::NoPressImg);
	getButton("sbtn_grange_on_stay2")->setListener(this);

	m_TapIndex = 0;

}


bool PopupUserReplayPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_bMovingCell = false;
	m_fMoveG = 0.f;

	CCPoint _pos = convertToNodeSpace(pTouch->getLocation());
	float _maxHight = DESIGN_HEIGHT - 72;
	if (_maxHight < _pos.y)
		return false;

	m_bTouchCancel = false;
	cellTouchStart(pTouch->getLocation());

	return true;
}


void PopupUserReplayPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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
		if (m_fMoveG > USER_REPLAY_CELL_HEIGHT)
		{
			m_fMoveG = USER_REPLAY_CELL_HEIGHT;
		}
	}
	else if (_moveV < 0)
	{
		if (m_fMoveG < -USER_REPLAY_CELL_HEIGHT)
		{
			m_fMoveG = -USER_REPLAY_CELL_HEIGHT;
		}
	}

	if (_size <= USER_REPLAY_CELL_MAX)	//셀 수가 MAX보다 많고
	{
		m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, _moveV));
		return;
	}

	bool _bMove = false;
	if (_moveV > 0)
	{
		float _maxMove = -USER_REPLAY_CELL_HEIGHT * 2.5f;
		if (_offSetPoint.y <= _maxMove)
		{
			if (m_CellIndex > 0)
			{
				m_CellIndex--;
				m_pReplayListView->setContentOffset(_offSetPoint + ccp(0, USER_REPLAY_CELL_HEIGHT));
				for (int _i = 0; _i < USER_REPLAY_CELL_MAX; _i++)
				{
					UpdateReplayCell(_i, _size - USER_REPLAY_CELL_MAX - m_CellIndex + _i);
				}
				_bMove = true;
			}
		}
	}
	else if (_moveV < 0)
	{
		float _minMove = -USER_REPLAY_CELL_HEIGHT;
		if (_offSetPoint.y >= _minMove)
		{
			if (m_CellIndex + USER_REPLAY_CELL_MAX < _size)
			{
				m_CellIndex++;
				m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, USER_REPLAY_CELL_HEIGHT));
				for (int _i = 0; _i < USER_REPLAY_CELL_MAX; _i++)
				{
					UpdateReplayCell(_i, _size - USER_REPLAY_CELL_MAX - m_CellIndex + _i);
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


void PopupUserReplayPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
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



void PopupUserReplayPanel::resume()
{
}

void PopupUserReplayPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (strncmp("ReplayButton", name.c_str(), 12) == 0)
	{
		int _index = nxExtractInt(name, "ReplayButton");
		
		if (GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->has_seq())
		{
			int64 _seq = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->seq();
			bool _isLike = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->islike();
			ReplayGameManager::getSingletonPtr()->SetIsLike(_isLike);
			eReplayType _type = eReplayType::Person;

			WebService::getSingletonPtr()->_sendReplayStartReq(_type, _seq);
		}
	}

	if (strncmp("EditBtn", name.c_str(), 7) == 0)
	{
		int _index = nxExtractInt(name, "EditBtn");

		if (m_TapIndex == 2)
		{
			ShowReplayInfoPanel(_index, REPLAY_OWN::OWN_MINE);
		}
		else
		{
			ShowReplayInfoPanel(_index, REPLAY_OWN::OWN_SOMEONE);
		}
	}

	if (name == "sbtn_grange_on_stay1")
	{

	}

	if (name == "sbtn_grange_on_stay2")
	{

	}

}

void PopupUserReplayPanel::ClickTapButton(int _idx)
{

}

void PopupUserReplayPanel::update(float dt)
{
	ScrollViewOffsetProcess(dt);
}

bool PopupUserReplayPanel::handling(STCMD &stCmd)
{
	return false;
}

void PopupUserReplayPanel::SetReplayList()
{
	m_CellIndex = 0;
	m_bMovingCell = false;
	scheduleUpdate();

	ClearReplayList();

	m_pReplayListContainer = CCLayer::create();
	CCSize _contentSize = getDummy("dmy_tab1_scrollsize_1").size - CCSize(ccp(0.f, 10.f));

	int _size = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size();
	CreateReplayCell(_size);

	//for (int _i = 0; _i < _size; _i++)
	//{
	//	W_ReplaySaveInfo* _pInfo = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_i];
	//	if (_pInfo)
	//	{
	//		if (_i < USER_REPLAY_CELL_MAX)
	//		{
	//			//m_ListCell[_i] = CreateReplayCell(_i);
	//			//m_pReplayListContainer->addChild(m_ListCell[_i]);
	//			//m_ListCell[_i]->release();
	//			int _idx = _size - USER_REPLAY_CELL_MAX;
	//			if (_idx < 0)
	//			{
	//				_idx = 0;
	//			}
	//			UpdateReplayCell(_i, _idx + _i);
	//		}
	//	}
	//}
	int _dstIdx = _size - USER_REPLAY_CELL_MAX - m_CellIndex;
	if (_dstIdx < 0)
	{
		m_CellIndex += _dstIdx;
		if (m_CellIndex < 0)
			m_CellIndex = 0;
		_dstIdx = 0;
	}

	for (int _i = 0; _i < USER_REPLAY_CELL_MAX; _i++)
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

		m_pReplayListContainer->setContentSize(CCSizeMake(_contentSize.width, USER_REPLAY_CELL_HEIGHT * _listSize));
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
	m_pReplayListView->setContentOffset(ccp(0, _contentSize.height - (USER_REPLAY_CELL_HEIGHT*_size)), false);

	CCPoint _ListPos = _contentSize / -2.f;
	m_pReplayListView->setPosition(_ListPos);
	getSkel("skel_tab1_panel_f1_2_center4")->addChild(m_pReplayListView, 10);
	m_pReplayListView->setTouchEnabled(false);
	//getSkel("skel_tab1_panel_f1_2_center4")->setVisible(false);
}



void PopupUserReplayPanel::ClearReplayList()
{
	if (m_pReplayListContainer)
	{
		m_pReplayListContainer->cleanup();
		m_pReplayListContainer->removeFromParent();
		m_pReplayListContainer = nullptr;
	}

	if (m_pReplayListView)
	{
		m_pReplayListView->cleanup();
		m_pReplayListView->removeFromParent();
		m_pReplayListView = nullptr;
	}
}

bool PopupUserReplayPanel::cellTouchStart(const CCPoint& tableTouchPoint)
{
	if (m_pReplayListContainer == nullptr)
		return false;


	auto& panelNodes = m_pReplayListContainer->getChildren();
	for(auto _node : panelNodes)
	{
		Panel* _panel = dynamic_cast<Panel*>(_node);
		Button* btn1 = _panel->getButton("sbtn_inpanel_button2_stay");
		Button* btn2 = _panel->getButton("sbtn_my_edit_button");
		Button* btn3 = _panel->getButton("sbtn_scroll_panel");
		if (btn1 && btn2 && btn3) {
			if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint)) && btn1->isEnabled()){
				btn1->setSkelAnimation("inpanel_button_in", false);
				return true;
			}
			else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint)) && btn2->isEnabled()){
				return true;
			}
			else if (btn3->hasCollided(btn3->convertToNodeSpace(tableTouchPoint)) && btn3->isEnabled()){
				return true;
			}
		}
	}

	return false;
}

bool PopupUserReplayPanel::cellTouchCancel(const CCPoint& tableTouchPoint)
{
	if (m_pReplayListContainer == nullptr)
		return false;

	auto& panelNodes = m_pReplayListContainer->getChildren();
	for (auto _node : panelNodes)
	{
		Panel* _panel = dynamic_cast<Panel*>(_node);
		Button* btn1 = _panel->getButton("sbtn_inpanel_button2_stay");
		Button* btn2 = _panel->getButton("sbtn_my_edit_button");
		Button* btn3 = _panel->getButton("sbtn_scroll_panel");
		if (btn1 && btn2 && btn3) {
			if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint)) && btn1->isEnabled()){
				btn1->setSkelAnimation("inpanel_button_out", false);
				btn1->setSkelAppendAnimation("inpanel_button_stay");
			}
			else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint)) && btn2->isEnabled()){
					return true;
			}
			else if (btn3->hasCollided(btn3->convertToNodeSpace(tableTouchPoint)) && btn3->isEnabled()){
				//return false;
			}
		}
	}
	return false;
}

bool PopupUserReplayPanel::cellTouch(const CCPoint& tableTouchPoint)
{
	if (m_pReplayListContainer != nullptr)
	{
		auto& panelNodes = m_pReplayListContainer->getChildren();
		for (auto _node : panelNodes)
		{
			Panel* _panel = dynamic_cast<Panel*>(_node);
			Button* btn1 = _panel->getButton("sbtn_inpanel_button2_stay");
			Button* btn2 = _panel->getButton("sbtn_my_edit_button");
			Button* btn3 = _panel->getButton("sbtn_scroll_panel");
			if (btn1 && btn2 && btn3) {
				if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint)) && btn1->isEnabled()){
					string _BtnName = "ReplayButton" + StringConverter::toString(btn1->getTag());
					onClicked(_BtnName);
					btn1->setSkelAnimation("inpanel_button_out", false);
					btn1->setSkelAppendAnimation("inpanel_button_stay");
				}
				else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint)) && btn2->isEnabled()){
					string _BtnName = "EditBtn" + StringConverter::toString(btn2->getTag());
					onClicked(_BtnName);
				}
				else if (btn3->hasCollided(btn3->convertToNodeSpace(tableTouchPoint)) && btn3->isEnabled()){
					string _BtnName = "EditBtn" + StringConverter::toString(btn3->getTag());
					onClicked(_BtnName);
				}
			}
		}
	}
	return false;
}

void PopupUserReplayPanel::cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}

void PopupUserReplayPanel::ScrollViewOffsetProcess(float _dt)
{
	if (m_bMovingCell == false)
		return;

	if (m_pReplayListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pReplayListView->getContentOffset();
	int _size = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size();

	if (m_fMoveG < 0)
	{
		m_fMoveG += USER_REPLAY_CELL_HEIGHT * 0.5f * _dt;

		if (m_fMoveG > -5.f)
		{
			m_bMovingCell = false;
			m_fMoveG = 0.f;
			return;
		}

		float _minMove = -USER_REPLAY_CELL_HEIGHT;
		if (_offSetPoint.y >= _minMove && m_CellIndex + USER_REPLAY_CELL_MAX < _size)
		{
			m_CellIndex++;
			m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, USER_REPLAY_CELL_HEIGHT - m_fMoveG));
			for (int _i = 0; _i < USER_REPLAY_CELL_MAX; _i++)
			{
				UpdateReplayCell(_i, _size - USER_REPLAY_CELL_MAX - m_CellIndex + _i);
			}
		}
		else
			m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
	}
	else
	{
		m_fMoveG -= USER_REPLAY_CELL_HEIGHT * 0.5f * _dt;

		if (m_fMoveG < 5.f)
		{
			m_bMovingCell = false;
			m_fMoveG = 0.f;
			return;
		}

		float _maxMove = -USER_REPLAY_CELL_HEIGHT * 2.5f;
		if (_offSetPoint.y <= _maxMove && m_CellIndex > 0)
		{
			m_CellIndex--;
			m_pReplayListView->setContentOffset(_offSetPoint + ccp(0, USER_REPLAY_CELL_HEIGHT - m_fMoveG));
			for (int _i = 0; _i < USER_REPLAY_CELL_MAX; _i++)
			{
				UpdateReplayCell(_i, _size - USER_REPLAY_CELL_MAX - m_CellIndex + _i);
			}
		}
		else
			m_pReplayListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
	}
}

void PopupUserReplayPanel::CreateReplayCell(int _size)
{
	int _MakeCellSize = _size;
	if (_MakeCellSize > USER_REPLAY_CELL_MAX)
		_MakeCellSize = USER_REPLAY_CELL_MAX;

	for (int _i = 0; _i < _MakeCellSize; _i++)
	{
		m_ListCell[_i] = new Panel();

		m_ListCell[_i]->construct(getMxmlPath() + "dmy_rp_bar.mxml");
		m_ListCell[_i]->setTag(-1);

		CCSize _ButtonPanelSize = m_ListCell[_i]->getDummy("dmy_rp_bar").size;
		int _dataSize = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size() - 1;

		m_ListCell[_i]->setPosition(ccp(10.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (USER_REPLAY_CELL_HEIGHT * _i)));

		Button* _pButton = m_ListCell[_i]->getButton("sbtn_inpanel_button2_stay");
		_pButton->getButtonSkelObject()->playAnimation("inpanel_button_stay");
		_pButton->getButtonSkelObject()->setSkin("image_replay");
		_pButton->setType(Button::NoPressImg);
		_pButton->setTag((_dataSize - _i));
		_pButton->setListener(this);
		_pButton->setPaused(true);

		m_ListCell[_i]->getButton("sbtn_scroll_panel")->setType(Button::NoPressImg);
		m_ListCell[_i]->getButton("sbtn_scroll_panel")->setPaused(true);
		m_ListCell[_i]->getButton("sbtn_scroll_panel")->setTag((_dataSize - _i));

		m_ListCell[_i]->getLabel("txt_expertscore")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_expertgrade")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_recommend")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_savedate")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_replaytitle")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_my_savedate")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		Nx::Label* _pScore = m_ListCell[_i]->getLabel("txt_expertscore");
		Nx::Label* _pGrade = m_ListCell[_i]->getLabel("txt_expertgrade");
		Nx::Label* _Recommend = m_ListCell[_i]->getLabel("txt_recommend");
		Nx::Label* _pSaveData = m_ListCell[_i]->getLabel("txt_savedate");
		Nx::Label* _pReplayTitle = m_ListCell[_i]->getLabel("txt_replaytitle");

		SkelObject* _userPhoto = m_ListCell[_i]->getSkel("skel_userphoto");
		SkelObject* _userPhotoLine = m_ListCell[_i]->getSkel("skel_userphoto_line");

		SkelObject* _MyPhotoSpace = m_ListCell[_i]->getSkel("skel_my_inpanelspace");
		SkelObject* _MyPhoto = m_ListCell[_i]->getSkel("skel_my_userphoto");
		SkelObject* _MyPhotoLine = m_ListCell[_i]->getSkel("skel_my_userphoto_line");
		Nx::Label* _pMySaveData = m_ListCell[_i]->getLabel("txt_my_savedate");
		TextField* _pMyReplayTitle = m_ListCell[_i]->getTextField("fld_my_replaytitle");
		Button* _pMyEditBtn = m_ListCell[_i]->getButton("sbtn_my_edit_button");

		m_ListCell[_i]->getSkel("skel_rank_1")->setVisible(false);
		m_ListCell[_i]->getSkel("skel_rank_2")->setVisible(false);
		m_ListCell[_i]->getSkel("skel_rank_3")->setVisible(false);

		_MyPhotoSpace->setVisible(false);
		_MyPhoto->setVisible(false);
		_MyPhotoLine->setVisible(false);
		_pMySaveData->setVisible(false);
		_pMyReplayTitle->setVisible(false);

		_pMyEditBtn->setVisible(false);
		_pMyEditBtn->setEnable(false);

		m_ReplayRankLabel[_i] = CCLabelBMFont::create("", "fonts/number_rank.fnt");
		m_ReplayRankLabel[_i]->retain();
		m_ReplayRankLabel[_i]->setAnchorPoint(ccp(0.5f, 0.8f));
		m_ReplayRankLabel[_i]->setScale(0.9f);
		m_ReplayRankLabel[_i]->setPosition(m_ListCell[_i]->getSkel("skel_rank_1")->getPosition());
		m_ReplayRankLabel[_i]->setString(StringConverter::toString((_dataSize - _i + 1)).c_str());
		m_ListCell[_i]->addChild(m_ReplayRankLabel[_i]);
		m_ReplayRankLabel[_i]->release();
		
		m_ListCell[_i]->setPosition(ccp(1.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (USER_REPLAY_CELL_HEIGHT * _i)));
		m_pReplayListContainer->addChild(m_ListCell[_i]);
		m_ListCell[_i]->release();
	}

}

void PopupUserReplayPanel::UpdateReplayCell(int _toIdx, int _dstIdx)
{
	//m_ListCell[_toIdx]->getButton("sbtn_inpanel_button2_stay")->setTag(_dstIdx);
	//m_ListCell[_toIdx]->getButton("sbtn_scroll_panel")->setTag(_dstIdx);

	if (_dstIdx >= GameDataManager::getSingletonPtr()->m_ReplaySaveList.size())
		return;

	if (m_ListCell[_toIdx]->getTag() == _dstIdx)
		return;

	m_ListCell[_toIdx]->setTag(_dstIdx);

	CCSize _ButtonPanelSize = m_ListCell[_toIdx]->getDummy("dmy_rp_bar").size;
	int _dataSize = GameDataManager::getSingletonPtr()->m_ReplaySaveList.size() - 1;

	//m_ListCell[_toIdx]->setPosition(ccp(10.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (USER_REPLAY_CELL_HEIGHT * _dstIdx)));

	Button* _pButton = m_ListCell[_toIdx]->getButton("sbtn_inpanel_button2_stay");
	_pButton->setTag((_dataSize - _dstIdx));

	m_ListCell[_toIdx]->getButton("sbtn_scroll_panel")->setTag((_dataSize - _dstIdx));

	Nx::Label* _pScore = m_ListCell[_toIdx]->getLabel("txt_expertscore");
	Nx::Label* _pGrade = m_ListCell[_toIdx]->getLabel("txt_expertgrade");
	Nx::Label* _Recommend = m_ListCell[_toIdx]->getLabel("txt_recommend");
	Nx::Label* _pSaveData = m_ListCell[_toIdx]->getLabel("txt_savedate");
	Nx::Label* _pReplayTitle = m_ListCell[_toIdx]->getLabel("txt_replaytitle");

	SkelObject* _userPhoto = m_ListCell[_toIdx]->getSkel("skel_userphoto");
	SkelObject* _userPhotoLine = m_ListCell[_toIdx]->getSkel("skel_userphoto_line");

	SkelObject* _MyPhotoSpace = m_ListCell[_toIdx]->getSkel("skel_my_inpanelspace");
	SkelObject* _MyPhoto = m_ListCell[_toIdx]->getSkel("skel_my_userphoto");
	SkelObject* _MyPhotoLine = m_ListCell[_toIdx]->getSkel("skel_my_userphoto_line");
	Nx::Label* _pMySaveData = m_ListCell[_toIdx]->getLabel("txt_my_savedate");
	TextField* _pMyReplayTitle = m_ListCell[_toIdx]->getTextField("fld_my_replaytitle");
	Button* _pMyEditBtn = m_ListCell[_toIdx]->getButton("sbtn_my_edit_button");

	
	W_ReplaySaveInfo* _pInfo = GameDataManager::getSingletonPtr()->m_ReplaySaveList[(_dataSize - _dstIdx)];

	if (_pInfo == nullptr)
	{
		return;
	}

	if (m_TapIndex == 0) // || m_TapIndex == 1)
	{
		if (_pInfo->has_title())
		{
			if (_pInfo->title().length() == 0)
			{
				int count = 0;
				GamePlaySummaryData summaryData = _pInfo->gamesummarydata();

				string titleStr = GameDataManager::getSingletonPtr()->GetChannelGradeName(_pInfo->channelid());

				if (titleStr.length() > 0)
				{
					titleStr = "[" + titleStr + "] ";
				}

				UserSummaryInfo userInfo;
				for (int i = 0, j = summaryData.usersummaryinfo_size(); i < j; i++)
				{
					userInfo = summaryData.usersummaryinfo(i);
					if (userInfo.winkind() >= WinKind::GIVEUP_WIN)
					{
						if (count > 0)
							titleStr += ",";
						titleStr += userInfo.nickname();
						count++;
					}
				}

				if (count >= 1) {
					titleStr = NxGetFormatString(GameStringDepot::getSingleton().getString("TXT_OF_REPLAY"), titleStr);
				}
				_pReplayTitle->setString(titleStr.c_str());
			}
			else
				_pReplayTitle->setString(_pInfo->title().c_str());

			_pReplayTitle->setVisible(true);
		}

		if (_pInfo->has_date())
		{
			_pSaveData->setString(_pInfo->date().c_str());
		}

		m_ReplayRankLabel[_toIdx]->setString(StringConverter::toString((_dataSize - _dstIdx + 1)).c_str());

		if (_pInfo->has_gametype())
		{
			switch (_pInfo->gametype())
			{
			case GameKind::GAMEKIND_7POKER:
				_userPhoto->playAnimation("symbol_sevenpoker");
				break;
			case GameKind::GAMEKIND_HIGH_LOW:
				_userPhoto->playAnimation("symbol_highlow");
				break;
			case GameKind::GAMEKIND_BADUKI:
				_userPhoto->playAnimation("symbol_badugi");
				break;
			case GameKind::GAMEKIND_HOLDEM:
				_userPhoto->playAnimation("symbol_texasholdem");
				break;
			default:
				_userPhoto->playAnimation("symbol_allgame");
				break;
			}
		}
	}
	
	if (_pInfo->has_point())
	{
		_pScore->setString(StringConverter::toString(_pInfo->point()).c_str());
	}

	if (_pInfo->has_likecnt())
	{
		_Recommend->setString(StringConverter::toString(_pInfo->likecnt()).c_str());
	}
}

void PopupUserReplayPanel::ShowReplayInfoPanel(int _idx, int _type)
{
	CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::REPLAY_INFO_TYPE, _idx, _type, eReplayType::Person);

	if (panel)
	{
		LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
	}
}