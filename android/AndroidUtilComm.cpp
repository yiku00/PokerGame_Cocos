/**********************************
 Java Native Interface library
**********************************/
#include <jni.h>
#include "jni/JniHelper.h"
#include "GameDataManager.h"
#include "PanelHelper.h"

extern "C"
{

	/** This is the C implementation of the Java native method.
	@param env Pointer to JVM environment
	@param thiz Reference to Java this object
	*/
	JNIEXPORT void JNICALL Java_com_newzensoft_pfutil_PFUtil_jnitest(JNIEnv* env, jclass thiz, jstring stringParam)
	{
		std::string stdString = JniHelper::jstring2string(stringParam);
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_pfutil_PFUtil_SetEditText(JNIEnv* env, jclass thiz, jstring stringParam)
	{
		std::string stdString = JniHelper::jstring2string(stringParam);
		GameDataManager::getSingletonPtr()->SetEdittextString(stdString);
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_pfutil_CustomWebView_AdultResult(JNIEnv* env, jclass thiz, jboolean result)
	{
		bool isResult = result;
		CCLog("Java_com_numixent_pfutil_CustomWebView_AdultResult result = %d", isResult);		
		if (isResult) {
			SceneManager::getSingleton().getCurrentScene()->onMessage("adult_sucess");
		}
		else {
			SceneManager::getSingleton().getCurrentScene()->onMessage("adult_fail");
		}

	}

	JNIEXPORT void JNICALL Java_com_newzensoft_pfutil_CustomWebView_OnAuthFinished(JNIEnv *env, jclass clazz)
	{
		WebService::getSingleton()._sendGameDataReq();
	}
}

