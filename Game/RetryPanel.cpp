#include "pch.h"
#include "RetryPanel.h"
#include "HeroUtil.h"
#include "SceneUtil.h"

RetryPanel::RetryPanel()
{
	construct(getMxmlPath() + "popup_ui.mxml");
	setButtonListener(this);

}

RetryPanel::~RetryPanel()
{

}

void RetryPanel::onClicked(const string& buttonName)
{
	SceneUtil::changeScene(SceneUtil::SceneFight);
}

