#include "pch.h"
#include "TournamentSeedUpPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"

TournamentSeedUpPanel::TournamentSeedUpPanel(int64 seedMoney, bool isMax)
{
	initPanel();	
	mIcon->playAnimation("bet_up", true);
	if (isMax)
		mDesc->setString(GameStringDepot::getSingleton().getString("TXT_MAX_SEED").c_str());
	else {
		string msgText = NxGetFormatString(GameStringDepot::getSingleton().getString("TournamentSeedUpPanel_DESC"), GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(seedMoney)));
		mDesc->setString(msgText.c_str());
	}	

	addActionClose();
}

TournamentSeedUpPanel::TournamentSeedUpPanel(string ani, string desc)
{
	initPanel();
	mIcon->playAnimation(ani, true);
	mDesc->setString(GameStringDepot::getSingleton().getString("TXT_ROOM_REARRANGE").c_str());
	addActionClose();
}

TournamentSeedUpPanel::~TournamentSeedUpPanel()
{
	
}

void TournamentSeedUpPanel::initPanel()
{
	construct(getMxmlPath() + "dmy_guide_bar.mxml");	
	mIcon = getSkel("skel_stay_mark");	
	mDesc = getLabel("txt_guide");	
	mBg = getSkel("skel_guidebar");
	mBg->playAnimation("guidebar1_start");
	mBg->appendAnimation("guidebar1_loop");
	getLabel("txt_rank_sum1")->setVisible(false);
	getLabel("txt_rank_sum2")->setVisible(false);
	getLabel("txt_rank_sum3")->setVisible(false);
}

void TournamentSeedUpPanel::closePanel()
{
	LayerManager::getSingleton().popLayer(this);
}

void TournamentSeedUpPanel::addActionClose()
{
	runAction(CCSequence::create(
		CCFadeIn::create(0.1f),
		CCDelayTime::create(2.f),
		CCFadeOut::create(0.1f),
		CCCallFunc::create(this, callfunc_selector(TournamentSeedUpPanel::closePanel)),
		NULL));
}

