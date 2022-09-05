#include "pch.h"
#include "ChannelRoomCell.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
//#include "SimplePopupPanel.h"
//#include "HeroApp.h"

#include "Web/WebService.h"
#include "GameStringDepot.h"
#include "LobbyScene.h"
#include "PokerShopHelper.h"

ChannelRoomCell::ChannelRoomCell()
{
	mLoginProcess = false;
	InitPanel();
	InitImage();
	InitButton();

	setTouchable(false);
	setButtonListener(this);
}

ChannelRoomCell::~ChannelRoomCell()
{
	//destruct();
}

void ChannelRoomCell::InitPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_room_list_panel.mxml");
	mMainPanel->setButtonListener(this);
	CCSize contentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(contentSize.height - DESIGN_HEIGHT - contentSize.height / 2.f);
	mMainPanel->setPositionX(-contentSize.width / 2.f);
	mMainPanel->setContentSize(contentSize);
	this->setContentSize(contentSize);
}

void ChannelRoomCell::InitImage()
{
	mEnterBtn = mMainPanel->getButton("sbtn_button");
	mEnterBtnLabel = mMainPanel->getLabel("txt_button");
	mEnterBtnUnderLabel = mMainPanel->getLabel("txt_button_under");

	mMainPanel->getSkel("skel_user2")->setFlipX(true);
	mMainPanel->getSkel("skel_user4")->setFlipX(true);

	string buttonStr = "";
	string roomStr = "";
	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_7POKER) {
		buttonStr = "button_in_seven";
		roomStr = "room_seven";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HIGH_LOW) {
		buttonStr = "button_highlow";
		roomStr = "room_highlow";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_BADUKI) {
		buttonStr = "button_in_badugi";
		roomStr = "room_badugi";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM) {
		buttonStr = "button_in_texas";
		roomStr = "room_texas";
	}
	mMainPanel->getSkel("skel_room")->playAnimation(roomStr);
	mEnterBtn->setSkelAnimation(buttonStr);
	setButtonListener(this);
}

void ChannelRoomCell::InitButton()
{
	
}

void ChannelRoomCell::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void ChannelRoomCell::onClicked(const string& name)
{
	if (isVisible() == false)
		return;

	if (mLoginProcess)
		return;

	if (name == getButtonName(mEnterBtn))
	{
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			if (m_isSecret)
			{
				CustomPopupPanel* _panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::ENTER_CHANNEL_ROOM_TYPE, m_idx);
				if (_panel)
				{
					LayerManager::getSingleton().pushDynamicLayer(_panel, DYNAMIC_PUSH_LAYER);
				}
			}
			else
			{
				_pScene->EnterGameRoom(m_idx, "");
				//GameDataManager::getSingletonPtr()->GetChannelPanel()->onClicked("sbtn_option_button");
			}
			
		}
	}
}

void ChannelRoomCell::update(float dt)
{

}

bool ChannelRoomCell::handling(STCMD &stCmd)
{
	if (!mLoginProcess)
		return false;

	return false;
}

void ChannelRoomCell::UpdateRoomInfo(int _index)
{
	RoomInfo* _pInfo;
	if (GameDataManager::getSingletonPtr()->m_RoomInfoList.size() <= _index)
	{
		SetDisable();
		return;
	}
	else
		_pInfo = GameDataManager::getSingletonPtr()->m_RoomInfoList[_index];

	if (!_pInfo->IsInitialized())
	{
		SetDisable();
		return;
	}

	m_idx = _pInfo->roomidx();
	string _roomNumber = "No." + StringConverter::toString(m_idx);
	//string _roomNumber = "Room[" + StringConverter::toString(_index) + "]";
	setRoomNumber(_roomNumber);

	_pInfo->masterpo();
	_pInfo->currentuser();
	_pInfo->maxuser();

	if (_pInfo->issecret())
	{
		m_isSecret = true;
		mMainPanel->getSkel("skel_lock")->setVisible(true);
		
	}
	else
	{
		m_isSecret = false;
		mMainPanel->getSkel("skel_lock")->setVisible(false);
	}

	int _size = _pInfo->playerinfo_size();
	if (_pInfo->potmoney() > 0 && _size > 1)
	{
		string pot = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_pInfo->potmoney()), 2);
		mMainPanel->getLabel("txt_room_rule")->setString(pot.c_str());
	}
	else
		mMainPanel->getLabel("txt_room_rule")->setString("READY");
	
	if (_pInfo->issecret())
	{
		//열쇠 표시
	}
	else {
		//열쇠 푯히 안하고
	}
	
	if (_size == 5)
	{
		mEnterBtn->setEnable(false);
		mEnterBtn->setGrayscale(true);
		//5명이면 입장 불가
		string enterBtnStr = GameStringDepot::getSingleton().getString("ChannelRoomCell_FULL");
		mEnterBtnLabel->setVisible(true);
		mEnterBtnUnderLabel->setVisible(true);
		mEnterBtnLabel->setString(enterBtnStr.c_str());
		mEnterBtnUnderLabel->setString(enterBtnStr.c_str());
		mEnterBtnLabel->setGrayscale(true);
		

	}
	else
	{
		mEnterBtn->setEnable(true);
		mEnterBtn->setGrayscale(false);
		//5명이면 입장
		string enterBtnStr = GameStringDepot::getSingleton().getString("ChannelRoomCell_ENTER");
		mEnterBtnLabel->setVisible(true);
		mEnterBtnUnderLabel->setVisible(true);
		mEnterBtnLabel->setString(enterBtnStr.c_str());
		mEnterBtnUnderLabel->setString(enterBtnStr.c_str());
		mEnterBtnLabel->setGrayscale(false);
		
	}
	mEnterBtn->setVisible(true);
	mEnterBtnLabel->setVisible(true);
	mEnterBtnUnderLabel->setVisible(true);	
	for (int _i = 0; _i < 5; _i++)
	{
		if (_i < _size)
			setRoomUser(_i, true, _pInfo->playerinfo(_i).nickname() , _pInfo->playerinfo(_i).charidx());
		else
			setRoomUser(_i, false);
	}
}

void ChannelRoomCell::SetDisable()
{
	mEnterBtnLabel->setVisible(false);
	mEnterBtnUnderLabel->setVisible(false);
	m_idx = -1;
	setRoomNumber("");
	mMainPanel->getLabel("txt_room_rule")->setString("");

	m_isSecret = false;
	mMainPanel->getSkel("skel_lock")->setVisible(false);
	mMainPanel->getLabel("txt_room_rule")->setString("");
	mEnterBtn->setVisible(false);
	mEnterBtn->setEnable(false);

	for (int _i = 0; _i < 5; _i++)
	{
		setRoomUser(_i, false);
	}
}

void ChannelRoomCell::setRoomNumber(string _str)
{
	mMainPanel->getLabel("txt_room_number_sum")->setString(_str.c_str());
}

void ChannelRoomCell::setRoomUser(int _idx, bool _visible, string _username, int characterIdx)
{
	if (_idx >= 5)
		return;

	string _SkelName1 = "skel_user" + StringConverter::toString(_idx + 1);
	string _LabelName = "txt_user_name_" + StringConverter::toString(_idx + 1);
	mMainPanel->getSkel(_SkelName1)->setVisible(_visible);
	mMainPanel->getLabel(_LabelName)->setVisible(_visible);
	if (_username != "")
	{
		mMainPanel->getLabel(_LabelName)->setString(_username.c_str());
	}

	if (characterIdx != -1) {
		const W_CharacterData characterData = PokerShopHelper::getCharacterData(characterIdx);
		string iconStr = "icon_" + characterData.image();
		mMainPanel->getSkel(_SkelName1)->playAnimation(iconStr);
	}
}

void ChannelRoomCell::setActivate(bool activate)
{
	if (activate) {		
		mEnterBtn->setEnable(true);
		setVisible(true);
	}
	else {	
		setVisible(false);
		SetDisable();		
	}
}
void ChannelRoomCell::onEnter()
{
	Panel::onEnter();

	scheduleUpdate();
}