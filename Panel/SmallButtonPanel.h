#pragma once

#include "NxFramework.h"

class SmallButtonPanel : public Panel, public Button::Listener
{
public:

	enum DMY_BUTTON_TYPE {
		LOBBY_FRIEND_TYPE,		//lobbyFriend1 하단 버트에 쓰이는 타입
		LOBBY_UI_TYPE,			//로비 메인에서 쓰는 버튼 타입 ( 충전소 , 쿠폰 )
		LOBBY_UI_SHOP_TYPE,		//상점 dummy 사용	//돈 표시
		LOBBY_UI_SHOP_RUBY,
		LOBBY_UI_SHOP_DISCOUNT,	//상품 discount
		LOBBY_UI_IMPOSSIBLE,	//사용불가
		LOBBY_UI_BIG_SHOP_RUBY,
		LOBBY_UI_BIG_DISCOUNT,
		LOBBY_UI_CONFIRM,
		LOBBY_UI_SSMALL,
		LOBBY_UI_MEMBERNOTICE,		//멤버쉽 보러가기
	};

	SmallButtonPanel(DMY_BUTTON_TYPE type);
	virtual ~SmallButtonPanel();

	void InitPanel();
	
	virtual void onClicked(const string& name);

	void SetBtnText(string _text);
	void SetButtonListener(Button::Listener* _ptr);
	void setSaleState(int originPay, int salePay);
	void setNoUse();	// 사용불가
	bool isDiscountType();

public:
	Button* m_Button;

private:
	DMY_BUTTON_TYPE mType;
	Nx::Label* m_TextShadow;
	Nx::Label* m_Text;
	SkelObject* mLightEffect;
	SkelObject* mResourceIcon;
	Nx::Label* mBeforeAmountLabel;
	Nx::Label* mBeforeAmountUnderLabel;
	Nx::Label* mSaledAmountLabel;
	Nx::Label* mSaledAmountUnderLabel;
	Nx::Label* mButtonLabel;
	Nx::Label* mButtonLabelUnder;
};
