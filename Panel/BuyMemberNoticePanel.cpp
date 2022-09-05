#include "pch.h"
#include "BuyMemberNoticePanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "PanelHelper.h"
#include "GameDataManager.h"


BuyMemberNoticePanel::BuyMemberNoticePanel()
{
	initPanel();
}

BuyMemberNoticePanel::~BuyMemberNoticePanel()
{
	//destruct();
}

void BuyMemberNoticePanel::onClicked(const string& name)
{
	if (name == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == getButtonName(mMemberBtn->m_Button)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
		PanelHelper::pushMemberShipShopPanel();
	}
}

void BuyMemberNoticePanel::initPanel()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_membership_indu.mxml");
	setButtonListener(this);
	mCloseBtn = getButton("sbtn_cancel");
	//제목
	getLabel("txt_title");
	getLabel("txt_title_under");
	//금고
	//는
	//멤버쉽
	//을 구입하셔야
	//사용할 수 있습니다.
	//더 많은 혜택을 확인해보세요.

	
	{
		int fontSize = GameStringDepot::getSingleton().getStringSize("BuyMemberNoticePanel_DESC_1");
		//금고는
		Script* descScript = Script::create(GameStringDepot::getSingleton().getString("BuyMemberNoticePanel_DESC_1"), getDummy("dmy_info1").size, fontSize, kCCTextAlignmentLeft, "KBIZgo H");
		CCSize contentSize = descScript->getContentSize();
		int gapHeight = getFontGap("fonts/KBIZgo H.ttf", fontSize);
		descScript->setCenterPos(getImage("dmy_info1")->getPosition(), gapHeight);
		addChild(descScript);
	}

	{
		int fontSize = GameStringDepot::getSingleton().getStringSize("BuyMemberNoticePanel_DESC_2");
		//멤버쉽을 구입하셔야
		Script* descScript = Script::create(GameStringDepot::getSingleton().getString("BuyMemberNoticePanel_DESC_2"), getDummy("dmy_info2").size, fontSize, kCCTextAlignmentLeft, "KBIZgo H");
		CCSize contentSize = descScript->getContentSize();
		int gapHeight = getFontGap("fonts/KBIZgo H.ttf", fontSize);
		descScript->setCenterPos(getImage("dmy_info2")->getPosition(), gapHeight);
		addChild(descScript);
	}

	{
		int fontSize = GameStringDepot::getSingleton().getStringSize("BuyMemberNoticePanel_DESC_3");
		//사용할 수 있습니다.
		Script* descScript = Script::create(GameStringDepot::getSingleton().getString("BuyMemberNoticePanel_DESC_3"), getDummy("dmy_info3").size, fontSize, kCCTextAlignmentLeft, "KBIZgo H");
		CCSize contentSize = descScript->getContentSize();
		int gapHeight = getFontGap("fonts/KBIZgo H.ttf", fontSize);
		descScript->setCenterPos(getImage("dmy_info3")->getPosition(), gapHeight);
		addChild(descScript);
	}


	mMemberBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_MEMBERNOTICE);
	addChild(mMemberBtn);
	mMemberBtn->release();
	CCPoint pos = getDummy("dmy_button_smiddle").origin;
	pos.y = -pos.y;
	mMemberBtn->setPosition(pos);
	mMemberBtn->m_Button->setName("buy");
	mMemberBtn->SetButtonListener(this);
	mMemberBtn->SetBtnText(GameStringDepot::getSingleton().getString("BuyMemberNoticePanel_MemberBtn"));

}