#pragma once
/********************************************************************
file name:	SeasonRatingPanel.h

purpose:	SeasonRatingPanel 등급업할때 보여주는 창
*********************************************************************/
#include "NxFramework.h"
#include "W_TourRatingUpInfo.pb.h"

class SeasonRatingPanel : public Panel
{
	enum RATING_GRADE {
		RATING_BRONZE,		//0 1 2 3 4
		RATING_SILVER,		//4 5 6 7
		RATING_GOLD,		//7 8 9 10
		RATING_PLATINUM,	//10 11 12 13
		RATING_DIA,			//14 15
		RATING_END,		//16끝 없다
	};

public:
	SeasonRatingPanel();
	virtual ~SeasonRatingPanel();

public:
	virtual void update(float delta);
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnter() override;

private:
	void initPanel();
	void initData();
	void startAction();	//애니 진행
	void repeatAction();
	void eventAction();	//완료 됐을때 액션	
	void refreshTxt();	//글자
	void refreshGaugeBar();
	void refreshRankIcon();
	void refreshBg();
	void setGrade();	
	


private:
	int mStartIndex;	//시작시 grade
	int mEndIndex;	//마지막 인덱스
	float nowRatio;	//
	float mStartRatio;
	int mRankIndex;

	int mStartActionIndex;
	int mTargetActionIndex;
	W_TourRatingUpInfo mRatingUpInfo;

	SkelObject* mBg;
	SkelObject* mRankingIcon;
	SkelObject* mRankingIconBg;
	Nx::Label* mGradeFirst1;		//등급 없음 에서 실버3
	Nx::Label* mGradeFirst2;
	Nx::Label* mGradeFirst3;
	Nx::Label* mGradeFirst4;
	Nx::Label* mGradeFirst5;

	Nx::Label* mGradeSecond1;		//실버3 에서 골드 까지 위치
	Nx::Label* mGradeSecond2;
	Nx::Label* mGradeSecond3;
	Nx::Label* mGradeSecond4;

	Nx::Label* mGradeThird1;		//다이아는 2단계다
	Nx::Label* mGradeThird2;
	Nx::Label* mGradeThird3;

	SkelObject* mGaugeBar;
	RATING_GRADE mGradeMode;

	Nx::Label* mNowRepute;
	Nx::Label* mSlash;
	Nx::Label* mNextRepute;

	int mNowGrade;
	int mMaxGrade;

	bool mMoveFlag;
	float mTargetRatio;

	Nx::Label* mRankTitle;

	float mStartUserRatio;
	float mEndUserRatio;

	bool mUserMoveFlag;	//다 돋달했고, 유저 raion 만큰 더 이동한다.
	float mStartAniRatio;
	float mStartEndRatio;
};
