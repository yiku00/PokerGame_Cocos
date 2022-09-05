#pragma once

#include "NxFramework.h"
#include "W_VipData.pb.h"

class LobbyMyHomeTap2 : public Panel, public Button::Listener
{
public:
	LobbyMyHomeTap2();
	virtual ~LobbyMyHomeTap2();

	void InitPanel();
	void InitImage();
	void initButton();
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);

    void resume();
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);

	void UpdateRankInfo();
	void SetRankPercentBar(int _now);
	void SetVipBonus(int _vipLevel);
private:
	void SetVipOption(W_VipData_VipOption _data);
public:
	bool mLoginProcess;

	int m_SelectedRank;
	CCScrollView* m_pReplayListView;
	CCLayer* m_pReplayListContainer;

	bool m_bTouchCancel;

	float m_ButtonPosX;
	float m_ButtonMaxPosX;
	CCPoint m_ButtonStartPosition;

	SkelObject* mVipIcon;
	Nx::Label* mVipAmount;
	SkelObject* mRankIcon;

	Nx::Label* mVipDesc;

	Button* mInfoBtn;
	Nx::Label* mInfoBtnLabel;
	Nx::Label* mInfoBtnUnderLabel;

	Nx::Label* mVipPeriodDesc;
	Nx::Label* mVipTitle;
	Nx::Label* mVipTitleUnder;
};
