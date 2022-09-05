#include "pch.h"
#include "WeeklyResultPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PokerRankHelper.h"
#include "PokerResourceHelper.h"


WeeklyResultPanel::WeeklyResultPanel()
{
	W_TourOfInfo* tourofInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	mWeeklyRewardInfo.CopyFrom(tourofInfo->weeklyrewardinfo());
	initPanel();	
	refreshResult();
}

WeeklyResultPanel::~WeeklyResultPanel()
{
	//destruct();
}

void WeeklyResultPanel::onClicked(const string& name)
{
	if (name == "Close") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
}

void WeeklyResultPanel::initPanel()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_season_end2.mxml");
	setButtonListener(this);
	mTitle = getLabel("txt_title");
	mTitleUnder = getLabel("txt_title_under");
	mDesc = getLabel("txt_info");
	
	mRankTitle = getLabel("txt_sub_title1");
	mRank = getLabel("txt_rank_info");
	
	mRewardTitle = getLabel("txt_sub_title2");
	mRewardAmount = getLabel("txt_reward_info");

	mConfirmBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_CONFIRM);
	addChild(mConfirmBtn);
	mConfirmBtn->release();
	CCPoint pos = getDummy("dmy_button_smiddle").origin;
	pos.y = -pos.y;
	mConfirmBtn->setPosition(pos);
	mConfirmBtn->m_Button->setName("Close");
	mConfirmBtn->SetButtonListener(this);
	mConfirmBtn->SetBtnText(GameStringDepot::getSingleton().getString("TXT_OK_LABEL"));

	//고정된 값들
	string titleStr = GameStringDepot::getSingleton().getString("WeeklyResultPanel_TITLE");
	mTitle->setString(titleStr.c_str());
	mTitleUnder->setString(titleStr.c_str());
	
	string descStr = GameStringDepot::getSingleton().getString("WeeklyResultPanel_DESC");
	mDesc->setString(descStr.c_str());

	string rankTitleStr = GameStringDepot::getSingleton().getString("WeeklyResultPanel_RANK_TITLE");
	mRankTitle->setString(rankTitleStr.c_str());
	
	string rewardTitleStr = GameStringDepot::getSingleton().getString("WeeklyResultPanel_REWARD_TITLE");
	mRewardTitle->setString(rewardTitleStr.c_str());
}

void WeeklyResultPanel::refreshResult()
{
	//등수
	string rankStr = StringConverter::toString(mWeeklyRewardInfo.currank()) + GameStringDepot::getSingleton().getString("TXT_RANK");
	mRank->setString(rankStr.c_str());
	string reputeStr = StringConverter::toString(mWeeklyRewardInfo.repute());
	
	string moneyStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(mWeeklyRewardInfo.rewardinfo().rewardset(0).amount()));
	mRewardAmount->setString(moneyStr.c_str());	
}

void WeeklyResultPanel::onRefresh()
{
	setVisible(true);
}
