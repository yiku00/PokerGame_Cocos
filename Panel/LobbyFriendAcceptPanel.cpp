#include "pch.h"
#include "LobbyFriendAcceptPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"

LobbyFriendAcceptPanel::LobbyFriendAcceptPanel()
{
	initPanel();
}

LobbyFriendAcceptPanel::~LobbyFriendAcceptPanel()
{
}

CCSize LobbyFriendAcceptPanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* LobbyFriendAcceptPanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CCTableViewCell* cell = table->dequeueCell();

	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		FriendCellMiddle* pPanel = new FriendCellMiddle(FriendCellMiddle::FRIEND_REQUEST_TYPE);
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

ssize_t LobbyFriendAcceptPanel::numberOfCellsInTableView(CCTableView *table)
{
	return GameDataManager::getSingletonPtr()->m_RequestDataList.size();
}

void LobbyFriendAcceptPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	FriendCellMiddle* pPanel = dynamic_cast<FriendCellMiddle*>(cell->getChildByTag(1));
	if (pPanel){
		pPanel->cellTouch(table->getTouchPoint());
	}
}

void LobbyFriendAcceptPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_friend_request1.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);
	mCellSize = mMainPanel->getDummy("dmy_f_barmiddle2").size;

	mMainPanel->getLabel("txt_empty1")->setVisible(false);
	mMainPanel->getLabel("txt_empty1")->setString(GameStringDepot::getSingleton().getString("NO_INVITEFRIEND_DESC").c_str());

	mMainPanel->getLabel("txt_friendrecommend")->setString("");
	mMainPanel->getLabel("txt_friendrecommend_now")->setString("");
	mMainPanel->getLabel("txt_friendrecommend_max")->setString("");

	mTitleLabel = mMainPanel->getLabel("txt_title1");
	mTitleUnderLabel = mMainPanel->getLabel("txt_title1_under");
	mTitleLabel->setString(GameStringDepot::getSingleton().getString("LobbyFriendAcceptPanel_TITLE").c_str());
	mTitleUnderLabel->setString(GameStringDepot::getSingleton().getString("LobbyFriendAcceptPanel_TITLE").c_str());

	for (int _i = 0; _i < 2; _i++)
	{
		CCPoint _btnPos = mMainPanel->getDummy("dmy_button_small" + StringConverter::toString(_i + 1)).origin;

		m_smallButton[_i] = new SmallButtonPanel(SmallButtonPanel::LOBBY_FRIEND_TYPE);
		m_smallButton[_i]->setPositionX(_btnPos.x);
		m_smallButton[_i]->setPositionY(-_btnPos.y);
		mMainPanel->addChild(m_smallButton[_i]);
		m_smallButton[_i]->release();
		m_smallButton[_i]->SetButtonListener(this);
	}

	m_smallButton[0]->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_ALL_DISAGREE"));
	m_smallButton[1]->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_ALL_AGREE"));
	m_smallButton[0]->m_Button->setName("BTN_ALL_DISAGREE");
	m_smallButton[1]->m_Button->setName("BTN_ALL_AGREE");
	
	drawTableView();
}

void LobbyFriendAcceptPanel::drawTableView()
{
	CCRect tableViewRect = mMainPanel->getDummyUI("dmy_scrollsize1");
	mTableView = Nx::TableView::create(this, tableViewRect.size);
	mMainPanel->addChild(mTableView);
	mTableView->setDirection(ScrollView::Direction::VERTICAL);
	mTableView->setVerticalFillOrder(Nx::TableView::VerticalFillOrder::TOP_DOWN);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setDelegate(this);
	mTableView->reloadData();
	mTableView->setBounceable(false);
}

void LobbyFriendAcceptPanel::onClicked(const string& buttonName)
{
	//친구 요청창
	if (buttonName == "BTN_ALL_DISAGREE")
	{
		CCLog("LobbyFriendAcceptPanel::onClicke BTN_ALL_DISAGREE");
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//모두 거절
		vector<int64> _uidList;
		for (W_FriendInfo* _info : GameDataManager::getSingletonPtr()->m_RequestDataList)
		{
			if (!_info->has_status() && !_info->has_uid())
				continue;

			if (_info->status() == W_FriendInfo_eFriendStatus_eWait)
			{
				int64 _uid = _info->uid();
				_uidList.push_back(_uid);
			}
		}
		if (_uidList.size() > 0)
		{
			WebService::getSingletonPtr()->_sendFriendRejectReq(_uidList);
		}
	}
	else if (buttonName == "BTN_ALL_AGREE")
	{
		CCLog("LobbyFriendAcceptPanel::onClicke BTN_ALL_AGREE");
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//모두 수락
		vector<int64> _uidList;
		for (W_FriendInfo* _info : GameDataManager::getSingletonPtr()->m_RequestDataList)
		{
			if (!_info->has_status() && !_info->has_uid())
				continue;

			CCLog("LobbyFriendAcceptPanel::onClicke _info->status() = %d", _info->status());

			if (_info->status() == W_FriendInfo_eFriendStatus_eWait)
			{
				int64 _uid = _info->uid();
				_uidList.push_back(_uid);
			}
		}

		CCLog("LobbyFriendAcceptPanel::onClicke _uidList = %d", _uidList.size());
		if (_uidList.size() > 0)
		{
			WebService::getSingletonPtr()->_sendFriendAddReq(_uidList);
		}

	}

}

void LobbyFriendAcceptPanel::refreshTableView()
{
	setTableViewReload(mTableView);
	mMainPanel->getLabel("txt_empty1")->setVisible(GameDataManager::getSingletonPtr()->m_RequestDataList.size() == 0);
}

void LobbyFriendAcceptPanel::refreshPhoto(int index)
{
	for (int i = 0; i < mFriends.size(); i++)
	{
		mFriends[i]->InitFriendPhoto(index, false);
	}
}

void LobbyFriendAcceptPanel::onLayerMessage(const string& msg)
{

}

void LobbyFriendAcceptPanel::cellTouch(const CCPoint& touchPoint)
{
	const PanelNodeContainer& panelNodes = mMainPanel->getNodes();
	for (auto it = panelNodes.begin(); it != panelNodes.end(); ++it)
	{
		Button* btn = dynamic_cast<Button*>(it->second);
		if (btn) {
			if (btn->hasCollided(btn->convertToNodeSpace(touchPoint))){
				if (btn->isEnabled()){
					onClicked(btn->getName());
					CCDelayTime* delay = CCDelayTime::create(CELL_TOUCH_TIME * 2);
					CCActionInstant* func = CCCallFuncN::create(this, callfuncN_selector(LobbyFriendAcceptPanel::_cellTouchEnd));
					btn->runAction(CCSequence::create(delay, func, nullptr));
					return;
				}
			}
		}
	}
}

void LobbyFriendAcceptPanel::_cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}
