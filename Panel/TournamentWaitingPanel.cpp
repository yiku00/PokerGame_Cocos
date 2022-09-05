#include "pch.h"
#include "TournamentWaitingPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"

TournamentWaitingPanel::TournamentWaitingPanel()
{
	initPanel();		
}

TournamentWaitingPanel::~TournamentWaitingPanel()
{
	
}

void TournamentWaitingPanel::initPanel()
{
	construct(getMxmlPath() + "dmy_guide_bar.mxml");	
	mIcon = getSkel("skel_stay_mark");
	mIcon->playAnimation("stay" , true);
	mDesc = getLabel("txt_guide");
	mDesc->setString(GameStringDepot::getSingleton().getString("TXT_STAY_TIME").c_str());
	mBg = getSkel("skel_guidebar");
	mBg->playAnimation("guidebar1_start");
	mBg->appendAnimation("guidebar1_loop");
	getLabel("txt_rank_sum1")->setVisible(false);
	getLabel("txt_rank_sum2")->setVisible(false);
	getLabel("txt_rank_sum3")->setVisible(false);
}

void TournamentWaitingPanel::closePanel(bool isAni /*= false*/)
{
	if (isAni) {
		runAction(CCSequence::create(
			CCFadeOut::create(0.3f),
			CCCallFunc::create(this, callfunc_selector(TournamentWaitingPanel::popPanel)),
			NULL));
	}
	else {
		popPanel();
	}
}

//void TournamentWaitingPanel::closePanel(int LastRound, bool isAni /*= false*/)
//{
//	if (isAni) {
//		runAction(CCSequence::create(
//			CCFadeOut::create(0.1f), //NZ 0.3인거 일부로 확인하기 위해 바꿔줌
//			CCCallFunc::create(this, callfunc_selector(TournamentWaitingPanel::popPanel)),
//			NULL));
//	}
//	else {
//		runAction(CCSequence::create(
//			CCFadeOut::create(0.1f),
//			CCCallFunc::create(this, callfunc_selector(TournamentWaitingPanel::popPanel)),
//			NULL));
//
//
//	}
//}

void TournamentWaitingPanel::popPanel()
{
	LayerManager::getSingleton().popLayer(this);
}

void TournamentWaitingPanel::setDesc(string desc)
{
	mDesc->setString(desc.c_str());
}
