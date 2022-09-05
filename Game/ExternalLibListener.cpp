#include "pch.h"
#include "GameDataManager.h"
#include "ExternalLibListener.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "android/AndroidUtilManager.h"
#include "android/IGAWorksManager.h"
#include "android/CrittercismManager.h"
#endif
#include "SceneUtil.h"
#include "GameStringDepot.h"
#include "GlobalDefine.h"

template<> ExternalLibListener* Singleton<ExternalLibListener>::msSingleton = 0;


ExternalLibListener::ExternalLibListener()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManager::getSingletonPtr()->SetListener(this);
	FacebookManager::getSingletonPtr()->SetListener(this);
#endif
	m_externalEvent.m_type = NO_EVENT;
}

ExternalLibListener::~ExternalLibListener()
{
}

void ExternalLibListener::onPopupLoaded(const bool isLoad)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (isLoad)
		IGAWorksManager::getSingletonPtr()->ShowPopup();
#endif
}

void ExternalLibListener::onPopupDeepLinkClicked(const string& result)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLOG(result.c_str(),"");

	CSJson::Reader reader;
	CSJson::Value linkData;
	std::string urlStr = "";
	if (reader.parse(result, linkData))
	{
		if (linkData.isMember("url"))
		{
			urlStr = linkData["url"].asString();
			IGAWorksManager::getSingletonPtr()->CloseTopPopup();
			AndroidUtilManager::getSingletonPtr()->InitWebView(urlStr, 50, 50, 1000, 500);
		}
		else
			return;

	}
#endif
}

void ExternalLibListener::onPopupClicked()
{
	CCLOG("onPopup Clicked!!!!");
}

void ExternalLibListener::onPopupCancelBtnClicked()
{
	CCLOG("onPopupCancelBtn Clicked!!!!");
}

void ExternalLibListener::onCloseAdPopcorn()
{
	CCLOG("onCloseAdPopcorn Clicked!!!!");
}

void ExternalLibListener::onEnablePush(bool isSuccess, bool isEnablePush)
{
	CCLOG("onEnablePush Clicked!!!!");
}

void ExternalLibListener::onCouponInputResult(bool result, string& msg, int itemKey, string& itemName, int64 quantity)
{
	CCLOG("onCouponInputResult Clicked!!!!");
}

void ExternalLibListener::onLoadedNanuFanPage(string& url)
{
	if (url.length() == 0)
	{
		return;
	}
	else
	{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		AndroidUtilManager::getSingletonPtr()->InitWebView(url, 0, 0, AndroidUtilManager::getSingletonPtr()->GetScreenWidth(), AndroidUtilManager::getSingletonPtr()->GetScreenHeight());
#endif

	}
}

void ExternalLibListener::onFacebookEvent(const int resultCode, const std::string paramStr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	switch (resultCode)
	{
		case FB_ERROR:
			break;
		case FB_LOGIN_START:
			break;
		case FB_LOGIN_SUCCESS:
		{
			FacebookUserData * myData = FacebookManager::getSingletonPtr()->GetMyUserData();

			GameDataManager::getSingletonPtr()->m_FacebookUserId = myData->fb_id;
			GameDataManager::getSingletonPtr()->m_FacebookUserName = myData->fb_name;
			GameDataManager::getSingletonPtr()->m_FacebookUserEmail = myData->fb_email;
			GameDataManager::getSingletonPtr()->m_FacebookUserPhotoUrl = myData->fb_photoUrl;
			CCLog("myData->fb_name = %s", myData->fb_name.c_str());

			registEvent(FACEBOOK_LOGIN_AFTER_EVENT, 1000);
			break;
		}
		case FB_LOGIN_CANCEL:
			break;
		case FB_LOGIN_FAIL:
			break;
		case FB_LOGOUT:
		case FB_ALREADY_LOGOUT:
		{
			registEvent(FACEBOOK_LOGOUT_AFTER_EVENT, 100);
			break;
		}
		case FB_FRIENDLIST_REQUEST_SUCCESS:
			break;
		case FB_FRIENDLIST_REQUEST_FAIL:
			break;
		case FB_SEND_EMAIL_SUCCESS:
			break;
		case FB_SEND_EMAIL_FAIL:
			break;
		case FB_FRIEND_INVITE_REQUEST_SUCCESS:
			break;
		case FB_LOGOUT_FAIL:
		{
			registEvent(FACEBOOK_LOGOUT_FAIL_AFTER_EVENT, 100);
			break;
		}
	}
	
	if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneTitle)
	{
		switch (resultCode)
		{
			case FB_ERROR:
			case FB_LOGIN_CANCEL:
			case FB_LOGIN_FAIL:
				if (LayerManager::getSingletonPtr()->hasLayer("Title"))
				{
					TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
					_panel->showLoginButton(true);
				}
				break;
		}
	}

#endif
}

void ExternalLibListener::registEvent(EXTERNAL_EVENT_TYPE event, int exeTimeInterval)
{
	m_externalEvent.m_type = event;
	m_externalEvent.m_exeInterval = exeTimeInterval;
}

void ExternalLibListener::update(float _dt)
{
	if (m_externalEvent.m_type == NO_EVENT)
		return;

	string msgText;
	SimplePopupPanel * panel = nullptr;

	switch (m_externalEvent.m_type)
	{
		case FACEBOOK_LOGIN_AFTER_EVENT :
			if (LayerManager::getSingletonPtr()->hasLayer("Title"))
			{
				WebService::getSingletonPtr()->_sendFacebookLoginReq(GameDataManager::getSingletonPtr()->m_FacebookUserId, GameDataManager::getSingletonPtr()->m_FacebookUserPhotoUrl);
			}
			else {			
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)				
				if (!GameDataManager::getSingleton().getUserInfo()->isloginfacebook()) {
					CCLog("SEND PLATFORM");
					WebService::getSingleton().sendFacebookPlatFormReq();
				}
				else {
					CCLog("NO SEND PLATFORM");
					FacebookManager::getSingletonPtr()->RequestOriginUserList();
				}
#endif			
			}

			break;
		case FACEBOOK_LOGOUT_AFTER_EVENT :
			//������ �ʱ�ȭ.0707 �׽�Ʈ �Ѵ�.
			GameDataManager::getSingletonPtr()->m_FacebookUserId = "";	//�ʱ�ȭ				
			if (SceneUtil::getCurrentSceneId() != SceneUtil::SceneState::SceneTitle) {
				GameDataManager::getSingletonPtr()->m_FacebookUserId = "";	//�ʱ�ȭ				
			}
			break;
		case FACEBOOK_LOGOUT_FAIL_AFTER_EVENT :
			msgText = GameStringDepot::getSingleton().getString("TXT_LOGOUT_FAIL");//U8("��Ʈ��ũ ����!");
			panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText);
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
			break;
	}

	m_externalEvent.m_type = NO_EVENT;
}

void ExternalLibListener::onLayerMessage(const string& msg)
{
	if (msg == "net_to_main")
	{
		if (SceneUtil::getCurrentSceneId() != SceneUtil::SceneState::SceneTitle) {
			CCLog("ExternalLibListener::onLayerMessage msg == net_to_main");
			CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyLoginType.c_str(), 0);
			CCUserDefault::sharedUserDefault()->flush();
			SceneUtil::changeScene(SceneUtil::SceneTitle);
		}
		else
		{
			if (LayerManager::getSingletonPtr()->hasLayer("Title"))
			{
				TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
				_panel->showLoginButton(true);

			}
		}
	}
	else if (msg == "net_to_exit")
	{
		CCDirector::sharedDirector()->end();
	}
}





