#include "pch.h"
#include "GameWinPanel.h"
#include "HeroApp.h"
#include "HeroUtil.h"

GameWinPanel::GameWinPanel(PANEL_KINDS type)
{
	mKinds = type;
	initPanel();
}

GameWinPanel::~GameWinPanel()
{
	
}

void GameWinPanel::setResult(string str)
{
	mResultLabel->setString(str.c_str());
}

void GameWinPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	if (mKinds == PANEL_MY_RESULT) {
		mMainPanel->construct(getMxmlPath() + "dmy_my_panel_winner.mxml");
	}
	else if (mKinds == PANEL_ENEMY_RESULT) {
		mMainPanel->construct(getMxmlPath() + "dmy_panel_winner.mxml");
	}
	else if (mKinds == PANEL_ENEMY_HOLDEM_RESULT) {
		mMainPanel->construct(getMxmlPath() + "dmy_tex_panel_winner.mxml");
	}
	CCSize contentSize = mMainPanel->getContentSize();	
	mMainPanel->setPositionY(contentSize.height - DESIGN_HEIGHT - contentSize.height / 2.f);
	mMainPanel->setPositionX(-contentSize.width / 2.f);
	mMainPanel->setContentSize(contentSize);
	this->setContentSize(contentSize);

	mWinImg = mMainPanel->getSkel("skel_winnerimg");
	mResultLabel = mMainPanel->getLabel("txt_getgold");
}

SkelObject* GameWinPanel::getWinSkel()
{
	return mWinImg;
}
