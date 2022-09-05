#include "pch.h"
#include "BettingHighLowPanel.h"
#include "HeroUtil.h"
//#include "PokerButtonWidget.h"
//#include "Game.h"
#include "FightScene.h"
//#include "Player.h"
//#include "GameState.h"
#include "socket/TCPService.h"
#include "NxDefine.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "NotiDataManager.h"
#include "PanelHelper.h"


#define DEFAULT_PLAYER_SEAT 2

const char * HIGHLOW_KIND_STR[] = { "high", "low", "swing"};

BettingHighLowPanel::BettingHighLowPanel()
{
	_initData();
	_setParentPanel();
	_initPanel();
	setTouchable(false);

	Init();
}
BettingHighLowPanel::~BettingHighLowPanel()
{
	if (mMainPanel)
		mMainPanel->removeAllChildren();

	removeAllChildren();
}

void BettingHighLowPanel::Init()
{
	mHighLowButton[0] = mMainPanel->getButton("sbtn_highbutton");
	mHighLowButton[1] = mMainPanel->getButton("sbtn_lowbutton");
	mHighLowButton[2] = mMainPanel->getButton("sbtn_swingbutton");
	
	for (int i = 0; i < HIGHLOW_KIND_CNT; i++)
	{
		if (mHighLowButton[i] == nullptr)
			continue;
		mHighLowButton[i]->setListener(this);
		mHighLowButton[i]->setEnable(false);
		mHighLowButton[i]->setType(Button::Touching);
		string name = HIGHLOW_KIND_STR[i];
		mHighLowButton[i]->setSkelAnimation(name + "_stay", false);
		//mHighLowButton[i]->setSkelAppendAnimation(name + "_loop", true);
	}

	mMainPanel->getLabel("txt_high")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_swing")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_low")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	
	mMainPanel->getLabel("txt_high")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_HIGH").c_str());
	mMainPanel->getLabel("txt_swing")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_SWING").c_str());
	mMainPanel->getLabel("txt_low")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_LOW").c_str());	
}

bool BettingHighLowPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchEnabled())
		return true;

	return false;
}

void BettingHighLowPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchEnabled())
		return;
}

void BettingHighLowPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchEnabled())
		return;
}

void BettingHighLowPanel::onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

HighLowBettingKind BettingHighLowPanel::GetHighLowKind(const string& name)
{
	HighLowBettingKind kind;

	if (name == "sbtn_highbutton")
	{
		kind = HighLowBettingKind::HIGH_BET;
	}
	else if (name == "sbtn_swingbutton")
	{
		kind = HighLowBettingKind::SWING_BET;
	}
	else if (name == "sbtn_lowbutton")
	{
		kind = HighLowBettingKind::LOW_BET;
	}
	return kind;
}

void BettingHighLowPanel::onClicked(const string& name)
{
	HighLowBettingKind kind;

	if (name.find("touchEnd") != string::npos)
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		string nameset1 = nxReplace(name, "touchEnd", "");
		kind = GetHighLowKind(nameset1);
		SetReleaseButton(kind);
		return;
	}
	else if (name.find("touch") != string::npos)
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		string nameset1 = nxReplace(name, "touch", "");
		kind = GetHighLowKind(nameset1);
		SetPressButton(kind);
		return;
	}

	kind = GetHighLowKind(name);
	GameDataManager::getSingleton().GetGameRoomInfoPtr()->HighLowBettingChoice(kind);
	InitHighLowButton();
	setVisible(false);
}

void BettingHighLowPanel::showPanel()
{
	mTouchEnable = true;
}

void BettingHighLowPanel::hidePanel()
{
	mTouchEnable = false;
}

void BettingHighLowPanel::_initData()
{
	mParentPanel = nullptr;
	mMainPanel = nullptr;
	mCurrentScene = nullptr;
	mTouchEnable = false;
}

void BettingHighLowPanel::_initPanel()
{
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		//mMainPanel->setPosition(ccp(mParentPanel->getDummy("dmy_underborad_highlow").origin.x, mParentPanel->getDummy("dmy_underborad_highlow").origin.y));
		mMainPanel->construct(getMxmlPath() + "dmy_underborad_highlow.mxml");
		
		CCSize contentsSize = mMainPanel->getDummy("dmy_underborad_highlow").size;
		mMainPanel->setPositionY(contentsSize.height - DESIGN_HEIGHT - contentsSize.height / 2.f);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		this->setPosition(mParentPanel->getImage("dmy_underborad_highlow")->getPosition());
		
		addChild(mMainPanel);
		mMainPanel->release();
	}

	mCurrentScene = dynamic_cast<FightScene*>(SceneManager::getSingleton().getCurrentScene());
	assert(mCurrentScene);
}

void BettingHighLowPanel::_setParentPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("Background"));
}

void BettingHighLowPanel::InitHighLowButton()
{
	for (int i = 0; i < HIGHLOW_KIND_CNT; i++)
	{
		if (mHighLowButton[i] == nullptr)
			continue;
		mHighLowButton[i]->setEnable(false);
	}

	NotiFocusPanel* pPanel = nullptr;
	if (NotiDataManager::getSingleton().getHighLowNoti() == NotiData_eNotiType_FirstHighLow) {
		if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
	}
	if (pPanel)
		pPanel->setVisible(false);

	setVisible(false);
}

void BettingHighLowPanel::ShowHighLowButton()
{
	for (int i = 0; i < HIGHLOW_KIND_CNT; i++)
	{
		if (mHighLowButton[i] == nullptr)
			continue;
		mHighLowButton[i]->setEnable(true);
		string name = HIGHLOW_KIND_STR[i];
		mHighLowButton[i]->setSkelAnimation(name + "_start", false);
		mHighLowButton[i]->setSkelAppendAnimation(name + "end", true);
	}

	NotiFocusPanel* pPanel = nullptr;
	if (NotiDataManager::getSingleton().getHighLowNoti() == NotiData_eNotiType_FirstHighLow) {
		if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
		else {
			if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW) {
				PanelHelper::pushNotiFocusPanel(NotiData_eNotiType_FirstHighLow);
			}
		}
	}

	if (pPanel)
		pPanel->setSubList();

	setVisible(true);
}

void BettingHighLowPanel::DisableHighLowButton(int idx)
{
	if (mHighLowButton[idx] == nullptr)
		return;
	mHighLowButton[idx]->setEnable(false);
	string name = HIGHLOW_KIND_STR[idx];
	mHighLowButton[idx]->setSkelAnimation(name + "_stay", true);
}

void BettingHighLowPanel::SetPressButton(int kind)
{
	string name = HIGHLOW_KIND_STR[kind];
	mHighLowButton[kind]->setSkelAnimation(name + "_in", false);
}

void BettingHighLowPanel::SetReleaseButton(int kind)
{
	string name = HIGHLOW_KIND_STR[kind];
	mHighLowButton[kind]->setSkelAnimation(name + "_out", false);
	mHighLowButton[kind]->setSkelAppendAnimation(name + "_stay", false);
}
