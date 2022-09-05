#include "pch.h"
#include "RecordPokerStateContentPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"


RecordPokerStateContentPanel::RecordPokerStateContentPanel()
{
	initPanel();
}

RecordPokerStateContentPanel::~RecordPokerStateContentPanel()
{

}

void RecordPokerStateContentPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_record_victory.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);

	mVictoryLabel = mMainPanel->getLabel("txt_victory_sum");
	mHalfVictoryLabel = mMainPanel->getLabel("txt_second_sum");
	mPlayoffLabel = mMainPanel->getLabel("txt_third_sum");
	mPlayoffTitleLabel = mMainPanel->getLabel("txt_third");

	//우승
	mMainPanel->getLabel("txt_victory")->setString(GameStringDepot::getSingletonPtr()->getString("RecordPokerStateContentPanel_WIN").c_str());
	//준우승
	mMainPanel->getLabel("txt_second")->setString(GameStringDepot::getSingletonPtr()->getString("RecordPokerStateContentPanel_SECOND_WIN").c_str());
	//예선통과
	mMainPanel->getLabel("txt_third")->setString(GameStringDepot::getSingletonPtr()->getString("RecordPokerStateContentPanel_PLAYOFF").c_str());
}

void RecordPokerStateContentPanel::setData(int win, int halfWin, int playoff)
{
	string winStr = StringConverter::toString(win) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
	mVictoryLabel->setString(winStr.c_str());
	string halfWinStr = StringConverter::toString(halfWin) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
	mHalfVictoryLabel->setString(halfWinStr.c_str());
	if (playoff == -1) {
		mPlayoffLabel->setVisible(false);
		mPlayoffTitleLabel->setVisible(false);
	}
	else {
		string playOffStr = StringConverter::toString(playoff) + GameStringDepot::getSingleton().getString("TXT_COUNT_UNIT");
		mPlayoffLabel->setString(playOffStr.c_str());
	}
	
}

