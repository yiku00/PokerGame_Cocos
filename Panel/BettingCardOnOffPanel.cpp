#include "pch.h"
#include "BettingCardOnOffPanel.h"
#include "HeroUtil.h"
#include "RefDefine.h"
#include "PokerCardWidget.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

BettingCardOnOffPanel::BettingCardOnOffPanel()
{
	m_pCancelButton = nullptr;
	_initData();
	_setParentPanel();
	_initPanel();
	_initImage();
	_initTimeGauge();
	setButtonListener(this);
}

BettingCardOnOffPanel::~BettingCardOnOffPanel()
{
	//Release Check Complete
	if (mMainPanel)
		mMainPanel->removeAllChildren(); 
	
	removeAllChildren();
}
void BettingCardOnOffPanel::onClicked(const string& buttonName)
{
	if (!mTouchEnable)
		return;
	
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (mOnOffStep == CardOffOff) {
		onClickedOff(buttonName);
	}
	else if (mOnOffStep == CardOffOn) {
		onClickedOn(buttonName);
	}
}

void BettingCardOnOffPanel::onClickedOff(const string& buttonName)
{
	int selectedIndex = -1;
	if (buttonName == "sbtn_selectcard1") {
		mOnOffStep = CardOffOn;
		selectedIndex = nxExtractInt(buttonName, "sbtn_selectcard") - 1;
		mOffCardIndex = selectedIndex;
	}
	else if (buttonName == "sbtn_selectcard2") {
		mOnOffStep = CardOffOn;
		selectedIndex = nxExtractInt(buttonName, "sbtn_selectcard") - 1;
		mOffCardIndex = selectedIndex;
	}
	else if (buttonName == "sbtn_selectcard3") {
		mOnOffStep = CardOffOn;
		selectedIndex = nxExtractInt(buttonName, "sbtn_selectcard") - 1;
		mOffCardIndex = selectedIndex;
		
	}
	else if (buttonName == "sbtn_selectcard4") {
		mOnOffStep = CardOffOn;
		selectedIndex = nxExtractInt(buttonName, "sbtn_selectcard") - 1;
		mOffCardIndex = selectedIndex;
	}

	if (selectedIndex != -1)
	{
		int _playerIdx = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetMyPo();
		RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_playerIdx);
		mMainPanel->getLabel("txt_outfont")->setVisible(false);
		mMainPanel->getLabel("txt_openfont")->setVisible(true);
		_pPlayer->SelectOffCard(mOffCardIndex);
	}
}

void BettingCardOnOffPanel::onClickedOn(const string& buttonName)
{
	cout << "void BettingCardOnOffPanel::onClickedOn(const string& buttonName)" << endl;
	int selectedIndex = -1;
	if (buttonName == "sbtn_selectcard1") {
		selectedIndex = nxExtractInt(buttonName, "sbtn_selectcard") - 1;
		mOnCardIndex = selectedIndex;
	}
	else if (buttonName == "sbtn_selectcard2") {
		selectedIndex = nxExtractInt(buttonName, "sbtn_selectcard") - 1;
		mOnCardIndex = selectedIndex;
	}
	else if (buttonName == "sbtn_selectcard3") {
		selectedIndex = nxExtractInt(buttonName, "sbtn_selectcard") - 1;
		mOnCardIndex = selectedIndex;
	}
	else if (buttonName == "sbtn_selectcard4") {
		selectedIndex = nxExtractInt(buttonName, "sbtn_selectcard") - 1;
		mOnCardIndex = selectedIndex;
	}

	if (mOnCardIndex == mOffCardIndex)
	{
		mOnOffStep = CardOffOff;
		int _playerIdx = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetMyPo();
		RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_playerIdx);
		mMainPanel->getLabel("txt_outfont")->setVisible(true);
		mMainPanel->getLabel("txt_openfont")->setVisible(false);
		_pPlayer->SelectOffCard(mOffCardIndex, true);
		mOnCardIndex = -1;
		mOffCardIndex = -1;
		return;
	}

	if (mOnCardIndex != -1) {
		
		int _playerIdx = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetMyPo();
		RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_playerIdx);

		GameDataManager::getSingleton().GetGameRoomInfoPtr()->CardChoiceREQ(mOffCardIndex, mOnCardIndex);
		_pPlayer->SelectOnCard(mOffCardIndex, mOnCardIndex);

		ClosePanel();
	}
}

void BettingCardOnOffPanel::StartSetting()
{
	setVisible(true);
	setTouchEnable(true);	
	mMainPanel->getLabel("txt_outfont")->setVisible(true);
	mMainPanel->getLabel("txt_openfont")->setVisible(false);
	_makeCardPosition(true);
}

void BettingCardOnOffPanel::onUpdate(float dt)
{
	mElapsedTime += dt;
	if (mElapsedTime > GAME_CARD_CHOICE_TIME) {
		setTimeGauge(0);
		if (mOffCardIndex == -1 && mOnCardIndex == -1)
		{
			mOnCardIndex = 2;
			mOffCardIndex = 3;
		}
		else if (mOffCardIndex != -1)
		{
			if (mOffCardIndex == 0)
			{
				mOnCardIndex = 3;
			}
			else
			{
				mOnCardIndex = mOffCardIndex - 1;
			}			
		}
		int _playerIdx = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetMyPo();
		RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_playerIdx);
		_pPlayer->SelectOnCard(mOffCardIndex, mOnCardIndex);

		GameDataManager::getSingleton().GetGameRoomInfoPtr()->CardChoiceREQ(mOffCardIndex, mOnCardIndex);
		ClosePanel();
	}
	else
	{
		float _leftTime = (GAME_CARD_CHOICE_TIME - mElapsedTime) * 10.f;
		float _per = _leftTime / 100.f;
		setTimeGauge(_per);
	}
}

void BettingCardOnOffPanel::_initData()
{
	mParentPanel = nullptr;

	mElapsedTime = 0.f;
	//mGamePlayInterface = nullptr ;
	mInitCardNumbers.clear();
	//mCards.clear();

	mTouchEnable = false;
	mOnOffStep = CardOffOff;

	mOffCardIndex = -1;
	mOnCardIndex = -1;
}

void BettingCardOnOffPanel::_initPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		mMainPanel->construct(getMxmlPath() + "dmy_selectcard.mxml");
		addChild(mMainPanel);
		mMainPanel->release();
		CCSize contentsSize = mMainPanel->getDummy("dmy_selectcard").size;
		contentsSize.height -= 35;
		contentsSize.width += 10;
		mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		this->setPosition(mParentPanel->getImage("dmy_selectcard")->getPosition());
	}
}

void BettingCardOnOffPanel::_initImage()
{
	mMainPanel->getSkel("skel_selectcard")->setVisible(true);
	mMainPanel->getLabel("txt_outfont")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_openfont")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_outfont")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SELECT_DROP_CARD").c_str());
	mMainPanel->getLabel("txt_openfont")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SELECT_OPEN_CARD").c_str());
	mMainPanel->getLabel("txt_outfont")->setVisible(true);
	mMainPanel->getLabel("txt_openfont")->setVisible(false);

	mMainPanel->getButton("sbtn_selectcard1")->setVisible(false);
	mMainPanel->getButton("sbtn_selectcard2")->setVisible(false);
	mMainPanel->getButton("sbtn_selectcard3")->setVisible(false);
	mMainPanel->getButton("sbtn_selectcard4")->setVisible(false);

	mMainPanel->getButton("sbtn_unselectmark1")->setVisible(false);
	mMainPanel->getButton("sbtn_unselectmark2")->setVisible(false);
	mMainPanel->getButton("sbtn_unselectmark3")->setVisible(false);
	mMainPanel->getButton("sbtn_unselectmark4")->setVisible(false);

	mMainPanel->getButton("sbtn_selectcard1")->setListener(this);
	mMainPanel->getButton("sbtn_selectcard2")->setListener(this);
	mMainPanel->getButton("sbtn_selectcard3")->setListener(this);
	mMainPanel->getButton("sbtn_selectcard4")->setListener(this);

	/*mMainPanel->getButton("sbtn_selectcard1")->setPaused(true);
	mMainPanel->getButton("sbtn_selectcard2")->setPaused(true);
	mMainPanel->getButton("sbtn_selectcard3")->setPaused(true);
	mMainPanel->getButton("sbtn_selectcard4")->setPaused(true);*/

	if (m_pCancelButton == nullptr)
	{
		m_pCancelButton = new SkelObject();
		m_pCancelButton->setSkelAnim("ui/smallbutton_8888.json");
		m_pCancelButton->playAnimation("cancel_stay");
		m_pCancelButton->setVisible(false);
		LayerManager::getSingleton().getLayer("CardLayer")->addChild(m_pCancelButton, 15);
		m_pCancelButton->release();
	}
}

void BettingCardOnOffPanel::_initLabel()
{

}
void BettingCardOnOffPanel::_initTimeGauge()
{
	
}

void BettingCardOnOffPanel::_setParentPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("Background"));
}

void BettingCardOnOffPanel::_makeCardPosition(bool _state)
{

	if (m_pCancelButton)
	{
		if (_state == false)
		{
			m_pCancelButton->setVisible(false);
		}
	}

	GameRoomInfo* _pRoomInfo = GameDataManager::getSingleton().GetGameRoomInfoPtr();
	RoomUserData* _pUserData = _pRoomInfo->GetUserDataPtr(_pRoomInfo->GetMyPo());

	int _size = _pUserData->GetCardManager()->m_CardList.size();
	if (_size < 4 && _state == true)
	{
		setVisible(false);
		setTouchable(false);
		ClosePanel();
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SetIsSelectedCard();
		return;
	}


	if (_size > 4)
		_size = 4;

	for (int _i = 0; _i < _size; _i++)
	{
		PokerCardWidget* _pCard = _pUserData->GetCardManager()->m_CardList[_i]->m_pCard;
		SkelObject* _pSkelObj = _pUserData->GetCardManager()->m_CardList[_i]->m_pCard->GetCardSkelObj();
		CCPoint _moveTo;
		CCPoint _movePo = mMainPanel->getImage("sbtn_selectcard" + StringConverter::toString(_i + 1))->getPosition();
		
		_pCard->setVisible(true);
		_pCard->stopAllActions();
		_pCard->GetCardSkelObj()->stopAllActions();
		_pCard->GetCardSkelObj()->setScale(1.f);
		_pCard->GetCardSkelObj()->setRotation(0.f);
		_pCard->setScale(1.f);
		_pCard->SetCardIdx(_i);
		_pCard->setRotation(0.f);

		if (_state == true)
		{
			_pCard->stopAllActions();
			_moveTo = mMainPanel->getPosition() + getPosition() + _movePo;
			_pCard->Action_InitSelectCardPos(0.3f);
			_pUserData->GetCardManager()->ActionMoveCard(_i, _moveTo, 0.2f);
		}
		else
		{
			_moveTo = _pUserData->GetCardManager()->GetTableCardRect(_i).origin;
			//string _frameName = "cardfront_s" + StringConverter::toString(_i + 1) + "end";
			//_pSkelObj->playAnimation(_frameName);
			_pUserData->GetCardManager()->m_CardList[_i]->m_pCard->setRotation(0.f);
			_pUserData->GetCardManager()->m_CardList[_i]->m_pCard->setPosition(_moveTo);
			_pUserData->GetCardManager()->m_CardList[_i]->m_pCard->GetCardSkelObj()->playAnimation("cardfront");
		}
	}

	if (_state == true)
	{
		//mMainPanel->getSkel("skel_selectcard")->playAnimation("timestart");
		//mMainPanel->getSkel("skel_selectcard")->appendAnimation("timeend", false, false, 0.33f);
		_makeTimeGaugeFull();
		GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_CARDFLOP);
		GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TIMER, true, true);
	}	
}


void BettingCardOnOffPanel::_makeTimeGaugeFull()
{
	mMainPanel->getSkel("skel_timeline")->setVisible(true);
	float _scaleX = TIME_LINE_WIDTH_MAX / TIME_LINE_WIDTH;

	mMainPanel->getSkel("skel_timeline")->setPositionX(TIME_LINE_INIT_POSX + (TIME_LINE_WIDTH_MAX * 0.5f));
	mMainPanel->getSkel("skel_timeline")->setScaleX(_scaleX);
}

void BettingCardOnOffPanel::setTimeGauge(float _per)
{
	if (_per == 0.f)
	{
		mMainPanel->getSkel("skel_timeline")->setVisible(false);
		return;
	}

	mMainPanel->getSkel("skel_timeline")->setVisible(true);
	float _scaleX = TIME_LINE_WIDTH_MAX / TIME_LINE_WIDTH * _per;

	mMainPanel->getSkel("skel_timeline")->setPositionX(TIME_LINE_INIT_POSX + (TIME_LINE_WIDTH_MAX * 0.5f * _per));
	mMainPanel->getSkel("skel_timeline")->setScaleX(_scaleX);

}
//void BettingCardOnOffPanel::_refreshCards()
//{
//	GameRoomInfo* _pRoomInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
//	int _playerIdx = _pRoomInfo->m_MyPo;
//
//	//TODO : Ä«µå 
//}

void BettingCardOnOffPanel::ClosePanel()
{
	GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TIMER, false);
	//GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_CARDDEAL);
	GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_CARDDOWN);

	_makeCardPosition(false);

	setVisible(false);
	mElapsedTime = 0;

	_initData();
	setTouchEnable(false);
	//LayerManager::getSingletonPtr()->closeLayer(this);
}

void BettingCardOnOffPanel::ShowCancelBtn(int _idx, bool _show)
{
	if (_show == false)
	{
		m_pCancelButton->setVisible(false);
		return;
	}

	string _cancelBtnName = "sbtn_unselectmark" + StringConverter::toString(_idx + 1);
	CCPoint _pos = mMainPanel->getImage(_cancelBtnName)->getPosition() + mMainPanel->getPosition() + getPosition();
	m_pCancelButton->setPosition(_pos);
	m_pCancelButton->setVisible(true);
}
#include "PokerPlayerInfoMyPanel.h"
#include "PokerUserInfoPanel.h"
#include "PokerTopPanel.h"
void BettingCardOnOffPanel::setTouchEnable(bool touchEnable)
{
	mTouchEnable = touchEnable;
	setTouchable(mTouchEnable);
	
	for (auto e : GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetTopPanel()->getChildren())
	{
		auto q = dynamic_cast<PokerUserInfoPanel*>(e);
		if (q == nullptr)
			continue;

		q->setTouchable(!touchEnable);		
	}
	/*mMainPanel->getButton("sbtn_selectcard1")->setPaused(!touchEnable);
	mMainPanel->getButton("sbtn_selectcard2")->setPaused(!touchEnable);
	mMainPanel->getButton("sbtn_selectcard3")->setPaused(!touchEnable);
	mMainPanel->getButton("sbtn_selectcard4")->setPaused(!touchEnable);*/
}
