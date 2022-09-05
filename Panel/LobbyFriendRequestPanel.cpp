#include "pch.h"
#include "LobbyFriendRequestPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/FacebookManager.h"
#include "android/AndroidUtilManager.h"
#endif

LobbyFriendRequestPanel::LobbyFriendRequestPanel()
{
	initPanel();
}

LobbyFriendRequestPanel::~LobbyFriendRequestPanel()
{
}

CCSize LobbyFriendRequestPanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* LobbyFriendRequestPanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CCTableViewCell* cell = table->dequeueCell();

	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		FriendCellMiddle* pPanel = new FriendCellMiddle(FriendCellMiddle::FRIEND_RECOMMEND_TYPE);
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);
		pPanel->setFriendInfo(idx);
		pPanel->setPosition(ccp(pPanel->getContentSize().width / 2.f, pPanel->getContentSize().height / 2.f));
		pPanel->setListener(this);
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

ssize_t LobbyFriendRequestPanel::numberOfCellsInTableView(CCTableView *table)
{
	return GameDataManager::getSingletonPtr()->m_RecommendDataList.size();
}

void LobbyFriendRequestPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	FriendCellMiddle* pPanel = dynamic_cast<FriendCellMiddle*>(cell->getChildByTag(1));
	if (pPanel){
		pPanel->cellTouch(table->getTouchPoint());
	}
}

void LobbyFriendRequestPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_friend_request2.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);
	mCellSize = mMainPanel->getDummy("dmy_f_barmiddle").size;

	CCPoint _textFieldPos = mMainPanel->getDummy("dmy_intable_search").origin;
	m_TextFieldPanel = new IntableSearchPanel();
	m_TextFieldPanel->setPositionX(_textFieldPos.x);
	m_TextFieldPanel->setPositionY(-_textFieldPos.y);
	m_TextFieldPanel->setZOrder(2);
	mMainPanel->addChild(m_TextFieldPanel);
	m_TextFieldPanel->release();
	m_TextFieldPanel->m_inputTouch->setListener(this);
	m_TextFieldPanel->m_searchBtn->setListener(this);
	m_TextFieldPanel->m_inputTouch->setName("BTN_SEARCH_FRIEND_INPUT");
	m_TextFieldPanel->m_searchBtn->setName("BTN_SEARCH_FRIEND");


	m_pFriendName = m_TextFieldPanel->m_TextField;
	m_pFriendName->setPlaceHolder(GameStringDepot::getSingletonPtr()->getString("TXT_INPUT_NICKNAME").c_str());
	m_pFriendName->setString("");

	mMainPanel->getLabel("txt_empty2")->setVisible(false);
	mMainPanel->getLabel("txt_empty2")->setString(GameStringDepot::getSingleton().getString("NO_RECOMMEND_DESC").c_str());

	mMainPanel->getLabel("txt_friendrequest")->setString("");
	mMainPanel->getLabel("txt_friendrequest_now")->setString("");
	mMainPanel->getLabel("txt_friendrequest_max")->setString("");
	
	for (int _i = 0; _i < 2; _i++)
	{
		CCPoint _btnPos = mMainPanel->getDummy("dmy_button_small" + StringConverter::toString(_i + 3)).origin;
		m_smallButton[_i] = new SmallButtonPanel(SmallButtonPanel::LOBBY_FRIEND_TYPE);
		m_smallButton[_i]->setPositionX(_btnPos.x);
		m_smallButton[_i]->setPositionY(-_btnPos.y);
		mMainPanel->addChild(m_smallButton[_i]);
		m_smallButton[_i]->release();
		m_smallButton[_i]->SetButtonListener(this);
	}
	m_smallButton[0]->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_REFRESH"));
	m_smallButton[1]->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_ALL_APPLY"));	
	m_smallButton[0]->m_Button->setName("BTN_REFRESH");
	m_smallButton[1]->m_Button->setName("BTN_ALL_APPLY");

	mTitleLabel = mMainPanel->getLabel("txt_title2");
	mTitleUnderLabel = mMainPanel->getLabel("txt_title2_under");
	mTitleLabel->setString(GameStringDepot::getSingleton().getString("LobbyFriendRequestPanel_TITLE").c_str());
	mTitleUnderLabel->setString(GameStringDepot::getSingleton().getString("LobbyFriendRequestPanel_TITLE").c_str());
	drawTableView();

}

void LobbyFriendRequestPanel::drawTableView()
{
	CCRect tableViewRect = mMainPanel->getDummyUI("dmy_scrollsize2");
	mTableView = Nx::TableView::create(this, tableViewRect.size);
	mMainPanel->addChild(mTableView);
	mTableView->setDirection(ScrollView::Direction::VERTICAL);
	mTableView->setVerticalFillOrder(Nx::TableView::VerticalFillOrder::TOP_DOWN);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setBounceable(false);
	mTableView->setDelegate(this);
	mTableView->reloadData();
	
}

void LobbyFriendRequestPanel::onClicked(const string& buttonName)
{
	if (buttonName == "BTN_REFRESH")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//새로고침
		//WebService::getSingletonPtr()->_sendFriendReCommendReq();
		WebService::getSingletonPtr()->_sendFriendRequestListReq();
	}
	else if (buttonName == "BTN_ALL_APPLY")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//모두 신청
		vector<int64> _uidList;
		for (W_FriendInfo* _info : GameDataManager::getSingletonPtr()->m_RecommendDataList)
		{
			if (!_info->has_uid())
				continue;
			if (_info->status() == W_FriendInfo_eFriendStatus_eWait)
			{
				int64 _uid = _info->uid();
				_uidList.push_back(_uid);
			}
		}
		if (_uidList.size() > 0)
		{
			WebService::getSingletonPtr()->_sendFriendRequestReq(_uidList);
		}
	}
	else if (buttonName == "BTN_SEARCH_FRIEND_INPUT")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		GameDataManager::getSingletonPtr()->m_bEditTextField = false;
		GameDataManager::getSingletonPtr()->m_onFocusTextFeild = m_pFriendName;
		std::string _fieldText = m_pFriendName->getString();
		AndroidUtilManager::getSingletonPtr()->InitCustomEditTextField();
		AndroidUtilManager::getSingletonPtr()->ShowCustomEditTextField(_fieldText);
#else
		m_pFriendName->attachWithIME();
#endif


	}
	else if (buttonName == "BTN_SEARCH_FRIEND")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		string _friendName = m_pFriendName->getString();
		if (_friendName.length() == 0)
			return;
		WebService::getSingletonPtr()->_sendFriendFindReq(_friendName);
	}
}

void LobbyFriendRequestPanel::refreshTableView()
{
	setTableViewReload(mTableView);
}

void LobbyFriendRequestPanel::refreshPhoto(int index)
{
	for (int i = 0; i < mFriends.size(); i++)
	{
		mFriends[i]->InitFriendPhoto(index, false);
	}
}

void LobbyFriendRequestPanel::onLayerMessage(const string& msg)
{

}
