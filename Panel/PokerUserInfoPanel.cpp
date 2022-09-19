#include "pch.h"
#include "PokerUserInfoPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "PokerBackgroundPanel.h"
#include "GameStringDepot.h"
#include "GameRoomInfo.h"
#include "RoomUserData.h"
#include "RoomPlayerInfo.pb.h"
#include "PokerTopPanel.h"
#include "PokerPlayerInfoMyPanel.h"
#include "FriendHelper.h"
#include "PokerRankHelper.h"
#include "PokerResourceHelper.h"

#define DISAPPEAR_ACTION_TAG 255

PokerUserInfoPanel::PokerUserInfoPanel(int _panelType)
{
	m_bBlockEmotion = false;
	mPlayerOutFlag = false;
	m_PanelType = _panelType;
	m_PlayerOutButton = nullptr;
	mSmallFrirendBtnPanel = nullptr;
	m_userName = nullptr;
	m_userLevel = nullptr;
	m_winningRateLabel = nullptr;
	m_winningRateText = nullptr;
	m_pofitLabel = nullptr;
	m_pofitText = nullptr;

	m_madeLabel = nullptr;
	m_madeText = nullptr;
	m_allinLabel = nullptr;
	m_allinText = nullptr;

	m_bShowPanel = false;

	mEmotionBtn = nullptr;

	InitPanel();
	InitImage();
	initButton();
	//setTouchable(true);
	setButtonListener(this);
	refreshEmotionBtnState();
	refreshPlayerOutBtnState();
}

PokerUserInfoPanel::~PokerUserInfoPanel()
{
	//destruct();
}

void PokerUserInfoPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_userinfo_board.mxml");	
	mRankIcon = getSkel("skel_rank");
	mPlayOutLabel = getLabel("txt_out");
	//감정표현차단
	getLabel("txt_emoticon")->setString(GameStringDepot::getSingletonPtr()->getString("PokerUserInfoPanel_EMOTION_BLOCK").c_str());
	//창밖을 터치하면 닫기
	getLabel("txt_closeinfo")->setString(GameStringDepot::getSingletonPtr()->getString("PokerUserInfoPanel_CLOSE_DESC").c_str());

}

void PokerUserInfoPanel::InitImage()
{
	PokerBackgroundPanel* _pBackPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetBackgroundPanel();

	if (!_pBackPanel)
		return;

	switch (m_PanelType)
	{
		case PANEL_TYPE_LEFT_ONE:
		{
			CCRect _infoRect = _pBackPanel->getDummy("dmy_userinfo_board4");	//확정
			CCPoint _infoPanelPos = ccp(_infoRect.origin.x, -_infoRect.origin.y);
			setPosition(_infoPanelPos);						
			break;
		}
		case PANEL_TYPE_LEFT_TWO:
		{
			CCRect _infoRect = _pBackPanel->getDummy("dmy_userinfo_board2");	//확정
			CCPoint _infoPanelPos = ccp(_infoRect.origin.x, -_infoRect.origin.y);
			setPosition(_infoPanelPos);			
			break;
		}
		case PANEL_TYPE_RIGHT_ONE:
		{
			CCRect _infoRect = _pBackPanel->getDummy("dmy_userinfo_board5");
			CCPoint _infoPanelPos = ccp(_infoRect.origin.x, -_infoRect.origin.y);
			setPosition(_infoPanelPos);			
			break;
		}
		case PANEL_TYPE_RIGHT_TWO:
		{
			CCRect _infoRect = _pBackPanel->getDummy("dmy_userinfo_board3");	//확정
			CCPoint _infoPanelPos = ccp(_infoRect.origin.x, -_infoRect.origin.y);
			setPosition(_infoPanelPos);			
			break;
		}
		case PANEL_TYPE_MY:
		{
			CCRect _infoRect = _pBackPanel->getDummy("dmy_userinfo_board1");	//확정
			CCPoint _infoPanelPos = ccp(_infoRect.origin.x, -_infoRect.origin.y);
			setPosition(_infoPanelPos);
			break;
		}
	}

	getLabel("txt_username")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));//유저이름입니다" / >
	getLabel("txt_userlevel")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));//"LV.100" / >
	getLabel("txt_winning_rate")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));//"승률 : " / >
	getLabel("txt_profit")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));//"수익 : " / >
	getLabel("txt_winning_rate_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));//"xxx승/xxx패(xx%)" / >
	getLabel("txt_profit_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));//"xxx승/xxx패(xx%)" / >

	m_userName = getLabel("txt_username");
	m_userLevel = getLabel("txt_userlevel");
	m_winningRateLabel = getLabel("txt_winning_rate");
	m_winningRateText = getLabel("txt_winning_rate_sum");
	m_pofitLabel = getLabel("txt_profit");
	m_pofitText = getLabel("txt_profit_sum");
	mEmotionBtnLabel = getLabel("txt_emoticon");
	if (m_PanelType == PANEL_TYPE_MY)
	{
		setVislbleButton(getButton("sbtn_tbutton_left"), false);
		setVislbleButton(getButton("sbtn_tbutton_right"), false);		
		mEmotionBtnLabel->setVisible(false);
		getLabel("txt_out")->setVisible(false);		
	}
	else
	{		
		getLabel("txt_out")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));//txt_out		
	}

	m_pPhoto = new Widget();
	getImage("dmy_photo")->addChild(m_pPhoto);
	m_pPhoto->setSpriteFrameWithFile(FriendHelper::getDefaultImg());
	m_pPhoto->release();
}

void PokerUserInfoPanel::initButton()
{
	if (m_PanelType != PANEL_TYPE_MY)
	{
		mSmallFrirendBtnPanel = new SmallBtnPanel(this, "friendBtn");
		addChild(mSmallFrirendBtnPanel);
		mSmallFrirendBtnPanel->release();
		CCPoint pos = getDummy("dmy_button_small").origin;
		pos.y = -pos.y;
		mSmallFrirendBtnPanel->setPosition(pos);
		Button* friendBtn = mSmallFrirendBtnPanel->getSmallButton();		
		friendBtn->setType(Button::NoPressImg);
		friendBtn->getButtonSkelObject()->setSkin("txt_friend");		
		m_PlayerOutButton = getButton("sbtn_tbutton_left");
		m_PlayerOutButton->setType(Button::REAL_NO_ANI);
		m_PlayerOutButton->setListener(this);

		//감정 표시 차단
		mEmotionBtn = getButton("sbtn_tbutton_right");
	}	
}


bool PokerUserInfoPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	int _myPo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_MyPo;
	PokerPlayerInfoMyPanel* _myPanel = dynamic_cast<PokerPlayerInfoMyPanel*>(GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(_myPo));
	if (_myPanel)
	{
		if (_myPanel->TouchBadugiCardCheck(pTouch->getLocation()) == true)
		{
			m_bCancelTouch = true;
			return true;
		}
	}

	m_bShowPanel = false;
	int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(m_PanelType);
	PokerPlayerInfoCommonPanel* _pPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(_serverIndex);
	if (_pPanel)
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->isHiddenCheck() == true)
		{
			return false;
		}
		if(_pPanel->m_pUserPanelBtn->hasCollided(_pPanel->m_pUserPanelBtn->convertToNodeSpace(pTouch->getLocation())) == true)
		{
			if(GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
				return false;

			m_bCancelTouch = false;
			return true;
		}
		else if (isVisible() == true)
		{
			HidePanel();
			return false;
		}
	}

	//if (m_PlayerOutButton)
	//{
	//	if (m_PlayerOutButton->hasCollided(m_PlayerOutButton->convertToNodeSpace(pTouch->getLocation())) == true)
	//	{
	//		m_bCancelTouch = false;
	//		return true;
	//	}
	//}
	return false;
}


void PokerUserInfoPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//if (m_PlayerOutButton)
	//{
	//	if (m_PlayerOutButton->hasCollided(m_PlayerOutButton->convertToNodeSpace(pTouch->getLocation())) == false)
	//	{
	//		m_bCancelTouch = true;
	//	}
	//}
}


void PokerUserInfoPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bCancelTouch == true)
	{
		int _myPo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_MyPo;
		PokerPlayerInfoMyPanel* _myPanel = dynamic_cast<PokerPlayerInfoMyPanel*>(GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(_myPo));
		if (_myPanel)
		{
			_myPanel->TouchBadugiCard(pTouch->getLocation());
		}
		return;
	}

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_PlayStatus == PlayStatus::PLAY_CARD_CHOICE)
	{
		HidePanel();
		return;
	}

	int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(m_PanelType);
	PokerPlayerInfoCommonPanel* _pPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(_serverIndex);
	if (_pPanel->m_pUserPanelBtn)
	{
		if (_pPanel->m_pUserPanelBtn->hasCollided(_pPanel->m_pUserPanelBtn->convertToNodeSpace(pTouch->getLocation())) == true)
		{
			PokerTopPanel* _pTopPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetTopPanel();
			_pTopPanel->onClicked(_pPanel->m_pUserPanelBtn->getName());
			m_bShowPanel = true;
		}
	}

	//if (m_PlayerOutButton)
	//{
	//	if (m_PlayerOutButton->hasCollided(m_PlayerOutButton->convertToNodeSpace(pTouch->getLocation())) == true)
	//	{
	//		onClicked(m_PlayerOutButton->getName());
	//	}
	//}
}

void PokerUserInfoPanel::resume()
{
}

void PokerUserInfoPanel::HidePanel()
{
	m_bShowPanel = false;
	setActivatePanel(false);
}

void PokerUserInfoPanel::SetTimerShow()
{
	if (isVisible()) {
		setActivatePanel(false);
	}
	else{
		SetPanelString();
		cleanup();
		setActivatePanel(true);
	}	
}

void PokerUserInfoPanel::onClicked(const string& name)
{
	if (isVisible() == false)
		return;
	if (name == getButtonName(m_PlayerOutButton))
	{
		mPlayerOutFlag = !mPlayerOutFlag;
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_MasterPo != GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_MyPo)
			return;

		int _clientIndex = m_PanelType;
		int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_clientIndex);
		RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
		//플레이어 강퇴
		if (_pPlayer)
		{
			int64 _socketid = _pPlayer->m_pPlayerData->GetSocketID();
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->CanExit(_serverIndex))
			{
				TCPService::getSingletonPtr()->SendKickoutPlayerReq(_serverIndex, _socketid);	//한번 더 보내고.
			}
			else
			{
				TCPService::getSingletonPtr()->SendKickoutPlayerResvReq(_serverIndex, _socketid);
			}
		}
		refreshPlayerOutBtnState();
	}
	else if (name == mSmallFrirendBtnPanel->getButtonName())
	{
		//만약 친구라면
		//친구 삭제 보내고
		//친구가 아니라면
			//친구 요청중이라면
			//대기.
		int _clientIndex = m_PanelType;
		int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_clientIndex);
		RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
		//친구 추가
		if (_pPlayer)
		{
			vector<int64> _uidList;
			int64 _uid = _pPlayer->m_pPlayerData->GetUID();
			_uidList.push_back(_uid);

			if (FriendHelper::isFriend(_uid)) {
				//친구 삭제
				WebService::getSingletonPtr()->_sendFriendRemoveReq(_uid);
			}
			else if (!FriendHelper::isFriendRequest(_uid)) {
				WebService::getSingletonPtr()->_sendFriendRequestReq(_uidList);
				_pPlayer->m_IsFriendRequest = true;
				//mSmallFrirendBtnPanel->getSmallButton()->setEnable(false);
			}			
		}
		//창 닫자.
		//refreshFriendState();
		HidePanel();
	}
	else if (name == getButtonName(mEmotionBtn)) {
		if (m_bBlockEmotion == true)
		{
			m_bBlockEmotion = false;
			int _clientIndex = m_PanelType;
			int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_clientIndex);
			RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
			if (_pPlayer)
			{
				_pPlayer->m_bEmotionBlock = false;
			}
		}
		else
		{
			m_bBlockEmotion = true;
			int _clientIndex = m_PanelType;
			int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_clientIndex);
			RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);

			if (_pPlayer)
			{
				_pPlayer->m_bEmotionBlock = true;
			}

		}

		refreshEmotionBtnState();
	}	
}

void PokerUserInfoPanel::update(float dt)
{
}

bool PokerUserInfoPanel::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK>(&stCmd))
	{
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK res = *pstIt;

		if (res.param != GAMEUSER_PHOTO)
			return false;

		if (!res.imagePath.empty())
		{
			InitUserPhoto(false);
		}
		return true;
	}

	return false;
}

void PokerUserInfoPanel::SetPanelString()
{
	int _clientIndex = m_PanelType;
	int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_clientIndex);
	RoomUserData* _pUserInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
	PlayerData* _pPlayerInfo = _pUserInfo->m_pPlayerData;

	string _labelText = _pPlayerInfo->m_NickName;
	m_userName->setString(_labelText.c_str());
	_labelText = "LV." + StringConverter::toString(_pPlayerInfo->m_Level);
	m_userLevel->setString(_labelText.c_str());
	_labelText = GameStringDepot::getSingletonPtr()->getString("TXT_WIN_PERCENT") + " : ";
	m_winningRateLabel->setString(_labelText.c_str());

	GameKind _kind = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind();
	int _win = _pUserInfo->m_CurWin;
	int _lose = _pUserInfo->m_CurLose;
	int _winPercent = 0;
	if (_win != 0)
	{
		_winPercent = (_win * 100) / (_win + _lose);
	}
	_labelText = StringConverter::toString(_win) + GameStringDepot::getSingletonPtr()->getString("TXT_TOTAL_WIN");
	_labelText += StringConverter::toString(_lose) + GameStringDepot::getSingletonPtr()->getString("TXT_TOTAL_LOSE");
	_labelText += "(" + StringConverter::toString(_winPercent) + "%)";
	m_winningRateText->setString(_labelText.c_str());

	_labelText = GameStringDepot::getSingletonPtr()->getString("TXT_WIN_RATE");
	m_pofitLabel->setString(_labelText.c_str());

	_labelText = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_pUserInfo->m_AcqMoney), 2);
	m_pofitText->setString(_labelText.c_str());

	if (m_PanelType == PANEL_TYPE_MY)
	{
	}
	else
	{
		refreshFriendState(); //친구 소개 설정		
	}

	//Friend
	Button* smallFriendBtn = nullptr;
	if (mSmallFrirendBtnPanel)
		smallFriendBtn = mSmallFrirendBtnPanel->getSmallButton();

	if (smallFriendBtn)
	{
		int _size = GameDataManager::getSingletonPtr()->m_FriendDataList.size();
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _pfriend = GameDataManager::getSingletonPtr()->m_FriendDataList[_i];
			if (_pfriend == nullptr)
				continue;

			if (_pfriend->uid() == _pPlayerInfo->GetUID())
			{
				_pUserInfo->m_IsFriendRequest = true;
				smallFriendBtn->setEnable(false);
			}
			else
			{
				_pUserInfo->m_IsFriendRequest = false;
				smallFriendBtn->setEnable(true);
			}
		}
	}	
	InitUserPhoto(true);
	PokerRankHelper::setRankIcon(mRankIcon, _pPlayerInfo->m_Vip);
}


void PokerUserInfoPanel::InitUserPhoto(bool isTryDownload)
{
	int _clientIndex = m_PanelType;
	int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_clientIndex);
	RoomUserData* _pUserInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
	PlayerData* _info = _pUserInfo->m_pPlayerData;

	//bool _ret;
	//if (_info->m_thumbnailUrl != "")
	//{
	//	_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
	//		_info->m_NickName,
	//		_info->m_thumbnailUrl,
	//		DOWNLOAD_FILE_TYPE::GAMEUSER_PHOTO,
	//		m_pPhoto,
	//		isTryDownload,
	//		TEMP_PHOTO_FOLDER
	//		);

	//	// 로딩되었으면 이미지를 교체한다.
	//	if (_ret)
	//	{
	//		UpdateUserPhoto();
	//	}
	//}
	//else
	//{
	//	m_pPhoto->setSpriteFrameWithFile(PokerResourceHelper::getCharacterPhotoImg(_info->m_CharacterIdx));
	//	UpdateUserPhoto();		
	//}

	m_pPhoto->setSpriteFrameWithFile(PokerResourceHelper::getCharacterPhotoImg(_info->m_CharacterIdx));
	UpdateUserPhoto();
}

void PokerUserInfoPanel::UpdateUserPhoto()
{
	CCRect rect = getDummy("dmy_photo");
	m_pPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
	m_pPhoto->setVisible(true);
}


void PokerUserInfoPanel::setEmotionActivate(bool visible)
{
	if (visible) {

	}
}

void PokerUserInfoPanel::refreshEmotionBtnState()
{
	if (mEmotionBtn) {
		if (m_bBlockEmotion) {
			//false 가 차단 안한 상태
			mEmotionBtn->setSkelAnimation("tbuttonr_on");						
			mEmotionBtnLabel->setColor(StringConverter::parseColor3B("372004"));
		}
		else {
			//true 가 차단 안한 상태
			mEmotionBtn->setSkelAnimation("tbuttonr_off");
			mEmotionBtnLabel->setColor(StringConverter::parseColor3B("f4c868"));
		}
	}
}

void PokerUserInfoPanel::refreshPlayerOutBtnState()
{
	if (m_PlayerOutButton) {
		if (mPlayerOutFlag) {
			m_PlayerOutButton->setSkelAnimation("tbuttonl_on"); 
			string buttonStr = GameStringDepot::getSingleton().getString("PokerUserInfoPanel_CANCEL");
			mPlayOutLabel->setString(buttonStr.c_str());			
			mPlayOutLabel->setColor(StringConverter::parseColor3B("372004")); 
		}
		else {
			string buttonStr = GameStringDepot::getSingleton().getString("PokerUserInfoPanel_OUT"); 
			m_PlayerOutButton->setSkelAnimation("tbuttonl_off");
			mPlayOutLabel->setString(buttonStr.c_str());			
			mPlayOutLabel->setColor(StringConverter::parseColor3B("f4c868"));
		}

		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr() != nullptr) {
			bool bMasterIsMe = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_MasterPo == GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_MyPo;
			if (bMasterIsMe == false)
				mPlayOutLabel->setColor(StringConverter::parseColor3B("66523c"));
		}		
	}
}

void PokerUserInfoPanel::setActivatePanel(bool visible)
{
	setVisible(visible);
	float posX = getPositionX();
	if (visible) {		
		if (posX < 0) {
			posX += DESIGN_WIDTH;
			setPositionX(posX);
			CCDelayTime* delay = CCDelayTime::create(3.0f);
			CCFiniteTimeAction* callback = CCCallFunc::create(this, callfunc_selector(PokerUserInfoPanel::setNovisibleTimeOver));
			CCAction* disAppearAction = CCSequence::create(delay, callback , NULL);
			disAppearAction->setTag(DISAPPEAR_ACTION_TAG);			
			runAction(disAppearAction);
		}
	}
	else {
		if (posX > 0) {
			posX -= DESIGN_WIDTH;
			setPositionX(posX);
			stopActionByTag(DISAPPEAR_ACTION_TAG);
		}
	}
}

void PokerUserInfoPanel::initButtonState()
{
	m_bBlockEmotion = false;
	mPlayerOutFlag = false;
	refreshEmotionBtnState();
	refreshPlayerOutBtnState();
}

void PokerUserInfoPanel::refreshFriendState()
{
	//친구가 아니라면
	//친구라면 친구 삭제라 보인다.
	//아니라면 요청중 혹은 요청보내기등	
	int _clientIndex = m_PanelType;
	int _serverIndex = GameDataManager::getSingletonPtr()->ClientToServerIndex(_clientIndex);
	RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_serverIndex);
	//친구 추가
	if (_pPlayer)
	{
		int64 _uid = _pPlayer->m_pPlayerData->GetUID();
		if (FriendHelper::isFriend(_uid)) {
			//친구 삭제
			string inviteStr = GameStringDepot::getSingleton().getString("POKER_USERINFO_DELETE");
			mSmallFrirendBtnPanel->setButtonLabel(inviteStr);
		}
		else if (FriendHelper::isFriendRequest(_uid)) {
			string inviteStr = GameStringDepot::getSingleton().getString("POKER_USERINFO_REQUEST");
			mSmallFrirendBtnPanel->setButtonLabel(inviteStr);
		}
		else {
			string inviteStr = GameStringDepot::getSingleton().getString("POKER_USERINFO_INVITE");
			mSmallFrirendBtnPanel->setButtonLabel(inviteStr);
		}
	}
}

void PokerUserInfoPanel::setNovisibleTimeOver()
{
	HidePanel();
}

void PokerUserInfoPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}