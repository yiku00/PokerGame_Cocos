#pragma once

#include "NxFramework.h"
#include "W_RewardInfo.pb.h"

class LobbyTopUiPanel : public Panel, public Button::Listener, public Nx::Layer::Listener
{
public:
	LobbyTopUiPanel();
	virtual ~LobbyTopUiPanel();

	void InitPanel();
	void InitImage();
	void initButton();
	
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onLayerMessage(const string& msg);
	virtual void onEnter() override;

    void resume();
public:
	virtual bool handling(STCMD &stCmd);
	virtual void update(float dt);
	void UpdatePlayerInfo();
	void SetTopTitle(int _kind);
	void SetVisiebleUserInfo(bool _visible);

	void updateVip();

	void pushUiPanel(int status);	//기덕 수정.. dynamicpush 로 수정
	bool isCloseBtn();				//closeBtn 상태인가.
	void addRewardInfo(W_RewardInfo rewardInfo);
	void addRewardRuby(int64 ruby);

	void refreshUserPhoto();
	void refreshBank();
	void InitMyPhoto(bool isDownload = true);

    void initNotiWidget();
    void updateNotiWidget();
    
private:
	void _updateIntAction();
	void _completeIntAction();	
private:
	void setvisibleRank(bool vislble);
	bool isBankOpen();

public:
	bool mLoginProcess;
	CCPoint m_ExpStartPos;

	
	bool	m_isUseProfilePhoto;
	int		m_menuTitleFirstX;
	int		m_menuTitleFirstW;

	SkelObject* mVipIcon;
	Nx::Label* mVipAmount;
	Nx::Label* mLvTitle;
	SkelObject* mMemberIcon;
	Widget* mAddRubyIcon;
	
	Button* mCloseBtn;
	Button* mMyRoomBtn;
	Button* mBankBtn;
	Widget* mBankEffect;
	Button* mRubyBtn;

	int64 mRewardGameMoneyInit;
	int64 mRewardAddGameMoney;
	int64 mRewardResultGameMoney;
	Widget* mUserPhoto;
	Widget* mMyHomeAni;

    typedef vector<class NotiWidget*> NotiWidgetContainer;
    NotiWidgetContainer mNotiWidgets;
};
