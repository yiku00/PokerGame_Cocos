#include "pch.h"
#include "MemberShipContentPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

MemberShipContentPanel::MemberShipContentPanel(MEMBERSHIP_TYPE type)
{
	mMemberType = type;
	InitPanel();
	InitImage();
	initButton();	
	setButtonListener(this);
	refresh();
}

MemberShipContentPanel::~MemberShipContentPanel()
{
	//destruct();
}

void MemberShipContentPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_membership.mxml");	
	setButtonListener(this);	
	mDetailBtn = getButton("sbtn_buttoninfo");
	mDetailStr = getLabel("txt_detail");
	mSpecLabel = getLabel("txt_membership_spec");

	if (mMemberType == MEMBER_SILVER) {
		getSkel("skel_membership_gold")->playAnimation("membership_silver");
		mDetailBtn->setSkelAnimation("button_insilver");
		mDetailStr->setColor({ 74, 80, 90 });
		mSpecLabel->setColor({ 74, 80, 90 });
	}
	else if (mMemberType == MEMBER_GOLD) {
		getSkel("skel_membership_gold")->playAnimation("membership_gold");
		mDetailBtn->setSkelAnimation("button_ingold");
		
		mDetailStr->setColor({ 103, 57, 13 });
		mSpecLabel->setColor({ 103, 57, 13 });
	}

	

	//spec
	W_MonthlyClassShopData _Data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(mMemberType);	
	int _line = _Data.desc_size();
	string _desc = "";
	for (int _l = 0; _l < _line; _l++)
	{
		W_MonthlyClassShopData_ShopDesc _ShopDesc = _Data.desc(_l);
		if (_ShopDesc.has_content())
		{
			_desc += _ShopDesc.content();
		}
		if (_l != _line - 1)
		{
			_desc += "\n";
		}
	}
	mSpecLabel->setString(_desc.c_str());
}

void MemberShipContentPanel::InitImage()
{
	mApplyIcon = getImage("skel_mark_apply");
	mDiscountLabel = getLabel("txt_discount");

	mApplyLabel = getLabel("txt_apply");
	mApplyUnderLabel = getLabel("txt_apply_under");

	mLeftLabel = getLabel("txt_leftbutton");
	mMiddleLabel = getLabel("txt_discount");
	mRightLabel = getLabel("txt_rightbutton");
}

void MemberShipContentPanel::onClicked(const string& name)
{
	if (name == mSelectBtn->getName()) {
		fireMessage("SELECT_MEMBERSHIP" + StringConverter::toString(mMemberType));
	}
}

void MemberShipContentPanel::initButton()
{
	CCPoint _btnPos = getDummy("dmy_button_shop3").origin;
	m_ButtonPanel = new Panel();
	m_ButtonPanel->construct(getMxmlPath() + "dmy_button_shop.mxml");
	m_ButtonPanel->setPositionX(_btnPos.x);
	m_ButtonPanel->setPositionY(-_btnPos.y);
	addChild(m_ButtonPanel);
	m_ButtonPanel->release();

	mSelectBtn = m_ButtonPanel->getButton("sbtn_button");
	mSelectBtnLabel = m_ButtonPanel->getLabel("txt_price1");
	mSelectBtn->setListener(this);
	m_ButtonPanel->getImage("skel_icon")->setVisible(false);
	m_ButtonPanel->getLabel("txt_price2_under")->setVisible(false);
	m_ButtonPanel->getLabel("txt_price2")->setVisible(false);
	m_ButtonPanel->getLabel("txt_price1_under")->setVisible(false);
	//m_ButtonPanel->getLabel("txt_price1")->setVisible(false);		
}

void MemberShipContentPanel::refresh()
{
	refreshBtnState();
	refreshApply();
}

void MemberShipContentPanel::refreshBtnState()
{
	mApplyLabel->setVisible(false);
	mApplyUnderLabel->setVisible(false);

	mLeftLabel->setVisible(false);
	mMiddleLabel->setVisible(true);
	mRightLabel->setVisible(false);

	PlayerData * _playerData = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();
	if (_playerData->m_MonthlyClassID == 0) {
		//구매하기 버튼.
		mMiddleLabel->setString(GameStringDepot::getSingleton().getString("MEMBER_NOT_APPLY_DESC").c_str());
		mSelectBtnLabel->setString(GameStringDepot::getSingleton().getString("MEMBER_BTN_BUY").c_str());
	}
	else {
		W_MonthlyClassShopData _Data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(mMemberType);
		if (_Data.id() == _playerData->m_MonthlyClassID) {
			//현재 적용중
			mApplyLabel->setVisible(true);
			mApplyUnderLabel->setVisible(true);			
			mSelectBtn->setEnable(false);
			mSelectBtn->setVisible(false);
			mMiddleLabel->setString(GameStringDepot::getSingleton().getString("MEMBER_APPLY_DESC").c_str());
			mSelectBtnLabel->setString(GameStringDepot::getSingleton().getString("MEMBER_BTN_CONTINUE").c_str());
		}
		else {
			//적용중이 아님
			mMiddleLabel->setString(GameStringDepot::getSingleton().getString("MEMBER_UPPER_APPLY_DESC").c_str());
			mSelectBtnLabel->setString(GameStringDepot::getSingleton().getString("MEMBER_BTN_READY").c_str());
		}
	}
}

void MemberShipContentPanel::refreshApply()
{
	mApplyIcon->setVisible(false);
	mDiscountLabel->setVisible(false);

}

