#include "pch.h"
#include "NotiFocusTalkContentPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"


NotiFocusTalkContentPanel::NotiFocusTalkContentPanel()
{
	initPanel();
}

NotiFocusTalkContentPanel::~NotiFocusTalkContentPanel()
{

}

void NotiFocusTalkContentPanel::initPanel()
{
	mMainPanel = new Panel();
	mMainPanel->construct(getMxmlPath() + "dmy_dialogue2.mxml");
	addChild(mMainPanel);
	mMainPanel->release();
	CCSize _contentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(_contentSize.height - DESIGN_HEIGHT - _contentSize.height / 2.f);
	mMainPanel->setPositionX(-_contentSize.width / 2.f);
	mMainPanel->setContentSize(_contentSize);
	this->setContentSize(_contentSize);
	this->setPositionX(DESIGN_WIDTH / 2);
	this->setPositionY(DESIGN_HEIGHT / 2);
	mTalkLabel = mMainPanel->getLabel("txt_dialogue_content");
	mWindowBg = mMainPanel->getSkel("skel_dialogue");
	mWindowBg->playAnimation("image_dialogue2_start");
	mWindowBg->appendAnimation("image_dialogue2_stay",true);
}

void NotiFocusTalkContentPanel::setTalkStr(NotiData_eNotiType notiType)
{
	int notiTypeIndex = notiType;
	string talkStr = "TXT_EVENT_POPUP_DESC" + StringConverter::toString(notiType);
	mTalkLabel->setString(GameStringDepot::getSingleton().getString(talkStr).c_str());
}
