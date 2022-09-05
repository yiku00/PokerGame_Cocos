#pragma once

#include "NxFramework.h"

enum 
{
	TOUCH_EVENT_TYPE_BEGIN,
	TOUCH_EVENT_TYPE_MOVE,
	TOUCH_EVENT_TYPE_CANCEL,
	TOUCH_EVENT_TYPE_END,
};

class LobbyMyHomeTap1 : public Panel, public Button::Listener
{
public:
	LobbyMyHomeTap1();
	virtual ~LobbyMyHomeTap1();

	void InitPanel();
	void InitImage();
	void initButton();
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onEnter() override;
    void resume();
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);

	void SetMainUiPanelPtr(Panel* _pPanel) { m_pMainUiPanel = _pPanel; }

	void SetLevelExp();
	void SetMyMoney();
	void SetMyCharacter();
	void SetUserInfo();
	
	void ShowNextLevelInfo(bool _show);
	void showLimitedInfo(bool _show);
	void ShowCharacterSelectPanel();
	Button* GetColisionButton(CCTouch *pTouch, int _eventType);
	void InitMyPhoto(bool isTryDownload);

public:
	bool mLoginProcess;
	
	int m_ViewDataIndex;
	CCScrollView* m_pReplayListView;
	CCLayer* m_pReplayListContainer;

	Panel* m_pNextLevelInfoPanel;
	Panel* mLimitedInfoPanel;
	
	bool m_bTouchCancel;

	float m_ButtonPosX;
	float m_ButtonMaxPosX;
	CCPoint m_ButtonStartPosition;
	
	Panel* m_pButtonPanel[3];
	
	Button* m_EditNickNameBtn;
	Button* m_CharaterInfoBtn;
	Button* m_NextLevelInfoBtn;
	Button* m_GotoRubyShopBtn;

	Nx::Label* mUserInfoTitle;		//유저정보
	Nx::Label* mUserInfoTitleUnder;	//유저정보
	Nx::Label* mNickNameTitle;		//닉네임:
	Nx::Label* mMyGoodsTitle;		//소지재화 
	Nx::Label* mMyGoodsTitleUnder;	//소지재화 
	Nx::Label* mMyGoodsGoldTitle;	//소지골드
	Nx::Label* mMyGoodsBankTitle;	//금고골드
	Nx::Label* mInsuranceTitle;		//보험금
	Nx::Label* mRefilTitle;			//리필정보
	Nx::Label* mMebershipTitle;		//맴버쉽 리필

	Nx::Label* m_pUserInfo;
	Nx::Label* m_pGoldInfo;
	Nx::Label* m_pNickName;
	Nx::Label* m_pAcount;
	Nx::Label* m_pLevel;
	Nx::Label* m_pLevelupLeft;
	Nx::Label* m_pLevelExp;
	Nx::Label* m_pMyGold;
	Nx::Label* m_pMaxMyGold;
	Nx::Label* m_pMyChip;
	Nx::Label* m_pMaxMyChip;
	Nx::Label* m_pMyGameMoneyLabel;
	Nx::Label* m_pMyGameMoney;
	Nx::Label* m_pMyBankMoneyLabel;
	Nx::Label* m_pMyBankMoney;
	Nx::Label* m_pInsuranceLabel;
	Nx::Label* m_pInsurance;
	Nx::Label* m_pLoseMoneyLabel;
	Nx::Label* m_pLoseMoney;
	Nx::Label* m_pMaxLoseMoney;
	Nx::Label* m_pRefillCount;
	Nx::Label* m_pRefillCountLabel;
	Nx::Label* m_pRubyPlus;
	Nx::Label* m_pTotalRuby;

	Panel* m_pMainUiPanel;	
	Widget* mRubyPlusIcon;
	Widget* m_pMyPhoto;

	Nx::Label* mMemberShipRefillLabel;
};
