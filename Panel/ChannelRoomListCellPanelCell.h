#pragma once

#include "NxFramework.h"
#include "ChannelRoomCell.h"

class ChannelRoomListCellPanelCell : public Panel
{
	typedef vector<ChannelRoomCell*> RoomCellContainer;
public:
	ChannelRoomListCellPanelCell();
	virtual ~ChannelRoomListCellPanelCell();

public:
	void setCellIndex(int index);
private:
	void InitPanel();
	

private:
	RoomCellContainer mContainer;
	Panel* mMainPanel;
};