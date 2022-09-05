#include "pch.h"
#include "LobbyRecordTourmentPanel.h"

#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "RankInfoContentPanel.h"
#include "GameDataManager.h"


LobbyRecordTourmentPanel::LobbyRecordTourmentPanel()
{
	_init();
}

LobbyRecordTourmentPanel::~LobbyRecordTourmentPanel()
{

}

void LobbyRecordTourmentPanel::_init()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_record3.mxml");
	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);

	mRankInfoPanel = new RankInfoContentPanel(RankInfoContentPanel::RANK_INFO_NO_GAUGE);
	mMainPanel->addChild(mRankInfoPanel);
	mRankInfoPanel->release();
	CCPoint _shop1Pos = mMainPanel->getDummy("dmy_season_rank").origin;
	_shop1Pos.y = -_shop1Pos.y;
	mRankInfoPanel->setPosition(_shop1Pos);

	mContentPanel_1 = new LobbyLatelybarContentPanel(LobbyLatelybarContentPanel::BAR_TOURMENT_TYPE);
	mMainPanel->addChild(mContentPanel_1);
	mContentPanel_1->release();
	mContentPanel_1->setPosition(mMainPanel->getImage("dmy_record_latelybar1")->getPosition());

	mContentPanel_2 = new LobbyLatelybarContentPanel(LobbyLatelybarContentPanel::BAR_TOURMENT_TYPE);
	mMainPanel->addChild(mContentPanel_2);
	mContentPanel_2->release();
	mContentPanel_2->setPosition(mMainPanel->getImage("dmy_record_latelybar2")->getPosition());

	mContentPanel_3 = new LobbyLatelybarContentPanel(LobbyLatelybarContentPanel::BAR_TOURMENT_TYPE);
	mMainPanel->addChild(mContentPanel_3);
	mContentPanel_3->release();
	mContentPanel_3->setPosition(mMainPanel->getImage("dmy_record_latelybar3")->getPosition());

	mWinInfo_1 = new RecordPokerStateContentPanel();
	mMainPanel->addChild(mWinInfo_1);
	mWinInfo_1->release();
	mWinInfo_1->setPosition(mMainPanel->getImage("dmy_record_victory1")->getPosition());

	mWinInfo_2 = new RecordPokerStateContentPanel();
	mMainPanel->addChild(mWinInfo_2);
	mWinInfo_2->release();
	mWinInfo_2->setPosition(mMainPanel->getImage("dmy_record_victory2")->getPosition());

	mWinInfo_3 = new RecordPokerStateContentPanel();
	mMainPanel->addChild(mWinInfo_3);
	mWinInfo_3->release();
	mWinInfo_3->setPosition(mMainPanel->getImage("dmy_record_victory3")->getPosition());

	//시즌기록
	mMainPanel->getLabel("txt_title_season_under")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_TITLE").c_str());
	mMainPanel->getLabel("txt_title_season")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_TITLE").c_str());
	//초급
	mMainPanel->getLabel("txt_low")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_LOW_TITLE").c_str());
	//중급
	mMainPanel->getLabel("txt_middle")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_MIDDLE_TITLE").c_str());
	//고급
	mMainPanel->getLabel("txt_high")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_HIGH_TITLE").c_str());
	//최근기록
	mMainPanel->getLabel("txt_lately_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_RECORD_TITLE").c_str());
	mMainPanel->getLabel("txt_lately_title")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_RECORD_TITLE").c_str());
	//날짜
	mMainPanel->getLabel("txt_lately_day")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_DAY_TITLE").c_str());
	//대회명
	mMainPanel->getLabel("txt_lately_match")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordTourmentPanel_CUP_TITLE").c_str());
	//순위
	mMainPanel->getLabel("txt_lately_ranking")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_RANK_LABEL").c_str());
	//명성
	mMainPanel->getLabel("txt_lately_fame")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REPUTE_UNIT").c_str());

}

void LobbyRecordTourmentPanel::onClicked(const string& buttonName)
{

}

void LobbyRecordTourmentPanel::setActivate(bool activate)
{
	if (activate) {
		setVisible(true);
		if (getPositionX() < 0) {
			setPositionX(getPositionX() + DESIGN_WIDTH);
		}

		W_RecordSeasonInfo* seasonInfo = GameDataManager::getSingleton().getRecordSeasonInfo();
		
		if (seasonInfo && seasonInfo->placeinfo_size() > 0) {
			W_RecordPlaceInfo placeInfo = seasonInfo->placeinfo(0);
			bool hasoption = placeInfo.has_qualifier();
			int qualifier = -1;
			if (placeInfo.has_qualifier()) {
				qualifier = placeInfo.qualifier();
			}
			mWinInfo_1->setData(placeInfo.firstplace(), placeInfo.secondplace(), qualifier);
			mWinInfo_1->setVisible(true);
		}
		else {
			mWinInfo_1->setVisible(false);
		}

		if (seasonInfo && seasonInfo->placeinfo_size() > 1) {
			W_RecordPlaceInfo placeInfo = seasonInfo->placeinfo(1);
			mWinInfo_2->setData(placeInfo.firstplace(), placeInfo.secondplace(), placeInfo.qualifier());
			mWinInfo_2->setVisible(true);
		}
		else {
			mWinInfo_2->setVisible(false);
		}

		if (seasonInfo && seasonInfo->placeinfo_size() > 2) {
			W_RecordPlaceInfo placeInfo = seasonInfo->placeinfo(2);
			mWinInfo_3->setData(placeInfo.firstplace(), placeInfo.secondplace(), placeInfo.qualifier());
			mWinInfo_3->setVisible(true);
		}
		else {
			mWinInfo_3->setVisible(false);
		}



		if (seasonInfo && seasonInfo->latelyinfo_size() > 0) {
			W_RecordLatelyInfo laytelyInfo = seasonInfo->latelyinfo(0);
			mContentPanel_1->setBar(laytelyInfo.date(), laytelyInfo.title(), laytelyInfo.rank(), laytelyInfo.honor());
			mContentPanel_1->setVisible(true);
		}
		else {
			mContentPanel_1->setVisible(false);
		}

		if (seasonInfo && seasonInfo->latelyinfo_size() > 1) {
			W_RecordLatelyInfo laytelyInfo = seasonInfo->latelyinfo(1);
			mContentPanel_2->setBar(laytelyInfo.date(), laytelyInfo.title(), laytelyInfo.rank(), laytelyInfo.honor());
			mContentPanel_2->setVisible(true);
		}
		else {
			mContentPanel_2->setVisible(false);
		}

		if (seasonInfo && seasonInfo->latelyinfo_size() > 2) {
			W_RecordLatelyInfo laytelyInfo = seasonInfo->latelyinfo(2);
			mContentPanel_3->setBar(laytelyInfo.date(), laytelyInfo.title(), laytelyInfo.rank(), laytelyInfo.honor());
			mContentPanel_3->setVisible(true);
		}
		else {
			mContentPanel_3->setVisible(false);
		}

	}
	else {
		setVisible(false);
		if (getPositionX() > 0) {
			setPositionX(getPositionX() - DESIGN_WIDTH);
		}
	}
}
