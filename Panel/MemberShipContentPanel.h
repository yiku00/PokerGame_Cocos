/********************************************************************
file name:	MemberShipContentPanel.h

purpose:	맴버쉽 내용창
*********************************************************************/
#pragma once
#include "NxFramework.h"

class MemberShipContentPanel : public Panel, public Button::Listener
{
public:
	enum MEMBERSHIP_TYPE
	{
		MEMBER_SILVER,
		MEMBER_GOLD,
	};

public:
	MemberShipContentPanel(MEMBERSHIP_TYPE type);
	virtual ~MemberShipContentPanel();

public:
	virtual void onClicked(const string& name);
private:
	void InitPanel();
	void InitImage();
	void initButton();

	void refresh();
	void refreshBtnState();	//
	void refreshApply();

private:
	MEMBERSHIP_TYPE mMemberType;
	Button* mDetailBtn;

	Nx::Label* mLeftLabel;
	Nx::Label* mMiddleLabel;
	Nx::Label* mRightLabel;

	Widget* mApplyIcon;
	Nx::Label* mDiscountLabel;
	Nx::Label* mSpecLabel;

	Panel* m_ButtonPanel;

	Nx::Label* mApplyLabel;
	Nx::Label* mApplyUnderLabel;

	//구매하기 버튼
	Button* mSelectBtn;
	//구매가기 버튼 글자
	Nx::Label* mSelectBtnLabel;
	Nx::Label* mDetailStr;

};
