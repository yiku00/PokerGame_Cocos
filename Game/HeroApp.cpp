#include "pch.h"

//#pragma pointers_to_members( full_generality, multiple_inheritance )

#include "HeroApp.h"
#include "GlobalDefine.h"
#include "InterstitialScene.h"
#include "LogoScene.h"
//#include "LoginScene.h"
#include "ResourceLoadingScene.h"
//#include "ViewerScene.h"   ==> 현재 버전 사용 안함
#include "WaitingPanel.h"
#include "MessagePanel.h"
#include "GameService.h"
#include "base/ZipUtils.h"
#include "GameStringDepot.h"
#include "FightScene.h"
#include "TitleScene.h"
#include "LobbyScene.h"
#include "SimplePopupPanel.h"
#include "socket/TCPService.h"
#include "MiniGamesScene.h"
#include "SynopsisScene.h"
#include "Web/WebService.h"
#include "PanelHelper.h"

//#include "NxFilePlugin.h"

template<> HeroApp* Singleton<HeroApp>::msSingleton = nullptr;

#define DEFAULT_SERVER_ID 1

#define ENERGY_NOTIFICATION_ID 801
#define PVP_ENERGY_NOTIFICATION_ID 802

#define PING_DELAY 600.f

#define VIEW_FPS false

#define RESUME_DELAY_TIME 5 * 60	//5분
//#define RESUME_DELAY_TIME 5  	//5초

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AdmobManager.h"

//static u_long myNextRandom = 1;
//double atof(const char *nptr)
//{
//	return (strtod(nptr, NULL));
//}

//int rand(void)
//{
//	return (int)((myNextRandom = (1103515245 * myNextRandom) + 12345) % ((u_long)RAND_MAX + 1));
//}

//void srand(u_int seed)
//{
//	myNextRandom = seed;
//}
#endif
#include "CustomPopupPanel.h"

HeroApp::HeroApp() {

	// Set design resolution.
	mDesignSize.width = DESIGN_WIDTH;		//DESIGN_WIDTH;
	mDesignSize.height = DESIGN_HEIGHT;		//DESIGN_HEIGHT;
	mCenterPoint.x = DESIGN_WIDTH * 0.5f;	//DESIGN_WIDTH * 0.5f;
	mCenterPoint.y = DESIGN_HEIGHT * 0.5f;	//DESIGN_HEIGHT * 0.5f;

	mConnected = false;
	mRefreshTriggerred = false;
	mRefreshing = false;
	mRefreshRequested = false;
	mWaitingCount = 0;
	mActiveTime = 0;
	mElapsedTime = 0.f;
	mLogOut = false;
	mPingDelay = PING_DELAY;
	mPingPong = false;
	mWaitingCount = 0;

	Nx::Scene::setListener(this);
}

HeroApp::~HeroApp() {
	//delete ChatService::getSingletonPtr();
	delete GameService::getSingletonPtr();

	//if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	//	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);

	CCScriptEngineManager::sharedManager()->purgeSharedManager();
}

bool HeroApp::applicationDidFinishLaunching() {

	// initialize director
	auto pDirector = Director::getInstance();
	auto glview = pDirector->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("Version3_Migrate", cocos2d::Rect(0, 0, mDesignSize.width, mDesignSize.height));
#else
		glview = GLViewImpl::create("Version3_Migrate");
#endif
		pDirector->setOpenGLView(glview);
	}

	// Set version string.
	mVersion = StringConverter::toString(VERSION_MAJOR) + "." + StringConverter::toString(VERSION_MINOR);
#if VERSION_MAINTENANCE
	mVersion += "." + StringConverter::toString(VERSION_MAINTENANCE);
#endif
	//string buildName = VERSION_NAME;
	//if (!buildName.empty()) {
	//	mVersion += " (" + buildName + ")";
	//}

	// Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//CCEGLView::sharedOpenGLView()->setFrameSize(1024, 768);
	//CCEGLView::sharedOpenGLView()->setFrameSize(1280, 800);
	//CCEGLView::sharedOpenGLView()->setFrameSize(960, 640);
	//CCEGLView::sharedOpenGLView()->setFrameSize(1136, 640);
	//CCEGLView::sharedOpenGLView()->setFrameSize(480, 320);
	//CCEGLView::sharedOpenGLView()->setFrameSize(2000, 1000);
	//CCEGLView::sharedOpenGLView()->setFrameSize(DESIGN_WIDTH, DESIGN_HEIGHT);
	//CCEGLView::sharedOpenGLView()->setFrameSize(1280, 800);
	//CCEGLView::sharedOpenGLView()->setFrameSize(800, 480);

	int width = CCUserDefault::sharedUserDefault()->getIntegerForKey("frame_width", DESIGN_WIDTH);
	int height = CCUserDefault::sharedUserDefault()->getIntegerForKey("frame_height", DESIGN_HEIGHT);
	width = 1024.f;
	height = 576.f;
	glview->setFrameSize(width, height);

	CCUserDefault::sharedUserDefault()->setIntegerForKey("frame_width", width);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("frame_height", height);
	CCUserDefault::sharedUserDefault()->flush();
#endif

	//CCEGLView::sharedOpenGLView()->setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, kResolutionExactFit);
	glview->setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, ResolutionPolicy::SHOW_ALL);
	//CCEGLView::sharedOpenGLView()->setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, kResolutionShowAll);
	//CCEGLView::sharedOpenGLView()->setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, kResolutionShowAllExt, 960.f/640.f, 800.f/480.f);
	//CCEGLView::sharedOpenGLView()->setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, kResolutionShowAllExt, 960.f/640.f, 1136.f/640.f);

	// enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
	//     pDirector->enableRetinaDisplay(true);

	// turn on display FPS	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pDirector->setDisplayStats(VIEW_FPS);
	//pDirector->setDisplayStats(true);
#endif
	//pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	pDirector->setProjection(kCCDirectorProjection2D);

	// Set default texture pixel format. //texture 사용량 수정
	//CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
	//CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565);
	//
	ZipUtils::ccSetPvrEncryptionKeyPart(0, 0x906f905c);
	ZipUtils::ccSetPvrEncryptionKeyPart(1, 0x53bfad01);
	ZipUtils::ccSetPvrEncryptionKeyPart(2, 0xf346fdb0);
	ZipUtils::ccSetPvrEncryptionKeyPart(3, 0x68c708d3);

	//CCFileUtils::sharedFileUtils()->addSearchPath("boot/");
	string patch = CCFileUtils::sharedFileUtils()->getWritablePath() + "assets/";
	CCFileUtils::sharedFileUtils()->addSearchPath(patch.c_str());

	//CCDirector::sharedDirector()->setContentScaleFactor(0.5f);
	//CCDirector::sharedDirector()->setContentScaleFactor(0.75f);
	//CCDirector::sharedDirector()->setContentScaleFactor(2.f);

#if 0
	FilePlugin* plugin = new FilePlugin();
	string cards = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("cards.zip");
	plugin->addArchive("cards", cards);
	CCFileUtils::sharedFileUtils()->installPlugin(plugin);
#endif
	nxSetPackageName("com/newzensoft/poker");
	string packageName = PACKAGE_NAME;
	nxSetPackageName(packageName);
	// Services
	new GameService();
	//new ChatService();
	//ChatService::getSingleton().start("192.168.0.200", 8000);
	//ChatService::getSingleton().start("192.168.0.8:8088", 0);

	// Extra setup.
	GameService::getSingleton().ready();

	// Create scenes.
	SceneManager::getSingleton().setInterstitialScene(new InterstitialScene());
	SceneManager::getSingleton().addScene(SceneUtil::SceneLogo, new LogoScene());
	SceneManager::getSingleton().addScene(SceneUtil::SceneTitle, new TitleScene());
	SceneManager::getSingleton().addScene(SceneUtil::SceneLobby, new LobbyScene());
	SceneManager::getSingleton().addScene(SceneUtil::SceneFight, new FightScene());
	SceneManager::getSingleton().addScene(SceneUtil::SceneResourceLoading, new ResourceLoadingScene());
	/*	SceneManager::getSingleton().addScene(SceneUtil::SceneViewer, new ViewerScene());*/
	SceneManager::getSingleton().addScene(SceneUtil::SceneMinigame, new MiniGamesScene());
	SceneManager::getSingleton().addScene(SceneUtil::SceneSynopsis, new SynopsisScene());
	SceneManager::getSingleton().initialScene(SceneUtil::SceneLogo);
	ResourceManager::getSingleton().setTargetGroupId(SceneUtil::SceneLogo);
#ifdef _DEBUG

#endif	
	// Set up update loop.
	//CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(HeroApp::update), this, 0, false);
	//CCScheduler::sharedScheduler()->scheduleUpdateForTarget(this, -1, false);
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(HeroApp::update), this, 0, false);

	//	unsigned long size = 0;
	//	unsigned char* data = CCFileUtils::sharedFileUtils()->getFileDataFromZip("cards.zip", "cards/1.png", &size);

		//기덕 추가 sound, effect 적용
	bool soundBGM = CCUserDefault::sharedUserDefault()->getBoolForKey(NSGameConfig::keySoundBgm.c_str(), true);
	bool soundEffect = CCUserDefault::sharedUserDefault()->getBoolForKey(NSGameConfig::keySoundEffect.c_str(), true);
	//battle defalut value ( auto 모드 , speed
	int battleSpeed = CCUserDefault::sharedUserDefault()->getIntegerForKey(NSGameConfig::keyBattleSpeed.c_str(), 0);
	bool battleAuto = CCUserDefault::sharedUserDefault()->getBoolForKey(NSGameConfig::keyBattleAuto.c_str(), false);
	bool tutorial = CCUserDefault::sharedUserDefault()->getBoolForKey(NSGameConfig::keyTutorial.c_str(), false);
	int developServer = CCUserDefault::sharedUserDefault()->getIntegerForKey(NSGameConfig::keyDevelopServer.c_str(), DEFAULT_SERVER_ID);
	bool socialMessageSend = CCUserDefault::sharedUserDefault()->getBoolForKey(NSGameConfig::keyPushSend.c_str(), true);
	int loginType = CCUserDefault::sharedUserDefault()->getIntegerForKey(NSGameConfig::keyLoginType.c_str(), 0);
	int coolTimeType = CCUserDefault::sharedUserDefault()->getIntegerForKey(NSGameConfig::keyGameTurnType.c_str(), 4);
	CCUserDefault::sharedUserDefault()->setBoolForKey(NSGameConfig::keySoundBgm.c_str(), soundBGM);
	CCUserDefault::sharedUserDefault()->setBoolForKey(NSGameConfig::keySoundEffect.c_str(), soundEffect);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyBattleSpeed.c_str(), battleSpeed);
	CCUserDefault::sharedUserDefault()->setBoolForKey(NSGameConfig::keyBattleAuto.c_str(), battleAuto);
	CCUserDefault::sharedUserDefault()->setBoolForKey(NSGameConfig::keyTutorial.c_str(), tutorial);
	CCUserDefault::sharedUserDefault()->setBoolForKey(NSGameConfig::keyPushSend.c_str(), socialMessageSend);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyDevelopServer.c_str(), developServer);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyLoginType.c_str(), loginType);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyGameTurnType.c_str(), coolTimeType);
	CCUserDefault::sharedUserDefault()->flush();
	SoundManager::getSingleton().setEnabledBGM(soundBGM);
	SoundManager::getSingleton().setEnabledEffect(soundEffect);
	// 로컬 푸시 클리어
	//clearLocalNotification(ENERGY_NOTIFICATION_ID);
	//clearLocalNotification(PVP_ENERGY_NOTIFICATION_ID);

	///NxFramework/Framework/NxUtil.cpp:29: error: undefined reference to 'cocos2d::__String::getCString() const' for android
	CCDictionary::create();
	//NxFramework/Framework/NxSkelObject.cpp:969: error: undefined reference to 'spine::SkeletonAnimation::setEventListener(std::__ndk1::function<void (spTrackEntry*, spEvent*)> const&)' for android
	SkeletonAnimation::createWithFile("ui/alluse_board_8888.json", "ui/alluse_board_8888.atlas");

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void HeroApp::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();
	CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
	//SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	if (SoundManager::getSingletonPtr()) {
		SoundManager::getSingleton().pauseBGM();
		SoundManager::getSingleton().stopEffects();
	}

	// 로컬 푸시 설정
// 	if (isConnected() && UserInfoDepot::getSingletonPtr() && GameStringDepot::getSingletonPtr()) {
// 	
// 	}
	//pause 된 시간
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	mCurTime = (timeinfo->tm_hour * 3600) + (timeinfo->tm_min * 60) + timeinfo->tm_sec;
}

// this function will be called when the app is active again
void HeroApp::applicationWillEnterForeground() {
	//pause 된 시간	
	if (GameService::getSingletonPtr()) {
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		int time = (timeinfo->tm_hour * 3600) + (timeinfo->tm_min * 60) + timeinfo->tm_sec;
		int gapTime = time - mCurTime;
		mCurTime = time;
		//초
		//우선 대기 하고
		//소켓이 끊겼다면 다시 연결한다.
// 		CCLog("applicationWillEnterForeground");
// 		if (!TCPService::getSingletonPtr()->IsConnected()) {
// 			CCLog("applicationWillEnterForeground 1");
// 			TCPService::getSingletonPtr()->Reconnect();
// 			CCLog("applicationWillEnterForeground 2");
// 		}
// 		CCLog("applicationWillEnterForeground 3");
		/*
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneFight) {
			if (gapTime > RESUME_DELAY_TIME) {
				//소켓 닫고 로비로 이동하자.
				GameDataManager::getSingleton().SetGameSceneLoaded(GameSceneLoadeStatus::GAME_SCENE_NOT_LOAD);
				TCPService::getSingleton().Close();
				SceneUtil::changeScene(SceneUtil::SceneTitle);
			}
		}
		*/
	}
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	//SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	if (SoundManager::getSingletonPtr()) {
		SoundManager::getSingleton().resumeBGM();
	}

	// 게임서비스 재시작
	if (GameService::getSingletonPtr()) {
		GameService::getSingleton().resume();
	}

	// 빌딩 정보를 재설정한다.
	refresh();

	// 핑 딜레이 재설정
	resetPing();

	// 로컬 푸시 클리어
	clearLocalNotification(ENERGY_NOTIFICATION_ID);
	clearLocalNotification(PVP_ENERGY_NOTIFICATION_ID);
}

void HeroApp::update(float dt)
{
	mActiveTime += dt;
	mElapsedTime = dt;

	if (mRefreshRequested) {
		if (LayerManager::getSingleton().hasLayerType<ServerMessagePanel>()) {
			LayerManager::getSingleton().popLayer(LayerManager::getSingleton().getLayerType<ServerMessagePanel>());
		}
		_sendRefreshReq();

		mRefreshRequested = false;
	}

	// 핑퐁
	if (mConnected && !mPingPong) {
		mPingDelay -= dt;

		if (mPingDelay < 0.f) {
			_sendPing();
			mPingDelay = PING_DELAY;
		}
	}

	//NXASSERT(_CrtCheckMemory());
	GameService::getSingleton().update(dt);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (mConnected && !mRefreshTriggerred && GetAsyncKeyState(VK_F3)) {
		_sendRefreshReq(true);
		mRefreshTriggerred = true;
	}

	if (mRefreshTriggerred && !GetAsyncKeyState(VK_F3)) {
		mRefreshTriggerred = false;
	}

	static bool soundTrigger = false;
	if (!soundTrigger && GetAsyncKeyState(VK_DOWN)) {
		soundTrigger = true;
	}
	else if (soundTrigger && !GetAsyncKeyState(VK_DOWN)) {
		soundTrigger = false;

		if (SoundManager::getSingleton().getEnabledBGM()) {
			SoundManager::getSingleton().setEnabledBGM(false);
			SoundManager::getSingleton().setEnabledEffect(false);
		}
		else {
			SoundManager::getSingleton().setEnabledBGM(true);
			SoundManager::getSingleton().setEnabledEffect(true);
		}
	}

	/* 구버전 모델뷰 제거(현재 미작동이므로)
	static bool triggerred = false;
	if (!triggerred && GetAsyncKeyState(VK_F2)) {
		triggerred = true;
	}

	if (triggerred && !GetAsyncKeyState(VK_F2)) {
		triggerred = false;
		SceneUtil::changeScene(SceneUtil::SceneViewer);
	}
	*/


#endif
}

void HeroApp::_sendRefreshReq(bool fresh)
{

	mRefreshing = true;
}

void HeroApp::_recvRefreshRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		mRefreshing = false;
		return;
	}


	mRefreshing = false;
}

void HeroApp::_sendPing()
{
	if (WebService::getSingletonPtr())
	{
		WebService::getSingletonPtr()->SendPing();
	}
}

void HeroApp::_recvPong(HttpMessage* msg)
{

}

void HeroApp::startWaiting()
{
	if (mWaitingCount == 0) {
		LayerManager::getSingleton().pushDynamicLayer(new WaitingPanel(), ZORDER_WAITING_PANEL, TAG_WAITING_PANEL);
	}

	++mWaitingCount;
}

void HeroApp::stopWaiting()
{
	//NXASSERT(mWaitingCount > 0);
	if (mWaitingCount <= 0)
		return;

	--mWaitingCount;

	if (mWaitingCount == 0) {
		LayerManager::getSingleton().popTaggedLayers(TAG_WAITING_PANEL);
	}
}

void HeroApp::showMessagePanel(const wstring& msg, const wstring& title /*= L"" */, CCObject* target /*= NULL*/, ObjectListener listener /*= NULL*/, MessagePanel::MessageType type /*= MessagePanel::OK*/)
{
	showMessagePanel(StringConverter::toString(msg), StringConverter::toString(title), target, listener, type);
}

void HeroApp::showTopMessagePanel(const string& msg, const string& title /*= ""*/, CCObject* target /*= NULL*/, ObjectListener listener /*= NULL*/, MessagePanel::MessageType type /*= MessagePanel::OK*/)
{
	if (LayerManager::getSingleton().hasLayerType<TopMessagePanel>()) {
		Nx::Layer* layer = LayerManager::getSingleton().getLayerType<TopMessagePanel>();
		LayerManager::getSingleton().closeLayer(layer);
	}

	TopMessagePanel* panel = new TopMessagePanel(title, nxReplaceNewl(msg), type);
	panel->setGeneralListener(target, listener);
	LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
}

void HeroApp::showMessageNoticePanel(const string& msg, const string& title /*= "" */, const string& notice /*= "" */, CCObject* target /*= NULL*/, ObjectListener listener /*= NULL*/, MessagePanel::MessageType type /*= MessagePanel::OK*/)
{
	MessagePanel* panel = new MessagePanel(title, nxReplaceNewl(msg), notice, type);
	panel->setGeneralListener(target, listener);
	LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
}

void HeroApp::showMessagePanel(const string& msg, const string& title /*= ""*/, CCObject* target /*= NULL*/, ObjectListener listener /*= NULL*/, MessagePanel::MessageType type /*= MessagePanel::OK*/)
{
	MessagePanel* panel = new MessagePanel(title, nxReplaceNewl(msg), "", type);
	panel->setGeneralListener(target, listener);
	LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
}

// void HeroApp::showNoMoneyPanel( GameResourceType type )
// {
// 	if(type == GameMoney){
// 		showMessagePanel(GameStringDepot::getSingleton().getString("NeedGameMoneyDesc"), GameStringDepot::getSingleton().getString("NeedGameMoneyTitle"), nullptr, nullptr, MessagePanel::NOGAMEMONEY);
// 	}
// 	else if( type == HonorPoint){
// 		showMessagePanel(GameStringDepot::getSingleton().getString("NeedHonorPointDesc"), GameStringDepot::getSingleton().getString("NeedHonorPointTitle"), nullptr, nullptr, MessagePanel::OK);
// 	}
// 	else{
// 		showMessagePanel(GameStringDepot::getSingleton().getString("NeedCashDesc"), GameStringDepot::getSingleton().getString("NeedCashTitle"), nullptr, nullptr, MessagePanel::NOCASH);
// 	}
// }

void HeroApp::end()
{
	CCDirector::sharedDirector()->end();

	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//	exit(0);
	//#endif
}

int HeroApp::getMajorVersion()
{
	return VERSION_MAJOR;
}

int HeroApp::getMinorVersion()
{
	return VERSION_MINOR;
}

int HeroApp::getBuildNumber()
{
	return VERSION_MAINTENANCE;
}

const string HeroApp::getBuildName()
{
	return VERSION_NAME;
}

void HeroApp::refresh()
{
	if (mConnected && !mRefreshing) {
		mRefreshRequested = true;
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SceneManager::getSingleton().getCurrentScene()->onMessage("onResume");
#endif
}

void HeroApp::exit()
{

	if (LayerManager::getSingleton().isCurrentLayerType<SimplePopupPanel>()) {
		SimplePopupPanel* exitPanel = dynamic_cast<SimplePopupPanel*>(LayerManager::getSingleton().getCurrentLayer());
		if (exitPanel && exitPanel->isGameEndType()) {
			//무시
			return;
		}
	}

	//exit 처리
	bool isExcuteConfirmPanel = false;
	bool isSendConfirmPanel = false;
	if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLogo) {
		//logo 무시
		return;
	}
	else if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneTitle || SceneUtil::getCurrentSceneId() == SceneUtil::SceneFight ||
		SceneUtil::getCurrentSceneId() == SceneUtil::SceneMinigame || SceneUtil::getCurrentSceneId() == SceneUtil::SceneSynopsis) {
		//fight 씬 일 경우 팝업창으로 종료 물어봄
		//TitieScene 에서도 팝업창으로 종료 물어봄
		//minigame 에서도 팝업창으로 종료 물어봄
		isExcuteConfirmPanel = true;
	}
	else if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby) {
		if (LayerManager::getSingleton().getCurrentLayer()->isDynamic()) {
			if (LayerManager::getSingleton().isCurrentLayerType<WaitingPanel>()) {
				isSendConfirmPanel = true;
			}
			else if (LayerManager::getSingleton().isCurrentLayerType<CustomPopupPanel>()) {
				CustomPopupPanel* pCustomPopupPanel = dynamic_cast<CustomPopupPanel*>(LayerManager::getSingleton().getLayerType<CustomPopupPanel>());
				pCustomPopupPanel->clearThisPanel();
			}
			else {
				Nx::Layer* currentLayer = LayerManager::getSingleton().getCurrentLayer();
				if (currentLayer->getZOrder() == 0) {
					if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
					{
						LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
						if (_pTopUiPanel)
						{
							_pTopUiPanel->onClicked("sbtn_option_button");	// x 버튼 눌렀다.
						}
					}
				}
				else {
					LayerManager::getSingleton().popLayer();
				}
			}
		}
		else {
			isExcuteConfirmPanel = true;
		}
	}
	if (isExcuteConfirmPanel) {
		string _OkMsg = "EXIT_GAME";
		string _title = GameStringDepot::getSingleton().getString("TXT_EXIT_POPUP_TITLE");
		string _content = GameStringDepot::getSingleton().getString("TXT_EXIT_GAME");
		SimplePopupPanel* pPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::GAME_END, _content, _title);
		pPanel->SetOkEventMsg(_OkMsg);
		pPanel->setGeneralListener(this, GeneralObjectListener(HeroApp::_onExit));
		LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER + 1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//AdmobManager::getSingleton().showInterstitialAd();
#endif
	}

	if (isSendConfirmPanel) {
		string _OkMsg = "EXIT_GAME";
		string _title = GameStringDepot::getSingleton().getString("TXT_SERVER_EXIT_POPUP_TITLE");
		string _content = GameStringDepot::getSingleton().getString("TXT_SERVER_EXIT_GAME");
		SimplePopupPanel* pPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::GAME_END, _content, _title);
		pPanel->SetOkEventMsg(_OkMsg);
		pPanel->setGeneralListener(this, GeneralObjectListener(HeroApp::_onExit));
		LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER + 1);
	}
}

void HeroApp::_onExit(const string& msg)
{
	if (msg == "EXIT_GAME") {
		CCDirector::sharedDirector()->end();
	}
}

void HeroApp::showServerErrorMessage(const string& msg, const string& title /*= "" */, const string& notice /*= "" */, CCObject* target /*= NULL*/, ObjectListener listener /*= NULL*/, MessagePanel::MessageType type /*= MessagePanel::OK*/)
{
	bool temp1 = SceneManager::getSingleton().isChanging();

	if (!LayerManager::getSingleton().isInitialized() ||
		SceneManager::getSingleton().isChanging())
		return;

	string errorNotice = "";

	PanelHelper::popLoadingPanel();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	errorNotice = notice;
#endif	
	SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msg);
	panel->SetToastAlign(SimplePopupPanel::ToastAlign::TOP);
	if (panel)
	{
		panel->setGeneralListener(target, listener);
		LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER + 1);
	}
}

void HeroApp::notiServerErrorMessage(const string& msg, const string& title /*= "" */, const string& notice /*= "" */, CCObject* target /*= NULL*/, ObjectListener listener /*= NULL*/, MessagePanel::MessageType type /*= MessagePanel::OK*/)
{
	if (!LayerManager::getSingleton().isInitialized() ||
		SceneManager::getSingleton().isChanging())
		return;

	SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msg);
	panel->SetToastAlign(SimplePopupPanel::ToastAlign::TOP);
	if (panel)
	{
		panel->setListener(TCPService::getSingletonPtr());
		LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
	}
}

void HeroApp::onFinalized()
{
	if (mLogOut && HeroApp::getSingleton().isConnected()) {
		// Reset data.
		//GameDataDepot::getSingleton().release();
		//UserInfoDepot::getSingleton().release();
		// Set connection false.
		HeroApp::getSingleton().setConnected(false);
		CCLOG("Log Out!");
	}

	mLogOut = false;
}

void HeroApp::logOut()
{
	mLogOut = true;
}

void HeroApp::resetPing()
{
	if (mConnected && !mPingPong) {
		mPingDelay = PING_DELAY;
	}
}

void HeroApp::showFunctionClose()
{
	showMessagePanel(GameStringDepot::getSingleton().getString("NextUpdate"));
}

void HeroApp::connectionInitAni()
{
	PanelHelper::popLoadingPanel();
}
