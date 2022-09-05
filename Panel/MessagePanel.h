/********************************************************************
	file name:	MessagePanel.h
	
	purpose:	메세지 창
*********************************************************************/
#pragma once
#include "NxFramework.h"

#define MessageButtonOk "btn_bluebtn1"
#define MessageButtonCancel "btn_redbtn1"

class MessagePanel : public Panel, public Nx::Layer::Listener
{
	typedef vector<Button*> ButtonContainer;

public:
	enum MessageType {
		OK,
		OKCANCEL,
		YESNO,
		NOCASH,
		NOGAMEMONEY,
	};

public:
	static const string BTN_OK;
	static const string BTN_YES;
	static const string BTN_NO;

public:
	MessagePanel(const string& title , const string& text , const string& notice , MessageType type = OK);
	virtual ~MessagePanel();

public:	/*Layer::Listener*/
	virtual	void onLayerMessage(const string& msg);
	virtual void update(float dt);
	virtual void onEnter() override;
public:
	void setGeneralListener(CCObject* target, ObjectListener listener) { mTarget = target; mGeneralListener = listener; }

private:
	CCObject* mTarget;
	ObjectListener mGeneralListener;
	MessageType mType;

	Nx::Label* mTitle;
	Nx::Label* mDesc;
	Button* mMiddleOkBtn;
	Nx::Label* mMiddleOkBtnText;
	Button* mLeftOkBtn;
	Nx::Label* mLeftOkBtnText;
	Button* mCancelBtn;
	Nx::Label* mCancelBtnText;
};

class TopMessagePanel : public MessagePanel
{
public:
	TopMessagePanel(const string& title, const string& text, MessageType type)
		: MessagePanel(title, text, "", type) {}
	virtual ~TopMessagePanel() {}
};

class ServerMessagePanel : public MessagePanel
{
public:
	ServerMessagePanel(const string& title, const string& text, const string& notice , MessageType type)
		: MessagePanel(title, text, notice, type) {}
	virtual ~ServerMessagePanel() {}
};