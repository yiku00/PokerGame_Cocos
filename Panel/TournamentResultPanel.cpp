#include "pch.h"
#include "TournamentResultPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"

TournamentResultPanel::TournamentResultPanel(int rank)
{
	mRank = rank;
	runAction(CCSequence::create(
		CCDelayTime::create(1.f),
		CCCallFunc::create(this, callfunc_selector(TournamentResultPanel::initPanel)),
		NULL));
}

TournamentResultPanel::~TournamentResultPanel()
{
	
}

void TournamentResultPanel::initPanel()
{
	if (mRank < 4)	//1 , 2, 3
		initThophyPanel();
	else
		initEtcPanel();	
}

void TournamentResultPanel::initThophyPanel()
{
	construct(getMxmlPath() + "dmy_guidewinner_bar.mxml");
	mBg = getSkel("skel_guidebar");
	mBg->playAnimation("guidebar2_start");
	mBg->appendAnimation("guidebar2_loop");

	getSkel("skel_light")->playAnimation("light_shine");
	string trophyImgStr = "ui/trophy_gold.png";
	if (mRank == 2) {
		trophyImgStr = "ui/trophy_silver.png";		
	}
	else if (mRank == 3) {
		trophyImgStr = "ui/trophy_bronze.png";		
	}
	getImage("img_trophy_gold")->setSpriteFrameWithFile(trophyImgStr);


	//title 관련
	//1등일때
	//2 _ 3등 일때
	string descStr = GameStringDepot::getSingleton().getString("TournamentResultPanel_GOLD");
	string titleStr = NxGetFormatString(GameStringDepot::getSingleton().getString("TournamentResultPanel_TITLE"), mRank);
	if (mRank == 1) {
		bool isFinalWin = true;
		W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
		if (_pInfoData)
		{
			W_TourInfo _tourInfo = _pInfoData->tourinfo(GameDataManager::getSingletonPtr()->mTourSelectIndex);
			if (_tourInfo.stepinfo_size() > GameDataManager::getSingletonPtr()->mTourStep + 1)
				isFinalWin = false;
		}

		if (isFinalWin) {
			titleStr = GameStringDepot::getSingleton().getString("TournamentResultPanel_FINAL_TITLE");
			descStr = GameStringDepot::getSingleton().getString("TournamentResultPanel_FINAL_WIN");
		}
		else {
			titleStr = GameStringDepot::getSingleton().getString("TournamentResultPanel_WIN_TITLE");
			descStr = GameStringDepot::getSingleton().getString("TournamentResultPanel_WIN");
		}
		
	}
	getLabel("txt_rank")->setString(titleStr.c_str());
	getLabel("txt_victory")->setString(descStr.c_str());
}

void TournamentResultPanel::initEtcPanel()
{
	construct(getMxmlPath() + "dmy_guide_bar.mxml");
	mBg = getSkel("skel_guidebar");
	mBg->playAnimation("guidebar1_start");
	mBg->appendAnimation("guidebar1_loop");	
	getSkel("skel_stay_mark")->playAnimation("blank");
	string titleStr = NxGetFormatString(GameStringDepot::getSingleton().getString("TournamentResultPanel_TITLE"), mRank);
	getLabel("txt_guide")->setString(titleStr.c_str());

	getLabel("txt_rank_sum1")->setVisible(false);
	getLabel("txt_rank_sum2")->setVisible(false);
	getLabel("txt_rank_sum3")->setVisible(false);


	if (mRank < 10) {
		getLabel("txt_rank_sum1")->setVisible(true);
		getLabel("txt_rank_sum1")->setString(StringConverter::toString(mRank).c_str());
	}
	else if (mRank < 100) {
		getLabel("txt_rank_sum2")->setVisible(true);
		getLabel("txt_rank_sum2")->setString(StringConverter::toString(mRank).c_str());
	}
	else {
		getLabel("txt_rank_sum3")->setVisible(true);
		getLabel("txt_rank_sum3")->setString(StringConverter::toString(mRank).c_str());
	}
}

