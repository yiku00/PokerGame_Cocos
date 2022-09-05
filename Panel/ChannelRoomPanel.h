#pragma once

#include "NxFramework.h"
#include "ChannelRoomMainPanel.h"


class ChannelRoomPanel : public Panel, public Button::Listener, public TextField::Listener
{
public:
	ChannelRoomPanel();
	virtual ~ChannelRoomPanel();

public:
	void UpdateChannelUiPanel();
private:
	void initPanel();
	
// Button::Listener
	virtual void onClicked(const string& name);	
	virtual void onDetached();

public:
	ChannelRoomMainPanel* mChannelRoomMainPanel;
	int m_searchIdx;
	bool m_isSearching;
};
