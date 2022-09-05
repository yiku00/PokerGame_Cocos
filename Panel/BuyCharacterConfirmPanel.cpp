#include "pch.h"
#include "BuyCharacterConfirmPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "FriendHelper.h"
#include "PokerShopHelper.h"
#include "PokerResourceHelper.h"
#include "W_PayReserveReq.pb.h"
#include "W_PayReserveRes.pb.h"
#include "CmdQueue.h"
#include "W_PayReq.pb.h"
#include "W_PayRes.pb.h"
#include "PanelHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include "android/IapManager.h"
#endif

BuyCharacterConfirmPanel::BuyCharacterConfirmPanel()
{
	initPanel();
}

BuyCharacterConfirmPanel::~BuyCharacterConfirmPanel()
{

}

void BuyCharacterConfirmPanel::initPanel()
{
	addMouseBlockPanel(this , true);	//ok 처리
	construct(getMxmlPath() + "dmy_get_board_buycharac.mxml");	
	setButtonListener(this);
	mTitle = getLabel("txt_title");
	mTitleUnder = getLabel("txt_title_under");
	//titie
	mTitle->setString(GameStringDepot::getSingleton().getString("CHARACTER_CONFIRM_TITLE").c_str());
	mTitleUnder->setString(GameStringDepot::getSingleton().getString("CHARACTER_CONFIRM_TITLE").c_str());

	mCharacterImg = getImage("dmy_character");
	mItemName = getLabel("txt_item_name");

	CCPoint _RankPos = getDummy("dmy_number_shop").origin;
	CCSize _RankSize = getDummy("dmy_number_shop").size;
	_RankPos.x = _RankPos.x + _RankSize.width;
	_RankPos.y = DESIGN_HEIGHT - _RankPos.y - (_RankSize.height / 2);
	mTerm = CCLabelBMFont::create("", "fonts/number_shop_80p.fnt");
	mTerm->setContentSize(_RankSize);
	mTerm->setAnchorPoint(ccp(1.0f, 0.5f));
	mTerm->setPosition(_RankPos);
	addChild(mTerm);	

	mCancelBtn = getButton("sbtn_cancel");	
	//골드
	getLabel("txt_item_info")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT").c_str());
	//구매합니다.
	getLabel("txt_buy")->setString(GameStringDepot::getSingletonPtr()->getString("BuyCharacterConfirmPanel_BUY").c_str());
}

void BuyCharacterConfirmPanel::setCharacterConfirm(int characterId)
{
	mCharacterShopId = characterId;
	W_CharacterShopData _ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(characterId);
	mCharacterId = _ShopInfo.characterid();
	W_CharacterData _Data = PokerShopHelper::getCharacterData(mCharacterId);
	string characterNameStr = "";
	string itemDescStr = "";
	int characterImgId = -1;
	if (_Data.has_id() && _ShopInfo.has_id())
	{
		if (_Data.id() == _ShopInfo.id())
		{
			characterImgId = _Data.id();
			if (_Data.has_name())
				characterNameStr = _Data.name();

			if (_ShopInfo.has_periodday())
				itemDescStr = "[" + StringConverter::toString(_ShopInfo.periodday()) + GameStringDepot::getSingleton().getString("TXT_DAY") + "]";

			if (_ShopInfo.has_rewardinfo())
			{
				int _rewardSize = _ShopInfo.rewardinfo().rewardset_size();
				string _rewardText = "";
				for (int _j = 0; _j < _rewardSize; _j++)
				{
					W_RewardInfo_RewardSet _set = _ShopInfo.rewardinfo().rewardset(_j);

					//if (_set.has_id());

					if (_set.has_amount())
						_rewardText += "+" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_set.amount()), 1);

					if (_set.has_type())
					{
						switch (_set.type())
						{
						case CASH:
							_rewardText += GameStringDepot::getSingleton().getString("TXT_GET_CASH");// U8(" CASH지급");
							break;
						case GAMEMONEY:
							_rewardText += GameStringDepot::getSingleton().getString("TXT_GET_GOLD");//U8(" GOLD지급");
							break;
						case CHIP:
							_rewardText += GameStringDepot::getSingleton().getString("TXT_GET_CHIP");// U8(" CHIP지급");
							break;
						case CHARACTER:
							continue;
							break;
						}
					}

					if (_j != _rewardSize - 1)
					{
						_rewardText += "\n";
					}

				}
				itemDescStr += _rewardText;
			}
		}
		//item Desc		
		string characterImgStr = PokerResourceHelper::getCharacterShopWithMoneyImgName(_ShopInfo.characterid());
		mCharacterImg->setSpriteFrameWithFile(characterImgStr);
		mItemName->setString(_ShopInfo.name().c_str());
		
		if (isCharacterMoneyType()) {				
			mBuyBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SHOP_TYPE);
			addChild(mBuyBtn);
			mBuyBtn->release();
			CCPoint pos = getDummy("dmy_button_smiddle").origin;
			pos.y = -pos.y;
			
			mBuyBtn->setPosition(pos);
			mBuyBtn->m_Button->setName("buy");
			mBuyBtn->SetButtonListener(this);				
			string txtPrice = StringConverter::toString(_ShopInfo.money()) + GameStringDepot::getSingleton().getString("TXT_COUNT_MONEY");
			mBuyBtn->SetBtnText(txtPrice);
		}		
		else {
				
			mBuyBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SHOP_RUBY);
			addChild(mBuyBtn);
			mBuyBtn->release();
			CCPoint pos = getDummy("dmy_button_smiddle").origin;
			pos.y = -pos.y;
			mBuyBtn->setPosition(pos);
			mBuyBtn->m_Button->setName("buy");
			mBuyBtn->SetButtonListener(this);				
			mBuyBtn->SetBtnText(StringConverter::toString(_ShopInfo.cash()));
		}

		//금액 표시		
		mEventStr = "Chracter_Shop_Res_" + StringConverter::toString(characterId);
		setListener(WebService::getSingletonPtr());
	}
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
				_rewardText = PokerResourceHelper::getImgFontForGameMoney(_set.amount() , false);
			}
		}
	}
	CCLOG("mtarmstr = %s", _rewardText.c_str());
	mTerm->setString((_rewardText).c_str());	
}

void BuyCharacterConfirmPanel::onClicked(const string& name)
{
	if (name == "buy") {
		if (isCharacterMoneyType()) {
			int32 _buyId = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(mCharacterShopId).id();
			sendPayReserveReq(_buyId);
		}
		else {
			LayerManager::getSingleton().popLayer(this);
			fireMessage(mEventStr);
		}		
	}
	else if (name == getButtonName(mCancelBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
}

bool BuyCharacterConfirmPanel::isCharacterMoneyType()
{
	bool isMoneyType = false;
	W_CharacterShopData _ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(mCharacterShopId);
	if (_ShopInfo.cash() == 0) {
		isMoneyType = true;
	}
	
	return isMoneyType;
}

void BuyCharacterConfirmPanel::sendPayReserveReq(int cashId)
{
	mBuyCashId = cashId;
	W_PayReserveReq req;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (IapManager::getSingleton().getPaymentType() == IapManager::ONE_STORE)
		req.set_markettype(OneStore);
	else
		req.set_markettype(Google);
#else
	req.set_markettype(Local);
#endif

	req.set_paytype(ePayCharacter);
	req.set_id(cashId);
	HttpMessage msg(req, HttpResponseHandler(BuyCharacterConfirmPanel::recvWPayReserveRes), this);
	HttpManager::getSingleton().send(msg);
}

void BuyCharacterConfirmPanel::recvWPayReserveRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_PayReserveRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		CCLog("W_PayReserveRes sucess");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
		if (IapManager::getSingleton().getPaymentType() == IapManager::ONE_STORE) {
			CCLog("W_PayReserveRes onestore");
			IapManager::getSingleton().sendPaymentRequest(res.productid(), "", res.tid());
		}
		else {
			mGoogleTid = res.productid();
			IapManager::getSingleton().launchPurchaseFlow(res.productid(), "", res.tid());
		}
#else
		//WebService::getSingletonPtr()->_sendCashBuyReq(mBuyCashId);
		CCLog("W_PayReserveRes win2");
		STCMD_IAP_ONESTORE_REQUEST_RESULT iapRequestResult;
		iapRequestResult.isSucess = true;
		iapRequestResult.errMsg = "";
		iapRequestResult.tid = res.tid();
		iapRequestResult.txid = "win";
		iapRequestResult.receipt = res.productid();
		CCmdQueue::getSingleton().pushQueue(iapRequestResult);

#endif // DEBUG


	}
	else {
		CCLog("W_PayReserveRes fail");
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}
}

bool BuyCharacterConfirmPanel::handling(STCMD &stCmd)
{
	if (!isVisible()) {
		CCLog("NO vislble false");
		return false;
	}

	if (auto *pstIt = castCMD<STCMD_IAP_ONESTORE_REQUEST_RESULT>(&stCmd))
	{
		STCMD_IAP_ONESTORE_REQUEST_RESULT res = *pstIt;
		if (res.isSucess) {
			CCLog("STCMD_IAP_REQUEST_RESULT sucess res.tid = %s , res.txid = %s , res.receipt = %s", res.tid.c_str(), res.txid.c_str(), res.receipt.c_str());
			sendW_PayReq(res.tid, res.txid, res.receipt);
		}
		else {
			CCLog("STCMD_IAP_REQUEST_RESULT false");
			SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errMsg, "IAP Request");
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}
		return true;
	}
	else if (auto *pstIt = castCMD<STCMD_IAP_GOOGLESTORE_REQUEST_RESULT>(&stCmd))
	{
		STCMD_IAP_GOOGLESTORE_REQUEST_RESULT res = *pstIt;
		if (res.isSucess) {
			CCLog("STCMD_IAP_REQUEST_RESULT sucess res.tid = %s , res.txid = %s , res.receipt = %s", res.tid.c_str(), res.orderId.c_str(), res.purchaseToken.c_str());
			sendW_PayReq(res.tid, res.orderId, res.purchaseToken);
		}
		else {
			CCLog("STCMD_IAP_REQUEST_RESULT false");
			SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errMsg, "IAP Request");
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}
		return true;
	}
	return false;
}

void BuyCharacterConfirmPanel::sendW_PayReq(string tID, string txId, string receipt)
{
	W_PayReq req;
	req.set_tid(tID);
	req.set_txid(txId);
	req.set_receipt(receipt);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
		req.set_order_id(txId);
	}
#endif
	HttpMessage msg(req, HttpResponseHandler(BuyCharacterConfirmPanel::recvW_PayRes), this);
	HttpManager::getSingleton().send(msg);
}

void BuyCharacterConfirmPanel::recvW_PayRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}


	W_PayRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		CCLog("recvW_PayRes sucess");
		LayerManager::getSingleton().popLayer(this);		
		if (res.has_playerinfo())
		{
			if (res.has_playerinfo())
			{
				int32 _curRuby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
				int32 _nextRuby = res.playerinfo().cash();
				PanelHelper::pushCharacterBuySucessPanel(mCharacterId, _nextRuby - _curRuby);
				GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
			}
			GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_BUY_CHARACTER_RES);
		}
		//똑같은 걸 두번 보낼수도 있어서...
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE && !mGoogleTid.empty()) {
			IapManager::getSingleton().consumeProduceId(mGoogleTid);
			mGoogleTid = "";
		}

		if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
			CCLog("W_PayRes checkAsyncInventory");
			IapManager::getSingleton().checkAsyncInventory();
		}
#endif
	}
	else {
		CCLog("recvW_PayRes fail");
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}

	for (int i = 0; i < res.limitshopinfo_size(); i++)
	{
		GameDataManager::getSingleton().setLimitShopInfo(res.limitshopinfo(i));
	}

	if (res.has_playerinfo()) {
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_PLAYER_INFO_RES);
	}
}
