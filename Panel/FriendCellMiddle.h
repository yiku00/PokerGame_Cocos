#pragma once

#include "NxFramework.h"
#include "SlotButtonPanel.h"

class FriendCellMiddle : public Panel, public Button::Listener
{
public:
	enum FRIEND_CELL_TYPE {
		FRIEND_REQUEST_TYPE,
		FRIEND_RECOMMEND_TYPE,
		FACEBOOK_REQUEST_TYPE,
	};

public:
	FriendCellMiddle(FRIEND_CELL_TYPE type);
	virtual ~FriendCellMiddle();

public:
	void setFriendInfo(int idx);
	virtual void onClicked(const string& name);
	void InitFriendPhoto(int _index, bool isTryDownload);
	void cellTouch(const CCPoint& touchPoint);

private:
	void InitPanel();
	void InitImage();
	void initButton();	
	void UpdateFriendPhoto(int _cellIndex);	

private:
	void _cellTouchEnd(CCNode* node);

public:
	Panel* mMainPanel;
	CCSize mContentSize;

	SlotButtonPanel* m_SendBtnPanel;
	SlotButtonPanel* m_GetBtnPanel;

	Button* m_sendGiftBtn;
	Button* m_getGiftBtn;

	Widget* mUserPhoto;
	
	Nx::Label* m_userName;
	Nx::Label* m_lastJoin;

	FRIEND_CELL_TYPE mCellType;
	int mCellIndex;

};
