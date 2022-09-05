#include "pch.h"
#include "GoodsPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "PokerResourceHelper.h"

GoodsPanel::GoodsPanel()
{
	InitPanel();
	InitImage();
	initButton();
	SetGoodsType(TYPE_NO_RUBY_GOODS);
	setButtonListener(this);
}

GoodsPanel::~GoodsPanel()
{
	//destruct();
}

void GoodsPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_goods_panel.mxml");	
}

void GoodsPanel::InitImage()
{
	m_Spec = getLabel("txt_spec");
	
	mCenteTitle = getLabel("txt_gold_goods_center");	
	mCenterPos = mCenteTitle->getPosition();
	mTopPos = getImage("dmy_gold_goods_top")->getPosition();
	mBottomPos = getImage("dmy_gold_goods_bottom")->getPosition(); 
	mTopPos.x = mCenterPos.x;
	mBottomPos.x = mCenterPos.x;

	m_DayLimit = getLabel("txt_limit");
	m_Name = getLabel("txt_character_name");
	m_DiscountUnder = getLabel("txt_label_shadow");
	m_Discount = getLabel("txt_label");

	m_GoodsPanel = getSkel("skel_goods_penal_1_stay");
	m_Cover = getSkel("skel_cover");
	m_HotMark = getSkel("skel_label_red2");
	mDisCount = getSkel("skel_label_red");
	mCharacter = getImage("img_character_boxer");
	
	mCoverImg = getImage("skel_line_choose");
	mCoverImg->setVisible(false);

	getImage("skel_cover_gold")->setVisible(false);
	getImage("skel_bonus")->setVisible(false);
	getLabel("txt_bonus")->setVisible(false);
}

void GoodsPanel::initButton()
{
	CCPoint _btnPos = getDummy("dmy_button_shop").origin;
	m_ButtonPanel = new Panel();
	m_ButtonPanel->construct(getMxmlPath() + "dmy_button_shop.mxml");
	m_ButtonPanel->setPositionX(_btnPos.x);
	m_ButtonPanel->setPositionY(-_btnPos.y);
	addChild(m_ButtonPanel);
	m_ButtonPanel->release();

	m_ButtonPanel->getLabel("txt_price2_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_ButtonPanel->getLabel("txt_price2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_ButtonPanel->getLabel("txt_price1_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_ButtonPanel->getLabel("txt_price1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	
	m_OkBtn = m_ButtonPanel->getButton("sbtn_button");
	m_OkBtn->setPaused(true); 
	mButtons.push_back(m_OkBtn);	
}

void GoodsPanel::onClicked(const string& name)
{
	if (name == m_OkBtn->getName()) {
		fireMessage(BUY_BTN_SEND_MSG + StringConverter::toString(mIdx));
	}	
}

void GoodsPanel::SetGoodsType(GoodsPanelType _type)
{
	m_panelType = _type;

	switch (_type)
	{
	case TYPE_NO_RUBY_GOODS:
		m_ButtonPanel->getSkel("skel_icon")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price1_under")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price1")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price2_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2")->setVisible(false);
		m_Discount->setVisible(false);
		m_DiscountUnder->setVisible(false);
		m_HotMark->setVisible(false);		
		mDisCount->setVisible(false);
		break;
	case TYPE_RUBY_GOODS:
		m_ButtonPanel->getSkel("skel_icon")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price1_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price1")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2_under")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price2")->setVisible(true);
		m_Discount->setVisible(false);
		m_DiscountUnder->setVisible(false);
		m_HotMark->setVisible(false);
		mDisCount->setVisible(false);
		break;
	}
}

void GoodsPanel::SetBtnText(string _text)
{
	switch (m_panelType)
	{
	case TYPE_NO_RUBY_GOODS:
		m_ButtonPanel->getLabel("txt_price1_under")->setString(_text.c_str());
		m_ButtonPanel->getLabel("txt_price1")->setString(_text.c_str());
		break;
	case TYPE_RUBY_GOODS:
		m_ButtonPanel->getLabel("txt_price1_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price1")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2")->setVisible(false);
		if (isCharacterMoneyType()) {
			m_ButtonPanel->getSkel("skel_icon")->setVisible(false);
			m_ButtonPanel->getLabel("txt_price1_under")->setString(_text.c_str());
			m_ButtonPanel->getLabel("txt_price1")->setString(_text.c_str());
			m_ButtonPanel->getLabel("txt_price1_under")->setVisible(true);
			m_ButtonPanel->getLabel("txt_price1")->setVisible(true);
		}
		else {
			m_ButtonPanel->getSkel("skel_icon")->setVisible(true);
			m_ButtonPanel->getLabel("txt_price2_under")->setString(_text.c_str());
			m_ButtonPanel->getLabel("txt_price2")->setString(_text.c_str());
			m_ButtonPanel->getLabel("txt_price2_under")->setVisible(true);
			m_ButtonPanel->getLabel("txt_price2")->setVisible(true);
		}
		
		break;
	}
}

void GoodsPanel::setIndex(int idx)
{
	mIdx = idx;
	mCenteTitle->setVisible(false);
	int _CharacterId = -1;
	int _day = 0;
	string _sLimitDay = "";

	m_ButtonPanel->getLabel("txt_price1")->setColor(StringConverter::parseColor3B("ffffff"));

	if (m_panelType == TYPE_NO_RUBY_GOODS){
		W_CharacterInfo* characterInfo = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[idx];
		_CharacterId = characterInfo->id();
		mCoverImg->setVisible(false);
		if (characterInfo->isbase())
		{
			_sLimitDay = GameStringDepot::getSingletonPtr()->getString("TXT_UNLIMIT");
		}
		else
		{
			_sLimitDay = GameDataManager::getSingletonPtr()->GetTimeString(characterInfo->expirelefttime()) + GameStringDepot::getSingletonPtr()->getString("TXT_TIMELEFT");
		}
		m_OkBtn->setSkelAnimation("button_shop_on");

		string _btnTxt = "";
		if (GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx == _CharacterId)
		{
			_btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_SELECTED_UNIT");
			m_OkBtn->setEnable(false);
			m_OkBtn->setSkelAnimation("button_shop_use");
			mCoverImg->setVisible(true);			
			m_ButtonPanel->getLabel("txt_price1")->setColor(StringConverter::parseColor3B("ffd042"));
		}
		else
		{
			W_CharacterInfo* _pInfo = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[idx];
			if (_pInfo->expirelefttime() == 0 && _pInfo->isbase() == false)
			{
				_btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CHARACTER_BUY_UNIT");
			}
			else
			{
				_btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CHANGEING_UNIT");
			}
			m_OkBtn->setEnable(true);
			m_OkBtn->setGrayscale(false);
		}
		SetBtnText(_btnTxt.c_str());
		const W_CharacterData* characterData = GameDataManager::getSingleton().getCharacterData(_CharacterId);
		m_Name->setString(characterData->name().c_str());
	}
	else if (m_panelType == TYPE_RUBY_GOODS) {
		//index 를 가지고 글 표시
		W_CharacterShopData _ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(idx);
		if (_ShopInfo.has_characterid())
			_CharacterId = _ShopInfo.characterid();

		m_HotMark->setVisible(false);
		mDisCount->setVisible(false);
		m_Discount->setVisible(false);
		m_DiscountUnder->setVisible(false);

		if (_ShopInfo.bandtype() == eBandNew) {
			m_HotMark->setVisible(true);
			m_HotMark->playAnimation("label_yellow");
		}
		else if (_ShopInfo.bandtype() == eBandHot) {
			m_HotMark->setVisible(true);
			m_HotMark->playAnimation("label_red");
		}
		string _rewardText = "";
		if (_ShopInfo.has_rewardinfo())
		{
			int _rewardSize = _ShopInfo.rewardinfo().rewardset_size();

			for (int _j = 0; _j < _rewardSize; _j++)
			{
				W_RewardInfo_RewardSet _set = _ShopInfo.rewardinfo().rewardset(_j);


				//if (_set.has_id());

				if (_set.has_amount())
				{
					_rewardText += GameStringDepot::getSingleton().getString("TXT_IMMEDIATELY");
					_rewardText += " " + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_set.amount()));
					_rewardText += " " + GameStringDepot::getSingleton().getString("TXT_GET_UNIT");
				}
			}
		}
		mCenteTitle->setString((_rewardText).c_str());
		_day = _ShopInfo.periodday();
		_sLimitDay = GameStringDepot::getSingletonPtr()->getString("TXT_LIMITTIME") + ":" + StringConverter::toString(_day) + GameStringDepot::getSingletonPtr()->getString("TXT_DAY");
		
		if (isCharacterMoneyType()) {
			string txtPrice = StringConverter::toString(_ShopInfo.money()) + GameStringDepot::getSingleton().getString("TXT_COUNT_MONEY");
			SetBtnText(txtPrice.c_str());			
			m_Name->setColor(StringConverter::parseColor3B("E6FFD5"));
			m_DayLimit->setColor(StringConverter::parseColor3B("88E35C"));
			m_GoodsPanel->playAnimation("goods_penal_3_stay");
			m_Cover->playAnimation("table_shopcash");
		}
		else {
			SetBtnText(StringConverter::toString(_ShopInfo.cash()).c_str());
			m_Name->setString(_ShopInfo.name().c_str());
			m_Name->setColor(StringConverter::parseColor3B("FFF0D5"));
			m_DayLimit->setColor(StringConverter::parseColor3B("E28C48"));
			m_GoodsPanel->playAnimation("goods_penal_1_stay");
			m_Cover->playAnimation("table_shopcharac");
		}
		
		m_Name->setString(_ShopInfo.name().c_str());
	}

	const W_CharacterData* characterData = GameDataManager::getSingleton().getCharacterData(_CharacterId);

	//공통표시
	m_DayLimit->setString(_sLimitDay.c_str());
	string _sDesc = "";
	int _size = characterData->effect_size();
	int realEffectSize = 0;
	for (int _i = 0; _i < _size; _i++)
	{
		W_CharacterData_CharacterEffect _dataEff = characterData->effect(_i);
		if (_dataEff.type() != W_CharacterData_eEffectType_None) {
			if (realEffectSize != 0)
				_sDesc += "\n";
			// 승리시 문구 추가, 서버에서 보내주는 데이터인데 일단 클라에서 예외처리
			if (_dataEff.desc().find("Exp") == 0) 
				_sDesc += GameStringDepot::getSingleton().getString("TXT_CHAEACTOR_CARD_EFFECT_WIN") + " " + _dataEff.desc();
			else
				_sDesc += _dataEff.desc();			
			realEffectSize++;
		}
	}

	//캐릭터 상품일때만 뿌린다.
	if (m_panelType == TYPE_RUBY_GOODS) {
		if (realEffectSize == 2) {
			mCenteTitle->setVisible(true);
			mCenteTitle->setPosition(mCenterPos); 
		}
		else if (realEffectSize == 1) {
			mCenteTitle->setVisible(true);			
			mCenteTitle->setPosition(mTopPos);
		}
		else if (realEffectSize == 0) {
			mCenteTitle->setVisible(true);
			mCenteTitle->setPosition(mBottomPos);
		}
	}
	m_Spec->setString(_sDesc.c_str());
	
	//캐릭터 표시		
	
	if (m_panelType == TYPE_NO_RUBY_GOODS) {
		mCharacter->setSpriteFrameWithFile(PokerResourceHelper::getCharacterImgName(_CharacterId));
	}
	else {
		mCharacter->setSpriteFrameWithFile(PokerResourceHelper::getCharacterShopWithMoneyImgName(_CharacterId));
	}
}

void GoodsPanel::cellTouch(const CCPoint& touchPoint)
{
	for (Button* btn : mButtons)
	{
		if (btn->hasCollided(btn->convertToNodeSpace(touchPoint))){
			if (btn->isEnabled()){
				onClicked(btn->getName());
				CCDelayTime* delay = CCDelayTime::create(CELL_TOUCH_TIME * 2);
				CCActionInstant* func = CCCallFuncN::create(this, callfuncN_selector(GoodsPanel::_cellTouchEnd));
				btn->runAction(CCSequence::create(delay, func, nullptr));
				return;
			}
		}
	}
	fireMessage(INFO_BTN_SEND_MSG + StringConverter::toString(mIdx));	
}

void GoodsPanel::_cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}

bool GoodsPanel::isCharacterMoneyType()
{
	bool isMoneyType = false;
	if (m_panelType == TYPE_RUBY_GOODS){
		W_CharacterShopData _ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(mIdx);
		if (_ShopInfo.cash() == 0) {
			isMoneyType = true;
		}
	}
	return isMoneyType;
}
