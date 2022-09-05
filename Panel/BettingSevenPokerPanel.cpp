#include "pch.h"
#include "BettingSevenPokerPanel.h"
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AdmobManager.h"
#endif

#define DEFAULT_PLAYER_SEAT 2

const char * BET_KIND_STR[] = { "check", "call", "bing", "tadang", "quarter", "half", "die", "big"};

const ccColor3B ccPointGrayColor = { 120, 120, 120 };

BettingSevenPokerPanel::BettingSevenPokerPanel()
{
	mLabelHalfMoney = nullptr;
	mLabelQuarterMoney = nullptr;
	mLabelMaxBetMoney = nullptr;

	_initData();
	_setParentPanel();
	_initPanel();
	setTouchable(false);

	Init();
}
BettingSevenPokerPanel::~BettingSevenPokerPanel()
{
	if (mLabelHalfMoney)
		mLabelHalfMoney->removeAllChildren();
	if (mLabelQuarterMoney)
		mLabelQuarterMoney->removeAllChildren();
	if (mLabelMaxBetMoney)
		mLabelMaxBetMoney->removeAllChildren();

	if (mMainPanel)
		mMainPanel->removeAllChildren();

	removeAllChildren();
}

void BettingSevenPokerPanel::Init()
{
	mBettingButton[0] = mMainPanel->getButton("sbtn_bettingbutton4");// 체크
	mBettingButton[1] = mMainPanel->getButton("sbtn_bettingbutton3");//콜
	mBettingButton[2] = mMainPanel->getButton("sbtn_bettingbutton2");//삥
	mBettingButton[3] = mMainPanel->getButton("sbtn_bettingbutton5");//따당
	mBettingButton[4] = mMainPanel->getButton("sbtn_bettingbutton6");//쿼터
	mBettingButton[5] = mMainPanel->getButton("sbtn_bettingbutton7");//하프
	mBettingButton[6] = mMainPanel->getButton("sbtn_bettingbutton1");//다이
	
	mBettingButton[7] = mMainPanel->getButton("sbtn_bigbutton");//빅베팅
	mBettingButton[7]->setName("sbtn_bettingbutton8");
	mBettingButton[7]->setVisible(false);

	m_BettingBtnText[0] = mMainPanel->getLabel("txt_check");
	m_BettingBtnText[1] = mMainPanel->getLabel("txt_check");
	m_BettingBtnText[2] = mMainPanel->getLabel("txt_bing");
	m_BettingBtnText[3] = mMainPanel->getLabel("txt_tadang");
	m_BettingBtnText[4] = mMainPanel->getLabel("txt_quarter");
	m_BettingBtnText[5] = mMainPanel->getLabel("txt_half");
	m_BettingBtnText[6] = mMainPanel->getLabel("txt_die");
	m_BettingBtnText[7] = mMainPanel->getLabel("txt_bigbatting");
	m_BettingBtnText[7]->setVisible(false);

	for (int i = 0; i < 8; i++)
	{
		m_BettingBtnText[i]->setGrayColor(ccPointGrayColor);
		m_BettingBtnText[i]->setGrayscale(true);
	}


	mMainPanel->getLabel("txt_check")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_bing")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_tadang")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_quarter")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_half")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_die")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_bigbatting")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	mMainPanel->getLabel("txt_check")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_CHECK").c_str());
	mMainPanel->getLabel("txt_bing")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_BING").c_str());
	mMainPanel->getLabel("txt_tadang")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_TADANG").c_str());
	mMainPanel->getLabel("txt_quarter")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_QUARTER").c_str());
	mMainPanel->getLabel("txt_half")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_HALF").c_str());
	mMainPanel->getLabel("txt_die")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_DIE").c_str());
	mMainPanel->getLabel("txt_bigbatting")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_BIGBET").c_str());

	CCPoint target = getPosition();// +mMainPanel->getPosition();
	mSkelHalfMoney = mMainPanel->getSkel("skel_battsumback1");
	mSkelQuarterMoney = mMainPanel->getSkel("skel_battsumback2");
	mSkelMaxBetMoney = mMainPanel->getSkel("skel_battsumback7");	
	mLabelHalfMoney = mMainPanel->getLabel("txt_batt1");
	mLabelQuarterMoney = mMainPanel->getLabel("txt_batt2");
	mLabelMaxBetMoney = mMainPanel->getLabel("txt_batt7");

	mSkelHalfMoney->setVisible(false);
	mSkelQuarterMoney->setVisible(false);
	mSkelMaxBetMoney->setVisible(false);
	mLabelHalfMoney->setVisible(false);
	mLabelQuarterMoney->setVisible(false);
	mLabelMaxBetMoney->setVisible(false);


	for (int i = 0; i < BETTING_KIND_CNT; i++)
	{
		if (mBettingButton[i] == nullptr)
			continue;
		mBettingButton[i]->setListener(this);
		mBettingButton[i]->setEnable(false);
		mBettingButton[i]->setVisible(true);
		mBettingButton[i]->setType(Button::Touching);
	}

	CCPoint _curPos = getPosition();
	m_ShowPos = _curPos;
	m_HidePos = _curPos + ccp(0, -mMainPanel->getDummy("sbtn_bettingbutton4").size.height);
	
	MovePanel(false);
}

bool BettingSevenPokerPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchEnabled())
		return false;

	return true;
}

void BettingSevenPokerPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchEnabled())
		return;
}

void BettingSevenPokerPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchEnabled())
		return;
}

void BettingSevenPokerPanel::onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

BettingKind BettingSevenPokerPanel::GetBettingKind(const string& name)
{
	BettingKind kind;

	bool isTHoldem = GameDataManager::getSingletonPtr()->m_isTraditionalHoldem;

	if (name == "sbtn_bettingbutton4")
		kind = BettingKind::CHECK;
	else if (name == "sbtn_bettingbutton3")
		kind = BettingKind::CALL;
	else if (name == "sbtn_bettingbutton2")
		kind = BettingKind::BBING;
	else if (name == "sbtn_bettingbutton5")
		kind = BettingKind::DDADANG;
	else if (name == "sbtn_bettingbutton6")
		kind = BettingKind::QUARTER;
	else if (name == "sbtn_bettingbutton7")
		kind = BettingKind::HALF;
	else if (name == "sbtn_bettingbutton1")
		kind = BettingKind::DIE;
	else if (name == "sbtn_bettingbutton8")
		kind = BettingKind::MAX_BETTING;
		

	return kind;
}

void BettingSevenPokerPanel::onClicked(const string& name)
{
	CCLOG("%s", name.c_str());

	BettingKind kind;
	int po = 0;

	if (name.find("touchEnd") != string::npos)
	{
		return;
	}
	else if (name.find("touch") != string::npos)
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		string nameset1 = nxReplace(name, "touch", "");
		kind = GetBettingKind(nameset1);
		SetPressButton(kind);
		return;
	}
	
	kind = GetBettingKind(name);
	SetBetting(kind);

	GameDataManager::getSingleton().GetGameRoomInfoPtr()->BettingChoice(kind);
	//InitCanBetting();
}

/*
void BettingSevenPokerPanel::onAnimationStarted(const string& ani)
{
	CCLOG("33333%s", ani);
}

void BettingSevenPokerPanel::onAnimationEnded(const string& ani)
{
	CCLOG("4444444%s", ani);
}
*/

void BettingSevenPokerPanel::showPanel()
{
	mTouchEnable = true;
}

void BettingSevenPokerPanel::hidePanel()
{
	mTouchEnable = false;
}

void BettingSevenPokerPanel::_initData()
{
	mParentPanel = nullptr;
	mMainPanel = nullptr;
	mCurrentScene = nullptr;
	mTouchEnable = false;
}

void BettingSevenPokerPanel::_initPanel()
{
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		mMainPanel->construct(getMxmlPath() + "dmy_underborad_betting.mxml");		
		addChild(mMainPanel);
		mMainPanel->release();
		CCSize contentsSize = mMainPanel->getDummy("dmy_underborad_betting").size;
		mMainPanel->setPositionY(contentsSize.height - DESIGN_HEIGHT - contentsSize.height / 2.f);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		this->setPosition(mParentPanel->getImage("dmy_underborad_betting")->getPosition());
	}

	mCurrentScene = dynamic_cast<FightScene*>(SceneManager::getSingleton().getCurrentScene());	
	assert(mCurrentScene);
}

void BettingSevenPokerPanel::_setParentPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("Background"));
}

void BettingSevenPokerPanel::InitCanBetting()
{
	for (int i = 0; i < BETTING_KIND_CNT; i++)
	{
		if (mBettingButton[i] == nullptr)
			continue;
		SetEnableButton(i, false, false);
	}

	mBettingButton[BettingKind::CHECK]->setVisible(true);
	mBettingButton[BettingKind::CALL]->setVisible(false);
	mBettingButton[BettingKind::MAX_BETTING]->setVisible(false);

	mSkelHalfMoney->setVisible(false);
	mSkelQuarterMoney->setVisible(false);
	mSkelMaxBetMoney->setVisible(false);
	mLabelHalfMoney->setVisible(false);
	mLabelQuarterMoney->setVisible(false);
	mLabelMaxBetMoney->setVisible(false);
}

void BettingSevenPokerPanel::SetBetting(int number)
{
	for (int i = 0; i < BETTING_KIND_CNT; i++)
	{
		if (mBettingButton[i] == nullptr)
			continue;
		SetEnableButton(i, false, i == number);
	}


	mSkelHalfMoney->setVisible(false);
	mSkelQuarterMoney->setVisible(false);
	mSkelMaxBetMoney->setVisible(false);
	mLabelHalfMoney->setVisible(false);
	mLabelQuarterMoney->setVisible(false);
	mLabelMaxBetMoney->setVisible(false);
}

void BettingSevenPokerPanel::SetCanBetting(int kind, bool isCan)
{
	kind %= 20;
	if (mBettingButton[kind] == nullptr)
		return;

	SetEnableButton(kind, isCan, false);

	m_BettingBtnText[kind]->setGrayscale(!isCan);

	CCLOG("SetCanBetting kind = %d , isCan = %d", kind, isCan);

	NotiFocusPanel* pPanel = nullptr;
	if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
		pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
	}

	if (isCan)
	{
		mBettingButton[kind]->setVisible(true);
		switch (kind)
		{
			case BettingKind::CHECK:
				mBettingButton[BettingKind::CALL]->setVisible(false);
				m_BettingBtnText[BettingKind::CALL]->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_CHECK").c_str());
				m_BettingBtnText[BettingKind::CALL]->setGrayscale(!isCan);
				break;
			case BettingKind::CALL:
				mBettingButton[BettingKind::CHECK]->setVisible(false);
				m_BettingBtnText[BettingKind::CHECK]->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BETTING_CALL").c_str());
				m_BettingBtnText[BettingKind::CHECK]->setGrayscale(!isCan);
				if (pPanel)
					pPanel->setBettingCall();
				break;
			case BettingKind::HALF:
				if (pPanel && pPanel->isShowMoneyType()) {
					mLabelHalfMoney->setVisible(false);
					mSkelHalfMoney->setVisible(false);
					pPanel->setHalfMoney(mNotiHalfMoney);
				}
				else {
					mLabelHalfMoney->setVisible(true);
					mSkelHalfMoney->setVisible(true);
				}
				
				break;
			case BettingKind::QUARTER:
				if (pPanel && pPanel->isShowMoneyType()) {
					mLabelQuarterMoney->setVisible(false);
					mSkelQuarterMoney->setVisible(false);
					pPanel->setQuarterMoney(mNotiQuarterMoney);
				}
				else {
					mLabelQuarterMoney->setVisible(true);
					mSkelQuarterMoney->setVisible(true);
				}
				break;
			case BettingKind::MAX_BETTING :
				if (pPanel && pPanel->isShowMoneyType()) {
					mLabelMaxBetMoney->setVisible(false);
					mSkelMaxBetMoney->setVisible(false);

					CCLOG("bigben = %d", mBettingButton[BettingKind::MAX_BETTING]->isVisible());

					pPanel->setMaxMoney(mNotiMaxMoney);
				}
				else {
					mLabelMaxBetMoney->setVisible(true);
					mSkelMaxBetMoney->setVisible(true);
				}		

				break;
		}
	}	
}

void BettingSevenPokerPanel::SetBettingMoney(int64 quarterMoney, int64 halfMoney, int64 maxMoney)
{
	if (mLabelQuarterMoney == nullptr || mLabelHalfMoney == nullptr)
		return;

	NotiFocusPanel* pPanel = nullptr;
	if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
		pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
	}

	mNotiQuarterMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(quarterMoney), 2);
	//quarterStr.append(GameStringDepot::getSingleton().getString("TXT_GOLD_UNIT"));//U8("골드"));
	mLabelQuarterMoney->setString(mNotiQuarterMoney.c_str());
	if (pPanel)
		pPanel->setQuarterMoney(mNotiQuarterMoney);
	

	mNotiHalfMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(halfMoney), 2);
	//halfStr.append(GameStringDepot::getSingleton().getString("TXT_GOLD_UNIT"));//U8("골드"));
	mLabelHalfMoney->setString(mNotiHalfMoney.c_str());
	if (pPanel)
		pPanel->setHalfMoney(mNotiHalfMoney);


	bool bigButtonVisible = mBettingButton[BettingKind::MAX_BETTING]->isVisible();

	mNotiMaxMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(maxMoney), 2);
	mLabelMaxBetMoney->setString(mNotiMaxMoney.c_str());
	if (pPanel && bigButtonVisible)
		pPanel->setMaxMoney(mNotiMaxMoney);
}

void BettingSevenPokerPanel::SetEnableButton(int kind, bool isEnable, bool isSelect)
{
	if (mBettingButton[kind]->isEnabled() == isEnable)
	{
		if (kind == BettingKind::MAX_BETTING && !isEnable)
		{
			mBettingButton[kind]->setVisible(false);
			m_BettingBtnText[kind]->setVisible(false);
		}
		return;
	}

	m_BettingBtnText[kind]->setGrayscale(!isEnable);
	CCLOG("SetEnableButton kind = %d , isCan = %d", kind, isEnable);

	string name = BET_KIND_STR[kind];
	if (isEnable)
	{
		mBettingButton[kind]->setSkelAnimation(name + "_start", false);
		mBettingButton[kind]->setSkelAppendAnimation(name + "_loop", true);

		if (kind == BettingKind::HALF)
		{
			mSkelHalfMoney->setVisible(true);
			/*mSkelHalfMoney->playAnimation("battsumback_start", false);
			mSkelHalfMoney->playAnimation("battsumback_loop", true);*/
		}
		else if (kind == BettingKind::QUARTER)
		{
			mSkelQuarterMoney->setVisible(true);
			/*mSkelQuarterMoney->playAnimation("battsumback_start", false);
			mSkelQuarterMoney->appendAnimation("battsumback_loop", true);*/
		}
		else if (kind == BettingKind::MAX_BETTING)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GAMEKIND_HOLDEM)
			{
				mBettingButton[kind]->setVisible(true);
				m_BettingBtnText[kind]->setVisible(true);
				mSkelMaxBetMoney->setVisible(true);
				/*mSkelMaxBetMoney->playAnimation("battsumback_start", false);
				mSkelMaxBetMoney->appendAnimation("battsumback_loop", true);*/
			}
		}
	}
	else
	{
		if (isSelect)
		{
			mBettingButton[kind]->setSkelAnimation(name + "_out", false);
			mBettingButton[kind]->setSkelAppendAnimation(name + "_end", false);
		}
		else
			mBettingButton[kind]->setSkelAnimation(name + "_end", false);
		mBettingButton[kind]->setSkelAppendAnimation(name + "_stay", true);

		if (kind == BettingKind::HALF)
			mSkelHalfMoney->setVisible(false);
		else if (kind == BettingKind::QUARTER)
			mSkelQuarterMoney->setVisible(false);
		else if (kind == BettingKind::MAX_BETTING)
		{
			mBettingButton[kind]->setVisible(false);
			m_BettingBtnText[kind]->setVisible(false);
			mSkelMaxBetMoney->setVisible(false);
		}
	}

	mBettingButton[kind]->setEnable(isEnable);
}

void BettingSevenPokerPanel::SetPressButton(int kind)
{
	string name = BET_KIND_STR[kind];
	mBettingButton[kind]->setSkelAnimation(name + "_in", false);
}


void BettingSevenPokerPanel::MovePanel(bool _isShow)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (_isShow) {
		//AdmobManager::getSingleton().hideAdmob();
	}
	else {
		//AdmobManager::getSingleton().showAdMob();
	}	
#endif

	if (mBettingButton[0] == nullptr)
		return;

	stopAllActions();
	CCPoint _curPos = getPosition();

	NotiFocusPanel* pPanel = nullptr;
	if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_7POKER) {
		if (NotiDataManager::getSingleton().getPokerNoti() == NotiData_eNotiType_FirstPoker) {
			//창이 없으면 뿌려주고 visible 이면 끈다		
			if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
				pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
			}
			else {
				PanelHelper::pushNotiFocusPanel(NotiData_eNotiType_FirstPoker);
			}
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM) {
		if (NotiDataManager::getSingleton().getHoldemNoti() == NotiData_eNotiType_FirstHoldem) {
			//창이 없으면 뿌려주고 visible 이면 끈다		
			if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
				pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
			}
			else {
				PanelHelper::pushNotiFocusPanel(NotiData_eNotiType_FirstHoldem);
			}
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
		else if (NotiDataManager::getSingleton().getHoldemNoti() == NotiData_eNotiType_HoldemComunityCard) {
			//창이 없으면 뿌려주고 visible 이면 끈다		
			if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
				pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
			}
			else {
				PanelHelper::pushNotiFocusPanel(NotiData_eNotiType_HoldemComunityCard);
			}
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW) {
		if (NotiDataManager::getSingleton().getHighLowNoti() == NotiData_eNotiType_FirstHighLow) {
			//창이 없으면 뿌려주고 visible 이면 끈다		
			if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
				pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
			}
			else {
				PanelHelper::pushNotiFocusPanel(NotiData_eNotiType_FirstHighLow);
			}
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI) {
		if (NotiDataManager::getSingleton().getBadukiNoti() == NotiData_eNotiType_FirstBaduki) {
			//창이 없으면 뿌려주고 visible 이면 끈다		
			if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
				pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
			}
			else {
				PanelHelper::pushNotiFocusPanel(NotiData_eNotiType_FirstBaduki);
			}
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
	}

	

	if (pPanel)
		pPanel->setVisible(_isShow);


	if (_isShow)
	{
		runAction(CCMoveTo::create(0.1f, m_ShowPos));				
	}		
	else
	{		
		runAction(CCMoveTo::create(0.1f, m_HidePos));
	}	
}