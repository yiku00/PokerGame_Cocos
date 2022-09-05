#pragma once

#include "NxFramework.h"
#include "NxSingleton.h"
#include "NxDefine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include "android/IGAWorksManager.h"
	#include "android/FacebookManager.h"
#endif

enum EXTERNAL_EVENT_TYPE
{
	NO_EVENT							= -1,
	FACEBOOK_LOGIN_AFTER_EVENT			= 1,
	FACEBOOK_LOGOUT_AFTER_EVENT			= 2,
	FACEBOOK_LOGOUT_FAIL_AFTER_EVENT	= 3,
};

struct EXTERNAL_EVENT
{
	EXTERNAL_EVENT_TYPE		m_type;
	float					m_exeInterval;
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
class ExternalLibListener : public Singleton < ExternalLibListener >, public IGAWorksManager::Listener, public FacebookManager::Listener, public Nx::Layer::Listener
#else
class ExternalLibListener : public Singleton < ExternalLibListener >, public Nx::Layer::Listener
#endif
{
public:
	ExternalLibListener();
	~ExternalLibListener();

	// Related with IGAWorksManager
	virtual void onPopupLoaded(const bool isLoad);
	virtual void onPopupDeepLinkClicked(const string& ani);
	virtual void onPopupClicked();
	virtual void onPopupCancelBtnClicked();
	virtual void onCloseAdPopcorn();
	virtual void onEnablePush(bool isSuccess, bool isEnablePush);
	virtual void onCouponInputResult(bool result, string& msg, int itemKye, string& itemName, int64 quantity);
	virtual void onLoadedNanuFanPage(string& url);

	// Related with FacebookManager
	virtual void onFacebookEvent(const int resultCode, const std::string paramStr);


	void registEvent(EXTERNAL_EVENT_TYPE event, int exeTimeInterval);
	void update(float _dt);
	void onLayerMessage(const string& msg);
	EXTERNAL_EVENT		m_externalEvent;

};