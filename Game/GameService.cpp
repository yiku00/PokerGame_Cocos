#include "pch.h"
#include "GameService.h"
#include "GameStringDepot.h"
#include "SoundDataMgr.h"
#include "CmdQueue.h"
#include "HeroApp.h"
#include "CurlMgr.h"
#include "SocialManager.h"
#include "HttpImpl.h"
#include "socket/TCPSocket.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "PokerCardHelper.h"
#include "Web/WebService.h"
#include "ReplayGameManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include "android/AndroidUtilManager.h"
	#include "android/IGAWorksManager.h"
	#include "android/CrittercismManager.h"
	#include "android/FacebookManager.h"
	#include "android/GoogleManager.h"
	#include "android/IapManager.h"
	#include "android/UnityAdsManager.h"
	#include "android/AdColonyManager.h"
	#include "android/VungleManager.h"
	#include "android/AdmobManager.h"	
#endif
#include "ExternalLibListener.h"
#include "NotiDataManager.h"

#define PATCH_PATH "patch"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//static const string GAMBLE_DEFAULT_URL = "http://192.168.1.184:8200/poker_server/";
//static const string GAMBLE_DEFAULT_URL = "http://110.45.190.221:8200/poker_server/";
//static const string GAMBLE_DEFAULT_URL = "http://14.63.198.175:8200/poker_server/";
//static const string GAMBLE_DEFAULT_URL = "http://14.63.167.48:8200/poker_server/";

#else
//static const string GAMBLE_DEFAULT_URL = "http://192.168.1.184:8200/poker_server/";
//static const string GAMBLE_DEFAULT_URL = "http://110.45.190.221:8200/poker_server/";
//static const string GAMBLE_DEFAULT_URL = "http://14.63.198.175:8200/poker_server/";
//static const string GAMBLE_DEFAULT_URL = "http://14.63.167.48:8200/poker_server/";
#endif

template<> GameService* Singleton<GameService>::msSingleton = 0;

GameService::GameService()
{
	mStep = StartUp;

	mPatchPath = CCFileUtils::sharedFileUtils()->getWritablePath();
	mPatchPath += PATCH_PATH;
	// Framework
	// Framework
	new SceneManager();	
	new LayerManager();
	new SoundManager();
	new ResourceManager();
	new HttpManager();
	HttpManager::getSingleton().setImpl(new HttpImpl());
	//기덕 추가 httpmanager 에서는 이제 gateway 에서 안 부침. 그래서 + 해준다.
	ssize_t size = 0;
	string serverFile = CCFileUtils::sharedFileUtils()->fullPathForFilename("server.txt");	
	const char *server = serverFile.empty() ? nullptr : (char*)CCFileUtils::sharedFileUtils()->getFileData(serverFile.c_str(), "rt", &size);
	if (size) {
		stringstream stream(server);
		string line;
		getline(stream, line);
		//const char CR = 0x0d;
		//line.push_back(CR);
		nxRemoveCRLF(line);
		CC_SAFE_DELETE_ARRAY(server);
		HttpManager::getSingleton().setDefaultURL(line);
	}
	else {
		HttpManager::getSingleton().setDefaultURL(GAMBLE_DEFAULT_URL + "gateway_servlet");
	}	
	new BillingManager();
	new PushManager();
	new SocialManager();
	new CCUrlMgr();
	new CustomShaderCache();
	new PanelLayoutCache();	
	new DictCache();
	new SamCache();
	new SkelCache();	
	// XML
	vector<string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
	vector<string> searchPathsBackup = searchPaths;
	vector<string>::iterator iter = searchPaths.begin();
	searchPaths.insert(iter, mPatchPath);
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
	new GameStringDepot();	
	new SoundDataMgr();
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPathsBackup);

	//new CGvInterface();
	new CCmdQueue();
	new PokerCardHelper();
	//20151007 add by cuan
	new GameDataManager();
	new TCPService();
	new WebService();
	new ReplayGameManager();
	new NotiDataManager();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		new AndroidUtilManager();
		//AndroidUtilManager::getSingletonPtr()->InitWebView("http://www.daum.net", 50, 50, 1000, 500);
		//new IGAWorksManager();
		//new CrittercismManager();
		new FacebookManager();
		new GoogleManager();
		//GoogleManager::getSingleton().googleInit();
		new IapManager();
		//new UnityAdsManager();		
		//new OneStoreManager();
		//new AdColonyManager();
		//new VungleManager();
		new AdmobManager();		
	#endif
	new ExternalLibListener();	
}

GameService::~GameService()
{
	SoundDataMgr::getSingleton().unloadSceneSound("Common");

	delete CCmdQueue::getSingletonPtr();
	//delete CGvInterface::getSingletonPtr();
	delete SoundDataMgr::getSingletonPtr();
	delete GameStringDepot::getSingletonPtr();
	delete SkelCache::getSingletonPtr();
	delete SamCache::getSingletonPtr();
	delete DictCache::getSingletonPtr();
	delete PanelLayoutCache::getSingletonPtr();
	delete CustomShaderCache::getSingletonPtr();
	delete CCUrlMgr::getSingletonPtr();
	delete SocialManager::getSingletonPtr();
	delete PushManager::getSingletonPtr();
	delete BillingManager::getSingletonPtr();
	delete HttpManager::getSingletonPtr();
	//20151007 add by cuan
	delete GameDataManager::getSingletonPtr();
	delete WebService::getSingletonPtr();
	delete ReplayGameManager::getSingletonPtr();
	delete LayerManager::getSingletonPtr();
	delete SceneManager::getSingletonPtr();
	delete PokerCardHelper::getSingletonPtr();
	delete TCPService::getSingletonPtr();
	delete SoundManager::getSingletonPtr();
	delete ResourceManager::getSingletonPtr();
	delete ExternalLibListener::getSingletonPtr();
	delete NotiDataManager::getSingletonPtr();
		
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		delete AndroidUtilManager::getSingletonPtr();
		//delete IGAWorksManager::getSingletonPtr();
		//delete CrittercismManager::getSingletonPtr();
		delete FacebookManager::getSingletonPtr();
		delete GoogleManager::getSingletonPtr();
		delete IapManager::getSingletonPtr();
	//	delete UnityAdsManager::getSingletonPtr();
		//delete AdColonyManager::getSingletonPtr();
		delete VungleManager::getSingletonPtr();		
	#endif
}

void GameService::ready()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#ifdef _DEBUG
	//SoundManager::getSingleton().setEnabledBGM(false);
	//SoundManager::getSingleton().setEnabledEffect(false);
#endif
#endif

	PushManager::getSingleton().startService();

	CustomShaderCache::getSingleton().loadCustomShaders();

	// GameString ?뫥뮻돤?
	GameStringDepot::getSingleton().LoadDataXml();	
	SoundDataMgr::getSingleton().loadData();
	SoundDataMgr::getSingleton().loadSceneSound("Common");
	//GameStringDepot::getSingleton().changeLanguage(GameStringDepot::English);

	CCUrlMgr::getSingleton().threadStart();
}

void GameService::start()
{
	sendGameDataReq();
}

void GameService::stop()
{
	mStep = StartUp;
	mStatus.clear();
}


void GameService::resume()
{
	if (mStep == Started) {
		checkChatService(true);
	}
}

static bool dispatch = true;
void GameService::update(float dt)
{
	
	if (dispatch != CCDirector::sharedDirector()->getEventDispatcher()->isEnabled()) {
		dispatch = CCDirector::sharedDirector()->getEventDispatcher()->isEnabled();
		CCLOG("%d ==================================================================================================== GameService update START : dispatch %d",
			CCDirector::sharedDirector()->getTotalFrames(), dispatch);
	}

	HttpManager::getSingleton().update();
	LayerManager::getSingleton().update(dt);
	SceneManager::getSingleton().update(dt);
	SoundManager::getSingleton().update();
	
	DictCache::getSingleton().update();
	SamCache::getSingleton().update();
	SkelCache::getSingleton().update();

	//UserInfoDepot::getSingleton().update(dt);

	if (dispatch != CCDirector::sharedDirector()->getEventDispatcher()->isEnabled()) {
		dispatch = CCDirector::sharedDirector()->getEventDispatcher()->isEnabled();
		CCLOG("%d ==================================================================================================== GameService update END : dispatch %d",
			CCDirector::sharedDirector()->getTotalFrames(), dispatch);
	}

	TCPService::getSingleton().Update(dt);
	ReplayGameManager::getSingleton().Update(dt);

	WebService::getSingleton().update(dt);

	GameDataManager::getSingleton().update(dt);
	if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo)
	{
		GameDataManager::getSingletonPtr()->UpdateSurvivalLeftTime(dt);
	}

	ExternalLibListener::getSingletonPtr()->update(dt);
}

void GameService::sendGameDataReq()
{
// 	GameDataReq req;
// 	
// 	HttpMessage msg(req, HttpResponseHandler(GameService::recvGameDataRes), this, false);
// 	HttpManager::getSingleton().send(msg);
// 
// 	mStatus = GameStringDepot::getSingleton().getString("LoginLoadGameData");
// 
// 	mStep = LoadGameData;
}

void GameService::recvGameDataRes(HttpMessage* msg)
{
// 	if (msg->hasCode()) {
// 		return;
// 	}
// 
// 	GameDataRes res;
// 	res.ParseFromArray(msg->getData(), msg->getSize());
// 	assert(res.IsInitialized());
// 
// 	if (res.has_gamedata()) {
// 		GameDataDepot::getSingleton().initialize(res.gamedata());
// 	}
// 	else {
// 		GameDataDepot::getSingleton().initialize();
// 	}
// 		
// 	// Send user data request.
// 	sendUserDataReq();
	
}

void GameService::sendUserDataReq()
{
// 	UserInfoReq req;
// 	req.set_type(UserInfoReq_RequestType_ALL);
// 	HttpMessage msg(req, HttpResponseHandler(GameService::recvUserDataRes), this, false);
// 	HttpManager::getSingleton().send(msg);
// 
// 	mStatus = GameStringDepot::getSingleton().getString("LoginLoadUserInfo");
// 
// 	mStep = LoadUserInfo;
}

void GameService::recvUserDataRes(HttpMessage* msg)
{
// 	if (msg->hasCode()) {
// 		return;
// 	}
// 
// 	UserInfoRes res;
// 	res.ParseFromArray(msg->getData(), msg->getSize());
// 	assert(res.IsInitialized());
// 
// 	if (res.result() == UserInfoRes_Result_SUCCESS) {
// 		UserInfoDepot::getSingleton().initialize(res.userinfo());
// 
// 		//mStep = Started;
// 		sendChatServerReq();
// 
// 		mStatus = GameStringDepot::getSingleton().getString("LoginLoadChatServer");
// 
// 		mStep = LoadChatServer;
// 	}
// 	else {
// 		HeroApp::getSingleton().showMessagePanel(GameStringDepot::getSingleton().getString("ConnectFail"), "" , this, GeneralObjectListener(GameService::onFailed));
// 	}
}

void GameService::onFailed(const string& msg)
{
	SceneManager::getSingleton().getCurrentScene()->onMessage("GameServiceFailed");
}

float GameService::getProgress()
{
	switch (mStep)
	{
	case GameService::StartUp:
		return 0.f;
	case GameService::LoadGameData:
		return HttpManager::getSingleton().getProgress()/3.f;
	case GameService::LoadUserInfo:
		return 1/3.f + HttpManager::getSingleton().getProgress()/3.f;
	case GameService::LoadChatServer:
		return 2/3.f + HttpManager::getSingleton().getProgress()/3.f;
	case GameService::Started:
		return 1.f;
	default:
		return 0.f;
	}
}

const string& GameService::getStatus()
{
	return mStatus;
}

void GameService::sendChatServerReq()
{
// 	M_ChatServerReq req;
// 
// 	HttpMessage msg(req, HttpResponseHandler(GameService::recvChatServerRes), this, false);
// 	HttpManager::getSingleton().send(msg);
}

void GameService::recvChatServerRes(HttpMessage* msg)
{
// 	if (msg->hasCode()) {
// 		return;
// 	}
// 
// 	M_ChatServerRes res;
// 	res.ParseFromArray(msg->getData(), msg->getSize());
// 	assert(res.IsInitialized());
// 
// 	NXASSERT(res.has_isconnect());
// 	if (res.isconnect()) {
// 		NXASSERT(res.has_uri());
// 		NXASSERT(res.has_tiket());
// 		NXASSERT(res.has_uid());
// 		if (!res.uri().empty()) {
// 			ChatService::getSingleton().start(res.uri(), res.tiket(), res.uid());
// 		}
// 	}
// 
// 	mStep = Started;
// 
// 	mStatus = GameStringDepot::getSingleton().getString("LoginLoadCompleted");
}

void GameService::checkChatService(bool force /*= false*/)
{
// 	if (force) {
// 		if (!ChatService::getSingleton().isConnected()) {
// 			ChatService::getSingleton().stop();
// 			sendChatServerReq();
// 		}
// 	}
// 	else {
// 		if (ChatService::getSingleton().needToRestart()) {
// 			ChatService::getSingleton().stop();
// 			sendChatServerReq();
// 		}
// 	}
}

void GameService::reloadXml()
{
	//PartsDataDepot::getSingleton().reload();
	GameStringDepot::getSingleton().reload();	
	SoundDataMgr::getSingleton().reload();
}
