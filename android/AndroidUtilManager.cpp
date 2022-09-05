#include "android/AndroidUtilManager.h"
#include "jni/JniHelper.h"



template<> AndroidUtilManager* Singleton<AndroidUtilManager>::msSingleton = 0;

struct AndroidUtilManagerObject
{
	JNIEnv* env;
	jobject object;

	AndroidUtilManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, ANDROID_UTIL_OBJECT, "instance", "()Ljava/lang/Object;"))
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

	~AndroidUtilManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

struct MainActivityManagerObject
{
	JNIEnv* env;
	jobject object;

	MainActivityManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, PACKAGE_NAME, "getActivity", "()Ljava/lang/Object;"))
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

	~MainActivityManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};


AndroidUtilManager::AndroidUtilManager()
{
	Init();
}

AndroidUtilManager::~AndroidUtilManager()
{
}

void AndroidUtilManager::Init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	MainActivityManagerObject activityObj;

	AndroidUtilManagerObject utilObj;

	if (!activityObj.getObject())
		return;

	if (!utilObj.getObject())
		return;

	
	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "Init", "(Ljava/lang/Object;)V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, activityObj.getObject());
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void AndroidUtilManager::OpenShare()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "CallSMSForShare", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void AndroidUtilManager::DeleteWebView()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "DeleteWebView", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

std::string AndroidUtilManager::Test()
{
	std::string ret = "";


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, ANDROID_UTIL_OBJECT, "test1", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		ret = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);
	}

	/*JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, ANDROID_UTIL_OBJECT, "test", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}*/
#endif
	return ret;
}

void AndroidUtilManager::InitWebView(string url, int x, int y, int w, int h)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "InitWebView", "(Ljava/lang/String;IIII)V"))
	{
		jstring urlstr = t.env->NewStringUTF(url.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, urlstr, x, y, w, h);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(urlstr);
	}
#endif
}

void AndroidUtilManager::ShowWebView()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "ShowWebView", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void AndroidUtilManager::HideWebView()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "HideWebView", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void AndroidUtilManager::ReleaseWebView()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "ReleaseWebView", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

string AndroidUtilManager::GetDeviceID()
{
	std::string deviceId = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return deviceId;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "GetDeviceID", "()Ljava/lang/String;"))
	{
		jstring str = (jstring)t.env->CallObjectMethod(utilObj.getObject(), t.methodID);
		deviceId = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);
	}
#endif

	return deviceId;
}

string AndroidUtilManager::GetPhoneNumber()
{
	std::string deviceId = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return deviceId;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "GetPhoneNumber", "()Ljava/lang/String;"))
	{
		jstring str = (jstring)t.env->CallObjectMethod(utilObj.getObject(), t.methodID);
		deviceId = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);
	}
#endif

	return deviceId;
}

string AndroidUtilManager::GetOSVersion()
{
	std::string deviceId = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return deviceId;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "GetOSVersion", "()Ljava/lang/String;"))
	{
		jstring str = (jstring)t.env->CallObjectMethod(utilObj.getObject(), t.methodID);
		deviceId = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);
	}
#endif

	return deviceId;
}

int AndroidUtilManager::GetScreenWidth()
{
	int width = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return width;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "GetScreenWidth", "()I"))
	{
		width = t.env->CallIntMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif

	return width;
}

int AndroidUtilManager::GetScreenHeight()
{
	int height = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return height;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "GetScreenHeight", "()I"))
	{
		height = t.env->CallIntMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif

	return height;
}

void AndroidUtilManager::RegisterAlarm(int millis, string msg, int repeat, int alarmIdx)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "RegisterAlarm", "(ILjava/lang/String;II)V"))
	{
		jstring urlstr = t.env->NewStringUTF(msg.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, millis, urlstr, repeat, alarmIdx);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(urlstr);
	}
#endif
}

void AndroidUtilManager::UnregisterAlarm(int alarmIdx)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "UnregisterAlarm", "(I)V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, alarmIdx);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void AndroidUtilManager::ShowCustomEditTextField(string text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "ShowEditTextField", "(Ljava/lang/String;)V"))
	{
		jstring _fieldText = t.env->NewStringUTF(text.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, _fieldText);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(_fieldText);
	}
#endif
}

void AndroidUtilManager::HideCustomEditTextField()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "HideEditTextField", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void AndroidUtilManager::InitCustomEditTextField()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "initEditTextField", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void AndroidUtilManager::ReleaseCustomEditTextField()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "ReleaseEditTextField", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void AndroidUtilManager::initAdultView(string url, int x, int y, int w, int h)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "adultWebView", "(Ljava/lang/String;IIII)V"))
	{
		jstring urlstr = t.env->NewStringUTF(url.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, urlstr, x, y, w, h);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(urlstr);
	}
#endif
}

void AndroidUtilManager::OpenAdultURL(string url, int uid, string ip)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, ANDROID_UTIL_OBJECT, "OpenAdultWebView", "(Ljava/lang/String;ILjava/lang/String;)V"))
	{
		jstring jurl = t.env->NewStringUTF(url.c_str());
		jstring jip = t.env->NewStringUTF(ip.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, jurl, uid,jip);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

/*
bool AndroidUtilManager::isAgreement()
{
	ILoveGameHelperObject obj;
	if (!obj.getObject())
		return true;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, HELPER_OBJECT, "isAgreement", "()Z")) {
		jboolean ret = t.env->CallBooleanMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
		return ret;
	}

	return false;
}

void ILoveGameImpl::setAgreement(bool agree)
{
	ILoveGameHelperObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, HELPER_OBJECT, "setAgreement", "(Z)V")) {
		t.env->CallVoidMethod(obj.getObject(), t.methodID, agree);
		t.env->DeleteLocalRef(t.classID);
	}
}
*/
