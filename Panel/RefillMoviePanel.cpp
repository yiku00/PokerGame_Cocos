#include "pch.h"
#include "RefillMoviePanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PanelHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include "android/AdColonyManager.h"
#include "android/VungleManager.h"
#include "android/AdmobManager.h"

#endif
#include "MoviePopupPanel.h"
#include "CmdQueue.h"

#define CELL_COUNT 10

RefillMoviePanel::RefillMoviePanel()
{
	initPanel();
	refreshData();
}

RefillMoviePanel::~RefillMoviePanel()
{
}

void RefillMoviePanel::onClicked(const string& name)
{	
	if (name == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == getButtonName(mPlayBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		string title = GameStringDepot::getSingletonPtr()->getString("TXT_INFORMATION");
		string detail = GameStringDepot::getSingletonPtr()->getString("UPDATE_DESC");
		PanelHelper::pushSimpleConfirmPopupPanel(detail, title);
//		if (isPossibleView()) {
//			HeroApp::getSingleton().startWaiting();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
//			AdmobManager::getSingleton().showRewardAd();
//			
//#else
//			STCMD_ADMOB_VIDEO_RESULT result;
//			result.isResult = true;
//			CCmdQueue::getSingleton().pushQueue(result);
//#endif
//		}
//		else {
//			LayerManager::getSingleton().pushDynamicLayer(new RewardPopupPanel(RewardPopupPanel::POPUP_FULL), DYNAMIC_PUSH_LAYER);
//		}
	}
}

void RefillMoviePanel::initPanel()
{
	addMouseBlockPanel(this, true);	//ok 처리
	construct(getMxmlPath() + "dmy_freerefill.mxml");
	setButtonListener(this);

	string titleStr = GameStringDepot::getSingleton().getString("RefillMoviePanel_TITLE");
	mTitleLabel = getLabel("txt_title");
	mTitleUnderLabel = getLabel("txt_title_under");

	mTitleLabel->setString(titleStr.c_str());
	mTitleUnderLabel->setString(titleStr.c_str());

	mPlayBtn = getButton("sbtn_button");
	mCloseBtn = getButton("sbtn_cancel");
	mNowPlayLabel = getLabel("txt_count_now");
	mMaxPlayLabel = getLabel("txt_count_total");

	for (int i = 0; i < CELL_COUNT; i++)
	{
		string str = "dmy_table_free" + StringConverter::toString(i + 1);
		RefillMovieContentPanel* pPanel = new RefillMovieContentPanel(i);
		addChild(pPanel);
		pPanel->release();
		pPanel->setPosition(getImage(str)->getPosition());
		mContentPanels.push_back(pPanel);
	}

	//total 금액

	int freeDataSize = GameDataManager::getSingleton().GetGameDataPtr()->freechargedata_size();
	string attendStr = NxGetFormatString(GameStringDepot::getSingleton().getString("RefillMovieTitle"));
	int fontSize = GameStringDepot::getSingleton().getStringSize("RefillMovieTitle");
	Script* descScript = Script::create(attendStr, getDummy("dmy_refill_info").size, fontSize, kCCTextAlignmentLeft, "KBIZgo H");
	CCSize contentSize = descScript->getContentSize();
	int gapHeight = getFontGap("fonts/KBIZgo H.ttf", fontSize);
	descScript->setCenterPos(getImage("dmy_refill_info")->getPosition(), gapHeight);	
	addChild(descScript);

	mMovieDescLabel = getLabel("txt_count_info");
	mMovieDescUnderLabel = getLabel("txt_count_info_under");
	mMovieDescLabel->setString(GameStringDepot::getSingleton().getString("RefillMoviePanel_Desc").c_str());
	mMovieDescUnderLabel->setString(GameStringDepot::getSingleton().getString("RefillMoviePanel_Desc").c_str());
	mPlayBtnUnderLabel = getLabel("str_button_under");
	mPlayBtnLabel = getLabel("txt_button");
	mPlayBtnLabel->setString(GameStringDepot::getSingleton().getString("RefillMoviePanel_PlayBtn").c_str());
	mPlayBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("RefillMoviePanel_PlayBtn").c_str());
}

bool RefillMoviePanel::handling(STCMD &stCmd)
{
	CCLog("RefillMoviePanel::handling");
	if (auto *pstIt = castCMD<STCMD_VUNGLE_VIDEO_RESULT>(&stCmd))
	{
		//구글 로그인 결과
		STCMD_VUNGLE_VIDEO_RESULT res = *pstIt;
		CCLog("RefillMoviePanel::handling 1112 = %d", res.isResult);
		if (res.isResult) {
			//성공	
			CCDelayTime* delay = CCDelayTime::create(2.f);
			CCFiniteTimeAction* callbackAction = CCCallFunc::create(this, callfunc_selector(RefillMoviePanel::sendReward));
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
		CCLog("RefillMoviePanel::handling 2 = %d", res.isResult);
		if (res.isResult) {
			//성공	
			CCDelayTime* delay = CCDelayTime::create(2.f);
			CCFiniteTimeAction* callbackAction = CCCallFunc::create(this, callfunc_selector(RefillMoviePanel::sendReward));
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
			CCFiniteTimeAction* callbackAction = CCCallFunc::create(this, callfunc_selector(RefillMoviePanel::sendReward));
			runAction(CCSequence::create(delay, callbackAction, NULL));
		}
		else if (!res.isLoaded) {
			HeroApp::getSingleton().stopWaiting();
			std::string title = GameStringDepot::getSingletonPtr()->getString("TXT_LOAD_AD_FAIL_TITLE");
			std::string detail = GameStringDepot::getSingletonPtr()->getString("TXT_LOAD_AD_FAIL_DETAIL");
			SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, detail, title);
			LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
		}
		else {
			HeroApp::getSingleton().stopWaiting();
		}
		return true;
	}
	return false;
}

void RefillMoviePanel::refreshData()
{
	//젤 마지
	int nowPlay = GameDataManager::getSingleton().getPlayerInfo().freechargecnt();
	int maxPlay = GameDataManager::getSingleton().GetGameDataPtr()->startassets().free_charge_max_count(); 	
	mNowPlayLabel->setString(StringConverter::toString(nowPlay).c_str());
	string maxStr = StringConverter::toString(maxPlay);
	mMaxPlayLabel->setString(maxStr.c_str());

}

bool RefillMoviePanel::isPossibleView()
{
	int nowPlay = GameDataManager::getSingleton().getPlayerInfo().freechargecnt();
	int maxPlay = GameDataManager::getSingleton().GetGameDataPtr()->startassets().free_charge_max_count();
	return nowPlay < maxPlay;
}

void RefillMoviePanel::sendReward()
{
	HeroApp::getSingleton().stopWaiting();
	LayerManager::getSingleton().pushDynamicLayer(new RewardPopupPanel(RewardPopupPanel::POPUP_RESULT_OK), DYNAMIC_PUSH_LAYER);
	WebService::getSingleton().sendFreeChargeReq();
	
}

void RefillMoviePanel::addReward()
{
	refreshData();
	int nowPlay = GameDataManager::getSingleton().getPlayerInfo().freechargecnt() - 1;
	if (nowPlay < 0)
		nowPlay = 0;
	mContentPanels[nowPlay]->addReward();
}
