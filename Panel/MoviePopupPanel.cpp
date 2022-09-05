#include "pch.h"
#include "MoviePopupPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "LobbyTopUiPanel.h"
#include "LobbyScene.h"
#include "SceneUtil.h"
#include "LobbyUIPanel.h"
#include "RewardWidget.h"
#include "PokerResourceHelper.h"
#include "PokerShopHelper.h"
#include "LobbyMissionPanel.h"
#include "RefillMoviePanel.h"

RewardPopupPanel::RewardPopupPanel(REWARD_POPUP_TYPE type)
{
	mRewardRuby = 0;
	mType = type;
	mRewardInfo = nullptr;
	initPanel();
	SoundManager::getSingleton().playEffect("result_star");
}

RewardPopupPanel::RewardPopupPanel(int rewardRuby, int rubyId)
{
	mRewardRuby = rewardRuby;
	mRubyId = rubyId;
	mType = SHOP_RUBY;
	mRewardInfo = nullptr;
	initPanel();
	SoundManager::getSingleton().playEffect("result_star");
}

RewardPopupPanel::~RewardPopupPanel()
{

}

void RewardPopupPanel::onClicked(const string& name)
{
	if (name == "CLOSE_BTN") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
		if (mRewardInfo) {
			if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
			{
				LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
				_pScene->m_LobbyUIPanel->m_pTopPanel->addRewardInfo(*mRewardInfo);
			}
		}

		if (mRewardRuby > 0) {
			if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
			{
				LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
				_pScene->m_LobbyUIPanel->m_pTopPanel->addRewardRuby(mRewardRuby);
			}
		}

		if (mType == EVENT_REWARD) {
			if (LayerManager::getSingleton().hasLayerType<LobbyMissionPanel>()){
				LobbyMissionPanel* lobbyMissionPanel = dynamic_cast<LobbyMissionPanel*>(LayerManager::getSingleton().getLayerType<LobbyMissionPanel>());
				if (lobbyMissionPanel) {
					lobbyMissionPanel->onCloseRewardPopupPanel();
				}
			}
		}
		else if (mType == POPUP_RESULT_OK) {
			if (LayerManager::getSingleton().hasLayerType<RefillMoviePanel>()){
				RefillMoviePanel* refillMoviePanel = dynamic_cast<RefillMoviePanel*>(LayerManager::getSingleton().getLayerType<RefillMoviePanel>());
				refillMoviePanel->addReward();
			}
		}

	}
}

void RewardPopupPanel::initPanel()
{
	addMouseBlockPanel(this, true);
	mTitle = nullptr;
	mTitleUnder = nullptr;
	mDesc = nullptr;
	mRewardBg = nullptr;
	mRewardIcon = nullptr;
	mRewardLabel = nullptr;
	mCharacterImg = nullptr;

	if (mType == POPUP_RESULT_OK) {
		construct(getMxmlPath() + "dmy_freerefill_check1.mxml");
		mTitle = getLabel("txt_title");
		mDesc = getLabel("txt_check");
		mTitleUnder = getLabel("txt_title_under");
		getSkel("skel_backlight")->playAnimation("light_get");
		mRewardIcon = getSkel("skel_image");		
	}
	else if (mType == POPUP_FULL) {
		construct(getMxmlPath() + "dmy_freerefill_check2.mxml");
		mTitle = getLabel("txt_title");
		mTitleUnder = getLabel("txt_title_under");
	}
	else if (mType == POPUP_DELAY) {
		construct(getMxmlPath() + "dmy_freerefill_check3.mxml");
		mTitle = getLabel("txt_title");
		mTitleUnder = getLabel("txt_title_under");
	}
	else if (mType == COMMON_REWARD) {
		construct(getMxmlPath() + "dmy_get_board.mxml");
		mRewardBg = getSkel("skel_deco");
		mTitle = getLabel("txt_title");
		mTitleUnder = getLabel("txt_title_under");
		mDesc = getLabel("txt_check");
		getSkel("skel_backlight")->playAnimation("light_get");
		mRewardIcon = getSkel("skel_image");
		mRewardLabel = getLabel("txt_item_name");
		mCharacterImg = getImage("dmy_photo_boxer_60p");
	}
	else if (mType == SHOP_RUBY) {
		construct(getMxmlPath() + "dmy_get_board.mxml");
		mRewardBg = getSkel("skel_deco");
		mTitle = getLabel("txt_title");
		mTitleUnder = getLabel("txt_title_under");
		mDesc = getLabel("txt_check");
		getSkel("skel_backlight")->playAnimation("light_get");
		mRewardIcon = getSkel("skel_image");
		mRewardLabel = getLabel("txt_item_name");
		mCharacterImg = getImage("dmy_photo_boxer_60p");
	}
	else if (mType == LETTER_REWARD) {
		construct(getMxmlPath() + "dmy_get_board.mxml");
		mRewardBg = getSkel("skel_deco");
		mTitle = getLabel("txt_title");
		mTitleUnder = getLabel("txt_title_under");
		mDesc = getLabel("txt_check");
		getSkel("skel_backlight")->playAnimation("light_get");
		mRewardIcon = getSkel("skel_image");
		mRewardLabel = getLabel("txt_item_name");
		mCharacterImg = getImage("dmy_photo_boxer_60p");
	}
	else if (mType == BIG_POT) {
		construct(getMxmlPath() + "dmy_get_board.mxml");
		mRewardBg = getSkel("skel_deco");
		mTitle = getLabel("txt_title");
		mTitleUnder = getLabel("txt_title_under");
		mDesc = getLabel("txt_check");
		getSkel("skel_backlight")->playAnimation("light_get");
		mRewardIcon = getSkel("skel_image");
		mRewardLabel = getLabel("txt_item_name");
		mCharacterImg = getImage("dmy_photo_boxer_60p");
	}
	else if (mType == EVENT_REWARD) {
		construct(getMxmlPath() + "dmy_get_board.mxml");
		mRewardBg = getSkel("skel_deco");
		mTitle = getLabel("txt_title");
		mTitleUnder = getLabel("txt_title_under");
		mDesc = getLabel("txt_check");
		getSkel("skel_backlight")->playAnimation("light_get");
		mRewardIcon = getSkel("skel_image");
		mRewardLabel = getLabel("txt_item_name");
		mCharacterImg = getImage("dmy_photo_boxer_60p");
	}

	CCPoint _btnPos = getDummy("dmy_button_small").origin;
	mCloseBtnPanel = new SmallButtonPanel(SmallButtonPanel::LOBBY_FRIEND_TYPE);
	mCloseBtnPanel->setPositionX(_btnPos.x);
	mCloseBtnPanel->setPositionY(-_btnPos.y);
	mCloseBtnPanel->SetButtonListener(this);
	addChild(mCloseBtnPanel);
	mCloseBtnPanel->release();	
	mCloseBtnPanel->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_OK_LABEL"));
	mCloseBtnPanel->m_Button->setName("CLOSE_BTN");
	initDesc();
}

void RewardPopupPanel::initDesc()
{
	if (mType == POPUP_RESULT_OK) {

		int nowPlay = GameDataManager::getSingleton().getPlayerInfo().freechargecnt();
		int64 amount = GameDataManager::getSingleton().GetGameDataPtr()->freechargedata(nowPlay).rewardset().amount();
		string rewardStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(amount));
		string attendStr = NxGetFormatString(GameStringDepot::getSingleton().getString("RefillPopupDesc_OK"), nowPlay + 1,  rewardStr);
		int fontSize = GameStringDepot::getSingleton().getStringSize("RefillPopupDesc_OK");
		Script* descScript = Script::create(attendStr, getDummy("dmy_info1").size, fontSize, kCCTextAlignmentLeft, "KBIZgo H");
		CCSize contentSize = descScript->getContentSize();
		int gapHeight = getFontGap("fonts/KBIZgo H.ttf", fontSize);
		descScript->setCenterPos(getImage("dmy_info1")->getPosition(), gapHeight);
		addChild(descScript);
		mDesc->setString(GameStringDepot::getSingleton().getString("RefillPopupDesc_DESC").c_str());

	}
	else if (mType == POPUP_FULL) {
		string attendStr = NxGetFormatString(GameStringDepot::getSingleton().getString("RefillPopupDesc_FULL"));
		int fontSize = GameStringDepot::getSingleton().getStringSize("RefillPopupDesc_FULL");
		Script* descScript = Script::create(attendStr, getDummy("dmy_info1").size, fontSize, kCCTextAlignmentLeft, "KBIZgo H");
		CCSize contentSize = descScript->getContentSize();
		int gapHeight = getFontGap("fonts/KBIZgo H.ttf", fontSize);
		descScript->setCenterPos(getImage("dmy_info1")->getPosition(), gapHeight);
		addChild(descScript);
	}
	else if (mType == POPUP_DELAY) {		
	}
	else if (mType == SHOP_RUBY) {
		initItemBox();
	}
	else if (mType == LETTER_REWARD) {
		initItemBox();
	}
	else if (mType == BIG_POT) {
		initItemBox();
	}
	else if (mType == EVENT_REWARD) {
		initItemBox();
	}
}


void RewardPopupPanel::setDesc(string title, string content)
{
	if (title.empty()) {
		mTitle->setString(GameStringDepot::getSingleton().getString("COMMON_REWARD_TITLE").c_str());
		if (mTitleUnder)
			mTitleUnder->setString(GameStringDepot::getSingleton().getString("COMMON_REWARD_TITLE").c_str());
	}
	else {
		mTitle->setString(title.c_str());
		if (mTitleUnder)
			mTitleUnder->setString(title.c_str());
	}
	mDesc->setString(content.c_str());
}

void RewardPopupPanel::setRewardInfo(W_RewardInfo rewardInfo)
{
	if (mRewardInfo == nullptr)
		mRewardInfo = new W_RewardInfo(rewardInfo);
}

void RewardPopupPanel::initItemBox()
{
	
}

void RewardPopupPanel::setRubyReward(int rewardRuby, int rubyId)
{
	if (mRewardBg)
		mRewardBg->playAnimation("check_ruby");

	if (mRewardIcon)
		mRewardIcon->playAnimation(PokerResourceHelper::getBigRubyIcon());

	if (mCharacterImg)
		mCharacterImg->setVisible(false);

	//루비 상점 보상
	mTitle->setString(GameStringDepot::getSingleton().getString("RUBY_SHOP_TITLE").c_str());
	mTitleUnder->setString(GameStringDepot::getSingleton().getString("RUBY_SHOP_TITLE").c_str());
	//받은 아이템 이름
	string itemNameStr = "";
	bool isMoneyRuby = false;
	for (int i = 0; i < GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata_size(); i++)
	{
		if (GameDataManager::getSingleton().GetGameDataPtr()->cashshopdata(i).id() == rubyId) {
			itemNameStr = GameDataManager::getSingleton().GetGameDataPtr()->cashshopdata(i).title();
			if (GameDataManager::getSingleton().GetGameDataPtr()->cashshopdata(i).functiontype() == W_CashShopData_eFunctionType_Monthly) {
				isMoneyRuby = true;
			}
		}
	}
	if (mRewardLabel) {
		mRewardLabel->setString(itemNameStr.c_str());
	}

	// desc 보상을 확인하세요.
	mDesc->setString(GameStringDepot::getSingleton().getString("REWARD_CONFIRM_TOPUI").c_str());
}

void RewardPopupPanel::setLetterReward(W_RewardInfo rewardInfo)
{
	setRewardInfo(rewardInfo);
	
	//루비 상점 보상
	mTitle->setString(GameStringDepot::getSingleton().getString("LETTER_TITLE").c_str());	
	mTitleUnder->setString(GameStringDepot::getSingleton().getString("LETTER_TITLE").c_str());
	// desc 보상을 확인하세요.
	string itemNameStr = "";
	string bgStr = "";
	eResourceType type = rewardInfo.rewardset(0).type();
	if (type == CASH) {
		itemNameStr = GameStringDepot::getSingleton().getString("TXT_RUBY_UNIT");
		bgStr = "check_ruby";
	}
	else if (type == GAMEMONEY) {
		itemNameStr = GameStringDepot::getSingleton().getString("TXT_GOLD_UNIT");
		bgStr = "check_gold";
	}
	else if (type == CHIP) {
		itemNameStr = GameStringDepot::getSingleton().getString("TXT_CHIP_UNIT");
		bgStr = "check_chip";
	}
	else if (type == REPUTE) {
		itemNameStr = GameStringDepot::getSingleton().getString("TXT_REPUTE_UNIT");
		bgStr = "check_all";
	}
	else if (type == CHARACTER) {
		W_CharacterData characterData = PokerShopHelper::getCharacterData(rewardInfo.rewardset(0).id());
		itemNameStr = characterData.name();
		bgStr = "check_all";
	}
	else {
		itemNameStr = PokerResourceHelper::getTicketName(rewardInfo.rewardset(0).id());
		bgStr = "check_all";
	}


	if (mRewardBg)
		mRewardBg->playAnimation(bgStr);

	if (type == CHARACTER) {
		if (mRewardIcon)
			mRewardIcon->setVisible(false);

		if (mCharacterImg) {
			mCharacterImg->setSpriteFrameWithFile(PokerResourceHelper::getCharacterPhotoImg(rewardInfo.rewardset(0).id()));
			mCharacterImg->fit(getDummy("dmy_photo_boxer_60p").size);
		}
	}
	else {
		if (mRewardIcon)
			mRewardIcon->setVisible(true);

		if (mRewardIcon)
			mRewardIcon->playAnimation(PokerResourceHelper::getBigRewardIconStr(rewardInfo.rewardset(0)));

		if (mCharacterImg)
			mCharacterImg->setVisible(false);
	}	

	if (mRewardLabel)
		mRewardLabel->setString(PokerResourceHelper::getRewardString(rewardInfo.rewardset(0)).c_str());

	string descStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REWARD_POPUP_DESC"), itemNameStr, rewardInfo.rewardset(0).amount());
	mDesc->setString(descStr.c_str());
}
