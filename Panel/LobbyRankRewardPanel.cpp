#include "pch.h"
#include "LobbyRankRewardPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PokerResourceHelper.h"

LobbyRankRewardPanel::LobbyRankRewardPanel()
{
	_init();
}

LobbyRankRewardPanel::~LobbyRankRewardPanel()
{

}

void LobbyRankRewardPanel::_init()
{
	Panel* panel = new Panel();
	addChild(panel);
	panel->release();
	addMouseBlockPanel(panel, true);
	panel->construct(getMxmlPath() + "dmy_week_rank.mxml");
	panel->setButtonListener(this);
	CCSize contentSize = panel->getContentSize();
	panel->setPositionY(contentSize.height - DESIGN_HEIGHT - contentSize.height / 2.f);
	panel->setPositionX(-contentSize.width / 2.f);
	panel->setContentSize(contentSize);
	this->setContentSize(contentSize);
	this->setPositionX(DESIGN_WIDTH / 2);
	this->setPositionY(DESIGN_HEIGHT / 2);
	mCloseBtn = panel->getButton("sbtn_cancel");
	mTimeLimitLabel = panel->getLabel("txt_timelimit");
	string titleStr = GameStringDepot::getSingleton().getString("LobbyRankRewardPanel_TITLE");
	mTitle = panel->getLabel("txt_title");
	mTitleUnder = panel->getLabel("txt_title_under");
	mTitle->setString(titleStr.c_str());
	mTitleUnder->setString(titleStr.c_str());	
	string dmyStr = "";
	for (int i = 0; i < 16; i++)
	{
		dmyStr = "dmy_weekplay_table" + StringConverter::toString(i + 1);
		LobbyRankRewardContentPanel* contentPanel = new LobbyRankRewardContentPanel(i);
		panel->addChild(contentPanel);
		contentPanel->release();
		contentPanel->setPosition(panel->getImage(dmyStr)->getPosition());
		mContents.push_back(contentPanel);
	}		

	//남은시간
	panel->getLabel("txt_time")->setString(GameStringDepot::getSingleton().getString("LobbyRankRewardPanel_TIME_TITLE").c_str());
	panel->getLabel("txt_bottommessage")->setString(GameStringDepot::getSingleton().getString("LobbyRankRewardPanel_DESC").c_str());
}

void LobbyRankRewardPanel::onClicked(const string& buttonName)
{
	if (buttonName == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
}

void LobbyRankRewardPanel::update(float delta)
{
	W_TourOfInfo* tourOfInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	string timeFormatStr = PokerResourceHelper::getPeroidDesc(tourOfInfo->endlefttime());	
	mTimeLimitLabel->setString(timeFormatStr.c_str());
}
void LobbyRankRewardPanel::onEnter()
{
	Panel::onEnter();

	scheduleUpdate();
}