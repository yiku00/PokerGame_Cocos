#include "pch.h"
#include "SmallButtonPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "PokerResourceHelper.h"

SmallButtonPanel::SmallButtonPanel(DMY_BUTTON_TYPE type)
{
	mType = type;
	m_TextShadow = nullptr;
	m_Text = nullptr;
	m_Button = nullptr;
	mLightEffect = nullptr;
	mResourceIcon = nullptr;
	InitPanel();		
}

SmallButtonPanel::~SmallButtonPanel()
{
	//destruct();
}

void SmallButtonPanel::InitPanel()
{
	//안 쓰는
	mButtonLabel = nullptr;
	mButtonLabelUnder = nullptr;
	mBeforeAmountLabel = nullptr;
	mBeforeAmountUnderLabel = nullptr;
	mSaledAmountLabel = nullptr;
	mSaledAmountUnderLabel = nullptr;
	mResourceIcon = nullptr;

	if (mType == LOBBY_FRIEND_TYPE) {
		construct(getMxmlPath() + "dmy_button_small.mxml");
		getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_TextShadow = getLabel("txt_button_under");
		m_Text = getLabel("txt_button");
		m_Button = getButton("sbtn_button");
	}
	else if (mType == LOBBY_UI_TYPE) {
		construct(getMxmlPath() + "dmy_button_sub.mxml");
		m_TextShadow = getLabel("txt_sub_under");
		m_Text = getLabel("txt_sub");
		m_Button = getButton("sbtn_button");
		mLightEffect = getSkel("skel_light");
	}
	else if (mType == LOBBY_UI_SHOP_TYPE) {
		construct(getMxmlPath() + "dmy_button_shop.mxml");
		m_TextShadow = getLabel("txt_price1_under");
		m_Text = getLabel("txt_price1");
		m_Button = getButton("sbtn_button");
		getImage("skel_icon")->setVisible(false);	//안 쓴다.		
		mButtonLabel = getLabel("txt_price2_under");
		mButtonLabel->setVisible(false);
		mButtonLabelUnder = getLabel("txt_price2");
		mButtonLabelUnder->setVisible(false);
	}
	else if (mType == LOBBY_UI_SHOP_RUBY) {
		construct(getMxmlPath() + "dmy_button_shop.mxml");
		m_TextShadow = getLabel("txt_price2_under");
		m_Text = getLabel("txt_price2");
		m_Button = getButton("sbtn_button");		
		mButtonLabelUnder = getLabel("txt_price1_under");
		mButtonLabelUnder->setVisible(false);
		mButtonLabel = getLabel("txt_price1");
		mButtonLabel->setVisible(false);
	}
	else if (mType == LOBBY_UI_SHOP_DISCOUNT) {
		construct(getMxmlPath() + "dmy_button_shop_discount.mxml");		
		m_Button = getButton("sbtn_button");
		mResourceIcon = getSkel("skel_icon");
		mBeforeAmountLabel = getLabel("txt_price1");
		mBeforeAmountUnderLabel = getLabel("txt_price1_under");
		mSaledAmountLabel = getLabel("txt_price2");
		mSaledAmountUnderLabel = getLabel("txt_price2_under");
	}
	else if (mType == LOBBY_UI_IMPOSSIBLE) {
		construct(getMxmlPath() + "dmy_button_shop.mxml");		
		m_Button = getButton("sbtn_button");
		mResourceIcon = getSkel("skel_icon");
		setNoUse();
	}
	else if (mType == LOBBY_UI_BIG_SHOP_RUBY) {
		construct(getMxmlPath() + "dmy_button_smiddle.mxml");
		m_TextShadow = getLabel("txt_button_under2");
		m_Text = getLabel("txt_button2");
		m_Button = getButton("sbtn_button");
		mButtonLabelUnder = getLabel("txt_button_under");
		mButtonLabelUnder->setVisible(false);
		mButtonLabel = getLabel("txt_button");
		mButtonLabel->setVisible(false);
		mResourceIcon = getSkel("skel_icon_gold2");
		mResourceIcon->playAnimation(PokerResourceHelper::getRubyIcon());
	}
	else if (mType == LOBBY_UI_BIG_DISCOUNT) {
		construct(getMxmlPath() + "dmy_button_smiddle_discount.mxml");
		m_Button = getButton("sbtn_button");
		mResourceIcon = getSkel("skel_icon_gold");
		mResourceIcon->playAnimation(PokerResourceHelper::getRubyIcon());
		mBeforeAmountLabel = getLabel("txt_price1");
		mBeforeAmountUnderLabel = getLabel("txt_price1_under");
		mSaledAmountLabel = getLabel("txt_button2");
		mSaledAmountUnderLabel = getLabel("txt_button_under2");
	}
	else if (mType == LOBBY_UI_CONFIRM) {
		construct(getMxmlPath() + "dmy_button_smiddle.mxml");
		m_TextShadow = getLabel("txt_button_under");
		m_Text = getLabel("txt_button");
		m_Button = getButton("sbtn_button");
		m_Button->setSkelAnimation("button_smiddle_y");
		mButtonLabelUnder = getLabel("txt_button_under2");
		mButtonLabelUnder->setVisible(false);
		mButtonLabel = getLabel("txt_button2");
		mButtonLabel->setVisible(false);
		mResourceIcon = getSkel("skel_icon_gold2");
		mResourceIcon->setVisible(false);
	}
	else if (mType == LOBBY_UI_MEMBERNOTICE) {
		construct(getMxmlPath() + "dmy_button_smiddle.mxml");
		m_TextShadow = getLabel("txt_button_under");
		m_Text = getLabel("txt_button");
		m_Button = getButton("sbtn_button");
		m_Button->setSkelAnimation("button_smiddle_y");
		mButtonLabelUnder = getLabel("txt_button_under2");
		mButtonLabelUnder->setVisible(false);
		mButtonLabel = getLabel("txt_button2");
		mButtonLabel->setVisible(false);
		mResourceIcon = getSkel("skel_icon_gold2");
		mResourceIcon->setVisible(false);
	}
	else if (mType == LOBBY_UI_SSMALL) {
		construct(getMxmlPath() + "dmy_button_ssmall.mxml");
		m_Button = getButton("sbtn_button");	
		m_TextShadow = getLabel("txt_button_under");
		m_Text = getLabel("txt_button");
	}
}

void SmallButtonPanel::onClicked(const string& name)
{
	return;
}

void SmallButtonPanel::SetBtnText(string _text)
{
	if (m_TextShadow == nullptr || m_Text == nullptr)
		return;

	m_TextShadow->setString(_text.c_str());
	m_Text->setString(_text.c_str());
}

void SmallButtonPanel::SetButtonListener(Button::Listener* _listener)
{
	if (m_Button == nullptr)
		return;

	m_Button->setListener(_listener);
}

void SmallButtonPanel::setSaleState(int originPay, int salePay)
{
	mBeforeAmountLabel->setString(StringConverter::toString(originPay).c_str());
	mBeforeAmountUnderLabel->setString(StringConverter::toString(originPay).c_str());
	mSaledAmountLabel->setString(StringConverter::toString(salePay).c_str());
	mSaledAmountUnderLabel->setString(StringConverter::toString(salePay).c_str());
}

void SmallButtonPanel::setNoUse()
{
	//글씨 표시
	getLabel("txt_price2_under")->setVisible(false);
	getLabel("txt_price2")->setVisible(false);
	getLabel("txt_price1")->setVisible(true);
	getSkel("skel_icon")->setVisible(false);
	getLabel("txt_price1_under")->setVisible(true);
	getLabel("txt_price1_under")->setString(GameStringDepot::getSingleton().getString("MEMBER_CANT_BUY_BTN").c_str());
	getLabel("txt_price1")->setString(GameStringDepot::getSingleton().getString("MEMBER_CANT_BUY_BTN").c_str());
	getLabel("txt_price1")->setColor(StringConverter::parseColor3B("ffd042"));
	m_Button->setEnable(false);
	m_Button->setSkelAnimation("button_shop_use");

	if (hasElement("skel_line")){
		getImage("skel_line")->setVisible(false);
	}		
}

bool SmallButtonPanel::isDiscountType()
{
	return mType == LOBBY_UI_SHOP_DISCOUNT;
}
