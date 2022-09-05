/********************************************************************
	file name:	TCPService.h
	
	purpose:	
*********************************************************************/
#pragma once

#include "NxSingleton.h"
#include "RefDefine.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif

#define IGAWORKS_JAVA_OBJECT "com/numixent/common/IGAWorksActivity"

enum COHORT_KIND
{
	COHORT_1		= 1,
	COHORT_2		= 2,
	COHORT_3		= 3
};

class IGAWorksManager : public Nx::Singleton<IGAWorksManager>
{
public :
	class Listener
	{
		public:

			// 팝업이 로딩되었을 때
			virtual void onPopupLoaded(const bool isLoad) = 0;
			// 팝업창의 딥링크가 클릭되었을때
			virtual void onPopupDeepLinkClicked(const string& ani) = 0;

			// 팝업창이 클릭되었을 때
			virtual void onPopupClicked() = 0;
			// 팝업창의 닫기 버튼을 클릭했을 때
			virtual void onPopupCancelBtnClicked() = 0;

			// 팝업창이 닫혀졌을 때
			virtual void onCloseAdPopcorn() = 0;

			// 푸시 ENABLE 여부가 적용되었을 때
			virtual void onEnablePush(bool isSuccess, bool isEnablePush) = 0;
			// 쿠폰 입력 결과가 넘어왔을 때
			virtual void onCouponInputResult(bool result, string& msg, int itemKey, string& itemName, Nx::int64 quantity) = 0;

			// 나누 팬 페이지가 열렸을 때
			virtual void onLoadedNanuFanPage(string& url) = 0;
	};

	IGAWorksManager();
	~IGAWorksManager();

public:
	void Init();

	/*
	- 리스너를 등록한다.
	- 리스너가 등록되지 않으면 IGAWORKS의 디폴트 행위가 취해진다.
	*/
	void SetListener(IGAWorksManager::Listener * worksListener);



	////////////////////////////////////////////////////////////////////////
	////////////////// ABOUT ADBRIX				////////////////////////////
	////////////////////////////////////////////////////////////////////////
	/*
	 첫경험 시간 추적 
	 userActivity : 유저 행동 이름
	*/
	void FirstTimeExperienceTracking(string userActivity);
	/* 
	첫경험 시간 추적 
	userActivity : 유저 행동 이름, param : 세부 항목
	*/
	void FirstTimeExperienceTracking(string userActivity, string param);
	/*
	구입 내역 추적
	userActivity : 구입 내역 이름
	*/
	void BuyTracking(string userActivity);
	/*
	유저 행동 추적
	userActivity : 추적할 행동명
	*/
	void ActivityTracking(string userActivity);
	/*
	유저 행동 추적
	userActivity : 추적할 행동명, param : 세부 항목
	*/
	void ActivityTracking(string userActivity, string param);
	/*
	코호트 추적
	cohortKind : 코호트 종류(1, 2, 3), userActivity : 추적할 행동명
	*/
	void CohortTracking(COHORT_KIND cohortKind, string userActivity);




	////////////////////////////////////////////////////////////////////////
	////////////////// ABOUT NOTICE POPUP 		////////////////////////////
	////////////////////////////////////////////////////////////////////////
	/*
	공지 팝업창 로딩 - 팝업창에 필요한 리소스만 로딩
	공지 팝업창을 보여줄려면 ShowPopup을 호출해야함.
	Listener가 등록되지 않으면 자동으로 ShowPopup이 호출된다.
	*/
	void LoadPopup();
	/*
	모든 공지팝업을 닫는다.
	*/
	void CloseAllPopup();
	/*
	최상위 팝업창(현재 열려있는 팝업창)을 닫는다.
	*/
	void CloseTopPopup();
	/*
	팝업창을 연다.
	*/
	void ShowPopup();
	/*
	- 팝업창 로딩 여부 
	- LoadPopup이 호출되면 그에 대한 결과로 이 함수가 호출됨
	- isLoad : 로딩 여부 
	*/
	void OnLoadPopup(bool isLoad);
	/*
	- 팝업창의 딥링크가 클릭되었음
	- 일반 링크 혹은  딥링크의 주소가 URL이면 이 함수는 호출되지 않는다.
	- data : 딥링크를 위한 JSON 데이터
	*/
	void OnPopupDeepLinkClicked(const string& data);
	/*
	- 팝업창 안의 이미지를 클릭한 경우 호출된다.
	- 딥링크인 경우 OnPopupDeepLinkClicked도 같이 호출된다.
	*/
	void OnPopupClicked();
	/*
	- 팝업창 안의 닫기 버튼을 클릭한 경우 호출된다.
	*/
	void OnPopupCancelBtnClicked();





	////////////////////////////////////////////////////////////////////////
	////////////////// ABOUT ADPOPCORN			////////////////////////////
	////////////////////////////////////////////////////////////////////////
	/*
	- 애드팝콘창을 연다.
	- title : 애드팝콘창의 상단 제목
	- themeColor : 애드팝콘창의 테마 (ARPG순으로 하는듯...)
	- isDeviceAutoRotate : 가로모드일때 애드팝콘 창이 뜨면 자동 세로로 바꿀지 여부
	*/
	void OpenAdPopcorn(string title = "", int themeColor = 0xff3d7caf, bool isDeviceAutoRotate = true);

	/*
	- 애드팝콘창을 닫는다.
	*/
	void OnCloseAdPopcorn();
	




	////////////////////////////////////////////////////////////////////////
	////////////////// ABOUT PUSH(REMOTE AND LOCAL)	////////////////////////////
	////////////////////////////////////////////////////////////////////////
	/*
	- 푸시 사용 여부 설정
	- enable : 사용 여부
	*/
	void SetEnablePush(bool enable);
	/*
	- 클라이언트 푸시 설정
	- msgID : 클라이언트 푸시 그룹 번호(클라이언트에서 알아서 정하세요)
	- delayTime : 몇초 후에 푸시 실행 (초단위)
	- msg : 푸시 메시지 내용
	- isExeInGame : 게임 실행중에도 실행할지 여부
	*/
	void SetClientPush(int msgID, int delayTime, string& msg, bool isExeInGame);
	/*
	- 클라이언트 푸시 설정한 걸 취소한다.
	- msgID : 취소할 클라이언트 푸시 그룹 번호(클라이언트에서 알아서 정하세요)
	*/
	void CancelClientPush(int msgID);
	/*
	- SetEnablePush 함수에 대한 결과
	- isSuccess : 푸시 사용 여부 적용 성공 여부
	- isEnablePush : 사용 여부
	*/
	void OnEnablePush(bool isSuccess, bool isEnablePush);




	////////////////////////////////////////////////////////////////////////
	////////////////// ABOUT COUPON				////////////////////////////
	////////////////////////////////////////////////////////////////////////
	/*
	- 쿠폰 입력창을 연다.
	- showResultMsgToast : 결과를 토스트로 보여줄지 여부
	*/
	void OpenCouponDialog(bool showResultMsgToast);
	/*
	- 쿠폰 입력한 결과를 보여준다.
	- OpenCouponDialog(true)로 설정시 이 콜백 함수는 호출되지 않는다.
	- result : 결과
	- msg : 메시지 내용
	- itemKey : 아이템 키
	- itemName : 아이템 이름
	- quantity : 아이템 양
	*/
	void OnCouponInputResult(bool result, string& msg, int itemKey, string& itemName, Nx::int64 quantity);

	////////////////////////////////////////////////////////////////////////
	////////////////// ABOUT NANU				////////////////////////////
	////////////////////////////////////////////////////////////////////////
	/*
	- 쿠폰 입력창을 연다.
	- openAutomatically : 웹브라우저에서 자동으로 열지 여부
	- 자동으로 열기 싫으면 false -> OnLoadedNanuFanPage로 콜백이 날라온다.
	*/
	void OpenNanuFanPage(bool openAutomatically);

	void OnLoadedNanuFanPage(string& url);

	void setUserId(Nx::int64 uid);
	
private:
	IGAWorksManager::Listener * listener;
};
