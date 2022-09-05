/********************************************************************
	filename: 	RefApp.h
	
	purpose:	
*********************************************************************/
#pragma once

#include "NxApp.h"

class RefApp : public App, public Singleton<RefApp>
{
	static float SCENE_DEFAULT_TRANSITION_TIME;

public:
	enum SceneState {
		Logo,
		//Login,
		Title,
		ResourceLoading,
		Fight,
		Viewer,
	};

public:
	RefApp();
	~RefApp();

private:
	virtual bool onLaunching() override;
	virtual void onBackground() override;
	virtual void onForeground() override;
	virtual void onUpdate() override;

public:
	void changeScene(SceneState nextScene, 
		const CSJson::Value& params = CSJson::Value(), 
		SceneManager::TransitionType tran = SceneManager::FadeBlack, 
		float duration = SCENE_DEFAULT_TRANSITION_TIME);

	bool isConnected() { return false; }

	void networkStart();
	void connected();

};