#include "pch.h"
#include "BadugiSelectCardPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"

#include "Web/WebService.h"
#include "GameStringDepot.h"
#include "NotiDataManager.h"
#include "PanelHelper.h"

BadugiSelectCardPanel::BadugiSelectCardPanel()
{
	mLoginProcess = false;
	InitPanel();
	InitImage();
	InitButton();
}

BadugiSelectCardPanel::~BadugiSelectCardPanel()
{
	removeAllChildren();
}

void BadugiSelectCardPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_underborad_badugi.mxml");

	Panel* _panel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("Background"));
	CCPoint _panePos = _panel->getDummy("dmy_underborad_badugi").origin;
	_panePos.y = -_panePos.y;

	m_showPosition = _panePos;
	m_hidePosition = _panePos - ccp(0.f, 300.f);

	setPosition(m_hidePosition);
	setVisible(false);
}

void BadugiSelectCardPanel::InitImage()
{
	getLabel("txt_change")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_pass")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));	
	getLabel("txt_change")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_CHANGE").c_str());
	getLabel("txt_pass")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_PASS").c_str());
}

void BadugiSelectCardPanel::InitButton()
{
	m_ChangeBtn = getButton("sbtn_change");
	m_PassBtn = getButton("sbtn_pass");
	m_SelectBtn1 = getButton("sbtn_number1");
	m_SelectBtn2 = getButton("sbtn_number2");
	m_SelectBtn3 = getButton("sbtn_number3");
	m_SelectBtn4 = getButton("sbtn_number4");

	m_ChangeBtn->setType(Button::NoPressImg);
	m_PassBtn->setType(Button::NoPressImg);
	m_SelectBtn1->setType(Button::NoPressImg);
	m_SelectBtn2->setType(Button::NoPressImg);
	m_SelectBtn3->setType(Button::NoPressImg);
	m_SelectBtn4->setType(Button::NoPressImg);

	m_SelectBtn1->getButtonSkelObject()->setSkin("number_1");
	m_SelectBtn2->getButtonSkelObject()->setSkin("number_2");
	m_SelectBtn3->getButtonSkelObject()->setSkin("number_3");
	m_SelectBtn4->getButtonSkelObject()->setSkin("number_4");
	
	m_ChangeBtn->getButtonSkelObject()->playAnimation("change_loop", true);
	m_PassBtn->getButtonSkelObject()->playAnimation("pass_loop", true);
	m_SelectBtn1->getButtonSkelObject()->playAnimation("number_off_stay", true);
	m_SelectBtn2->getButtonSkelObject()->playAnimation("number_off_stay", true);
	m_SelectBtn3->getButtonSkelObject()->playAnimation("number_off_stay", true);
	m_SelectBtn4->getButtonSkelObject()->playAnimation("number_off_stay", true);

	m_ChangeBtn->setEnable(true);
	m_ChangeBtn->setPaused(true);
	m_PassBtn->setPaused(true);
	m_SelectBtn1->setPaused(true);
	m_SelectBtn2->setPaused(true);
	m_SelectBtn3->setPaused(true);
	m_SelectBtn4->setPaused(true);
	
	for (int _i = 0; _i < 6; _i++)
	{
		m_TouchButton[_i] = false;
	}
}

void BadugiSelectCardPanel::SetNumberButtonState()
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[0] == false)
	{
		m_SelectBtn1->getButtonSkelObject()->playAnimation("number_off_stay", true);
	}
	else
	{
		m_SelectBtn1->getButtonSkelObject()->playAnimation("number_on_stay", true);
	}

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[1] == false)
	{
		m_SelectBtn2->getButtonSkelObject()->playAnimation("number_off_stay", true);
	}
	else
	{
		m_SelectBtn2->getButtonSkelObject()->playAnimation("number_on_stay", true);
	}

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[2] == false)
	{
		m_SelectBtn3->getButtonSkelObject()->playAnimation("number_off_stay", true);
	}
	else
	{
		m_SelectBtn3->getButtonSkelObject()->playAnimation("number_on_stay", true);
	}

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[3] == false)
	{
		m_SelectBtn4->getButtonSkelObject()->playAnimation("number_off_stay", true);
	}
	else
	{
		m_SelectBtn4->getButtonSkelObject()->playAnimation("number_on_stay", true);
	}
}

bool BadugiSelectCardPanel::TouchStart(CCTouch *pTouch)
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_PlayStatus == PLAY_SHARE_CARD)
		return false;

	CCPoint _Touchpos = pTouch->getLocation();

	if (m_ChangeBtn->hasCollided(m_ChangeBtn->convertToNodeSpace(_Touchpos)) && m_ChangeBtn->isEnabled())
	{
		m_ChangeBtn->getButtonSkelObject()->playAnimation("change_in");
		m_TouchButton[0] = true;
		return true;
	}

	if (m_PassBtn->hasCollided(m_PassBtn->convertToNodeSpace(_Touchpos)) && m_PassBtn->isEnabled())
	{
		m_PassBtn->getButtonSkelObject()->playAnimation("pass_in");
		m_TouchButton[1] = true;
		return true;
	}

	if (m_SelectBtn1->hasCollided(m_SelectBtn1->convertToNodeSpace(_Touchpos)) && m_SelectBtn1->isEnabled())
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[0] == true)
		{
			m_SelectBtn1->getButtonSkelObject()->playAnimation("number_on_in");
			m_TouchButton[2] = true;
		}
		else
		{
			m_SelectBtn1->getButtonSkelObject()->playAnimation("number_off_in");
			m_TouchButton[2] = true;
		}
		return true;
	}

	if (m_SelectBtn2->hasCollided(m_SelectBtn2->convertToNodeSpace(_Touchpos)) && m_SelectBtn2->isEnabled())
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[1] == true)
		{
			m_SelectBtn2->getButtonSkelObject()->playAnimation("number_on_in");
			m_TouchButton[3] = true;
		}
		else
		{
			m_SelectBtn2->getButtonSkelObject()->playAnimation("number_off_in");
			m_TouchButton[3] = true;
		}
		return true;
	}

	if (m_SelectBtn3->hasCollided(m_SelectBtn3->convertToNodeSpace(_Touchpos)) && m_SelectBtn3->isEnabled())
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[2] == true)
		{
			m_SelectBtn3->getButtonSkelObject()->playAnimation("number_on_in");
			m_TouchButton[4] = true;
		}
		else
		{
			m_SelectBtn3->getButtonSkelObject()->playAnimation("number_off_in");
			m_TouchButton[4] = true;
		}
		return true;
	}

	if (m_SelectBtn4->hasCollided(m_SelectBtn4->convertToNodeSpace(_Touchpos)) && m_SelectBtn4->isEnabled())
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[3] == true)
		{
			m_SelectBtn4->getButtonSkelObject()->playAnimation("number_on_in");
			m_TouchButton[5] = true;
		}
		else
		{
			m_SelectBtn4->getButtonSkelObject()->playAnimation("number_off_in");
			m_TouchButton[5] = true;
		}

		return true;
	}

	return false;
}

void BadugiSelectCardPanel::TouchMove(CCTouch *pTouch)
{
	CCPoint _Touchpos = pTouch->getLocation();

	if (m_ChangeBtn->hasCollided(m_ChangeBtn->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[0] == false && m_ChangeBtn->isEnabled())
		{
			m_ChangeBtn->getButtonSkelObject()->playAnimation("change_in");
			m_TouchButton[0] = true;
		}
	}
	else
	{
		if (m_TouchButton[0] == true && m_ChangeBtn->isEnabled())
		{
			m_ChangeBtn->getButtonSkelObject()->playAnimation("change_out");
			m_ChangeBtn->getButtonSkelObject()->appendAnimation("change_loop", true);
			m_TouchButton[0] = false;

		}
	}

	if (m_PassBtn->hasCollided(m_PassBtn->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[1] == false)
		{
			m_PassBtn->getButtonSkelObject()->playAnimation("pass_in");
			m_TouchButton[1] = true;
		}
	}
	else
	{
		if (m_TouchButton[1] == true)
		{
			m_PassBtn->getButtonSkelObject()->playAnimation("pass_out");
			m_PassBtn->getButtonSkelObject()->appendAnimation("pass_loop", true);
			m_TouchButton[1] = false;
		}
	}

	if (m_SelectBtn1->hasCollided(m_SelectBtn1->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[2] == false)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[0] == true)
			{
				m_SelectBtn1->getButtonSkelObject()->playAnimation("number_on_in");
			}
			else
			{
				m_SelectBtn1->getButtonSkelObject()->playAnimation("number_off_in");
			}
			m_TouchButton[2] = true;
		}
	}
	else
	{
		if (m_TouchButton[2] == true)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[0] == true)
			{
				m_SelectBtn1->getButtonSkelObject()->playAnimation("number_on_out");
				m_SelectBtn1->getButtonSkelObject()->appendAnimation("number_on_stay", true);
			}
			else
			{
				m_SelectBtn1->getButtonSkelObject()->playAnimation("number_off_out");
				m_SelectBtn1->getButtonSkelObject()->appendAnimation("number_off_stay", true);
			}
			m_TouchButton[2] = false;
		}
	}

	if (m_SelectBtn2->hasCollided(m_SelectBtn2->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[3] == false)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[1] == true)
			{
				m_SelectBtn2->getButtonSkelObject()->playAnimation("number_on_in");
			}
			else
			{
				m_SelectBtn2->getButtonSkelObject()->playAnimation("number_off_in");
			}
			m_TouchButton[3] = true;
		}
	}
	else
	{
		if (m_TouchButton[3] == true)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[1] == true)
			{
				m_SelectBtn2->getButtonSkelObject()->playAnimation("number_on_out");
				m_SelectBtn2->getButtonSkelObject()->appendAnimation("number_on_stay", true);
			}
			else
			{
				m_SelectBtn2->getButtonSkelObject()->playAnimation("number_off_out");
				m_SelectBtn2->getButtonSkelObject()->appendAnimation("number_off_stay", true);
			}
			m_TouchButton[3] = false;
		}
	}

	if (m_SelectBtn3->hasCollided(m_SelectBtn3->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[4] == false)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[2] == true)
			{
				m_SelectBtn3->getButtonSkelObject()->playAnimation("number_on_in");
			}
			else
			{
				m_SelectBtn3->getButtonSkelObject()->playAnimation("number_off_in");
			}
			m_TouchButton[4] = true;
		}
	}
	else
	{
		if (m_TouchButton[4] == true)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[2] == true)
			{
				m_SelectBtn3->getButtonSkelObject()->playAnimation("number_on_out");
				m_SelectBtn3->getButtonSkelObject()->appendAnimation("number_on_stay", true);
			}
			else
			{
				m_SelectBtn3->getButtonSkelObject()->playAnimation("number_off_out");
				m_SelectBtn3->getButtonSkelObject()->appendAnimation("number_off_stay", true);
			}
			m_TouchButton[4] = false;
		}
	}

	if (m_SelectBtn4->hasCollided(m_SelectBtn4->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[5] == false)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[3] == true)
			{
				m_SelectBtn4->getButtonSkelObject()->playAnimation("number_on_in");
			}
			else
			{
				m_SelectBtn4->getButtonSkelObject()->playAnimation("number_off_in");
			}
			m_TouchButton[5] = true;
		}
	}
	else
	{
		if (m_TouchButton[5] == true)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[3] == true)
			{
				m_SelectBtn4->getButtonSkelObject()->playAnimation("number_on_out");
				m_SelectBtn4->getButtonSkelObject()->appendAnimation("number_on_stay", true);
			}
			else
			{
				m_SelectBtn4->getButtonSkelObject()->playAnimation("number_off_out");
				m_SelectBtn4->getButtonSkelObject()->appendAnimation("number_off_stay", true);
			}
			m_TouchButton[5] = false;
		}
	}
}

void BadugiSelectCardPanel::TouchEnd(CCTouch *pTouch)
{
	CCPoint _Touchpos = pTouch->getLocation();

	if (m_ChangeBtn->hasCollided(m_ChangeBtn->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[0] == true && m_ChangeBtn->isEnabled())
		{
			m_ChangeBtn->getButtonSkelObject()->playAnimation("change_out");
			m_ChangeBtn->getButtonSkelObject()->appendAnimation("change_loop", true);
			m_TouchButton[0] = false;

			SendChangeCardReq();
		}
		return;
	}

	if (m_PassBtn->hasCollided(m_PassBtn->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[1] == true && m_PassBtn->isEnabled())
		{
			m_PassBtn->getButtonSkelObject()->playAnimation("pass_out");
			m_PassBtn->getButtonSkelObject()->appendAnimation("pass_loop", true);
			m_TouchButton[1] = false;

			SendChangePassReq();
		}
		return;
	}

	if (m_SelectBtn1->hasCollided(m_SelectBtn1->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[2] == true)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[0] == true)
			{
				m_SelectBtn1->getButtonSkelObject()->playAnimation("number_on_out");
				m_SelectBtn1->getButtonSkelObject()->appendAnimation("number_off_start");
				m_SelectBtn1->getButtonSkelObject()->appendAnimation("number_off_stay", true);
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[0] = false;
			}
			else
			{
				m_SelectBtn1->getButtonSkelObject()->playAnimation("number_off_out");
				m_SelectBtn1->getButtonSkelObject()->appendAnimation("number_on_start");
				m_SelectBtn1->getButtonSkelObject()->appendAnimation("number_on_stay", true);
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[0] = true;
			}
			m_TouchButton[2] = false;
		}
	}
	if (m_SelectBtn2->hasCollided(m_SelectBtn2->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[3] == true)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[1] == true)
			{
				m_SelectBtn2->getButtonSkelObject()->playAnimation("number_on_out");
				m_SelectBtn2->getButtonSkelObject()->appendAnimation("number_off_start");
				m_SelectBtn2->getButtonSkelObject()->appendAnimation("number_off_stay", true);
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[1] = false;
			}
			else
			{
				m_SelectBtn2->getButtonSkelObject()->playAnimation("number_off_out");
				m_SelectBtn2->getButtonSkelObject()->appendAnimation("number_on_start");
				m_SelectBtn2->getButtonSkelObject()->appendAnimation("number_on_stay", true);
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[1] = true;
			}
			m_TouchButton[3] = false;
		}
	}
	if (m_SelectBtn3->hasCollided(m_SelectBtn3->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[4] == true)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[2] == true)
			{
				m_SelectBtn3->getButtonSkelObject()->playAnimation("number_on_out");
				m_SelectBtn3->getButtonSkelObject()->appendAnimation("number_off_start");
				m_SelectBtn3->getButtonSkelObject()->appendAnimation("number_off_stay", true);
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[2] = false;
			}
			else
			{
				m_SelectBtn3->getButtonSkelObject()->playAnimation("number_off_out");
				m_SelectBtn3->getButtonSkelObject()->appendAnimation("number_on_start");
				m_SelectBtn3->getButtonSkelObject()->appendAnimation("number_on_stay", true);
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[2] = true;
			}
			m_TouchButton[4] = false;
		}
	}
	if (m_SelectBtn4->hasCollided(m_SelectBtn4->convertToNodeSpace(_Touchpos)))
	{
		if (m_TouchButton[5] == true)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[3] == true)
			{
				m_SelectBtn4->getButtonSkelObject()->playAnimation("number_on_out");
				m_SelectBtn4->getButtonSkelObject()->appendAnimation("number_off_start");
				m_SelectBtn4->getButtonSkelObject()->appendAnimation("number_off_stay", true);
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[3] = false;
			}
			else
			{
				m_SelectBtn4->getButtonSkelObject()->playAnimation("number_off_out");
				m_SelectBtn4->getButtonSkelObject()->appendAnimation("number_on_start");
				m_SelectBtn4->getButtonSkelObject()->appendAnimation("number_on_stay", true);
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[3] = true;
			}
			m_TouchButton[5] = false;
		}
	}

	GameRoomInfo* _pInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
	RoomUserData* _User = _pInfo->GetUserDataPtr(_pInfo->m_MyPo);
	_User->SetBadugiSelectedCardEffect();
	ApplyChangeButtonState();
}

void BadugiSelectCardPanel::ApplyChangeButtonState()
{
	for (int _i = 0; _i < 4; _i++)
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_i] == true)
		{
			if (m_ChangeBtn->isEnabled() == false)
			{
				m_ChangeBtn->setEnable(true);
				m_ChangeBtn->getButtonSkelObject()->playAnimation("change_start");
				m_ChangeBtn->getButtonSkelObject()->appendAnimation("change_loop");
			}
			return;
		}
	}

	if (m_ChangeBtn->isEnabled() == true)
	{
		m_ChangeBtn->setEnable(false);
		m_ChangeBtn->getButtonSkelObject()->playAnimation("change_end");
		m_ChangeBtn->getButtonSkelObject()->appendAnimation("change_stay");
	}
}

void BadugiSelectCardPanel::SetChangeButtonState()
{
	for (int _i = 0; _i < 4; _i++)
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_i] == true)
		{
			if (m_ChangeBtn->isEnabled() == false)
			{
				m_ChangeBtn->setEnable(true);
				m_ChangeBtn->getButtonSkelObject()->playAnimation("change_start");
				m_ChangeBtn->getButtonSkelObject()->appendAnimation("change_loop");
			}
			return;
		}
	}

	if (m_ChangeBtn->isEnabled() == true)
	{
		m_ChangeBtn->setEnable(false);
		m_ChangeBtn->getButtonSkelObject()->playAnimation("change_end");
		m_ChangeBtn->getButtonSkelObject()->playAnimation("change_stay");
	}
}

void BadugiSelectCardPanel::SetSeletBtn(int _idx, bool _on)
{
	string _FrameName1 = "";
	string _FrameName2 = "";
	if (_on == true)
	{
		_FrameName1 = "number_on_start";
		_FrameName2 = "number_on_stay";
	}
	else
	{
		_FrameName1 = "number_off_start";
		_FrameName2 = "number_off_stay";
	}

	Button* _btn = nullptr;
	switch (_idx)
	{
	case 0:
		_btn = m_SelectBtn1;
		break;
	case 1:
		_btn = m_SelectBtn2;
		break;
	case 2:
		_btn = m_SelectBtn3;
		break;
	case 3:
		_btn = m_SelectBtn4;
		break;
	default:
		break;
	}

	if (_btn == nullptr)
		return;

	_btn->getButtonSkelObject()->appendAnimation(_FrameName1);
	_btn->getButtonSkelObject()->appendAnimation(_FrameName2, true);
}

void BadugiSelectCardPanel::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void BadugiSelectCardPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;
}

void BadugiSelectCardPanel::update(float dt)
{

}

bool BadugiSelectCardPanel::handling(STCMD &stCmd)
{
	if (!mLoginProcess)
		return false;

	return false;
}

void BadugiSelectCardPanel::ShowBadugiSelectCardPanel(bool _visible)
{

	NotiFocusPanel* pPanel = nullptr;
	if (NotiDataManager::getSingleton().getBadukiNoti() == NotiData_eNotiType_FirstBaduki) {
		if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
		else {
			if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI) {
				PanelHelper::pushNotiFocusPanel(NotiData_eNotiType_FirstBaduki);
			}
		}
	}

	if (pPanel) {
		pPanel->setVisible(_visible);
		if (_visible)
			pPanel->setSubList();
	}


	if (_visible == true)
	{
		SetEnableButton(true);
		setPosition(m_showPosition);
		SetNumberButtonState();
		SetChangeButtonState();
		setVisible(true);
	}
	else
	{
		SetEnableButton(false);
		setPosition(m_hidePosition);
		setVisible(false);
	}
}

void BadugiSelectCardPanel::SendChangeCardReq()
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_bSendWait == false)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SendBadugiChangeCardReq();
		ShowBadugiSelectCardPanel(false);
	}
	else
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_bSendChanageRequest = true;
		SetEnableButton(false);
	}
	
}

void BadugiSelectCardPanel::SendChangePassReq()
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_bSendWait == false)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SendBadugiChangePassReq();
		ShowBadugiSelectCardPanel(false);
	}
	else
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_bSendPassRequest = true;
		SetEnableButton(false);
	}
	
}

void BadugiSelectCardPanel::SetEnableButton(bool _enable)
{
	m_ChangeBtn->setEnable(_enable);
	m_PassBtn->setEnable(_enable);
	m_SelectBtn1->setEnable(_enable);
	m_SelectBtn2->setEnable(_enable);
	m_SelectBtn3->setEnable(_enable);
	m_SelectBtn4->setEnable(_enable);

	if (_enable == false)
	{
		m_ChangeBtn->getButtonSkelObject()->playAnimation("change_end");
		m_ChangeBtn->getButtonSkelObject()->appendAnimation("change_stay");

		m_PassBtn->getButtonSkelObject()->playAnimation("pass_end");
		m_PassBtn->getButtonSkelObject()->appendAnimation("pass_stay");
	}
	else
	{
		m_ChangeBtn->getButtonSkelObject()->playAnimation("change_start");
		m_ChangeBtn->getButtonSkelObject()->appendAnimation("change_loop");

		m_PassBtn->getButtonSkelObject()->playAnimation("pass_start");
		m_PassBtn->getButtonSkelObject()->appendAnimation("pass_loop");
	}
}
