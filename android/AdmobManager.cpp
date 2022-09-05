#include "android/AdmobManager.h"
#include "jni/JniHelper.h"
#include "CmdList.h"
#include "Web/WebService.h"
#include "CmdQueue.h"

template<> AdmobManager* Singleton<AdmobManager>::msSingleton = 0;

struct AdmobManagerObject
{
	JNIEnv* env;
	jobject object;

	AdmobManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, ADMOB_OBJECT, "instance", "()Ljava/lang/Object;"))
		{
			env = t.env;
			object = env->CallStaticObjectMethod(t.classID, t.methodID);
			env->DeleteLocalRef(t.classID);
		}
		else {
			object = nullptr;
		}
#else
		object = nullptr;
#endif
	}

	~AdmobManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

AdmobManager::AdmobManager()
{
	setUseFlag(true);
	AdmobManagerObject obj;
}

AdmobManager::~AdmobManager()
{
}

//일반광고(배너, 네이티브)광고 호출 함수
void AdmobManager::showAdMob()
{
	if (!mUseFlag)
		return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AdmobManagerObject obj;

	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, ADMOB_OBJECT, "ShowAd", "()V")) {
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void AdmobManager::hideAdmob()
{
	if (!mUseFlag)
		return;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AdmobManagerObject obj;

	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, ADMOB_OBJECT, "hideAd", "()V")) {
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

//전면광고 호출 함수 
void AdmobManager::showInterstitialAd()
{
	if (!mUseFlag)
		return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("_____________________________________________________________________________________________hideAdmob");
	AdmobManagerObject obj;

	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, ADMOB_OBJECT, "showInterstitialAd", "()V")) {
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}



void AdmobManager::showRewardAd()
{
	if (!mUseFlag)
		return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("_____________________________________________________________________________________________hideAdmob");
	AdmobManagerObject obj;

	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, ADMOB_OBJECT, "showRewardad", "()V")) {
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);

	}
#endif
}

void AdmobManager::HandleReward()
{
	STCMD_ADMOB_VIDEO_RESULT result;

	CanReward == true ? result.isResult = true : result.isResult = false;
	mIsLoaded == true ? result.isLoaded = true : result.isLoaded = false;

	CCmdQueue::getSingleton().pushQueue(result);
	SetReward(false);
}

void AdmobManager::SetReward(bool val)
{
	CanReward = val;
}

void AdmobManager::SetLoaded(bool val)
{
	mIsLoaded = val;
}

void AdmobManager::setUseFlag(bool flag)
{
	mUseFlag = flag;
}
