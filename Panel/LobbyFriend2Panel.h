#pragma once

#include "NxFramework.h"
#include "W_FriendInfo.pb.h"
#include "TockInvtationPanel.h"
#include "SmallButtonPanel.h"
#include "FriendCellMiddle.h"
#include "IntableSearchPanel.h"
#include "LobbyFriendAcceptPanel.h"
#include "LobbyFriendRequestPanel.h"

#define FRIEND_MAX_COUNT 50
#define RECOMMEND_TAG 1000

#define FRIEND_CELL_MAX 20

class LobbyFriend2Panel : public Panel, public Button::Listener
{
public:
	LobbyFriend2Panel();
	virtual ~LobbyFriend2Panel();

public:
	virtual void onClicked(const string& name);
private:
	void InitPanel();
    //void resume();
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);

	void SetRequestFriendList();
	void SetRecommendFriendList();
	void ClearRequestList();
	void ClearRecommendlList();


	void SetButtonPause(bool _pause);
	void refreshTableView();

	void setActivate(bool activate);

private:
	void ShowFriendInfoPanel(int _index);

public:
	int m_TapIndex;
	LobbyFriendAcceptPanel* mFriendAcceptPanel;
	LobbyFriendRequestPanel* mFriendRequestPanel;
};