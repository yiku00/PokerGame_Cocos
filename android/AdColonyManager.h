#pragma once
//#include "NxDefine.h"
//#include "pch.h"
//
//#include "NxSingleton.h"
#include "NxFramework.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif
#include "NxHttpManager.h"

#define ADCOLONY_OBJECT "com/newzensoft/adcolony/AdcolonyManager"

using google::protobuf::Message;

class AdColonyManager : public Nx::Singleton < AdColonyManager >, public Panel
{

public:
	AdColonyManager();
	~AdColonyManager();

public:	
	bool isReadyShowAds();
	void showAds(string prefix);

public:
	void adColonyFinish();
	void adColonyError();
};

