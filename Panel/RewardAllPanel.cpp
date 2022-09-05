#include "pch.h"
#include "RewardAllPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "FriendHelper.h"
#include "PokerShopHelper.h"
#include "PokerResourceHelper.h"
#include "RewardWidget.h"
#include "LobbyScene.h"

RewardAllPanel::RewardAllPanel()
{
	initPanel();
	SoundManager::getSingleton().playEffect("result_star");
}

RewardAllPanel::~RewardAllPanel()
{

}

void RewardAllPanel::initPanel()
{
	addMouseBlockPanel(this , true);	//ok 처리
	construct(getMxmlPath() + "dmy_get_board_all.mxml");	
	mTitle = getLabel("txt_title");
	mTitleUnder = getLabel("txt_title_under");
	mDesc = getLabel("txt_check1");		
	mItemDesc = getLabel("txt_check2");
	mCellSize = getDummy("dmy_postbox1").size;
	getSkel("skel_backlight")->playAnimation("light_get");
	mTitle->setString(GameStringDepot::getSingleton().getString("REWARD_ALL_TITLE").c_str());
	mTitleUnder->setString(GameStringDepot::getSingleton().getString("REWARD_ALL_TITLE").c_str());
	mItemDesc->setString(GameStringDepot::getSingleton().getString("REWARD_ALL_DESC").c_str());
	mDesc->setString(GameStringDepot::getSingleton().getString("REWARD_ALL_ITEM_DESC").c_str());	
	{
		mCancelBtn = new SmallBtnPanel(this, "cancel");
		addChild(mCancelBtn);
		mCancelBtn->release();
		CCPoint pos = getDummy("dmy_button_small1").origin;
		pos.y = -pos.y;
		mCancelBtn->setPosition(pos);
		mCancelBtn->setButtonLabel(GameStringDepot::getSingleton().getString("TXT_OK_LABEL")); 
		mCancelBtn->setButtonSkelAni("button_small_o");
	}	
}

void RewardAllPanel::onClicked(const string& name)
{
	if (name == "buy") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);		
	}
	else if (name == "cancel") {
		//topu ui refresh
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_pScene)
			_pScene->ApplyUserData();
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
}

cocos2d::CCSize RewardAllPanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* RewardAllPanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CCTableViewCell* cell = table->dequeueCell();

	if (!cell){
		cell = new CCTableViewCell();	
		cell->autorelease();
		RewardWidget* pPanel = new RewardWidget();
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);
		CCLOG("height = %f", pPanel->getContentSize().height);
		int gapHeight = (mCellSize.height - pPanel->getContentSize().height ) * 0.5f;
		pPanel->setPosition(ccp(mCellSize.width / 2.0f, mCellSize.height / 2.0f));
		pPanel->setRewardSet(mRewardInfo.rewardset(idx));
	}
	else{
		RewardWidget* pPanel = dynamic_cast<RewardWidget*>(cell->getChildByTag(1));
		if (pPanel)
			pPanel->setRewardSet(mRewardInfo.rewardset(idx));

	}

	return cell;
}

ssize_t RewardAllPanel::numberOfCellsInTableView(CCTableView *table)
{
	return mRewardInfo.rewardset_size();
}

void RewardAllPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{

}

void RewardAllPanel::drawTableView()
{
	CCRect tableViewRect = getDummyUI("dmy_sell_scrollsize");
	mTableView = Nx::TableView::create(this, tableViewRect.size);
	addChild(mTableView);
	mTableView->setDirection(ScrollView::Direction::HORIZONTAL);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setDelegate(this);
	mTableView->reloadData();
	mTableView->setBounceable(true);
}

void RewardAllPanel::setRewardInfo(W_RewardInfo rewardInfo)
{
	mRewardInfo.CopyFrom(rewardInfo);
	if (mRewardInfo.rewardset_size() > 5) {
		drawTableView();
	}
	else {
		drawEachReward();
	}
}

void RewardAllPanel::setTitle(string title)
{
	mTitle->setString(title.c_str());
	mTitleUnder->setString(title.c_str());
}

void RewardAllPanel::setDesc(string desc)
{
	mDesc->setString(desc.c_str());
}

void RewardAllPanel::setItemDesc(string itemDesc)
{
	mItemDesc->setString(itemDesc.c_str());
}

void RewardAllPanel::drawEachReward()
{
	int size = mRewardInfo.rewardset_size();
	vector<int> dmyIdx;
	if (size == 1) {
		dmyIdx.push_back(3);
	}
	else if (size == 2) {
		dmyIdx.push_back(7);
		dmyIdx.push_back(8);
	}
	else if (size == 3) {
		dmyIdx.push_back(2);
		dmyIdx.push_back(3);
		dmyIdx.push_back(4);
	}
	else if (size == 4) {
		dmyIdx.push_back(6);
		dmyIdx.push_back(7);
		dmyIdx.push_back(8);
		dmyIdx.push_back(9);
	}
	else if (size == 5) {
		dmyIdx.push_back(1);
		dmyIdx.push_back(2);
		dmyIdx.push_back(3);
		dmyIdx.push_back(4);
		dmyIdx.push_back(5);
	}	

	for (int i = 0; i < dmyIdx.size(); i++)
	{
		drawReward(i, dmyIdx[i]);
	}
}

void RewardAllPanel::drawReward(int idx, int posIdx)
{
	string dmyStr = "dmy_postbox" + StringConverter::toString(posIdx);
	RewardWidget* pPanel = new RewardWidget();
	addChild(pPanel);
	pPanel->release();
	pPanel->setTag(1);	
	pPanel->setPosition(getImage(dmyStr)->getPosition());
	pPanel->setRewardSet(mRewardInfo.rewardset(idx));
}
