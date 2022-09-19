#include "pch.h"
#include "FriendCell.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "FriendHelper.h"
#include "PokerResourceHelper.h"

FriendCell::FriendCell()
{
	mIndex = -1;

	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

FriendCell::~FriendCell()
{
	//destruct();
}

void FriendCell::InitPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_f_bar.mxml");
	mMainPanel->setButtonListener(this);
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);
}

void FriendCell::InitImage()
{
	mMainPanel->getLabel("txt_username")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_lastjoin")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	mUserPhoto = mMainPanel->getImage("dmy_photo");
	
	m_userName = mMainPanel->getLabel("txt_username");
	m_lastJoin = mMainPanel->getLabel("txt_lastjoin");
}	

void FriendCell::initButton()
{
	CCPoint _sendBtnPos = mMainPanel->getDummy("dmy_button_slot1").origin;
	CCPoint _getBtnPos = mMainPanel->getDummy("dmy_button_slot2").origin;
	CCPoint _removeBtnPos = mMainPanel->getDummy("dmy_button_slot3").origin;

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

	mRemoveBtnPanel = new SlotButtonPanel();
	mRemoveBtnPanel->setPositionX(_removeBtnPos.x);
	mRemoveBtnPanel->setPositionY(-_removeBtnPos.y);
	mMainPanel->addChild(mRemoveBtnPanel);
	mRemoveBtnPanel->release();	

	m_userTouch = mMainPanel->getButton("sbtn_usertouch");
	m_sendGiftBtn = m_SendBtnPanel->m_Button;
	m_sendGiftBtn->setName("m_sendGiftBtn");
	m_getGiftBtn = m_GetBtnPanel->m_Button;
	m_getGiftBtn->setName("m_getGiftBtn");

	mRemoveBtn = mRemoveBtnPanel->m_Button;
	mRemoveBtn->setName("mRemoveBtn");

	m_sendGiftBtn->setPaused(true);
	m_getGiftBtn->setPaused(true);
	mRemoveBtn->setPaused(true);

	m_SendBtnPanel->SetBtnType(TYPE_SEND_CHIP_OFF);
	m_GetBtnPanel->SetBtnType(TYPE_GET_CHIP_OFF);

	mRemoveBtnPanel->SetBtnType(TYPE_APPLY_FRIEND);
	mRemoveBtnPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("POKER_USERINFO_DELETE").c_str());

	m_userTouch->setVisible(false);
	m_userTouch->setPaused(true);
}

void FriendCell::onClicked(const string& name)
{
	if (name == getButtonName(m_sendGiftBtn)) {
		//보내기
		fireMessage("FRIEND_GIFT" + StringConverter::toString(mIndex));
	}
	else if (name == getButtonName(m_getGiftBtn)) {
		//받기
		fireMessage("FRIEND_GET" + StringConverter::toString(mIndex));
	}
	else if (name == getButtonName(mRemoveBtn)) {
		fireMessage("FRIEND_CONFIRM_REMOVE" + StringConverter::toString(mIndex));
	}
}

void FriendCell::setFriendInfo(int idx)
{
	mIndex = idx;

	if (idx % 2 == 0) {
		mMainPanel->getSkel("skel_bar")->playAnimation("bar_longa");
	}
	else {
		mMainPanel->getSkel("skel_bar")->playAnimation("bar_longb");
	}

	W_FriendInfo* _pInfo = GameDataManager::getSingletonPtr()->m_FriendDataList[idx];
	if (_pInfo == nullptr)
	{
		return;
	}

	if (_pInfo->has_name())
		m_userName->setString(_pInfo->name().c_str());

	if (_pInfo->has_connecttime())
		m_lastJoin->setString(_pInfo->connecttime().c_str());

	if (_pInfo->has_isgiftreceive())
	{
		if (_pInfo->isgiftreceive())
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

	if (_pInfo->has_isgiftsend())
	{
		if (_pInfo->isgiftsend())
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
	InitFriendPhoto(mIndex, true);
}

void FriendCell::InitFriendPhoto(int _index, bool isTryDownload)
{
	if (_index == -1)
		return;

	if (_index != mIndex)
		return;

	W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_FriendDataList[mIndex];
	bool _ret;
	DOWNLOAD_FILE_TYPE _type = DOWNLOAD_FILE_TYPE::FRIEND_PHOTO;
	//기덕 default 이미지
	mUserPhoto->setSpriteFrameWithFile(FriendHelper::getDefaultImg());
	//if (_info->has_imageurl() && _info->imageurl() != "")
	//{
	//	_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
	//		_info->name(),
	//		_info->imageurl(),
	//		_type,
	//		mUserPhoto,
	//		isTryDownload,
	//		STATIC_PHOTO_FOLDER,
	//		_index
	//		);

	//	// 로딩되었으면 이미지를 교체한다.
	//	if (_ret)
	//	{
	//		UpdateFriendPhoto(_index);			
	//	}
	//}
	//else
	//{
	//	mUserPhoto->setSpriteFrameWithFile(PokerResourceHelper::getCharacterPhotoImg(_info->characterid()));
	//}
	mUserPhoto->setSpriteFrameWithFile(PokerResourceHelper::getCharacterPhotoImg(_info->characterid()));
	CCRect rect = mMainPanel->getDummy("dmy_photo");
	mUserPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
}

void FriendCell::UpdateFriendPhoto(int _cellIndex)
{
	CCRect rect = mMainPanel->getDummy("dmy_photo");
	mUserPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
}

void FriendCell::cellTouch(const CCPoint& touchPoint)
{
	if (m_sendGiftBtn->hasCollided(m_sendGiftBtn->convertToNodeSpace(touchPoint))){
		if (m_sendGiftBtn->isEnabled()){
			onClicked(m_sendGiftBtn->getName());
			CCDelayTime* delay = CCDelayTime::create(CELL_TOUCH_TIME * 2);
			CCActionInstant* func = CCCallFuncN::create(this, callfuncN_selector(FriendCell::_cellTouchEnd));
			m_sendGiftBtn->runAction(CCSequence::create(delay, func, nullptr));
			return;
		}
	}
	else if (m_getGiftBtn->hasCollided(m_getGiftBtn->convertToNodeSpace(touchPoint))){
		if (m_getGiftBtn->isEnabled()){
			onClicked(m_getGiftBtn->getName());
			CCDelayTime* delay = CCDelayTime::create(CELL_TOUCH_TIME * 2);
			CCActionInstant* func = CCCallFuncN::create(this, callfuncN_selector(FriendCell::_cellTouchEnd));
			m_getGiftBtn->runAction(CCSequence::create(delay, func, nullptr));
			return;
		}
	}
	else if (mRemoveBtn->hasCollided(mRemoveBtn->convertToNodeSpace(touchPoint))){
		if (mRemoveBtn->isEnabled()){
			onClicked(mRemoveBtn->getName());
			CCDelayTime* delay = CCDelayTime::create(CELL_TOUCH_TIME * 2);
			CCActionInstant* func = CCCallFuncN::create(this, callfuncN_selector(FriendCell::_cellTouchEnd));
			mRemoveBtn->runAction(CCSequence::create(delay, func, nullptr));
			return;
		}
	}
}

void FriendCell::_cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}