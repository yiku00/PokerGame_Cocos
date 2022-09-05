#include "pch.h"
#include "RefApp.h"
#include "InterstitialScene.h"
#include "LogoScene.h"
//#include "LoginScene.h"
#include "FightScene.h"
//#include "ViewerScene.h"
#include "GameStringDepot.h"
#include "SocialManager.h"
#include "CmdQueue.h"
#include "SoundDataMgr.h"
#include "ResourceLoadingScene.h"
#include "HttpImpl.h"
#include "PokerCardHelper.h"

#include "TypeDefine.pb.h"


#include "socket/TCPSocket.h"
#include "socket/TCPService.h"

#include "GameDataManager.h"
#include "TitleScene.h"

template<> RefApp* Singleton<RefApp>::msSingleton = 0;
float RefApp::SCENE_DEFAULT_TRANSITION_TIME = 0.5f;

RefApp::RefApp()
{
	_setDesignResolution(CCSizeMake(DESIGN_WIDTH, DESIGN_HEIGHT));

	new GameStringDepot();
	new SoundDataMgr();
	new SocialManager();
	new CCmdQueue();
	new PokerCardHelper();

	//20151007 add by cuan
	new GameDataManager();

	new TCPService();
}

RefApp::~RefApp()
{
	delete GameStringDepot::getSingletonPtr();
	delete SoundDataMgr::getSingletonPtr();
	delete SocialManager::getSingletonPtr();
	delete CCmdQueue::getSingletonPtr();
	delete PokerCardHelper::getSingletonPtr();

	//20151007 add by cuan
	delete GameDataManager::getSingletonPtr();
}

bool RefApp::onLaunching()
{
	// 팩키지 이름 설정 형식 알아보기
	//nxSetPackageName("com/newzensoft/ref/RefActivity");

	HttpManager::getSingleton().setImpl(new HttpImpl());
	SoundDataMgr::getSingleton().loadSceneSound("Common");

	// Create scenes.
	//SceneManager::getSingleton().setInterstitialScene(new InterstitialScene());
	SceneManager::getSingleton().addScene(Logo, new LogoScene());
	//SceneManager::getSingleton().addScene(Login, new LoginScene());
	SceneManager::getSingleton().addScene(Title, new TitleScene());
	SceneManager::getSingleton().addScene(ResourceLoading, new ResourceLoadingScene());
	//TODO :: Make ChannelWindow
	SceneManager::getSingleton().addScene(Fight, new FightScene());		//CardGameWindow
	//SceneManager::getSingleton().addScene(Viewer, new ViewerScene());   ==> 안쓰는거?

	SceneManager::getSingleton().initialScene(Title);
	//SceneManager::getSingleton().initialScene(Logo); //시작 화면 결정 방법.
	return true;
}

void RefApp::networkStart()
{
	//TCPService::getSingleton().start("192.168.1.23", 14001, true);
}

void RefApp::onBackground()
{

}

void RefApp::onForeground()
{

}

void RefApp::onUpdate()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	static bool triggerred = false;
	if (!triggerred && GetAsyncKeyState(VK_F2)) {
		triggerred = true;
	}

	if (triggerred && !GetAsyncKeyState(VK_F2)) {
		triggerred = false;

		changeScene(Viewer);
	}

	//TCPService::getSingleton().Update();

#endif
}

void RefApp::changeScene(SceneState nextScene, const CSJson::Value& params /*= CSJson::Value()*/, SceneManager::TransitionType tran /*= SceneManager::FadeBlack*/, float duration /*= SCENE_DEFAULT_TRANSITION_TIME*/)
{
	uint currentSceneId = SceneManager::getSingleton().getCurrentSceneID();

	const auto& list = SceneManager::getSingleton().getScene(nextScene)->getPreloadList();
	bool loading = !list.empty();
	if (ResourceManager::getSingleton().hasResourceGroup(currentSceneId) && !list.empty()) {
		ResourceManager::getSingleton().changeResourceGroupId(currentSceneId, nextScene, list);
	}

	if (currentSceneId != ResourceLoading && currentSceneId != nextScene) {
		ResourceLoadingScene* scene = dynamic_cast<ResourceLoadingScene*>(SceneManager::getSingleton().getScene(ResourceLoading));
		//scene->setNextAppState(nextScene);
		scene->setLoadingPanel(loading);
		SceneManager::getSingleton().changeScene(ResourceLoading, params, tran, duration);
		ResourceManager::getSingleton().setTargetGroupId(ResourceLoading);
	}
	else {
		SceneManager::getSingleton().changeScene(nextScene, params, tran, duration);
		ResourceManager::getSingleton().setTargetGroupId(nextScene);
	}

}

void RefApp::connected()
{
	CCLOG("called connected!!!!!!");
}
