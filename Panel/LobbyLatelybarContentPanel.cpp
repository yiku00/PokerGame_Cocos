#include "pch.h"
#include "LobbyLatelybarContentPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"


LobbyLatelybarContentPanel::LobbyLatelybarContentPanel(LATELYBAR_TYPE type)
{
	mType = type;
	initPanel();
}

LobbyLatelybarContentPanel::~LobbyLatelybarContentPanel()
{

}

void LobbyLatelybarContentPanel::setBar(string day, string match, int ranking, int honnor)
{
	mDay->setString(day.c_str());
	mMatch->setString(match.c_str());
	string rankStr = NxGetFormatString(GameStringDepot::getSingleton().getString("RANK_GRADE_PREFIX"), ranking);
	mRanking->setString(rankStr.c_str());
	string honnorStr = NxGetFormatString(GameStringDepot::getSingleton().getString("RANK_GRADE_REPUTE"), honnor);
	mFrame->setString(honnorStr.c_str());
}

void LobbyLatelybarContentPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();

	if (mType == BAR_TOURMENT_TYPE) {
		mMainPanel->construct(getMxmlPath() + "dmy_record3_latelybar.mxml");
		mDay = mMainPanel->getLabel("txt_lately_day");
		mMatch = mMainPanel->getLabel("txt_lately_match");
		mRanking = mMainPanel->getLabel("txt_lately_ranking");
		mFrame = mMainPanel->getLabel("txt_lately_fame");
	}
	else {
		mMainPanel->construct(getMxmlPath() + "dmy_record4_latelybar.mxml");
		mDay = mMainPanel->getLabel("txt_lately_day");
		mMatch = mMainPanel->getLabel("txt_lately_match");
		mRanking = mMainPanel->getLabel("txt_lately_ranking");		
		mFrame = mMainPanel->getLabel("txt_lately_prize");
	}

	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);

	

}

void LobbyLatelybarContentPanel::setSurvival(string day, string match, int ranking, int64 money)
{
	mDay->setString(day.c_str());
	mMatch->setString(match.c_str());
	string rankStr = NxGetFormatString(GameStringDepot::getSingleton().getString("RANK_GRADE_PREFIX"), ranking);
	mRanking->setString(rankStr.c_str());

	string moneyStr = "+" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(money));
	mFrame->setString(moneyStr.c_str());
}

