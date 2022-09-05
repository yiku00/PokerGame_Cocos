#pragma once

#include "NxFramework.h"
#include "ChannelRoomCell.h"

class ChannelRoomPage : public Panel, public Button::Listener
{
public:
	ChannelRoomPage();
	virtual ~ChannelRoomPage();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	void UpdatePageData(int _page);

	void setActivate(bool activate);
	virtual void onEnter() override;
public:
	ChannelRoomCell* m_pCell[4];
};