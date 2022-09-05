#include "android/GoogleManager.h"
#include "jni/JniHelper.h"
#include "CmdList.h"
#include "CmdQueue.h"

template<> GoogleManager* Singleton<GoogleManager>::msSingleton = 0;

struct GoogleManagerObject
{
	JNIEnv* env;
	jobject object;

	GoogleManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, GOOGLE_JAVA_OBJECT, "instance", "()Ljava/lang/Object;"))
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

	~GoogleManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};


GoogleManager::GoogleManager()
{
	mIsResult = false;
}

GoogleManager::~GoogleManager()
{
	
}

void GoogleManager::googleLogin()
{
	mGameResulted = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("GoogleManager::googleLogin()");
	GoogleManagerObject googleObject;
	if (!googleObject.getObject())
		return;
	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, GOOGLE_JAVA_OBJECT, "signIn", "()V"))
	{
		CCLog("GoogleManager::googleLogin() 123");
		t.env->CallVoidMethod(googleObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
	CCLog("GoogleManager::googleLogin()4456");
#endif
}

void GoogleManager::googleLogOut()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("GoogleManager::googleLogOut()");
	GoogleManagerObject googleObject;
	if (!googleObject.getObject())
		return;
	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, GOOGLE_JAVA_OBJECT, "signOut", "()V"))
	{
		CCLog("GoogleManager::googleLogOut() 123");
		t.env->CallVoidMethod(googleObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
	CCLog("GoogleManager::googleLogOut()4456");
#endif
}

void GoogleManager::OnLoginResult(bool result, string googleID, string googleName, string googleEmail, string googlePhotoUrl)
{
	CCLog("GoogleManager::OnLoginResult");
	STCMD_GOOGLE_LOGIN_RESULT loginResult;
	loginResult.isSucess = result;
	loginResult.googleID = googleID;
	loginResult.googleName = googleName;
	loginResult.googleEmail = googleEmail;
	loginResult.googlePhotoUrl = googlePhotoUrl;
	CCLog("GoogleManager::OnLoginResult 221");
	CCmdQueue::getSingleton().pushQueue(loginResult);
	CCLog("GoogleManager::OnLoginResult googleID = %s", googleID.c_str());
}

void GoogleManager::googleInit()
{
	CCLog("googleInit");
	GoogleManagerObject googleObject;
	if (!googleObject.getObject())
		return;
	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, GOOGLE_JAVA_OBJECT, "googleInit", "()V"))
	{
		CCLog("googleInit excute");
		t.env->CallVoidMethod(googleObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
	
}

void GoogleManager::logOutResult(bool result)
{
	if (result) {
		//�α׾ƿ��϶� Ÿ��Ʋ�� �̵�
		initGoogleLoginData();
		CCLog("GoogleManager::OnLoginResult");
		STCMD_GOOGLE_LOGOUT_RESULT loginResult;
		loginResult.isSucess = result;		
		CCmdQueue::getSingleton().pushQueue(loginResult);		
	}
	else {
		//���� �޼���
	}
}

void GoogleManager::setGoogleResult(bool result)
{
	mIsResult = result;
	CCLog("googleInit mIsResult = %d", mIsResult);
}

void GoogleManager::initGoogleLoginData()
{
	mConnected = false;
	mGameConnected = false;
	mGameResulted = false;
	mIsResult = false;
	mGoogleId = "";
	mGoogleName = "";
	mGoogleEmail = "";
	mPhotoUrl = "";
}

void GoogleManager::submitLeaderBoard(int score)
{
	CCLog("submitLeaderBoard");
	GoogleManagerObject googleObject;
	if (!googleObject.getObject())
		return;
	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, GOOGLE_JAVA_OBJECT, "leaderBoardSubmit", "(I)V"))
	{
		CCLog("submitLeaderBoard excute");
		t.env->CallVoidMethod(googleObject.getObject(), t.methodID , score );
		t.env->DeleteLocalRef(t.classID);
	}
}

void GoogleManager::showLeaderBoard()
{
	CCLog("showLeaderBoard");
	GoogleManagerObject googleObject;
	if (!googleObject.getObject())
		return;
	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, GOOGLE_JAVA_OBJECT, "leaderBoardShow", "()V"))
	{
		CCLog("showLeaderBoard excute");
		t.env->CallVoidMethod(googleObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void GoogleManager::achieveUnlock()
{
	CCLog("achieveUnlock");
	GoogleManagerObject googleObject;
	if (!googleObject.getObject())
		return;
	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, GOOGLE_JAVA_OBJECT, "achieveUnlock", "()V"))
	{
		CCLog("achieveUnlock excute");
		t.env->CallVoidMethod(googleObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void GoogleManager::achieveIncrement()
{
	CCLog("achieveIncrement");
	GoogleManagerObject googleObject;
	if (!googleObject.getObject())
		return;
	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, GOOGLE_JAVA_OBJECT, "achieveIncrement", "()V"))
	{
		CCLog("achieveIncrement excute");
		t.env->CallVoidMethod(googleObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void GoogleManager::showAchieve()
{
	CCLog("showAchieve");
	GoogleManagerObject googleObject;
	if (!googleObject.getObject())
		return;
	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, GOOGLE_JAVA_OBJECT, "showAchieve", "()V"))
	{
		CCLog("showAchieve excute");
		t.env->CallVoidMethod(googleObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void GoogleManager::googleRevokeAccess()
{
	CCLog("GoogleManager revokeAccess");
	GoogleManagerObject googleObject;
	if (!googleObject.getObject())
		return;
	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, GOOGLE_JAVA_OBJECT, "revokeAccess", "()V"))
	{
		CCLog("GoogleManager revokeAccess excute");
		t.env->CallVoidMethod(googleObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void GoogleManager::OnLoginConnected()
{
	mConnected = true;
}

void GoogleManager::OnGameConnected()
{
	mGameConnected = true;
	mGameResulted = true;
}

void GoogleManager::OnGameConnectionFailed()
{
	mGameConnected = false;
	mGameResulted = true;
}
