#include "android/CrittercismManager.h"
#include "jni/JniHelper.h"



template<> CrittercismManager* Singleton<CrittercismManager>::msSingleton = 0;

struct CrittercismManagerObject
{
	JNIEnv* env;
	jobject object;

	CrittercismManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, CRITTERCISM_OBJECT, "instance", "()Ljava/lang/Object;"))
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

	~CrittercismManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

CrittercismManager::CrittercismManager()
{
}

CrittercismManager::~CrittercismManager()
{
}

void CrittercismManager::WriteHandledException(string url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CrittercismManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, CRITTERCISM_OBJECT, "writeHandledException", "(Ljava/lang/String;)V"))
	{
		jstring urlstr = t.env->NewStringUTF(url.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, urlstr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(urlstr);
	}
#endif
}

bool CrittercismManager::DidCrash()
{
	bool isCrash = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CrittercismManagerObject utilObj;

	if (!utilObj.getObject())
		return isCrash;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, CRITTERCISM_OBJECT, "didCrash", "()Z"))
	{
		isCrash = t.env->CallBooleanMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif

	return isCrash;
}

void CrittercismManager::critterLeaveBreadcrumb(string breadcrumb)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CrittercismManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, CRITTERCISM_OBJECT, "critterLeaveBreadcrumb", "(Ljava/lang/String;)V"))
	{
		jstring urlstr = t.env->NewStringUTF(breadcrumb.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, urlstr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(urlstr);
	}
#endif
}
