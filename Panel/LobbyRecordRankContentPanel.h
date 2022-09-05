/********************************************************************
file name:	LobbyRecordRankContentPanel.h

purpose:	전체 랭킹 list 창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "W_ReputeRankInfo.pb.h"

class LobbyRecordRankContentPanel : public Panel, public Button::Listener
{	
public:
	enum BG_TYPE
	{
		BG_TYPE_MY,
		BG_TYPE_ODD,
		BG_TYPE_EVENT
	};
	LobbyRecordRankContentPanel();
	virtual ~LobbyRecordRankContentPanel();

public:
	virtual void onClicked(const string& buttonName);

public:
	void setReputeRankInfo(W_ReputeRankInfo rankInfo);
	void setRank(int rank);
	void setUserName(int lv , string name);
	void setVipIcon(int vip);
	void setRepute(int repute);
	void setType(BG_TYPE type);
	void initFriendPhoto(bool down);
	void initMyPhoto();
	void setMyRankType();
private:
	void _init();	

private:
	CCSize mContentsSize;
	Panel* mMainPanel;	
	int mIdx;

	SkelObject* mBg;
	Nx::Label* mUserName;
	SkelObject* mRankIcon;		//유저 등급 아이콘
	SkelObject* mTrophy;
	CCLabelBMFont* mRankBmp;
	CCLabelBMFont* mReputeBmp;

	Nx::Label* mNoRankLabel;
	Nx::Label* mNoRankUnderLabel;
	Widget* mUserPhoto;
	W_ReputeRankInfo mReputeRankInfo;
	Widget* mPointBg;
};