#include "pch.h"
#include "LobbyMyHomeMainPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "LobbyMyHomeTap1.h"
#include "LobbyMyHomeTap2.h"
#include "LobbyMyHomeTap3.h"
#include "LobbyScene.h"
#include "LobbyUIPanel.h"
#include "SceneUtil.h"
#include "GameStringDepot.h"
#include "PanelHelper.h"

LobbyMyHomeMainPanel::LobbyMyHomeMainPanel()
{
	mLoginProcess = false;

	for (int _i = 0; _i < 4; _i++)
	{
		m_pTapView[_i] = nullptr;
		m_pTapViewContainer[_i] = nullptr;
	}

	//m_pCharacterSelectPanel = nullptr;
	_pBasicPanel = nullptr;
	_pRecordPanel = nullptr;
	_pVipClassPanel = nullptr;

	m_nTapIndex = 0;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);

	setVisible(true);
}

LobbyMyHomeMainPanel::~LobbyMyHomeMainPanel()
{
	//destruct();
}

void LobbyMyHomeMainPanel::InitPanel()
{
	Panel* panel = addMouseBlockPanel(this, true);
	panel->setContentSize(CCSize(DESIGN_WIDTH, DESIGN_HEIGHT - 72));

	construct(getMxmlPath() + "dmy_my_room.mxml");

	m_ShowPos = getPosition();
	m_HidePos = m_ShowPos - ccp(0, DESIGN_HEIGHT);

	//setPosition(m_HidePos);
	for (int _i = 0; _i < 3; _i++)
	{
		mTapButtonPanel[_i] = new Panel();
		mTapButtonPanel[_i]->construct(getMxmlPath() + "dmy_button_tab.mxml");
		string _dmyName = "dmy_button_tab" + StringConverter::toString(_i + 1);

		CCPoint _pos = getDummy(_dmyName).origin;
		_pos.y = -_pos.y;

		mTapButtonPanel[_i]->setPosition(_pos);

		addChild(mTapButtonPanel[_i]);
		mTapButtonPanel[_i]->release();

		string _btnName = "sbtn_tapbutton_on_stay" + StringConverter::toString(_i + 1);

		mTapButtonPanel[_i]->getButton("sbtn_button")->setType(Button::NoPressImg);
		mTapButtonPanel[_i]->getButton("sbtn_button")->setName(_btnName);
		mTapButtonPanel[_i]->getButton("sbtn_button")->setListener(this);

		mTapButtonPanel[_i]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		mTapButtonPanel[_i]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	}
}

void LobbyMyHomeMainPanel::InitImage()
{
	//getSkel("skel_backcolor2")->setVisible(false);
	HideHomeTitle();

	mTapButtonPanel[0]->getLabel("txt_off_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP1_UNIT").c_str());
	mTapButtonPanel[0]->getLabel("txt_on_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP1_UNIT").c_str());
	mTapButtonPanel[0]->getLabel("txt_off_tab")->setVisible(false);
	mTapButtonPanel[0]->getLabel("txt_on_tab")->setVisible(true);

	mTapButtonPanel[1]->getLabel("txt_off_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP2_UNIT").c_str());
	mTapButtonPanel[1]->getLabel("txt_on_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP2_UNIT").c_str());
	mTapButtonPanel[1]->getLabel("txt_off_tab")->setVisible(true);
	mTapButtonPanel[1]->getLabel("txt_on_tab")->setVisible(false);

	mTapButtonPanel[2]->getLabel("txt_off_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP3_UNIT").c_str());
	mTapButtonPanel[2]->getLabel("txt_on_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP3_UNIT").c_str());
	mTapButtonPanel[2]->getLabel("txt_off_tab")->setVisible(true);
	mTapButtonPanel[2]->getLabel("txt_on_tab")->setVisible(false);

}

void LobbyMyHomeMainPanel::initButton()
{
	//mTapButton[0] = getButton("sbtn_tapbutton_on_stay1");
	//mTapButton[1] = getButton("sbtn_tapbutton_on_stay2");
	//mTapButton[2] = getButton("sbtn_tapbutton_on_stay3");

	//m_DailyCheckButton = getButton("sbtn_tab1_small_button_3_stay");
	//m_DailyCheckButton->setType(Button::NoPressImg);
	//m_DailyCheckButton->getButtonSkelObject()->setSkin("txt_attendance_check");
}


bool LobbyMyHomeMainPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}


void LobbyMyHomeMainPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void LobbyMyHomeMainPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyMyHomeMainPanel::resume()
{
}

void LobbyMyHomeMainPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	int _index = 0;

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (name == "sbtn_tapbutton_on_stay1")
	{
		SetTapPanel(0);
	}
	if (name == "sbtn_tapbutton_on_stay2")
	{
		SetTapPanel(1);
	}
	if (name == "sbtn_tapbutton_on_stay3")
	{
		SetTapPanel(2);
	}
	
	if (name == "GOTO_SHOP_CLASS")
	{
		if (m_nTapIndex == 2)
			GotoShop(0);
	}
	if (name == "GOTO_SHOP_RUBY")
	{
		if (m_nTapIndex == 2)
			GotoShop(1);
	}	
	if (name == "TAP1_GOTO_SHOP_RUBY")
	{
		if (m_nTapIndex == 0)
			GotoShop(1);
	}
}

void LobbyMyHomeMainPanel::update(float dt)
{
}

bool LobbyMyHomeMainPanel::handling(STCMD &stCmd)
{
	return false;
}

void LobbyMyHomeMainPanel::ShowMyHomePanel()
{
	setVisible(true);
	scheduleUpdate();
	ShowHomeTitle();
	SetTapPanel(m_nTapIndex);
}

void LobbyMyHomeMainPanel::HideMyHomePanel()
{
	HideHomeTitle();	
	unVisibleHomePanel();	
}

void LobbyMyHomeMainPanel::ShowHomeTitle()
{
	//getSkel("skel_title_back")->setVisible(true);
	//getSkel("skel_my_room_title")->setVisible(true);
	//getSkel("skel_my_room_mark")->setVisible(true);
	GameDataManager::getSingletonPtr()->FreeUiProcess();

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MYHOME);
		}
	}
}

void LobbyMyHomeMainPanel::HideHomeTitle()
{
	//getSkel("skel_title_back")->setVisible(false);
	//getSkel("skel_my_room_title")->setVisible(false);
	//getSkel("skel_my_room_mark")->setVisible(false);

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MAIN);
		}
	}
}

void LobbyMyHomeMainPanel::unVisibleHomePanel()
{
	ReleaseBasicInfoTap();
	ReleaseRecordInfoTap();
	ReleaseVipClassInfoTap();
	unscheduleUpdate();
	GameDataManager::getSingletonPtr()->FreeUiProcess();
}

void LobbyMyHomeMainPanel::SetTapPanel(int _idx)
{
	m_nTapIndex = _idx;
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
	switch (_idx)
	{
	case 0:
		SetBasicInfoTap();
		ReleaseRecordInfoTap();
		ReleaseVipClassInfoTap();
		break;
	case 1:
		ReleaseBasicInfoTap();
		SetRecordInfoTap();
		ReleaseVipClassInfoTap();
		break;
	case 2:
		ReleaseBasicInfoTap();
		ReleaseRecordInfoTap();
		SetVipClassInfoTap();
		break;
	default:
		break;
	}
}
void LobbyMyHomeMainPanel::SetEnableTap(int _index)
{
	for (int _i = 0; _i < 3; _i++)
	{
		//if (m_pTapView[_i]){
		//	m_pTapView[_i]->setVisible(_i == _index);
		//	m_pTapView[_i]->setTouchEnabled(_i == _index);
		//}
		if (_i == _index)
		{
			mTapButtonPanel[_i]->setZOrder(2);
			mTapButtonPanel[_i]->getButton("sbtn_button")->setSkelAnimation("tab_on");
			mTapButtonPanel[_i]->getLabel("txt_off_tab")->setVisible(false);
			mTapButtonPanel[_i]->getLabel("txt_on_tab")->setVisible(true);
			//m_TapBtn[_i]->setGrayscale(false);
		}
		else
		{
			mTapButtonPanel[_i]->setZOrder(1);
			mTapButtonPanel[_i]->getButton("sbtn_button")->setSkelAnimation("tab_off");
			mTapButtonPanel[_i]->getLabel("txt_off_tab")->setVisible(true);
			mTapButtonPanel[_i]->getLabel("txt_on_tab")->setVisible(false);
			//m_TapBtn[_i]->setGrayscale(true);
		}
	}

	switch (_index)
	{
	case 0:
		if (m_pTapView[0])
		{
			m_pTapView[0]->setVisible(true);
			m_pTapView[0]->setTouchEnabled(true);
			_pBasicPanel->setVisible(true);
		}
		if (m_pTapView[1])
		{
			m_pTapView[1]->setVisible(false);
			m_pTapView[1]->setTouchEnabled(false);
			_pRecordPanel->setVisible(false);
		}
		if (m_pTapView[2])
		{
			m_pTapView[2]->setVisible(false);
			m_pTapView[2]->setTouchEnabled(false);
			_pVipClassPanel->setVisible(false);
		}
		break;
	case 1:
		if (m_pTapView[0])
		{
			m_pTapView[0]->setVisible(false);
			m_pTapView[0]->setTouchEnabled(false);
			_pBasicPanel->setVisible(false);
		}
		if (m_pTapView[1])
		{
			m_pTapView[1]->setVisible(true);
			m_pTapView[1]->setTouchEnabled(true);
			_pRecordPanel->setVisible(true);
		}
		if (m_pTapView[2])
		{
			m_pTapView[2]->setVisible(false);
			m_pTapView[2]->setTouchEnabled(false);
			_pVipClassPanel->setVisible(false);
		}
		break;
	case 2:
		if (m_pTapView[0])
		{
			m_pTapView[0]->setVisible(false);
			m_pTapView[0]->setTouchEnabled(false);
			_pBasicPanel->setVisible(false);
		}
		if (m_pTapView[1])
		{
			m_pTapView[1]->setVisible(false);
			m_pTapView[1]->setTouchEnabled(false);
			_pRecordPanel->setVisible(false);
		}
		if (m_pTapView[2])
		{
			m_pTapView[2]->setVisible(true);
			m_pTapView[2]->setTouchEnabled(true);
			_pVipClassPanel->setVisible(true);
		}
		break;
	}
}

void LobbyMyHomeMainPanel::SetBasicInfoTap()
{
	if (m_pTapView[0] == nullptr)
	{
		_pBasicPanel = new LobbyMyHomeTap1();
		
		m_pTapViewContainer[0] = CCLayer::create();
		CCSize _contentSize = getDummy("dmy_scrollsize").size;
		CCSize _TapPanelSize = _pBasicPanel->getDummy("dmy_basicsinfo").size;
		CCPoint _panelPos = ccp(0, _TapPanelSize.height - DESIGN_HEIGHT);
		_pBasicPanel->setPosition(_panelPos);

		m_pTapViewContainer[0]->setContentSize(_TapPanelSize);
		m_pTapViewContainer[0]->addChild(_pBasicPanel);
		_pBasicPanel->release();
		_pBasicPanel->SetMainUiPanelPtr(this);

		m_pTapView[0] = CCScrollView::create(_contentSize, m_pTapViewContainer[0]);

		m_pTapView[0]->setDirection(extension::ScrollView::Direction::VERTICAL);
		m_pTapView[0]->setBounceable(false);
		m_pTapView[0]->setContentOffset(ccp(0, _contentSize.height - _TapPanelSize.height), false);

		CCPoint _ListPos = getDummy("dmy_scrollsize").origin;
		m_pTapView[0]->setPositionX(_ListPos.x);
		m_pTapView[0]->setPositionY(4);

		//getSkel("skel_panel_f1_2_center5")->addChild(m_pTapView[0]);
		addChild(m_pTapView[0]);
	}
	SetEnableTap(0);
}

void LobbyMyHomeMainPanel::SetRecordInfoTap()
{
	if (m_pTapView[1] == nullptr)
	{
		m_pTapViewContainer[1] = CCLayer::create();
		CCSize _contentSize = getDummy("dmy_scrollsize").size;
		CCSize _TapPanelSize = getDummy("dmy_vipinfo").size;
		m_pTapViewContainer[1]->setContentSize(_TapPanelSize);

		_pRecordPanel = new LobbyMyHomeTap2();
		_pRecordPanel->setPosition(ccp(0, _TapPanelSize.height - DESIGN_HEIGHT));
		m_pTapViewContainer[1]->addChild(_pRecordPanel);
		_pRecordPanel->release();

		m_pTapView[1] = CCScrollView::create(_contentSize, m_pTapViewContainer[1]);

		m_pTapView[1]->setDirection(extension::ScrollView::Direction::VERTICAL);
		m_pTapView[1]->setBounceable(false);
		m_pTapView[1]->setContentOffset(ccp(0, _contentSize.height - _TapPanelSize.height), false);

		CCPoint _ListPos = getDummy("dmy_scrollsize").origin;
		m_pTapView[1]->setPositionX(_ListPos.x);
		m_pTapView[1]->setPositionY(4);

		//getSkel("skel_panel_f1_2_center5")->addChild(m_pTapView[1]);
		addChild(m_pTapView[1]);
	}
	SetEnableTap(1);
}

void LobbyMyHomeMainPanel::SetVipClassInfoTap()
{
	if (m_pTapView[2] == nullptr)
	{
		m_pTapViewContainer[2] = CCLayer::create();
		CCSize _contentSize = getDummy("dmy_scrollsize").size;
		CCSize _TapPanelSize = getDummy("dmy_classinfo").size;
		m_pTapViewContainer[2]->setContentSize(_TapPanelSize);

		_pVipClassPanel = new LobbyMyHomeTap3();
		_pVipClassPanel->setPosition(ccp(0, _TapPanelSize.height - DESIGN_HEIGHT));
		m_pTapViewContainer[2]->addChild(_pVipClassPanel);
		_pVipClassPanel->release();

		//_pVipClassPanel->m_GotoRubyShopBtn->setListener(this);
		_pVipClassPanel->m_GotoClassShopBtn->setListener(this);

		m_pTapView[2] = CCScrollView::create(_contentSize, m_pTapViewContainer[2]);

		m_pTapView[2]->setDirection(extension::ScrollView::Direction::VERTICAL);
		m_pTapView[2]->setBounceable(false);
		m_pTapView[2]->setContentOffset(ccp(0, _contentSize.height - _TapPanelSize.height), false);

		CCPoint _ListPos = getDummy("dmy_scrollsize").origin;
		m_pTapView[2]->setPositionX(_ListPos.x);
		m_pTapView[2]->setPositionY(4);

		//getSkel("skel_panel_f1_2_center5")->addChild(m_pTapView[2]);
		addChild(m_pTapView[2]);
		
	}
	SetEnableTap(2);
}

void LobbyMyHomeMainPanel::GotoShop(int _tapIndex)
{
	if (_tapIndex == 0)
		PanelHelper::pushMemberShipShopPanel();
	else if (_tapIndex == 1)
		PanelHelper::pushRubyShopPanel();
	else if (_tapIndex == 2)
		PanelHelper::pushCharacterShopPanel();
}

void LobbyMyHomeMainPanel::ReleaseBasicInfoTap()
{
	if (m_pTapView[0] != nullptr)
	{
		_pBasicPanel->removeAllChildren();
		_pBasicPanel->removeFromParent();
		m_pTapViewContainer[0]->removeAllChildren();
		m_pTapViewContainer[0]->removeFromParent();
		m_pTapView[0]->removeFromParent();
	}
	_pBasicPanel = nullptr;
	m_pTapViewContainer[0] = nullptr;
	m_pTapView[0] = nullptr;
}

void LobbyMyHomeMainPanel::ReleaseRecordInfoTap()
{
	if (m_pTapView[1] != nullptr)
	{
		_pRecordPanel->removeAllChildren();
		_pRecordPanel->removeFromParent();
		m_pTapViewContainer[1]->removeAllChildren();
		m_pTapViewContainer[1]->removeFromParent();
		m_pTapView[1]->removeFromParent();
	}
	_pRecordPanel = nullptr;
	m_pTapViewContainer[1] = nullptr;
	m_pTapView[1] = nullptr;
}

void LobbyMyHomeMainPanel::ReleaseVipClassInfoTap()
{
	if (m_pTapView[2] != nullptr)
	{
		_pVipClassPanel->removeAllChildren();
		_pVipClassPanel->removeFromParent();
		m_pTapViewContainer[2]->removeAllChildren();
		m_pTapViewContainer[2]->removeFromParent();
		m_pTapView[2]->removeFromParent();
	}
	_pVipClassPanel = nullptr;
	m_pTapViewContainer[2] = nullptr;
	m_pTapView[2] = nullptr;
}

void LobbyMyHomeMainPanel::refreshUserName()
{
	if (_pBasicPanel)
		_pBasicPanel->SetUserInfo();
}

void LobbyMyHomeMainPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}