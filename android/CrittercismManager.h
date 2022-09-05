/********************************************************************
	file name:	CrittercismManager.h
	
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

#define CRITTERCISM_OBJECT "com/newzensoft/pfutil/CrittercismMgr"

class CrittercismManager : public Singleton < CrittercismManager >
{

	public:
		

		
		CrittercismManager();
		~CrittercismManager();

	public:
		
		// 정의된 에러를 남긴다.
		void WriteHandledException(string error);
	
		// 이전에 클래쉬로 인해 어플이 종료되었는지 여부 판단.
		bool DidCrash();

		void critterLeaveBreadcrumb(string breadcrumb);

};
