/********************************************************************
	file name:	PopupPanel.h
	
	purpose:	공통 팝업창 Push 레이어가 아닌 부치는 panel
*********************************************************************/
#pragma once
#include "NxFramework.h"
//#include "TypeDefine.pb.h"

#define PopupOk "PopupOk"
#define PopupCancel "PopupCancel"

class PopupPanel : public Panel, public Button::Listener
{
public:
	
	enum PopupType{
		WholeNotice,	//전체 공지 처럼 한 화면에 내용만 있는  것
		NormalNotice,			//제목 , 타이틀 , 버튼
		PriceNotice,	//제목 타이틀 버튼에 재화 표시
		ItemNotice,		//제목 , 타이틀 , 버튼 , 재화 , 아이템 이름.
	};
	
	
	enum PopupBtnType {
		Confirm,
		CancelOk,
	};

public:
	PopupPanel(PopupBtnType type , const string&text);		//전체 냉용만 있는 것
	~PopupPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);

public:
	virtual void onRefresh();

public:
	void setGeneralListener(CCObject* target, ObjectListener listener) { mTarget = target; mGeneralListener = listener; }
public:
	void addTitle(const string& title);
	void setResourceTitle(const wstring& gameStringStr);
	void addNotice(const string& notice);

private:
	void initPanel();
	void initDesc(const string& text);	//각 string data 및 visible init
	void setBtnType();
	void setTextType();
	void setUseNotice(bool flag);
	void clearThisPanel();

private:

	CCObject* mTarget;
	ObjectListener mGeneralListener;

	std::string mContentsStr;
	PopupType mType;
	PopupBtnType mBtnType;
	Nx::Label* mTitle;
	
	Nx::Label* mWholeDesc;	//전체 공지용
	Nx::Label* mDesc;	//중간 내용
	Nx::Label* mItemName;

	Nx::Label* mResourceTitle;
	CCPoint mRewardPosition;
	Button* mMiddleOkBtn;
	Nx::Label* mMiddleOkBtnText;
	Button* mOkBtn;
	Nx::Label* mOkBtnText;
	Button* mCancelBtn;
	Nx::Label* mCancelBtnText;
	Nx::Label* mNoticeText;
};
