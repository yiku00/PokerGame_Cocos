#include "pch.h"
#include "SlotMachineBackPanel.h"
#include "HeroUtil.h"
#include "SceneUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
//#define SLOT_WHEEL
#define SLOT_PANEL_WIDTH DESIGN_WIDTH * 1.5f

SlotMachineBackPanel::SlotMachineBackPanel()
{
	initPanel();
}

SlotMachineBackPanel::~SlotMachineBackPanel()
{
	
}

void SlotMachineBackPanel::initPanel()
{
	mMoveAni = false;
#ifdef SLOT_WHEEL
	mType = SLOT_CHIP_TYPE;
	construct(getMxmlPath() + "slot_machine_back.mxml");
	setButtonListener(this);
	mCloseBtn = getButton("sbtn_gameout");
	mChipPanel = new SlotMachinePanel(SlotMachinePanel::SLOT_CHIP_TYPE);
	addChild(mChipPanel);
	mChipPanel->release();
	mChipPanel->setListener(this);

	mRubyPanel = new SlotMachinePanel(SlotMachinePanel::SLOT_RUBY_TYPE);
	addChild(mRubyPanel);
	mRubyPanel->release();
	mRubyPanel->setListener(this);
	mRubyPanel->setPositionX(SLOT_PANEL_WIDTH);
	//setActivate(SLOT_CHIP_TYPE);	
#else
	construct(getMxmlPath() + "slot_machine_back.mxml");
	setButtonListener(this);
	mCloseBtn = getButton("sbtn_gameout");
	mWheelPanel = new SlotMachineWheelPanel();
	addChild(mWheelPanel);
	mWheelPanel->release();
	mWheelPanel->setListener(this);
#endif

	getLabel("txt_gameout")->setString(GameStringDepot::getSingleton().getString("TXT_OUT").c_str());
}

void SlotMachineBackPanel::onClicked(const string& buttonName)
{
	if (buttonName == "sbtn_gameout")
	{
		bool playing = false;
#ifdef SLOT_WHEEL
		if (mType == SLOT_CHIP_TYPE)
			playing = mChipPanel->m_GamePlaying;
		else
			playing = mRubyPanel->m_GamePlaying;
#else
		playing = mWheelPanel->m_GamePlaying;
#endif
		if (playing)
			return;

		SoundManager::getSingletonPtr()->stopEffects();
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		SceneUtil::changeScene(SceneUtil::SceneLobby);
	}
}

void SlotMachineBackPanel::onLayerMessage(const string& msg)
{
#ifdef SLOT_WHEEL
	if (msg == "SELECT_TYPE_CHIP") {
		setActivate(SLOT_CHIP_TYPE , true);
	}
	else if(msg == "SELECT_TYPE_RUBY") {
		setActivate(SLOT_RUBY_TYPE , true);
	}
#else
	setActivate(true);
#endif
}
#ifdef SLOT_WHEEL
void SlotMachineBackPanel::setActivate(SLOT_TYPE type, bool ani /*= false*/)
{
	if (mType == type)
		return;

	if (mMoveAni)	//움직이고 있다면
		return;

	//처음에 슬롯  //루비가 오른쪽
	if (ani) {
		mType = type;
		mMoveAni = true;
		if (mType == SLOT_CHIP_TYPE) {
			CCFiniteTimeAction* ani_moveup = CCMoveBy::create(0.3f, CCPointMake(SLOT_PANEL_WIDTH, 0));
			CCFiniteTimeAction* ani_moveup2 = CCMoveBy::create(0.3f, CCPointMake(SLOT_PANEL_WIDTH, 0));
			CCFiniteTimeAction* callbackAction = CCCallFunc::create(this, callfunc_selector(SlotMachineBackPanel::aniEnd));

			CCAction* squenceAction = CCSequence::create(ani_moveup,NULL);
			CCAction* squenceAction2 = CCSequence::create(ani_moveup2, callbackAction, NULL);
			mChipPanel->runAction(squenceAction);
			mRubyPanel->runAction(squenceAction2);
			mChipPanel->SetPlayCount(0);
		}
		else if (mType == SLOT_RUBY_TYPE) {
			CCFiniteTimeAction* ani_moveup = CCMoveBy::create(0.3f, CCPointMake(-SLOT_PANEL_WIDTH, 0));
			CCFiniteTimeAction* ani_moveup2 = CCMoveBy::create(0.3f, CCPointMake(-SLOT_PANEL_WIDTH, 0));
			CCFiniteTimeAction* callbackAction = CCCallFunc::create(this, callfunc_selector(SlotMachineBackPanel::aniEnd));
			CCAction* squenceAction = CCSequence::create(ani_moveup, NULL);
			CCAction* squenceAction2 = CCSequence::create(ani_moveup2, callbackAction , NULL);
			mChipPanel->runAction(squenceAction);
			mRubyPanel->runAction(squenceAction2);
			mRubyPanel->SetPlayCount(0);
		}
	}
	else {
		mType = type;
		if (mType == SLOT_CHIP_TYPE) {
			mChipPanel->setVisible(true);
			mChipPanel->setPositionX(0);			
			mChipPanel->SetPlayCount(0);
		}
		else if (mType == SLOT_RUBY_TYPE) {
			mRubyPanel->setVisible(true);
			mRubyPanel->setPositionX(0);
			mRubyPanel->SetPlayCount(0);			
		}
	}	
}

void SlotMachineBackPanel::SetSlotMachine()
{
	if (mType == SLOT_CHIP_TYPE) {
		mChipPanel->SetSlotMachine();
	}
	else if(mType == SLOT_RUBY_TYPE) {
		mRubyPanel->SetSlotMachine();
	}
}

#else

void SlotMachineBackPanel::setActivate( bool ani /*= false*/)
{
	if (mMoveAni)	//움직이고 있다면
		return;

	//처음에 슬롯  //루비가 오른쪽
	if (ani) {
		mMoveAni = true;
		CCFiniteTimeAction* ani_moveup = CCMoveBy::create(0.3f, CCPointMake(SLOT_PANEL_WIDTH, 0));
		//CCFiniteTimeAction* callbackAction = CCCallFunc::create(this, callfunc_selector(SlotMachineBackPanel::aniEnd));

		CCAction* squenceAction = CCSequence::create(ani_moveup, NULL);
		mWheelPanel->runAction(squenceAction);
		mWheelPanel->SetPlayCount(0);
	}
	else {
		
		mWheelPanel->setVisible(true);
		mWheelPanel->setPositionX(0);
		mWheelPanel->SetPlayCount(0);
		
	}
}

void SlotMachineBackPanel::SetSlotMachine()
{
#ifdef SLOT_WHEEL
	mWheelPanel->SetSlotMachine();
#endif	//SLOT_WHEEL
}
#endif

void SlotMachineBackPanel::aniEnd()
{
	mMoveAni = false;
}

