#include "pch.h"
#include "BigBonusPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "CmdQueue.h"
#include "PanelHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include "android/VungleManager.h"
#include "android/AdColonyManager.h"
#include "android/AdmobManager.h"
#endif


BigBonusPanel::BigBonusPanel()
{
	initPanel();
}

BigBonusPanel::~BigBonusPanel()
{

}

void BigBonusPanel::initPanel()
{
	addMouseBlockPanel(this , true);	//ok 처리
	construct(getMxmlPath() + "dmy_limited_goods.mxml");	
	mTitle = getLabel("txt_title");
	mTitleUnder = getLabel("txt_title_under");
	mTopDesc = getLabel("txt_info1");
	mBottomDesc = getLabel("txt_info2");

	mLeftPanel = new LimitedGoodContentPanel(LimitedGoodContentPanel::GRAND_NORMAL);
	addChild(mLeftPanel);
	mLeftPanel->release();
	mLeftPanel->setPosition(getImage("dmy_limited_goods_slot1")->getPosition());
	mLeftPanel->setListener(this);

	mRightPanel = new LimitedGoodContentPanel(LimitedGoodContentPanel::GRAND_RANDOM);
	addChild(mRightPanel);
	mRightPanel->release();
	mRightPanel->setPosition(getImage("dmy_limited_goods_slot2")->getPosition());
	mRightPanel->setListener(this);

	mCloseBtn = getButton("sbtn_cancel");
	setButtonListener(this);

	mTitle->setString(GameStringDepot::getSingleton().getString("GranTitle").c_str());
	mTitleUnder->setString(GameStringDepot::getSingleton().getString("GranTitle").c_str());
	mTopDesc->setString(GameStringDepot::getSingleton().getString("GranTopDesc").c_str());
	mBottomDesc->setString(GameStringDepot::getSingleton().getString("GranBottomDesc").c_str());
}

void BigBonusPanel::onClicked(const string& name)
{
	if (name == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
}

void BigBonusPanel::onLayerMessage(const string& msg)
{
	if (msg == "GRAND_NORMAL") {
		LayerManager::getSingleton().popLayer(this);
		WebService::getSingleton().sendW_GranChanceNormalReq();
	}
	else if (msg == "GRAND_RANDOM") {
		string title = GameStringDepot::getSingletonPtr()->getString("TXT_INFORMATION");
		string detail = GameStringDepot::getSingletonPtr()->getString("UPDATE_DESC");
		PanelHelper::pushSimpleConfirmPopupPanel(detail, title);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
//		HeroApp::getSingleton().startWaiting();
//		AdmobManager::getSingleton().showRewardAd();
//#else
//		STCMD_VUNGLE_VIDEO_RESULT result;
//		result.isResult = true;
//		CCmdQueue::getSingleton().pushQueue(result);
//#endif

	}
}

bool BigBonusPanel::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_VUNGLE_VIDEO_RESULT>(&stCmd))
	{
		//구글 로그인 결과
		STCMD_VUNGLE_VIDEO_RESULT res = *pstIt;
		if (res.isResult) {
			//성공	
			CCDelayTime* delay = CCDelayTime::create(2.f);
			CCFiniteTimeAction* callbackAction = CCCallFunc::create(this, callfunc_selector(BigBonusPanel::sendReward));
			runAction(CCSequence::create(delay, callbackAction, NULL));
		}
		else {
			HeroApp::getSingleton().stopWaiting();
		}
		return true;
	}
	else if (auto *pstIt = castCMD<STCMD_ADCOLONY_VIDEO_RESULT>(&stCmd))
	{
		//구글 로그인 결과
		STCMD_ADCOLONY_VIDEO_RESULT res = *pstIt;
		if (res.isResult) {
			//성공	
			CCDelayTime* delay = CCDelayTime::create(2.f);
			CCFiniteTimeAction* callbackAction = CCCallFunc::create(this, callfunc_selector(BigBonusPanel::sendReward));
			runAction(CCSequence::create(delay, callbackAction, NULL));
		}
		else {
			HeroApp::getSingleton().stopWaiting();
		}
		return true;
	}
	else if (auto* pstIt = castCMD<STCMD_ADMOB_VIDEO_RESULT>(&stCmd))
	{
		//구글 로그인 결과
		STCMD_ADMOB_VIDEO_RESULT res = *pstIt;
		CCLog("RefillMoviePanel::handling 3 = %d", res.isResult);
		if (res.isResult) {
			//성공	
			CCDelayTime* delay = CCDelayTime::create(2.f);
			CCFiniteTimeAction* callbackAction = CCCallFunc::create(this, callfunc_selector(BigBonusPanel::sendReward));
			runAction(CCSequence::create(delay, callbackAction, NULL));
		}
		else {
			HeroApp::getSingleton().stopWaiting();
		}
		return true;
	}
	return false;
}

void BigBonusPanel::sendReward()
{
	HeroApp::getSingleton().stopWaiting();
	LayerManager::getSingleton().popLayer(this);
	WebService::getSingleton().sendW_GranChanceRandomReq();
}
