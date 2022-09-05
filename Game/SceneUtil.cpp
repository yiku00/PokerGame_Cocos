#include "pch.h"
#include "SceneUtil.h"
#include "HeroUtil.h"
#include "ResourceLoadingScene.h"

//#define NO_LOADING

void SceneUtil::changeScene(SceneUtil::SceneState nextScene, const CSJson::Value& params /*= CSJson::Value()*/, SceneManager::TransitionType tran /*= SceneManager::FadeBlack*/, float duration /*= SCENE_DEFAULT_TRANSITION_TIME*/)
{
	//critterLeaveBreadcrumb("Change from " + getSceneName(getCurrentSceneId()) + " to " + getSceneName(nextScene));
	string logStr = "Change from " + getSceneName(getCurrentSceneId()) + " to " + getSceneName(nextScene);
	CCLog(logStr.c_str(),"");	
	//bool loading = !SceneManager::getSingleton().getScene(nextScene)->getPreloadList().empty() ||
	//	!SceneManager::getSingleton().getCurrentScene()->getPreloadList().empty();
	//bool loading = !SceneManager::getSingleton().getScene(nextScene)->getPreloadList().empty();

	uint currentSceneId = SceneManager::getSingleton().getCurrentSceneID();

	const auto& list = SceneManager::getSingleton().getScene(nextScene)->getPreloadList();
	bool loading = !list.empty();
	if (ResourceManager::getSingleton().hasResourceGroup(currentSceneId) && !list.empty()) {
		ResourceManager::getSingleton().changeResourceGroupId(currentSceneId, nextScene, list);
	}

#ifdef NO_LOADING
	SceneManager::getSingleton().changeScene(nextScene, params, tran, duration);
	ResourceManager::getSingleton().setTargetGroupId(nextScene);
	return;
#endif // NO_LOADING
	if (currentSceneId != SceneUtil::SceneResourceLoading && currentSceneId != nextScene) {
		ResourceLoadingScene* scene = dynamic_cast<ResourceLoadingScene*>(SceneManager::getSingleton().getScene(SceneUtil::SceneResourceLoading));
		scene->setNextAppState(nextScene);
		scene->setLoadingPanel(loading);
		SceneManager::getSingleton().changeScene(SceneUtil::SceneResourceLoading, params, tran, duration);
		ResourceManager::getSingleton().setTargetGroupId(SceneUtil::SceneResourceLoading);
	}
	else {
		SceneManager::getSingleton().changeScene(nextScene, params, tran, duration);
		ResourceManager::getSingleton().setTargetGroupId(nextScene);
	}
}

std::string SceneUtil::getSceneName(SceneUtil::SceneState state)
{
	switch (state)
	{
	case SceneUtil::SceneLogo:
		return "LogoScene";
	case SceneUtil::SceneTitle:
		return "TitleScene";
	case SceneUtil::SceneLobby:
		return "LobbyScene";
	case SceneUtil::SceneIntro:
		return "IntroScene";
	case SceneUtil::SceneResourceLoading:
		return "ResourceLoadingScene";
	case SceneUtil::SceneViewer:
		return "ViewerScene";
	case SceneUtil::SceneFight:
		return "FightScene";
	case SceneUtil::SceneMinigame:
		return "MiniGamesScene";
	case SceneUtil::SceneSynopsis:
		return "SynopsisScene";
	default:
		return "";
	}
}

SceneUtil::SceneState SceneUtil::getSceneId(const string& sceneName)
{
	if (sceneName == "FightScene") {
		return SceneUtil::SceneFight;
	}	
	NXASSERT(false, "Invalid scene name. %s", sceneName.c_str());
	return SceneUtil::SceneLogo;
}

SceneUtil::SceneState SceneUtil::getCurrentSceneId()
{
	return static_cast<SceneUtil::SceneState>(SceneManager::getSingleton().getCurrentSceneID());
}
