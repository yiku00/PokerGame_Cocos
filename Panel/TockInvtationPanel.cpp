#include "pch.h"
#include "TockInvtationPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "SimplePopupPanel.h"
#include "LobbyFriendPanel.h"

TockInvtationPanel::TockInvtationPanel()
{
	mLoginProcess = false;

	m_pTockFrinedListView = nullptr;
	m_pTockFrinedListContainer = nullptr;
}

TockInvtationPanel::~TockInvtationPanel()
{
	mMainPanel->destruct();
}

void TockInvtationPanel::InitPanel()
{
	mParentPanel = dynamic_cast<LobbyFriendPanel*>(getParent());
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		mMainPanel->construct(getMxmlPath() + "dmy_tockinvitation.mxml");
		addChild(mMainPanel);
		mMainPanel->release();
		CCSize contentsSize = mMainPanel->getDummy("dmy_tockinvitation").size;
		mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		this->setPosition(mParentPanel->getImage("dmy_tockinvitation")->getPosition());
	}

	InitImage();
	initButton();

	setTouchable(false);
	setButtonListener(this);

	setVisible(false);
	unscheduleUpdate();
}

void TockInvtationPanel::InitImage()
{
	mMainPanel->getSkel("skel_small_title")->setSkin("title_tockinvitation");
}

void TockInvtationPanel::initButton()
{
	mMainPanel->getButton("sbtn_title_cancel_stay")->getButtonSkelObject()->setSkin("mark_cancel");
	mMainPanel->getButton("sbtn_title_cancel_stay")->setListener(dynamic_cast<LobbyFriendPanel*>(getParent()));
}


bool TockInvtationPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_bTouchCancel = false;
	return cellTouchStart(pTouch->getLocation());
	//return Panel::ccTouchBegan(pTouch, pEvent);
}


void TockInvtationPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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
}


void TockInvtationPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	Panel::ccTouchEnded(pTouch, pEvent);

	if (m_bTouchCancel == true)
		return;

	CCPoint _startTouch = pTouch->getStartLocationInView();
	CCPoint _EndTouch = pTouch->getLocationInView();

	float _defPos = abs(_startTouch.y - _EndTouch.y);

	if (_defPos <= 10.f)
	{
		cellTouch(pTouch->getLocation());
	}
}



void TockInvtationPanel::resume()
{
}

void TockInvtationPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;
}

void TockInvtationPanel::update(float dt)
{
	ScrollViewOffsetProcess();
}

bool TockInvtationPanel::handling(STCMD &stCmd)
{
	return false;
}


void TockInvtationPanel::ShowPopupPanel()
{
	setVisible(true);
	setTouchable(true);
}

void TockInvtationPanel::HidePopupPanel()
{
	setVisible(false);
	setTouchable(false);
}

void TockInvtationPanel::SetFriendlList()
{
	ClearFriendlList();

	m_pTockFrinedListContainer = CCLayer::create();
	CCSize _contentSize = mMainPanel->getDummy("dmy_tockinvitation").size;

	int _size = 50;

	for (int _i = 0; _i < _size; _i++)
	{
		//W_FriendInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SnsDataList[_i];
		//if (_pInfo)
		//{
		//	if (_pInfo->has_uid() && _pInfo->has_name() && _pInfo->has_level() && _pInfo->has_connecttime())
		//	{
				if (_i < 10)
				{
					m_ListCell[_i] = new Panel();
					m_ListCell[_i]->construct(getMxmlPath() + "dmy_f_barshort.mxml");

					CCSize _ButtonPanelSize = m_ListCell[_i]->getDummy("dmy_f_barshort").size;
					m_ListCell[_i]->setPosition(ccp(10.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (88.f * _i)));

					Button* _pButton1 = m_ListCell[_i]->getButton("sbtn_scroll_panel_shortl");
					_pButton1->setType(Button::NoPressImg);
					_pButton1->setListener(this);
					_pButton1->setPaused(true);

					Button* _pButton2 = m_ListCell[_i]->getButton("sbtn_inpanel_button2_stay");
					_pButton2->setType(Button::NoPressImg);
					_pButton2->setListener(this);
					_pButton2->setPaused(true);

					Nx::Label* _pNickName = m_ListCell[_i]->getLabel("txt_username");
					Nx::Label* _pMessage = m_ListCell[_i]->getLabel("txt_f_barshortmessage");

					string _name = "__NUM_" + StringConverter::toString(_i);
					_pNickName->setString(_name.c_str());
					m_pTockFrinedListContainer->addChild(m_ListCell[_i]);
					m_ListCell[_i]->release();
				}
		//	}
		//}
	}
	if (_size > 0)
	{
		m_pTockFrinedListContainer->setContentSize(CCSizeMake(_contentSize.width, 88.f*_size));
	}
	else
	{
		m_pTockFrinedListContainer->setContentSize(_contentSize);
	}

	m_pTockFrinedListView = CCScrollView::create(_contentSize, m_pTockFrinedListContainer);
	m_pTockFrinedListView->setDirection(extension::ScrollView::Direction::VERTICAL);
	m_pTockFrinedListView->setBounceable(false);
	//가장 상단으로 올리기.
	//m_pFrinedListView->setContentOffset(ccp(0, _contentSize.height - 88.f), false);
	m_pTockFrinedListView->setContentOffset(ccp(0, 0), false);
	
	CCPoint _ListPos = getDummy("dmy_scrollsize_1").origin;
	_ListPos.y = DESIGN_HEIGHT - getDummy("dmy_scrollsize_1").size.height - _ListPos.y;
	m_pTockFrinedListView->setPosition(_ListPos);

	addChild(m_pTockFrinedListView, 10);
}

void TockInvtationPanel::ClearFriendlList()
{
	if (m_pTockFrinedListContainer)
	{
		m_pTockFrinedListContainer->cleanup();
		m_pTockFrinedListContainer->removeFromParent();
	}
	m_pTockFrinedListContainer = nullptr;

	if (m_pTockFrinedListView)
	{
		m_pTockFrinedListView->cleanup();
		m_pTockFrinedListView->removeFromParent();

	}
	m_pTockFrinedListView = nullptr;
}

bool TockInvtationPanel::cellTouchStart(const CCPoint& tableTouchPoint)
{
	if (m_pTockFrinedListContainer == nullptr)
		return false;

	auto& panelNodes = m_pTockFrinedListContainer->getChildren();
	for (auto _node : panelNodes)
	{
		Panel* _panel = dynamic_cast<Panel*>(_node);
		Button* btn1 = _panel->getButton("sbtn_scroll_panel_shortl");
		Button* btn2 = _panel->getButton("sbtn_inpanel_button2_stay");
		if (btn1 && btn2) {
			if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
				if (btn1->isEnabled()){
					return false;
				}
			}
			else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint))){
				if (btn2->isEnabled()){
					return true;
				}
			}
		}
	}

	return false;
}

bool TockInvtationPanel::cellTouchCancel(const CCPoint& tableTouchPoint)
{
	if (m_pTockFrinedListContainer == nullptr)
		return false;

	auto& panelNodes = m_pTockFrinedListContainer->getChildren();
	for (auto _node : panelNodes)
	{
		Panel* _panel = dynamic_cast<Panel*>(_node);
		Button* btn1 = _panel->getButton("sbtn_scroll_panel_shortl");
		Button* btn2 = _panel->getButton("sbtn_inpanel_button2_stay");
		if (btn1 && btn2) {
			if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
				if (btn1->isEnabled()){
				}
			}
			else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint))){
				if (btn2->isEnabled()){
				}
			}
		}
	}

	return false;
}

bool TockInvtationPanel::cellTouch(const CCPoint& tableTouchPoint)
{
	if (m_pTockFrinedListContainer == nullptr)
		return false;


	auto& panelNodes = m_pTockFrinedListContainer->getChildren();
	for(auto _node : panelNodes)
	{
		Panel* _panel = dynamic_cast<Panel*>(_node);
		Button* btn1 = _panel->getButton("sbtn_scroll_panel_shortl");
		Button* btn2 = _panel->getButton("sbtn_inpanel_button2_stay");
		if (btn1 && btn2) {
			if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
				if (btn1->isEnabled()){
				}
			}
			else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint))){
				if (btn2->isEnabled()){
				}
			}
		}
	}

	return false;
}

void TockInvtationPanel::cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}


void TockInvtationPanel::ScrollViewOffsetProcess()
{
	if (m_pTockFrinedListView == nullptr)
		return;

	float _offSetPoint = -m_pTockFrinedListView->getContentOffset().y;

	int _size = 50;

	if (_size <= 10)					//셀 수가 10보다 많고
		return;

	if (_offSetPoint >= 88.f * 2.f)	//두칸 이상 셀이 이동 했을 때
	{
		int _toIdx = (_offSetPoint - (88.f * 2.f)) / 88.f;
		int _dstIdx = _toIdx + 10;
		_toIdx = _toIdx % 10;

		for (int _i = 0; _i < 2; _i++)
		{
			CCSize _ButtonPanelSize = m_ListCell[_toIdx]->getDummy("dmy_f_barshort").size;
			m_ListCell[_toIdx]->setPosition(ccp(10.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (88.f * _dstIdx)));

			Button* _pButton1 = m_ListCell[_toIdx]->getButton("sbtn_scroll_panel_shortl");
			_pButton1->setType(Button::NoPressImg);
			//_pButton1->setListener(this);
			_pButton1->setPaused(true);

			Button* _pButton2 = m_ListCell[_toIdx]->getButton("sbtn_inpanel_button2_stay");
			_pButton2->setType(Button::NoPressImg);
			//_pButton2->setListener(this);
			_pButton2->setPaused(true);

			Nx::Label* _pNickName = m_ListCell[_toIdx]->getLabel("txt_username");
			Nx::Label* _pLastJoin = m_ListCell[_toIdx]->getLabel("txt_f_barshortmessage");

			string _name = "__NUM_" + StringConverter::toString(_dstIdx);
			_pNickName->setString(_name.c_str());

			_toIdx = (_toIdx + 1)%10;		//지워지는 셀의 위의 셀은 새로 나타난 셀로 판단한다.
			_dstIdx = _dstIdx - 9;		//
		}
	}
	else
	{
		CCSize _ButtonPanelSize = m_ListCell[0]->getDummy("dmy_f_barshort").size;
		m_ListCell[0]->setPosition(ccp(10.f, _ButtonPanelSize.height - DESIGN_HEIGHT + (88.f * 0.f)));

		Button* _pButton1 = m_ListCell[0]->getButton("sbtn_scroll_panel_shortl");
		_pButton1->setType(Button::NoPressImg);
		//_pButton1->setListener(this);
		_pButton1->setPaused(true);

		Button* _pButton2 = m_ListCell[0]->getButton("sbtn_inpanel_button2_stay");
		_pButton2->setType(Button::NoPressImg);
		//_pButton2->setListener(this);
		_pButton2->setPaused(true);

		Nx::Label* _pNickName = m_ListCell[0]->getLabel("txt_username");
		Nx::Label* _pLastJoin = m_ListCell[0]->getLabel("txt_f_barshortmessage");

		string _name = "__NUM_" + StringConverter::toString(0);
		_pNickName->setString(_name.c_str());
	}
}