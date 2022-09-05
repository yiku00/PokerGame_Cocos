/**********************************
 Java Native Interface library
**********************************/
#include <jni.h>
#include "jni/JniHelper.h"
#include "android/FacebookManager.h"

extern "C"
{

	/** This is the C implementation of the Java native method.
	@param env Pointer to JVM environment
	@param thiz Reference to Java this object
	*/
	JNIEXPORT void JNICALL Java_com_newzensoft_social_FacebookMgr_OnFacebookEvent(JNIEnv* env, jclass thiz, int _envId, jstring _data)
	{
		std::string friendData = JniHelper::jstring2string(_data);
		FacebookManager::getSingletonPtr()->OnFacebookEvent(_envId, friendData);
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_social_FacebookMgr_FacebookUserData(JNIEnv* env, jclass thiz, jstring _id, jstring _name, jstring _email, jstring _photourl)
	{
		FacebookManager::getSingletonPtr()->m_UserData.fb_id = JniHelper::jstring2string(_id);
		FacebookManager::getSingletonPtr()->m_UserData.fb_name = JniHelper::jstring2string(_name);
		FacebookManager::getSingletonPtr()->m_UserData.fb_email = JniHelper::jstring2string(_email);
		FacebookManager::getSingletonPtr()->m_UserData.fb_photoUrl = JniHelper::jstring2string(_photourl);
	}
}
