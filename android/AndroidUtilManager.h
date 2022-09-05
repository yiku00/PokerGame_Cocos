/********************************************************************
	file name:	AndroidUtilManager.h
	
	purpose:	
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "NxSingleton.h"
#pragma once

#include "NxDefine.h"
#include "pch.h"

#include "NxSingleton.h"
#include "NxFramework.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif

#define ANDROID_UTIL_OBJECT "com/newzensoft/pfutil/PFUtil"

class AndroidUtilManager : public Singleton < AndroidUtilManager >
{
	public:
		AndroidUtilManager();
		~AndroidUtilManager();

	public:
		std::string Test();
	void Init();
	// 웹 뷰 처음 만들때(자동으로 이 함수를 호출하면 자동으로 보여짐)
	void InitWebView(string url, int x, int y, int w, int h);
	void initAdultView(string url, int x, int y, int w, int h);
	// 감춰진 뷰를 보이게 할때
	void ShowWebView();
	// 만들어진 웹뷰 안보이게 할때
	void HideWebView();
	// 웹 뷰 없앨때 부르세용.
	void ReleaseWebView();
	// 디바이스 id 알아내기
	string GetDeviceID();
	// 폰번호 알아내기
	string GetPhoneNumber();
	// os 버전
	string GetOSVersion();
	// 화면 너비
	int GetScreenWidth();
	// 화면 높이
	int GetScreenHeight();

	void DeleteWebView();

	void ShowCustomEditTextField(std::string text);
	void HideCustomEditTextField();
	void InitCustomEditTextField();
	void ReleaseCustomEditTextField();

	void RegisterAlarm(int millis, std::string msg, int repeat, int alarmIdx);
	void UnregisterAlarm(int alarmIdx);

	void OpenAdultURL(string url, int uid, string ip);

	void OpenShare();
};