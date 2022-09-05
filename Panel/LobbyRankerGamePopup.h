/********************************************************************
filename: 	LobbyRankerGamePopup.h

purpose:	서바이벌 매치에서 랭커 다시 보기…
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "W_DeathMatchInfo.pb.h"

#define RANKER_CELL_MAX 5

class LobbyRankerGamePopup : public Panel, public Button::Listener
{
public:
	LobbyRankerGamePopup();
	virtual ~LobbyRankerGamePopup();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onEnter() override;
	virtual bool handling(STCMD &stCmd);

	void SetData(string& matchName);
	void ShowPanel(bool _enable);
	void SetType(GameMode _gamemode);
public:
	Panel* m_RankerGameCell[RANKER_CELL_MAX];
	GameMode m_gameMode;

};
