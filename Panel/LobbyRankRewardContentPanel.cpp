#include "pch.h"
#include "LobbyRankRewardContentPanel.h"
#include "HeroUtil.h"
#include "W_PointWeeklyRankData.pb.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "PokerResourceHelper.h"

LobbyRankRewardContentPanel::LobbyRankRewardContentPanel(int idx)
{
	mDataIndex = idx;
	_init();
	displayRankData();
}

LobbyRankRewardContentPanel::~LobbyRankRewardContentPanel()
{

}

void LobbyRankRewardContentPanel::_init()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_weekrank_table.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);

	mRewardIcon = mMainPanel->getSkel("skel_icon");
	mRankIcon = mMainPanel->getSkel("skel_rank");
	mClassNumberLabel = mMainPanel->getLabel("txt_classnumber");
	mClassNumberUnderLabel = mMainPanel->getLabel("txt_classnumber_under");
	mBonusLabel = mMainPanel->getLabel("txt_bonus");
	mBonusUnderLabel = mMainPanel->getLabel("txt_bonus_under");
}

void LobbyRankRewardContentPanel::displayRankData()
{
	string rankStr = "";
	const W_PointWeeklyRankData data = GameDataManager::getSingleton().GetGameDataPtr()->tourrankdata(mDataIndex);
	if (data.ranktype() == W_PointWeeklyRankData_eWeeklyRankType_AbsRank) {
		if (data.minrank() == data.maxrank()) {
			rankStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REWARD_RANK_SOLO_TITLE"), data.minrank());
		}
		else if (data.maxrank() == -1) {
			rankStr = GameStringDepot::getSingleton().getString("REWARD_RANK_END_TITLE");
		}
		else {
			rankStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REWARD_RANK_GUIDE_TITLE"), data.minrank(), data.maxrank());
		}
	}	

	mRankIcon->setVisible(false);

	if (data.minrank() == 1) {
		mRankIcon->setVisible(true);
		mRankIcon->playAnimation("rank_1_s");		
		mClassNumberLabel->setVisible(false);
		mClassNumberUnderLabel->setVisible(false);
	}
	else if (data.minrank() == 2) {
		mRankIcon->setVisible(true);
		mRankIcon->playAnimation("rank_2_s");
		mClassNumberLabel->setVisible(false);
		mClassNumberUnderLabel->setVisible(false);
	}
	else if (data.minrank() == 3) {
		mRankIcon->setVisible(true);
		mRankIcon->playAnimation("rank_3_s");
		mClassNumberLabel->setVisible(false);
		mClassNumberUnderLabel->setVisible(false);
	}
	//몇등~ 몇등
	mClassNumberLabel->setString(rankStr.c_str());
	mClassNumberUnderLabel->setString(rankStr.c_str());	
	W_RewardInfo_RewardSet rewardSet = data.rewardinfo().rewardset(0);
	PokerResourceHelper::setRewardIcon(mRewardIcon, rewardSet);
	//rewardIcon 이 캐쉬 냐 게임 머니냐.
	//mRewardIcon
	//보상 금액
	string gameMoneyStr = "";
	if (rewardSet.type() == GAMEMONEY) {
		gameMoneyStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(rewardSet.amount()));
	}
	else {
		gameMoneyStr = StringConverter::toString(rewardSet.amount());
	}
	mBonusUnderLabel->setString(gameMoneyStr.c_str());
	mBonusLabel->setString(gameMoneyStr.c_str());
}
