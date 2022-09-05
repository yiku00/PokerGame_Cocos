#include "pch.h"
#include "MessagePanel.h"
#include "HeroUtil.h"
#include "PopupPanel.h"


const string MessagePanel::BTN_OK = "btn_actionSmallBlue2";
const string MessagePanel::BTN_YES = "btn_actionSmallBlue";
const string MessagePanel::BTN_NO = "btn_actionSmallRed";

MessagePanel::MessagePanel( const string& title , const string& text , const string& notice , MessageType type /*= OK*/ )
{
	mType = type;
	PopupPanel* pPanel;
	if(mType == OK)
		pPanel = new PopupPanel(PopupPanel::Confirm , text);
	else 
		pPanel = new PopupPanel(PopupPanel::CancelOk , text);

	pPanel->addTitle(title);

	if(!notice.empty())
		pPanel->addNotice(notice);

	addChild(pPanel);
	pPanel->setListener(this);
	pPanel->release();


}

MessagePanel::~MessagePanel()
{
}

void MessagePanel::update(float dt)
{
	Panel::update(dt);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
		onLayerMessage(PopupOk);
	}
#endif
}

void MessagePanel::onLayerMessage( const string& msg )
{
	NXASSERT(isDynamic());
	LayerManager::getSingleton().popLayer(this);

	if(mType == OKCANCEL){
		//예 일때만 보낸다.
		if(msg == PopupOk){			
			if (mGeneralListener) 
				(mTarget->*mGeneralListener)(MessageButtonOk);			
		}
	}
	else if(mType == OK){
		if(msg == PopupOk)
			if (mGeneralListener) 
				(mTarget->*mGeneralListener)(BTN_OK);	
	}
	else{
		if (mGeneralListener){
			if(msg == PopupOk)
				(mTarget->*mGeneralListener)(BTN_YES);	
			else if(msg == PopupCancel)
				(mTarget->*mGeneralListener)(BTN_NO);	
		}
	}
}
void MessagePanel::onEnter()
{
	Panel::onEnter();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	scheduleUpdate();
#endif
}