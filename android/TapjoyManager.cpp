#include "android/TapjoyManager.h"
#include "jni/JniHelper.h"
#include "CmdList.h"
#include "CmdQueue.h"
#include "TypeDefine.pb.h"
#include "SimplePopupPanel.h"
#include "HeroUtil.h"

template<> TapjoyManager* Singleton<TapjoyManager>::msSingleton = 0;

struct TapjoyManagerObject
{
	JNIEnv* env;
	jobject object;

	TapjoyManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, TAPJOY_OBJECT, "instance", "()Ljava/lang/Object;"))
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

	~TapjoyManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

TapjoyManager::TapjoyManager()
{
	setPlacementRequest();
}

TapjoyManager::~TapjoyManager()
{
	
}

void TapjoyManager::showPlacement_stageFailed()
{
	TapjoyManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, TAPJOY_OBJECT, "showPlacement_stageFailed", "()V"))
	{
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void TapjoyManager::showPlacement_IAPAbandon()
{
	TapjoyManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, TAPJOY_OBJECT, "showPlacement_IAPAbandon", "()V"))
	{
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void TapjoyManager::showPlacement_LevelComplete()
{
	TapjoyManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, TAPJOY_OBJECT, "showPlacement_LevelComplete", "()V"))
	{
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void TapjoyManager::showPlacement_request(string name)
{
	CCLog("TapjoyManager::name = %s", name.c_str());
	TapjoyManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, TAPJOY_OBJECT, "setPlacement_request", "(Ljava/lang/String;)V")) {
		jstring jproductId = t.env->NewStringUTF(name.c_str());
		t.env->CallVoidMethod(obj.getObject(), t.methodID, jproductId);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jproductId);
	}
	CCLog("TapjoyManager::showPlacement_request");
}

void TapjoyManager::showPlacement_show(string name)
{
	CCLog("TapjoyManager::name = %s", name.c_str());
	TapjoyManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, TAPJOY_OBJECT, "setPlacement_show", "(Ljava/lang/String;)V")) {
		jstring jproductId = t.env->NewStringUTF(name.c_str());
		t.env->CallVoidMethod(obj.getObject(), t.methodID, jproductId);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jproductId);
	}
	CCLog("TapjoyManager::showPlacement_show");
}

void TapjoyManager::setPlacementRequest()
{
	showPlacement_request("Notice");
	showPlacement_request("offerwall_plus");
	showPlacement_request("messagetoearn");
	showPlacement_request("UserInitiated");
}
