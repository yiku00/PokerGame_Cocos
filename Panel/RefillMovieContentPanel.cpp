#include "pch.h"
#include "RefillMovieContentPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

RefillMovieContentPanel::RefillMovieContentPanel(int index)
{
	mIndex = index;
	mClearPanel = nullptr;
	initPanel();
}

RefillMovieContentPanel::~RefillMovieContentPanel()
{
}

void RefillMovieContentPanel::onClicked(const string& name)
{	
	
}

void RefillMovieContentPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_table_free.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);
	mPeriodLabel = mMainPanel->getLabel("txt_count");
	string titleStr = NxGetFormatString(GameStringDepot::getSingleton().getString("RefillTitle"), mIndex + 1);
	mPeriodLabel->setString(titleStr.c_str());
	mRewardLabel = mMainPanel->getLabel("txt_gold");
	int64 amount = GameDataManager::getSingleton().GetGameDataPtr()->freechargedata(mIndex).rewardset().amount();
	mRewardLabel->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(amount)).c_str());
	mTable = mMainPanel->getSkel("skel_table");
	addClearPanel();
}

void RefillMovieContentPanel::addClearPanel()
{
	if (mClearPanel != nullptr)
		return;

	int nowPlay = GameDataManager::getSingleton().getPlayerInfo().freechargecnt();
	if (mIndex < nowPlay) {
		mClearPanel = new Panel();
		mMainPanel->addChild(mClearPanel);
		mClearPanel->release();
		mClearPanel->construct(getMxmlPath() + "dmy_clear_free.mxml");
		CCPoint pos = mMainPanel->getDummy("dmy_clear_free").origin;
		pos.y = -pos.y;
		mClearPanel->setPosition(pos);
		mClearPanel->getSkel("skel_clear")->playAnimation("clear_loop",true);		
		mTable->playAnimation("table_free_off");
	}	
}

void RefillMovieContentPanel::addReward()
{
	if (mClearPanel == nullptr) {
		mClearPanel = new Panel();
		mMainPanel->addChild(mClearPanel);
		mClearPanel->release();
		mClearPanel->construct(getMxmlPath() + "dmy_clear_free.mxml");
		CCPoint pos = mMainPanel->getDummy("dmy_clear_free").origin;
		pos.y = -pos.y;
		mClearPanel->setPosition(pos);
		mClearPanel->getSkel("skel_clear")->playAnimation("clear_start");
		mClearPanel->getSkel("skel_clear")->appendAnimation("clear_loop", true);
	}

	mTable->playAnimation("table_free_off");
}
