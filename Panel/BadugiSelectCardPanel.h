/********************************************************************
file name:	BadugiSelectCardPanel.h

purpose:	바둑이 게임 하단에 패스 패스 창 나열된 창
*********************************************************************/
#pragma once
#include "NxFramework.h"

class BadugiSelectCardPanel : public Panel, public Button::Listener
{
public:
	BadugiSelectCardPanel();
	virtual ~BadugiSelectCardPanel();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	bool TouchStart(CCTouch *pTouch);
	void TouchMove(CCTouch *pTouch);
	void TouchEnd(CCTouch *pTouch);

	void SendChangeCardReq();
	void ShowBadugiSelectCardPanel(bool _visible);
	void SetNumberButtonState();
	void SendChangePassReq();
	void SetSeletBtn(int _idx, bool _on);
	void ApplyChangeButtonState();
	void SetChangeButtonState();
	void SetEnableButton(bool _enable);
public:
	bool mLoginProcess;
	bool m_GamePlaying;

	Button* m_ChangeBtn;
	Button* m_PassBtn;
	Button* m_SelectBtn1;
	Button* m_SelectBtn2;
	Button* m_SelectBtn3;
	Button* m_SelectBtn4;

	bool m_TouchButton[6];
private:
	CCPoint m_showPosition;
	CCPoint m_hidePosition;
};
