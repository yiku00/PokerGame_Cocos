/********************************************************************
	file name:	AdmobManager.h
	
	purpose:	
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "NxSingleton.h"
#include "HeroUtil.h"
#pragma once

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif

#define ADMOB_OBJECT "com/newzensoft/admob/AdmobManager"

class AdmobManager : public Singleton < AdmobManager >
{
public:
	AdmobManager();
	~AdmobManager();

public:
	void showAdMob();
	void hideAdmob();
	void showInterstitialAd();
	void showRewardAd();
	void SetReward(bool val);
	void SetLoaded(bool val);
	void HandleReward();
	void SetIntend(bool val){ShowIntend = val;}
	bool GetIntend(){return ShowIntend;}
private:
	void setUseFlag(bool flag);
private:
	bool mUseFlag;
	bool CanReward = false;
	bool mIsLoaded = false;
	bool ShowIntend = false;
};
