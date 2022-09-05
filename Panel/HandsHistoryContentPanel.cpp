#include "pch.h"
#include "HandsHistoryContentPanel.h"
#include "HeroUtil.h"
#include "PokerRecordHelper.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

HandsHistoryContentPanel::HandsHistoryContentPanel(HISTORY_TYPE type)
{
	mType = type;
	initPanel();
}

HandsHistoryContentPanel::~HandsHistoryContentPanel()
{

}

void HandsHistoryContentPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();

	if (mType == HISTORY_SEVEN_POKER) {		
		mMainPanel->construct(getMxmlPath() + "dmy_record_sevenpoker.mxml");
		mTitleLanbel = mMainPanel->getLabel("txt_title");
		mTitleUnderLanbel = mMainPanel->getLabel("txt_title_under");
		mPoker_RotiflAmountLabel = mMainPanel->getLabel("txt_royalfl_sum");	//로티플
		mPoker_StiflAmountLabel = mMainPanel->getLabel("txt_straightfl_sum");	//스티플
		mPoker_4CardAmountLabel = mMainPanel->getLabel("txt_four_sum");		//포카드
		mPoker_FullHouseAmountLabel = mMainPanel->getLabel("txt_fullhouse_sum");		//플하우스
		mPoker_FlushAmountLabel = mMainPanel->getLabel("txt_flush_sum");		//플러쉬
		mPoker_StraitAmountLabel = mMainPanel->getLabel("txt_straight_sum");		//스트레이트
		mPoker_TripleAmountLabel = mMainPanel->getLabel("txt_three_sum");		//스티플
		mPoker_2PairAmountLabel = mMainPanel->getLabel("txt_two_sum");		//2페어
		mPoker_1PairAmountLabel = mMainPanel->getLabel("txt_one_sum");		//1페어
		mPoker_DieAmountLabel = mMainPanel->getLabel("txt_die_sum");		//다이
		//
		mTitleLanbel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SEVEN_POKER").c_str());
		mTitleUnderLanbel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SEVEN_POKER").c_str());

		mMainPanel->getLabel("txt_royalfl")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ROYAL_SHORT").c_str());
		mMainPanel->getLabel("txt_straightfl")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_STIFUL_SHORT").c_str());
		mMainPanel->getLabel("txt_four")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FOURCARD").c_str());
		mMainPanel->getLabel("txt_fullhouse")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FULLHOUSE").c_str());
		mMainPanel->getLabel("txt_flush")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FLUSH").c_str());
		mMainPanel->getLabel("txt_straight")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_STRAIGHT").c_str());
		mMainPanel->getLabel("txt_three")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_THREEFUL").c_str());
		mMainPanel->getLabel("txt_two")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_TWOFAIR").c_str());
		mMainPanel->getLabel("txt_one")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ONEFAIR").c_str());
		//총 다이 횟수
		mMainPanel->getLabel("txt_die")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TOTAL_DIE").c_str());
	}
	else if (mType == HISTORY_HIGH_LOW) {
		mMainPanel->construct(getMxmlPath() + "dmy_record_highlow.mxml");	
		mTitleLanbel = mMainPanel->getLabel("txt_title");
		mTitleUnderLanbel = mMainPanel->getLabel("txt_title_under");
		mHighTitle = mMainPanel->getLabel("txt_high");	//하이 
		mLowTitle = mMainPanel->getLabel("txt_low");	//로우
		SwingTitle = mMainPanel->getLabel("txt_swing");	//스윙
		mHigh_FullHouseAmountLabel = mMainPanel->getLabel("txt_fullhouse_sum");	//하이 풀하우스
		mHigh_FlushAmountLabel = mMainPanel->getLabel("txt_flush_sum");	//하이 플러쉬
		mHigh_StraitAmountLabel = mMainPanel->getLabel("txt_straight_sum");	//하이 스트레이트
		mHigh_TripleAmountLabel = mMainPanel->getLabel("txt_three_sum");	//하이 트리플
		mHigh_2PairAmountLabel = mMainPanel->getLabel("txt_two_sum");	//하이 2페어
		mHigh_1PairAmountLabel = mMainPanel->getLabel("txt_one_sum");	//하이 1페어이하
		mLow_6TopAmountLabel = mMainPanel->getLabel("txt_6top_sum");	//로우 6탑
		mLow_7TopAmountLabel = mMainPanel->getLabel("txt_7top_sum");	//로우 7탑
		mLow_8TopAmountLabel = mMainPanel->getLabel("txt_8top_sum");	//로우 8탑
		mLow_9TopAmountLabel = mMainPanel->getLabel("txt_9top_sum");	//로우 9탑
		mLow_10TopAmountLabel = mMainPanel->getLabel("txt_10top_sum");	//로우 10탑
		mLow_jTopAmountLabel = mMainPanel->getLabel("txt_jtop_sum");	//로우 j탑이하
		mSwing_RotiflAmountLabel = mMainPanel->getLabel("txt_royalfl_sum");	//스윙 로티플
		mSwing_StiflAmountLabel = mMainPanel->getLabel("txt_straightfl_sum");	//스윙 스티플
		mSwing_4CardAmountLabel = mMainPanel->getLabel("txt_four_sum");	//스윙 포카드		
		mHighLow_totalDieAmountLabel = mMainPanel->getLabel("txt_die_sum");	//총 다이 횟수
		// 하이 , 로우
		mTitleLanbel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HIGHLOW").c_str());
		mTitleUnderLanbel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HIGHLOW").c_str());
		//타이틀
		mHighTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_HIGHLOW_HI").c_str());
		mLowTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_HIGHLOW_LOW").c_str());
		SwingTitle->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_HIGHLOW_SWING").c_str());

		//하이
		mMainPanel->getLabel("txt_fullhouse")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FULLHOUSE").c_str());
		mMainPanel->getLabel("txt_flush")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FLUSH").c_str());
		mMainPanel->getLabel("txt_straight")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_STRAIGHT").c_str());
		mMainPanel->getLabel("txt_three")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_THREEFUL").c_str());
		mMainPanel->getLabel("txt_two")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_TWOFAIR").c_str());
		mMainPanel->getLabel("txt_one")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_HIGHLOW_UNDER_ONEPAIR").c_str());
		//로우
		mMainPanel->getLabel("txt_6top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_6TOP").c_str());
		mMainPanel->getLabel("txt_7top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_7TOP").c_str());
		mMainPanel->getLabel("txt_8top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_8TOP").c_str());
		mMainPanel->getLabel("txt_9top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_9TOP").c_str());
		mMainPanel->getLabel("txt_10top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_10TOP").c_str());
		mMainPanel->getLabel("txt_jtop")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_HIGHLOW_UNDER_JTOP").c_str());
		//스윙
		mMainPanel->getLabel("txt_royalfl")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ROYAL_SHORT").c_str());
		mMainPanel->getLabel("txt_straightfl")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_STIFUL_SHORT").c_str());
		mMainPanel->getLabel("txt_four")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FOURCARD").c_str());
		//총 다이 횟수
		mMainPanel->getLabel("txt_die")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TOTAL_DIE").c_str());

	}
	else if (mType == HISTORY_BADDUGI) {
		mMainPanel->construct(getMxmlPath() + "dmy_record_badugi.mxml");
		mTitleLanbel = mMainPanel->getLabel("txt_title");
		mTitleUnderLanbel = mMainPanel->getLabel("txt_title_under");
		mBadugi_GolfAmountLabel = mMainPanel->getLabel("txt_golf_sum");	//골프
		mBadugi_SecondAmountLabel = mMainPanel->getLabel("txt_second_sum");  	//세컨드
		mBadugi_ThirdAmountLabel = mMainPanel->getLabel("txt_third_sum");	//서드
		mBadugi_5TopAmountLabel = mMainPanel->getLabel("txt_5top_sum");	//5탑
		mBadugi_6TopAmountLabel = mMainPanel->getLabel("txt_6top_sum");	//6탑
		mBadugi_7TopAmountLabel = mMainPanel->getLabel("txt_7top_sum");	//7탑
		mBadugi_8TopAmountLabel = mMainPanel->getLabel("txt_8top_sum");	//8탑
		mBadugi_9TopAmountLabel = mMainPanel->getLabel("txt_9top_sum");	//9탑
		mBadugi_10TopAmountLabel = mMainPanel->getLabel("txt_10top_sum");	//10탑
		mBadugi_JTopAmountLabel = mMainPanel->getLabel("txt_jtop_sum");	//J탑
		mBadugi_QTopAmountLabel = mMainPanel->getLabel("txt_qtop_sum");	//Q탑
		mBadugi_KTopAmountLabel = mMainPanel->getLabel("txt_ktop_sum");	//K탑
		mBadugi_BaseAmountLabel = mMainPanel->getLabel("txt_base_sum");	//베이스
		mBadugi_Under2BaseAmountLabel = mMainPanel->getLabel("txt_twobase_sum");	//투베이스 이하
		mBadugi_TotalDieAmountLabel = mMainPanel->getLabel("txt_die_sum");	//총 다이 횟수
		//
		mTitleLanbel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI").c_str());
		mTitleUnderLanbel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI").c_str());

		mMainPanel->getLabel("txt_golf")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI_GOLF").c_str());
		mMainPanel->getLabel("txt_second")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI_SECOND").c_str());
		mMainPanel->getLabel("txt_third")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI_THIRD").c_str());
		mMainPanel->getLabel("txt_5top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI_5TOP").c_str());
		mMainPanel->getLabel("txt_6top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_6TOP").c_str());
		mMainPanel->getLabel("txt_7top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_7TOP").c_str());
		mMainPanel->getLabel("txt_8top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_8TOP").c_str());
		mMainPanel->getLabel("txt_9top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_9TOP").c_str());
		mMainPanel->getLabel("txt_10top")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_10TOP").c_str());
		mMainPanel->getLabel("txt_jtop")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_JTOP").c_str());
		mMainPanel->getLabel("txt_qtop")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_QTOP").c_str());
		mMainPanel->getLabel("txt_ktop")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_KTOP").c_str());
		mMainPanel->getLabel("txt_base")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI_BASE").c_str());		
		mMainPanel->getLabel("txt_twobase")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_BADUGI_BASE").c_str());
		//총 다이 횟수
		mMainPanel->getLabel("txt_die")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TOTAL_DIE").c_str());
	}
	else if (mType == HISTORY_HODEM) {
		mMainPanel->construct(getMxmlPath() + "dmy_record_texas.mxml");
		mTitleLanbel = mMainPanel->getLabel("txt_title");
		mTitleUnderLanbel = mMainPanel->getLabel("txt_title_under");
		mHodem_RotiflAmountLabel = mMainPanel->getLabel("txt_royalfl_sum");	//로티플
		mHodem_StiflAmountLabel = mMainPanel->getLabel("txt_straightfl_sum");	//스티플
		mHodem_4CardAmountLabel = mMainPanel->getLabel("txt_four_sum");		//포카드
		mHodem_FullHouseAmountLabel = mMainPanel->getLabel("txt_fullhouse_sum");		//플하우스
		mHodem_FlushAmountLabel = mMainPanel->getLabel("txt_flush_sum");		//플러쉬
		mHodem_StraitAmountLabel = mMainPanel->getLabel("txt_straight_sum");		//스트레이트
		mHodem_TripleAmountLabel = mMainPanel->getLabel("txt_three_sum");		//스티플
		mHodem_2PairAmountLabel = mMainPanel->getLabel("txt_two_sum");		//2페어
		mHodem_1PairAmountLabel = mMainPanel->getLabel("txt_one_sum");		//1페어
		mHodem_DieAmountLabel = mMainPanel->getLabel("txt_die_sum");		//다이	
		//
		mTitleLanbel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HOLDEM").c_str());
		mTitleUnderLanbel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HOLDEM").c_str());

		mMainPanel->getLabel("txt_royalfl")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ROYAL_SHORT").c_str());
		mMainPanel->getLabel("txt_straightfl")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_STIFUL_SHORT").c_str());
		mMainPanel->getLabel("txt_four")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FOURCARD").c_str());
		mMainPanel->getLabel("txt_fullhouse")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FULLHOUSE").c_str());
		mMainPanel->getLabel("txt_flush")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FLUSH").c_str());
		mMainPanel->getLabel("txt_straight")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_STRAIGHT").c_str());
		mMainPanel->getLabel("txt_three")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_THREEFUL").c_str());
		mMainPanel->getLabel("txt_two")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_TWOFAIR").c_str());
		mMainPanel->getLabel("txt_one")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ONEFAIR").c_str());
		//총 다이 횟수
		mMainPanel->getLabel("txt_die")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordWorldTourPanel_TOTAL_DIE").c_str());
	}

	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);
}

void HandsHistoryContentPanel::setActivate(bool activate)
{
	setVisible(activate);
	if (activate)
		refreshAmount();
}

void HandsHistoryContentPanel::refreshAmount()
{
	W_RecordInfo* recordInfo = GameDataManager::getSingletonPtr()->m_pRecordInfo;
	if (mType == HISTORY_SEVEN_POKER) {
		mPoker_RotiflAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_7POKER, HIGH_ROYAL_STRAIGHT_FLUSH).c_str()); //로티플
		mPoker_StiflAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_7POKER, HIGH_STRAIGHT_FLUSH).c_str());//스티플
		mPoker_4CardAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_7POKER, HIGH_FOUR_CARD).c_str());	//포카드
		mPoker_FullHouseAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_7POKER, HIGH_FULL_HOUSE).c_str());		//플하우스
		mPoker_FlushAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_7POKER, HIGH_FLUSH).c_str());		//플러쉬
		mPoker_StraitAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_7POKER, HIGH_STRAIGHT).c_str());		//스트레이트
		mPoker_TripleAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_7POKER, HIGH_TRIPLE).c_str());		//트리플
		mPoker_2PairAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_7POKER, HIGH_TWO_PAIR).c_str());		//2페어
		mPoker_1PairAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_7POKER, HIGH_ONE_PAIR).c_str());		//1페어
		//mPoker_DieAmountLabel->setString(PokerRecordHelper::getBattleStateStr(recordInfo->poker7_jokbo(HIGH_ROYAL_STRAIGHT_FLUSH).c_str());		//다이
		string dieStr = StringConverter::toString(recordInfo->poker7_basic().totaldie()) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
		mPoker_DieAmountLabel->setString(dieStr.c_str());		//다이
	}
	else if (mType == HISTORY_HIGH_LOW) {
		mHigh_FullHouseAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, HIGH_FULL_HOUSE).c_str());	//하이 풀하우스
		mHigh_FlushAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, HIGH_FLUSH).c_str());	//하이 플러쉬
		mHigh_StraitAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, HIGH_STRAIGHT).c_str());	//하이 스트레이트
		mHigh_TripleAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, HIGH_TRIPLE).c_str());	//하이 트리플
		mHigh_2PairAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, HIGH_TWO_PAIR).c_str());	//하이 2페어
		mHigh_1PairAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, HIGH_ONE_PAIR).c_str());	//하이 1페어이하
		mLow_6TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, LOW_SIX_TOP).c_str());	//로우 6탑
		mLow_7TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, LOW_SEVEN_TOP).c_str());	//로우 7탑
		mLow_8TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, LOW_EIGHT_TOP).c_str());	//로우 8탑
		mLow_9TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, LOW_NINE_TOP).c_str());	//로우 9탑
		mLow_10TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, LOW_TEN_TOP).c_str());	//로우 10탑
		mLow_jTopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, LOW_J_TOP).c_str());	//로우 j탑이하
		mSwing_RotiflAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, HIGH_ROYAL_STRAIGHT_FLUSH).c_str());	//스윙 로티플
		mSwing_StiflAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, HIGH_STRAIGHT_FLUSH).c_str());	//스윙 스티플
		mSwing_4CardAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HIGH_LOW, HIGH_FOUR_CARD).c_str());	//스윙 포카드
		string dieStr = StringConverter::toString(recordInfo->highlow_basic().totaldie()) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
		mHighLow_totalDieAmountLabel->setString(dieStr.c_str());		//다이
	}
	else if (mType == HISTORY_BADDUGI) {
		mBadugi_GolfAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_GOLF).c_str());	//골프
		mBadugi_SecondAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_SECOND).c_str());  	//세컨드
		mBadugi_ThirdAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_THIRD).c_str());	//서드
		mBadugi_5TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_FIVE_TOP).c_str());	//5탑
		mBadugi_6TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_SIX_TOP).c_str());	//6탑
		mBadugi_7TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_SEVEN_TOP).c_str());	//7탑
		mBadugi_8TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_EIGHT_TOP).c_str());	//8탑
		mBadugi_9TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_NINE_TOP).c_str());	//9탑
		mBadugi_10TopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_TEN_TOP).c_str());	//10탑
		mBadugi_JTopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_J_TOP).c_str());	//J탑
		mBadugi_QTopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_Q_TOP).c_str());	//Q탑
		mBadugi_KTopAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_K_TOP).c_str());	//K탑
		mBadugi_BaseAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_BASE).c_str());	//베이스
		mBadugi_Under2BaseAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_BADUKI, BADUKI_TWO_BASE).c_str());	//투베이스 이하
		//mBadugi_TotalDieAmountLabel->setString(PokerRecordHelper::getBattleStateStr(HIGH_FULL_HOUSE).c_str());	//총 다이 횟수
		string dieStr = StringConverter::toString(recordInfo->baduki_basic().totaldie()) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
		mBadugi_TotalDieAmountLabel->setString(dieStr.c_str());		//다이
	}
	else if (mType == HISTORY_HODEM) {
		mHodem_RotiflAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HOLDEM, HIGH_ROYAL_STRAIGHT_FLUSH).c_str());	//로티플
		mHodem_StiflAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HOLDEM, HIGH_STRAIGHT_FLUSH).c_str());	//스티플
		mHodem_4CardAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HOLDEM, HIGH_FOUR_CARD).c_str());		//포카드
		mHodem_FullHouseAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HOLDEM, HIGH_FULL_HOUSE).c_str());		//플하우스
		mHodem_FlushAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HOLDEM, HIGH_FLUSH).c_str());		//플러쉬
		mHodem_StraitAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HOLDEM, HIGH_STRAIGHT).c_str());		//스트레이트
		mHodem_TripleAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HOLDEM, HIGH_TRIPLE).c_str());		//스티플
		mHodem_2PairAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HOLDEM, HIGH_TWO_PAIR).c_str());		//2페어
		mHodem_1PairAmountLabel->setString(PokerRecordHelper::getPokerBattleStateStr(GAMEKIND_HOLDEM, HIGH_ONE_PAIR).c_str());	//1페어
		//mHodem_DieAmountLabel->setString(PokerRecordHelper::getBattleStateStr(BADUKI_GOLF).c_str());		//다이	
		string dieStr = StringConverter::toString(recordInfo->holdem_basic().totaldie()) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
		mHodem_DieAmountLabel->setString(dieStr.c_str());		//다이
	}
}
