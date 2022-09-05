#include "android/UnityAdsManager.h"
#include "jni/JniHelper.h"
#include "CmdList.h"
#include "CmdQueue.h"
#include "TypeDefine.pb.h"
#include "SimplePopupPanel.h"
#include "HeroUtil.h"

template<> UnityAdsManager* Nx::Singleton<UnityAdsManager>::msSingleton = 0;

struct UnitAdsManagerObject
{
	JNIEnv* env;
	jobject object;

	UnitAdsManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, UNITYADS_OBJECT, "instance", "()Ljava/lang/Object;"))
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

	~UnitAdsManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

UnityAdsManager::UnityAdsManager()
{		
}

UnityAdsManager::~UnityAdsManager()
{
	
}

bool UnityAdsManager::isReadyShowAds()
{
	UnitAdsManagerObject obj;
	if (!obj.getObject())
		return false;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, UNITYADS_OBJECT, "isReadyShow", "()Z")) {
		jboolean ret = t.env->CallBooleanMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
		return ret;
	}
	return false;
}

void UnityAdsManager::showAds()
{
	UnitAdsManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, UNITYADS_OBJECT, "adsShow", "()V")) {
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void UnityAdsManager::unityAdsFinish(string zoneId)
{
	STCMD_UNITADS_FINISH result;
	result.zoneId = zoneId;
	CCmdQueue::getSingleton().pushQueue(result);
}

void UnityAdsManager::unityAdsError(string error)
{
	LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, error), DYNAMIC_PUSH_LAYER);
}
