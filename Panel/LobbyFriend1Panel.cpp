#include "pch.h"
#include "LobbyFriend1Panel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "SimplePopupPanel.h"
#include "Web/WebService.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"
#include "LobbyTopUiPanel.h"
#include "LobbyUIPanel.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/FacebookManager.h"
#endif
#include "FriendHelper.h"
#include "PokerResourceHelper.h"


LobbyFriend1Panel::LobbyFriend1Panel()
{
	InitPanel();
	InitImage();
	initButton();	
	setButtonListener(this);		
}

LobbyFriend1Panel::~LobbyFriend1Panel()
{

}

void LobbyFriend1Panel::InitPanel()
{
	construct(getMxmlPath() + "dmy_friend1.mxml");

	mMaxFriendLabel = getLabel("txt_friend_total");	
	mNowFriendLabel = getLabel("txt_friend_on");
	mFriendTitleLabel = getLabel("txt_friend_sum");
	mFriendTitleLabel->setString(GameStringDepot::getSingleton().getString("TXT_FRIEND_COMPLETE").c_str());

	mCellSize = getDummy("dmy_f_bar1").size;
	drawTableView();
	refreshFriendState();
}

void LobbyFriend1Panel::InitImage()
{
	getLabel("txt_empty")->setString(GameStringDepot::getSingleton().getString("NO_GAMEFRIEND_DESC").c_str());
	getLabel("txt_friend")->setString(GameStringDepot::getSingleton().getString("LobbyFriend1Panel_FRIEND_TITLE").c_str());
	mCellSize = getDummy("dmy_f_bar1").size;
}

void LobbyFriend1Panel::initButton()
{
	for (int _i = 0; _i < 2; _i++)
	{
		CCPoint _btnPos = getDummy("dmy_button_small" + StringConverter::toString(_i + 2)).origin;
		m_pSmallButton[_i] = new SmallButtonPanel(SmallButtonPanel::LOBBY_FRIEND_TYPE);
		m_pSmallButton[_i]->setPositionX(_btnPos.x);
		m_pSmallButton[_i]->setPositionY(-_btnPos.y);
		m_pSmallButton[_i]->SetButtonListener(this);
		addChild(m_pSmallButton[_i]);
		m_pSmallButton[_i]->release();
	}

	//m_pSmallButton[0]->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_INVITE_FRIENDS"));
	m_pSmallButton[0]->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_AUTO_GIFT_UNIT")); 
	m_pSmallButton[1]->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_AUTO_GET_UNIT"));	

	//m_pSmallButton[0]->m_Button->setName("BTN_INVITE_FRIENDS");
	m_pSmallButton[0]->m_Button->setName("BTN_AUTO_SEND_GIFT"); 
	m_pSmallButton[1]->m_Button->setName("BTN_AUTO_GET_GIFT");
	
}

void LobbyFriend1Panel::ShowEmptyText(bool _visible)
{
	
}


void LobbyFriend1Panel::ShowFriendInfoPanel(int _index)
{
	CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::FRIEND_INFO_TYPE, _index, m_TapIndex + 1);

	if (panel)
	{
		LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
	}
}

void LobbyFriend1Panel::onClicked(const string& name)
{
	if (name == "BTN_INVITE_FRIENDS")
	{
#ifndef USE_FACEBOOK_LOGIN
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		FacebookManager::getSingletonPtr()->RequestInvitableUserList(false);
#endif
#endif
		return;
	}
	else if (name == "BTN_AUTO_GET_GIFT")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		vector<int64> _uidList;
		if (m_TapIndex == 0)
		{
			for (W_FriendInfo* _info : GameDataManager::getSingletonPtr()->m_SnsDataList)
			{
				if (_info->has_isgiftreceive() && _info->has_uid())
				{
					if (_info->isgiftreceive())
						_uidList.push_back(_info->uid());
				}
			}
		}
		else if (m_TapIndex == 1)
		{
			for (W_FriendInfo* _info : GameDataManager::getSingletonPtr()->m_FriendDataList)
			{
				if (_info->has_isgiftreceive() && _info->has_uid())
				{
					if (_info->isgiftreceive())
						_uidList.push_back(_info->uid());
				}
			}
		}
		
		if (_uidList.size() > 0) WebService::getSingletonPtr()->_sendFriendGiftReceiveReq(_uidList);
	}
	else if (name == "BTN_AUTO_SEND_GIFT")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		vector<int64> _uidList;
		if (m_TapIndex == 0)
		{
			for (W_FriendInfo* _info : GameDataManager::getSingletonPtr()->m_SnsDataList)
			{
				if (_info->has_isgiftsend() && _info->has_uid())
				{
					if (_info->isgiftsend())
						_uidList.push_back(_info->uid());
				}
			}
		}
		else if (m_TapIndex == 1)
		{
			for (W_FriendInfo* _info : GameDataManager::getSingletonPtr()->m_FriendDataList)
			{
				if (_info->has_isgiftsend() && _info->has_uid())
				{
					if (_info->isgiftsend())
						_uidList.push_back(_info->uid());
				}
			}
		}
		if (_uidList.size() > 0) WebService::getSingletonPtr()->_sendFriendGiftSendReq(_uidList);
	}	
}

void LobbyFriend1Panel::update(float dt)
{
	
}

bool LobbyFriend1Panel::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK>(&stCmd))
	{
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK res = *pstIt;
		DOWNLOAD_FILE_TYPE _type;

		if (m_TapIndex == 0)
		{
			_type = DOWNLOAD_FILE_TYPE::SNS_FRIEND_PHOTO;
		}
		else if (m_TapIndex == 1)
		{
			_type = DOWNLOAD_FILE_TYPE::FRIEND_PHOTO;
		}
		if (res.param != _type)
			return false;

		if (!res.imagePath.empty())
		{
			int _index = res.dParam;

			if (res.param == _type)
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

void LobbyFriend1Panel::SetFriendlList()
{
	ClearFriendlList();
	m_nSortType = SORT_TYPE_DATE;
	getLabel("txt_empty")->setVisible(false);
	CCSize _contentSize = getDummy("dmy_tab1_scrollsize").size;

	int _size = 0;
	if (m_TapIndex == 0)
		_size = GameDataManager::getSingletonPtr()->m_SnsDataList.size();
	if (m_TapIndex == 1)
		_size = GameDataManager::getSingletonPtr()->m_FriendDataList.size();

	if (_size > 0)
	{
		getLabel("txt_empty")->setVisible(false);
	}
	else
	{
		getLabel("txt_empty")->setVisible(true);
	}	
	refreshTableView();	
}

void LobbyFriend1Panel::ClearFriendlList()
{
	
}

void LobbyFriend1Panel::SetButtonPause(bool _pause)
{
	for (int _i = 0; _i < 2; _i++)
	{
		m_pSmallButton[_i]->m_Button->setPaused(_pause);
	}
}

void LobbyFriend1Panel::SetFriendPanelType(TypeFriendPanel _type)
{
	if (_type == TYPE_SNS_FRIEND)
		m_TapIndex = 0;
	else if (_type == TYPE_GAME_FRIEND)
		m_TapIndex = 1;

}

void LobbyFriend1Panel::drawTableView()
{
	CCRect tableViewRect = getDummyUI("dmy_tab1_scrollsize");
	mTableView = Nx::TableView::create(this, tableViewRect.size);
	addChild(mTableView);
	mTableView->setDirection(ScrollView::Direction::VERTICAL);
	mTableView->setVerticalFillOrder(Nx::TableView::VerticalFillOrder::TOP_DOWN);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setDelegate(this);
	mTableView->reloadData();
	mTableView->setBounceable(false);
}

CCSize LobbyFriend1Panel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* LobbyFriend1Panel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CCTableViewCell* cell = table->dequeueCell();

	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		FriendCell* pPanel = new FriendCell();
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);
		pPanel->setFriendInfo(idx);
		pPanel->setPosition(ccp(pPanel->getContentSize().width / 2.f, pPanel->getContentSize().height / 2.f));
		pPanel->setListener(this);
		mFriends.push_back(pPanel);
	}
	else {
		FriendCell* pPanel = dynamic_cast<FriendCell*>(cell->getChildByTag(1));
		if (pPanel) {
			pPanel->setFriendInfo(idx);			
		}
	}
	return cell;
}

ssize_t LobbyFriend1Panel::numberOfCellsInTableView(CCTableView *table)
{
	return GameDataManager::getSingletonPtr()->m_FriendDataList.size();
}

void LobbyFriend1Panel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	FriendCell* pPanel = dynamic_cast<FriendCell*>(cell->getChildByTag(1));
	if (pPanel){
		pPanel->cellTouch(table->getTouchPoint());
	}
}

void LobbyFriend1Panel::onLayerMessage(const string& msg)
{
	if (msg.find("FRIEND_CONFIRM_REMOVE") != string::npos){
		int idx = nxExtractInt(msg, "FRIEND_CONFIRM_REMOVE");
		W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_FriendDataList[idx];
		string _OkMsg = "FRIEND_REMOVE" + StringConverter::toString(idx);
		string _title = GameStringDepot::getSingleton().getString("POKER_USERINFO_DELETE");
		string _content =NxGetFormatString(GameStringDepot::getSingleton().getString("LobbyFriend1Panel_DESC") , _info->name());
		SimplePopupPanel* pPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::FRIEND_REMOVE, _content, _title);
		pPanel->SetOkEventMsg(_OkMsg);
		pPanel->setListener(this);
		LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);

	}
	else if (msg.find("FRIEND_GIFT") != string::npos){
		int idx = nxExtractInt(msg, "FRIEND_GIFT");
		W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_FriendDataList[idx];
		if (_info->has_isgiftsend() && _info->has_uid())
		{
			if (_info->isgiftsend())
			{
				vector<int64> _uidList;
				_uidList.push_back(_info->uid());
				WebService::getSingletonPtr()->_sendFriendGiftSendReq(_uidList);
			}
		}
	}
	else if (msg.find("FRIEND_GET") != string::npos){
		int idx = nxExtractInt(msg, "FRIEND_GET");
		W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_FriendDataList[idx];
		if (_info->has_isgiftreceive() && _info->has_uid())
		{
			if (_info->isgiftreceive())
			{
				vector<int64> _uidList;
				_uidList.push_back(_info->uid());
				WebService::getSingletonPtr()->_sendFriendGiftReceiveReq(_uidList);
			}
		}
	}
	else if (msg.find("FRIEND_REMOVE") != string::npos){
		int idx = nxExtractInt(msg, "FRIEND_REMOVE");
		W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_FriendDataList[idx];		
		WebService::getSingletonPtr()->_sendFriendRemoveReq(_info->uid());
	}
}

void LobbyFriend1Panel::refreshTableView()
{
	if (mTableView) {
		setTableViewReload(mTableView);
	}

	refreshFriendState();
}

void LobbyFriend1Panel::setActivate(bool activate)
{
	if (activate) {
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

void LobbyFriend1Panel::refreshFriendState()
{
	int _size = GameDataManager::getSingletonPtr()->m_FriendDataList.size();
	int maxSize = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().friend_max_count();
	mNowFriendLabel->setString(StringConverter::toString(_size).c_str());
	string maxStr = "/ " + StringConverter::toString(maxSize);
	mMaxFriendLabel->setString(maxStr.c_str());
}
