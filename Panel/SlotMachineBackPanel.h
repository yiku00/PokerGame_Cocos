/********************************************************************
file name:	SlotMachineBackPanel.h

purpose:	슬롯 머진 back 창 ( 기본 배경 과 칩 , 루비 머신 보여준다.
*********************************************************************/
#pragma once
#include "NxFramework.h"
//#define SLOT_WHEEL
#ifdef SLOT_WHEEL
#include "SlotMachinePanel.h"
#else
#include "SlotMachineWheelPanel.h"
#endif
class SlotMachineBackPanel : public Panel, public Button::Listener, public Nx::Layer::Listener
{	
#ifdef SLOT_WHEEL
	enum SLOT_TYPE {
		SLOT_NONE = 0,
		SLOT_CHIP_TYPE,
		SLOT_RUBY_TYPE,
	};
#endif

public:	
	SlotMachineBackPanel();
	virtual ~SlotMachineBackPanel();
	
public:
	virtual void onClicked(const string& buttonName);
	virtual void onLayerMessage(const string& msg);

public:
#ifdef SLOT_WHEEL
	void setActivate(SLOT_TYPE type, bool ani = false);
#else
	void setActivate(bool ani = false);
#endif
	void SetSlotMachine();
private:
	void initPanel();
	void aniEnd();

private:
#ifdef SLOT_WHEEL
	SlotMachinePanel* mChipPanel;
	SlotMachinePanel* mRubyPanel;
	SLOT_TYPE mType;
#else
	SlotMachineWheelPanel* mWheelPanel;

#endif
	Button* mCloseBtn;
	bool mMoveAni;	
};