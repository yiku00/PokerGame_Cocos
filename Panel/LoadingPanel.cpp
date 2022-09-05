#include "pch.h"
#include "LoadingPanel.h"
#include "HeroUtil.h"


LoadingPanel::LoadingPanel()
{	
	construct(getMxmlPath() + "loading_screen.mxml");
	mLoadingDesc = getLabel("txt_info");
	m_company_name_label = getLabel("txt_company_name");

	Panel *panel = new Panel();
	panel->makeColored(ccc4(0x00, 0x00, 0x00, 0xff));		
	panel->setContentSize(CCSize(DESIGN_WIDTH, 50));
	addChild(panel);
	panel->release();
}

LoadingPanel::~LoadingPanel()
{	
}

void LoadingPanel::setTextStr( const string& loadingText )
{
	mTextStr = loadingText;
	mLoadingDesc->setString(mTextStr.c_str());
}

const string& LoadingPanel::getTextStr()
{
	return mTextStr;
}

void LoadingPanel::setDelayClose(float dt)
{
	if (dt == 0.f)
		closePanel();
	else {
		CCDelayTime* delay = CCDelayTime::create(dt);
		CCCallFunc* baseFunc = CCCallFunc::create(this, callfunc_selector(LoadingPanel::closePanel));
		CCAction* squenceAction = CCSequence::create(delay, baseFunc, NULL);
		runAction(squenceAction);
	}
}

void LoadingPanel::closePanel()
{
	LayerManager::getSingleton().popLayer(this);
}
