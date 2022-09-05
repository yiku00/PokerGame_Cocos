#include "android/AdColonyManager.h"
#include "jni/JniHelper.h"
#include "CmdList.h"
#include "CmdQueue.h"
#include "TypeDefine.pb.h"
#include "SimplePopupPanel.h"

template<> AdColonyManager* Nx::Singleton<AdColonyManager>::msSingleton = 0;

struct AdColonyManagerObject
{
	JNIEnv* env;
	jobject object;

	AdColonyManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, ADCOLONY_OBJECT, "instance", "()Ljava/lang/Object;"))
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

	~AdColonyManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

AdColonyManager::AdColonyManager()
{		
}

AdColonyManager::~AdColonyManager()
{
	
}

bool AdColonyManager::isReadyShowAds()
{
	AdColonyManagerObject obj;
	if (!obj.getObject())
		return false;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, ADCOLONY_OBJECT, "isReadyShow", "()Z")) {
		jboolean ret = t.env->CallBooleanMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
		return ret;
	}
	return false;
}

void AdColonyManager::showAds(string prefix)
{
	AdColonyManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, ADCOLONY_OBJECT, "playAd", "(Ljava/lang/String;)V")) {
		jstring _uidStr = t.env->NewStringUTF(prefix.c_str());
		t.env->CallVoidMethod(obj.getObject(), t.methodID, _uidStr);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AdColonyManager::adColonyFinish()
{

}

void AdColonyManager::adColonyError()
{

}
