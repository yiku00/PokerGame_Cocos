#include "pch.h"
#include "LobbyRecordRankPanel.h"

#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "LobbyRecordRankContentPanel.h"
#include "LobbyRankRewardPanel.h"
#include "Web\WebService.h"
#include "PokerRankHelper.h"
#include "GameDataManager.h"


LobbyRecordRankPanel::LobbyRecordRankPanel()
{
	_init();
}

LobbyRecordRankPanel::~LobbyRecordRankPanel()
{

}

void LobbyRecordRankPanel::_init()
{
	mTotalRanks = nullptr;
	mFriendRanks = nullptr;
	mRankType = RECORD_TOTAL_RANK;
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_record1.mxml");
	mContentsSize = mMainPanel->getContentSize(); 
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);

	mMainPanel->getLabel("txt_tab1_empty")->setVisible(false);	

	mCellSize = mMainPanel->getDummy("dmy_r_bar").size;


	CCPoint pos = mMainPanel->getDummy("dmy_rank_tabl").origin;
	pos.y = -pos.y;

	Panel* tapTotalPanel = new Panel();
	mMainPanel->addChild(tapTotalPanel);
	tapTotalPanel->release();
	tapTotalPanel->construct(getMxmlPath() + "dmy_rank_tabl.mxml");
	tapTotalPanel->setPosition(pos);


	pos = mMainPanel->getDummy("dmy_rank_tabr").origin;
	pos.y = -pos.y;
	Panel* tapFriendPanel = new Panel();
	mMainPanel->addChild(tapFriendPanel);
	tapFriendPanel->release();
	tapFriendPanel->construct(getMxmlPath() + "dmy_rank_tabr.mxml");
	tapFriendPanel->setPosition(pos);

	mTabTotalBtnLabel = tapTotalPanel->getLabel("txt_title");
	mTabTotalBtnUnderLabel = tapTotalPanel->getLabel("txt_title_under");
	mTabTotalBtnLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordRankPanel_TOTAL_TITLE").c_str());
	mTabTotalBtnUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordRankPanel_TOTAL_TITLE").c_str());

	mTabTotalBtn = tapTotalPanel->getButton("sbtn_tab");
	mTabTotalBtn->setName("tabTotal");
	mTabTotalBtn->setListener(this);

	mTabFriendBtnLabel = tapFriendPanel->getLabel("txt_title");
	mTabFriendBtnUnderLabel = tapFriendPanel->getLabel("txt_title_under");
	mTabFriendBtnLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordRankPanel_FRIEND_TITLE").c_str());
	mTabFriendBtnUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordRankPanel_FRIEND_TITLE").c_str());

	mTabFriendBtn = tapFriendPanel->getButton("sbtn_tab");
	mTabFriendBtn->setName("tabFriend");
	mTabFriendBtn->setListener(this);
	
	mMyRankLabel = mMainPanel->getLabel("txt_myrank");
	mMyRankLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordRankPanel_MyRank").c_str());

	mMyRankPanel = new LobbyRecordRankContentPanel();
	mMainPanel->addChild(mMyRankPanel);
	mMyRankPanel->release();	
	mMyRankPanel->setPosition(mMainPanel->getImage("dmy_r_bar")->getPosition());		
	mMainPanel->reorderChild(mMainPanel->getImage("skel_goldline"), 1);
	mMainPanel->reorderChild(mMyRankLabel, 3);
	mMyRankPanel->setMyRankType();

	CCPoint _btnPos = mMainPanel->getDummy("dmy_button_small").origin;
	mRewardPanel = new SmallButtonPanel(SmallButtonPanel::LOBBY_FRIEND_TYPE);
	mRewardPanel->setPositionX(_btnPos.x);
	mRewardPanel->setPositionY(-_btnPos.y);
	mRewardPanel->SetButtonListener(this);
	mMainPanel->addChild(mRewardPanel);
	mRewardPanel->release();
	mRewardPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("RECORD_REWARD"));
	mRewardPanel->m_Button->setName("GIFT_INFO");

	drawTableView();
	refresh();
}

void LobbyRecordRankPanel::setActivate(bool activate)
{
	if (activate) {
		setVisible(true);
		if (getPositionX() < 0) {
			setPositionX(getPositionX() + DESIGN_WIDTH);
		}

		if (mRankType == RECORD_TOTAL_RANK) {
			if (mTotalRanks == nullptr) {
				WebService::getSingleton().sendReputeRankReq(RECORD_TOTAL_RANK);
			}

		}
		else if (mRankType == RECORD_FRIEND_RANK) {
			if (mFriendRanks == nullptr) {
				WebService::getSingleton().sendReputeRankReq(RECORD_FRIEND_RANK);
			}
		}		
	}
	else {
		setVisible(false);
		if (getPositionX() > 0) {
			setPositionX(getPositionX() - DESIGN_WIDTH);
		}
	}
}

void LobbyRecordRankPanel::onClicked(const string& buttonName)
{
	if (buttonName == "tabTotal") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (mRankType != RECORD_TOTAL_RANK) {
			mRankType = RECORD_TOTAL_RANK;
			if (mTotalRanks == nullptr) {
				WebService::getSingleton().sendReputeRankReq(RECORD_TOTAL_RANK);
			}			
			refresh();
		}
	}
	else if (buttonName == "tabFriend") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (mRankType != RECORD_FRIEND_RANK) {
			mRankType = RECORD_FRIEND_RANK;
			if (mFriendRanks == nullptr) {
				WebService::getSingleton().sendReputeRankReq(RECORD_FRIEND_RANK);
			}
			refresh();
		}
	}	
	else if (buttonName == "GIFT_INFO") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().pushDynamicLayer(new LobbyRankRewardPanel(), DYNAMIC_PUSH_LAYER);
	}
}

void LobbyRecordRankPanel::drawTableView()
{
	CCRect tableViewRect = mMainPanel->getDummyUI("dmy_tab1_scrollsize");
	mTableView = Nx::TableView::create(this, tableViewRect.size);	
	mTableView->setDirection(ScrollView::Direction::VERTICAL);
	mTableView->setVerticalFillOrder(Nx::TableView::VerticalFillOrder::TOP_DOWN);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setDelegate(this);
	mMainPanel->addChild(mTableView);
	mTableView->reloadData();
	mTableView->setBounceable(false);
}

CCSize LobbyRecordRankPanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* LobbyRecordRankPanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CCTableViewCell* cell = table->dequeueCell();

	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		LobbyRecordRankContentPanel* pPanel = new LobbyRecordRankContentPanel();
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);		
		pPanel->setPosition(ccp(pPanel->getContentSize().width / 2.f, pPanel->getContentSize().height / 2.f));
		if (mRankType == RECORD_TOTAL_RANK)
			pPanel->setReputeRankInfo(mTotalRanks->rankinfo(idx));
		else
			pPanel->setReputeRankInfo(mFriendRanks->rankinfo(idx));
		if (idx %2 == 0)
			pPanel->setType(LobbyRecordRankContentPanel::BG_TYPE_ODD);
		else
			pPanel->setType(LobbyRecordRankContentPanel::BG_TYPE_EVENT);
	}
	else {
		LobbyRecordRankContentPanel* pPanel = dynamic_cast<LobbyRecordRankContentPanel*>(cell->getChildByTag(1));
		if (pPanel) {
			if (mRankType == RECORD_TOTAL_RANK)
				pPanel->setReputeRankInfo(mTotalRanks->rankinfo(idx));
			else
				pPanel->setReputeRankInfo(mFriendRanks->rankinfo(idx));

			if (idx % 2 == 0)
				pPanel->setType(LobbyRecordRankContentPanel::BG_TYPE_ODD);
			else
				pPanel->setType(LobbyRecordRankContentPanel::BG_TYPE_EVENT);
		}

	}
	return cell;

}

ssize_t LobbyRecordRankPanel::numberOfCellsInTableView(CCTableView *table)
{
	if (mRankType == RECORD_TOTAL_RANK) {
		if (mTotalRanks == nullptr)
			return 0;
		else
			return mTotalRanks->rankinfo_size();
	}
	else {
		if (mFriendRanks == nullptr)
			return 0;
		else
			return mFriendRanks->rankinfo_size();
	}
}

void LobbyRecordRankPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{

}

void LobbyRecordRankPanel::refreshTabBtn()
{
	ccColor3B _onColor = ccc3(240, 216, 165);
	ccColor3B _offColor = ccc3(144, 130, 99);	
	if (mRankType == RECORD_TOTAL_RANK) {
		mTabTotalBtn->getButtonSkelObject()->playAnimation("tab_rankl_on");
		mTabFriendBtn->getButtonSkelObject()->playAnimation("tab_rankr_off");
		mTabTotalBtnLabel->setColor(_onColor);
		mTabFriendBtnLabel->setColor(_offColor);
	}
	else if (mRankType == RECORD_FRIEND_RANK) {
		mTabTotalBtn->getButtonSkelObject()->playAnimation("tab_rankl_off");
		mTabFriendBtn->getButtonSkelObject()->playAnimation("tab_rankr_on");
		mTabTotalBtnLabel->setColor(_offColor);
		mTabFriendBtnLabel->setColor(_onColor);
	}	
}

void LobbyRecordRankPanel::refresh()
{
	refreshTabBtn();
	mTableView->reloadData();
	int rank = 0;
	int level = 0;
	int rating = 0;
	int repute = 0;

	mMyRankPanel->initMyPhoto();
	if (mRankType == RECORD_TOTAL_RANK) {
		if (mTotalRanks) {
			rank = mTotalRanks->myinfo().rank();
			level = mTotalRanks->myinfo().level();
			rating = mTotalRanks->myinfo().rating();
			repute = mTotalRanks->myinfo().repute();
			mMyRankPanel->setRank(rank);
			mMyRankPanel->setVipIcon(rating);
			mMyRankPanel->setRepute(repute);
			mMyRankPanel->setUserName(level, GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName);
		}
	}
	else if (mRankType == RECORD_FRIEND_RANK) {
		if (mFriendRanks) {
			rank = mFriendRanks->myinfo().rank();
			level = mFriendRanks->myinfo().level();
			rating = mFriendRanks->myinfo().rating();
			repute = mFriendRanks->myinfo().repute();
			mMyRankPanel->setRank(rank);
			mMyRankPanel->setVipIcon(rating);
			mMyRankPanel->setRepute(repute);
			mMyRankPanel->setUserName(level, GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName);
		}
	}
	
}

void LobbyRecordRankPanel::clearRankData()
{
	if (mTotalRanks)
		mTotalRanks->Clear();
	mTotalRanks = nullptr;

	if (mFriendRanks)
		mFriendRanks->Clear();
	mFriendRanks = nullptr;
}

void LobbyRecordRankPanel::recvTotalReputeRankRes(W_ReputeRankRes res)
{
	if (mTotalRanks) {
		mTotalRanks->CopyFrom(res);
	}
	else {
		mTotalRanks = new W_ReputeRankRes(res);
	}
	refresh();
}

void LobbyRecordRankPanel::recvFriendReputeRankRes(W_ReputeRankRes res)
{
	if (mFriendRanks) {
		mFriendRanks->CopyFrom(res);
	}
	else {
		mFriendRanks = new W_ReputeRankRes(res);
	}
	refresh();
}
