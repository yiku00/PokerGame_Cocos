#include "pch.h"
#include "TitlePanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
//#include "SimplePopupPanel.h"
//#include "HeroApp.h"

#include "Web/WebService.h"
#include "AccountPopupPanel.h"
#include "SimplePopupPanel.h"
#include "GameStringDepot.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AndroidUtilManager.h"
#include "android/IGAWorksManager.h"
#include "android/CrittercismManager.h"
#include "android/GoogleManager.h"
#include "android/UnityAdsManager.h"
#include "android/IapManager.h"
#include "android/AdColonyManager.h"
#include "android/VungleManager.h"
#include "android/IGAWorksManager.h"
#include "android/AdmobManager.h"
#endif
#include "ExternalLibListener.h"
#include "GlobalDefine.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <io.h>
#endif
#include "PanelHelper.h"
#include "GameService.h"


#define BUILD_VERSION "Live ver.1.0.1 Data_04_28"

//#define CHECK_INTEGRITY

//#define TEST_ADS
//#define TEST_ADCOLONY
//#define TEST_VUNGLE

#define POSSIBLE_BORDER_COLOR_4F ccc4f(0x66 / 255.f, 0xFF / 255.f, 255.f, 255.f)

TitlePanel::TitlePanel()
{


	mLoginProcess = false;
	m_ExitPanel = nullptr;
	m_bShowExitPanel = false;

	//m_NumixButton1 = nullptr;
	//m_NumixButton2 = nullptr;
	//m_FaceBookButton1 = nullptr;
	//m_FaceBookButton2 = nullptr;

	InitPanel();
	setButtonListener(this);
	islocal = false;		
}
	

TitlePanel::~TitlePanel()
{
	//destruct();
}

void TitlePanel::InitPanel()
{	
	construct(getMxmlPath() + "main_screen.mxml"); 
	//m_NumixButton1 = getButton("sbtn_nbutton");
	//m_NumixButton2 = getButton("sbtn_nmark");
	//m_FaceBookButton1 = getButton("sbtn_fbutton");
	//m_FaceBookButton2 = getButton("sbtn_fmark");
	mGoogleLoginIcon = getButton("sbtn_gmark"); 
	mGoogleLogin = getButton("sbtn_gbutton");	
	m_VERSION = getLabel("txt_game_version");	

	mGoogleLoginLabel = getLabel("txt_google");
	mGoogleLoginUnderLabel = getLabel("txt_google_under");
	//mFacebookLoginLabel = getLabel("txt_facebook_under");
	//mFacebookLoginUnderLabel = getLabel("txt_facebook");
	//mGuestLoginLabel = getLabel("txt_guest_under");
	//mGuestLoginUnderLabel = getLabel("txt_guest");

	mGoogleLoginLabel->setString(GameStringDepot::getSingleton().getString("GOOGLE_LOGIN").c_str());
	mGoogleLoginUnderLabel->setString(GameStringDepot::getSingleton().getString("GOOGLE_LOGIN").c_str());
	//mFacebookLoginLabel->setString(GameStringDepot::getSingleton().getString("FACEBOOK_LOGIN").c_str());
	//mFacebookLoginUnderLabel->setString(GameStringDepot::getSingleton().getString("FACEBOOK_LOGIN").c_str());
	//mGuestLoginLabel->setString(GameStringDepot::getSingleton().getString("GUEST_LOGIN").c_str());
	//mGuestLoginUnderLabel->setString(GameStringDepot::getSingleton().getString("GUEST_LOGIN").c_str());

	//딜링 인증기
	Button* Btn2 = getButton("sbtn_button1");
	Btn2->setAnchorPoint(ccp(1.0f, 1.0f));
	Btn2->setScale(1.2f);

	Btn2->setPosition(ccp(
		this->getContentSize().width - 110, 
		this->getContentSize().height - 48)
	); 
	int a = Btn2->getContentSize().width;
	Nx::Label* btn1Label2 = new Nx::Label();
	btn1Label2->initWithString(L"RNG 딜링 인증 \n진행중", CCSizeMake(180, 56), kCCTextAlignmentCenter, 20, kCCVerticalTextAlignmentCenter);
	btn1Label2->setColor(ccc3(0, 255, 0));
	btn1Label2->setOpacity(255);
	btn1Label2->setAnchorPoint(ccp(0.5f,0.5f));
	btn1Label2->setPosition(Btn2->getPosition());
	addChild(btn1Label2);
	btn1Label2->release();
	string verStr = "ver." + StringConverter::toString(VERSION_MAJOR) + "." + StringConverter::toString(VERSION_MAINTENANCE) + "." + StringConverter::toString(VERSION_MINOR);

#ifdef PAY_GOOGLE
	verStr += ".google";
#endif

	if (GAMBLE_DEFAULT_URL == "http://ilovepoker-live-world.numixent.com:8200/poker_server/") {
		verStr += ".live";
	}
	else {
		verStr += ".staging";
	}
	

	m_VERSION->setString(verStr.c_str());
	//m_VERSION->setRotation(-45);
	
	//_checkIntegrity();
}

void TitlePanel::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	switch (type)
	{
		case TITLE_CMD::CONNECT_SUCCESS_CMD:
		{
			//for (int i = 0; i < 5; i++)
			//	m_UserButton[i]->setEnable(true);
			break;
		}
	}
}

void TitlePanel::onClicked(const string& name)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef TEST_ADS
	if (UnityAdsManager::getSingleton().isReadyShowAds()) {
		CCLog("OK Ready");
		UnityAdsManager::getSingleton().showAds();
	}
	else {
		CCLog("Not Ready");
	}
	return;
#endif

#ifdef TEST_ADCOLONY
	if (AdColonyManager::getSingleton().isReadyShowAds()) {
		CCLog("OK Ready");
		AdColonyManager::getSingleton().showAds();
	}
	else {
		CCLog("Not Ready");
	}
	return;
#endif // TEST_ADCOLONY

#ifdef TEST_VUNGLE
	if (VungleManager::getSingleton().isReadyShowAds()) {
		CCLog("OK Ready");
		VungleManager::getSingleton().showAds();
	}
	else {
		CCLog("Not Ready");
	}
	return;
#endif // TEST_VUNGLE



#endif
	//mName = name;
	if (name == "btn_User_0")
	{
		//TCPService::getSingletonPtr()->SendNewUserReq("", UserKind::NORMAL, 10, 9010);
		//\SceneManager::getSingleton().changeScene(SceneUtil::SceneLobby);
	}
	else if (name == "btn_User_1")
	{
		//TCPService::getSingletonPtr()->SendNewUserReq("", UserKind::NORMAL, 15, 9010);
		//SceneManager::getSingleton().changeScene(SceneUtil::SceneLobby);
	}
	else if (name == "btn_User_2")
	{
		//TCPService::getSingletonPtr()->SendNewUserReq("", UserKind::NORMAL, 22, 9010);
		//SceneManager::getSingleton().changeScene(SceneUtil::SceneLobby);
	}
	else if (name == "btn_User_3")
	{
		//TCPService::getSingletonPtr()->SendNewUserReq("", UserKind::NORMAL, 23, 9010);
		//SceneManager::getSingleton().changeScene(SceneUtil::SceneLobby);
	}
	else if (name == "btn_User_4")
	{
		//TCPService::getSingletonPtr()->SendNewUserReq("", UserKind::NORMAL, 24, 9010);
		//SceneManager::getSingleton().changeScene(SceneUtil::SceneLobby);
	}
	else if (name == "sbtn_nbutton" || name == "sbtn_nmark")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		connectGuest();		
		/*IGAWorksManager::getSingletonPtr()->FirstTimeExperienceTracking("GameEnter", "7Poker");
		IGAWorksManager::getSingletonPtr()->BuyTracking("Ruby_1000");
		IGAWorksManager::getSingletonPtr()->ActivityTracking("LobbyEnter");
		IGAWorksManager::getSingletonPtr()->ActivityTracking("LobbyEnter1", "7Poker");
		IGAWorksManager::getSingletonPtr()->CohortTracking(COHORT_KIND::COHORT_1, "1_level");*/

		//IGAWorksManager::getSingletonPtr()->LoadPopup();
		//IGAWorksManager::getSingletonPtr()->OpenAdPopcorn();
		// IGAWorksManager::getSingletonPtr()->SetClientPush(1, 30, data, true);
		//IGAWorksManager::getSingletonPtr()->OpenCouponDialog(true);
		//IGAWorksManager::getSingletonPtr()->OpenNanuFanPage(false);
	}
	else if (name == "sbtn_fbutton" || name == "sbtn_fmark")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		connectFaceBook();		
#endif
	}
	else if (name == "sbtn_gbutton" || name == "sbtn_gmark")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		connectGoogle();
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		connectGuest();
#endif
	}
}


void TitlePanel::update(float dt)
{

}

bool TitlePanel::handling(STCMD &stCmd)
{
	CCLog("TitlePanel::handling mLoginProcess = %d", mLoginProcess);
	
	if (auto *pstIt = castCMD<STCMD_GOOGLE_LOGIN_RESULT>(&stCmd))
	{
		CCLog("TitlePanel::handling");
		//구글 로그인 결과
		STCMD_GOOGLE_LOGIN_RESULT res = *pstIt;		
		if (res.isSucess) {
			//성공
			CCLog("TitlePanel::handling googleID = %s", res.googleID.c_str());
			WebService::getSingletonPtr()->sendGoogleLoginReq(res.googleID, res.googlePhotoUrl);
		}		
		else {
			//실패
			//실패 처리.....
			PanelHelper::popLoadingPanel();
			showLoginButton(true);
		}
		return true;
	}		
	else if (auto *pstIt = castCMD<STCMD_UNITADS_FINISH>(&stCmd)) {
		CCLog("STCMD_UNITADS_FINISH");
		return true;
	}


	
		//	if (auto *pstIt = castCMD<STCMD_ILOVEGAME_LOGINWITHTOKEN_RESULT>(&stCmd))
		//	{
		//		STCMD_ILOVEGAME_LOGINWITHTOKEN_RESULT res = *pstIt;
		//		if (res.success) {
		//
		//			if (res.isSimple) {
		//				string id = *mIdField->getInputText();
		//				string pw = *mPassField->getInputText();
		//				SocialManager::getSingleton().getInterface()->loginId(id, pw);
		//			}
		//			else {
		//				SocialManager::getSingleton().getInterface()->login();
		//			}
		//
	//#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
	//			if (LayerManager::getSingleton().getCurrentLayer() == this)
	//				LayerManager::getSingleton().popLayer();
	//#endif
	//		}		
	//		else {
	//			mLoginProcess = false;
	//
	//			CSJson::Reader reader;
	//			CSJson::Value params;
	//			reader.parse(res.result, params);
	//			string msg = "";
	//			string notice = "";
	//			if (params.isMember("error"))
	//				msg = params["error"].asString();
	//			else
	//				msg = "LOGINWITHTOKEN Failed.";
	//
	//			//HeroApp::getSingleton().notiServerErrorMessage(msg, "", notice);
	//
	//			return true;
	//		}
	//	}
	return false;
}

void TitlePanel::onKeypadKeyPressed(EventKeyboard::KeyCode  keyCode, Event* /*event*/)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		HeroApp::getSingleton().exit();
		return;

		if (SceneManager::getSingletonPtr()->isChanging())
			return;

		if (GameDataManager::getSingletonPtr()->IsPushCustomWebview())
			return;

		//EXIT
		//CCDirector::sharedDirector()->end();
		if (m_bShowExitPanel == false)
		{
			m_bShowExitPanel = true;
			string _OkMsg = "EXIT_GAME";
			string _title = GameStringDepot::getSingleton().getString("TXT_EXIT_POPUP_TITLE");
			string _content = GameStringDepot::getSingleton().getString("TXT_EXIT_GAME");
			m_ExitPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::YESNONotice, _content, _title);
			if (m_ExitPanel)
			{
				m_ExitPanel->SetOkEventMsg(_OkMsg);
				m_ExitPanel->setListener(this);
				LayerManager::getSingleton().pushDynamicLayer(m_ExitPanel, DYNAMIC_PUSH_LAYER);
			}
		}
		else
		{
			if (m_ExitPanel)
			{
				m_ExitPanel->onClicked("sbtn_cancel");
			}
		}
	}
}

void TitlePanel::onLayerMessage(const string& msg)
{

	if (strncmp(msg.c_str(), "EXIT_GAME", 9) == 0)
	{
		CCDirector::sharedDirector()->end();
	}

	if (strncmp(msg.c_str(), "PopupCancel", 11) == 0)
	{
		m_bShowExitPanel = false;
	}
}

void TitlePanel::showLoginButton(bool visible)
{
	return;

	//m_NumixButton1->setEnable(visible);
	//m_NumixButton1->setVisible(visible);
	
	//m_NumixButton2->setEnable(visible);
	//m_NumixButton2->setVisible(visible);
	
	//m_FaceBookButton1->setEnable(visible);
	//m_FaceBookButton1->setVisible(visible);
	
	//m_FaceBookButton2->setEnable(visible);
	//m_FaceBookButton2->setVisible(visible);

	mGoogleLoginIcon->setEnable(visible);
	mGoogleLogin->setEnable(visible);
}

void TitlePanel::autoLogin()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef TEST_ADS
	if (UnityAdsManager::getSingleton().isReadyShowAds()) {
		CCLog("autoLogin OK Ready");
		//UnityAdsManager::getSingleton().showAds();
		IapManager::getSingleton().launchPurchaseFlow("com.numixent.gamble.test.id1", "", "1");
	}
	else {
		CCLog("Not Ready");
	}
	return;
#endif // TEST_ADS	
#endif

	int loginType = CCUserDefault::sharedUserDefault()->getIntegerForKey(NSGameConfig::keyLoginType.c_str(), 0);
	CCLOG("autoLogin loginType = %d", loginType);
	if (loginType == 0) {	//기존에 접속했던 부분 없으므로 자동 접속 안한다.
		
	}
	else if (loginType == eLoginType::FACEBOOK) {
		connectFaceBook();
	}
	else if (loginType == eLoginType::GOOGLE) {
		connectGoogle();
	}
	else if (loginType == eLoginType::GUEST) {
		connectGuest();
	}
}

void TitlePanel::connectGuest()
{
#ifdef CHECK_INTEGRITY
	vector<string> mxmlList;
	_finddata_t fd;
	long handle;
	int result = 1;
	string path = getMxmlPath() + "*.*";
	handle = _findfirst(path.c_str(), &fd);

	if (handle == -1)
	{

	}
	while (result != -1)
	{
		printf("File: %s\n", fd.name);
		result = _findnext(handle, &fd);

		string name = fd.name;
		if (!name.compare(".") || !name.compare(".."))
			continue;
		mxmlList.push_back(name);
	}
	_findclose(handle);
	for (uint i = 0; i < mxmlList.size(); ++i)
	{
		CCLOG("Checking %s ...", mxmlList[i].c_str());
		Panel* panel = new Panel();
		panel->construct(getMxmlPath() + mxmlList[i]);
		panel->destruct();
		delete panel;
	}
#else
	GameDataManager::getSingletonPtr()->SetLoginType(GUEST);
	//WebService::getSingletonPtr()->_sendPreloginReq();

	WebService::getSingletonPtr()->VersionReq();
	showLoginButton(false);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
	//GoogleManager::getSingleton().googleRevokeAccess();
#endif

#endif // CHECK_INTEGRITY	
}

void TitlePanel::connectFaceBook()
{
	GameDataManager::getSingletonPtr()->SetLoginType(FACEBOOK);
	WebService::getSingletonPtr()->VersionReq();
	showLoginButton(false);
}

void TitlePanel::connectGoogle()
{
	//나중에 개발해야할 부분 GameDataManager::getSingletonPtr()->SetLoginType(GOOGLE);	
	GameDataManager::getSingletonPtr()->SetLoginType(GOOGLE);
	WebService::getSingletonPtr()->VersionReq();
	showLoginButton(false);


}

bool TitlePanel::_checkIntegrity()
{
		bool integrity = true;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		vector<string> mxmlList;

		_finddata_t fd;
		long handle;
		int result = 1;
		string path = getMxmlPath() + "*.*";
		handle = _findfirst(path.c_str(), &fd);

		if (handle == -1)
		{
			return false;
		}
		while (result != -1)
		{
			printf("File: %s\n", fd.name);
			result = _findnext(handle, &fd);

			string name = fd.name;
			if (!name.compare(".") || !name.compare(".."))
				continue;
			mxmlList.push_back(name);
		}
		_findclose(handle);
		for (uint i = 0; i < mxmlList.size(); ++i)
		{
			CCLOG("Checking %s ...", mxmlList[i].c_str());
			Panel* panel = new Panel();
			panel->construct(getMxmlPath() + mxmlList[i]);
			panel->destruct();
			delete panel;
		}
#endif
	return integrity;
}

void TitlePanel::onEnter()
{
	Panel::onEnter();

	setKeypadEnabled(true);
	setTouchable(true);
	scheduleUpdate();
	GameDataManager::getSingletonPtr()->GetGAID();
}