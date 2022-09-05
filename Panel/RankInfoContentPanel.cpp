#include "pch.h"
#include "RankInfoContentPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "PokerRankHelper.h"
#include "LobbyRankRewardPanel.h"
#include "PanelHelper.h"


RankInfoContentPanel::RankInfoContentPanel(RANK_INFO_TYPE type)
{
	initPanel();
	refresh();
}

RankInfoContentPanel::~RankInfoContentPanel()
{

}

void RankInfoContentPanel::onClicked(const string& name)
{
	if (name == "sbtn_move") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushVipInfoPanel();		
	}
}

void RankInfoContentPanel::initPanel()
{
	construct(getMxmlPath() + "dmy_season_rank.mxml");
	mRankTitleLabel = getLabel("str_rank_name");
	mRankLabel = getLabel("txt_total_number");
	mMyRankLabel = getLabel("txt_my_fame"); 
	mMaxRankLabel = getLabel("txt_total_fame");
	mGaugeBg = getImage("skel_gaugebar");
	mGaugeBar = getImage("skel_gauge");
	mGaugeBar->setAnchorPoint(ccp(0.f, 0.5f));
	mGaugeBar->setPositionX(mGaugeBar->getPositionX() - getDummy("skel_gauge").size.width / 2.0f);

	mRankIcon = getSkel("skel_rankicon");	
	CCPoint pos = getDummy("dmy_button_lsmall").origin;
	pos.y = -pos.y;
	Panel* pPanel = new Panel();
	pPanel->construct(getMxmlPath() + "dmy_button_lsmall.mxml");
	addChild(pPanel);
	pPanel->release();
	pPanel->setPosition(pos);
	mMoveBtn = pPanel->getButton("sbtn_button");
	mMoveBtn->setListener(this);
	mMoveBtn->setName("sbtn_move");
	mMoveBtn->setType(Button::NoPressImg);
	mMovebtnLabel = pPanel->getLabel("txt_button");
	mMovebtnUnderLabel = pPanel->getLabel("txt_button_under");
	mMovebtnLabel->setString(GameStringDepot::getSingleton().getString("MEMBER_GO_INFO_BTN").c_str());
	mMovebtnUnderLabel->setString(GameStringDepot::getSingleton().getString("MEMBER_GO_INFO_BTN").c_str());

}

void RankInfoContentPanel::refresh()
{
	float rankRatio = PokerRankHelper::getRankRatio();
	string rankStr = "";
	if (rankRatio == 0.f)
		rankStr = GameStringDepot::getSingleton().getString("RankInfoContentPanel_NO_DATA");
	else
		rankStr = NxGetFormatString(GameStringDepot::getSingleton().getString("RANK_GRADE_UPPER"), PokerRankHelper::getRankRatio());
	mRankLabel->setString(rankStr.c_str());
	mGaugeBar->setScaleX(PokerRankHelper::getRatioRepute());
	mMyRankLabel->setString(StringConverter::toString(PokerRankHelper::getNowRepute()).c_str());
	string maxStr = "";
	if (PokerRankHelper::getLevelupRepute() == -1)
		maxStr = "/ MAX";
	else
		maxStr = "/" + StringConverter::toString(PokerRankHelper::getLevelupRepute());
	mMaxRankLabel->setString(maxStr.c_str());	
	//랭킹 표시
	PokerRankHelper::setRankIcon(mRankIcon, PokerRankHelper::getRank());
	//랭킹 타이틀 표시
	mRankTitleLabel->setString(PokerRankHelper::getRankTitleStr(PokerRankHelper::getRank()).c_str());
	mRankTitleLabel->setColor(StringConverter::parseColor3B(PokerRankHelper::getRankTitleColorStr(PokerRankHelper::getRank())));
	
}
