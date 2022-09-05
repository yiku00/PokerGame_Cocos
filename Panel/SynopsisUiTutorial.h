#pragma once

#include "NxFramework.h"
#include "LobbyTopUiPanel.h"
#include "LobbyLeftUiPanel.h"

class SynopsisUiTutorial : public Panel, public Button::Listener
{
public:
	SynopsisUiTutorial();
	virtual ~SynopsisUiTutorial();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual void onClicked(const string& name);
	//virtual void keyBackClicked();
	virtual bool handling(STCMD &stCmd);
	virtual void onEnter() override;

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);

	void ShowPage(int _page);

	void EndTutorial();

	void SetMainUiPanel();
	void applyUserData();
	void UpdateUserVip();
	void UpdateUserMoney();
	void UpdateUserLevel();
	void UpdateUserNickName();
	void UpdateUserChip();
	void UpdateUserCash();
	void ReadyAppear();
	void AppearUi();

	void InitTopUiPanel();
	void InitLeftUiPanel();
public:
	bool m_Process;
	float m_BlockTime;

	Button* m_BlockButton;

	vector<SkelObject*> m_page1;
	vector<SkelObject*> m_page2;
	vector<SkelObject*> m_page3;
	vector<SkelObject*> m_page4;

	vector<Nx::Label*> m_page1Label;
	vector<Nx::Label*> m_page2Label;
	vector<Nx::Label*> m_page3Label;
	vector<Nx::Label*> m_page4Label;

	int m_PageIndex;

	Panel* m_UiPanel;
	LobbyTopUiPanel* m_pTopPanel;
	LobbyLeftUiPanel* m_pLeftUiPanel;

	Nx::Label* m_pLeftLabel[5];
	Nx::Label* m_pLeftLabelBack[5];

	CCPoint m_LeftLabelShowPos[5];
	CCPoint m_LeftLabelHidePos[5];
	CCPoint m_LeftLabelBackShowPos[5];
	CCPoint m_LeftLabelBackHidePos[5];

	Button* m_pMyHomeButton;
	Button* m_pLetterButton;
	Button* m_pFriendButton;
	Button* m_pMissionButton;
	Button* m_pShopButton;
	Button* m_p7PokerButton;
	Button* m_pHighLowButton;
	Button* m_pBadugiButton;
	//Button* m_pHoldemButton;
	Button* m_pMiniGameButton;
	Button* m_pDailyCheckButton;
	Button* m_pRankingButton;
	Button* m_pReplayButton;

	CCPoint m_MyHomeposHide;
	CCPoint m_MyHomeposSHow;
	CCPoint m_LetterposHide;
	CCPoint m_LetterposSHow;
	CCPoint m_FriendposHide;
	CCPoint m_FriendposSHow;
	CCPoint m_MissionposHide;
	CCPoint m_MissionposSHow;
	CCPoint m_ShopposHide;
	CCPoint m_ShopposSHow;
	CCPoint m_pos7PokerHide;
	CCPoint m_pos7PokerSHow;
	CCPoint m_posHighLowHide;
	CCPoint m_posHighLowShow;
	CCPoint m_posBadugiHide;
	CCPoint m_posBadugiShow;
	CCPoint m_posHoldemHide;
	CCPoint m_posHoldemShow;
	CCPoint m_posMiniGameHide;
	CCPoint m_posMiniGameShow;
	CCPoint m_posDailyCheckHide;
	CCPoint m_posDailyCheckShow;
	CCPoint m_posRankingHide;
	CCPoint m_posRankingShow;
	CCPoint m_posReplayHide;
	CCPoint m_posReplayShow;


};
