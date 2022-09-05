#pragma once

#include "NxFramework.h"

enum TypeSlotButton
{
	TYPE_GET_CHIP,
	TYPE_GET_CHIP_OFF,
	TYPE_SEND_CHIP,
	TYPE_SEND_CHIP_OFF,
	TYPE_GET_GOLD,
	TYPE_GET_GOLD_OFF,
	TYPE_SEND_GOLD,
	TYPE_SEND_GOLD_OFF,
	TYPE_APPLY_FRIEND,
};

class SlotButtonPanel : public Panel, public Button::Listener
{
public:
	SlotButtonPanel();
	virtual ~SlotButtonPanel();

	void InitPanel();
	void InitImage();
	void initButton();

	virtual void onClicked(const string& name);

	void SetBtnType(int _type);
	void SetBtnText(string _text);
	void SetButtonListener(Button::Listener* _ptr);
public:
	Button* m_Button;
	SkelObject* m_GetIcon;

private:
	int m_ButtonType;

	Nx::Label* m_TextShadow;
	Nx::Label* m_Text;
	Nx::Label* m_GetTextShadow;
	Nx::Label* m_GetText;

};
