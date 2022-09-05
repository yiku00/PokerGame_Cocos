#include "pch.h"
#include "NotiFocusPanel.h"
#include "HeroUtil.h"
#include "NotiDataManager.h"
#include "LobbyScene.h"
#include "SceneUtil.h"
#include "NxSceneManager.h"
#include "LobbyUIPanel.h"


NotiFocusPanel::NotiFocusPanel(NotiData_eNotiType type) : Panel("NotiFocusPanel")
{
	mType = type;
	mFocusTalkPanel = nullptr;
	mListPanel = nullptr;
	mListSubPanel = nullptr;
	initPanel();
}

NotiFocusPanel::~NotiFocusPanel()
{

}

void NotiFocusPanel::initPanel()
{
	construct(getMxmlPath() + "dmy_leadnoti.mxml");
	mFocusBg = getSkel("skel_tublack");	
	setFocus();
	drawText();
}

bool NotiFocusPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	NotiDataManager::getSingleton().setValue(mType, true);
	clearUINoti();
	LayerManager::getSingleton().popLayer(this);		
	return true;
}

void NotiFocusPanel::setFocus()
{
	int aniIndex = mType;	
	if (mType == 11)
		aniIndex = 19;
	else if (mType > 10)
		aniIndex = mType - 1;

	string aniStr = "tublack_" + StringConverter::toString(aniIndex);
	if (mFocusBg->hasAnimation(aniStr))
		mFocusBg->playAnimation(aniStr);
	else
		mFocusBg->setVisible(false);

	LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
	if (_pScene) {
		LobbyUIPanel* uiPanel = _pScene->m_LobbyUIPanel;
		// lobbyScene 에서만 해야 할 
		if (mType == NotiData_eNotiType_TutorialEnd) {			
		}
	}	
}

void NotiFocusPanel::drawText()
{
	if (mType < NotiData_eNotiType_OpenNewArea) {
		//말창이 한개이다.
		mFocusTalkPanel = new NotiFocusTalkContentPanel();
		addChild(mFocusTalkPanel);
		mFocusTalkPanel->release();
		mFocusTalkPanel->setPosition(getImage("dmy_dialogue21")->getPosition());
		mFocusTalkPanel->setTalkStr(mType);
	}
	else if (mType < NotiData_eNotiType_FirstPoker) {
		//말창이 한개이다.
		mFocusTalkPanel = new NotiFocusTalkContentPanel();
		addChild(mFocusTalkPanel);
		mFocusTalkPanel->release();
		mFocusTalkPanel->setPosition(getImage("dmy_dialogue22")->getPosition());
		mFocusTalkPanel->setTalkStr(mType);
	}
	else if (mType == NotiData_eNotiType_FirstPoker) {
		//14는 1부터 6개		
		mListPanel = new NotiTalkListPanel(NotiTalkListPanel::TALK_POKER_BTN_LIST);
		addChild(mListPanel);
		mListPanel->release();
		mListPanel->setPosition(getImage("dmy_pan_info1")->getPosition());		
	}
	else if (mType == NotiData_eNotiType_FirstHighLow) {		
		mListPanel = new NotiTalkListPanel(NotiTalkListPanel::TALK_POKER_BTN_LIST);
		addChild(mListPanel);
		mListPanel->release();
		mListPanel->setPosition(getImage("dmy_pan_info1")->getPosition());

		//15는 1부터 3개
		mListSubPanel = new NotiTalkListPanel(NotiTalkListPanel::TALK_HIGHLOW_BTN_LIST);
		addChild(mListSubPanel);
		mListSubPanel->release();
		mListSubPanel->setPosition(getImage("dmy_pan_info2")->getPosition());
	}
	else if (mType == NotiData_eNotiType_FirstBaduki) {
		mListPanel = new NotiTalkListPanel(NotiTalkListPanel::TALK_POKER_BTN_LIST);
		addChild(mListPanel);
		mListPanel->release();
		mListPanel->setPosition(getImage("dmy_pan_info1")->getPosition());

		//16는 1부터 3개
		mListSubPanel = new NotiTalkListPanel(NotiTalkListPanel::TALK_BADUKI_BTN_LIST);
		addChild(mListSubPanel);
		mListSubPanel->release();
		mListSubPanel->setPosition(getImage("dmy_pan_info3")->getPosition());
	}
	else if (mType == NotiData_eNotiType_FirstHoldem) {
		//16는 1부터 3개
		mListPanel = new NotiTalkListPanel(NotiTalkListPanel::TALK_HOLDEM_BTN_LIST);
		addChild(mListPanel);
		mListPanel->release();
		mListPanel->setPosition(getImage("dmy_pan_info4")->getPosition());
	}
	else if (mType == NotiData_eNotiType_HoldemComunityCard) {
		mListPanel = new NotiTalkListPanel(NotiTalkListPanel::TALK_HOLDEM_BTN_LIST);
		addChild(mListPanel);
		mListPanel->release();
		mListPanel->setPosition(getImage("dmy_pan_info4")->getPosition());

		//3개씩
		mListSubPanel = new NotiTalkListPanel(NotiTalkListPanel::TALK_HOLDEM_COMMUNITY);
		addChild(mListSubPanel);
		mListSubPanel->release();
		mListSubPanel->setPosition(getImage("dmy_pan_info5")->getPosition());
	}

	if (mListPanel)
		mListPanel->setVisible(false);

	if (mListSubPanel)
		mListSubPanel->setVisible(false);

}

void NotiFocusPanel::setHalfMoney(string halfMoneyStr)
{
	mListPanel->setVisible(true);
	CCLOG("NotiFocusPanel::setHalfMoneysetHalfMoneysetHalfMoneysetHalfMoneysetHalfMoneysetHalfMoney");
	if (mListPanel)
		mListPanel->setHalfMoney(halfMoneyStr);	

	if (mListSubPanel) {
		mListPanel->setVisible(true);
		if (mType != NotiData_eNotiType_HoldemComunityCard)
			mListSubPanel->setVisible(false);
	}
}

void NotiFocusPanel::setQuarterMoney(string quarterMoneyStr)
{
	//
	CCLOG("NotiFocusPanel::setQuarterMoneyNotiFocusPanel::setQuarterMoneyNotiFocusPanel::setQuarterMoneyNotiFocusPanel::setQuarterMoneyNotiFocusPanel::setQuarterMoney");
	if (mListPanel)
		mListPanel->setQuarterMoney(quarterMoneyStr);	

	if (mListSubPanel) {
		mListPanel->setVisible(true);
		if (mType != NotiData_eNotiType_HoldemComunityCard)
			mListSubPanel->setVisible(false);
	}
}

void NotiFocusPanel::setMaxMoney(string maxMoneyStr)
{
	CCLOG("NotiFocusPanel::setMaxMoneysetMaxMoneysetMaxMoneysetMaxMoneysetMaxMoneysetMaxMoneysetMaxMoneysetMaxMoneysetMaxMoneysetMaxMoney isvisible = %d", mListPanel->isVisible());
	if (NotiDataManager::getSingleton().getHoldemNoti() == NotiData_eNotiType_FirstHoldem || NotiDataManager::getSingleton().getHoldemNoti() == NotiData_eNotiType_HoldemComunityCard) {
		if (mListPanel)
			mListPanel->setMaxMoney(maxMoneyStr);
	}
}

bool NotiFocusPanel::isShowMoneyType()
{
	return true;
}

void NotiFocusPanel::clearUINoti()
{
	LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
	if (_pScene) {
		LobbyUIPanel* pzPanel = _pScene->m_LobbyUIPanel;
		pzPanel->refreshNotiEffect(NotiData_eNotiType_NoType);		
	}
}

void NotiFocusPanel::setSubList()
{
	setVisible(true);
	if (mListPanel)
		mListPanel->setVisible(false);

	if (mListSubPanel) {
		mListSubPanel->setVisible(true);		
	}
}

void NotiFocusPanel::setBettingCall()
{
	if (NotiDataManager::getSingleton().getHoldemNoti() == NotiData_eNotiType_FirstHoldem || NotiDataManager::getSingleton().getHoldemNoti() == NotiData_eNotiType_HoldemComunityCard) {
		if (mListPanel)
			mListPanel->setBettingCall();
	}
}

void NotiFocusPanel::onEnter()
{
	Panel::onEnter();

	if (mType < NotiData_eNotiType_OpenNewArea) {
		setTouchable(true);
	}
	else if (mType < NotiData_eNotiType_FirstPoker) {
		setTouchable(true);
	}
}