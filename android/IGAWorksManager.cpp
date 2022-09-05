#include "android/IGAWorksManager.h"
#include "NxUtil.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif




template<> IGAWorksManager* Nx::Singleton<IGAWorksManager>::msSingleton = 0;

struct IGAWorksManagerObject
{
	JNIEnv* env;
	jobject object;

	IGAWorksManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, IGAWORKS_JAVA_OBJECT, "getIGAActivity", "()Ljava/lang/Object;"))
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

	~IGAWorksManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

IGAWorksManager::IGAWorksManager()
{
	listener = nullptr;
	Init();
}


IGAWorksManager::~IGAWorksManager()
{
}

void IGAWorksManager::Init()
{	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;
	if (!utilObj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "initIGAWorks", "(Ljava/lang/String;)V"))
	{
		std::string uuid = getUUID();
		jstring tmpstr = t.env->NewStringUTF(uuid.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, tmpstr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
	}
#endif	
}

void IGAWorksManager::FirstTimeExperienceTracking(string userActivity)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "firstTimeExperienceTracking", "(Ljava/lang/String;)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(userActivity.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, tmpstr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
	}
#endif
}

void IGAWorksManager::FirstTimeExperienceTracking(string userActivity, string param)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "firstTimeExperienceTracking", "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(userActivity.c_str());
		jstring tmpstr2 = t.env->NewStringUTF(param.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, tmpstr, tmpstr2);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
		t.env->DeleteLocalRef(tmpstr2);
	}
#endif
}

void IGAWorksManager::BuyTracking(string userActivity)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "buyTracking", "(Ljava/lang/String;)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(userActivity.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, tmpstr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
	}
#endif
}

void IGAWorksManager::ActivityTracking(string userActivity)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "activityTracking", "(Ljava/lang/String;)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(userActivity.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, tmpstr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
	}
#endif
}

void IGAWorksManager::ActivityTracking(string userActivity, string param)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "activityTracking", "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(userActivity.c_str());
		jstring tmpstr2 = t.env->NewStringUTF(param.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, tmpstr, tmpstr2);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
		t.env->DeleteLocalRef(tmpstr2);
	}
#endif
}

void IGAWorksManager::CohortTracking(COHORT_KIND cohortKind, string userActivity)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "cohortTracking", "(ILjava/lang/String;)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(userActivity.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, cohortKind, tmpstr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
	}
#endif
}

void IGAWorksManager::LoadPopup()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("IGAWorksManager::LoadPopup()");
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "loadPopup", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void IGAWorksManager::ShowPopup()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("IGAWorksManager::ShowPopup()");
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "showPopup", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void IGAWorksManager::CloseTopPopup()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "closeTopPopup", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}



void IGAWorksManager::CloseAllPopup()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "closeAllPopup", "()V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void IGAWorksManager::SetEnablePush(bool enable)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "setEnablePush", "(Z)V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, enable);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}


void IGAWorksManager::SetClientPush(int msgID, int delayTime, string& msg, bool isExeInGame)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "setClientPush", "(IILjava/lang/String;Z)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(msg.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, msgID, delayTime, tmpstr, isExeInGame);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
	}
#endif
}

void IGAWorksManager::CancelClientPush(int msgID)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "cancelClientPush", "(I)V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, msgID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void IGAWorksManager::OpenAdPopcorn(string title, int titleColor, bool isDeviceAutoRotate)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "openAdPopcorn", "(Ljava/lang/String;IZ)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(title.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, tmpstr, titleColor, isDeviceAutoRotate);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
	}
#endif
}

void IGAWorksManager::OpenCouponDialog(bool showResultMsgToast)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "openCouponDialog", "(Z)V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, showResultMsgToast);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void IGAWorksManager::OpenNanuFanPage(bool openAutomatically)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;

	if (!utilObj.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "openNanuFanPage", "(Z)V"))
	{
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, openAutomatically);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}



void IGAWorksManager::OnLoadPopup(bool isLoad)
{
	if (listener == nullptr)
		return;

	listener->onPopupLoaded(isLoad);
}

void IGAWorksManager::OnEnablePush(bool isSuccess, bool isEnablePush)
{
	if (listener == nullptr)
		return;

	listener->onEnablePush(isSuccess, isEnablePush);
}

void IGAWorksManager::OnPopupDeepLinkClicked(const string& data)
{
	if (listener == nullptr)
		return;

	listener->onPopupDeepLinkClicked(data);
}

void IGAWorksManager::OnPopupClicked()
{
	if (listener == nullptr)
		return;

	listener->onPopupClicked();
}

void IGAWorksManager::OnPopupCancelBtnClicked()
{
	if (listener == nullptr)
		return;

	listener->onPopupCancelBtnClicked();
}



void IGAWorksManager::OnCloseAdPopcorn()
{
	if (listener == nullptr)
		return;

	listener->onCloseAdPopcorn();
}


void IGAWorksManager::OnCouponInputResult(bool result, string& msg, int itemKey, string& itemName, Nx::int64 quantity)
{
	if (listener == nullptr)
		return;

	listener->onCouponInputResult(result, msg, itemKey, itemName, quantity);
}

void IGAWorksManager::OnLoadedNanuFanPage(string& url)
{
	if (listener == nullptr)
		return;

	listener->onLoadedNanuFanPage(url);
}

void IGAWorksManager::SetListener(IGAWorksManager::Listener * worksListener)
{ 
	listener = worksListener; 
}

void IGAWorksManager::setUserId(Nx::int64 uid)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IGAWorksManagerObject utilObj;
	if (!utilObj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, IGAWORKS_JAVA_OBJECT, "initUid", "(Ljava/lang/String;)V"))
	{
		std::string uuid = "user" + Nx::StringConverter::toString(uid);
		jstring tmpstr = t.env->NewStringUTF(uuid.c_str());
		t.env->CallVoidMethod(utilObj.getObject(), t.methodID, tmpstr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
	}
#endif	
}
