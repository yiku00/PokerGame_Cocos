#pragma once

#include "NxFramework.h"
#include "W_MonthlyClassData.pb.h"

class LobbyMyHomeTap3 : public Panel, public Button::Listener
{
public:
	LobbyMyHomeTap3();
	virtual ~LobbyMyHomeTap3();

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
	//void SetVipInfo(int _vipLevel);
	//void SetVipXpBar(int _per);
	//void SetVipDesc(int _level);
	void SetClassInfo();
	void SetClassDesc(int _classId);
	void SetBonusTable(W_MonthlyClassData_eClassType _type, int64 _amount, int64 _effect);
	
public:
	bool mLoginProcess;

	//int m_VipDescId;
	int m_ClassDescId;

	int m_ViewDataIndex;
	CCScrollView* m_pReplayListView;
	CCLayer* m_pReplayListContainer;

	bool m_bTouchCancel;

	float m_ButtonPosX;
	float m_ButtonMaxPosX;
	CCPoint m_ButtonStartPosition;

	Panel* m_classShopBtnPanel;

	//Button* m_GotoRubyShopBtn;
	//Button* m_VipLeftBtn;
	//Button* m_VipRightBtn;

	Button* m_GotoClassShopBtn;
	Button* m_ClassLeftBtn;
	Button* m_ClassRightBtn;

	//Label* m_pVipXp;
	//Label* m_pNextVipXp;
	//Label* m_pVipNumberLabel;
	//Label* m_pVipDesc;
	//Label* m_pVipTitleLabelShadow;
	//Label* m_pVipTitleLabel;
	SkelObject* mGoldIcon;
	SkelObject* mSilverIcon;
	Nx::Label* mClassLimitGold;
	Nx::Label* mClassLimitSiver;


	Nx::Label* m_pClassGrade;
	Nx::Label* m_pClassGradeUnder;
	Nx::Label* m_pClassDesc;
	//Label* m_pClassTitleLabelShadow;
	Nx::Label* m_pClassTitleLabel;
	Nx::Label* m_pClassTitleUnderLabel;

	Nx::Label* mInstancePayTitle;
	Nx::Label* mInstancePayUnderTitle;


	Nx::Label* mPrizeTitle_1;
	Nx::Label* mPrizeTitle_2;
	Nx::Label* mPrizeTitle_3;
	Nx::Label* mPrizeTitle_4;
	Nx::Label* mPrizeTitle_5;


};
