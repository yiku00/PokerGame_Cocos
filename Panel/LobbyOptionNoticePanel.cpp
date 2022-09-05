#include "pch.h"
#include "LobbyOptionNoticePanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "SimplePopupPanel.h"
#include "GameStringDepot.h"
#include "PokerChipWidget.h"
#include "LobbyTopUiPanel.h"
#include "LobbyUIPanel.h"
#include "PokerChipWidget.h"
#include "LobbyTopUiPanel.h"
#include "LobbyUIPanel.h"
#include "PokerResourceHelper.h"
#include "PokerShopHelper.h"

LobbyOptionNoticePanel::LobbyOptionNoticePanel()
{
	m_CellIndex = 0;
	m_bMovingCell = false;

	mLoginProcess = false;
	m_pLetterListView = nullptr;
	m_pLetterListContainer = nullptr;

	for (int _i = 0; _i < MAX_LETTER_CELL; _i++)
	{
		m_CellBtnPanel[_i] = nullptr;
	}

	InitPanel();
	InitImage();
	initButton();

	//setTouchable(false);
	setTouchable(true);
	setButtonListener(this);
	m_ViewDataIndex = 10;
}

LobbyOptionNoticePanel::~LobbyOptionNoticePanel()
{
	//destruct();
}

void LobbyOptionNoticePanel::InitPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_option_notice.mxml");
	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);
	
	mMainPanel->getLabel("txt_tab1_letter")->setString(GameStringDepot::getSingleton().getString("TXT_NOTICE_UNIT").c_str());
	mMainPanel->getLabel("txt_tab1_empty")->setString(GameStringDepot::getSingleton().getString("EMPTY_NOTICE_DESC").c_str());

	mCellSize = mMainPanel->getDummy("dmy_l_bar1").size;
}

void LobbyOptionNoticePanel::InitImage()
{
	//m_LetterTitleLabel = getSkel("skel_letter_title");
	//m_LetterTitleMark = getSkel("skel_letter_mark");
	//m_LetterTitleBg = getSkel("skel_title_back");
	//m_ShadowBg = getSkel("skel_mission_title_black");

	//m_LetterTitleLabel->setVisible(false);
	//m_LetterTitleMark->setVisible(false);
	//m_LetterTitleBg->setVisible(false);
	//m_ShadowBg->setVisible(false);

	m_LetterCount = mMainPanel->getLabel("txt_tab1_letter_read");
	m_LetterMaxCount = mMainPanel->getLabel("txt_tab1_letter_max");
	m_LetterCount->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_LetterMaxCount->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	mMainPanel->getLabel("txt_tab1_letter")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_warning_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	//getLabel("txt_tab1_slash")->setVisible(false);

	m_LetterCount->setVisible(false);
	m_LetterMaxCount->setVisible(false);
	mMainPanel->getLabel("txt_warning_sum")->setVisible(false);

}

void LobbyOptionNoticePanel::initButton()
{
	//m_TapBtn = getButton("sbtn_tapbutton_on_stay1");
	//m_TapBtn->getButtonSkelObject()->setSkin("tab_gift");a
	//m_TapBtn->setZOrder(1);
	//m_TapBtn->setType(Button::NoPressImg);
	//m_TapBtn->setEnable(false);

	//m_AllGetBtn = getButton("sbtn_tab1_small_button_2_stay2");
	//m_AllGetBtn->getButtonSkelObject()->setSkin("txt_allget");
	//m_AllGetBtn->setListener(this);
	//m_AllGetBtn->setType(Button::NoPressImg);
	//m_AllGetBtn->setEnable(true);

	/*CCPoint _getBtnPos = mMainPanel->getDummy("dmy_button_small").origin;
	m_BtnPanel = new Panel();
	m_BtnPanel->construct(getMxmlPath() + "dmy_button_small.mxml");
	m_BtnPanel->setPositionX(_getBtnPos.x);
	m_BtnPanel->setPositionY(-_getBtnPos.y);
	mMainPanel->addChild(m_BtnPanel);
	m_BtnPanel->release();
	m_BtnPanel->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_BtnPanel->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	string _btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_ALL_GET_UNIT");
	m_BtnPanel->getLabel("txt_button_under")->setString(_btnTxt.c_str());
	m_BtnPanel->getLabel("txt_button")->setString(_btnTxt.c_str());
	m_AllGetBtn = m_BtnPanel->getButton("sbtn_button");
	m_AllGetBtn->setName("ALL_GET_BUTTON");	
	string _tapTxt = GameStringDepot::getSingletonPtr()->getString("TXT_LETTER_UNIT");	
	m_AllGetBtn->setListener(this);*/
}


bool LobbyOptionNoticePanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLOG("LobbyOptionNoticePanel::ccTouchBegan");
	if (!isVisible())
		return false;

	if (pTouch->getLocation().y >= DESIGN_HEIGHT - 72.f)
		return false;

	if (pTouch->getLocation().x < 175.f)
		return false;


// 	CCRect boudning = CCRectMake(-getPositionX(), -getPositionY(), getContentSize().width, getContentSize().height);
// 	CCPoint point = convertTouchToNodeSpace(pTouch);
// 	if (!boudning.containsPoint(point))
// 		return false;


	m_bMovingCell = false;
	m_fMoveG = 0.f;

	CCPoint _pos = convertToNodeSpace(pTouch->getLocation());

// 	float _maxHight = DESIGN_HEIGHT - 130;
// 	float _minHight = 62;
// 	if (_maxHight < _pos.y || _minHight > _pos.y)
// 		return false;

	m_bTouchCancel = false;
	cellTouchStart(pTouch->getLocation());
	
	return true;
	//return Panel::ccTouchBegan(pTouch, pEvent);
}


void LobbyOptionNoticePanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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

	if (m_pLetterListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pLetterListView->getContentOffset();
	int _size = GameDataManager::getSingletonPtr()->m_pLetterInfoList.size();
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
	

	if (_size <= MAX_LETTER_CELL)			//셀 수가 MAX_LETTER_CELL보다 많고
	{
		m_pLetterListView->setContentOffset(_offSetPoint - ccp(0, _moveV));
		return;
	}

	//float _contentheight = getDummy("dmy_tab1_scrollsize_1").size.height;
	
	bool _bMove = false;
	if (_moveV > 0)
	{
		float _maxMove = -mCellSize.height * 2.5f;
		if (_offSetPoint.y <= _maxMove)
		{
			if (m_CellIndex > 0)
			{
				m_CellIndex--;
				m_pLetterListView->setContentOffset(_offSetPoint + ccp(0, mCellSize.height));
				for (int _i = 0; _i < MAX_LETTER_CELL; _i++)
				{
					UpdateLetterCell(_i, _size - MAX_LETTER_CELL - m_CellIndex + _i);
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
			if (m_CellIndex + MAX_LETTER_CELL < _size)
			{
				m_CellIndex++;
				m_pLetterListView->setContentOffset(_offSetPoint - ccp(0, mCellSize.height));
				for (int _i = 0; _i < MAX_LETTER_CELL; _i++)
				{
					UpdateLetterCell(_i, _size - MAX_LETTER_CELL - m_CellIndex + _i);
				}
				_bMove = true;
			}
		}
	}

	if (_bMove == false)
	{
		m_pLetterListView->setContentOffset(_offSetPoint - ccp(0, _moveV));
	}
}


void LobbyOptionNoticePanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
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



void LobbyOptionNoticePanel::resume()
{
}

void LobbyOptionNoticePanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);

	if (name == "GetLetterButton2")
	{

	//	http : //13.124.143.194:8200/poker_server/usage_terms.htm
	//	#define GAMBLE_PRIVATE_POLICY			"usage_terms.htm"
	//	http : //13.124.143.194:8200/poker_server/poker_web/term/term.jsp?state=5
	//	#define GAMBLE_USE_TERM				"poker_web/term/term.jsp?state=5"
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_CAMPAIGN_TYPE);
	}
	else if (name == "GetLetterButton1")
	{
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_TERM_TYPE);
	}
	else if (name == "GetLetterButton0")
	{
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_CAMPAIGN_TYPE);
	}

}

void LobbyOptionNoticePanel::update(float dt)
{
	ScrollViewOffsetProcess(dt);
}

bool LobbyOptionNoticePanel::handling(STCMD &stCmd)
{
	return false;
}
void LobbyOptionNoticePanel::ShowLetterPanel()
{
	m_CellIndex = 0;
	m_bMovingCell = false;

	ShowLetterUi();
	SetLetterlList();
	ShowLetterTitie();	
}

void LobbyOptionNoticePanel::HideLetterPanel()
{
	HideLetterTitie();
	HideLetterUi();

	//runAction(CCSequence::create(
	//	CCCallFunc::create(this, callfunc_selector(LobbyLetterBoxPanel::HideLetterTitie)),
	//	CCMoveTo::create(0.3f, m_HidePosition),
	//	CCCallFunc::create(this, callfunc_selector(LobbyLetterBoxPanel::HideLetterUi)),
	//	NULL));
}

void LobbyOptionNoticePanel::ShowLetterUi()
{
	scheduleUpdate();
}

void LobbyOptionNoticePanel::HideLetterUi()
{
	unscheduleUpdate();

	ClearLetterList();
	//setVisible(false);
	GameDataManager::getSingletonPtr()->FreeUiProcess();
	LayerManager::getSingleton().popLayer("LobbyLetter");
	//LayerManager::getSingleton().popLayer("LobbyTopUI");
}

void LobbyOptionNoticePanel::ShowLetterTitie()
{
	//m_LetterTitleLabel->setVisible(true);
	//m_LetterTitleMark->setVisible(true);
	//m_LetterTitleBg->setVisible(true);

	//for (Button* _btn : m_TapBtn)
	//{
	//	_btn->setEnable(true);
	//}

	//m_TapBtn->setEnable(true);
	//setTouchable(true);
	GameDataManager::getSingletonPtr()->FreeUiProcess();

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_LETTER);
		}
	}
}

void LobbyOptionNoticePanel::HideLetterTitie()
{
	//m_LetterTitleLabel->setVisible(false);
	//m_LetterTitleMark->setVisible(false);
	//m_LetterTitleBg->setVisible(false);

	//m_TapBtn->setEnable(false);
	//setTouchable(false);

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MAIN);
		}
	}
}

void LobbyOptionNoticePanel::SetLetterlList()
{
	ClearLetterList();

	m_pLetterListContainer = CCLayer::create();
	CCSize _contentSize = mMainPanel->getDummy("dmy_tab1_scrollsize_1").size;

	int _size = 1;//GameDataManager::getSingletonPtr()->m_pLetterInfoList.size();
	CreateCell(_size);

	int _dstIdx = _size - MAX_LETTER_CELL - m_CellIndex;
	if (_dstIdx < 0)
	{
		m_CellIndex += _dstIdx;
		if (m_CellIndex < 0)
			m_CellIndex = 0;
		_dstIdx = 0;
	}

	for (int _i = 0; _i < MAX_LETTER_CELL; _i++)
	{
		if (_i < _size)
		{
			//UpdateLetterCell(_i, _dstIdx + _i);
		}
	}

	if (_size > 0)
	{
		mMainPanel->getLabel("txt_tab1_empty")->setVisible(false);

		int _listSize = _size;
		if (_listSize > MAX_LETTER_CELL)
			_listSize = MAX_LETTER_CELL;

		m_pLetterListContainer->setContentSize(CCSizeMake(_contentSize.width, mCellSize.height * _listSize));
	}
	else
	{
		mMainPanel->getLabel("txt_tab1_empty")->setVisible(true);
		mMainPanel->getLabel("txt_tab1_empty")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		m_pLetterListContainer->setContentSize(_contentSize);
	}

	if (m_pLetterListView == nullptr) {
		m_pLetterListView = CCScrollView::create(_contentSize, m_pLetterListContainer);
		m_pLetterListView->setDirection(extension::ScrollView::Direction::VERTICAL);
		m_pLetterListView->setBounceable(false);
		//가장 상단으로 올리기.
		//m_pLetterListView->setContentOffset(ccp(0, 0), false);
		CCPoint _ListPos = mMainPanel->getDummy("dmy_tab1_scrollsize_1").origin;
		m_pLetterListView->setPositionX(_ListPos.x);
		m_pLetterListView->setPositionY(DESIGN_HEIGHT - _ListPos.y - _contentSize.height);
		mMainPanel->addChild(m_pLetterListView, 10);
	}
	m_pLetterListView->setContentOffset(ccp(0, -(mCellSize.height*MAX_LETTER_CELL)), false);
	m_pLetterListView->setTouchEnabled(false);
}

void LobbyOptionNoticePanel::ClearLetterList()
{
	if (m_pLetterListContainer)
	{
		m_pLetterListContainer->cleanup();
		m_pLetterListContainer->removeFromParent();
	}
	m_pLetterListContainer = nullptr;

	if (m_pLetterListView)
	{
		m_pLetterListView->cleanup();
		m_pLetterListView->removeFromParent();
	}
	m_pLetterListView = nullptr;
}


bool LobbyOptionNoticePanel::cellTouchStart(const CCPoint& tableTouchPoint)
{
	if (m_pLetterListContainer == nullptr)
		return false;

	auto& panelNodes = m_pLetterListContainer->getChildren();
	for(auto _node : panelNodes)
	{
		//Panel* _panel = dynamic_cast<Panel*>(_node);
		//Button* btn = _panel->getButton("sbtn_inpanel_button2_stay");
		//if (btn) {
		//	if (btn->hasCollided(btn->convertToNodeSpace(tableTouchPoint))){
		//		if (btn->isEnabled()){
		//			btn->setSkelAnimation("inpanel_button_in", false);
		//			return true;
		//		}
		//	}
		//}
	}

	return false;
}

void LobbyOptionNoticePanel::cellTouchCancel(const CCPoint& tableTouchPoint)
{
	if (m_pLetterListContainer == nullptr)
		return;

	auto& panelNodes = m_pLetterListContainer->getChildren();
	for (auto _node : panelNodes)
	{
		//Panel* _panel = dynamic_cast<Panel*>(_node);
		//Button* btn1 = _panel->getButton("sbtn_inpanel_button2_stay");
		//if (btn1) {
		//	if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
		//		if (btn1->isEnabled()){
		//			btn1->setSkelAnimation("inpanel_button_out", false);
		//			btn1->setSkelAppendAnimation("inpanel_button_stay");
		//		}
		//	}
		//}
	}


}

bool LobbyOptionNoticePanel::cellTouch(const CCPoint& tableTouchPoint)
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

	if (m_pLetterListContainer != nullptr)
	{
		for (int _i = 0; _i < MAX_LETTER_CELL; _i++)
		{
			if (m_CellBtnPanel[_i] == nullptr)
				continue;

			Button* _btn = m_CellBtnPanel[_i]->getButton("sbtn_button");
			if (_btn)
			{
				if (_btn->hasCollided(_btn->convertToNodeSpace(tableTouchPoint))){
					if (_btn->isEnabled()){						
						string _BtnName = "GetLetterButton" + StringConverter::toString(_btn->getTag());
						onClicked(_BtnName);
					}
				}
			}
		}
		//CCObject* _node;
		//CCArray* panelNodes = m_pLetterListContainer->getChildren();
		//CCARRAY_FOREACH(panelNodes, _node)
		//{
		//	Panel* _panel = dynamic_cast<Panel*>(_node);
		//	Button* btn1 = _panel->getButton("sbtn_inpanel_button2_stay");
		//	if (btn1) {
		//		if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
		//			if (btn1->isEnabled()){
		//				eResourceType _kind = GameDataManager::getSingletonPtr()->m_pLetterInfoList[btn1->getTag()]->rewardinfo().rewardset(0).type();
		//				for (int _i = 0; _i < 8; _i++)
		//				{
		//					PokerChipWidget* _pEffect = PokerChipWidget::createBonus(_kind, tableTouchPoint + _diffPos, 0.2f + _i*0.05f);
		//					if (_pEffect && _pTopPanel)
		//					{
		//						_pTopPanel->addChild(_pEffect);
		//						_pEffect->release();
		//					}
		//				}
		//				string _BtnName = "GetLetterButton" + StringConverter::toString(btn1->getTag());
		//				onClicked(_BtnName);
		//				btn1->setSkelAnimation("inpanel_button_out", false);
		//				btn1->setSkelAppendAnimation("inpanel_button_stay");
		//			}
		//		}
		//	}
		//}
	}
	return false;
}

void LobbyOptionNoticePanel::cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}

void LobbyOptionNoticePanel::ScrollViewOffsetProcess(float _dt)
{
	if (m_bMovingCell == false)
		return;

	if (m_pLetterListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pLetterListView->getContentOffset();
	int _size = GameDataManager::getSingletonPtr()->m_pLetterInfoList.size();

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
		if (_offSetPoint.y >= _minMove && m_CellIndex + MAX_LETTER_CELL < _size)
		{
			m_CellIndex++;
			m_pLetterListView->setContentOffset(_offSetPoint - ccp(0, mCellSize.height - m_fMoveG));
			for (int _i = 0; _i < MAX_LETTER_CELL; _i++)
			{
				UpdateLetterCell(_i, _size - MAX_LETTER_CELL - m_CellIndex + _i);
			}
		}
		else
			m_pLetterListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
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
			m_pLetterListView->setContentOffset(_offSetPoint + ccp(0, mCellSize.height - m_fMoveG));
			for (int _i = 0; _i < MAX_LETTER_CELL; _i++)
			{
				UpdateLetterCell(_i, _size - MAX_LETTER_CELL - m_CellIndex + _i);
			}
		}
		else
			m_pLetterListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
	}

}


void LobbyOptionNoticePanel::CreateCell(int _size)
{
	int _MakeCellSize = _size;
	if (_MakeCellSize > MAX_LETTER_CELL)
		_MakeCellSize = MAX_LETTER_CELL;

	for (int _i = 0; _i < MAX_LETTER_CELL; _i++)
	{
		if (_i >= _size)
		{
			m_ListCell[_i] = nullptr;
			m_CellBtnPanel[_i] = nullptr;
			continue;
		}

		m_ListCell[_i] = new Panel();
		m_ListCell[_i]->setTag(-1);
		m_ListCell[_i]->construct(getMxmlPath() + "dmy_option_notice_bar.mxml");

		CCSize _ButtonPanelSize = m_ListCell[_i]->getDummy("dmy_l_bar").size;		
		CCPoint _btnPos = m_ListCell[_i]->getDummy("dmy_button_small").origin;
		_btnPos.y = -_btnPos.y;
		m_CellBtnPanel[_i] = new Panel();
		m_CellBtnPanel[_i]->construct(getMxmlPath() + "dmy_button_small.mxml");
		m_CellBtnPanel[_i]->setPosition(_btnPos);
		m_ListCell[_i]->addChild(m_CellBtnPanel[_i]);
		m_CellBtnPanel[_i]->release();

		// '보기' 버튼
		Button* _pButton = m_CellBtnPanel[_i]->getButton("sbtn_button");
		_pButton->setTag(_i);
		_pButton->setPaused(true);
		Nx::Label* _pBtnShodow = m_CellBtnPanel[_i]->getLabel("txt_button_under");
		Nx::Label* _pBtnText = m_CellBtnPanel[_i]->getLabel("txt_button");
		_pBtnShodow->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pBtnText->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pBtnShodow->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SHOWTERM_UNIT").c_str());
		_pBtnText->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SHOWTERM_UNIT").c_str());

		// [공지사항]
		// 내용이 이러이러 합니다.
		Nx::Label* _pSendUserName = m_ListCell[_i]->getLabel("txt_username");
		Nx::Label* _pLetterName = m_ListCell[_i]->getLabel("txt_letter_name");
		_pSendUserName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pLetterName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		// 야매로 내용 채우기
		switch (_i)
		{
		case 0:
			m_ListCell[_i]->getSkel("skel_bar")->playAnimation("bar_longb");
			_pSendUserName->setString(GameStringDepot::getSingletonPtr()->getString("TXT_PRIVACY_TITLE").c_str());
			_pLetterName->setString(GameStringDepot::getSingletonPtr()->getString("TXT_TEMP_DATA_2").c_str());
			break;
		default:
			break;
		}

		//Button* _pButton = m_CellBtnPanel[_i]->getButton("sbtn_button");
		//_pButton->setTag(_i);
		//_pButton->setPaused(true);

		//Label* _pBtnShodow = m_CellBtnPanel[_i]->getLabel("txt_button_under");
		//Label* _pBtnText = m_CellBtnPanel[_i]->getLabel("txt_button");

		//Label* _pLetterName = m_ListCell[_i]->getLabel("txt_letter_name");
		//Label* _pSendUserName = m_ListCell[_i]->getLabel("txt_username");
		//Label* _pTimeLimit = m_ListCell[_i]->getLabel("txt_letter_timelimit");
		//Label* _pNum = m_ListCell[_i]->getLabel("txt_buttonsum");

		//_pBtnShodow->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		//_pBtnText->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		//_pLetterName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		//_pSendUserName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		//_pTimeLimit->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		//_pNum->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		////m_ListCell[_i]->getLabel("txt_letter_send")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		//_pBtnShodow->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTER_GET_UNIT").c_str());
		//_pBtnText->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTER_GET_UNIT").c_str());
		//_pTimeLimit->setOpacity(175);

		m_ListCell[_i]->setPosition(ccp(1.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (mCellSize.height * _i)));
		m_pLetterListContainer->addChild(m_ListCell[_i]);
		m_ListCell[_i]->release();
	}
}


void LobbyOptionNoticePanel::UpdateLetterCell(int _toIdx, int _dstIdx)
{
	if (_dstIdx >= GameDataManager::getSingletonPtr()->m_pLetterInfoList.size())
		return;

	if (m_ListCell[_toIdx]->getTag() == _dstIdx)
		return;

	m_ListCell[_toIdx]->setTag(_dstIdx);

	CCSize _ButtonPanelSize = m_ListCell[_toIdx]->getDummy("dmy_l_bar").size;

	int _letterCount = GameDataManager::getSingletonPtr()->m_pLetterInfoList.size();

	if (_dstIdx % 2 != _letterCount % 2)
	{
		m_ListCell[_toIdx]->getSkel("skel_bar")->playAnimation("bar_longa");
	}
	else
	{
		m_ListCell[_toIdx]->getSkel("skel_bar")->playAnimation("bar_longb");
	}

	Button* _pButton = m_CellBtnPanel[_toIdx]->getButton("sbtn_button");
	_pButton->setTag(_dstIdx);
	Nx::Label* _pBtnShodow = m_CellBtnPanel[_toIdx]->getLabel("txt_button_under");
	Nx::Label* _pBtnText = m_CellBtnPanel[_toIdx]->getLabel("txt_button");

	Nx::Label* _pLetterName = m_ListCell[_toIdx]->getLabel("txt_letter_name");
	Nx::Label* _pSendUserName = m_ListCell[_toIdx]->getLabel("txt_username");
	Nx::Label* _pTimeLimit = m_ListCell[_toIdx]->getLabel("txt_letter_timelimit");
	Nx::Label* _pNum = m_ListCell[_toIdx]->getLabel("txt_buttonsum");

	SkelObject* _pUserPhoto = m_ListCell[_toIdx]->getSkel("skel_symbol");

	W_LetterInfo* _pInfo = GameDataManager::getSingletonPtr()->m_pLetterInfoList[_dstIdx];
	_pLetterName->setString(_pInfo->content().c_str());
	_pSendUserName->setString(_pInfo->title().c_str());

	if (_pInfo->has_expiretime())
	{
		string _remainTime = _pInfo->expiretime();
		_pTimeLimit->setString(_remainTime.c_str());
	}
	else
	{
		_pTimeLimit->setString("");
	}

	if (_pInfo->has_rewardinfo())
	{
		m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(true);
		_pNum->setVisible(true);
		_pButton->setEnable(true);
		_pButton->setVisible(true);
		_pBtnShodow->setVisible(true);
		_pBtnText->setVisible(true);


		W_RewardInfo _RewardInfo = _pInfo->rewardinfo();
		if (_RewardInfo.rewardset_size() > 0)
		{
			W_RewardInfo_RewardSet rewardSet = _RewardInfo.rewardset(0);
			eResourceType type = rewardSet.type();
			_pNum->setString((GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(rewardSet.amount(), 2))).c_str());
			if (rewardSet.type() == CHARACTER) {				
				const W_CharacterData characterData = PokerShopHelper::getCharacterData(rewardSet.id());
				string iconStr = "icon_" + characterData.image();				
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation(iconStr);
				string characterNumStr = NxGetFormatString(GameStringDepot::getSingleton().getString("LETTER_CHARACTER_UNIT"), rewardSet.amount());
				_pNum->setString(characterNumStr.c_str());
			}
			else if (rewardSet.type() == SKIN) {
				const W_SkinData* skinData = GameDataManager::getSingleton().getSkinData(rewardSet.id());
				string iconStr = "icon_" + skinData->image();
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation(iconStr);
				string characterNumStr = NxGetFormatString(GameStringDepot::getSingleton().getString("LETTER_CHARACTER_UNIT"), rewardSet.amount());
				_pNum->setString(characterNumStr.c_str());
			}
			else  {				
				m_ListCell[_toIdx]->getSkel("skel_icon")->playAnimation(PokerResourceHelper::getRewardIconStr(rewardSet));
			}
		}
	}
	else {
		m_ListCell[_toIdx]->getSkel("skel_icon")->setVisible(false);
		_pNum->setVisible(false);
		_pButton->setEnable(true);
		_pButton->setVisible(true);
		_pBtnShodow->setVisible(true);
		_pBtnText->setVisible(true);
		_pBtnShodow->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTER_DELETE_UNIT").c_str());
		_pBtnText->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTER_DELETE_UNIT").c_str());
	}

	if (GameStringDepot::getSingleton().getString("TXT_UNLIMIT") == _pInfo->expiretime())
		_pUserPhoto->playAnimation("symbol_shop");
	else
		_pUserPhoto->playAnimation("symbol_allgame");

	//if (1)
	//{
	//	switch (_pInfo->gametype())
	//	{
	//	case GameKind::GAMEKIND_7POKER:
	//		_pUserPhoto->playAnimation("symbol_sevenpoker");
	//		break;
	//	case GameKind::GAMEKIND_HIGH_LOW:
	//		_pUserPhoto->playAnimation("symbol_highlow");
	//		break;
	//	case GameKind::GAMEKIND_BADUKI:
	//		_pUserPhoto->playAnimation("symbol_badugi");
	//		break;
	//	case 4:
	//		_pUserPhoto->playAnimation("symbol_slot");
	//		break;
	//	default:
	//		_pUserPhoto->playAnimation("symbol_allgame");
	//		break;
	//	}
	//}

}

void LobbyOptionNoticePanel::onLayerMessage(const string& msg)
{
	/*if (strncmp(msg.c_str(), "Letter_Res_", 11) == 0)
	{
		int _index = nxExtractInt(msg, "Letter_Res_");
		if (GameDataManager::getSingletonPtr()->m_pLetterInfoList[_index]->has_seq())
		{
			int64 _letterSeq = GameDataManager::getSingletonPtr()->m_pLetterInfoList[_index]->seq();
			WebService::getSingletonPtr()->_sendLetterUpdateReq(_letterSeq);
		}
	}*/	
}

void LobbyOptionNoticePanel::setActivate(bool activate)
{
	if (activate) {
		WebService::getSingletonPtr()->_sendLetterListReq();
		setVisible(true);
		if (getPositionX() < 0) {
			setPositionX(getPositionX() + DESIGN_WIDTH);
		}
	}
	else {
		setVisible(false);
		if (getPositionX() > 0) {
			setPositionX(getPositionX() - DESIGN_WIDTH);
		}
	}
}

