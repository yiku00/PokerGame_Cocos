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

#define VUNGLE_OBJECT "com/numixent/vungle/VungleManager"

using google::protobuf::Message;

class VungleManager : public Nx::Singleton < VungleManager >, public Panel
{

public:
	VungleManager();
	~VungleManager();

public:	
	bool isReadyShowAds();
	void showAds(string prefix);

public:
	void vungleMovieFinish();
	void vungleMovieError();
};

