/********************************************************************
file name:	BuySucessPanel.h

purpose:	물건 구매 성공창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "SmallBtnPanel.h"
#include "W_RewardInfo.pb.h"

class BuySucessPanel : public Panel, public SkelObject::EventListener
{	
public:
	enum BUY_TYPE
	{
		BUY_MEMBERSHIP,
		BUY_RUBY,
		BUY_CHARACTER,
		BUY_CARD,
	};
	BuySucessPanel(BUY_TYPE type);
	virtual ~BuySucessPanel();

public:
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onEvent(int trackIdx, spEvent* event) override;
	virtual void onEnter() override;


public:
	void setSkinSucess(int characterInfoId, int useRuby);
	void setCharacterSucess(int characterInfoId , int useRuby);
	void setMemberShipSucess(int memberShipId, W_RewardInfo rewardInfo);
	void setRubySucess(int rewardRuby, int rubyId, bool isFirstBuy);
	void update(float dt);
private:
	void initPanel();	
	void initTxt();
	void initImg();
	

private:	
	BUY_TYPE mType;
	SkelObject* mAni;
	Widget* mItemImg;
	CCLabelBMFont* mTerm;
	//골드 멤버쉽
	Nx::Label* mItemName;
	Nx::Label* mItemNameUnder;
	//골드,,등 ( bmpfont 뒤에)
	Nx::Label* mItemNamePost;
	Nx::Label* mItemNamePostUnder;
	//구매완료
	Nx::Label* mBuyComplete;
	Nx::Label* mBuyCompleteUnder;
	// 마이룸에서 멤버쉽
	Nx::Label* mItemDesc;
	Nx::Label* mItemDescUnder;
	//rewardinfo
	Nx::Label* mReward;
	Nx::Label* mRewardUnder;
	//rewarddesc
	Nx::Label* mRewardDesc;
	Nx::Label* mRewardDescUnder;
	Nx::Label* mTouchDesc;
	
};
