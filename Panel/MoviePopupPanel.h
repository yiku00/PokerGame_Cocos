/********************************************************************
	file name:	MoviePopupPanel.h
	
	purpose:	동영상 창 관련 창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "SmallButtonPanel.h"
#include "W_RewardInfo.pb.h"

class RewardPopupPanel : public Panel, public Button::Listener
{	
public:
	enum REWARD_POPUP_TYPE {
		POPUP_RESULT_OK,		//동영상 관련 ok
		POPUP_FULL,				//동영상을 다 봤다
		POPUP_DELAY,			//30초 이따가 해라.
		COMMON_REWARD,			//일반적 보상창
		SHOP_RUBY,				//루비 상점
		LETTER_REWARD,			//편지 보상
		BIG_POT,				//대박찬스 보상
		EVENT_REWARD,			//이
	};

	RewardPopupPanel(REWARD_POPUP_TYPE  type);
	RewardPopupPanel(int rewardRuby, int rubyId);
	~RewardPopupPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);	
public:
	void setDesc(string title , string content);
	void setRewardInfo(W_RewardInfo rewardInfo);
	void setRubyReward(int rewardRuby, int rubyId);		//루비 샀을대 처리
	void setLetterReward(W_RewardInfo rewardInfo);

private:
	void initPanel();
	void initDesc();
	void initItemBox();

private:		
	REWARD_POPUP_TYPE mType;
	SmallButtonPanel* mCloseBtnPanel;
	Nx::Label* mTitle;
	Nx::Label* mTitleUnder;	
	Nx::Label* mDesc;
	W_RewardInfo* mRewardInfo;	
	SkelObject* mRewardBg;

	SkelObject* mRewardIcon;
	Nx::Label* mRewardLabel;
	Widget* mCharacterImg;
	//루비 관련
	int mRewardRuby;
	int mRubyId;
};
