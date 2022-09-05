#include "pch.h"
#include "LobbyTourRewardContentPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"


LobbyTourRewardContentPanel::LobbyTourRewardContentPanel()
{
	InitPanel();
}

LobbyTourRewardContentPanel::~LobbyTourRewardContentPanel()
{

}

void LobbyTourRewardContentPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_tournament_round_slot.mxml");
	mGrade = getLabel("txt_grade");
	mGradeUnder = getLabel("txt_grade_under");
	mPayMoney = getLabel("txt_pay");
	mTrophy = getLabel("txt_score");	

	mWindow = getSkel("skel_main_back");
}

void LobbyTourRewardContentPanel::setRewardData(int grade, int64 paymoney, int trophy)
{
	string gradeStr = StringConverter::toString(grade + 1) + GameStringDepot::getSingleton().getString("TXT_RANK");
	mGrade->setString(gradeStr.c_str());
	mGradeUnder->setString(gradeStr.c_str());

	string _goldTxt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(paymoney), 2);
	mPayMoney->setString(_goldTxt.c_str());

	mTrophy->setString(StringConverter::toString(trophy).c_str());

	string windowAniStr = "";
	string underColorStr = "";

	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		underColorStr = "940707";
		windowAniStr = "grade_back_seven";
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		underColorStr = "00238C";
		windowAniStr = "grade_back_highlow";
		break;
	case GameKind::GAMEKIND_BADUKI:
		underColorStr = "198a03";
		windowAniStr = "grade_back_badugi";
		break;
	case GameKind::GAMEKIND_HOLDEM:
		underColorStr = "038a6c";
		windowAniStr = "grade_back_texas";
		break;
	}	
	mGradeUnder->setColor(StringConverter::parseColor3B(underColorStr));
	mWindow->playAnimation(windowAniStr.c_str());
}
