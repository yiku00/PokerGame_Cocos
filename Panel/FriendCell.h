#pragma once

#include "NxFramework.h"
#include "SlotButtonPanel.h"

class FriendCell : public Panel, public Button::Listener
{
public:
	FriendCell();
	virtual ~FriendCell();

public:
	virtual void onClicked(const string& name);


private:
	void InitPanel();
	void InitImage();
	void initButton();

public:
	void setFriendInfo(int idx);	
	void InitFriendPhoto(int _index, bool isTryDownload);
	void UpdateFriendPhoto(int _cellIndex);
	void cellTouch(const CCPoint& touchPoint);

private:
	void _cellTouchEnd(CCNode* node);

private:
	int mIndex;
	Panel* mMainPanel;
	CCSize mContentSize;
	SlotButtonPanel* m_SendBtnPanel;
	SlotButtonPanel* m_GetBtnPanel;
	SlotButtonPanel* mRemoveBtnPanel;

	Button* m_userTouch;
	Button* m_sendGiftBtn;
	Button* m_getGiftBtn;
	Button* mRemoveBtn;

	Widget* mUserPhoto;
	
	Nx::Label* m_userName;
	Nx::Label* m_lastJoin;

};
