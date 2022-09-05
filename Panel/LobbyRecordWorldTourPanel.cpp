#include "pch.h"
#include "LobbyRecordWorldTourPanel.h"

#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "PokerRecordHelper.h"
#include "GameDataManager.h"


LobbyRecordWorldTourPanel::LobbyRecordWorldTourPanel()
{
	_init();
	drawTableView();
	refreshLikeGamePercent();
	refreshHistoryPanel();
	refreshToday();
	refreshTotal();
}

LobbyRecordWorldTourPanel::~LobbyRecordWorldTourPanel()
{

}

void LobbyRecordWorldTourPanel::_init()
{
	mHistroyType = DISPLAY_HISTORY_SEVENPOKER;
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_record_size.mxml");
	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);	
	this->setContentSize(mContentsSize);
	
	mDisplayPanel = new Panel();	
	mDisplayPanel->construct(getMxmlPath() + "dmy_record2.mxml");
	mCellSize = mDisplayPanel->getContentSize();
	mDisplayPanel->setPositionY(mCellSize.height - DESIGN_HEIGHT - mCellSize.height / 2.f);
	mDisplayPanel->setPositionX(-mCellSize.width / 2.f);
	mDisplayPanel->setContentSize(mCellSize);

	mLeftBtn = mDisplayPanel->getButton("sbtn_movearrow_l");
	mLeftBtn->setListener(this);
	mRightBtn = mDisplayPanel->getButton("sbtn_movearrow_r");
	mRightBtn->setListener(this);
	
	mPokerGaugeBar = mDisplayPanel->getImage("skel_gauge1");
	mPokerGaugeBar->setAnchorPoint(ccp(0.f, 0.5f));
	mPokerGaugeBar->setPositionX(mPokerGaugeBar->getPositionX() - mDisplayPanel->getDummy("skel_gauge1").size.width / 2.0f);

	mHighLowGaugeBar = mDisplayPanel->getImage("skel_gauge2");
	mHighLowGaugeBar->setAnchorPoint(ccp(0.f, 0.5f));
	mHighLowGaugeBar->setPositionX(mHighLowGaugeBar->getPositionX() - mDisplayPanel->getDummy("skel_gauge2").size.width / 2.0f);

	mBadukiGaugeBar = mDisplayPanel->getImage("skel_gauge3");
	mBadukiGaugeBar->setAnchorPoint(ccp(0.f, 0.5f));
	mBadukiGaugeBar->setPositionX(mBadukiGaugeBar->getPositionX() - mDisplayPanel->getDummy("skel_gauge3").size.width / 2.0f);

	mHoldemGaugeBar = mDisplayPanel->getImage("skel_gauge4");
	mHoldemGaugeBar->setAnchorPoint(ccp(0.f, 0.5f));
	mHoldemGaugeBar->setPositionX(mHoldemGaugeBar->getPositionX() - mDisplayPanel->getDummy("skel_gauge4").size.width / 2.0f);

	mLikeGameSevenPokerPercentLabel = mDisplayPanel->getLabel("txt_sevenpoker_per");
	mLikeGameHighLowPercentLabel = mDisplayPanel->getLabel("txt_highlow_per");
	mLikeGameBaddugiPercentLabel = mDisplayPanel->getLabel("txt_badugi_per");
	mLikeGameHoldemPercentLabel = mDisplayPanel->getLabel("txt_texas_per");

	mTodayStateLabel = mDisplayPanel->getLabel("txt_today_total");
	mBestGetMoneyLabel = mDisplayPanel->getLabel("txt_today_gold_sum");

	mAccumulateStateLabel = mDisplayPanel->getLabel("txt_accrue_total");
	mAccumulateBestGetMoneyLabel = mDisplayPanel->getLabel("txt_accrue_gold_sum");
	mAccumulateAllinLabel = mDisplayPanel->getLabel("txt_accrue_allin_sum");

	mFavorGameTitle = mDisplayPanel->getLabel("txt_title_favorgame");		//선호게임
	mFavorGameUnderTitle = mDisplayPanel->getLabel("txt_title_favorgame_under");
	mTodayGameTitle = mDisplayPanel->getLabel("txt_title_today");		//오늘전적
	mTodayGameUnderTitle = mDisplayPanel->getLabel("txt_title_today_under");
	mAccurTitle = mDisplayPanel->getLabel("txt_title_accrue");	//누적전적
	mAccurUnderTitle = mDisplayPanel->getLabel("txt_title_accrue_under");
	mHandTitle = mDisplayPanel->getLabel("txt_title_hand");		//족보전적
	mHandUnderTitle = mDisplayPanel->getLabel("txt_title_hand_under");

	mFavorGameTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TAB_1").c_str());
	mFavorGameUnderTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TAB_1").c_str());
	mTodayGameTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TAB_2").c_str());
	mTodayGameUnderTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TAB_2").c_str());
	mAccurTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TAB_3").c_str());
	mAccurUnderTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TAB_3").c_str());
	mHandTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TAB_4").c_str());
	mHandUnderTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TAB_4").c_str());

	mBestGetTitle = mDisplayPanel->getLabel("txt_today_gold");	//최고 획득 머니
	mTodayBestGetTitle = mDisplayPanel->getLabel("txt_accrue_gold");	//최고 획득 머니
	mAllinTitle = mDisplayPanel->getLabel("txt_accrue_allin");	//mAllinTitle	
	mBestGetTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_BEST_MONEY").c_str());
	mTodayBestGetTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_BEST_MONEY").c_str());
	mAllinTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_ALLIN_COUNT").c_str());

	initHistyroPanel();
}

void LobbyRecordWorldTourPanel::onClicked(const string& buttonName)
{
	if (buttonName == getButtonName(mLeftBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int arraymHistroyType = (int)mHistroyType;
		arraymHistroyType--;
		if (arraymHistroyType < 0)
			arraymHistroyType = (int)(DISPLAY_HISTORY_END) - 1;
		mHistroyType = (DISPLAY_HISTORY_TYPE)arraymHistroyType;
		refreshHistoryPanel();
	}
	else if (buttonName == getButtonName(mRightBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int arraymHistroyType = (int)mHistroyType;
		arraymHistroyType++;
		if (arraymHistroyType == (int)(DISPLAY_HISTORY_END))
			arraymHistroyType = (int)(DISPLAY_HISTORY_SEVENPOKER);
		mHistroyType = (DISPLAY_HISTORY_TYPE)arraymHistroyType;
		refreshHistoryPanel();
	}
}

void LobbyRecordWorldTourPanel::setActivate(bool activate)
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

void LobbyRecordWorldTourPanel::drawTableView()
{
	CCRect tableViewRect = mMainPanel->getDummyUI("dmy_record_size");
	mTableView = Nx::TableView::create(this, tableViewRect.size);
	mMainPanel->addChild(mTableView);
	mTableView->setDirection(ScrollView::Direction::VERTICAL);
	mTableView->setVerticalFillOrder(Nx::TableView::VerticalFillOrder::TOP_DOWN);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setDelegate(this);
	mTableView->reloadData();
	mTableView->setBounceable(false);
}

CCSize LobbyRecordWorldTourPanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* LobbyRecordWorldTourPanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CCTableViewCell* cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		cell->addChild(mDisplayPanel);
		int zipHeight = DESIGN_HEIGHT - mContentsSize.height + 15;
		mDisplayPanel->setPosition(ccp(mDisplayPanel->getContentSize().width / 2.f - mCellSize.width * 0.5f, mDisplayPanel->getContentSize().height / 2.f - zipHeight));
		mDisplayPanel->release();
	}
 	return cell;
}

ssize_t LobbyRecordWorldTourPanel::numberOfCellsInTableView(CCTableView *table)
{
	return 1;
}

void LobbyRecordWorldTourPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{

}

void LobbyRecordWorldTourPanel::refreshLikeGamePercent()
{
	// % 에 따라서 게이지바를 정한다.
	int sevenRatio = PokerRecordHelper::getPoker7Ratio();
	int highRatio = PokerRecordHelper::getPokerHighLow();
	int dogRatio = PokerRecordHelper::getPokerBaduki();
	int holdemRatio = PokerRecordHelper::getPokerHoldem();

	int totalAmount = sevenRatio + highRatio + dogRatio + holdemRatio;
	int gapAmount = 100 - totalAmount;
	if (totalAmount == 0)
		gapAmount = 0;


	holdemRatio += gapAmount;

	//일때...
	int sevenDisplayRatio = sevenRatio;
	int hightDisplayRatio = sevenRatio + highRatio;
	int dogDisplayRatio = sevenRatio + highRatio + dogRatio;
	int holdomDisplayRatio = sevenRatio + highRatio + dogRatio + holdemRatio;
	//% 뿌린다.

	string amountStr = "";
	amountStr = StringConverter::toString(sevenRatio) + "%";
	mLikeGameSevenPokerPercentLabel->setString(amountStr.c_str());
	amountStr = StringConverter::toString(highRatio) + "%";
	mLikeGameHighLowPercentLabel->setString(amountStr.c_str());
	amountStr = StringConverter::toString(dogRatio) + "%";
	mLikeGameBaddugiPercentLabel->setString(amountStr.c_str());
	amountStr = StringConverter::toString(holdemRatio) + "%";
	mLikeGameHoldemPercentLabel->setString(amountStr.c_str());

	mPokerGaugeBar->setScaleX(sevenDisplayRatio * 0.01f);
	mHighLowGaugeBar->setScaleX(hightDisplayRatio  * 0.01f);
	mBadukiGaugeBar->setScaleX(dogDisplayRatio  * 0.01f);
	mHoldemGaugeBar->setScaleX(holdomDisplayRatio  * 0.01f);
}

void LobbyRecordWorldTourPanel::initHistyroPanel()
{
	mHistroyType = DISPLAY_HISTORY_SEVENPOKER;
	mSevenPokerHistoryPanel = new HandsHistoryContentPanel(HandsHistoryContentPanel::HISTORY_SEVEN_POKER);
	mDisplayPanel->addChild(mSevenPokerHistoryPanel);
	mSevenPokerHistoryPanel->release();
	mSevenPokerHistoryPanel->setPosition(mDisplayPanel->getImage("dmy_record_sevenpoker")->getPosition());
	mSevenPokerHistoryPanel->setActivate(false);

	mHighLowHistoryPanel = new HandsHistoryContentPanel(HandsHistoryContentPanel::HISTORY_HIGH_LOW);
	mDisplayPanel->addChild(mHighLowHistoryPanel);
	mHighLowHistoryPanel->release();
	mHighLowHistoryPanel->setPosition(mDisplayPanel->getImage("dmy_record_highlow")->getPosition());
	mHighLowHistoryPanel->setActivate(false);

	mBadugiHistoryPanel = new HandsHistoryContentPanel(HandsHistoryContentPanel::HISTORY_BADDUGI);
	mDisplayPanel->addChild(mBadugiHistoryPanel);
	mBadugiHistoryPanel->release();
	mBadugiHistoryPanel->setPosition(mDisplayPanel->getImage("dmy_record_badugi")->getPosition());
	mBadugiHistoryPanel->setActivate(false);

	mHoldemHistoryPanel = new HandsHistoryContentPanel(HandsHistoryContentPanel::HISTORY_HODEM);
	mDisplayPanel->addChild(mHoldemHistoryPanel);
	mHoldemHistoryPanel->release();
	mHoldemHistoryPanel->setPosition(mDisplayPanel->getImage("dmy_record_texas")->getPosition());
	mHoldemHistoryPanel->setActivate(false);


}

void LobbyRecordWorldTourPanel::refreshHistoryPanel()
{
	mSevenPokerHistoryPanel->setActivate(false);
	mHighLowHistoryPanel->setActivate(false);
	mBadugiHistoryPanel->setActivate(false);
	mHoldemHistoryPanel->setActivate(false);

	if (mHistroyType == DISPLAY_HISTORY_SEVENPOKER) {
		mSevenPokerHistoryPanel->setActivate(true);
	}
	else if (mHistroyType == DISPLAY_HISTORY_HIGHTLOW) {
		mHighLowHistoryPanel->setActivate(true);
	}
	else if (mHistroyType == DISPLAY_HISTORY_BADDUGI) {
		mBadugiHistoryPanel->setActivate(true);
	}
	else if (mHistroyType == DISPLAY_HISTORY_HOLDEMR) {
		mHoldemHistoryPanel->setActivate(true);
	}
}

void LobbyRecordWorldTourPanel::refreshToday()
{
	//총 몇 전 몇 패
	int todayWin = PokerRecordHelper::getTodayWin();
	int todayDefeat = PokerRecordHelper::getTodayDefeat();
	int todayRatio = 0;
	if (todayWin > 0 || todayDefeat > 0)
		todayRatio = ((float)todayWin / (float)(todayWin + todayDefeat)) * 100;
	string rankStr = NxGetFormatString(GameStringDepot::getSingleton().getString("BATTLE_STATE"), todayWin + todayDefeat, todayWin, todayDefeat, todayRatio);
	mTodayStateLabel->setString(rankStr.c_str());
	//최고머니
	int64 bestMoney = PokerRecordHelper::getTodayBestMoney();	
	mBestGetMoneyLabel->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(bestMoney)).c_str());
}

void LobbyRecordWorldTourPanel::refreshTotal()
{
	//총 몇 전 몇 패
	//최고머니
	//올인 시킨 횟수
	int totalWin = PokerRecordHelper::getTotalWin();
	int totalDefeat = PokerRecordHelper::getTotalDefeat();
	int totalRatio = 0;
	if (totalWin > 0 || totalDefeat > 0)
		totalRatio = ((float)totalWin / (float)(totalWin + totalDefeat)) * 100;
	//getTotalAllOut();
	string rankStr = NxGetFormatString(GameStringDepot::getSingleton().getString("BATTLE_STATE"), totalWin + totalDefeat, totalWin, totalDefeat, totalRatio);
	mAccumulateStateLabel->setString(rankStr.c_str());
	int64 bestMoney = PokerRecordHelper::getTotalBestMoney();
	mAccumulateBestGetMoneyLabel->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(bestMoney)).c_str());
	string allOutStr = StringConverter::toString(PokerRecordHelper::getTotalAllOut()) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
	mAccumulateAllinLabel->setString(allOutStr.c_str());
}
