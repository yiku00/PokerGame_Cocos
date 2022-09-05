#pragma once

#include "NxFramework.h"

class HandsHistoryContentPanel : public Panel
{
public:

	enum HISTORY_TYPE{
		HISTORY_SEVEN_POKER,
		HISTORY_HIGH_LOW,
		HISTORY_BADDUGI,
		HISTORY_HODEM,
	};

	HandsHistoryContentPanel(HISTORY_TYPE type);
	virtual ~HandsHistoryContentPanel();

private:
	void initPanel();
public:
	void setActivate(bool activate);
	
private:
	void refreshAmount();
private:
	CCSize mContentsSize;
	Panel* mMainPanel;


	HISTORY_TYPE mType;	
	Nx::Label* mTitleLanbel;
	Nx::Label* mTitleUnderLanbel;
	//세븐 포커 dmy_record_sevenpoker.mxml
	Nx::Label* mPoker_RotiflAmountLabel;	//로티플
	Nx::Label* mPoker_StiflAmountLabel;	//스티플
	Nx::Label* mPoker_4CardAmountLabel;		//포카드
	Nx::Label* mPoker_FullHouseAmountLabel;		//플하우스
	Nx::Label* mPoker_FlushAmountLabel;		//플러쉬
	Nx::Label* mPoker_StraitAmountLabel;		//스트레이트
	Nx::Label* mPoker_TripleAmountLabel;		//스티플
	Nx::Label* mPoker_2PairAmountLabel;		//2페어
	Nx::Label* mPoker_1PairAmountLabel;		//1페어
	Nx::Label* mPoker_DieAmountLabel;		//다이
	//하이로우  dmy_record_highlow
	Nx::Label* mHighTitle;
	Nx::Label* mHigh_FullHouseAmountLabel;	//하이 풀하우스
	Nx::Label* mHigh_FlushAmountLabel;	//하이 플러쉬
	Nx::Label* mHigh_StraitAmountLabel;	//하이 스트레이트
	Nx::Label* mHigh_TripleAmountLabel;	//하이 트리플
	Nx::Label* mHigh_2PairAmountLabel;	//하이 2페어
	Nx::Label* mHigh_1PairAmountLabel;	//하이 1페어이하
	Nx::Label* mLowTitle;
	Nx::Label* mLow_6TopAmountLabel;	//로우 6탑
	Nx::Label* mLow_7TopAmountLabel;	//로우 7탑
	Nx::Label* mLow_8TopAmountLabel;	//로우 8탑
	Nx::Label* mLow_9TopAmountLabel;	//로우 9탑
	Nx::Label* mLow_10TopAmountLabel;	//로우 10탑
	Nx::Label* mLow_jTopAmountLabel;	//로우 j탑이하
	Nx::Label* SwingTitle;
	Nx::Label* mSwing_RotiflAmountLabel;	//스윙 로티플
	Nx::Label* mSwing_StiflAmountLabel;	//스윙 스티플
	Nx::Label* mSwing_4CardAmountLabel;	//스윙 포카드
	Nx::Label* mHighLow_totalDieAmountLabel;	//총 다이 횟수
	//바둑이 dmy_record_badugi.mxml
	Nx::Label* mBadugi_GolfAmountLabel;		//골프
	Nx::Label* mBadugi_SecondAmountLabel;	//세컨드
	Nx::Label* mBadugi_ThirdAmountLabel;	//서드
	Nx::Label* mBadugi_5TopAmountLabel;	//5탑
	Nx::Label* mBadugi_6TopAmountLabel;	//6탑
	Nx::Label* mBadugi_7TopAmountLabel;	//7탑
	Nx::Label* mBadugi_8TopAmountLabel;	//8탑
	Nx::Label* mBadugi_9TopAmountLabel;	//9탑
	Nx::Label* mBadugi_10TopAmountLabel;	//10탑
	Nx::Label* mBadugi_JTopAmountLabel;	//J탑
	Nx::Label* mBadugi_QTopAmountLabel;	//Q탑
	Nx::Label* mBadugi_KTopAmountLabel;	//K탑
	Nx::Label* mBadugi_BaseAmountLabel;	//베이스
	Nx::Label* mBadugi_Under2BaseAmountLabel;	//투베이스 이하
	Nx::Label* mBadugi_TotalDieAmountLabel;	//총 다이 횟수
	//텍사스 홀덤 dmy_record_texas.mxml
	Nx::Label* mHodem_RotiflAmountLabel;	//로티플
	Nx::Label* mHodem_StiflAmountLabel;	//스티플
	Nx::Label* mHodem_4CardAmountLabel;		//포카드
	Nx::Label* mHodem_FullHouseAmountLabel;		//플하우스
	Nx::Label* mHodem_FlushAmountLabel;		//플러쉬
	Nx::Label* mHodem_StraitAmountLabel;		//스트레이트
	Nx::Label* mHodem_TripleAmountLabel;		//스티플
	Nx::Label* mHodem_2PairAmountLabel;		//2페어
	Nx::Label* mHodem_1PairAmountLabel;		//1페어
	Nx::Label* mHodem_DieAmountLabel;		//다이	
};
