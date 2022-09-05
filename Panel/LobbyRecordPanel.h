/********************************************************************
file name:	LobbyRecordPanel.h

purpose:	기록실 메인창 왼쪽에 리스트
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "TabButtonPanel.h"
#include "LobbyRecordRankPanel.h"
#include "LobbyRecordWorldTourPanel.h"
#include "LobbyRecordTourmentPanel.h"
#include "LobbyRecordSurvivalPanel.h"
#include "W_ReputeRankRes.pb.h"

class LobbyRecordPanel : public Panel, public Button::Listener
{
	typedef vector<TabButtonPanel*> TabButtonContainer;

public:
	LobbyRecordPanel();
	virtual ~LobbyRecordPanel();

public:
	virtual void onClicked(const string& buttonName);
	virtual bool handling(STCMD &stCmd);

public:
	void showPanel();
	void HidePanel();
	void recvTotalReputeRankRes(W_ReputeRankRes res);
	void recvFriendReputeRankRes(W_ReputeRankRes res);
private:
	void _init();
	void initTab();
	void initPanel();
	
	void addRankPanel();
	void addWorldTourPanel();
	void addTournamentPanel();
	void addSurvivalPanel();

	void refresh();
	void refreshListBtn();	//왼쪽 리스트에 월드투어 , 챔피언쉽 리스트
	void refreshPanel();	//탭 선택했을때 선택창

private:
	TabButtonContainer mTabButtons; 
	//Button* mListBtn1;	//랭킹
	//Button* mListBtn2;	//월드 투어
	//Button* mListBtn3;	//챔피언쉽
	//Button* mListBtn4;	//서바이벌
	
	int mTapIndex;
	CCSize mCellSize;

	LobbyRecordRankPanel* mRecordRankPanel;
	LobbyRecordWorldTourPanel* mRecordWorldTourPanel; 
	LobbyRecordTourmentPanel* mRecordTurmentPanel; 
	LobbyRecordSurvivalPanel* mRecordSurvivalPanel;		
};