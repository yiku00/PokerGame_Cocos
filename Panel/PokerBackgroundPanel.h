/********************************************************************
file name:	PokerBackgroundPanel.h

purpose:	기본 바닥에 캐릭터, 감정 표현창 버튼 , 등등 위치를 가지고있다.
*********************************************************************/
#pragma once
#include "NxFramework.h"

class PokerBackgroundPanel : public Panel, public SkelObject::Listener
{
	
public:
	PokerBackgroundPanel();
	virtual ~PokerBackgroundPanel();

public: // CCLayer
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

public:
	virtual void onAnimationStarted(const string& ani) {}
	virtual void onAnimationEnded(const string& ani);
	virtual void onEnter() override;
public:
	void setTotalBettingMoney(string bettingMoney);
	void setCallBettingMoney(string callMoney);

	void ShowBettingCardOnOffPannel();

	void MenuItemCallBack(CCObject* sender);

	//void TurnOnGetChip();
	//void TurnOffGetChip();

	void setVisibleCenterUI(bool _visible);

	void SetGameKindBoard(int _kind);
	void SetLastTableBoard();

	void ShowCenterBoxEffect(float _duration);
	void EndCenterBoxEffect();

	//void ShowLevelUpEffect();
	//void ShowMadeBonusEffect();
	//void ShowAutoRefillEffect();

	void setBadukiDayPanel(int _badukiDayType, bool _visible = true);
	void setMadeResult(int made);

	void setJackPotRewardPanel(string str);

	void setVibieCallBoard(bool visible);

	void refreshRoomNo();

private:
	void _intiPanel();
	void _initLabel();
	void _initImage();

	void initJackPotRewardPanel();
	
	void setActivateRoomNo(int roomId);
	void setDiactivateRoomNo();
	
private:
	Nx::Label* mBettingAmount;
	Nx::Label* mCallAmount;

public:
	Panel* m_DayPanel;
	//족보 이미지
	SkelObject* m_JokboBox;
	Nx::Label* m_JokboLabel[12];

	bool m_bCenterEffect;
	SkelObject* m_CenterBoxEffect;
	Button* m_pOptionButton;

	//SkelObject * m_Chip;
	//SkelObject* m_LevelupEffect;
	//SkelObject* m_MadeBonusEffect;
	//SkelObject* m_AutoRefillEffect;

	SkelObject* m_HoldemCommunityCard[5];
	SkelObject* m_HoldemCommunityCardEffect[5];
	SkelObject* m_HoldemCommunityCardEffectBack[5];
	SkelObject* m_HoldemCommunityCardSmoke[5];
	Button* m_HoldemCommunityCardButton;

	SkelObject* mPokerChip;
	SkelObject* mLimitedIcon;

	//잭팟 터텼을대 표시
	Panel* mJackPotRewardPanel;
	CCLabelBMFont* mTerm;
	SkelObject* mJackPotAni;

	Widget* mRoomNumberBg;
	Nx::Label* mRoomNumberTitle;
	Nx::Label* mRoomNumberSum;

	Widget* mRoomPasswardBg;
	Nx::Label* mRoomPassward;
	Nx::Label* mRoomPasswardBottom;
};