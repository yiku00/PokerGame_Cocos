#include "pch.h"
#include "InGameLoadingPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"

#define LIMIT_CARD_GRADE 5
#define TIP_MAX_COUNT 16
#define LIMIT_CARDID 10000

InGameLoadingPanel::InGameLoadingPanel(LoadingType type)
{	
	mType = type;
	construct(getMxmlPath() + "wnd_download_page.mxml");
	mGauseBar = getImage("skel_gauge1");
	mGauseBar->setAnchorPoint(ccp(0.f, 0.5f));
	mGauseBar->setPositionX(mGauseBar->getPositionX() - getDummy("skel_gauge1").size.width / 2.0f);
	mGauseBar->setScaleX(0.f);	
}

InGameLoadingPanel::~InGameLoadingPanel()
{	

}

void InGameLoadingPanel::setGaugeRatio( float ratio )
{
	if (mType == LoadingType::LOADING_RANDOM){
		if (ratio > 1.f)
			ratio = 1.f;

		mGauseBar->setScaleX(ratio);
	}
	else{

	}
	//mProgressAni->setPositionX(mStartPositionX + getDummy("sam_loadGage").size.width * ratio);
}
