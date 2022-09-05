#include "pch.h"
#include "BuyMemberShipConfirmPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "FriendHelper.h"
#include "PokerShopHelper.h"
#include "PokerResourceHelper.h"

BuyMemberShipConfirmPanel::BuyMemberShipConfirmPanel()
{
	initPanel();
}

BuyMemberShipConfirmPanel::BuyMemberShipConfirmPanel(string okMessage)
{
	mEventStr = okMessage;
	confirmPanel();
}

BuyMemberShipConfirmPanel::~BuyMemberShipConfirmPanel()
{

}

void BuyMemberShipConfirmPanel::initPanel()
{
	addMouseBlockPanel(this , true);	//ok 처리
	construct(getMxmlPath() + "dmy_get_board_buy1.mxml");	
	setButtonListener(this);
	mTitle = getLabel("txt_title");
	mTitleUnder = getLabel("txt_title_under");
	//titie
	mTitle->setString(GameStringDepot::getSingleton().getString("MEMBER_CONFIRM_TITLE").c_str());
	mTitleUnder->setString(GameStringDepot::getSingleton().getString("MEMBER_CONFIRM_TITLE").c_str());

	//왼쪽 사진
	mMemberShipImg = getImage("dmy_member_gold");
	//아이템 이름
	mItemName = getLabel("txt_item_name");

	CCPoint _RankPos = getDummy("dmy_number_shop").origin;
	CCSize _RankSize = getDummy("dmy_number_shop").size;
	_RankPos.x = _RankPos.x + _RankSize.width;	
	_RankPos.y = DESIGN_HEIGHT - _RankPos.y - (_RankSize.height / 2);
	mTerm = CCLabelBMFont::create("", "fonts/number_shop.fnt");
	mTerm->setContentSize(_RankSize);
	mTerm->setAnchorPoint(ccp(1.f, 0.5f));	
	addChild(mTerm);
	mTerm->setString("+30");	
	mTerm->setPosition(_RankPos);
	mCancelBtn = getButton("sbtn_cancel");	

	//일
	getLabel("txt_item_info")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_DAY").c_str());
	//구매합니다.
	getLabel("txt_buy")->setString(GameStringDepot::getSingletonPtr()->getString("BuyCharacterConfirmPanel_BUY").c_str());

	getLabel("txt_silverinfo1")->setVisible(false);
	getLabel("txt_silverinfo2")->setVisible(false);
	getLabel("txt_silverinfo3")->setVisible(false);	
}

void BuyMemberShipConfirmPanel::onClicked(const string& name)
{
	if (name == "buy") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
		fireMessage(mEventStr);
	}
	else if (name == getButtonName(mCancelBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
}

void BuyMemberShipConfirmPanel::setMemberConfirm(int memberShipId)
{
	//item Desc
	W_MonthlyClassShopData _Data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(memberShipId);
	W_MonthlyClassData _pData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassdata(PokerShopHelper::getMonthlyClassData(_Data.id()));
	mItemName->setString(_Data.name().c_str());
	
	//캐릭터 사진
	mMemberShipImg->setSpriteFrameWithFile(PokerResourceHelper::getMemberShipIcon(memberShipId));
	mMemberShipImg->fit(getDummy("dmy_member_gold").size);

	//금액 표시
	if (GameDataManager::getSingleton().getPlayerInfo().ismonthlyclassdiscount()) {
		mBuyBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_BIG_DISCOUNT);
		addChild(mBuyBtn);
		mBuyBtn->release();
		CCPoint pos = getDummy("dmy_button_smiddle").origin;
		pos.y = -pos.y;
		mBuyBtn->setPosition(pos);
		mBuyBtn->m_Button->setName("buy");
		mBuyBtn->SetButtonListener(this);
		mBuyBtn->setSaleState(_Data.cash(), _Data.cash() - _pData.discountcash());
		mBuyBtn->m_Button->setSkelAnimation("button_smiddle_y");
	}
	else {
			
		mBuyBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_BIG_SHOP_RUBY);
		addChild(mBuyBtn);
		mBuyBtn->release();
		CCPoint pos = getDummy("dmy_button_smiddle").origin;
		pos.y = -pos.y;
		mBuyBtn->setPosition(pos);
		mBuyBtn->m_Button->setName("buy");
		mBuyBtn->SetButtonListener(this);			
		mBuyBtn->SetBtnText(StringConverter::toString(_Data.cash()));
		mBuyBtn->m_Button->setSkelAnimation("button_smiddle_y");
	}	
	mEventStr = "MonthlyClass_Shop_Res_" + StringConverter::toString(memberShipId);
	setListener(WebService::getSingletonPtr());	
}

void BuyMemberShipConfirmPanel::confirmPanel()
{
	initPanel();
	getLabel("txt_silverinfo1")->setVisible(true);
	getLabel("txt_silverinfo2")->setVisible(true);
	getLabel("txt_silverinfo3")->setVisible(true);

	//titie
	mTitle->setString(GameStringDepot::getSingleton().getString("MEMBER_NOTICE_TITLE").c_str());
	mTitleUnder->setString(GameStringDepot::getSingleton().getString("MEMBER_NOTICE_TITLE").c_str());

	//왼쪽 사진
	mMemberShipImg = getImage("dmy_member_gold");
	//아이템 이름
	mItemName->setVisible(false);
	mTerm->setVisible(false);
	mCancelBtn = getButton("sbtn_cancel");
	//일
	getLabel("txt_item_info")->setVisible(false);
	//구매합니다.
	getLabel("txt_buy")->setVisible(false);
	getLabel("txt_silverinfo1")->setString(GameStringDepot::getSingleton().getString("MEMBERSHIP_CONFIRM_GOLD_DESC_1").c_str());
	getLabel("txt_silverinfo2")->setString(GameStringDepot::getSingleton().getString("MEMBERSHIP_CONFIRM_GOLD_DESC_2").c_str());
	getLabel("txt_silverinfo3")->setString(GameStringDepot::getSingleton().getString("MEMBERSHIP_CONFIRM_GOLD_DESC_3").c_str());	

	//캐릭터 사진
	mMemberShipImg->setSpriteFrameWithFile(PokerResourceHelper::getMemberShipIcon(0));
	mMemberShipImg->fit(getDummy("dmy_member_gold").size);

	mBuyBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_CONFIRM);
	addChild(mBuyBtn);
	mBuyBtn->release();
	CCPoint pos = getDummy("dmy_button_smiddle").origin;
	pos.y = -pos.y;
	mBuyBtn->setPosition(pos);
	mBuyBtn->m_Button->setName("buy");
	mBuyBtn->SetButtonListener(this);
	mBuyBtn->SetBtnText(GameStringDepot::getSingleton().getString("TXT_OK_LABEL").c_str());
}
