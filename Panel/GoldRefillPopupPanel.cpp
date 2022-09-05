#include "pch.h"
#include "GoldRefillPopupPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "SceneUtil.h"
#include "PanelHelper.h"


GoldRefillPopupPanel::GoldRefillPopupPanel()
{
	initPanel();
}

GoldRefillPopupPanel::~GoldRefillPopupPanel()
{

}

void GoldRefillPopupPanel::onClicked(const string& name)
{
	if (name == getButtonName(mCloseBtn)) {
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == "CANCEL") {
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == "REFILL_GOLD") {
		WebService::getSingletonPtr()->_sendFreeRefillReq();
		LayerManager::getSingletonPtr()->popLayer(this);
	}
	else if (name == "GO_BIGPOT") {
		PanelHelper::pushBigBonusPanel();
	}
	else if (name == "GO_FREEREFIL") {
		PanelHelper::pushFreeMoviePanel();
	}
	else if (name == "GO_MINEGAME") {
		LayerManager::getSingletonPtr()->popLayer(this);
		SceneUtil::changeScene(SceneUtil::SceneMinigame);
	}
}

void GoldRefillPopupPanel::initPanel()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_checkboard_refil.mxml");
	setButtonListener(this);
	mCloseBtn = getButton("sbtn_cancel");
	mRefillDesc = getLabel("txt_checktext2");

	//취소
	CCPoint _btnPos = getDummy("dmy_button_small1").origin;
 	mRefillGoPanel = new SmallButtonPanel(SmallButtonPanel::LOBBY_FRIEND_TYPE);
 	mRefillGoPanel->setPositionX(_btnPos.x);
 	mRefillGoPanel->setPositionY(-_btnPos.y);
 	mRefillGoPanel->SetButtonListener(this);
 	addChild(mRefillGoPanel);
 	mRefillGoPanel->release();

	_btnPos = getDummy("dmy_button_small2").origin;
	mGoBigChancePanel = new SmallButtonPanel(SmallButtonPanel::LOBBY_FRIEND_TYPE);
	mGoBigChancePanel->setPositionX(_btnPos.x);
	mGoBigChancePanel->setPositionY(-_btnPos.y);
	mGoBigChancePanel->SetButtonListener(this);
	addChild(mGoBigChancePanel);
	mGoBigChancePanel->release();

	_btnPos = getDummy("dmy_button_small3").origin;
	mFreeRefillPanel = new SmallButtonPanel(SmallButtonPanel::LOBBY_FRIEND_TYPE);
	mFreeRefillPanel->setPositionX(_btnPos.x);
	mFreeRefillPanel->setPositionY(-_btnPos.y);
	mFreeRefillPanel->SetButtonListener(this);
	addChild(mFreeRefillPanel);
	mFreeRefillPanel->release();

	_btnPos = getDummy("dmy_button_small4").origin;
	mGoMiniPanel = new SmallButtonPanel(SmallButtonPanel::LOBBY_FRIEND_TYPE);
	mGoMiniPanel->setPositionX(_btnPos.x);
	mGoMiniPanel->setPositionY(-_btnPos.y);
	mGoMiniPanel->SetButtonListener(this);
	addChild(mGoMiniPanel);
	mGoMiniPanel->release();


	mRefillGoPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_OK_LABEL"));
	mRefillGoPanel->m_Button->setName("REFILL_GOLD"); 

	//이동가능한 곳
	mGoBigChancePanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("GoldRefillRemainMoveBigPot"));
	mGoBigChancePanel->m_Button->setName("GO_BIGPOT");
	mFreeRefillPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("GoldRefillRemainMoveFreeRefil"));
	mFreeRefillPanel->m_Button->setName("GO_FREEREFIL");
	mGoMiniPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("GoldRefillRemainMoveMiniGame"));
	mGoMiniPanel->m_Button->setName("GO_MINEGAME");
	refreshTodayRefill();
}

void GoldRefillPopupPanel::refreshData()
{
	refreshTodayRefill();
}

void GoldRefillPopupPanel::refreshTodayRefill()
{
	int32 _RefillCount = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_FreeRefillCount;
	int32 maxRefill = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().free_refill_daily_count();
	string descStr = NxGetFormatString(GameStringDepot::getSingleton().getString("GoldRefillRemainDesc"), _RefillCount, maxRefill);
	mRefillDesc->setString(descStr.c_str());
}

void GoldRefillPopupPanel::onRefresh()
{
	setVisible(true);
	refreshTodayRefill();
}
