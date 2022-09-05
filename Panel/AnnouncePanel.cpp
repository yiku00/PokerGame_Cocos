#include "pch.h"
#include "AnnouncePanel.h"
#include "HeroUtil.h"

#define WATING_TIME 3.0f
#define REMOVE_TIME 1.0f

AnnouncePanel::AnnouncePanel()
{
	initPanel();
	removeAction();
}

AnnouncePanel::~AnnouncePanel()
{
	
}

void AnnouncePanel::setDesc(string desc)
{
	mDesc->setString(desc.c_str());
}

void AnnouncePanel::initPanel()
{
	construct(getMxmlPath() + "dmy_noticeboard.mxml");
	mDesc = getLabel("txt_info");	
}

void AnnouncePanel::removeAction()
{
	runAction(CCSequence::create(
		CCDelayTime::create(WATING_TIME),	//애니메이션 대기 시간.
		CCFadeOut::create(REMOVE_TIME),	//애니메이션 대기 시간.
		CCCallFunc::create(this, callfunc_selector(AnnouncePanel::closePanel)),
		NULL));	
}

void AnnouncePanel::closePanel()
{
	LayerManager::getSingleton().popLayer(this);
}

