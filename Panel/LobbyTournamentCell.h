#pragma once

#include "NxFramework.h"
#include "W_ChannelInfo.pb.h"

class LobbyTournamentCell : public Panel, public Button::Listener
{
public:
	LobbyTournamentCell();
	virtual ~LobbyTournamentCell();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	void SetCellData(int _index);

	void SelectTournamentCell(int _dst);
	void SendTournamentReady(int _index, int _stepIndex);
public:
	W_ChannelInfo* m_CellInfo;

	bool m_GamePlaying;

	Button* m_btnChannel;

	Nx::Label* m_labelTitle;
	Nx::Label* m_labelTicket;
	Nx::Label* m_labelTicketSum;
	Nx::Label* m_labelGift1;
	Nx::Label* m_labelGift2;
	Nx::Label* m_labelGift;

};
