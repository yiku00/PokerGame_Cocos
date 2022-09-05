/********************************************************************
filename: 	LobbyTourSelectPanel.h

purpose:	토너먼트 입장 선택창에서 입장 버튼 말고 최종 우승 상금 및 최근 우승 , ROUND1 , ROUND2 신청하기 상품등 표시
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_TourStepInfo.pb.h"
//#include "LobbyTournamentSubTop.h"
#include "W_TourInfo.pb.h"
#include "LobbyTourRewardListPanel.h"

#define COLOR_WINERGIF	ccc3(88, 42, 11)
#define COLOR_GIFTCOUNT ccc3(110, 58, 1)
#define BAR_WIDTH 180

class LobbyTourSelectPanel : public Panel, public Button::Listener , public Panel::Listener
{
public:
	LobbyTourSelectPanel();
	virtual ~LobbyTourSelectPanel();

	void InitPanel();
	void InitImage();
	void InitButton();

	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);
	virtual void onLayerMessage(const string& msg);
	virtual void onEnter() override;

	void update(float dt);

	void ShowSelectPanel(int round = 0);
	void SetMyRank();
	void SetMyBonus();
	void SetRound();
	void SetRanker();
	void SetTitleName();
	void SendTournamentReady(int _index, int _stepIndex);
	void SetJoinButton(int _index, W_TourStepInfo _info);
	void ApplyRankGamePopup();
	void SetRoundInfoTable(W_TourInfo _info);
	void SetRankGift(int _index, int _rank, int64 _gold, int _fame, bool _visible = true);
	void SetBonusPercentBar(int _now, int _max);
	void SetRankPercentBar();
	bool GameEnterCheck(int _step);

	void InitRankPhoto(int _index, bool isTryDownload);
	void UpdateRankPhoto(int _cellIndex);

	void refreshReward();	//보상 리워드 출력
	void initSeasonDesc();
	void initRoundState();	//버튼 , round dec 
	void refreshWindowColor();	// 윈도우 글자 색깔 수정

	void refreshData();	//

public:
	int m_SelectedIndex;

	//LobbyTournamentSubTop* m_SubTopPanel;
	Panel* m_pEnterButton[2];

	Panel* m_pRankGift[6];
	
	Widget* m_pRankerPhoto[3];

	Nx::Label* mCurrentRoundLabel;
	Button* mLeftRoundBtn;
	Button* mRightRoundBtn;
	LobbyTourRewardListPanel* mTourRewardListPanel;
	int mRoundIndex;


	Widget* mReputeGaugebar;
	Widget* mWinGaugebar;

	//보상 부분 관련
	Button* mRewardBtn;
	Nx::Label* mRewardStateLabel;

	Panel* mAddEnterPanel;
	Button* mEnterBtn;	//ppanel 붙인곳에서 바로 한다.
	Nx::Label* mEnterPay;
	// 이름
	Nx::Label* mTournamentName;
	//이번 시즌
	Nx::Label* mSeasonDesc;
	//다음 라운드	
	SkelObject* mEnterIcon;

	Widget* mMyGauseBar;
	Nx::Label* mMyState;

	Widget* mVictoryGauseBar;
	Nx::Label* mVictoryState;

	//현재 시즌 등급
	Nx::Label* mNowSeasonGrade;
	Nx::Label* mNowSeasonGradeUnder;
	SkelObject* mNowSeasonBg;
	
	//5회 승리시 보상
	Nx::Label* mReward;
	Nx::Label* mRewardUnder;
	SkelObject* mRewardBg;
	
	//최근 우승자
	Nx::Label* mRecentWinner;
	Nx::Label* mRecentWinnerUnder;
	SkelObject* mRecentWinnerBg;

	//user1
	Nx::Label* mUser1;
	
	//user2
	Nx::Label* mUser2;
	
	//user3
	Nx::Label* mUser3;
	

	SkelObject* mTournamentIcon;
	SkelObject* mTournamentWindow;


	//현재 시즌 등급
	Button* mRankIconBtn;

	Button* mRuleBtn;
	Nx::Label* mRuleBtnLabel;

	Button* mSeasonRankInfoBtn;
	Nx::Label* mSeasonRankInfoBtnLabel;

	Widget* mRewardCompleteIcon;
};
