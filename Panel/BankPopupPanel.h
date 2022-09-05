/********************************************************************
	file name:	PopupPanel.h
	
	purpose:	계정 생성 관련 팝업 판넬들 모음
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_LetterInfo.pb.h"
//#include "TypeDefine.pb.h"

class BankPopupPanel : public Panel, public Button::Listener, public SkelObject::Listener, public TextField::Listener
{
public :
	enum BankInOut
	{
		BANK_IN = 0,
		BANK_OUT = 1,

	};
public:
	BankPopupPanel(int param1 = 0, int param2 = 0);
	~BankPopupPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);
	virtual void onAnimationEnded(const string& ani);
	//TextField::Listener
	virtual void onDetached();
	virtual void update(float delta);
	virtual void onEnter() override;
public:
	virtual void onRefresh();

public:
	void setGeneralListener(CCObject* target, ObjectListener listener) { mTarget = target; mGeneralListener = listener; }
	
private:
	void initPanel();
	void clearThisPanel();
	void ExeEvent();
	void ButtonEnable(Button * button, bool enable);
	void MakeBankPanel();
	void IncreaseMoney(int64 num);
	void SetConsoleMoney();
	int64 GetCanBankMoney();
	void SetBankInOut(BankInOut inout);
	void InoutCheck();
	void SetRemainTime();
private:
	CCObject* mTarget;
	ObjectListener mGeneralListener;
	string	mEventName;

	int mParam1;
	int mParam2;

	Button * mNumButton[10];

	int64 mInputMoney;
	BankInOut mBankInOut;

	Nx::Label* mTitle;
	Nx::Label* mTitleUnder;

	Button* mCloseBtn;
	Button* mExcuteBtn;
	Nx::Label* mExcuteLabel;
	Nx::Label* mExcuteUnderLabel;
	SkelObject* mBankIcon;

	Panel* mInitBtnPanel;
};
