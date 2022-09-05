#include "pch.h"
#include "LobbyFriendInvitePanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "FriendCellMiddle.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include "android/FacebookManager.h"
#include "android/AndroidUtilManager.h"
#endif
#include "GameDataManager.h"
#include "PokerResourceHelper.h"
#include "W_FaceFriendInviteRewardReq.pb.h"
#include "W_FaceFriendInviteRewardRes.pb.h"

#define REWARD_GRADE 5

LobbyFriendInvitePanel::LobbyFriendInvitePanel()
{
	initPanel();
}

LobbyFriendInvitePanel::~LobbyFriendInvitePanel()
{
}

CCSize LobbyFriendInvitePanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* LobbyFriendInvitePanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CCTableViewCell *cell = table->dequeueCell();

	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		FriendCellMiddle* pPanel = new FriendCellMiddle(FriendCellMiddle::FACEBOOK_REQUEST_TYPE);
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);
		pPanel->setFriendInfo(idx);
		pPanel->setPosition(ccp(pPanel->getContentSize().width / 2.f, pPanel->getContentSize().height / 2.f));
		//pPanel->setListener(this);
		mFriends.push_back(pPanel);
	}
	else {
		FriendCellMiddle* pPanel = dynamic_cast<FriendCellMiddle*>(cell->getChildByTag(1));
		if (pPanel) {
			pPanel->setFriendInfo(idx);
		}
	}

	return cell;
}

ssize_t LobbyFriendInvitePanel::numberOfCellsInTableView(CCTableView *table)
{
	return GameDataManager::getSingletonPtr()->m_SnsDataList.size();
}

void LobbyFriendInvitePanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	FriendCellMiddle* pPanel = dynamic_cast<FriendCellMiddle*>(cell->getChildByTag(1));
	if (pPanel){
		pPanel->cellTouch(table->getTouchPoint());
	}
}

void LobbyFriendInvitePanel::initPanel()
{

	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_friend3_2.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	mMainPanel->setButtonListener(this);
	this->setContentSize(mContentSize);

	drawTableView();

	mTitleLabel = mMainPanel->getLabel("txt_invite_info1");
	mDesc_1 = mMainPanel->getLabel("txt_invite_info1");
	mDesc_2 = mMainPanel->getLabel("txt_invite_info2");
	mTitleLabel->setString(GameStringDepot::getSingleton().getString("LobbyFriendInvitePanel_TITLE").c_str());
	mDesc_1->setString(GameStringDepot::getSingleton().getString("LobbyFriendInvitePanel_DESC1").c_str());
	mDesc_2->setString(GameStringDepot::getSingleton().getString("LobbyFriendInvitePanel_DESC2").c_str());


	initFaceBookLoginBtn();
	initFaceBookRewardData();
	initRewardGaugeBar();	

	refreshRewardButton();
}

void LobbyFriendInvitePanel::drawTableView()
{
	CCRect tableViewRect = mMainPanel->getDummyUI("dmy_scrollsize");
	mTableView = Nx::TableView::create(this, tableViewRect.size);
	mMainPanel->addChild(mTableView);
	mTableView->setDirection(ScrollView::Direction::VERTICAL);
	mTableView->setVerticalFillOrder(Nx::TableView::VerticalFillOrder::TOP_DOWN);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setDelegate(this);
	mTableView->reloadData();
	mTableView->setBounceable(false);
}

void LobbyFriendInvitePanel::onClicked(const string& buttonName)
{
	if (buttonName.find("dmy_button_ssmall") != string::npos){
		int idx = nxExtractInt(buttonName, "dmy_button_ssmall");
		sendFaceFriendGiftSendReq(idx);
	}
	else if (buttonName == getButtonName(mFaceBookInviteBtn)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
		AndroidUtilManager::getSingletonPtr()->OpenShare();
#endif
	}
	else if (buttonName == "BTN_AUTO_GET_GIFT")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		vector<int64> _uidList;
		for (W_FriendInfo* _info : GameDataManager::getSingletonPtr()->m_SnsDataList)
		{
			if (_info->has_isgiftreceive() && _info->has_uid())
			{
				if (_info->isgiftreceive())
					_uidList.push_back(_info->uid());
			}
		}
		if (_uidList.size() > 0)
			WebService::getSingletonPtr()->_sendFaceFriendGiftReceiveReq(_uidList);
	}
	else if (buttonName == "BTN_AUTO_SEND_GIFT")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		vector<int64> _uidList;
		for (W_FriendInfo* _info : GameDataManager::getSingletonPtr()->m_SnsDataList)
		{
			if (_info->has_isgiftsend() && _info->has_uid())
			{
				if (_info->isgiftsend())
					_uidList.push_back(_info->uid());
			}
		}
		if (_uidList.size() > 0) 
			WebService::getSingletonPtr()->_sendFaceFriendGiftSendReq(_uidList);
	}
}

void LobbyFriendInvitePanel::setActivate(bool activate)
{
	setVisible(activate);
	float posX = getPositionX();
	if (activate) {
		if (posX < 0) {
			posX += DESIGN_WIDTH;
			setPositionX(posX);			
		}
	}
	else {
		if (posX > 0) {
			posX -= DESIGN_WIDTH;
			setPositionX(posX);			
		}
	}
}

void LobbyFriendInvitePanel::initFaceBookRewardData()
{
	mMaxFriendCount = 0;
	//몇 명
	int rewardSize = GameDataManager::getSingleton().GetGameDataPtr()->facefriendinvitedata_size();
	for (int i = 0; i < rewardSize; i++)
	{
		W_FaceFriendInviteData inviteData = GameDataManager::getSingleton().GetGameDataPtr()->facefriendinvitedata(i);
		string invitecountLabel = "txt_number" + StringConverter::toString(i + 1);
		if (mMainPanel->hasElement(invitecountLabel)) {
			string countStr = NxGetFormatString(GameStringDepot::getSingleton().getString("FRIEND_DESC"), inviteData.invitecount());
			mMainPanel->getLabel(invitecountLabel)->setString(countStr.c_str());
		}

		W_RewardInfo rewardInfo = inviteData.rewardinfo();
		//아이콘
		string rewardIconStr = "skel_reward" + StringConverter::toString(i + 1);
		if (mMainPanel->hasElement(rewardIconStr)) {
			//string rewardIcon = PokerResourceHelper::getRewardIconStr(rewardInfo.rewardset(0));
			//mMainPanel->getSkel(rewardIconStr)->playAnimation(rewardIcon);
		}

		string rewardNameDummyStr = "txt_giftinfo_" + StringConverter::toString(i + 1);
		if (mMainPanel->hasElement(rewardNameDummyStr)) {
			string rewardNameStr = PokerResourceHelper::getRewardString(rewardInfo.rewardset(0));
			mMainPanel->getLabel(rewardNameDummyStr)->setString(rewardNameStr.c_str());
		}

		string rewardButtonStr = "dmy_button_ssmall" + StringConverter::toString(i + 1);
		CCPoint _btnPos = mMainPanel->getDummy(rewardButtonStr).origin;
		SmallButtonPanel* rewardBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SSMALL);
		mMainPanel->addChild(rewardBtn);
		rewardBtn->release();
		rewardBtn->SetButtonListener(this);
		rewardBtn->setPositionX(_btnPos.x);
		rewardBtn->setPositionY(-_btnPos.y);
		rewardBtn->m_Button->setName(rewardButtonStr);
		rewardBtn->SetBtnText(GameStringDepot::getSingleton().getString("LobbyFriendInvitePanel_COMPLATE"));
		rewardBtn->m_Button->setSkelAnimation("button_ssmall_o");
		mRewardBtns.push_back(rewardBtn);

		string completeStr = "skel_clear" + StringConverter::toString(i + 1);
		mMainPanel->getSkel(completeStr)->playAnimation("clear_stay");
		mMainPanel->reorderChild(mMainPanel->getSkel(completeStr), 2);

		if (mMaxFriendCount < inviteData.invitecount())
			mMaxFriendCount = inviteData.invitecount();

		if (getInvitedFriendListCount() < inviteData.invitecount()) {
			rewardBtn->m_Button->setEnable(false);
			rewardBtn->m_Button->setSkelAnimation("button_ssmall_off");
			//미달성
			mMainPanel->getSkel(completeStr)->setVisible(false);
			rewardBtn->SetBtnText(GameStringDepot::getSingleton().getString("LobbyFriendInvitePanel_NOT_COMPLATE"));
		}
	}	
}

void LobbyFriendInvitePanel::initRewardGaugeBar()
{
	mGaugeBar = mMainPanel->getImage("skel_gauge");
	mGaugeBar->setAnchorPoint(ccp(0.f, 0.f));
	mGaugeBar->setPositionY(mGaugeBar->getPositionY() - mMainPanel->getDummy("skel_gauge").size.height / 2.0f);
	float ratioFriend = ((float)1 / (float)40) * getInvitedFriendListCount();
	mGaugeBar->setScaleY(ratioFriend);

	mFriendCount = mMainPanel->getLabel("txt_friendmeter");
	mFriendCount->setString(StringConverter::toString(getInvitedFriendListCount()).c_str());
	mFriendCountBg = mMainPanel->getImage("skel_meter");

	//라벨과 bg 를 percent 비율에 따라서 구한다.
	float addHeight = ratioFriend * mMainPanel->getDummy("skel_gauge").size.height;

	mCountPos = mFriendCount->getPositionY();
	mCountBgPos = mFriendCountBg->getPositionY();
	mFriendCount->setPositionY(mCountPos + addHeight);
	mFriendCountBg->setPositionY(mCountBgPos + addHeight);
}

void LobbyFriendInvitePanel::initRewardButton()
{
	
}

int LobbyFriendInvitePanel::getInvitedFriendListCount()
{
	return GameDataManager::getSingletonPtr()->m_SnsDataList.size();
}

void LobbyFriendInvitePanel::sendFaceFriendGiftSendReq(int idx)
{
	W_FaceFriendInviteRewardReq req;
	req.set_id(idx);
	HttpMessage msg(req, HttpResponseHandler(LobbyFriendInvitePanel::recvFaceFriendGiftSendRes), this);
	HttpManager::getSingleton().send(msg);
}

void LobbyFriendInvitePanel::recvFaceFriendGiftSendRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_FaceFriendInviteRewardRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success() == false)
	{
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
		return;
	}

	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());

	if (res.has_friendofinfo())
	{ 
		GameDataManager::getSingletonPtr()->RemoveSnsDataList();
		GameDataManager::getSingletonPtr()->RemoveFriendDataList();
		W_FriendOfInfo _friendOfInfo = res.friendofinfo();

		int _size = _friendOfInfo.facefriendinfo_size();

		GameDataManager::getSingletonPtr()->m_SnsDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.facefriendinfo(_i));
			GameDataManager::getSingletonPtr()->m_SnsDataList.push_back(_info);
		}

		_size = _friendOfInfo.friendinfo_size();
		GameDataManager::getSingletonPtr()->m_FriendDataList.reserve(_size);
		for (int _i = 0; _i < _size; _i++)
		{
			W_FriendInfo* _info = new W_FriendInfo(_friendOfInfo.friendinfo(_i));
			GameDataManager::getSingletonPtr()->m_FriendDataList.push_back(_info);
		}

		//facebook 리스트 정보
		GameDataManager::getSingletonPtr()->mRewardIds.clear();
		_size = _friendOfInfo.facefriendinviterewardlist_size();
		for (int _i = 0; _i < _size; _i++)
		{
			GameDataManager::getSingletonPtr()->mRewardIds.push_back(_friendOfInfo.facefriendinviterewardlist(_i));
		}		
	}

	string msgText = GameStringDepot::getSingleton().getString("BuySucessPanel_CHARACTER_ITEMDESC");
	LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText), DYNAMIC_PUSH_LAYER);

	GameDataManager::getSingletonPtr()->OnWebserviceMassage(WCSProtocol::W_S2C_ADD_FRIEND_LIST_RES);	// 그냥 갱신하자.
}

void LobbyFriendInvitePanel::initFaceBookLoginBtn()
{
	
	mFaceBookInviteBtn = mMainPanel->getButton("sbtn_button_b");
	mFacebookInviteLabel = mMainPanel->getLabel("txt_button");
	mFacebookInviteUnderLabel = mMainPanel->getLabel("txt_button_under"); 
	mFacebookInviteLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyFriendInvitePanel_INVITE").c_str());
	mFacebookInviteUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyFriendInvitePanel_INVITE").c_str());

	if (GameDataManager::getSingletonPtr()->m_FacebookUserId == "") {
		CCPoint _panelPos;

		mFaceBookInviteBtn->setEnable(true);
		mFaceBookInviteBtn->setSkelAnimation("button_b");
		mFacebookInviteLabel->setColor(StringConverter::parseColor3B("B6B6B6"));
		mFacebookInviteUnderLabel->setColor(StringConverter::parseColor3B("212121"));
		mFacebookInviteUnderLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("212121"));
	}		
	else {
		mFacebookInviteLabel->setColor(StringConverter::parseColor3B("FFFFFF"));
		mFacebookInviteUnderLabel->setColor(StringConverter::parseColor3B("03244E"));
		mFacebookInviteUnderLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("03244E"));
	}
}

void LobbyFriendInvitePanel::SetFriendlList()
{
	refreshRewardButton();
	CCLog("SetFriendlList 1");
	float ratioFriend = ((float)1 / (float)40) * getInvitedFriendListCount();
	mGaugeBar->setScaleY(ratioFriend);
	mFriendCount->setString(StringConverter::toString(getInvitedFriendListCount()).c_str());
	//라벨과 bg 를 percent 비율에 따라서 구한다.
	float addHeight = ratioFriend * mMainPanel->getDummy("skel_gauge").size.height;
	mFriendCount->setPositionY(mCountPos + addHeight);
	mFriendCountBg->setPositionY(mCountBgPos + addHeight);
	CCLog("SetFriendlList 2");


	//TODO : 보상을 받을 경우 저장하는 곳이 없다.
// 	int rewardSize = GameDataManager::getSingleton().GetGameDataPtr()->facefriendinvitedata_size();
// 	for (int i = 0; i < rewardSize; i++)
// 	{
// 		W_FaceFriendInviteData inviteData = GameDataManager::getSingleton().GetGameDataPtr()->facefriendinvitedata(i);
// 		mRewardBtns.push_back(rewardBtn->m_Button);
// 		if (getInvitedFriendListCount() < inviteData.invitecount()) {
// 			rewardBtn->m_Button->setEnable(false);
// 			rewardBtn->m_Button->setGrayscale(true);
// 		}
// 	}
}

bool LobbyFriendInvitePanel::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK>(&stCmd))
	{
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK res = *pstIt;
		if (res.param != DOWNLOAD_FILE_TYPE::SNS_FRIEND_PHOTO)
			return false;

		if (!res.imagePath.empty())
		{
			int _index = res.dParam;

			if (res.param == SNS_FRIEND_PHOTO)
			{
				for (int i = 0; i < mFriends.size(); i++)
				{
					mFriends[i]->InitFriendPhoto(_index, false);
				}

			}
		}
		return true;
	}
	return false;
}

void LobbyFriendInvitePanel::refreshTableView()
{
	CCLog("refreshTableView 1");
	setTableViewReload(mTableView);	
	CCLog("refreshTableView 2");
}

void LobbyFriendInvitePanel::refreshRewardButton()
{
	CCLog("refreshRewardButton");
	int rewardSize = GameDataManager::getSingleton().GetGameDataPtr()->facefriendinvitedata_size();
	for (int i = 0; i < rewardSize; i++)
	{
		int dataId = GameDataManager::getSingleton().GetGameDataPtr()->facefriendinvitedata(i).id();
		string completeStr = "skel_clear" + StringConverter::toString(i + 1);
		if (mRewardBtns[i]->m_Button->isEnabled()) {
			if (!isPossibleReward(dataId)) {
				mRewardBtns[i]->m_Button->setEnable(false);
				mRewardBtns[i]->m_Button->setSkelAnimation("button_ssmall_off");
				mRewardBtns[i]->m_Button->setVisible(false);
				mRewardBtns[i]->SetBtnText(GameStringDepot::getSingleton().getString("LobbyFriendInvitePanel_COMPLATE"));
				if (!mMainPanel->getSkel(completeStr)->isVisible()) {
					mMainPanel->getSkel(completeStr)->setVisible(true);
					mMainPanel->getSkel(completeStr)->playAnimation("clear_start");
					mMainPanel->getSkel(completeStr)->appendAnimation("clear_stay");
				}
			}
			else {
				mMainPanel->getSkel(completeStr)->setVisible(false);
			}
		}
		else {
			if (isPossibleReward(dataId)) {
				if (getInvitedFriendListCount() < GameDataManager::getSingleton().GetGameDataPtr()->facefriendinvitedata(i).invitecount()) {			
					mRewardBtns[i]->m_Button->setEnable(false);
					mRewardBtns[i]->m_Button->setSkelAnimation("button_ssmall_off");
				}				
			}		
		}
	}
}

bool LobbyFriendInvitePanel::isPossibleReward(int id)
{
	int size = GameDataManager::getSingleton().mRewardIds.size();
	CCLog("size = %d", size);
	for (int i = 0; i < size; i++)
	{
		CCLog("GameDataManager::getSingleton().mRewardIds[i] = %d", GameDataManager::getSingleton().mRewardIds[i]);
		if (GameDataManager::getSingleton().mRewardIds[i] == id)
			return false;
	}

	return true;
}

void LobbyFriendInvitePanel::facebookRefresh()
{
	CCLog("log4");
	//invite 버튼 만들고	
	mFaceBookInviteBtn->setEnable(true);
	mFaceBookInviteBtn->setSkelAnimation("button_b");
	mFacebookInviteLabel->setColor(StringConverter::parseColor3B("FFFFFF"));
	mFacebookInviteUnderLabel->setColor(StringConverter::parseColor3B("03244E"));
	mFacebookInviteUnderLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("03244E"));
	//
}

