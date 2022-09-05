#include "android/VungleManager.h"
#include "jni/JniHelper.h"
#include "CmdList.h"
#include "CmdQueue.h"
#include "TypeDefine.pb.h"
#include "SimplePopupPanel.h"

template<> VungleManager* Nx::Singleton<VungleManager>::msSingleton = 0;

struct VungleManagerObject
{
	JNIEnv* env;
	jobject object;

	VungleManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, VUNGLE_OBJECT, "instance", "()Ljava/lang/Object;"))
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

	~VungleManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

VungleManager::VungleManager()
{		
}

VungleManager::~VungleManager()
{
	
}

bool VungleManager::isReadyShowAds()
{
	VungleManagerObject obj;
	if (!obj.getObject())
		return false;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, VUNGLE_OBJECT, "isReadyShow", "()Z")) {
		jboolean ret = t.env->CallBooleanMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
		return ret;
	}
	return false;
}

void VungleManager::showAds(string prefix)
{
	VungleManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;	
	if (JniHelper::getMethodInfo(t, VUNGLE_OBJECT, "vungleShow", "(Ljava/lang/String;)V")) {
		jstring _uidStr = t.env->NewStringUTF(prefix.c_str());
		t.env->CallVoidMethod(obj.getObject(), t.methodID, _uidStr);
		t.env->DeleteLocalRef(t.classID);
	}
}

void VungleManager::vungleMovieFinish()
{

}

void VungleManager::vungleMovieError()
{

}
