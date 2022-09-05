/********************************************************************
	file name:	PopupPanel.h
	
	purpose:	계정 생성 관련 팝업 판넬들 모음
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_LetterInfo.pb.h"
//#include "TypeDefine.pb.h"

class AccountPopupPanel : public Panel, public Button::Listener, public SkelObject::Listener, public TextField::Listener
{
public:
	enum AccountPopupType{
		AGREE_TYPE,		//		
		NICKNAME_TYPE,
		NICKNAME_REPAIR_TYPE,
	};

public:
	AccountPopupPanel(AccountPopupType type, int param1 = 0, int param2 = 0);
	~AccountPopupPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);
	virtual void onAnimationEnded(const string& ani);
	//TextField::Listener
	virtual void onDetached();

public:
	virtual void onRefresh();

public:
	void setGeneralListener(CCObject* target, ObjectListener listener) { mTarget = target; mGeneralListener = listener; }
	void ShowPanel(bool isVisible);
private:
	void initPanel();
	void clearThisPanel();
	void ExeEvent();
	void MakeAccountPanel();
	//void ButtonEnable(Button * button, bool enable);
	void AgreeCheck(int idx, bool check);
	
	void MakeCharacterCell(int idx);
	void SelectCharacter(int idx);
	void MakeNicknamePanel();
	void EnableArgeeButton(bool _enable);
private:	
	Panel* m_pBtnPanel[4];
	Button* m_pCancel;
	Button* m_pAgree;
	Button* m_pShowTerm1;
	Button* m_pShowTerm2;
	AccountPopupType mType;

	CCObject* mTarget;
	ObjectListener mGeneralListener;
	string	mEventName;

	int mParam1;
	int mParam2;

	Panel* m_OkButtonPanel;

	Nx::Label* mTitle;
	Nx::Label* mTitleUnder;

	bool mIsAgree0, mIsAgree1;		// 약관 동의 1, 2
};
