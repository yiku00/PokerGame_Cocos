#include "pch.h"
#include "LobbyRecordPanel.h"

#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "LobbyTopUiPanel.h"
#include "GameDataManager.h"
#include "LobbyUIPanel.h"


LobbyRecordPanel::LobbyRecordPanel()
{
	mRecordRankPanel = nullptr;
	mRecordWorldTourPanel = nullptr;
	mRecordTurmentPanel = nullptr;
	mRecordSurvivalPanel = nullptr;
	_init();
}

LobbyRecordPanel::~LobbyRecordPanel()
{

}

void LobbyRecordPanel::initPanel()
{

}

void LobbyRecordPanel::refreshListBtn()
{
	for (int i = 0; i < mTabButtons.size(); i++)
	{
		if (i == mTapIndex) {
			mTabButtons[i]->SetBtnOnOff(true);
		}
		else {
			mTabButtons[i]->SetBtnOnOff(false);
		}
	}
}

void LobbyRecordPanel::_init()
{
	mTapIndex = 0;
	Panel* panel = addMouseBlockPanel(this, true);
	panel->setContentSize(CCSize(DESIGN_WIDTH, DESIGN_HEIGHT - 72));

	construct(getMxmlPath() + "dmy_record.mxml");
	initTab();
	initPanel();
}

void LobbyRecordPanel::initTab()
{
	for (int _i = 0; _i < 4; _i++)
	{
		CCPoint _tapBtnPos = getDummy("dmy_button_tab" + StringConverter::toString(_i + 1)).origin;
		TabButtonPanel* tapButtonPanel = new TabButtonPanel();
		tapButtonPanel->setPositionX(_tapBtnPos.x);
		tapButtonPanel->setPositionY(-_tapBtnPos.y);
		addChild(tapButtonPanel);
		tapButtonPanel->release();
		tapButtonPanel->SetButtonListener(this);
		tapButtonPanel->m_Button->setName("TAP_BUTTON" + StringConverter::toString(_i + 1));
		mTabButtons.push_back(tapButtonPanel);
	}
	mTabButtons[0]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_RECORD_RANK"));
	mTabButtons[1]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_RECORD_WORLDTOUR"));
	mTabButtons[2]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_RECORD_TOURMENT"));
	mTabButtons[3]->SetButtonText(GameStringDepot::getSingletonPtr()->getString("TXT_RECORD_SURVIVAL"));
}

void LobbyRecordPanel::onClicked(const string& buttonName)
{
	if (buttonName.find("TAP_BUTTON") != string::npos){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
		int idx = nxExtractInt(buttonName, "TAP_BUTTON") - 1;
		mTapIndex = idx;		
		refresh();
	}
}

void LobbyRecordPanel::HidePanel()
{
	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MAIN);
		}
	}
	LayerManager::getSingleton().popLayer("LobbyRecord");
	GameDataManager::getSingletonPtr()->FreeUiProcess();
}

void LobbyRecordPanel::showPanel()
{
	mTapIndex = 0;
	//record 랭킹 초기화해서 다시 받아오게 한다. pop 됐다가 push 될때 랭킹 갱신 시키려고
	if (mRecordRankPanel != nullptr) {
		mRecordRankPanel->clearRankData();
	}

	refresh();
}

void LobbyRecordPanel::refresh()
{
	refreshListBtn();
	refreshPanel();
}

void LobbyRecordPanel::refreshPanel()
{
	if (mTapIndex == 0) {	//랭킹
		if (mRecordRankPanel == nullptr) {
			addRankPanel();
		}
		mRecordRankPanel->setActivate(true);

		if (mRecordWorldTourPanel) {
			mRecordWorldTourPanel->setActivate(false);
		}

		if (mRecordTurmentPanel) {
			mRecordTurmentPanel->setActivate(false);
		}

		if (mRecordSurvivalPanel) {
			mRecordSurvivalPanel->setActivate(false);
		}
	}
	else if (mTapIndex == 1) {
		if (mRecordRankPanel) {
			mRecordRankPanel->setActivate(false);
		}

		if (mRecordWorldTourPanel == nullptr) {
			addWorldTourPanel();
		}
		mRecordWorldTourPanel->setActivate(true);

		if (mRecordTurmentPanel) {
			mRecordTurmentPanel->setActivate(false);
		}

		if (mRecordSurvivalPanel) {
			mRecordSurvivalPanel->setActivate(false);
		}
	}
	else if (mTapIndex == 2) {

		if (mRecordRankPanel) {
			mRecordRankPanel->setActivate(false);
		}

		if (mRecordWorldTourPanel) {
			mRecordWorldTourPanel->setActivate(false);
		}

		if (mRecordTurmentPanel == nullptr) {
			addTournamentPanel();
		}
		mRecordTurmentPanel->setActivate(true);		

		if (mRecordSurvivalPanel) {
			mRecordSurvivalPanel->setActivate(false);
		}

	}
	else if (mTapIndex == 3) {

		if (mRecordRankPanel) {
			mRecordRankPanel->setActivate(false);
		}		

		if (mRecordWorldTourPanel) {
			mRecordWorldTourPanel->setActivate(false);
		}

		if (mRecordTurmentPanel) {
			mRecordTurmentPanel->setActivate(false);
		}

		if (mRecordSurvivalPanel == nullptr) {
			addSurvivalPanel();
		}
		mRecordSurvivalPanel->setActivate(true);
	}
}

void LobbyRecordPanel::addRankPanel()
{
	CCPoint panelPos = getImage("dmy_record1")->getPosition();
	mRecordRankPanel = new LobbyRecordRankPanel();
	CCSize size = mRecordRankPanel->getContentSize();
	mRecordRankPanel->setPosition(panelPos);
	addChild(mRecordRankPanel);
	mRecordRankPanel->release();
	mRecordRankPanel->setActivate(false);
}

void LobbyRecordPanel::addWorldTourPanel()
{
	CCPoint panelPos = getImage("dmy_record2")->getPosition();
	mRecordWorldTourPanel = new LobbyRecordWorldTourPanel();
	CCSize size = mRecordWorldTourPanel->getContentSize();
	mRecordWorldTourPanel->setPosition(panelPos);
	addChild(mRecordWorldTourPanel);
	mRecordWorldTourPanel->release();
	mRecordWorldTourPanel->setActivate(false);
}

void LobbyRecordPanel::addTournamentPanel()
{
	CCPoint panelPos = getImage("dmy_record3")->getPosition();
	mRecordTurmentPanel = new LobbyRecordTourmentPanel();
	CCSize size = mRecordTurmentPanel->getContentSize();
	mRecordTurmentPanel->setPosition(panelPos);
	addChild(mRecordTurmentPanel);
	mRecordTurmentPanel->release();
	mRecordTurmentPanel->setActivate(false);
}

void LobbyRecordPanel::addSurvivalPanel()
{
	CCPoint panelPos = getImage("dmy_record4")->getPosition();
	mRecordSurvivalPanel = new LobbyRecordSurvivalPanel();
	CCSize size = mRecordSurvivalPanel->getContentSize();
	mRecordSurvivalPanel->setPosition(panelPos);
	addChild(mRecordSurvivalPanel);
	mRecordSurvivalPanel->release();
	mRecordSurvivalPanel->setActivate(false);
}

void LobbyRecordPanel::recvTotalReputeRankRes(W_ReputeRankRes res)
{
	if (mRecordRankPanel)
		mRecordRankPanel->recvTotalReputeRankRes(res);
}

void LobbyRecordPanel::recvFriendReputeRankRes(W_ReputeRankRes res)
{
	if (mRecordRankPanel)
		mRecordRankPanel->recvFriendReputeRankRes(res);
}

bool LobbyRecordPanel::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK>(&stCmd))
	{
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK res = *pstIt;
		DOWNLOAD_FILE_TYPE _type;
		_type = DOWNLOAD_FILE_TYPE::RANKING_PHOTO;
		if (res.param != _type)
			return false;

		if (!res.imagePath.empty())
		{
			if (mRecordRankPanel->isVisible()) {
				int _index = res.dParam;
				//update 해야 하는데 구조가 안 맞느거 같다
			}
		}
		return true;
	}
	return false;
}