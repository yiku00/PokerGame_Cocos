#include "pch.h"
#include "BuySucessPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "FriendHelper.h"
#include "PokerShopHelper.h"
#include "PokerResourceHelper.h"

BuySucessPanel::BuySucessPanel(BUY_TYPE type)
{
	mType = type;
	initPanel();
	SoundManager::getSingleton().playEffect("result_star");

}

BuySucessPanel::~BuySucessPanel()
{

}

void BuySucessPanel::initPanel()
{


	mAni = nullptr;
	mItemImg = nullptr;

	if (mType == BUY_CHARACTER)
		construct(getMxmlPath() + "dmy_get_board_buy2charac.mxml");		//캐릭터
	else if (mType == BUY_CARD)
		construct(getMxmlPath() + "dmy_get_board_buy2card.mxml");		//캐릭터
	else if (mType == BUY_RUBY)
		construct(getMxmlPath() + "dmy_get_board_buy2ruby.mxml");		//캐릭터		
	else
		construct(getMxmlPath() + "dmy_get_board_buy2.mxml");			//멤버쉽



	if (mType == BUY_MEMBERSHIP)
		mItemImg = getImage("dmy_membership");
	else if (mType == BUY_RUBY)
		mItemImg = getImage("dmy_rubby");
	else if (mType == BUY_CHARACTER)
		mItemImg = getImage("dmy_character");	
	else if (mType == BUY_CARD)
		mItemImg = getImage("dmy_card");

	//골드 멤버쉽
	mItemName = getLabel("txt_item_name");
	mItemNameUnder = getLabel("txt_item_name_under");
	//골드등
	mItemNamePost = getLabel("txt_item_info");
	mItemNamePostUnder = getLabel("txt_item_info_under");
	//구매완료
	mBuyComplete = getLabel("txt_get");
	mBuyCompleteUnder = getLabel("txt_get_under");
	mItemDesc = getLabel("txt_check");
	mItemDescUnder = getLabel("txt_check_under");
	//rewardinfo 추가
	mReward = getLabel("txt_bonus");
	mRewardUnder = getLabel("txt_bonus_under");
	//55조6000억골드
	//rewarddesc
	mRewardDesc = getLabel("txt_bonus_info");
	mRewardDescUnder = getLabel("txt_bonus_info_under");
	// 마이룸 맴버쉽에서 확인가능합니다.	
	mTouchDesc = getLabel("txt_touch");	
	mTouchDesc->setVisible(false);
	mAni = getSkel("skel_light");
	mAni->addEventListener(this);
}

void BuySucessPanel::setCharacterSucess(int characterInfoId , int useRuby)
{
	int shopIdx = PokerShopHelper::getShopDataIndex(characterInfoId);
	W_CharacterShopData _ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(shopIdx);
	W_CharacterData _Data = PokerShopHelper::getCharacterData(_ShopInfo.characterid());
	string characterNameStr = _Data.name();
	//아이템 이름
	mItemName->setString(_ShopInfo.name().c_str());
	mItemNameUnder->setString(_ShopInfo.name().c_str());
	
	//이미지
	string characterImgStr = PokerResourceHelper::getCharacterShopWithMoneyImgName(_ShopInfo.characterid());
	mItemImg->setSpriteFrameWithFile(characterImgStr);
	//일
	mItemNamePost->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_CHARACTER_POST").c_str());
	mItemNamePostUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_CHARACTER_POST").c_str());
	//구매완료!!
	mBuyComplete->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_COMPLETE").c_str());
	mBuyCompleteUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_COMPLETE").c_str());
	//확인창
	mItemDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_CHARACTER_ITEMDESC").c_str());
	mItemDescUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_CHARACTER_ITEMDESC").c_str());

	//금액 표시
	string _rewardText = "+";
	if (_ShopInfo.has_rewardinfo())
	{
		int _rewardSize = _ShopInfo.rewardinfo().rewardset_size();

		for (int _j = 0; _j < _rewardSize; _j++)
		{
			W_RewardInfo_RewardSet _set = _ShopInfo.rewardinfo().rewardset(_j);


			//if (_set.has_id());

			if (_set.has_amount())
			{
				_rewardText = PokerResourceHelper::getImgFontForGameMoney(_set.amount(), false);
			}
		}
	}	


	CCPoint _RankPos = getDummy("dmy_number_shop_80p").origin;
	CCSize _RankSize = getDummy("dmy_number_shop_80p").size;
	_RankPos.x = _RankPos.x + _RankSize.width;
	_RankPos.y = DESIGN_HEIGHT - _RankPos.y - (_RankSize.height / 2);
	mTerm = CCLabelBMFont::create("", "fonts/number_shop_80p.fnt");
	mTerm->setContentSize(_RankSize);
	mTerm->setAnchorPoint(ccp(1.f, 0.5f));
	addChild(mTerm);
	mTerm->setString(_rewardText.c_str());
	mTerm->setPosition(_RankPos);
	//안 보이게	
	mReward->setVisible(false);
	mRewardUnder->setVisible(false);
	mRewardDesc->setVisible(false);
	mRewardDescUnder->setVisible(false);

	mTouchDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_TOUCHDESC").c_str());
	//skel 애니 시작
	//화면 터치
	mAni->playAnimation("light_character_start");
	mAni->appendAnimation("light_character_stay", true);	
}

void BuySucessPanel::setMemberShipSucess(int memberShipId, W_RewardInfo rewardInfo)
{
	//item Desc
	int memberShipIndex = PokerShopHelper::getMemberShipIndex(memberShipId);
	W_MonthlyClassShopData _Data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(memberShipIndex);
	W_MonthlyClassData _pData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassdata(PokerShopHelper::getMonthlyClassData(memberShipId));
	mItemName->setString(_Data.name().c_str());
	mItemNameUnder->setString(_Data.name().c_str());

	//캐릭터 사진
	mItemImg->setSpriteFrameWithFile(PokerResourceHelper::getMemberShipIcon(memberShipIndex));
	//+30
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
	//일
	mItemNamePost->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_MEBERSHIP_POST").c_str());
	mItemNamePostUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_MEBERSHIP_POST").c_str());
	//구매완료!!
	mBuyComplete->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_COMPLETE").c_str());
	mBuyCompleteUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_COMPLETE").c_str());
	//확인창
	mItemDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_MEBERSHIP_ITEMDESC").c_str());
	mItemDescUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_MEBERSHIP_ITEMDESC").c_str());
	
	mReward->setVisible(false);
	mRewardUnder->setVisible(false);
	mRewardDesc->setVisible(false);
	mRewardDescUnder->setVisible(false);
	mTouchDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_TOUCHDESC").c_str());	
	//skel 애니 시작
	//화면 터치
	mAni->playAnimation("light_member_start");
	mAni->appendAnimation("light_member_stay",true);	
}

bool BuySucessPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (mTouchDesc->isVisible()) {
		LayerManager::getSingleton().popLayer(this);
	}
	return true;
}

void BuySucessPanel::setRubySucess(int rewardRuby, int rubyId ,bool isFirstBuy)
{
	string itemNameStr = "";
	string imgStr = "";
	string firstStr = "";
	bool isMonthly = false;
	for (int i = 0; i < GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata_size(); i++)
	{
		if (GameDataManager::getSingleton().GetGameDataPtr()->cashshopdata(i).id() == rubyId) {
			itemNameStr = GameDataManager::getSingleton().GetGameDataPtr()->cashshopdata(i).title();
			imgStr = "ui/" + GameDataManager::getSingleton().GetGameDataPtr()->cashshopdata(i).icon() + ".png";
			firstStr = GameDataManager::getSingleton().GetGameDataPtr()->cashshopdata(i).desc_2();
			isMonthly = GameDataManager::getSingleton().GetGameDataPtr()->cashshopdata(i).functiontype() == W_CashShopData_eFunctionType_Monthly;
		}
	}


	mItemName->setString(itemNameStr.c_str());
	mItemNameUnder->setString(itemNameStr.c_str());
	//샵 사진
	mItemImg->setSpriteFrameWithFile(imgStr);
	CCPoint _RankPos = getDummy("dmy_number_shop_ruby").origin;
	CCSize _RankSize = getDummy("dmy_number_shop_ruby").size;
	_RankPos.x = _RankPos.x + _RankSize.width;
	_RankPos.y = DESIGN_HEIGHT - _RankPos.y - (_RankSize.height / 2);
	mTerm = CCLabelBMFont::create("", "fonts/number_shop_ruby.fnt");
	mTerm->setContentSize(_RankSize);
	mTerm->setAnchorPoint(ccp(1.f, 0.5f));
	addChild(mTerm);
	string rewardStr = "+" + StringConverter::toString(rewardRuby);
	mTerm->setString(rewardStr.c_str());
	mTerm->setPosition(_RankPos);

	//일
	mItemNamePost->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_RUBY_POST").c_str());
	mItemNamePostUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_RUBY_POST").c_str());
	//구매완료!!
	mBuyComplete->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_COMPLETE").c_str());
	mBuyCompleteUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_COMPLETE").c_str());
	//확인창
	mItemDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_RUBY_ITEMDESC").c_str());
	mItemDescUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_RUBY_ITEMDESC").c_str());

	//첫 결제였다면 표시 해주고
	if (isFirstBuy) {
		mReward->setString(firstStr.c_str());
		mRewardUnder->setString(firstStr.c_str());
		mRewardDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_RUBY_REWARD_DESC").c_str());
		mRewardDescUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_RUBY_REWARD_DESC").c_str());
	}
	else {
		mReward->setVisible(false);
		mRewardUnder->setVisible(false);
		mRewardDesc->setVisible(false);
		mRewardDescUnder->setVisible(false);
	}
	
	mTouchDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_TOUCHDESC").c_str());
	//skel 애니 시작
	//화면 터치
	mAni->playAnimation("light_rubby_start");
	mAni->appendAnimation("light_rubby_stay", true);
	//월정액이라면 표시 수정 + 55개 이런거 안 보이게 한다.

	if (isMonthly) {
		mTerm->setString("+30");		
		mItemNamePost->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_MEBERSHIP_POST").c_str());
		mItemNamePostUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_MEBERSHIP_POST").c_str());
		mItemDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_MONTHLY_RUBY_ITEMDESC").c_str());
		mItemDescUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_MONTHLY_RUBY_ITEMDESC").c_str());
	}
}

void BuySucessPanel::update(float dt)
{
	if (mAni && mItemImg) {
		spBone* bone = mAni->getRootSkelAnimNode()->findBone("image");
		if (bone) {
			Nx::Transform t = mAni->getRootSkelAnimNode()->getBoneWorldTransform("image");
			mItemImg->setPosition(t.translation);
			mItemImg->setRotation(t.angle);
			mItemImg->setScaleX(t.scaleX);
			mItemImg->setScaleY(t.scaleY);
		}
	}	
}

void BuySucessPanel::setSkinSucess(int characterInfoId, int useRuby)
{
	int shopIdx = PokerShopHelper::getSkinShopDataIndex(characterInfoId);
	W_SkinShopData _ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->skinshopdata(shopIdx);
	const W_SkinData* skinData = GameDataManager::getSingleton().getSkinData(_ShopInfo.skinid());
	string characterNameStr = skinData->name();
	//아이템 이름
	mItemName->setString(skinData->name().c_str());
	mItemNameUnder->setString(skinData->name().c_str());

	//이미지
	string characterImgStr = PokerResourceHelper::getSkinShopWithMoneyImgName(_ShopInfo.skinid());
	mItemImg->setSpriteFrameWithFile(characterImgStr);
	//일
	mItemNamePost->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_CHARACTER_POST").c_str());
	mItemNamePostUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_CHARACTER_POST").c_str());
	//구매완료!!
	mBuyComplete->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_COMPLETE").c_str());
	mBuyCompleteUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_COMPLETE").c_str());
	//확인창
	mItemDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_CHARACTER_ITEMDESC").c_str());
	mItemDescUnder->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_CHARACTER_ITEMDESC").c_str());

	//금액 표시
	string _rewardText = "+";
	if (_ShopInfo.has_rewardinfo())
	{
		int _rewardSize = _ShopInfo.rewardinfo().rewardset_size();

		for (int _j = 0; _j < _rewardSize; _j++)
		{
			W_RewardInfo_RewardSet _set = _ShopInfo.rewardinfo().rewardset(_j);


			//if (_set.has_id());

			if (_set.has_amount())
			{
				_rewardText = PokerResourceHelper::getImgFontForGameMoney(_set.amount(), false);
			}
		}
	}


	CCPoint _RankPos = getDummy("dmy_number_shop_80p").origin;
	CCSize _RankSize = getDummy("dmy_number_shop_80p").size;
	_RankPos.x = _RankPos.x + _RankSize.width;
	_RankPos.y = DESIGN_HEIGHT - _RankPos.y - (_RankSize.height / 2);
	mTerm = CCLabelBMFont::create("", "fonts/number_shop_80p.fnt");
	mTerm->setContentSize(_RankSize);
	mTerm->setAnchorPoint(ccp(1.f, 0.5f));
	addChild(mTerm);
	mTerm->setString(_rewardText.c_str());
	mTerm->setPosition(_RankPos);
	//안 보이게	
	mReward->setVisible(false);
	mRewardUnder->setVisible(false);
	mRewardDesc->setVisible(false);
	mRewardDescUnder->setVisible(false);

	mTouchDesc->setString(GameStringDepot::getSingleton().getString("BuySucessPanel_TOUCHDESC").c_str());
	//skel 애니 시작
	//화면 터치
	mAni->playAnimation("light_card_start");
	mAni->appendAnimation("light_card_stay", true);	
}

void BuySucessPanel::onEvent(int trackIdx, spEvent* event)
{
	mTouchDesc->setVisible(true);
	mTouchDesc->runAction(PokerResourceHelper::getRepeatTwinkle());
}


void BuySucessPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}