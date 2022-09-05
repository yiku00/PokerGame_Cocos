#pragma once

#include "NxFramework.h"

class ChannelRoomCell : public Panel, public Button::Listener
{
public:
	ChannelRoomCell();
	virtual ~ChannelRoomCell();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	void setRoomNumber(string _str);
	void UpdateRoomInfo(int _index);
	void setRoomUser(int _idx, bool _visible, string _username = "" , int characterIdx = -1);
	void SetDisable();
	void setActivate(bool activate);
	virtual void onEnter() override;
public:
	bool mLoginProcess;
	bool m_isSecret;
	int m_idx;
	string m_password;
	Button* mEnterBtn;
	Nx::Label* mEnterBtnLabel;
	Nx::Label* mEnterBtnUnderLabel;
	Panel* mMainPanel;
};