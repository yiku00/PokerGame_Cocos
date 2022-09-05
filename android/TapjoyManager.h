#pragma once
//#include "NxDefine.h"
//#include "pch.h"

//#include "NxSingleton.h"
#include "NxFramework.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif

#define TAPJOY_OBJECT "com/numixent/social/TapjoyManager"

class TapjoyManager : public Singleton < TapjoyManager >, public Panel
{

public:
	TapjoyManager();
	~TapjoyManager();

public:	
	void showPlacement_request(string name);
	void showPlacement_show(string name);

	void showPlacement_stageFailed();
	void showPlacement_IAPAbandon();
	void showPlacement_LevelComplete();

private:
	void setPlacementRequest();	
};

