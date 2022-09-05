/********************************************************************
file name:	LobbyUIPanel.h

purpose:	로비 기본 버튼 UI ( 상점 , 우편함 , 등등 버튼 UI + 카지노입장 시즌 토너먼트 버튼
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "LobbyScene.h"
#include "CustomPopupPanel.h"
#include "SimplePopupPanel.h"
#include "LobbyTopUiPanel.h"
#include "LobbyLeftUiPanel.h"
#include "NotiData.pb.h"
#include "NotiWidget.h"

enum LobbyUiStatus
{
	LOBBY_UI_NO,
	LOBBY_UI_MAIN,
	LOBBY_UI_MYHOME,
	LOBBY_UI_LETTER,
	LOBBY_UI_FRIEND,
	LOBBY_UI_MISSION,
	LOBBY_UI_SHOP,
	LOBBY_UI_DAYCHECK,
	LOBBY_UI_RANKING,
	LOBBY_UI_RANKING_PROCESS,
	LOBBY_UI_REPLAY,
	LOBBY_UI_REPLAY_PROCESS,
	//LOBBY_UI_7POKER,
	//LOBBY_UI_HIGHLOW,
	LOBBY_UI_CHANNELLIST,
	LOBBY_UI_CHANNELROOM,
	//LOBBY_UI_BADUKI,
	//LOBBY_UI_HOLDEM,
	LOBBY_SLOTMACHINE,
	LOBBY_UI_BANK,
	LOBBY_UI_OPTION,
	LOBBY_UI_TOURNAMENT,
	LOBBY_UI_TOURNAMENT_SELECT,
	LOBBY_UI_SURVIVAL,
	LOBBY_UI_SURVIVAL_SELECT,
	LOBBY_UI_RANKER_GAME_POPUP,
	LOBBY_UI_POPUP,
	LOBBY_UI_SIMPLE_POPUP,
	LOBBY_UI_ACCOUNT_POPUP,
	LOBBY_UI_SELECT_CHARACTER_POPUP,
	//LOBBY_UI_CHARACTER_SHOP,
	LOBBY_UI_CHARACTER_INFO,
	LOBBY_UI_GOLD_REFILL_POPUP,
	LOBBY_UI_TUTORIAL,
	LOBBY_UI_INVEN,
	LOBBY_UI_RECORD,
};

class LobbyUIPanel : public Panel, public Button::Listener, public Nx::Layer::Listener
{
	enum SHOP_COMMERCIAL_TYPE {
		SHOP_COMMERCIAL_TYPE_NO,
		SHOP_COMMERCIAL_TYPE_MEMBERSHIP,					//맴버쉽 30일간 혜택
		SHOP_COMMERCIAL_TYPE_MEMBERSHIP_MONTHLY_DISCOUNT,	//멥버쉽 연장 할인
		SHOP_COMMERCIAL_TYPE_MEMBERSHIP_RUBY_PLUS,			//루비 플러스
		SHOP_COMMERCIAL_TYPE_MEMBERSHIP_ETC,				//나머지
	};

	typedef vector<NotiWidget*> NotiWidgetContainer;

public:
	LobbyUIPanel();
	virtual ~LobbyUIPanel();

	void InitPanel();
	void InitButton();
	void InitImage();
	void InitTopUiPanel();

// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onLayerMessage(const string& msg);

    void resume();
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);

	LobbyScene* GetLobbyScene();

	void applyUserData();
	void UpdateUserMoney();
	void UpdateUserLevel();
	void UpdateUserNickName();
	void UpdateUserVip();
	void UpdateUserChip();
	void UpdateUserCash();
	void UpdateUserCharacter();
	void UpdateNotiData();

	void makeUserCharacter();

	void ReadyAppear();
	void AppearUi();

	void PlayGoldLight();
	void PlayChipLight();
	void PlayRubyLight();
	void PlayHomeButtonLight();
	void PlayLetterButtonLight();
	void PlayFriendButtonLight();
	void PlayMissionButtonLight();
	void PlayShopButtonLight();

	//void ShowGameButton();
	//void HideGameButton();
	//void ShowMenuButton();
	//void HideMenuButton();

	void SetChannel();
	void SetShopUi(int tapIdx = -1);
	void SetLetterBoxUi();
	void SetFriendUi();
	
	void SetReplayUi();
	void ShowOptionUi();
	
	void HideChannelUi();
	void HideShopUi();
	void HideLetterBoxUi();
	void HideFriendUi();
	void HideMissionUi();
	void HideReplayUi();
	void HideOptionUi();
	void HideInventoryUi();
	void HideRecordUi();	//

	void SetLobbyUi();
	void SetRanking();

	void ReloadFriendUi();

	void ShowFriendLeftBack();
	void ShowMissoionLeftBack();
	void ShowShopLeftback();
	void ShowLetterLeftback();
	void FromOtherUiToShop(int _tapIdx);

	//void HideLeftBack();
	
	void HideRanking();
	void ShowRankingRighttback();

	void ShowReplayLeftBack();

	void HideRighttback();
	//void setPage(int _index);
	//void VisiblePageLight(bool _show);
	void ShowBankPanel();

	void ShowMyRoomUi();
	void HideMyRoomUi();
	void ShowMyHomeLeftback();
	void ShowOptionLeftback();

	void ShowTournamentUi();
	void UpdateTournamentUi();
	void HideTournamentUi();

	void ShowSurvivalUi();
	void UpdateSurvivalUi();
	void HideSurvivalUi();
	void UpdateSurvivalWidget();

	void HideLobbyMenu();
	void SetRankingTimeLimitUpdate(string _time);
	void HideLobbyUi();
	//void InitBankStatePopup();
	//void ShowBankStatePopup(string _msg);
	//void GoToOtherUiFromShopUi();

	//void CloseRewardPopup();

	void ShowCharacterShop();
	void HideCharacterShop();

	void ShowCharacterInfo(int _characterId);
	void HideCharacterInfo();

	void applyData();
	void MyCharacterIdleAction();
	void MyCharacterAction();

	void UpdateChannelList();

	void ShowGoldRefillPopup();
	void HideGoldRefillPopup();

	void refreshNotiEffect(NotiData_eNotiType type);

	//기록실 관련
	void showRecordUi();	//기록실 관련 push 


	//광고 관련
	bool isActivateShopCommercial();	//광고 상점 뿌릴 것이 있느냐
	bool isActivateMissionCommercial();	//미션 광고 뿌릴 것이 있느냐.

	void setShowCount(int showCount);
	virtual void onEnter() override;
private:
	bool isOpenLimitedJackpot();
	bool isOpenLimitedMade();
	void updateLimitedState();
	void setShopCommercial();

	void initNotiWidget();
	void updateNotiWidget();

public:
	bool m_bOtherUi;
	bool mUiProcess;

	int m_UiState;
	bool m_bShowExitPanel;
	SimplePopupPanel* m_ExitPanel;
	float m_fMyCharacterTime;
	float m_fButtonLightTime;
	Panel* m_bankStatePanel;
	SkelObject* m_pClassIcon;
	SkelObject* m_pBackCover;
	SkelObject* m_pUserCharacter;
	SkelObject* m_pUserCharaUnder;
	SkelObject* m_pCharaShadow;
	SkelObject* m_RightBack[2];
	Button* m_pOptionBackButtion;
	CustomPopupPanel * m_pBankPanel;
	LobbyTopUiPanel* m_pTopPanel;
	LobbyLeftUiPanel* m_pLeftUiPanel;

	
	Button* mLimitedIcon_1Btn;
	Nx::Label* mLimitedcon_1Label; 
	
	Button* mLimitedIcon_2Btn;
	Nx::Label* mLimitedcon_2Label;

	Button* mBigBonusBtn;

	
	Nx::Label* mGranChanceTimeLabel;

	SkelObject* mRankIcon;
	Nx::Label* mTourmentPointLabel;

	Nx::Label* mSeasonOpenTimeLabel;
	Nx::Label* mSeasonLeftLabel;
	Nx::Label* mTournamentLeftLabel;
	Nx::Label* mTournamentStateLabelUnder;
	Nx::Label* mTournamentStateLabelOver;
	Button* mSlotMachineBtn;

	Button* mRefillBtn;
	Button* mCouponBtn;
	SHOP_COMMERCIAL_TYPE mCommercialType;

	Button* mGoShopEventBtn;
	Button* mGoMissionEventBtn;
	Button* mFirsBuyBtn;

	NotiWidgetContainer mNotiWidgets;
	int mShowCount;	

	Widget* mSeasonLockIcon;
	Widget* mServivalLockIcon;


	Nx::Label* mMenu_1;	//상점 메뉴
	Nx::Label* mMenu_2;	//친구 메뉴
	Nx::Label* mMenu_3;	//미션 메뉴
	Nx::Label* mMenu_4;	//기록실 메뉴
	Nx::Label* mMenu_5;	//보관함 메뉴
	Nx::Label* mMenu_6;	//돌림판(슬롯머신)

	Nx::Label* mGoMenu_1;	//카지노 입장
	Nx::Label* mGoMenu_2;	//시즌토너먼트
	Nx::Label* mGoMenu_3;	//서바이벌매치

};