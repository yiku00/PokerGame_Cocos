#pragma once
#include "NxFramework.h"
#include "NxSceneManager.h"

static float SCENE_DEFAULT_TRANSITION_TIME = 0.5f;

class SceneUtil
{
public:
	enum SceneState {
		SceneLogo,
		SceneTitle,
		SceneLobby,
		SceneIntro,
		SceneFight,
		SceneResourceLoading,
		SceneViewer,
		SceneMinigame,
		SceneSynopsis,
	};

public:
	static void changeScene(SceneUtil::SceneState nextScene, const CSJson::Value& params = CSJson::Value(), SceneManager::TransitionType tran = SceneManager::FadeBlack, float duration = SCENE_DEFAULT_TRANSITION_TIME);
	static string getSceneName(SceneUtil::SceneState state);
	static SceneUtil::SceneState getSceneId(const string& sceneName);
	static SceneUtil::SceneState getCurrentSceneId();
};