/********************************************************************
file name:	LobbyFriendInvitePanel.h

purpose:	로비씬에서 친구 초대창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "SmallButtonPanel.h"
#include "SmallBtnPanel.h"
#include "FriendCellMiddle.h"



class LobbyFriendInvitePanel : public Panel, public Button::Listener, public CCTableViewDataSource, public CCTableViewDelegate
{
	typedef vector<SmallButtonPanel*> INVITE_REWARD_CONTAINER;
	typedef vector<FriendCellMiddle*> FriendCellContainer;

public:
	LobbyFriendInvitePanel();
	virtual ~LobbyFriendInvitePanel();	

public:
	virtual bool handling(STCMD &stCmd);
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);

	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view){}
	virtual void scrollViewDidZoom(CCScrollView* view){}

public:
	virtual void onClicked(const string& buttonName);
	
public:
	void setActivate(bool activate);
	void SetFriendlList();
	void refreshTableView();
	void facebookRefresh();

private:
	void initPanel();
	void drawTableView();

	void initFaceBookLoginBtn();
	void initFaceBookRewardData();	// facebook 친구 관련 적용
	void initRewardGaugeBar();		//보상 게이지 및 위치 친구 count 수ㅠ
	void initRewardButton();
	int getInvitedFriendListCount();	// 현재 게임 설치한 친구 수
	void refreshRewardButton();

	void sendFaceFriendGiftSendReq(int idx);
	void recvFaceFriendGiftSendRes(HttpMessage* msg);
	bool isPossibleReward(int id);
private:
	
	INVITE_REWARD_CONTAINER mRewardBtns;
	Widget* mRewardGaugeBar;
	Panel* mGaugeIndigatorPanel;

	Nx::TableView* mTableView;
	CCSize mCellSize;

	Panel* mMainPanel;
	CCSize mContentSize;

	Widget* mGaugeBar;
	Button* mFacebookLoginBtn;
	Nx::Label* mFaceBookMsgLabel;	//보상을 받으려면 
	Nx::Label* mNoFriendLabel;
	
	//화살표
	int mMaxFriendCount;
	Nx::Label* mFriendCount;
	Widget* mFriendCountBg;
	int mCountPos;
	int mCountBgPos;

	FriendCellContainer mFriends;
	Nx::Label* mNoFriendsLabel;

	Panel* mFaceBookPanel;

	Nx::Label* mTitleLabel;
	Nx::Label* mTitleUnderLabel;
	Nx::Label* mDesc_1;
	Nx::Label* mDesc_2;

	//페이스북 친구
	Button* mFaceBookInviteBtn;
	Nx::Label* mFacebookInviteLabel;
	Nx::Label* mFacebookInviteUnderLabel;
	//자동수령 , 자동 선물
	SmallButtonPanel* m_pSmallButton[2];
};