/**********************************
 Java Native Interface library
**********************************/
#include <jni.h>
#include "jni/JniHelper.h"
#include "android/AdmobManager.h"
#include "CmdList.h"
#include "SimplePopupPanel.h"
#include "HeroApp.h"
#include "GameStringDepot.h"
#include "CmdQueue.h"

extern "C"
{

	/** This is the C implementation of the Java native method.
	@param env Pointer to JVM environment
	@param thiz Reference to Java this object
	*/
	JNIEXPORT void JNICALL Java_com_newzensoft_admob_AdmobManager_CallBackSuccessRewardedVideoAd(JNIEnv* env, jclass thiz)
	{
        CCLog("Reward Earned!!!!!!!!!");
		AdmobManager::getSingleton().SetReward(true);
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_admob_AdmobManager_CallBackFailRewardedVideoAd(JNIEnv* env, jclass thiz)
	{
		STCMD_ADMOB_VIDEO_RESULT result;
		result.isResult = false;
		CCmdQueue::getSingleton().pushQueue(result);
		CCLog("Admob CallBack Fail");
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_admob_AdmobManager_CallBackOnRewardAdStarted(JNIEnv* env, jclass thiz)
	{


	}

	JNIEXPORT void JNICALL Java_com_newzensoft_admob_AdmobManager_CallbackOnRewardAdOpened(JNIEnv* env, jclass thiz)
	{


	}

	JNIEXPORT void JNICALL Java_com_newzensoft_admob_AdmobManager_CallBackOnRewardAdClosed(JNIEnv* env, jclass thiz)
	{
		AdmobManager::getSingleton().HandleReward();

	}

	JNIEXPORT void JNICALL Java_com_newzensoft_admob_AdmobManager_CallBackOnRewardAdLoaded(JNIEnv* env, jclass thiz)
	{
		AdmobManager::getSingleton().SetLoaded(true);
		if(AdmobManager::getSingleton().GetIntend())
		{
			AdmobManager::getSingleton().showRewardAd();
            AdmobManager::getSingleton().SetIntend(false);
		}
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_admob_AdmobManager_CallbackOnRewardAdFailToLoaded(JNIEnv* env, jclass thiz)
	{
		AdmobManager::getSingleton().SetLoaded(false);
		AdmobManager::getSingleton().SetReward(false);
		STCMD_ADMOB_VIDEO_RESULT result;
		AdmobManager::getSingleton().HandleReward();
	}
}
