#include "pch.h"
#include "FriendCellMiddle.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "FriendHelper.h"
#include "PokerResourceHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include "android/FacebookManager.h"
#endif

FriendCellMiddle::FriendCellMiddle(FRIEND_CELL_TYPE type)
{
	mCellType = type;
	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

FriendCellMiddle::~FriendCellMiddle()
{
	//destruct();
}

void FriendCellMiddle::InitPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();

	if (mCellType == FACEBOOK_REQUEST_TYPE)
		mMainPanel->construct(getMxmlPath() + "dmy_f_barmiddle.mxml");
	else
		mMainPanel->construct(getMxmlPath() + "dmy_f_barmiddle.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);
	mMainPanel->pauseAllButtons();
}

void FriendCellMiddle::InitImage()
{
	mUserPhoto = mMainPanel->getImage("dmy_photo");
	m_userName = mMainPanel->getLabel("txt_username");
	m_lastJoin = nullptr;
	if (mMainPanel->hasElement("txt_lastjoin"))
		m_lastJoin = mMainPanel->getLabel("txt_lastjoin");
}	

void FriendCellMiddle::initButton()
{
	CCPoint _sendBtnPos = mMainPanel->getDummy("dmy_button_slot1").origin;
	CCPoint _getBtnPos = mMainPanel->getDummy("dmy_button_slot2").origin;

	m_SendBtnPanel = new SlotButtonPanel();
	m_SendBtnPanel->setPositionX(_sendBtnPos.x);
	m_SendBtnPanel->setPositionY(-_sendBtnPos.y);
	mMainPanel->addChild(m_SendBtnPanel);
	m_SendBtnPanel->release();

	m_GetBtnPanel = new SlotButtonPanel();
	m_GetBtnPanel->setPositionX(_getBtnPos.x);
	m_GetBtnPanel->setPositionY(-_getBtnPos.y);
	mMainPanel->addChild(m_GetBtnPanel);
	m_GetBtnPanel->release();

	m_sendGiftBtn = m_SendBtnPanel->m_Button;
	m_sendGiftBtn->setPaused(true);
	m_sendGiftBtn->setName("m_sendGiftBtn");
	m_getGiftBtn = m_GetBtnPanel->m_Button;
	m_getGiftBtn->setPaused(true);
	m_getGiftBtn->setName("m_getGiftBtn");
	m_SendBtnPanel->SetBtnType(TYPE_SEND_CHIP_OFF);
	m_GetBtnPanel->SetBtnType(TYPE_GET_CHIP_OFF);

	if (mCellType == FRIEND_REQUEST_TYPE) {
		m_SendBtnPanel->SetBtnType(TYPE_APPLY_FRIEND);
		m_GetBtnPanel->SetBtnType(TYPE_APPLY_FRIEND);

		m_GetBtnPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_AGREE").c_str());
		m_SendBtnPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_DISAGREE").c_str());
	}
	else if (mCellType == FACEBOOK_REQUEST_TYPE) {
		m_SendBtnPanel->SetBtnType(TYPE_SEND_CHIP_OFF);
		m_GetBtnPanel->SetBtnType(TYPE_GET_CHIP_OFF);
	}
	else {
		m_sendGiftBtn->setVisible(false);
		m_sendGiftBtn->setEnable(false);
		m_SendBtnPanel->setVisible(false);
		m_GetBtnPanel->SetBtnType(TYPE_APPLY_FRIEND);
	}
}

void FriendCellMiddle::onClicked(const string& name)
{
	CCLog("FriendCellMiddle::onClicked");
	if (name == getButtonName(m_sendGiftBtn)) {
		CCLog("FriendCellMiddle::m_sendGiftBtn");
		if (mCellType == FRIEND_REQUEST_TYPE) {
			//FriendRequestReject
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);			
			W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_RequestDataList[mCellIndex];
			if (_info->has_uid())
			{
				vector<int64> _uidList;
				_uidList.push_back(_info->uid());
				WebService::getSingletonPtr()->_sendFriendRejectReq(_uidList);
			}
		}
		else if (mCellType == FRIEND_RECOMMEND_TYPE) {
		}
		else if (mCellType == FACEBOOK_REQUEST_TYPE) {
			//FriendRequestReject
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_SnsDataList[mCellIndex];
			if (_info->has_uid())
			{
				vector<int64> _uidList;
				_uidList.push_back(_info->uid());
				WebService::getSingletonPtr()->_sendFaceFriendGiftSendReq(_uidList);
			}
		}
	}
	else if (name == getButtonName(m_getGiftBtn)) {
		CCLog("FriendCellMiddle::m_getGiftBtn");
		if (mCellType == FRIEND_REQUEST_TYPE) {
			//FriendRequestAccept
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);			
			W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_RequestDataList[mCellIndex];
			CCLog("FriendCellMiddle::m_getGiftBtn = status = %d", _info->has_status());
			CCLog("FriendCellMiddle::m_getGiftBtn = uid = %d", _info->has_uid());			
			if (_info->has_status() && _info->has_uid())
			{
				CCLog("FriendCellMiddle::_sendFriendAddReq");
				vector<int64> _uidList;
				_uidList.push_back(_info->uid());
				CCLog("FriendCellMiddle::_sendFriendAddReq = %d", _info->uid());
				WebService::getSingletonPtr()->_sendFriendAddReq(_uidList);
			}
		}
		else if (mCellType == FRIEND_RECOMMEND_TYPE) {
			//FriendReCommendReq
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_RecommendDataList[mCellIndex];
			if (_info->has_uid())
			{
				vector<int64> _uidList;
				_uidList.push_back(_info->uid());
				WebService::getSingletonPtr()->_sendFriendRequestReq(_uidList);
			}		
		}
		else if (mCellType == FACEBOOK_REQUEST_TYPE) {
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_SnsDataList[mCellIndex];
			if (_info->has_uid())
			{
				vector<int64> _uidList;
				_uidList.push_back(_info->uid());
				WebService::getSingletonPtr()->_sendFaceFriendGiftReceiveReq(_uidList);
			}
		}
	}	
}

void FriendCellMiddle::setFriendInfo(int idx)
{
	mCellIndex = idx;
	if (idx % 2 == 0) {
		mMainPanel->getSkel("skel_bar")->playAnimation("bar_middlea");
	}
	else {
		mMainPanel->getSkel("skel_bar")->playAnimation("bar_middleb");
	}

	W_FriendInfo* _info = nullptr;
	
	if (mCellType == FRIEND_REQUEST_TYPE) {
		_info = GameDataManager::getSingletonPtr()->m_RequestDataList[mCellIndex];
	}
	else if (mCellType == FRIEND_RECOMMEND_TYPE) {
		_info = GameDataManager::getSingletonPtr()->m_RecommendDataList[mCellIndex];
		switch (_info->status())
		{
		case W_FriendInfo_eFriendStatus_eWait:
			m_getGiftBtn->getButtonSkelObject()->playAnimation("button_slot_o");
			m_GetBtnPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_FRIEND_APPLY").c_str());
			m_getGiftBtn->setEnable(true);
			break;
		case W_FriendInfo_eFriendStatus_eRequest:
			m_getGiftBtn->getButtonSkelObject()->playAnimation("button_slot_off");
			m_GetBtnPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_FRIEND_APPLY_WAIT").c_str());
			m_getGiftBtn->setEnable(false);
			break;
		case W_FriendInfo_eFriendStatus_eFriend:
			m_getGiftBtn->getButtonSkelObject()->playAnimation("button_slot_b");
			m_GetBtnPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_FRIEND_COMPLETE").c_str());
			m_getGiftBtn->setEnable(false);
			break;
		}
	}	
	else if (mCellType == FACEBOOK_REQUEST_TYPE) {
		_info = GameDataManager::getSingletonPtr()->m_SnsDataList[mCellIndex];
		if (_info->has_isgiftsend())
		{
			if (_info->isgiftsend())
			{
				m_sendGiftBtn->setEnable(true);
				m_sendGiftBtn->setSkelAnimation("button_slot_o");
				m_SendBtnPanel->SetBtnType(TYPE_SEND_CHIP);
			}
			else
			{
				m_sendGiftBtn->setEnable(false);
				m_sendGiftBtn->setSkelAnimation("button_slot_off");
				m_SendBtnPanel->SetBtnType(TYPE_SEND_CHIP_OFF);
			}
		}

		if (_info->has_isgiftreceive())
		{
			if (_info->isgiftreceive())
			{
				m_getGiftBtn->setEnable(true);
				m_getGiftBtn->setSkelAnimation("button_slot_o");
				m_GetBtnPanel->SetBtnType(TYPE_GET_CHIP);
			}
			else
			{
				m_getGiftBtn->setEnable(false);
				m_getGiftBtn->setSkelAnimation("button_slot_off");
				m_GetBtnPanel->SetBtnType(TYPE_GET_CHIP_OFF);
			}
		}

	}
	
	if(mCellType == FACEBOOK_REQUEST_TYPE) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		string facebookName = "";
		CCLog("FACEBOOK_REQUEST_TYPE = %s", _info->name().c_str());
		facebookName = FacebookManager::getSingleton().getFacebookFriendName(_info->name());
		m_userName->setString(facebookName.c_str());
#endif
	}
	else {
		if (_info->has_name())
			m_userName->setString(_info->name().c_str());
	}

	if (_info->has_connecttime())
	{
		if (m_lastJoin)
			m_lastJoin->setString(_info->connecttime().c_str());
	}
	else
	{
		if(m_lastJoin)
			m_lastJoin->setString("");
	}
	InitFriendPhoto(mCellIndex, true);
}

void FriendCellMiddle::InitFriendPhoto(int _index, bool isTryDownload)
{
	if (_index == -1)
		return;

	if (_index != mCellIndex)
		return;

	W_FriendInfo* _info = NULL;
	DOWNLOAD_FILE_TYPE _type = DOWNLOAD_FILE_TYPE::FRIEND_PHOTO;

	if (mCellType == FRIEND_REQUEST_TYPE) {
		_info = GameDataManager::getSingletonPtr()->m_RequestDataList[mCellIndex];		
		CCLog("InitFriendPhoto FRIEND_REQUEST_TYPE"); 
	}
	else if (mCellType == FACEBOOK_REQUEST_TYPE) {
		_info = GameDataManager::getSingletonPtr()->m_SnsDataList[mCellIndex];
		CCLog("InitFriendPhoto FACEBOOK_REQUEST_TYPE = %s" , _info->imageurl().c_str());
		_type = DOWNLOAD_FILE_TYPE::SNS_FRIEND_PHOTO;
	}
	else {
		_info = GameDataManager::getSingletonPtr()->m_RecommendDataList[mCellIndex];
		_type = DOWNLOAD_FILE_TYPE::RECOMMEND_PHOTO;
	}

	bool _ret;
	
	//기덕 default 이미지
	mUserPhoto->setSpriteFrameWithFile(FriendHelper::getDefaultImg());
	if (mCellType == FRIEND_REQUEST_TYPE) {
		CCLog("InitFriendPhoto FRIEND_REQUEST_TYPE _info = %s", _info->imageurl().c_str());
	}

	if (_info->has_imageurl() && _info->imageurl() != "")
	{
		_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
			_info->name(),
			_info->imageurl(),
			_type,
			mUserPhoto,
			isTryDownload,
			TEMP_PHOTO_FOLDER,
			_index
			);
		
		if (mCellType == FRIEND_REQUEST_TYPE) {
			CCLog("InitFriendPhoto _ret = %d", _ret);
		}
		// 로딩되었으면 이미지를 교체한다.
		if (_ret)
		{
			UpdateFriendPhoto(_index);
		}
	}
	else
	{
		mUserPhoto->setSpriteFrameWithFile(PokerResourceHelper::getCharacterPhotoImg(_info->characterid()));
	}

	CCRect rect = mMainPanel->getDummy("dmy_photo");
	mUserPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
}

void FriendCellMiddle::UpdateFriendPhoto(int _cellIndex)
{
	CCRect rect = mMainPanel->getDummy("dmy_photo");
	mUserPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
}

void FriendCellMiddle::cellTouch(const CCPoint& touchPoint)
{
	if (m_sendGiftBtn->hasCollided(m_sendGiftBtn->convertToNodeSpace(touchPoint))){
		if (m_sendGiftBtn->isEnabled()){
			onClicked(m_sendGiftBtn->getName());
			CCDelayTime* delay = CCDelayTime::create(CELL_TOUCH_TIME * 2);
			CCActionInstant* func = CCCallFuncN::create(this, callfuncN_selector(FriendCellMiddle::_cellTouchEnd));
			m_sendGiftBtn->runAction(CCSequence::create(delay, func, nullptr));
			return;
		}
	}
	else if (m_getGiftBtn->hasCollided(m_getGiftBtn->convertToNodeSpace(touchPoint))){
		if (m_getGiftBtn->isEnabled()){
			onClicked(m_getGiftBtn->getName());
			CCDelayTime* delay = CCDelayTime::create(CELL_TOUCH_TIME * 2);
			CCActionInstant* func = CCCallFuncN::create(this, callfuncN_selector(FriendCellMiddle::_cellTouchEnd));
			m_getGiftBtn->runAction(CCSequence::create(delay, func, nullptr));
			return;
		}
	}
}

void FriendCellMiddle::_cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}
