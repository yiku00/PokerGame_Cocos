#pragma once

#include "NxFramework.h"
#include "SmallBtnPanel.h"

class PokerUserInfoPanel : public Panel, public Button::Listener
{
public:
	PokerUserInfoPanel(int _panelType);
	virtual ~PokerUserInfoPanel();

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
	void SetPanelString();
	void SetTimerShow();
	void HidePanel();
	void InitUserPhoto(bool isTryDownload);
	void UpdateUserPhoto();
	void setEmotionActivate(bool visible);	// Emotion 관련 부분 vislble
	void setActivatePanel(bool visible);
	void initButtonState();	//감정 차단 , 강제퇴장 버튼 초기화

private:
	void refreshEmotionBtnState();		//현재 버틑 차단 상태에 따라서 처리한다.
	void refreshPlayerOutBtnState();	//쫒아내기 버튼 상태	
	void refreshFriendState();	//친구 소개 버튼 설정
	void setNovisibleTimeOver();	//3초가 되면 꺼진다.

public:
	bool m_bCancelTouch;
	bool m_bShowPanel;
	int m_PanelType;
	Button* m_PlayerOutButton;
	Button* mEmotionBtn;
	Nx::Label* mEmotionBtnLabel;
	SmallBtnPanel* mSmallFrirendBtnPanel;

	Nx::Label* m_userName;
	Nx::Label* m_userLevel;
	Nx::Label* m_winningRateLabel;
	Nx::Label* m_winningRateText;
	Nx::Label* m_pofitLabel;
	Nx::Label* m_pofitText;
	Nx::Label* m_madeLabel;
	Nx::Label* m_madeText;
	Nx::Label* m_allinLabel;
	Nx::Label* m_allinText;
	bool m_bBlockEmotion;	//기존에 emotionPanel 에 있던 값
	bool mPlayerOutFlag;
	SkelObject* mRankIcon;	
	Widget* m_pPhoto;

	Nx::Label* mPlayOutLabel;
};
