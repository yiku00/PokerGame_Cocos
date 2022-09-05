#pragma once
//#include "NxDefine.h"
//#include "pch.h"

//#include "NxSingleton.h"
#include "NxFramework.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif
#include "NxHttpManager.h"

#define UNITYADS_OBJECT "com/numixent/unitad/UnitAdManager"

using google::protobuf::Message;

class UnityAdsManager : public Nx::Singleton < UnityAdsManager >, public Panel
{

public:
	UnityAdsManager();
	~UnityAdsManager();

public:	
	bool isReadyShowAds();
	void showAds();
public:
	void unityAdsFinish(string zoneId);
	void unityAdsError(string error);
};

