#include "pch.h"
#include "SeasonRankInfoPanel.h"
#include "HeroUtil.h"
#include "PanelHelper.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"

#define TOTAL_RANK 15

SeasonRankInfoPanel::SeasonRankInfoPanel()
{
	initPanel();
	initData();
}

SeasonRankInfoPanel::~SeasonRankInfoPanel()
{
	//destruct();
}

void SeasonRankInfoPanel::initPanel()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_season_rankinfo.mxml");
	setButtonListener(this);
	mCloseBtn = getButton("sbtn_cancel");
	mVipInfoBtn = getButton("sbtn_button");
	mTitle = getLabel("txt_title");
	//시즌 등급 보상
	getLabel("txt_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("SeasonRankInfoPanel_TITLE").c_str());
	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("SeasonRankInfoPanel_TITLE").c_str());
	//vip혜택 보기
	getLabel("txt_button_under")->setString(GameStringDepot::getSingletonPtr()->getString("SeasonRankInfoPanel_VIP_INFO").c_str());
	getLabel("txt_button")->setString(GameStringDepot::getSingletonPtr()->getString("SeasonRankInfoPanel_VIP_INFO").c_str());
}

void SeasonRankInfoPanel::onClicked(const string& name)
{
	if (name == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == getButtonName(mVipInfoBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushVipInfoPanel();
	}
}

void SeasonRankInfoPanel::initData()
{
	CCSize originSize = getDummy("skel_rankicon1").size;
	CCSize iconSize = getDummy("dmy_rankicon1").size;
	float scale = getScaleFit(originSize, iconSize);

	//titie 
	for (int i = 0; i < TOTAL_RANK; i++)
	{
		//아이콘
		int labelIndex = TOTAL_RANK - i - 1;
		string iconStr = "rank_" + StringConverter::toString(labelIndex + 1);
		string skelStr = "skel_rankicon" + StringConverter::toString(labelIndex + 1);		//1부터 시작
		getSkel(skelStr)->playAnimation(iconStr);
		getSkel(skelStr)->setScale(scale);
		//타이틀 이름
		string titleGameStr = "RANK_GRADE_TXT_" + StringConverter::toString(labelIndex + 1);
		string titleStr = "txt_rank" + StringConverter::toString(labelIndex + 1);
		getLabel(titleStr)->setString(GameStringDepot::getSingleton().getString(titleGameStr).c_str());	//1브타 시작
		//점수		
		string labelStr = NxGetFormatString(GameStringDepot::getSingleton().getString("SEASON_RANK_REPUTE_DATA"), getReputeAmount(labelIndex + 1));
		string pointStr = "txt_score" + StringConverter::toString(labelIndex + 1);
		getLabel(pointStr)->setString(labelStr.c_str());	//1브타 시작
		string vipStr = "txt_vip" + StringConverter::toString(labelIndex + 1);
		string vipInfoStr = NxGetFormatString(GameStringDepot::getSingleton().getString("SEASON_RANK_REPUTE_VIP"), labelIndex + 1);
		getLabel(vipStr)->setString(vipInfoStr.c_str());
	}	
}

int SeasonRankInfoPanel::getReputeAmount(int repute)
{
	int size = GameDataManager::getSingleton().GetGameDataPtr()->reputedata_size();
	for (int i = 0; i < size; i++)
	{
		if (GameDataManager::getSingleton().GetGameDataPtr()->reputedata(i).rating() == repute) {
			return GameDataManager::getSingleton().GetGameDataPtr()->reputedata(i).amount();
		}
	}
	return -1;
}

