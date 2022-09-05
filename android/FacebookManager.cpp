#include "pch.h"
#include "android/FacebookManager.h"
#include "jni/JniHelper.h"
#include "Web/WebService.h"
#include "PanelHelper.h"


template<> FacebookManager* Nx::Singleton<FacebookManager>::msSingleton = 0;


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


struct FacebookManagerObject
{
	JNIEnv* env;
	jobject object;

	FacebookManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, FACEBOOK_OBJECT, "instance", "()Ljava/lang/Object;"))
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

	~FacebookManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

FacebookManager::FacebookManager()
{
	listener = nullptr;

	SetPrint(true);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;
	CCLOG("facebookObject is not null!!!!");
	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "init", "()V"))
	{
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

FacebookManager::~FacebookManager()
{
	clearFriendList();
}

void FacebookManager::ConnectFB()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "ConnectFB", "()V"))
	{
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void FacebookManager::clearFriendList()
{
	for (int i = 0, j = m_friendListData.size(); i < j; i++)
	{
		while (!m_friendListData.empty())
		{
			FaceBookFriendData * data = m_friendListData[i];
			m_friendListData.erase(m_friendListData.begin());
			NX_SAFE_DELETE(data);
		}
	}
}

void FacebookManager::OnFacebookEvent(int _event, std::string &paramData)
{
	CCLog("OnFacebookEvent _event = %d", _event);
	switch (_event)
	{
	case FB_ERROR:
		break;
	case FB_LOGIN_START:
		break;
	case FB_LOGIN_SUCCESS:
		SetFacebooUserData();
		CCLog("Success");
		WebService::getSingletonPtr()->_sendFacebookLoginReq(m_UserData.fb_id,m_UserData.fb_photoUrl);
		break;
	case FB_LOGIN_CANCEL:
		CCLog("cancel");
		PanelHelper::popLoadingPanel();
		break;
	case FB_LOGIN_FAIL:
		CCLog("FB_LOGIN_FAIL");
		PanelHelper::popLoadingPanel();
		break;
	case FB_LOGOUT:
		break;
	case FB_FRIENDLIST_REQUEST_SUCCESS:
	{
		SetFacebookFriendList(&paramData);
		break;
	}
	case FB_FRIENDLIST_REQUEST_FAIL:
		break;
	case FB_SEND_EMAIL_SUCCESS:
		break;
	case FB_SEND_EMAIL_FAIL:
		break;
	case FB_FRIEND_INVITE_REQUEST_SUCCESS :
		// paramData is not user id token that you have sent but user's id.
		// so, you should save this value in your database if you prevent duplicate invitation.
		m_inviteSuccessUser = paramData;
		break;
	case FB_ALREADY_LOGOUT:
		break;
	case FB_LOGOUT_FAIL :
		break;
	}

	if (listener)
		listener->onFacebookEvent(_event, paramData);
}


void FacebookManager::SetFacebooUserData()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "GetFacebookUserData", "()V"))
	{
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void FacebookManager::RequestInvitableUserList(bool isNext)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "RequestInvitableUserList", "(Z)V"))
	{
		clearFriendList();

		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID, isNext);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void FacebookManager::RequestInviteUser(std::string user_id, std::string message)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "RequestInviteUser", "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(user_id.c_str());
		jstring tmpstr2 = t.env->NewStringUTF(message.c_str());
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID, tmpstr, tmpstr2);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(tmpstr);
		t.env->DeleteLocalRef(tmpstr2);
	}
#endif
}


FaceBookFriendData * FacebookManager::GetFacebookFriend(int idx)
{
	if (m_friendListData.size() == 0)
		return nullptr;

	if (idx >= m_friendListData.size())
		return nullptr;

	return m_friendListData[idx];
}

vector<FaceBookFriendData*> FacebookManager::GetAllFacebookFriends()
{
	return m_friendListData;
}


void FacebookManager::SetFacebookFriendList(string * paramData)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CSJson::Reader reader;
	CSJson::Value params;
	reader.parse(*paramData, params);

	CSJson::Value friendData;
	if (params.isMember("data"))
		friendData = params["data"];

	FaceBookFriendData * data;
	CCLog("faceooksize = %d", friendData.size());
	if (friendData.size() > 0)
	{
		for (int i = 0, j = friendData.size(); i < j; i++)
		{
			data = new FaceBookFriendData();

			data->id = friendData[i]["id"].asString();
			data->name = friendData[i]["name"].asString();
			data->pictureUrl = friendData[i]["picture"]["data"]["url"].asString();			
			CCLog("faceooksize i = %d , name = %s", i, data->name.c_str());
			m_friendListData.push_back(data);
		}
	}
	SceneManager::getSingleton().getCurrentScene()->onMessage("SetFacebookFriendList");
#endif
}

void FacebookManager::SetPrint(bool isPrint)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;
	
	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "setPrint", "(Z)V"))
	{
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID, isPrint);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void FacebookManager::LogOut()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "LogOut", "()V"))
	{
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void FacebookManager::appInviteOpenDialog(string applinkurl , string imgurl)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "appInviteOpenDialog", "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring tmpstr = t.env->NewStringUTF(applinkurl.c_str());
		jstring tmpstr2 = t.env->NewStringUTF(imgurl.c_str());
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID, tmpstr, tmpstr2);

		t.env->DeleteLocalRef(t.classID);
	}

#endif
}

void FacebookManager::appLink()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "appLink", "()V"))
	{
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void FacebookManager::RequestOriginUserList()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "RequestUserList", "()V"))
	{
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

std::string FacebookManager::getFacebookFriendName(string id)
{
	for (int i = 0, j = m_friendListData.size(); i < j; i++)
	{
		FaceBookFriendData * data = m_friendListData[i];
		if (data->id == id)
			return data->name;		
	}

	return id;
}
