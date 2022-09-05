#include "pch.h"
#include "LobbyMyHomeTap1.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "LobbyMyHomeMainPanel.h"
#include "AccountPopupPanel.h"
#include "SelectCharacterPanel.h"
#include "CustomPopupPanel.h"
#include "PokerRankHelper.h"
#include "FriendHelper.h"

LobbyMyHomeTap1::LobbyMyHomeTap1()
{
	mLoginProcess = false;

	m_pReplayListView = nullptr;
	m_pReplayListContainer = nullptr;
	m_pNextLevelInfoPanel = nullptr;
	mLimitedInfoPanel = nullptr;
	m_pMainUiPanel = nullptr;

	InitPanel();
	InitImage();
	initButton();

	
	setButtonListener(this);
	
	SetUserInfo();
	SetMyCharacter();
	SetLevelExp();
	SetMyMoney();

	m_ViewDataIndex = 10;
}

LobbyMyHomeTap1::~LobbyMyHomeTap1()
{
	//destruct();
}

void LobbyMyHomeTap1::InitPanel()
{
	construct(getMxmlPath() + "dmy_basicsinfo.mxml");

	mRubyPlusIcon = getImage("skel_mark_rubyp");
	m_pMyPhoto = getImage("dmy_photo");
	CCSize _contentSize = getDummy("dmy_basicsinfo").size;
	m_pNextLevelInfoPanel = new Panel();
	m_pNextLevelInfoPanel->construct(getMxmlPath() + "dmy_up_panel.mxml");
	m_pNextLevelInfoPanel->getLabel("txt_bank_guide")->setVisible(false);
	m_pNextLevelInfoPanel->getLabel("txt_bank_guide")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pNextLevelInfoPanel->getLabel("txt_level_gift")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pNextLevelInfoPanel->getLabel("txt_level_next")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pNextLevelInfoPanel->getImage("skel_backcolor")->setVisible(false);
	m_pNextLevelInfoPanel->getSkel("skel_up_panel")->playAnimation("up_panel_start");
	m_pNextLevelInfoPanel->getSkel("skel_up_panel")->appendAnimation("up_panel_stay");
	
	CCPoint pos = getDummy("dmy_up_panel").origin;	
	m_pNextLevelInfoPanel->setPositionX(pos.x);
	m_pNextLevelInfoPanel->setPositionY(-pos.y);
	addChild(m_pNextLevelInfoPanel,1);
	m_pNextLevelInfoPanel->release();
	m_pNextLevelInfoPanel->setVisible(false);


	mLimitedInfoPanel = new Panel();
	mLimitedInfoPanel->construct(getMxmlPath() + "dmy_up_panel.mxml");
	mLimitedInfoPanel->getLabel("txt_level_gift")->setVisible(false);
	mLimitedInfoPanel->getLabel("txt_bank_guide")->setVisible(false);
	mLimitedInfoPanel->getImage("skel_backcolor")->setVisible(false);
	mLimitedInfoPanel->getSkel("skel_up_panel")->playAnimation("up_panel2_start");
	mLimitedInfoPanel->getSkel("skel_up_panel")->appendAnimation("up_panel2_stay");

	CCPoint pos2 = getDummy("dmy_up_panel2").origin;
	mLimitedInfoPanel->setPositionX(pos2.x);
	mLimitedInfoPanel->setPositionY(-pos2.y);
	addChild(mLimitedInfoPanel, 1);
	mLimitedInfoPanel->release();
	mLimitedInfoPanel->setVisible(false);

	CCPoint _btnPos[3];
	_btnPos[0] = getDummy("dmy_button_small1").origin;
	_btnPos[1] = getDummy("dmy_button_lsmall").origin;
	_btnPos[2] = getDummy("dmy_button_small2").origin;

	m_pButtonPanel[0] = new Panel();
	m_pButtonPanel[0]->construct(getMxmlPath() + "dmy_button_small.mxml");

	m_pButtonPanel[1] = new Panel();
	m_pButtonPanel[1]->construct(getMxmlPath() + "dmy_button_lsmall.mxml");
	
	m_pButtonPanel[2] = new Panel();
	m_pButtonPanel[2]->construct(getMxmlPath() + "dmy_button_small.mxml");

	for (int _i = 0; _i < 3; _i++)
	{
		_btnPos[_i].y = -_btnPos[_i].y;
		m_pButtonPanel[_i]->setPosition(_btnPos[_i]);
		addChild(m_pButtonPanel[_i]);
		m_pButtonPanel[_i]->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pButtonPanel[_i]->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pButtonPanel[_i]->release();
	}


	mUserInfoTitle = getLabel("txt_title_userinfo");		//유저정보
	mUserInfoTitleUnder = getLabel("txt_title_userinfo_under");	//유저정보
	mNickNameTitle = getLabel("txt_usernickname");		//닉네임:
	mMyGoodsTitle = getLabel("txt_possession_money");		//소지재화 
	mMyGoodsTitleUnder = getLabel("txt_possession_money_under");	//소지재화 
	mMyGoodsGoldTitle = getLabel("txt_now_gold");	//소지골드
	mMyGoodsBankTitle = getLabel("txt_bank");	//금고골드
	mInsuranceTitle = getLabel("txt_insurance");		//보험금
	mRefilTitle = getLabel("txt_refill");			//리필정보
	mMebershipTitle = getLabel("txt_member_refill");		//맴버쉽 리필

	mUserInfoTitle->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoTitle").c_str());
	mUserInfoTitleUnder->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoTitle").c_str());
	mNickNameTitle->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoNickname").c_str());
	mMyGoodsTitle->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoMyGoods").c_str());
	mMyGoodsTitleUnder->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoMyGoods").c_str());
	mMyGoodsGoldTitle->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoMyGold").c_str());
	mMyGoodsBankTitle->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoBank").c_str());
	mInsuranceTitle->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoInsurence").c_str());
	mRefilTitle->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoRefil").c_str());
	mMebershipTitle->setString(GameStringDepot::getSingleton().getString("MyHomeUserInfoMebership").c_str());

}

void LobbyMyHomeTap1::InitImage()
{
	m_pUserInfo = getLabel("txt_title_userinfo");
	m_pGoldInfo = getLabel("txt_possession_money_");
	m_pNickName = getLabel("txt_usernickname");
	m_pAcount = getLabel("txt_userid");
	m_pLevel = getLabel("txt_box_userlevel");
	m_pLevelupLeft = getLabel("txt_levelguide");
	m_pLevelExp = getLabel("txt_exppercent");
	m_pMyGold = getLabel("txt_total_goldsum");
	m_pMaxMyGold = getLabel("txt_goldlimit");
	m_pMyChip = getLabel("txt_total_chipsum");
	m_pMaxMyChip = getLabel("txt_chiplimit");
	m_pMyGameMoneyLabel = getLabel("txt_now_gold");
	m_pMyGameMoney = getLabel("txt_now_goldsum");
	m_pMyGameMoney->setGrayColor(StringConverter::parseColor3B("f73030"));
	m_pMyBankMoneyLabel = getLabel("txt_bank");
	m_pMyBankMoney = getLabel("txt_banksum");
	m_pInsuranceLabel = getLabel("txt_insurance");
	m_pInsurance = getLabel("txt_insurancesum");
	m_pLoseMoneyLabel = getLabel("txt_losegold");
	m_pLoseMoney = getLabel("txt_losegoldsum");
	m_pMaxLoseMoney = getLabel("txt_daygoldlimit");
	m_pRefillCount = getLabel("txt_refillsum");
	m_pRefillCountLabel = getLabel("txt_refill");
	m_pRubyPlus = getLabel("txt_rubbyplus");
	m_pTotalRuby = getLabel("txt_total_rubbysum");
	mMemberShipRefillLabel = getLabel("txt_member_refillsum");

	m_pLoseMoneyLabel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_TODAY_GETGOLD").c_str());

	m_pButtonPanel[0]->getLabel("txt_button_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_RENAME_UNIT").c_str());
	m_pButtonPanel[0]->getLabel("txt_button")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_RENAME_UNIT").c_str());

	m_pButtonPanel[1]->getLabel("txt_button_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_NEXTLEVEL_BONUS_UNIT").c_str());
	m_pButtonPanel[1]->getLabel("txt_button")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_NEXTLEVEL_BONUS_UNIT").c_str());

	m_pButtonPanel[2]->getLabel("txt_button_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BUY_UNIT").c_str());
	m_pButtonPanel[2]->getLabel("txt_button")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_BUY_UNIT").c_str());
	
}


void LobbyMyHomeTap1::initButton()
{
	m_CharaterInfoBtn = getButton("sbtn_exclamation");
	m_CharaterInfoBtn->setType(Button::NoPressImg);
	m_CharaterInfoBtn->setPaused(true);
	m_CharaterInfoBtn->setListener(this);

	m_EditNickNameBtn = m_pButtonPanel[0]->getButton("sbtn_button");
	//m_EditNickNameBtn = getButton("sbtn_edit_button");
	m_EditNickNameBtn->setName("sbtn_edit_button");
	m_EditNickNameBtn->setType(Button::NoPressImg);
	m_EditNickNameBtn->setPaused(true);
	m_EditNickNameBtn->setListener(this);

	m_NextLevelInfoBtn = m_pButtonPanel[1]->getButton("sbtn_button");
	//m_NextLevelInfoBtn = getButton("sbtn_clip_back_yellow2");
	m_NextLevelInfoBtn->setName("sbtn_clip_back_yellow2");
	m_NextLevelInfoBtn->setType(Button::NoPressImg);
	m_NextLevelInfoBtn->setPaused(true);

	//m_GotoCharacterShopBtn = getButton("sbtn_small_button_4_stay");
	//m_GotoCharacterShopBtn->setType(Button::NoPressImg);
	//m_GotoCharacterShopBtn->getButtonSkelObject()->setSkin("txt_buy");
	//m_GotoCharacterShopBtn->setPaused(true);

	//m_SelectCharacterBtn = getButton("sbtn_small_button_1_stay");
	//m_SelectCharacterBtn->setType(Button::NoPressImg);
	//m_SelectCharacterBtn->getButtonSkelObject()->setSkin("txt_storage_tray");
	//m_SelectCharacterBtn->setPaused(true);

	//m_ShowLoseMoneyInfoBtn = getButton("sbtn_exclamation_mark_stay2");
	//m_ShowLoseMoneyInfoBtn->setType(Button::NoPressImg);
	//m_ShowLoseMoneyInfoBtn->setPaused(true);

	m_GotoRubyShopBtn = m_pButtonPanel[2]->getButton("sbtn_button");
	//m_GotoRubyShopBtn = getButton("sbtn_small_button_4_stay2");
	m_GotoRubyShopBtn->setName("sbtn_small_button_4_stay2");
	m_GotoRubyShopBtn->setType(Button::NoPressImg);
	m_GotoRubyShopBtn->getButtonSkelObject()->setSkin("txt_buy");
	m_GotoRubyShopBtn->setPaused(true);
}


void LobbyMyHomeTap1::SetUserInfo()
{
	if (m_pNextLevelInfoPanel == nullptr)
		return;

	PlayerData* _playerInfo = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();
	
	string nickStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_NickStr"), _playerInfo->m_NickName);
	string uidStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_UidStr"),StringConverter::toString(_playerInfo->GetUID()));
	m_pNickName->setString(nickStr.c_str());
	m_pAcount->setString(uidStr.c_str());
	InitMyPhoto(true);
}

void LobbyMyHomeTap1::InitMyPhoto(bool isTryDownload)
{
	bool _ret;

	m_pMyPhoto->setSpriteFrameWithFile(FriendHelper::getDefaultImg());
	if (GameDataManager::getSingletonPtr()->m_FacebookUserId != "")
	{
		_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
			GameDataManager::getSingletonPtr()->m_FacebookUserId,
			GameDataManager::getSingletonPtr()->m_FacebookUserPhotoUrl,
			DOWNLOAD_FILE_TYPE::MYROOM_PHOTO,
			m_pMyPhoto,
			isTryDownload,
			STATIC_PHOTO_FOLDER
			);

		// 로딩되었으면 이미지를 교체한다.
		if (_ret)
		{
			CCRect rect = getDummy("dmy_photo");

			m_pMyPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
			m_pMyPhoto->setVisible(true);
		}
	}
	else if (GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_thumbnailUrl != "")
	{
		string userId = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName;
		string url = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_thumbnailUrl;
		_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
			userId,
			url,
			DOWNLOAD_FILE_TYPE::MYROOM_PHOTO,
			m_pMyPhoto,
			isTryDownload,
			STATIC_PHOTO_FOLDER
			);

		// 로딩되었으면 이미지를 교체한다.
		if (_ret)
		{
			CCRect rect = getDummy("dmy_photo");

			m_pMyPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
			m_pMyPhoto->setVisible(true);
		}
	}
	else
	{
		m_pMyPhoto->setSpriteFrameWithFile(FriendHelper::getMycharacterImg());		
	}
	CCRect rect = getDummy("dmy_photo");
	m_pMyPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
}

void LobbyMyHomeTap1::SetMyCharacter()
{
	PlayerData* _playerInfo = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();
	W_GameData* _gameData = GameDataManager::getSingletonPtr()->GetGameDataPtr();

	int _useCharacter = _playerInfo->m_CharacterIdx;
	int _dataSize = _gameData->characterdata_size();
	int _dataId = -1;
	for (int _i = 0; _i < _dataSize; _i++)
	{
		if (_gameData->characterdata(_i).has_id())
		{
			if (_gameData->characterdata(_i).id() == _useCharacter)
			{
				_dataId = _i;
				break;
			}
		}
	}	
}

void LobbyMyHomeTap1::SetMyMoney()
{
	int64 _GameMoney = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
	int64 _MaxGold = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyMax;

	string _sGameMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_GameMoney));
	string moneyStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_GoldStr"), _sGameMoney);
	m_pMyGameMoney->setString(moneyStr.c_str());
	if (_GameMoney >= _MaxGold) {
		m_pMyGameMoney->setGrayscale(true);
	}
	else {
		m_pMyGameMoney->setGrayscale(false);
	}


	int64 _BankMoney = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyBank;
	string _sBankMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_BankMoney));
	string bankStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_GoldStr"), _sBankMoney);
	m_pMyBankMoney->setString(bankStr.c_str());

	int64 _SafeMoney = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneySafe;
	string _insurance = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_SafeMoney));
	string insuranceStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_GoldStr"), _insurance);
	m_pInsurance->setString(insuranceStr.c_str());

	int64 _TotalGold = _GameMoney + _BankMoney;
	string _sTotalGold = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_TotalGold));	
	string totalStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_GoldStr"), _sTotalGold);
	m_pMyGold->setString(totalStr.c_str());

	string _sMaxGold = "(" + GameStringDepot::getSingleton().getString("TXT_LIMIT") + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_MaxGold)) + ")";
	m_pMaxMyGold->setString(_sMaxGold.c_str());

	int64 _Chip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	string chipStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_ChipStr"), _Chip);
	m_pMyChip->setString(chipStr.c_str());

	int64 _ChipMax = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_ChipMax;
	string _sClipMax = "(" + GameStringDepot::getSingleton().getString("TXT_LIMIT") + StringConverter::toString(_ChipMax) + GameStringDepot::getSingleton().getString("TXT_COUNT_THING") + ")";
	m_pMaxMyChip->setString(_sClipMax.c_str());	
}

void LobbyMyHomeTap1::SetLevelExp()
{
	int _level = PokerRankHelper::getLevel();
	string _sLevel = "Lv." + StringConverter::toString(_level);
	m_pLevel->setString(_sLevel.c_str());

	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata_size();
	int _idx = -1;
	for (int _i = 0; _i < _size; _i++)
	{
		if (_level + 1 == GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata(_i).id())
		{
			_idx = _i;
			break;
		}
	}

	if (_idx == -1)
	{
		if (m_NextLevelInfoBtn)
		{
			m_NextLevelInfoBtn->setEnable(false);
			m_NextLevelInfoBtn->setVisible(false);
			//m_pLevelNextInfoShadow->setVisible(false);
			//m_pLevelNextInfo->setVisible(false);
		}
	}

	int32 _exp = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Exp;
	int32 _accumExp = GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata(_level - 1).accumexp();
	int32 _needExp = GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata(_level - 1).needexp();

	int32 _leftExp = _accumExp - _exp;
	if (_leftExp < 0)
		_leftExp = 0;
	string _sLeftExp = NxGetFormatString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap1_EXP"), _leftExp);		
	m_pLevelupLeft->setString(_sLeftExp.c_str());

	//int _ExpPer = _leftExp * 100 / _needExp;
	int _ExpPer = (_needExp - _leftExp) * 100 / _needExp;
	if (_ExpPer >= 100)
		_ExpPer = 100;

	string _sExpPer = StringConverter::toString(_ExpPer) + " %";
	m_pLevelExp->setString(_sExpPer.c_str());

	float _width = getSkel("skel_gaugebar")->getBounding().size.width;
	float _startPos = 145.f;
	float _barWidth = getSkel("skel_gauge")->getBounding().size.width;
	float _scaleX = _width / _barWidth;

	getSkel("skel_gauge")->setPositionX(_startPos + (_width * ((float)_ExpPer / 200.f)));
	getSkel("skel_gauge")->setScaleX(_scaleX * ((float)_ExpPer/100.f));

	int64 _totalRuby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
	string _sTotalTuby = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_totalRuby), 1);
	string rubyStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_RubyStr"), _sTotalTuby);
	m_pTotalRuby->setString(rubyStr.c_str());
	
	if (!PokerRankHelper::hasRubyPlus()) {
		m_pRubyPlus->setVisible(false);
		mRubyPlusIcon->setVisible(false);
	}
	else {
		mRubyPlusIcon->setVisible(true);
		m_pRubyPlus->setVisible(true);		
		int rubyDay = PokerRankHelper::getRubyPlusDay();
		string _sRubyplus = GameStringDepot::getSingleton().getString("TXT_RUBY_PLUS_UNIT") + "( " + StringConverter::toString(rubyDay) + GameStringDepot::getSingleton().getString("TXT_DAY") + " " + GameStringDepot::getSingleton().getString("TXT_TIMELEFT") + " )";
		m_pRubyPlus->setString(_sRubyplus.c_str());
	}
	
	int64 _LoseMoney = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyLoss;
	_LoseMoney = -1 * _LoseMoney;
	string _sLoseMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_LoseMoney), 4) + GameStringDepot::getSingleton().getString("TXT_GOLD_UNIT");
	m_pLoseMoney->setString(_sLoseMoney.c_str());

	int64 _LoseMaxMoney = GameDataManager::getSingleton().GetGameDataPtr()->startassets().one_day_bet_gamemoney_loss_max();
	string _sLoseMaxMoney = "(" + GameStringDepot::getSingleton().getString("TXT_MAX_LOSEMONEY") + ":";
	_sLoseMaxMoney += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_LoseMaxMoney), 1);
	_sLoseMaxMoney += GameStringDepot::getSingleton().getString("TXT_GOLD_UNIT") + ")";
	m_pMaxLoseMoney->setString(_sLoseMaxMoney.c_str());
	
	
	//맵버쉬이 있다면 
	PlayerData * _playerData = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();	
	//vip
	int vipRefilCount = 0;
	int _vipLevel = PokerRankHelper::getVip();
	if (_vipLevel > 0) {
		int _DataSize = GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata_size();
		for (int _i = 0; _i < _DataSize; _i++)
		{
			W_VipData _vipData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata(_i);
			if (_vipLevel == _vipData.level())
			{
				int _size = _vipData.vipoption_size();
				for (int _index = 0; _index < _size; _index++)
				{
					if (_vipData.vipoption(_index).type() == W_VipData_eVipType_FreeRefillCount) {
						vipRefilCount = _vipData.vipoption(_index).amount();
					}

				}				
			}
		}
	}	
	//
	string refillDescStr = "";
	int nowCount = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_FreeRefillCount;
	int totalMaxCount = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().free_refill_daily_count() + vipRefilCount;
	int maxCount = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().free_refill_daily_count();
	int vipAmount = vipRefilCount;
	if (vipAmount == 0) {
		refillDescStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_FREE_REFILE"), nowCount, totalMaxCount , maxCount);
	}
	else {
		refillDescStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MyHomeBasicInfo_FREE_REFILE_VIP"), nowCount, totalMaxCount , maxCount, vipAmount);
	}
	
	//맴버쉽이 있다면
	if (_playerData->m_MonthlyClassID != 0) {
		
		string membershipStr = NxGetFormatString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap1_MemberShipDesc"), GameDataManager::getSingleton().getPlayerInfo().monthlyclassfreerefillcnt());
		mMemberShipRefillLabel->setString(membershipStr.c_str());
	}
	else {
		mMemberShipRefillLabel->setString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap1_MemberShipBuyDesc").c_str());
	}
	m_pRefillCount->setString(refillDescStr.c_str());

}

Button* LobbyMyHomeTap1::GetColisionButton(CCTouch *pTouch, int _eventType)
{
	if (isVisible() == false)
	{
		return NULL;
	}

	if (m_EditNickNameBtn->hasCollided(m_EditNickNameBtn->convertToNodeSpace(pTouch->getLocation())))
	{
		switch (_eventType)
		{
		case TOUCH_EVENT_TYPE_BEGIN:
			m_EditNickNameBtn->setTag(1);
			break;
		case TOUCH_EVENT_TYPE_MOVE:
			if (m_EditNickNameBtn->getTag() == 1)
			{
				if (m_EditNickNameBtn->hasCollided(m_EditNickNameBtn->convertToNodeSpace(pTouch->getLocation())))
				{
					if (pTouch->getStartLocation().getDistance(pTouch->getLocation()) > 10.f)
					{
						m_EditNickNameBtn->setTag(0);
					}
				}
			}
			break;
		case TOUCH_EVENT_TYPE_END:
			if (m_EditNickNameBtn->getTag() == 1)
			{
				if (m_EditNickNameBtn->hasCollided(m_EditNickNameBtn->convertToNodeSpace(pTouch->getLocation())))
				{
					m_EditNickNameBtn->setTag(0);
					onClicked(m_EditNickNameBtn->getName());
				}
			}
			break;
		}

		return m_EditNickNameBtn;
	}
	else if (m_CharaterInfoBtn->hasCollided(m_CharaterInfoBtn->convertToNodeSpace(pTouch->getLocation())))
	{
		switch (_eventType)
		{
		case TOUCH_EVENT_TYPE_BEGIN:
			m_CharaterInfoBtn->setTag(1);
			break;
		case TOUCH_EVENT_TYPE_MOVE:
			if (m_CharaterInfoBtn->getTag() == 1)
			{
				if (m_CharaterInfoBtn->hasCollided(m_CharaterInfoBtn->convertToNodeSpace(pTouch->getLocation())))
				{
					if (pTouch->getStartLocation().getDistance(pTouch->getLocation()) > 10.f)
					{
						m_CharaterInfoBtn->setTag(0);
					}
				}
			}
			break;
		case TOUCH_EVENT_TYPE_END:
			if (m_CharaterInfoBtn->getTag() == 1)
			{
				if (m_CharaterInfoBtn->hasCollided(m_CharaterInfoBtn->convertToNodeSpace(pTouch->getLocation())))
				{
					m_CharaterInfoBtn->setTag(0);
					onClicked(m_CharaterInfoBtn->getName());
				}
			}
			break;
		}

		return m_CharaterInfoBtn;
	}
	else if (m_NextLevelInfoBtn->hasCollided(m_NextLevelInfoBtn->convertToNodeSpace(pTouch->getLocation())))
	{
		if (m_NextLevelInfoBtn->isEnabled() == false)
			return nullptr;

		switch (_eventType)
		{
		case TOUCH_EVENT_TYPE_BEGIN:
			m_NextLevelInfoBtn->setTag(1);
			break;
		case TOUCH_EVENT_TYPE_MOVE:
			if (m_NextLevelInfoBtn->getTag() == 1)
			{
				if (m_NextLevelInfoBtn->hasCollided(m_NextLevelInfoBtn->convertToNodeSpace(pTouch->getLocation())))
				{
					if (pTouch->getStartLocation().getDistance(pTouch->getLocation()) > 10.f)
					{
						m_NextLevelInfoBtn->setTag(0);
					}
				}
			}
			break;
		case TOUCH_EVENT_TYPE_END:
			if (m_NextLevelInfoBtn->getTag() == 1)
			{
				if (m_NextLevelInfoBtn->hasCollided(m_NextLevelInfoBtn->convertToNodeSpace(pTouch->getLocation())))
				{
					m_NextLevelInfoBtn->setTag(0);
					onClicked(m_NextLevelInfoBtn->getName());
				}
			}
			break;
		}

		return m_NextLevelInfoBtn;
	}
	else if (m_GotoRubyShopBtn->hasCollided(m_GotoRubyShopBtn->convertToNodeSpace(pTouch->getLocation())))
	{
		switch (_eventType)
		{
		case TOUCH_EVENT_TYPE_BEGIN:
			m_GotoRubyShopBtn->setTag(1);
			break;
		case TOUCH_EVENT_TYPE_MOVE:
			if (m_GotoRubyShopBtn->getTag() == 1)
			{
				if (m_GotoRubyShopBtn->hasCollided(m_GotoRubyShopBtn->convertToNodeSpace(pTouch->getLocation())))
				{
					if (pTouch->getStartLocation().getDistance(pTouch->getLocation()) > 10.f)
					{
						m_GotoRubyShopBtn->setTag(0);
					}
				}
			}
			break;
		case TOUCH_EVENT_TYPE_END:
			if (m_GotoRubyShopBtn->getTag() == 1)
			{
				if (m_GotoRubyShopBtn->hasCollided(m_GotoRubyShopBtn->convertToNodeSpace(pTouch->getLocation())))
				{
					m_GotoRubyShopBtn->setTag(0);
					onClicked(m_GotoRubyShopBtn->getName());
				}
			}
			break;
		}

		return m_GotoRubyShopBtn;
	}

	return NULL;

	//else if (m_GotoCharacterShopBtn->hasCollided(m_GotoCharacterShopBtn->convertToNodeSpace(pTouch->getLocation())))
	//{
	//	switch (_eventType)
	//	{
	//	case TOUCH_EVENT_TYPE_BEGIN:
	//		m_GotoCharacterShopBtn->setTag(1);
	//		break;
	//	case TOUCH_EVENT_TYPE_MOVE:
	//		if (m_GotoCharacterShopBtn->getTag() == 1)
	//		{
	//			if (m_GotoCharacterShopBtn->hasCollided(m_GotoCharacterShopBtn->convertToNodeSpace(pTouch->getLocation())))
	//			{
	//				if (pTouch->getStartLocation().getDistance(pTouch->getLocation()) > 10.f)
	//				{
	//					m_GotoCharacterShopBtn->setTag(0);
	//				}
	//			}
	//		}
	//		break;
	//	case TOUCH_EVENT_TYPE_END:
	//		if (m_GotoCharacterShopBtn->getTag() == 1)
	//		{
	//			if (m_GotoCharacterShopBtn->hasCollided(m_GotoCharacterShopBtn->convertToNodeSpace(pTouch->getLocation())))
	//			{
	//				m_GotoCharacterShopBtn->setTag(0);
	//				onClicked(m_GotoCharacterShopBtn->getName());
	//			}
	//		}
	//		break;
	//	}

	//	return m_GotoCharacterShopBtn;
	//}
	//else if (m_SelectCharacterBtn->hasCollided(m_SelectCharacterBtn->convertToNodeSpace(pTouch->getLocation())))
	//{
	//	switch (_eventType)
	//	{
	//	case TOUCH_EVENT_TYPE_BEGIN:
	//		m_SelectCharacterBtn->setTag(1);
	//		m_SelectCharacterBtn->getButtonSkelObject()->playAnimation("small_button_1_off_stay");
	//		break;
	//	case TOUCH_EVENT_TYPE_MOVE:
	//		if (m_SelectCharacterBtn->getTag() == 1)
	//		{
	//			if (m_SelectCharacterBtn->hasCollided(m_SelectCharacterBtn->convertToNodeSpace(pTouch->getLocation())))
	//			{
	//				if (pTouch->getStartLocation().getDistance(pTouch->getLocation()) > 10.f)
	//				{
	//					m_SelectCharacterBtn->setTag(0);
	//					m_SelectCharacterBtn->getButtonSkelObject()->playAnimation("small_button_1_off_change");
	//					m_SelectCharacterBtn->getButtonSkelObject()->appendAnimation("small_button_1_stay");
	//				}
	//			}
	//		}
	//		break;
	//	case TOUCH_EVENT_TYPE_END:
	//		if (m_SelectCharacterBtn->getTag() == 1)
	//		{
	//			if (m_SelectCharacterBtn->hasCollided(m_SelectCharacterBtn->convertToNodeSpace(pTouch->getLocation())))
	//			{
	//				m_SelectCharacterBtn->setTag(0);
	//				m_SelectCharacterBtn->getButtonSkelObject()->playAnimation("small_button_1_off_change");
	//				m_SelectCharacterBtn->getButtonSkelObject()->appendAnimation("small_button_1_stay");
	//				onClicked(m_SelectCharacterBtn->getName());
	//			}
	//		}
	//		break;
	//	}

	//	return m_SelectCharacterBtn;
	//}
	//else if (m_ShowLoseMoneyInfoBtn->hasCollided(m_ShowLoseMoneyInfoBtn->convertToNodeSpace(pTouch->getLocation())))
	//{
	//	switch (_eventType)
	//	{
	//	case TOUCH_EVENT_TYPE_BEGIN:
	//		m_ShowLoseMoneyInfoBtn->setTag(1);
	//		break;
	//	case TOUCH_EVENT_TYPE_MOVE:
	//		if (m_ShowLoseMoneyInfoBtn->getTag() == 1)
	//		{
	//			if (m_ShowLoseMoneyInfoBtn->hasCollided(m_ShowLoseMoneyInfoBtn->convertToNodeSpace(pTouch->getLocation())))
	//			{
	//				if (pTouch->getStartLocation().getDistance(pTouch->getLocation()) > 10.f)
	//				{
	//					m_ShowLoseMoneyInfoBtn->setTag(0);
	//				}
	//			}
	//		}
	//		break;
	//	case TOUCH_EVENT_TYPE_END:
	//		if (m_ShowLoseMoneyInfoBtn->getTag() == 1)
	//		{
	//			if (m_ShowLoseMoneyInfoBtn->hasCollided(m_ShowLoseMoneyInfoBtn->convertToNodeSpace(pTouch->getLocation())))
	//			{
	//				m_ShowLoseMoneyInfoBtn->setTag(0);
	//				onClicked(m_ShowLoseMoneyInfoBtn->getName());
	//			}
	//		}
	//		break;
	//	}

	//	return m_ShowLoseMoneyInfoBtn;
	//}

}

bool LobbyMyHomeTap1::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_pNextLevelInfoPanel->isVisible() == true)
		ShowNextLevelInfo(false);

	if (mLimitedInfoPanel->isVisible() == true)
		showLimitedInfo(false);

	Button* _touchBtn = GetColisionButton(pTouch, TOUCH_EVENT_TYPE_BEGIN);
	if (_touchBtn)
	{
		return true;
	}

	return false;
}

void LobbyMyHomeTap1::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	GetColisionButton(pTouch, TOUCH_EVENT_TYPE_MOVE);
}


void LobbyMyHomeTap1::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	GetColisionButton(pTouch, TOUCH_EVENT_TYPE_END);
}

void LobbyMyHomeTap1::resume()
{
}

void LobbyMyHomeTap1::onClicked(const string& name)
{
	if (mLoginProcess)
		return;


	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (name == "sbtn_exclamation_mark_stay")
	{
		LayerManager::getSingleton().pushDynamicLayer(new CustomPopupPanel(CustomPopupPanel::CustomPopupType::CHAR_INFO_TYPE, GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx), DYNAMIC_PUSH_LAYER);
		return;
	}
	else if (name == "sbtn_edit_button")
	{
		new AccountPopupPanel(AccountPopupPanel::AccountPopupType::NICKNAME_REPAIR_TYPE);
	}
	else if (name == "sbtn_clip_back_yellow2")
	{
		ShowNextLevelInfo(true);
	}
	else if (name == "sbtn_small_button_4_stay")
	{
		dynamic_cast<LobbyMyHomeMainPanel*>(m_pMainUiPanel)->onClicked("TAP1_GOTO_SHOP_CHARACTER");
	}
	else if (name == "sbtn_small_button_4_stay2")
	{
		dynamic_cast<LobbyMyHomeMainPanel*>(m_pMainUiPanel)->onClicked("TAP1_GOTO_SHOP_RUBY");
	}
	else if (name == "sbtn_small_button_1_stay")
	{
		ShowCharacterSelectPanel();
	}
	else if (name == "sbtn_exclamation") {
		showLimitedInfo(true);
	}

}

void LobbyMyHomeTap1::update(float dt)
{
}

bool LobbyMyHomeTap1::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK>(&stCmd))
	{
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK res = *pstIt;

		if (res.param != MYROOM_PHOTO)
			return false;

		if (!res.imagePath.empty())
		{
			InitMyPhoto(false);
		}
		return true;
	}

	return false;
}


void LobbyMyHomeTap1::ShowNextLevelInfo(bool _show)
{
	if (m_pNextLevelInfoPanel)
		m_pNextLevelInfoPanel->setVisible(_show);

	if (_show == false)
		return;

	m_pNextLevelInfoPanel->getSkel("skel_up_panel")->playAnimation("up_panel_start");
	m_pNextLevelInfoPanel->getSkel("skel_up_panel")->appendAnimation("up_panel_stay");


	int _level = PokerRankHelper::getLevel();
	
	//Level
	CCSequence* _pAction1 = CCSequence::create(CCDelayTime::create(0.2f),CCFadeIn::create(0.1f),NULL);
	m_pNextLevelInfoPanel->getLabel("txt_level_next")->setOpacity(0);
	string _sNextLevel = NxGetFormatString(GameStringDepot::getSingletonPtr()->getString("TXT_NEXT_LEVEL_UNIT"),_level + 1);
	m_pNextLevelInfoPanel->getLabel("txt_level_next")->setString(_sNextLevel.c_str());
	m_pNextLevelInfoPanel->getLabel("txt_level_next")->runAction(_pAction1);
	//Effect
	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata_size();

	int _idx = -1;
	for (int _i = 0; _i < _size; _i++)
	{
		if (_level+1 == GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata(_i).id())
		{
			_idx = _i;
			break;
		}
	}

	if (_idx == -1)
		return;

	W_RewardInfo _info = GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata(_idx).rewardinfo();
	int _infoSize = _info.rewardset_size();
	string _sNextLevelGift = GameStringDepot::getSingletonPtr()->getString("TXT_NEXT_LEVEL_EFFECT");
	for (int _i = 0; _i < _infoSize; _i++)
	{
		W_RewardInfo_RewardSet _rewardSet = _info.rewardset(_i);
		if (_rewardSet.has_type() && _rewardSet.has_amount())
		{
			_sNextLevelGift += " " + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_rewardSet.amount()), 1);

			if (_rewardSet.has_type())
			{
				switch (_rewardSet.type())
				{
				case CASH:
					_sNextLevelGift += GameStringDepot::getSingleton().getString("TXT_GET_CASH");// U8(" CASH지급");
					break;
				case GAMEMONEY:
					_sNextLevelGift += GameStringDepot::getSingleton().getString("TXT_GET_GOLD");//U8(" GOLD지급");
					break;
				case CHIP:
					_sNextLevelGift += GameStringDepot::getSingleton().getString("TXT_GET_CHIP");// U8(" CHIP지급");
					break;
				case CHARACTER:
					continue;
					break;
				}
			}

			if (_i != _infoSize - 1)
			{
				_sNextLevelGift += "\n";
			}
		}
	}

	CCSequence* _pAction2 = CCSequence::create(CCDelayTime::create(0.2f), CCFadeIn::create(0.1f), NULL);
	m_pNextLevelInfoPanel->getLabel("txt_level_gift")->setOpacity(0);
	m_pNextLevelInfoPanel->getLabel("txt_level_gift")->setString(_sNextLevelGift.c_str());
	m_pNextLevelInfoPanel->getLabel("txt_level_gift")->runAction(_pAction2);

}

void LobbyMyHomeTap1::ShowCharacterSelectPanel()
{
	//new SelectCharacterPanel();
}

void LobbyMyHomeTap1::showLimitedInfo(bool _show)
{
	if (mLimitedInfoPanel)
		mLimitedInfoPanel->setVisible(_show);

	if (_show == false)
		return;

	mLimitedInfoPanel->getSkel("skel_up_panel")->playAnimation("up_panel2_start");
	mLimitedInfoPanel->getSkel("skel_up_panel")->appendAnimation("up_panel2_stay");

	CCSequence* _pAction2 = CCSequence::create(CCDelayTime::create(0.2f), CCFadeIn::create(0.1f), NULL);
	mLimitedInfoPanel->getLabel("txt_level_next")->setOpacity(0);
	mLimitedInfoPanel->getLabel("txt_level_next")->setString(GameStringDepot::getSingleton().getString("MYHOME_DAILY_LIMITED_DESC").c_str());
	mLimitedInfoPanel->getLabel("txt_level_next")->runAction(_pAction2);
}

void LobbyMyHomeTap1::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}