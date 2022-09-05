#include "pch.h"
#include "SeasonRatingPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PokerRankHelper.h"

#define ANI_GAUGEBAR_TIME 1.0f
#define ANI_DELAY_TIME 2.0f

SeasonRatingPanel::SeasonRatingPanel()
{
	mMoveFlag = false;
	mUserMoveFlag = false;

	initPanel();	
	initData();
}

SeasonRatingPanel::~SeasonRatingPanel()
{
	//destruct();
}

void SeasonRatingPanel::initPanel()
{
	construct(getMxmlPath() + "dmy_rank_progress.mxml");	

	mBg = getSkel("skel_rankback");
	mRankingIcon = getSkel("skel_rankicon");
	mGaugeBar = getSkel("skel_gauge");
	mGaugeBar->setAnchorPoint(ccp(0.f, 0.5f));
	mGaugeBar->setPositionX(mGaugeBar->getPositionX() - getDummy("skel_gauge").size.width / 2.0f);


	mGradeFirst1 = getLabel("txt_rank1");
	mGradeFirst2 = getLabel("txt_rank2");
	mGradeFirst3 = getLabel("txt_rank4");
	mGradeFirst4 = getLabel("txt_rank6");
	mGradeFirst5 = getLabel("txt_rank7");

	mGradeSecond1 = getLabel("txt_rank1");
	mGradeSecond2 = getLabel("txt_rank3");
	mGradeSecond3 = getLabel("txt_rank5");
	mGradeSecond4 = getLabel("txt_rank7");	

	mGradeThird1 = getLabel("txt_rank1");
	mGradeThird2 = getLabel("txt_rank4");
	mGradeThird3 = getLabel("txt_rank7");
	
	mNowRepute = getLabel("txt_fame_now");
	mSlash = getLabel("txt_slash");
	mNextRepute = getLabel("txt_fame_total");

	mRankTitle = getLabel("str_rank_name");

	//랭킹 진척도 txt_title
	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("SeasonRatingPanel_TITLE").c_str());
	//화면을 터치하면 창이 종료 됩니다.
	getLabel("txt_touch")->setString(GameStringDepot::getSingletonPtr()->getString("SeasonRatingPanel_TOUCHDESC").c_str());


}

void SeasonRatingPanel::initData()
{
	
  	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
  	mRatingUpInfo.CopyFrom(_pInfoData->ratingupinfo());
  	mStartIndex = mRatingUpInfo.prevrating();
  	mEndIndex = mRatingUpInfo.nextrating();
	mStartUserRatio = GameDataManager::getSingleton().getBeforeReputeRatio();
	mEndUserRatio = PokerRankHelper::getRatioRepute();	
	mTargetRatio = mEndUserRatio;
	CCLOG("SeasonRatingPanel::initData() ratio = %f", mEndUserRatio);
	mTargetActionIndex = 4;
	mStartRatio = mStartUserRatio;
	mRankIndex = mStartIndex;
	
	//mStartIndex = 0;
	//mEndIndex = 1;
	//mStartUserRatio = 0.99f;
	//mTargetRatio = 0.1f;
	//mEndUserRatio = 0.1f;	
	//mTargetActionIndex = 4;
	//mStartRatio = mStartUserRatio;
	//mRankIndex = mStartIndex;

	setGrade();
// 	if (mGradeMode == RATING_BRONZE) {
// 		// 0 1 2 3
// 		mStartActionIndex = mStartIndex;
// 		mStartAniRatio = mStartUserRatio * 0.25f;
// 		if (mStartActionIndex == 0)
// 			mStartAniRatio = 0.f;
// 		mStartRatio = mStartActionIndex * 0.25f + mStartAniRatio;
// 		mStartEndRatio = (mStartActionIndex + 1) *  0.25f;
// 	}
// 	else if (mGradeMode == RATING_SILVER) {	//4 5 6 7 
// 		mStartActionIndex = mStartIndex - 4;
// 		mStartAniRatio = mStartUserRatio * (float)1 / (float)3;
// 		if (mStartActionIndex == 0)
// 			mStartAniRatio = 0.f;
// 		mStartRatio = (mStartActionIndex)* (float)1 / (float)3 + mStartAniRatio;
// 		mStartEndRatio = (mStartActionIndex + 1) * (float)1 / (float)3;
// 	}
// 	else if (mGradeMode == RATING_GOLD) {	// 7 8 9 10
// 		mStartActionIndex = mStartIndex - 7;
// 		mStartAniRatio = mStartUserRatio * (float)1 / (float)3;
// 		if (mStartActionIndex == 0)
// 			mStartAniRatio = 0.f;
// 		mStartRatio = (mStartActionIndex)* (float)1 / (float)3 + mStartAniRatio;
// 		mStartEndRatio = (mStartActionIndex + 1) * (float)1 / (float)3;
// 	}
// 	else if (mGradeMode == RATING_PLATINUM) {	// 10 11 12 13
// 		mStartActionIndex = mStartIndex - 10;
// 		mStartAniRatio = mStartUserRatio * (float)1 / (float)3;
// 		if (mStartActionIndex == 0)
// 			mStartAniRatio = 0.f;
// 		mStartRatio = (mStartActionIndex)* (float)1 / (float)3 + mStartAniRatio;
// 		mStartEndRatio = (mStartActionIndex + 1) * (float)1 / (float)3;
// 	}
// 	else {
// 		mStartActionIndex = mStartIndex -13;
// 		mStartAniRatio = mStartUserRatio * 0.50f;
// 		if (mStartActionIndex == 0)
// 			mStartAniRatio = 0.f;
// 		mStartRatio = (mStartActionIndex)* 0.50f + mStartAniRatio;	//13 14 15 16
// 		mStartEndRatio = (mStartActionIndex + 1) * 0.50f;
// 	}
// 	CCLOG("SeasonRatingPanel::initData() mStartRatio = %f", mStartRatio);
	refreshTxt();
	refreshGaugeBar();
	refreshRankIcon();
	startAction();
	return;
	
}

void SeasonRatingPanel::refreshTxt()
{
	mGradeFirst1->setVisible(false);
	mGradeFirst2->setVisible(false);
	mGradeFirst3->setVisible(false);
	mGradeFirst4->setVisible(false);
	mGradeFirst5->setVisible(false);
	mGradeSecond1->setVisible(false);
	mGradeSecond2->setVisible(false);
	mGradeSecond3->setVisible(false);
	mGradeSecond4->setVisible(false);
	mGradeThird1->setVisible(false);
	mGradeThird2->setVisible(false);
	mGradeThird3->setVisible(false);


	if (mGradeMode == RATING_BRONZE) {
		mGradeFirst1->setVisible(true);
// 		mGradeFirst2->setVisible(true);
// 		mGradeFirst3->setVisible(true);
// 		mGradeFirst4->setVisible(true);
		mGradeFirst5->setVisible(true);
	}
	else if (mGradeMode == RATING_DIA) {
		mGradeThird1->setVisible(true);
	//	mGradeThird2->setVisible(true);
		mGradeThird3->setVisible(true);
	}
	else {
		mGradeSecond1->setVisible(true);
// 		mGradeSecond2->setVisible(true);
// 		mGradeSecond3->setVisible(true);
		mGradeSecond4->setVisible(true);
	}

	string fontColor = "";
	string totalFrameColor = "";
	string slaveColor = "";
	string nowColor = "";

	if (mGradeMode == RATING_BRONZE) {		//등급 없음 0 1 2 3
		fontColor = "fab466";
		totalFrameColor = "714824";
		slaveColor = "714824";
		nowColor = "ffb15a";

		if (mStartIndex == 0) {
			mGradeFirst1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_0").c_str());
			mGradeFirst5->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_1").c_str());
		}
		else if (mStartIndex == 1) {
			mGradeFirst1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_1").c_str());
			mGradeFirst5->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_2").c_str());
		}
		else if (mStartIndex == 2) {
			mGradeFirst1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_2").c_str());
			mGradeFirst5->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_3").c_str());
		}
		else if (mStartIndex == 3) {
			mGradeFirst1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_3").c_str());
			mGradeFirst5->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_4").c_str());
		}


		/*
		mGradeFirst1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_0").c_str());
		mGradeFirst2->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_1").c_str());
		mGradeFirst3->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_2").c_str());
		mGradeFirst4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_3").c_str());
		mGradeFirst5->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_4").c_str());
		*/
		mGradeFirst1->setColor(StringConverter::parseColor3B(fontColor));
		mGradeFirst2->setColor(StringConverter::parseColor3B(fontColor));
		mGradeFirst3->setColor(StringConverter::parseColor3B(fontColor));
		mGradeFirst4->setColor(StringConverter::parseColor3B(fontColor));
		mGradeFirst5->setColor(StringConverter::parseColor3B(fontColor));
		
	}
	else if (mGradeMode == RATING_SILVER) {	//4 5 6  
		fontColor = "aec8e3";
		totalFrameColor = "5b7286";
		slaveColor = "5b7286";
		nowColor = "aec8e3";

		if (mStartIndex == 4) {
			mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_4").c_str());
			mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_5").c_str());
		}
		else if (mStartIndex == 5) {
			mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_5").c_str());
			mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_6").c_str());
		}
		else if (mStartIndex == 6) {
			mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_6").c_str());
			mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_7").c_str());
		}
		/*
		mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_4").c_str());
		mGradeSecond2->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_5").c_str());
		mGradeSecond3->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_6").c_str());
		mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_7").c_str());
		*/
		mGradeSecond1->setColor(StringConverter::parseColor3B(fontColor));
		mGradeSecond2->setColor(StringConverter::parseColor3B(fontColor));
		mGradeSecond3->setColor(StringConverter::parseColor3B(fontColor));
		mGradeSecond4->setColor(StringConverter::parseColor3B(fontColor));
				
	}
	else if (mGradeMode == RATING_GOLD) {	// 7 8 9 
		fontColor = "ffd35a";
		totalFrameColor = "886920";
		slaveColor = "886920";
		nowColor = "ffd35a";


		if (mStartIndex == 7) {
			mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_7").c_str());
			mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_8").c_str());
		}
		else if (mStartIndex == 8) {
			mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_8").c_str());
			mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_9").c_str());
		}
		else if (mStartIndex == 9) {
			mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_9").c_str());
			mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_10").c_str());
		}
		/*
		mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_7").c_str());
		mGradeSecond2->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_8").c_str());
		mGradeSecond3->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_9").c_str());
		mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_10").c_str());
		*/
		mGradeSecond1->setColor(StringConverter::parseColor3B(fontColor));
		mGradeSecond2->setColor(StringConverter::parseColor3B(fontColor));
		mGradeSecond3->setColor(StringConverter::parseColor3B(fontColor));
		mGradeSecond4->setColor(StringConverter::parseColor3B(fontColor));		
	}
	else if (mGradeMode == RATING_PLATINUM) {	// 10 11 12
		fontColor = "dbd2ff";
		totalFrameColor = "7366a2";
		slaveColor = "7366a2";
		nowColor = "dbd2ff";


		if (mStartIndex == 10) {
			mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_10").c_str());
			mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_11").c_str());
		}
		else if (mStartIndex == 11) {
			mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_11").c_str());
			mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_12").c_str());
		}
		else if (mStartIndex == 12) {
			mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_12").c_str());
			mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_13").c_str());
		}

		/*
		mGradeSecond1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_10").c_str());
		mGradeSecond2->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_11").c_str());
		mGradeSecond3->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_12").c_str());
		mGradeSecond4->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_13").c_str());
		*/
		mGradeSecond1->setColor(StringConverter::parseColor3B(fontColor));
		mGradeSecond2->setColor(StringConverter::parseColor3B(fontColor));
		mGradeSecond3->setColor(StringConverter::parseColor3B(fontColor));
		mGradeSecond4->setColor(StringConverter::parseColor3B(fontColor));
		
	}
	else {		
		fontColor = "93f5ff";		
		totalFrameColor = "358a99";
		slaveColor = "358a99";
		nowColor = "93f5ff";

		if (mStartIndex == 13) {
			mGradeThird1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_13").c_str());
			mGradeThird3->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_14").c_str());
		}
		else if (mStartIndex == 14) {
			mGradeThird1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_14").c_str());
			mGradeThird3->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_15").c_str());
		}
		else if (mStartIndex == 15) {
			mGradeThird1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_14").c_str());
			mGradeThird3->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_15").c_str());
		}
		/*
		mGradeThird1->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_13").c_str());
		mGradeThird2->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_14").c_str());
		mGradeThird3->setString(GameStringDepot::getSingleton().getString("RANK_GRADE_TXT_15").c_str());
		*/
		mGradeThird1->setColor(StringConverter::parseColor3B(fontColor));
		mGradeThird2->setColor(StringConverter::parseColor3B(fontColor));
		mGradeThird3->setColor(StringConverter::parseColor3B(fontColor));
		
	}

	int initRepute = PokerRankHelper::getReputeAmount(mRankIndex);
	int maxRepute = PokerRankHelper::getReputeAmount(mRankIndex + 1);
	if (maxRepute == -1)
		maxRepute = PokerRankHelper::getReputeAmount(mRankIndex);
	
	int targetRepute = 0;
	int endRepute = 0;
	int perRepute = maxRepute - initRepute;
 	if (mStartIndex == mEndIndex) {
		targetRepute = GameDataManager::getSingleton().getPlayerInfo().repute() - initRepute;
		endRepute = perRepute;
	}
	else {
		targetRepute = perRepute;	//
		endRepute = perRepute;	//
	}

	//init reput 값
	//next repute 값 
	mNowRepute->setString(StringConverter::toString(0).c_str());
	mNowRepute->setColor(StringConverter::parseColor3B(nowColor));
	mNowRepute->setInt(0);
	mNowRepute->setIntAction(targetRepute, ANI_GAUGEBAR_TIME);

	mSlash->setColor(StringConverter::parseColor3B(slaveColor));


	//mSlash = getLabel("txt_slash");
	if (endRepute == 0)
		mNextRepute->setString("MAX");
	else
		mNextRepute->setString(StringConverter::toString(endRepute).c_str());		
	mNextRepute->setColor(StringConverter::parseColor3B(totalFrameColor));
	
	mRankTitle->setString(PokerRankHelper::getRankTitleStr(mRankIndex).c_str());
	mRankTitle->setColor(StringConverter::parseColor3B(PokerRankHelper::getRankTitleColorStr(mRankIndex)));
}

void SeasonRatingPanel::refreshGaugeBar()
{
	//스타트 게이지바
	if (mGradeMode == RATING_BRONZE) {		//등급 없음 0 1 2 3 4은
		mGaugeBar->playAnimation("gauge_1");
	}
	else if (mGradeMode == RATING_SILVER) {	//4 5 6 7 
		mGaugeBar->playAnimation("gauge_2");
	}
	else if (mGradeMode == RATING_GOLD) {	// 7 8 9 10
		mGaugeBar->playAnimation("gauge_3");
	}
	else if (mGradeMode == RATING_PLATINUM) {	// 10 11 12 13
		mGaugeBar->playAnimation("gauge_4");
	}
	else {
		mGaugeBar->playAnimation("gauge_5");
	}
	mGaugeBar->setScaleX(mStartRatio);	
}

void SeasonRatingPanel::refreshRankIcon()
{
	//ranking 아이콘	
	PokerRankHelper::setRankIcon(mRankingIcon, mRankIndex);	
}

void SeasonRatingPanel::startAction()
{
	setGrade();	
	refreshRankIcon();
	refreshTxt();

	///bg 적용
	if (mGradeMode == RATING_BRONZE) {		//등급 없음 0 1 2 3 4은
		mBg->playAnimation("back_rank1");
	}
	else if (mGradeMode == RATING_SILVER) {	//4 5 6 7 
		mBg->playAnimation("back_rank2");
	}
	else if (mGradeMode == RATING_GOLD) {	// 7 8 9 10
		mBg->playAnimation("back_rank3");
	}
	else if (mGradeMode == RATING_PLATINUM) {	// 10 11 12 13
		mBg->playAnimation("back_rank4");
	}
	else {
		mBg->playAnimation("back_rank5");
	}
	mMoveFlag = true;
	int initRepute = GameDataManager::getSingleton().getBeforeRepute();
	int nextRepute = PokerRankHelper::getReputeAmount(mRankIndex + 1);
	mNowRepute->setString(StringConverter::toString(initRepute).c_str());
	mNowRepute->setInt(initRepute);
	mNowRepute->setIntAction(nextRepute, ANI_GAUGEBAR_TIME);
	mNextRepute->setString(StringConverter::toString(nextRepute).c_str());
	return;
	/*
	//게이지바 엑션 진행
	float perGaugeBar = 0.f;
	if (mGradeMode == RATING_BRONZE) {	//0 1 2 3 4
		perGaugeBar = 0.25f;
		if (mEndIndex > 4)
			mTargetActionIndex = 4;
		else
			mTargetActionIndex = mEndIndex;

	}
	else if (mGradeMode == RATING_DIA) {
		perGaugeBar = 0.50f;
		mTargetActionIndex = mEndIndex;

	}
	else  {	//4 5 6 7 
		perGaugeBar = (float)1 / (float)3;
		
		if (mGradeMode == RATING_SILVER) {	//4 5 6 7
			if (mEndIndex > 7)
				mTargetActionIndex = 7;
			else
				mTargetActionIndex = mEndIndex;
		}
		else if (mGradeMode == RATING_GOLD) {	//7 8 9 10
			if (mEndIndex > 10)
				mTargetActionIndex = 10;
			else
				mTargetActionIndex = mEndIndex;
		}
		else if (mGradeMode == RATING_PLATINUM) {	//10 11 12 13
			if (mEndIndex > 13)
				mTargetActionIndex = 13;
			else
				mTargetActionIndex = mEndIndex;
		}
	}
	
	mMoveFlag = true;
	mTargetRatio = mStartEndRatio;
	//
	//max 수치 바꾸고
	int initRepute = GameDataManager::getSingleton().getBeforeRepute();
	int nextRepute = PokerRankHelper::getReputeAmount(mRankIndex + 1);
	mNowRepute->setString(StringConverter::toString(initRepute).c_str());
	mNowRepute->setInt(initRepute);
	mNowRepute->setIntAction(nextRepute, ANI_GAUGEBAR_TIME);
	mNextRepute->setString(StringConverter::toString(nextRepute).c_str());
	//게이지바...  증가
	//하나씩 증가하고 end 가 되면
	//action 이 끝났을때 end 라면 gaugebar 남어지 증가 하고
	//target 과 end 가 같다면

	//배경 바꾸고 txt 바꾼다.
	*/
}

void SeasonRatingPanel::eventAction()
{
	mRankIndex++;
	//등급이 바뀐다.
	setGrade();

	bool isRefreshBg = false;
	if (mRankIndex == 4 || mRankIndex == 7 || mRankIndex == 10 || mRankIndex == 13)
		isRefreshBg = true;


	if (isRefreshBg)
		refreshBg();

	//refreshGaugeBar();	

	string aniStr = "rank_" + StringConverter::toString(mRankIndex - 1) + "_change";
	string nextStr = "rank_" + StringConverter::toString(mRankIndex);

	///bg 적용
	if (mGradeMode == RATING_BRONZE) {		//등급 없음 0 1 2 3 4은
		mBg->playAnimation("back_rank1");
	}
	else if (mGradeMode == RATING_SILVER) {	//4 5 6 7 
		mBg->playAnimation("back_rank2");
	}
	else if (mGradeMode == RATING_GOLD) {	// 7 8 9 10
		mBg->playAnimation("back_rank3");
	}
	else if (mGradeMode == RATING_PLATINUM) {	// 10 11 12 13
		mBg->playAnimation("back_rank4");
	}
	else {
		mBg->playAnimation("back_rank5");
	}

	mRankTitle->setString(PokerRankHelper::getRankTitleStr(mRankIndex).c_str());
	mRankTitle->setColor(StringConverter::parseColor3B(PokerRankHelper::getRankTitleColorStr(mRankIndex)));

	mRankingIcon->playAnimation(aniStr);
	mRankingIcon->appendAnimation(nextStr);

	if (mRankIndex != mEndIndex) {
		runAction(CCSequence::create(
			CCDelayTime::create(ANI_DELAY_TIME),	//애니메이션 대기 시간.
			CCCallFunc::create(this, callfunc_selector(SeasonRatingPanel::repeatAction)),
			NULL));
	}
	else {
		CCLOG("SeasonRatingPanel eventAction mTargetRatio = %f", mTargetRatio);

		if (mRankIndex == 15)
			return;

		if (mEndIndex == 4 || mEndIndex == 7 || mEndIndex == 10 || mEndIndex == 13) {
			refreshBg();
		}

		if (mTargetRatio == 1.0f)
			mTargetRatio = 0.f;

		//현제 max 값 이전 max 값
		//현제 repute 에서 이전 max 값을 뺀 것을 % 구해서 더한다.
		//max 수치 바꾸고
		int initRepute = PokerRankHelper::getReputeAmount(mRankIndex);
		int nextRepute = GameDataManager::getSingleton().getPlayerInfo().repute();
		int maxRepute = PokerRankHelper::getReputeAmount(mRankIndex + 1);
		
		int perRepute = maxRepute - initRepute;
		int myRepute = nextRepute - initRepute;
		float endRatio = (float)myRepute / (float)perRepute;

		mUserMoveFlag = true;
		if (mGradeMode == RATING_BRONZE) {		//등급 없음 0 1 2 3 4은
			endRatio = endRatio * 0.25f;
			mTargetRatio = mTargetRatio + endRatio;
		}
		else if (mGradeMode == RATING_SILVER) {	//4 5 6 7 
			endRatio = endRatio * (float)1 / (float)3;
			mTargetRatio = mTargetRatio + endRatio;
		}
		else if (mGradeMode == RATING_GOLD) {	// 7 8 9 10
			endRatio = endRatio * (float)1 / (float)3;
			mTargetRatio = mTargetRatio + endRatio;
		}
		else if (mGradeMode == RATING_PLATINUM) {	// 10 11 12 13
			endRatio = endRatio * (float)1 / (float)3;
			mTargetRatio = mTargetRatio + endRatio;
		}
		else {
			endRatio = endRatio * 0.50f;
			mTargetRatio = mTargetRatio + endRatio;
		}
		
		CCLOG("eventAction mEndUserRatio = %f", mEndUserRatio);
		CCLOG("eventAction mTargetRatio = %f", mTargetRatio);
		CCLOG("eventAction endRatio = %f", endRatio);

		
		mNowRepute->setString(StringConverter::toString(initRepute).c_str());
		mNowRepute->setInt(initRepute);
		mNowRepute->setIntAction(nextRepute, ANI_GAUGEBAR_TIME);
		mNextRepute->setString(StringConverter::toString(maxRepute).c_str());
	}
}

void SeasonRatingPanel::refreshBg()
{
	//배경
	
	if (mGradeMode == RATING_SILVER) {	//4 5 6 7 
		mBg->playAnimation("back_rank1_change");		
	}
	else if (mGradeMode == RATING_GOLD) {	// 7 8 9 10
		mBg->playAnimation("back_rank2_change");		
	}
	else if (mGradeMode == RATING_PLATINUM) {	// 10 11 12 13
		mBg->playAnimation("back_rank3_change");		
	}
	else {
		mBg->playAnimation("back_rank4_change");		
	}

	//게이지바
	//스타트 게이지바
	if (mGradeMode == RATING_BRONZE) {		//등급 없음 0 1 2 3 4은
		mGaugeBar->playAnimation("gauge_1");
	}
	else if (mGradeMode == RATING_SILVER) {	//4 5 6 7 
		mGaugeBar->playAnimation("gauge_2");
	}
	else if (mGradeMode == RATING_GOLD) {	// 7 8 9 10
		mGaugeBar->playAnimation("gauge_3");
	}
	else if (mGradeMode == RATING_PLATINUM) {	// 10 11 12 13
		mGaugeBar->playAnimation("gauge_4");
	}
	else {
		mGaugeBar->playAnimation("gauge_5");
	}

	//글자 색깔 바꾼다. & 글씨 내용 바꾼다.
	refreshTxt();
	

	mStartRatio = 0.f;
	mGaugeBar->setScaleX(mStartRatio);
}

bool SeasonRatingPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	LayerManager::getSingleton().popLayer(this);
	return true;
}

void SeasonRatingPanel::setGrade()
{
	if (mRankIndex < 4) {			//등급 없음 0 1 2 3 4은
		mGradeMode = RATING_BRONZE;
	}
	else if (mRankIndex < 7) {		//4 5 6 7 
		mGradeMode = RATING_SILVER;
	}
	else if (mRankIndex < 10) {	// 7 8 9 10
		mGradeMode = RATING_GOLD;
	}
	else if (mRankIndex < 13) {	// 10 11 12 13
		mGradeMode = RATING_PLATINUM;
	}
	else if (mRankIndex < 15) {	//14 15
		mGradeMode = RATING_DIA;	// 13 14 1t5 16
	}	
	else {
		mGradeMode = RATING_END;	// 13 14 1t5 16
	}
}

void SeasonRatingPanel::update(float delta)
{
	if (mMoveFlag) {
		if (mStartRatio >= 1.0f) {
			++mStartIndex;
			mRankIndex = mStartIndex;
			mStartRatio = 0.f;
			if (mStartIndex == mEndIndex) {
				mMoveFlag = false;
				mUserMoveFlag = true;

				int initRepute = PokerRankHelper::getReputeAmount(mRankIndex);
				int nextRepute = GameDataManager::getSingleton().getPlayerInfo().repute();
				int maxRepute = PokerRankHelper::getReputeAmount(mRankIndex + 1);
				if (maxRepute == -1)
					maxRepute = PokerRankHelper::getReputeAmount(mRankIndex);

				int perRepute = maxRepute - initRepute;
				int myRepute = nextRepute - initRepute;
				
				if (PokerRankHelper::getReputeAmount(mRankIndex + 1) == -1) {
					mTargetRatio = 1.f;
					mStartRatio = 1.f;
				}
				else {
					mTargetRatio = (float)myRepute / (float)perRepute;
					if (mTargetRatio > 1.0f)
						mTargetRatio = 1.0f;
				}
				
			}			
			
			setGrade();
			refreshRankIcon();
			refreshTxt();
			bool isRefreshBg = false;
			if (mRankIndex == 4 || mRankIndex == 7 || mRankIndex == 10 || mRankIndex == 13)
				isRefreshBg = true;
			if (isRefreshBg)
				refreshBg();
		}
		else {
			mStartRatio += 0.01f;
			CCLOG("update mMoveFlag mStartRatio = %f", mStartRatio);
			mGaugeBar->setScaleX(mStartRatio);
		}
	}

	if (mUserMoveFlag) {
		mStartRatio += 0.01f;		
		CCLOG("update mUserMoveFlag mStartRatio = %f", mStartRatio);
		CCLOG("update mUserMoveFlag mStartRatio = %f", mStartRatio);
		if (mStartRatio >= mTargetRatio) {
			mStartRatio = mTargetRatio;
			mUserMoveFlag = false;			
		}
		mGaugeBar->setScaleX(mStartRatio);
	}
	return;
	if (mMoveFlag) {
		mStartRatio += 0.01f;		
		mGaugeBar->setScaleX(mStartRatio);
		if (mStartRatio >= mTargetRatio) {
			mStartRatio = mTargetRatio;
			mMoveFlag = false;
			CCLOG("mStartRatio = %f", mStartRatio);
			mGaugeBar->setScaleX(mStartRatio);
			eventAction();
		}
	}

	if (mUserMoveFlag) {
		CCLOG("mTargetRatio = %f", mTargetRatio);
		mStartRatio += 0.01f;
		mGaugeBar->setScaleX(mStartRatio);
		if (mStartRatio >= mTargetRatio) {
			mStartRatio = mTargetRatio;
			mUserMoveFlag = false;			
			mGaugeBar->setScaleX(mStartRatio);			
		}
	}
}

void SeasonRatingPanel::repeatAction()
{
	//게이지바 엑션 진행
	float perGaugeBar = 0.f;
	if (mGradeMode == RATING_BRONZE) {	//0 1 2 3 4
		perGaugeBar = 0.25f;
		if (mEndIndex > 4)
			mTargetActionIndex = 4;
		else
			mTargetActionIndex = mEndIndex;

	}
	else if (mGradeMode == RATING_DIA) {
		perGaugeBar = 0.50f;
		mTargetActionIndex = mEndIndex;

	}
	else  {	//4 5 6 7 
		perGaugeBar = (float)1 / (float)3;

		if (mGradeMode == RATING_SILVER) {	//4 5 6 7
			if (mEndIndex > 7)
				mTargetActionIndex = 7;
			else
				mTargetActionIndex = mEndIndex;
		}
		else if (mGradeMode == RATING_GOLD) {	//7 8 9 10
			if (mEndIndex > 10)
				mTargetActionIndex = 10;
			else
				mTargetActionIndex = mEndIndex;
		}
		else if (mGradeMode == RATING_PLATINUM) {	//10 11 12 13
			if (mEndIndex > 13)
				mTargetActionIndex = 13;
			else
				mTargetActionIndex = mEndIndex;
		}
	}

	mMoveFlag = true;
	mTargetRatio = mStartRatio + perGaugeBar;
	if (mStartAniRatio > 0.f) {
		mTargetRatio -= mStartAniRatio;
		mStartAniRatio = 0.f;
	}
	//
	//max 수치 바꾸고
	int initRepute = PokerRankHelper::getReputeAmount(mRankIndex);
	int nextRepute = PokerRankHelper::getReputeAmount(mRankIndex + 1);
	mNowRepute->setString(StringConverter::toString(initRepute).c_str());
	mNowRepute->setInt(initRepute);
	mNowRepute->setIntAction(nextRepute, ANI_GAUGEBAR_TIME);
	mNextRepute->setString(StringConverter::toString(nextRepute).c_str());
	//게이지바...  증가
	//하나씩 증가하고 end 가 되면
	//action 이 끝났을때 end 라면 gaugebar 남어지 증가 하고
	//target 과 end 가 같다면

	//배경 바꾸고 txt 바꾼다.
}

void SeasonRatingPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}
