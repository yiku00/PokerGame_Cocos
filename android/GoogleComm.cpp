/**********************************
 Java Native Interface library
**********************************/
#include <jni.h>
#include "jni/JniHelper.h"
#include "android/GoogleManager.h"

extern "C"
{

	/** This is the C implementation of the Java native method.
	@param env Pointer to JVM environment
	@param thiz Reference to Java this object
	*/
	JNIEXPORT void JNICALL Java_com_newzensoft_social_GoogleManager_OnGoogleLoginResult(JNIEnv* env, jclass thiz, jboolean result, jstring _id, jstring _name, jstring _email, jstring _photoUrl)
	{
		CCLog("Java_com_newzensoft_social_GoogleManager_OnGoogleLoginResult");
		bool isResult = result;
		std::string str_id = JniHelper::jstring2string(_id);
		std::string str_name = JniHelper::jstring2string(_name);
		std::string str_email = JniHelper::jstring2string(_email);
		std::string str_photoUrl = JniHelper::jstring2string(_photoUrl);
		GoogleManager::getSingleton().setGoogleResult(isResult);
		GoogleManager::getSingleton().setGoogleUserId(JniHelper::jstring2string(_id));
		GoogleManager::getSingleton().setGoogleName(JniHelper::jstring2string(_name));
		GoogleManager::getSingleton().setGoogleEmail(JniHelper::jstring2string(_email));
		GoogleManager::getSingleton().setGooglePhotoUrl(JniHelper::jstring2string(_photoUrl));

		GoogleManager::getSingleton().OnLoginResult(isResult, str_id, str_name, str_email, str_photoUrl);
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_social_GoogleManager_GoogleData(JNIEnv* env, jclass thiz, jboolean result, jstring _id, jstring _name, jstring _email, jstring _photourl)
	{
		bool isResult = result;
		CCLog("isResult = %d", isResult);
		GoogleManager::getSingleton().setGoogleResult(isResult);
		GoogleManager::getSingleton().setGoogleUserId(JniHelper::jstring2string(_id));
		GoogleManager::getSingleton().setGoogleName(JniHelper::jstring2string(_name));
		GoogleManager::getSingleton().setGoogleEmail(JniHelper::jstring2string(_email));
		GoogleManager::getSingleton().setGooglePhotoUrl(JniHelper::jstring2string(_photourl));
		CCLog("Java_com_newzensoft_social_GoogleManager_GoogleData");

	}

	JNIEXPORT void JNICALL Java_com_newzensoft_social_GoogleManager_OnGoogleLogOut(JNIEnv* env, jclass thiz, jboolean result)
	{
		bool isResult = result;
		GoogleManager::getSingleton().logOutResult(isResult);
		CCLog("Java_com_newzensoft_social_GoogleManager_OnGoogleLogOut");
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_social_GoogleManager_OnLoginConnected(JNIEnv* env, jclass thiz)
	{
		GoogleManager::getSingleton().OnLoginConnected();
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_social_GoogleManager_OnGameConnected(JNIEnv* env, jclass thiz)
	{
		GoogleManager::getSingleton().OnGameConnected();
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_social_GoogleManager_OnGameConnectionFailed(JNIEnv* env, jclass thiz)
	{
		CCLog("Java_com_newzensoft_social_GoogleManager_OnGameConnectionFailed 1");
		GoogleManager::getSingleton().OnGameConnectionFailed();
		CCLog("Java_com_newzensoft_social_GoogleManager_OnGameConnectionFailed 2");
	}
}
