#include "pch.h"
#include "LobbyRecordSurvivalPanel.h"

#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"


LobbyRecordSurvivalPanel::LobbyRecordSurvivalPanel()
{
	_init();
}

LobbyRecordSurvivalPanel::~LobbyRecordSurvivalPanel()
{

}

void LobbyRecordSurvivalPanel::_init()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_record4.mxml");
	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);

	mContentPanel_1 = new LobbyLatelybarContentPanel(LobbyLatelybarContentPanel::BAR_SURVIVAL_TYPE);
	mMainPanel->addChild(mContentPanel_1);
	mContentPanel_1->release();
	mContentPanel_1->setPosition(mMainPanel->getImage("dmy_record4_latelybar1")->getPosition());

	mContentPanel_2 = new LobbyLatelybarContentPanel(LobbyLatelybarContentPanel::BAR_SURVIVAL_TYPE);
	mMainPanel->addChild(mContentPanel_2);
	mContentPanel_2->release();
	mContentPanel_2->setPosition(mMainPanel->getImage("dmy_record4_latelybar2")->getPosition());

	mContentPanel_3 = new LobbyLatelybarContentPanel(LobbyLatelybarContentPanel::BAR_SURVIVAL_TYPE);
	mMainPanel->addChild(mContentPanel_3);
	mContentPanel_3->release();
	mContentPanel_3->setPosition(mMainPanel->getImage("dmy_record4_latelybar3")->getPosition());	

	mVictoryAmountLabel = mMainPanel->getLabel("txt_victory_sum");
	mHalfVictoryAmountLabel = mMainPanel->getLabel("txt_second_sum");
	mMoneyInAmountLabel = mMainPanel->getLabel("txt_moneyin_sum");
	mBestGetMoneyLabel = mMainPanel->getLabel("txt_topgold_sum");
	
	Trophy = mMainPanel->getSkel("skel_mark_big");
	Trophy->setScale(1.45f);
	Trophy->setVisible(false);

	mMainPanel->getLabel("txt_no_win_desc")->setColor(ccc3(251,201,113));
	mMainPanel->getLabel("txt_no_win_desc")->setVisible(false);

	//트로피
	mMainPanel->getLabel("txt_trophy")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordSurvivalPanel_TROPHY").c_str());
	//우승
	mMainPanel->getLabel("txt_victory")->setString(GameStringDepot::getSingletonPtr()->getString("RecordPokerStateContentPanel_WIN").c_str());
	//준우승
	mMainPanel->getLabel("txt_second")->setString(GameStringDepot::getSingletonPtr()->getString("RecordPokerStateContentPanel_SECOND_WIN").c_str());
	//머니인
	mMainPanel->getLabel("txt_moneyin")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordSurvivalPanel_MONEYIN").c_str());
	//최고 획득 상금
	mMainPanel->getLabel("txt_topgold")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordSurvivalPanel_BEST_GETMONEY").c_str());
	//최근기록
	mMainPanel->getLabel("txt_lately_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_RECORD_TITLE").c_str());
	mMainPanel->getLabel("txt_lately_title")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_RECORD_TITLE").c_str());
	//날짜
	mMainPanel->getLabel("txt_lately_day")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_DAY_TITLE").c_str());
	//대회명
	mMainPanel->getLabel("txt_lately_match")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_CUP_TITLE").c_str());
	//순위
	mMainPanel->getLabel("txt_lately_ranking")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_RANK_LABEL").c_str());
	//획득상금
	mMainPanel->getLabel("txt_lately_prize")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GET_WIN_MONEY").c_str());
}

void LobbyRecordSurvivalPanel::onClicked(const string& buttonName)
{

}

void LobbyRecordSurvivalPanel::setActivate(bool activate)
{
	if (activate) {
		setVisible(true);
		if (getPositionX() < 0) {
			setPositionX(getPositionX() + DESIGN_WIDTH);
		}
		W_RecordDeathMatchInfo* deathMatchInfo = GameDataManager::getSingleton().getRecordDeathMatchInfo();
		
		if (deathMatchInfo && deathMatchInfo->latelyinfo_size() > 0) {
			W_RecordLatelyInfo laytelyInfo = deathMatchInfo->latelyinfo(0);
			mContentPanel_1->setSurvival(laytelyInfo.date(), laytelyInfo.title(), laytelyInfo.rank(), laytelyInfo.money());
			mContentPanel_1->setVisible(true);
		}
		else {
			mContentPanel_1->setVisible(false);
			mMainPanel->getLabel("txt_no_win_desc")->setVisible(true);

		}

		if (deathMatchInfo && deathMatchInfo->latelyinfo_size() > 1) {
			W_RecordLatelyInfo laytelyInfo = deathMatchInfo->latelyinfo(1);
			mContentPanel_2->setSurvival(laytelyInfo.date(), laytelyInfo.title(), laytelyInfo.rank(), laytelyInfo.money());
			mContentPanel_2->setVisible(true);
		}
		else {
			mContentPanel_2->setVisible(false);
		}

		if (deathMatchInfo && deathMatchInfo->latelyinfo_size() > 2) {
			W_RecordLatelyInfo laytelyInfo = deathMatchInfo->latelyinfo(2);
			mContentPanel_3->setSurvival(laytelyInfo.date(), laytelyInfo.title(), laytelyInfo.rank(), laytelyInfo.money());
			mContentPanel_3->setVisible(true);
		}
		else {
			mContentPanel_3->setVisible(false);
		}
		int victoryAmount = 0;
		int secondAmount = 0;
		int moneyInAmount = 0;
		int64 bestMoney = 0;
		if (deathMatchInfo) {
			victoryAmount = deathMatchInfo->firstplace();
			secondAmount = deathMatchInfo->secondplace();
			moneyInAmount = deathMatchInfo->moneyin();
			bestMoney = deathMatchInfo->topobtainmoney();
		} 
		string victoryStr = StringConverter::toString(victoryAmount) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
		mVictoryAmountLabel->setString(victoryStr.c_str());
		string secondStr = StringConverter::toString(secondAmount) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
		mHalfVictoryAmountLabel->setString(secondStr.c_str());
		string moneyInStr = StringConverter::toString(moneyInAmount) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
		mMoneyInAmountLabel->setString(moneyInStr.c_str());
		string moneyStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(bestMoney)) + GameStringDepot::getSingleton().getString("TXT_GOLD_UNIT");
		mBestGetMoneyLabel->setString(moneyStr.c_str());
		
	}
	else {
		setVisible(false);
		if (getPositionX() > 0) {
			setPositionX(getPositionX() - DESIGN_WIDTH);
		}
	}
}
