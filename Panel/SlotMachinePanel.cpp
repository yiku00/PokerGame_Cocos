#include "pch.h"
#include "SlotMachinePanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
//#include "SimplePopupPanel.h"
//#include "HeroApp.h"

#include "Web/WebService.h"
#include "GameStringDepot.h"
#include "PokerChipWidget.h"

SlotMachinePanel::SlotMachinePanel(SLOT_TYPE slotType)
{
	mSkip = false;
	mSlotType = slotType;
	
	mLoginProcess = false;
	m_GamePlaying = false;
	m_bGetEvent = false;

	mMainPanel = nullptr;
	m_pSlotIconView = nullptr;
	m_pSlotIconContainer = nullptr;

	m_fLeftIconSpd = 0.f;
	m_fCenterIconSpd = 0.f;
	m_fRightIconSpd = 0.f;

	m_RandomEffectCount = 0.f;

	m_CanCount = 0;

	for (int _i = 0; _i < 3; _i++)
	{
		m_nRollSlot[_i] = 0;
		m_RollStopKind[_i] = -1;
	}

	for (int _i = 0; _i < 4; _i++)
	{
		m_nLeftIconIdx[_i] = 0;
		m_nCenterIconIdx[_i] = 0;
		m_nRightIconIdx[_i] = 0;
	}

	InitPanel();
	InitImage();
	InitButton();

	setButtonListener(this);	
}

SlotMachinePanel::~SlotMachinePanel()
{
	mMainPanel->destruct();
}

void SlotMachinePanel::InitPanel()
{
	CCSize contentsSize;
	mMainPanel = new Panel();
	if (mSlotType == SLOT_CHIP_TYPE) {
		mMainPanel->construct(getMxmlPath() + "slot_machine_chip.mxml");
		contentsSize = mMainPanel->getDummy("dmy_slot_machine_chip").size;
	}
	else if (mSlotType == SLOT_RUBY_TYPE) {
		mMainPanel->construct(getMxmlPath() + "slot_machine_ruby.mxml");
		contentsSize = mMainPanel->getDummy("dmy_slot_machine_ruby").size;
	}
	mMainPanel->setButtonListener(this);
	mMainPanel->setPositionY(contentsSize.height - DESIGN_HEIGHT); // -contentsSize.height / 2.f);
	mMainPanel->setContentSize(contentsSize);
	this->setContentSize(contentsSize);

	mSkipBtn = mMainPanel->getButton("sbtn_button_skip");
	setUseSkipBtn(false);

	CCSize size = CCDirector::sharedDirector()->getWinSize() / 2.f;

	m_pStencilImage = new CCSprite();
	m_pStencilImage->initWithTexture(CCTextureCache::sharedTextureCache()->addImage("ui/fade_spade.png"));
	m_pStencilImage->setPosition(ccp(size.width, size.height));
	m_pStencilImage->setScale(6.f);
	//m_pStencilImage->runAction(CCSequence::create(
	//	CCDelayTime::create(0.4f),
	//	CCScaleTo::create(0.5f, 6.f),
	//	NULL));

	mStartNotiAni = mMainPanel->getImage("skel_effect_lever");

	m_maskImage = CCClippingNode::create();
	m_maskImage->setInverted(false);
	m_maskImage->setAlphaThreshold(0);
	m_maskImage->addChild(mMainPanel);
	mMainPanel->release();
	m_maskImage->setStencil(m_pStencilImage);

	addChild(m_maskImage);
	//m_maskImage->release();

	mVictoryEffect = mMainPanel->getSkel("skel_effect_victory");
	mVictoryEffect->pauseAnimation();
	mVictoryEffect->setVisible(false);


	mStoneEffect1 = mMainPanel->getSkel("skel_effect_chance1");
	mStoneEffect1->pauseAnimation();
	mStoneEffect1->setVisible(false);
	mStoneEffect2 = mMainPanel->getSkel("skel_effect_chance2");
	mStoneEffect2->pauseAnimation();
	mStoneEffect2->setVisible(false);
	mStoneEffect3 = mMainPanel->getSkel("skel_effect_chance3");
	mStoneEffect3->pauseAnimation();
	mStoneEffect3->setVisible(false);
	

	mSlotLamp = mMainPanel->getSkel("skel_slot_lamp");
	mTypeSelectBtn = mMainPanel->getButton("sbtn_changebutton");

	mGoldTab = mMainPanel->getLabel("txt_mygold");
	mGoldTabUnder = mMainPanel->getLabel("txt_mygold_under");
	mNeedResoutceTab = mMainPanel->getLabel("txt_mychip");
	mNeedResoutceTabUnder = mMainPanel->getLabel("txt_mychip_under");
	mGameOppertunity = mMainPanel->getLabel("txt_chance");
	mGameOppertunityUnder = mMainPanel->getLabel("txt_chance_under");
	mGameName = mMainPanel->getLabel("txt_change");

	mGoldTab->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_MY_GOLD").c_str());
	mGoldTabUnder->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_MY_GOLD").c_str());
	mGameOppertunity->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_OPPORTUNITY").c_str());
	mGameOppertunityUnder->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_OPPORTUNITY").c_str());
	

	if (mSlotType == SLOT_CHIP_TYPE) {
		mNeedResoutceTab->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_MY_CHIP").c_str());
		mNeedResoutceTabUnder->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_MY_CHIP").c_str());
		mGameName->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_RUBY_CHANCE").c_str());		

		//cash 슬롯머신 비용이 0 이면 오픈 안한다.
		int perCash = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().slot_machine_cash();
		if (perCash == 0) {
			mTypeSelectBtn->setEnable(false);
			mTypeSelectBtn->setVisible(false);
			mGameName->setVisible(false);
		}
	}
	else {
		mNeedResoutceTab->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_MY_RUBY").c_str());
		mNeedResoutceTabUnder->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_MY_RUBY").c_str());
		mGameName->setString(GameStringDepot::getSingleton().getString("SLOTMACHINE_NORMAL_CHANCE").c_str());
	}

}

void SlotMachinePanel::InitImage()
{
	mReward1 = mMainPanel->getLabel("txt_productgold1");	//500억골드
	mReward2 = mMainPanel->getLabel("txt_productgold2");	//200억골드
	mReward3 = mMainPanel->getLabel("txt_productgold3");	//100억골드
	mReward4 = mMainPanel->getLabel("txt_productgold4");	//50억골드
	mReward5 = mMainPanel->getLabel("txt_productgold5");	//20억골드
	mReward6 = mMainPanel->getLabel("txt_productgold6");	//10억골드
	mReward7 = mMainPanel->getLabel("txt_productgold7");	//5억골드

	vector<Nx::Label*> labels;
	labels.push_back(mReward1);
	labels.push_back(mReward2);
	labels.push_back(mReward3);
	labels.push_back(mReward4);
	labels.push_back(mReward5);
	labels.push_back(mReward6);
	labels.push_back(mReward7);

	eResourceType slotResouceType = CASH;
	if (mSlotType == SLOT_CHIP_TYPE) {
		slotResouceType = CHIP;
	}
	

 	int size = GameDataManager::getSingleton().GetGameDataPtr()->slotmachinechancedata_size();
	int labelIndex = 0;
 	for (int i = 0; i < size; i++)
 	{
 		W_SlotMachineChanceData machineData = GameDataManager::getSingleton().GetGameDataPtr()->slotmachinechancedata(i);
		if (machineData.resourcetype() == slotResouceType) {
			string moneyStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(machineData.rewardinfo().rewardset(0).amount()), 3);
			if (labelIndex < labels.size()) {
				labels[labelIndex]->setString(moneyStr.c_str());
				labelIndex++;
			}
		}
 	}

	for (int _i = 0; _i < 7; _i++)
	{
		m_pScoreEffect[_i] = mMainPanel->getSkel("skel_score_effect" + StringConverter::toString(7-_i));
		m_pScoreEffect[_i]->playAnimation("score_effect_end");
		m_pScoreEffect[_i]->setVisible(false);
	}

	for (int _i = 0; _i < 6; _i++)
	{
		m_pLightEffect[_i] = mMainPanel->getSkel("skel_star_effect" + StringConverter::toString(_i + 1));
		m_pLightEffect[_i]->playAnimation("star_effect");
	}
	

	m_pLever = mMainPanel->getSkel("skel_lever_stick");
	m_pConnecter = mMainPanel->getSkel("skel_lever_connect");
	InitSlotIncon();

	m_MyGold = mMainPanel->getLabel("txt_gold");
	m_MyGold->setGrayColor(StringConverter::parseColor3B("f73030"));
	m_MyChip = mMainPanel->getLabel("txt_chip1");

	mMyCash = nullptr;
	if (mMainPanel->hasElement("txt_ruby1")) {
		mMyCash = mMainPanel->getLabel("txt_ruby1");
	}

	m_PlayChip = mMainPanel->getLabel("txt_chip2");

	mPlayCash = nullptr;
	if (mMainPanel->hasElement("txt_ruby2")) {
		mPlayCash = mMainPanel->getLabel("txt_ruby2");
	}

	//m_GetGold = mMainPanel->getLabel("txt_goldsum");
	mMainPanel->getLabel("txt_goldsum")->setVisible(false);

	m_GetGold = CCLabelBMFont::create("", "fonts/number_slot.fnt");
	m_GetGold->retain();
	m_GetGold->setAnchorPoint(ccp(0.5f, 0.5f));
	m_GetGold->setScale(1.f);
	m_GetGold->setPosition(ccp(DESIGN_WIDTH/2.f, 100.f));
	m_GetGold->setAnchorPoint(ccp(0.5f, 0.5f));
	mMainPanel->addChild(m_GetGold);
	m_GetGold->release();

	m_MyGold->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_MyChip->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_PlayChip->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//m_GetGold->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	int64 _MyGold = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
	int64 _MaxGold = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyMax;

	int64 _MyChip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	int myCash = GameDataManager::getSingleton().getPlayerInfo().cash();

	m_MyGold->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_MyGold), 3).c_str());
	if (_MyGold >= _MaxGold) {
		m_MyGold->setGrayscale(true);
	}
	else {
		m_MyGold->setGrayscale(false);
	}

	int _count = 0;
	int _cashcount = 0;

	if (mSlotType == SLOT_CHIP_TYPE) {
		m_MyChip->setString(StringConverter::toString(_MyChip).c_str());
		_count = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().slot_machine_chip();
		string perUseStr = NxGetFormatString(GameStringDepot::getSingleton().getString("SLOTMACHINE_PER_USE_RESOURCE"), _count);
		m_PlayChip->setString(perUseStr.c_str());
	}
	else if (mSlotType == SLOT_RUBY_TYPE) {

		mMyCash->setString(StringConverter::toString(myCash).c_str());
		m_MyChip->setString(StringConverter::toString(_MyChip).c_str());		
		_count = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().slot_machine_chip();
		_cashcount = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().slot_machine_cash();
		string perUseStr = NxGetFormatString(GameStringDepot::getSingleton().getString("SLOTMACHINE_PER_USE_RESOURCE"), _count);
		m_PlayChip->setString(perUseStr.c_str());
		string perCashUseStr = NxGetFormatString(GameStringDepot::getSingleton().getString("SLOTMACHINE_PER_USE_RESOURCE"), _cashcount); 
		mPlayCash->setString(perCashUseStr.c_str());
	}
	

	m_GetGold->setString("");
	m_GetGold->setVisible(false);
	m_CanCount = 0;

	m_CanPlayCount = nullptr;

	m_CanPlayCount = CCLabelBMFont::create("", "fonts/number_digital.fnt");
	m_CanPlayCount->retain();
	m_CanPlayCount->setAnchorPoint(ccp(0.5f, 0.5f));
	m_CanPlayCount->setScale(1.f);
	m_CanPlayCount->setPosition(mMainPanel->getImage("dmy_number_digital2")->getPosition() + ccp(0.f, 5.f));
	mMainPanel->addChild(m_CanPlayCount);
	m_CanPlayCount->release();	

	m_pSlotGoldEffect = mMainPanel->getSkel("skel_slot_gold_start");
	m_pSlotGoldEffect->setVisible(false);
	m_pSlotGoldEffect->stopLooping();
	m_pSlotGoldEffect->addEventListener(this);

	m_pSlotStarEffect = mMainPanel->getSkel("skel_slot_star");
	m_pSlotStarEffect->setVisible(false);
	m_pSlotStarEffect->stopLooping();

	SetPlayCount();
}



void SlotMachinePanel::InitButton()
{
	m_pLeverBall = mMainPanel->getButton("sbtn_lever_ball");
	m_pLeverBall->setType(Button::NoPressImg);
	m_pLeverBall->setEnable(true);
	m_pLeverBall->setPaused(true);


}

void SlotMachinePanel::InitSlotIncon()
{
	m_pSlotIconContainer = CCLayer::create();
	CCSize _contentSize = mMainPanel->getDummy("dmy_slotscreen_size").size;

	CCPoint _iconPosition = ccp(0.f, 0.f);
	for (int _i = 0; _i < 4; _i++)
	{
		m_pSlotIconLeft[_i] = new SkelObject();
		m_pSlotIconLeft[_i]->setSkelAnim("ui/slot_machine_8888.json");
		m_pSlotIconLeft[_i]->playAnimation(GetSlotIconName(_i, false));
		m_nLeftIconIdx[_i] = _i;
		m_pSlotIconLeft[_i]->setPosition(_iconPosition + ccp(_contentSize.width / 2.f - 208.f, 150 * _i));
		m_pSlotIconContainer->addChild(m_pSlotIconLeft[_i]);
		m_pSlotIconLeft[_i]->release();
	}

	for (int _i = 0; _i < 4; _i++)
	{
		m_pSlotIconCenter[_i] = new SkelObject();
		m_pSlotIconCenter[_i]->setSkelAnim("ui/slot_machine_8888.json");
		m_pSlotIconCenter[_i]->playAnimation(GetSlotIconName(_i, false));
		m_nCenterIconIdx[_i] = _i;
		m_pSlotIconCenter[_i]->setPosition(_iconPosition + ccp(_contentSize.width / 2.f, 150 * _i));
		m_pSlotIconContainer->addChild(m_pSlotIconCenter[_i]);
		m_pSlotIconCenter[_i]->release();
	}

	for (int _i = 0; _i < 4; _i++)
	{
		m_pSlotIconRight[_i] = new SkelObject();
		m_pSlotIconRight[_i]->setSkelAnim("ui/slot_machine_8888.json");
		m_pSlotIconRight[_i]->playAnimation(GetSlotIconName(_i, false));
		m_nRightIconIdx[_i] = _i;
		m_pSlotIconRight[_i]->setPosition(_iconPosition + ccp(_contentSize.width / 2.f + 208.f, 150 * _i));
		m_pSlotIconContainer->addChild(m_pSlotIconRight[_i]);
		m_pSlotIconRight[_i]->release();
	}

	m_pSlotIconContainer->setContentSize(_contentSize);

	m_pSlotIconView = CCScrollView::create(_contentSize, m_pSlotIconContainer);
	m_pSlotIconView->setDirection(extension::ScrollView::Direction::VERTICAL);
	m_pSlotIconView->setBounceable(false);

	m_pSlotIconView->setContentOffset(ccp(0, 0));

	CCPoint _ListPos = mMainPanel->getImage("dmy_slotscreen_size")->getPosition();
	m_pSlotIconView->setPosition(ccp(-512.f, -70.f));
	//기덕 수정	완료
	mMainPanel->getImage("dmy_slotscreen_size")->addChild(m_pSlotIconView);
	CCPoint pos = ccpSub(mMainPanel->getImage("dmy_slotscreen_size")->getPosition(), ccp(_contentSize.width * 0.5f, _contentSize.height * 0.5f));
	m_pSlotIconView->setPositionX(-_contentSize.width * 0.5f);
	m_pSlotIconView->setPositionY(-_contentSize.height * 0.5f);
}

void SlotMachinePanel::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void SlotMachinePanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (name == getButtonName(mTypeSelectBtn)) {
		if (mStartNotiAni->isVisible()) {
			string selectStr = "SELECT_TYPE_CHIP";
			if (mSlotType == SLOT_CHIP_TYPE)
				selectStr = "SELECT_TYPE_RUBY";
			fireMessage(selectStr);
		}
	}
	else if (name == getButtonName(mSkipBtn)) {
		mSkip = true;
		StopRollLeft();
		StopRollCenter();
		StopRollRight();
		setUseSkipBtn(false);
	}
}

void SlotMachinePanel::update(float dt)
{
	UpdateRandomEffect(dt);
	UpdateSlotIcon(dt);
	UpdateGetEvent(dt);
}

bool SlotMachinePanel::handling(STCMD &stCmd)
{
	if (!mLoginProcess)
		return false;

	return false;
}

void SlotMachinePanel::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
		HeroApp::getSingleton().exit();
		return;

		if (SceneManager::getSingletonPtr()->isChanging())
			return;

		if (m_GamePlaying)
			return;

		if (m_pSlotGoldEffect)
			m_pSlotGoldEffect->subEventListener(this);

		SoundManager::getSingletonPtr()->stopEffects();
		SceneUtil::changeScene(SceneUtil::SceneLobby);
	}
}

bool SlotMachinePanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint _tableTouch = pTouch->getLocation();
	if (m_pLeverBall->hasCollided(m_pLeverBall->convertToNodeSpace(_tableTouch)))
	{
		if (!m_GamePlaying)
		{
			m_LeverBallPosition = m_pLeverBall->getPosition();
			m_ConnecterPosition = m_pConnecter->getPosition();
			m_LeverPosition = m_pLever->getPosition();
			m_fLeverScale = 1.f;
			return true;
		}
	}
	return false;
}

void SlotMachinePanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_GamePlaying)
		return;

	CCPoint _TouchStart = pTouch->getStartLocation();
	CCPoint _TouchMove = pTouch->getLocation();

	float _moveY = _TouchMove.y - _TouchStart.y;

	if (_moveY > 0)
		return;

	if (_moveY < -200)
		return;

	float _posY = m_LeverBallPosition.y + _moveY;
	m_pLeverBall->setPositionY(_posY);

	float _ballScale = 1.f-(_moveY / 600.f);
	m_pLeverBall->getButtonSkelObject()->setScale(_ballScale);

	float _conPosY = m_ConnecterPosition.y + (_moveY / 8.f);
	m_pConnecter->setPositionY(_conPosY);

	float _LeverPosY = m_LeverPosition.y + (_moveY / 3.f);
	m_pLever->setPositionY(_LeverPosY);

	float _LeverScale = (250.f + _moveY) / 250.f;
	m_pLever->setScaleY(_LeverScale);

}

void SlotMachinePanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	ReturnLever();	
}

void SlotMachinePanel::PlaySlotMachine()
{
	//scheduleUpdate();
	RollIcon(0);
	RollIcon(1);
	RollIcon(2);
	m_GamePlaying = true;
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTSPIN, true, true);
}

void SlotMachinePanel::EndSlotMachine()
{
	mSkip = false;
	setUseSkipBtn(false);

	m_GamePlaying = false;
	m_bGetEvent = false;

	m_CurGold = 0;
	m_TargetGold = 0;


	mSlotLamp->playAnimation("slot_lamp");

	for (int _i = 0; _i < 7; _i++)
	{
		if (m_pScoreEffect[_i]->isVisible())
			m_pScoreEffect[_i]->playAnimation("score_effect_end");
	}

	for (int _i = 0; _i < 3; _i++)
	{
		m_nRollSlot[_i] = 0;
		m_RollStopKind[_i] = -1;
	}

	int64 _MyGold = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
	int64 _MaxGold = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyMax;
	int64 _MyChip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	int myCash = GameDataManager::getSingleton().getPlayerInfo().cash();
	m_MyGold->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_MyGold), 3).c_str());
	if (_MyGold >= _MaxGold) {
		m_MyGold->setGrayscale(true);
	}
	else {
		m_MyGold->setGrayscale(false);
	}

	if (mSlotType == SLOT_CHIP_TYPE) {
		m_MyChip->setString(StringConverter::toString(_MyChip).c_str());
	}
	else if (mSlotType == SLOT_RUBY_TYPE) {
		m_MyChip->setString(StringConverter::toString(_MyChip).c_str());
		mMyCash->setString(StringConverter::toString(myCash).c_str());
	}

	m_GetGold->setVisible(false);
	m_GetGold->setString("");

	m_pSlotGoldEffect->stopLooping();
	m_pSlotGoldEffect->appendAnimation("slot_gold_end");

	mVictoryEffect->setVisible(false);
	m_pSlotStarEffect->setVisible(false);
	mStartNotiAni->setVisible(true);
}

void SlotMachinePanel::SetSlotMachine()
{
	int _count = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().slot_machine_daily_count();
	m_CanCount = _count - GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_SlotMachineCount;

	if (GameDataManager::getSingletonPtr()->m_SlotMachineIcon[0] == -1 && GameDataManager::getSingletonPtr()->m_SlotMachineIcon[1] == -1 && GameDataManager::getSingletonPtr()->m_SlotMachineIcon[2] == -1) {
		m_RollStopKind[0] = 1;
		m_RollStopKind[1] = 1;
		m_RollStopKind[2] = 1;		
		mSkip = true;
		m_bGetEvent = true;
		SoundManager::getSingletonPtr()->stopEffects();
	}
	else {
		setUseSkipBtn(true);
		runAction(CCSequence::create(
			CCCallFunc::create(this, callfunc_selector(SlotMachinePanel::StopRollLeft)),
			CCDelayTime::create(0.4f),
			CCCallFunc::create(this, callfunc_selector(SlotMachinePanel::StopRollCenter)),
			CCDelayTime::create(1.6f),
			CCCallFunc::create(this, callfunc_selector(SlotMachinePanel::StopRollRight)),
			NULL));
	}	
}

void SlotMachinePanel::SendSlotMachineSeq()
{
	if (mSlotType == SLOT_CHIP_TYPE) {
		WebService::getSingletonPtr()->_sendSlotMachineReq(W_SlotMachineReq_eSlotMachineResourceType::W_SlotMachineReq_eSlotMachineResourceType_s_Chip);
	}
	else if (mSlotType == SLOT_RUBY_TYPE) {
		WebService::getSingletonPtr()->_sendSlotMachineReq(W_SlotMachineReq_eSlotMachineResourceType::W_SlotMachineReq_eSlotMachineResourceType_s_Cash);
	}
}

void SlotMachinePanel::ReturnLever()
{
	bool isPossible = true;
	//만약 할수 없다면 팝업창으로 한다.
	int64 _myChip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	int32 _playChip = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().slot_machine_chip();
	if (mSlotType == SLOT_CHIP_TYPE) {
		//Chip Error Effect
		if (m_CanCount == 0)
		{
			string msgText = GameStringDepot::getSingleton().getString("TXT_SLOTFAIL_NO_GAMECOUNT");
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText), DYNAMIC_PUSH_LAYER);
			m_pLeverBall->runAction(CCMoveTo::create(0.2f, m_LeverBallPosition));
			m_pLeverBall->getButtonSkelObject()->runAction(CCScaleTo::create(0.2f, 1.f));
			m_pConnecter->runAction(CCMoveTo::create(0.2f, m_ConnecterPosition));
			m_pLever->runAction(CCMoveTo::create(0.2f, m_LeverPosition));
			m_pLever->runAction(CCScaleTo::create(0.2f, 1.f, m_fLeverScale));
			mStartNotiAni->setVisible(true);
			return;
		}
		else if (_myChip < _playChip)
		{
			string msgText = GameStringDepot::getSingleton().getString("TXT_SLOTFAIL_NO_CHIP");
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText), DYNAMIC_PUSH_LAYER);
			m_pLeverBall->runAction(CCMoveTo::create(0.2f, m_LeverBallPosition));
			m_pLeverBall->getButtonSkelObject()->runAction(CCScaleTo::create(0.2f, 1.f));
			m_pConnecter->runAction(CCMoveTo::create(0.2f, m_ConnecterPosition));
			m_pLever->runAction(CCMoveTo::create(0.2f, m_LeverPosition));
			m_pLever->runAction(CCScaleTo::create(0.2f, 1.f, m_fLeverScale));
			mStartNotiAni->setVisible(true);
			return;
		}
		isPossible = m_CanCount != 0 && _myChip >= _playChip;
	}
	else {
		if (m_CanCount == 0)
		{
			string msgText = GameStringDepot::getSingleton().getString("TXT_SLOTFAIL_NO_GAMECOUNT");
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText), DYNAMIC_PUSH_LAYER);
			m_pLeverBall->runAction(CCMoveTo::create(0.2f, m_LeverBallPosition));
			m_pLeverBall->getButtonSkelObject()->runAction(CCScaleTo::create(0.2f, 1.f));
			m_pConnecter->runAction(CCMoveTo::create(0.2f, m_ConnecterPosition));
			m_pLever->runAction(CCMoveTo::create(0.2f, m_LeverPosition));
			m_pLever->runAction(CCScaleTo::create(0.2f, 1.f, m_fLeverScale));
			mStartNotiAni->setVisible(true);
			return;
		}
		else {
			int myCash = GameDataManager::getSingleton().getPlayerInfo().cash();
			int perCash = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().slot_machine_cash();
			isPossible = (myCash >= perCash) && (_myChip >= _playChip);
			if (!isPossible) {
				string msgText;
				if (_myChip < _playChip)
					msgText = GameStringDepot::getSingleton().getString("TXT_SLOTFAIL_NO_CHIP");
				else
					msgText = GameStringDepot::getSingleton().getString("TXT_SLOTFAIL_NO_RUBY");

				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText), DYNAMIC_PUSH_LAYER);
				m_pLeverBall->runAction(CCMoveTo::create(0.2f, m_LeverBallPosition));
				m_pLeverBall->getButtonSkelObject()->runAction(CCScaleTo::create(0.2f, 1.f));
				m_pConnecter->runAction(CCMoveTo::create(0.2f, m_ConnecterPosition));
				m_pLever->runAction(CCMoveTo::create(0.2f, m_LeverPosition));
				m_pLever->runAction(CCScaleTo::create(0.2f, 1.f, m_fLeverScale));
				mStartNotiAni->setVisible(true);
				return;
			}
		}		
	}

	if (isPossible)
	{
		m_pLeverBall->runAction(CCSequence::create(
			CCCallFunc::create(this, callfunc_selector(SlotMachinePanel::PlaySlotMachine)),
			CCMoveTo::create(0.2f, m_LeverBallPosition),
			CCDelayTime::create(1.f),
			CCCallFunc::create(this, callfunc_selector(SlotMachinePanel::SendSlotMachineSeq)),
			NULL));
	}
	else
	{
		m_pLeverBall->runAction(CCMoveTo::create(0.2f, m_LeverBallPosition));
	}

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTLEVER);
	m_pLeverBall->getButtonSkelObject()->runAction(CCScaleTo::create(0.2f, 1.f));
	m_pConnecter->runAction(CCMoveTo::create(0.2f, m_ConnecterPosition));
	m_pLever->runAction(CCMoveTo::create(0.2f, m_LeverPosition));
	m_pLever->runAction(CCScaleTo::create(0.2f, 1.f, m_fLeverScale));

	for (int _i = 0; _i < 7; _i++)
	{
		if(m_pScoreEffect[_i]->isVisible())
			m_pScoreEffect[_i]->setVisible(false);
	}

	SetPlayCount(-1);
	if (mStoneEffect3 && m_CanCount > 99) {
		mStoneEffect3->setVisible(true);
		mStoneEffect3->playAnimation("effect_chance");
	}

	if (mStoneEffect2 && m_CanCount > 9) {
		mStoneEffect2->setVisible(true);
		mStoneEffect2->playAnimation("effect_chance");
	}

	if (mStoneEffect1) {
		mStoneEffect1->setVisible(true);
		mStoneEffect1->playAnimation("effect_chance");
	}

	mStartNotiAni->setVisible(false);
}

std::string SlotMachinePanel::GetSlotIconName(int _type, bool _move)
{
	if (_type <= 0)
		_type += (SlotMachineIcon_max - 1);

	if (_type >= SlotMachineIcon_max)
		_type -= (SlotMachineIcon_max - 1);

	string _frameName = "";

	if (_move)
	{
		_frameName = "movingicon_";
	}
	else
	{
		_frameName = "sloticon_";
	}

	switch (_type)
	{
	case apple:
		_frameName += "apple";
		break;
	case lemon:
		_frameName += "lemon";
		break;
	case clover:
		_frameName += "clover";
		break;
	case diamond:
		_frameName += "diamond";
		break;
	case bar:
		_frameName += "bar";
		break;
	case seven:
		_frameName += "seven";
		break;
	case logo:
		_frameName += "logo";
		break;
	default:
		return "";
		break;
	}

	return _frameName;
}

void SlotMachinePanel::RollIcon(int _num)
{
	if (_num >= 3 || _num < 0)
		return;

	m_nRollSlot[_num] = true;
	
}

void SlotMachinePanel::UpdateLeftSlot(float dt)
{
	for (int _i = 0; _i < 4; _i++)
	{
		SkelObject* _obj = m_pSlotIconLeft[_i];
		float _posY = _obj->getPositionY();

		if (m_nRollSlot[0] == SLOT_ROLL)
		{
			if (m_fLeftIconSpd >= 1500.f)
			{
				m_fLeftIconSpd = 1500.f;
			}
			else
			{
				m_fLeftIconSpd += 1500.f*dt;
			}
		}
		else if (m_nRollSlot[0] == SLOT_STOP)
		{
			if (m_fLeftIconSpd <= 500.f)
			{
				m_fLeftIconSpd = 500.f;
			}
			else
			{
				m_fLeftIconSpd -= 150.f*dt;
			}
		}


		_posY -= (m_fLeftIconSpd * dt);

		if (_posY <= -200.f)
		{
			_posY += 600.f;
			m_nLeftIconIdx[_i] += 4;

			if (m_nLeftIconIdx[_i] >= SlotMachineIcon_max)
				m_nLeftIconIdx[_i] -= (SlotMachineIcon_max - 1);

			if (m_nLeftIconIdx[_i] == m_RollStopKind[0])
			{
				m_nRollSlot[0] = SLOT_STOP;
			}

			if (m_nRollSlot[0] == SLOT_STOP)
			{
				_obj->playAnimation(GetSlotIconName(m_nLeftIconIdx[_i], false));
			}
			else
			{
				_obj->playAnimation(GetSlotIconName(m_nLeftIconIdx[_i], true));
			}

			cout << "ICON IDX," << m_nLeftIconIdx[0] << "," << m_nLeftIconIdx[1] << "," << m_nLeftIconIdx[2] << "," << m_nLeftIconIdx[3] << endl;

		}

		CCLOG("_posY = %f", _posY);

		if (mSkip || _posY < 165.f && _posY > 135.f && m_fLeftIconSpd == 500.f && m_nLeftIconIdx[_i] == m_RollStopKind[0])
		{
			m_nRollSlot[0] = SLOT_END;
			for (int _count = 0; _count < 4; _count++)
			{
				int _index = _i - 1 + _count;

				if (_index < 0)
					_index += 4;

				if (_index >= 4)
					_index -= 4;

				m_pSlotIconLeft[_index]->setPositionY(150.f*_count);

				int _iconKind = m_RollStopKind[0] - 1 + _count;
				m_pSlotIconLeft[_index]->playAnimation(GetSlotIconName(_iconKind, false));
				m_nLeftIconIdx[_index] = _iconKind;
			}

			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTSTOP);

			if (isAllStopSlot())
				StartGetEvent();
			return;
		}
		else
		{
			_obj->setPositionY(_posY);
		}

	}
}
void SlotMachinePanel::UpdateCenterSlot(float dt)
{
	for (int _i = 0; _i < 4; _i++)
	{
		SkelObject* _obj = m_pSlotIconCenter[_i];
		float _posY = _obj->getPositionY();

		if (m_nRollSlot[1] == SLOT_ROLL)
		{
			if (m_fCenterIconSpd >= 1500.f)
			{
				m_fCenterIconSpd = 1500.f;
			}
			else
			{
				m_fCenterIconSpd += 1500.f*dt;
			}
		}
		else if (m_nRollSlot[1] == SLOT_STOP)
		{
			if (m_fCenterIconSpd <= 500.f)
			{
				m_fCenterIconSpd = 500.f;
			}
			else
			{
				m_fCenterIconSpd -= 150.f*dt;
			}
		}

		_posY += (m_fCenterIconSpd * dt);

		if (_posY >= 500.f)
		{
			_posY -= 600.f;
			m_nCenterIconIdx[_i] -= 4;


			if (m_nCenterIconIdx[_i] <= 0)
				m_nCenterIconIdx[_i] += (SlotMachineIcon_max - 1);

			if (m_nCenterIconIdx[_i] == m_RollStopKind[1])
			{
				m_nRollSlot[1] = SLOT_STOP;
			}

			if (m_nRollSlot[1] == SLOT_STOP)
			{
				_obj->playAnimation(GetSlotIconName(m_nCenterIconIdx[_i], false));
			}
			else
			{
				_obj->playAnimation(GetSlotIconName(m_nCenterIconIdx[_i], true));
			}
		}

		if (mSkip || _posY < 165.f && _posY > 135.f && m_fCenterIconSpd == 500.f && m_nCenterIconIdx[_i] == m_RollStopKind[1])
		{
			m_nRollSlot[1] = SLOT_END;
			for (int _count = 0; _count < 4; _count++)
			{
				int _index = _i - 1 + _count;

				if (_index < 0)
					_index += 4;

				if (_index >= 4)
					_index -= 4;

				m_pSlotIconCenter[_index]->setPositionY(150.f*_count);

				int _iconKind = m_RollStopKind[1] - 1 + _count;
				m_pSlotIconCenter[_index]->playAnimation(GetSlotIconName(_iconKind, false));
				m_nCenterIconIdx[_index] = _iconKind;
			}

			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTSTOP);

			if (isAllStopSlot())
				StartGetEvent();
			return;
		}
		else
		{
			_obj->setPositionY(_posY);
		}
	}
}
void SlotMachinePanel::UpdateRightSlot(float dt)
{
	cout << endl;
	cout << "Slot Kind : ";
	for (int _i = 0; _i < 4; _i++)
	{
		SkelObject* _obj = m_pSlotIconRight[_i];
		int _kind = m_nRightIconIdx[_i];

		cout << _kind << " ";

		float _posY = _obj->getPositionY();

		if (m_nRollSlot[2] == SLOT_ROLL)
		{
			if (m_fRightIconSpd >= 1500.f)
			{
				m_fRightIconSpd = 1500.f;
			}
			else
			{
				m_fRightIconSpd += 1500.f*dt;
			}
		}
		else if (m_nRollSlot[2] == SLOT_STOP)
		{
			if (m_fRightIconSpd <= 500.f)
			{
				m_fRightIconSpd = 500.f;
			}
			else
			{
				m_fRightIconSpd -= 150.f*dt;
			}
		}
		_posY -= (m_fRightIconSpd * dt);

		if (_posY <= -200.f)
		{
			_posY += 600.f;
			m_nRightIconIdx[_i] += 4;

			if (m_nRightIconIdx[_i] >= SlotMachineIcon_max)
				m_nRightIconIdx[_i] -= (SlotMachineIcon_max - 1);

			if (m_nRightIconIdx[_i] == m_RollStopKind[2])
			{
				m_nRollSlot[2] = SLOT_STOP;
			}

			if (m_nRollSlot[2] == SLOT_STOP)
			{
				_obj->playAnimation(GetSlotIconName(m_nRightIconIdx[_i], false));
			}
			else
			{
				_obj->playAnimation(GetSlotIconName(m_nRightIconIdx[_i], true));
			}

		}

		if (mSkip || _posY < 165.f && _posY > 135.f && m_fRightIconSpd == 500.f && m_nRightIconIdx[_i] == m_RollStopKind[2])
		{
			m_nRollSlot[2] = SLOT_END;
			for (int _count = 0; _count < 4; _count++)
			{
				int _index = _i-1 + _count;

				if (_index < 0)
					_index += 4;

				if (_index >= 4)
					_index -= 4;

				m_pSlotIconRight[_index]->setPositionY(150.f*_count);

				int _iconKind = m_RollStopKind[2] - 1 + _count;
				m_pSlotIconRight[_index]->playAnimation(GetSlotIconName(_iconKind, false));
				m_nRightIconIdx[_index] = _iconKind;
			}

			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTSTOP);

			if (isAllStopSlot())
				StartGetEvent();
			return;
		}
		else
		{
			_obj->setPositionY(_posY);
		}
	}
}

bool SlotMachinePanel::isAllStopSlot()
{
	for (int _i = 0; _i < 3; _i++)
	{
		if (m_nRollSlot[_i] != SLOT_END)
			return false;
	}
	return true;
}

void SlotMachinePanel::UpdateSlotIcon(float dt)
{
	if (m_GamePlaying == false)
	{
	//	unscheduleUpdate();
		return;
	}

	if (m_nRollSlot[0] != SLOT_READY && m_nRollSlot[0] != SLOT_END)
	{
		UpdateLeftSlot(dt);
	}

	if (m_nRollSlot[1] != SLOT_READY && m_nRollSlot[1] != SLOT_END)
	{
		UpdateCenterSlot(dt);
	}

	if (m_nRollSlot[2] != SLOT_READY && m_nRollSlot[2] != SLOT_END)
	{
		UpdateRightSlot(dt);
	}
}

void SlotMachinePanel::StopRollLeft()
{
	m_RollStopKind[0] = GameDataManager::getSingletonPtr()->m_SlotMachineIcon[0];
}

void SlotMachinePanel::StopRollCenter()
{
	m_RollStopKind[1] = GameDataManager::getSingletonPtr()->m_SlotMachineIcon[1];
}

void SlotMachinePanel::StopRollRight()
{
	m_RollStopKind[2] = GameDataManager::getSingletonPtr()->m_SlotMachineIcon[2];
}

void SlotMachinePanel::StartGetEvent()
{
	if (GameDataManager::getSingletonPtr()->m_SlotMachineRewardInfo == nullptr)
		return;

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTSPIN, false);

	m_bGetEvent = true;

	m_CurGold = 0;
	m_TargetGold = 0;

	W_RewardInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SlotMachineRewardInfo;

	int _size = _pInfo->rewardset_size();
	for (int _i = 0; _i < _size; _i++)
	{
		if (_pInfo->rewardset(_i).has_type() && _pInfo->rewardset(_i).has_amount())
		{
			if (_pInfo->rewardset(_i).type() == GAMEMONEY)
			{
				m_TargetGold += _pInfo->rewardset(_i).amount();
			}
		}
	}

	SetRewardEffect(m_RollStopKind[2]);

	m_GetGold->setString("0");
	m_GetGold->setVisible(true);

	if (m_TargetGold > 0)
	{
		if (m_pSlotGoldEffect->isVisible() == false)
			m_pSlotGoldEffect->setVisible(true);
		if (m_pSlotStarEffect->isVisible() == false)
			m_pSlotStarEffect->setVisible(true);

		m_pSlotGoldEffect->playAnimation("slot_gold_start");
		m_pSlotGoldEffect->appendAnimation("slot_gold_loop", true);

		mVictoryEffect->setVisible(true);
		mVictoryEffect->playAnimation("effect_victory");

		string skinStr = "";
		if (m_RollStopKind[0] == 7) {
			//$
			skinStr = "logo";
		}
		else if (m_RollStopKind[0] == 6) {
			//7
			skinStr = "seven";
		}
		else if (m_RollStopKind[0] == 5) {
			//bar
			skinStr = "bar";
		}
		else if (m_RollStopKind[0] == 4) {
			//dia
			skinStr = "diamond";
		}
		else if (m_RollStopKind[0] == 3) {
			//clover
			skinStr = "clover";
		}
		else if (m_RollStopKind[0] == 2) {
			//lemon
			skinStr = "lemon";
		}
		else if (m_RollStopKind[0] == 1) {
			//apple
			skinStr = "apple";
		}
		mVictoryEffect->setSkin(skinStr);

		//coin
		if (m_TargetGold >= 20000000000)
		{
			createGoldChip(300, 0.01f, 0);
		}
		if (m_TargetGold >= 5000000000)
		{
			createGoldChip(150, 0.02f, 0);
		}
		else
		{
			createGoldChip(60, 0.05f, 0);
		}

		//sound
		if (m_TargetGold >= 50000000000)
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTJACKPOT);
		}
		else
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTWIN);
		}
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTCOIN, true, true);			
	}
}

void SlotMachinePanel::UpdateGetEvent(float _dt)
{
	if (m_bGetEvent == false)
		return;

	int64 _plusValue = (m_TargetGold / 3) * _dt;
	m_CurGold += _plusValue;

	if (m_TargetGold <= m_CurGold)
	{
		m_CurGold = m_TargetGold;
		m_bGetEvent = false;
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTCOIN, false);
		runAction(CCSequence::create(
			CCDelayTime::create(1.8f),
			CCCallFunc::create(this, callfunc_selector(SlotMachinePanel::EndSlotMachine)),
			NULL));
	}

	string _getGold = StringConverter::toString(m_CurGold) + "gd";
	m_GetGold->setString(_getGold.c_str());
}

void SlotMachinePanel::SetRewardEffect(int _index)
{
	for (int _i = 0; _i < 7; _i++)
	{
		m_pScoreEffect[_i]->setVisible(true);
		if (_index - 1 == _i) {
			m_pScoreEffect[_i]->playAnimation("score_effect_start");
			m_pScoreEffect[_i]->appendAnimation("score_effect_stay", true);
		}
		else {
			m_pScoreEffect[_i]->playAnimation("score_effect_off_start");
		}
	}	

	if (_index > 5)
		mSlotLamp->playAnimation("slot_lamp2");
}

void SlotMachinePanel::UpdateRandomEffect(float dt)
{
	m_RandomEffectCount += dt;

	if (m_RandomEffectCount >= 3.f)
	{
		m_RandomEffectCount = (rand() % 20);
		m_RandomEffectCount = m_RandomEffectCount * 0.1f;

		int _idx = rand() % 6;
		m_pLightEffect[_idx]->playAnimation("star_effect");
	}
}

void SlotMachinePanel::onEvent(int trackIdx, spEvent* event)
{
	string _eventName = event->data->name;

	if (_eventName == "slot_star_start")
	{
		m_pSlotStarEffect->playAnimation("slot_star", true);
	}

	if (_eventName == "slot_star_end")
	{
		m_pSlotStarEffect->stopLooping();
	}
}

void SlotMachinePanel::createGoldChip(int _count, float _term, float _delay)
{

	for (int _j = 0; _j < _count; _j++)
	{
		PokerChipWidget* _pChipWiget = new PokerChipWidget();
		//기덕 수정
		mMainPanel->getImage("dmy_gold_position")->addChild(_pChipWiget, 9);		
		_pChipWiget->ActionSlotMachineGold(_delay + ((float)(_j)* _term));
		_pChipWiget->autorelease();
	}

	return;
}


void SlotMachinePanel::SetPlayCount(int recount /*= 0*/)
{
	if (m_CanPlayCount == nullptr) {
		m_CanCount = 999;
		return;
	}

	if (GameDataManager::getSingletonPtr()->GetGameDataPtr()->has_startassets())
	{
		if (GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().has_slot_machine_daily_count())
		{
			int _count = GameDataManager::getSingletonPtr()->GetGameDataPtr()->startassets().slot_machine_daily_count();
			m_CanCount = _count - GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_SlotMachineCount;
		}
	}

	if (m_CanCount > 999)
	{
		m_CanPlayCount->setString("999");
		return;
	}

	int showCount = m_CanCount + recount;
	string _number = StringConverter::toString((showCount / 100) % 10) + StringConverter::toString((showCount / 10) % 10) + StringConverter::toString(showCount % 10);

	m_CanPlayCount->setString(_number.c_str());
}

void SlotMachinePanel::setUseSkipBtn(bool use)
{
	mSkipBtn->setEnable(use);
	mSkipBtn->setVisible(use);
	mMainPanel->getLabel("txt_skip")->setVisible(use);
}

void SlotMachinePanel::onEnter()
{
	Panel::onEnter();

	setKeypadEnabled(true);
	setTouchable(true);
	scheduleUpdate();
}