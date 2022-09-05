#include "pch.h"
#include "LobbySurvivalCell.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"

LobbySurvivalCell::LobbySurvivalCell()
{
	m_CellInfo = nullptr;

	InitPanel();
	InitImage();
	initButton();

	setTouchable(false);
	setButtonListener(this);
}

LobbySurvivalCell::~LobbySurvivalCell()
{
	if (m_CellInfo)
	{
		NX_SAFE_DELETE(m_CellInfo);
		m_CellInfo = nullptr;
	}
}

void LobbySurvivalCell::InitPanel()
{
	construct(getMxmlPath() + "dmy_survival_button.mxml");
}

void LobbySurvivalCell::InitImage()
{
	m_labelTitle = getLabel("txt_tournament_title");
	m_labelGift = getLabel("txt_gift");
	m_labelGold = getLabel("txt_gold_sum");
	m_labelEnter = getLabel("txt_state");
	m_labelEnterCount = getLabel("txt_state_sum");

	m_labelTitle->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_labelGift->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_labelGold->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_labelEnter->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_labelEnterCount->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	string _giftTxt = GameStringDepot::getSingletonPtr()->getString("TXT_WINNER_GIFT");
	m_labelGift->setString(_giftTxt.c_str());
	string _enterTxt = GameStringDepot::getSingletonPtr()->getString("TXT_REGISTATION_LABEL");
	m_labelEnter->setString(_enterTxt.c_str());

	getSkel("skel_lock")->setVisible(false);
}

void LobbySurvivalCell::initButton()
{
	m_btnChannel = getButton("sbtn_survival_button");
	m_btnChannel->setPaused(true);
	m_btnChannel->setType(Button::ButtonType::NoPressImg);
}


bool LobbySurvivalCell::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	
	return false;
}


void LobbySurvivalCell::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void LobbySurvivalCell::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbySurvivalCell::resume()
{
}

void LobbySurvivalCell::onClicked(const string& name)
{
	if (name == "sbtn_button")
	{
		return;
	}
}

void LobbySurvivalCell::update(float dt)
{
}

bool LobbySurvivalCell::handling(STCMD &stCmd)
{
	return false;
}

void LobbySurvivalCell::SetCellData(int _index)
{
	int _size = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo_size();

	if (_size <= _index)
		return;

	if (m_CellInfo)
	{
		NX_SAFE_DELETE(m_CellInfo);
		m_CellInfo = nullptr;
	}

	m_CellInfo = new W_DeathMatchInfo(GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->matchinfo(_index));
	SetTitleString(m_CellInfo->name());


	//Final Reward 
	if (m_CellInfo->has_finalrewardinfo())
	{
		W_RewardInfo _Rewardinfo = m_CellInfo->finalrewardinfo();
		int _size = _Rewardinfo.rewardset_size();

		for (int _i = 0; _i < _size; _i++)
		{
			W_RewardInfo_RewardSet _reward = _Rewardinfo.rewardset(_i);
			switch (_reward.type())
			{
			case eResourceType::CASH:
				break;
			case eResourceType::GAMEMONEY:
			{
				std::string _gold = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_reward.amount()), 1);
				m_labelGold->setString(_gold.c_str());
				break;
			}
			case eResourceType::CHIP:
				break;
			}
		}
	}

	std::string _gold = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(m_CellInfo->joinmoney()), 1);
	m_labelGold->setString(_gold.c_str());

	int _registCount = m_CellInfo->registercnt();
	int _registMax = m_CellInfo->registermax();
	std::string _registTxt = StringConverter::toString(_registCount) + "/" + StringConverter::toString(_registMax);
	m_labelEnterCount->setString(_registTxt.c_str());

	string _frameName1 = "";
	string _frameName2 = "";
	switch (m_CellInfo->gamekind())
	{
	case GameKind::GAMEKIND_7POKER:
		_frameName1 = "seven_";
		_frameName2 = "lock_saven";
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_frameName1 = "highlow_";
		_frameName2 = "lock_highlow";
		break;
	case GameKind::GAMEKIND_BADUKI:
		_frameName1 = "badugi_";
		_frameName2 = "lock_badugi";
		break;
	case GameKind::GAMEKIND_HOLDEM:
		_frameName1 = "texas_";
		_frameName2 = "lock_texas";
		break;
	}

	if (m_btnChannel->isEnabled())
	{
		getSkel("skel_lock")->setVisible(false);
		_frameName1 += "stay";
	}
	else
	{
		getSkel("skel_lock")->setVisible(true);
		_frameName1 += "stayoff";
	}

	m_btnChannel->getButtonSkelObject()->playAnimation(_frameName1, true);
	getSkel("skel_lock")->playAnimation(_frameName2);

	m_btnChannel->setTag(_index);

	//if (getButton("sbtn_button")->isEnabled() == false)
	//{
	//	getButton("sbtn_button")->getButtonSkelObject()->setSkin("channel_off");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_7POKER)
	//{
	//	getButton("sbtn_button")->getButtonSkelObject()->setSkin("seven_poker");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_HIGH_LOW)
	//{
	//	getButton("sbtn_button")->getButtonSkelObject()->setSkin("highlow");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_BADUKI)
	//{
	//	getButton("sbtn_button")->getButtonSkelObject()->setSkin("badugi");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_HOLDEM)
	//{
	//	getButton("sbtn_button")->getButtonSkelObject()->setSkin("texasholdem");
	//}

	//if (getButton("sbtn_button")->isEnabled() == false)
	//{
	//	getButton("sbtn_button")->getButtonSkelObject()->playAnimation("normal_off");
	//}
	//else
	//{
	//	//string _skinName;
	//	//normal_boff : 패널은 활성화된상태로 버튼만 off
	//	//normal_bon: 버튼 파란색
	//	//normal_gon : 버튼 노란색
	//	//normal_stay : 버튼 일반색 활성화
	//	//normal_off : 패널전체 오프
	//	getButton("sbtn_button")->getButtonSkelObject()->playAnimation("normal_stay");
	//}

	///*
	//switch (m_CellInfo->userstatus())
	//{
	//case W_DeathMatchInfo_eUserStatus_eNot:
	//	SetOffButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_RESIST_OVER"));
	//	break;
	//case W_DeathMatchInfo_eUserStatus_eRegister:
	//case W_DeathMatchInfo_eUserStatus_eWait:
	//case W_DeathMatchInfo_eUserStatus_eGame:
	//{
	//	int _registCount = m_CellInfo->registercnt();
	//	int _registMax = m_CellInfo->registermax();
	//	std::string _registTxt = "[" + StringConverter::toString(_registCount);
	//	_registTxt += "/" + StringConverter::toString(_registMax) + "]";
	//	SetButtonString(_registTxt);
	//	break;
	//}
	//default:
	//	break;
	//}
	//*/
	//
	//// 등록 기간중일때
	//if (m_CellInfo->isregistertime())
	//{
	//	// 참여한적 없을때
	//	if (m_CellInfo->isregister() == false)
	//	{
	//		//TXT_REGISTATION_LABEL
	//		int _registCount = m_CellInfo->registercnt();
	//		int _registMax = m_CellInfo->registermax();
	//		std::string _registTxt = GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_CAN_JOIN") + "[" + StringConverter::toString(_registCount);
	//		_registTxt += "/" + StringConverter::toString(_registMax) + "]";
	//		SetButtonString(_registTxt, ENABLE);
	//	}
	//	// 참여했을 때
	//	else
	//	{
	//		//TXT_RESIST_COMPLETE
	//		SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_RESIST_COMPLETE"), HIGHLIGHT1);
	//	}
	//}
	//// 대기중일때
	//else if (m_CellInfo->matchstatus() == W_DeathMatchInfo_eMatchStatus_eGameWait)
	//{
	//	// 참여한적 없을때
	//	if (m_CellInfo->isregister() == false)
	//	{
	//		SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_DETAIL_VIEW"), DISABLE);
	//	}
	//	// 참여했을때
	//	else
	//	{
	//		SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_ENTER"), HIGHLIGHT2);
	//	}
	//}
	//// 게임 중일때
	//else if (m_CellInfo->matchstatus() == W_DeathMatchInfo_eMatchStatus_eGameIng)
	//{
	//	// 참여한적 없을때
	//	if (m_CellInfo->isregister() == false)
	//	{
	//		SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_DETAIL_VIEW"), DISABLE);
	//	}
	//	// 참여했을 때
	//	else
	//	{
	//		// 아직 개인이 게임중일때
	//		if (m_CellInfo->userstatus() == W_DeathMatchInfo_eUserStatus_eGame)
	//			SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_ENTER"), HIGHLIGHT2);
	//		// 내 게임은 끝났을 때
	//		else
	//			SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_DETAIL_VIEW"), DISABLE);
	//	}
	//	
	//}
	//else
	//{
	//	// 등록 안한 사람이면
	//	if (m_CellInfo->isregister() == false)
	//		SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_DETAIL_VIEW"), DISABLE);
	//	// 등록 한 사람
	//	else
	//	{
	//		// 게임 끝났으면 상세보기
	//		if (m_CellInfo->matchstatus() == W_DeathMatchInfo_eMatchStatus_eGameEnd)
	//			SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_DETAIL_VIEW"), DISABLE);
	//		// 디스플레이 타임 (등록 시간은 남아 잇으나, 등록시간이 안되었을때
	//		else if (m_CellInfo->registerabletime() > 0)
	//			SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_DETAIL_VIEW"), DISABLE);
	//		// 웨이트 타임 전이면서 등록은 완료되었을 때 
	//		else if (m_CellInfo->waitabletime() > 0)
	//			SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_RESIST_COMPLETE"), HIGHLIGHT1);
	//		// 게임 진행전이면서 대기 상태인경우
	//		else if (m_CellInfo->gameabletime() > 0)
	//			SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_RESIST_COMPLETE"), HIGHLIGHT1);
	//		// 그외 모두
	//		else
	//			SetButtonString(GameStringDepot::getSingletonPtr()->getString("TXT_DETAIL_VIEW"), DISABLE);
	//	}
	//}

	//W_DeathMatchInfo::eMatchStatus _status = m_CellInfo->matchstatus();
	//string upperStr = "";
	//switch (_status)
	//{
	//	case W_DeathMatchInfo_eMatchStatus_eGameEnd:
	//		upperStr = m_CellInfo->desc() + "(" + GameStringDepot::getSingletonPtr()->getString("TXT_GAME_END_LABEL") + ")";
	//		getLabel("txt_time_limit")->setString(upperStr.c_str());
	//		break;
	//	case W_DeathMatchInfo_eMatchStatus_eGameIng:
	//		upperStr = GameStringDepot::getSingletonPtr()->getString("TXT_DURING_LABEL");
	//		if (m_CellInfo->isregister())
	//			upperStr += " (" + GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_JOIN") + ")";
	//		else
	//			upperStr += " (" + GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_NOT_JOIN") + ")";
	//		getLabel("txt_time_limit")->setString(upperStr.c_str());
	//		break;
	//	default :
	//		upperStr = m_CellInfo->desc() + " " + GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_START") + "";
	//		getLabel("txt_time_limit")->setString(upperStr.c_str());
	//		break;
	//}
	//
	////Final Reward 
	//if (m_CellInfo->has_finalrewardinfo())
	//{
	//	W_RewardInfo _Rewardinfo = m_CellInfo->finalrewardinfo();
	//	int _size = _Rewardinfo.rewardset_size();

	//	for (int _i = 0; _i < _size; _i++)
	//	{
	//		W_RewardInfo_RewardSet _reward = _Rewardinfo.rewardset(_i);
	//		if (_reward.type() == eResourceType::CASH)
	//		{
	//			getSkel("skel_icon_gold");
	//		}
	//		else if (_reward.type() == eResourceType::GAMEMONEY)
	//		{
	//			getSkel("skel_icon_gold");
	//			std::string _gold = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_reward.amount()), 1);
	//			getLabel("str_gold_sum")->setString(_gold.c_str());

	//		}
	//		else if (_reward.type() == eResourceType::CHIP)
	//		{
	//			getSkel("skel_icon_gold");
	//		}
	//	}
	//}

	
}

void LobbySurvivalCell::SetOffButtonString(std::string _txt)
{
	//getLabel("txt_button_gon_under")->setVisible(false);
	//getLabel("txt_button_gon")->setVisible(false);
	//getLabel("txt_button_stay_under")->setVisible(true);
	//getLabel("txt_button_stay")->setVisible(true);
	//getLabel("txt_button_stay_under")->setString(_txt.c_str());
	//getLabel("txt_button_stay")->setString(_txt.c_str());
}

void LobbySurvivalCell::SetButtonString(std::string _txt, SURVIVAL_BUTTON_KIND btnKind)
{
	/*getLabel("txt_button_stay_under")->setVisible(false);
	getLabel("txt_button_stay")->setVisible(false);
	getLabel("txt_button_gon_under")->setVisible(true);
	getLabel("txt_button_gon")->setVisible(true);

	ccColor3B _color;
	
	switch (btnKind)
	{
		case DISABLE :
			_color.r = 133;
			_color.g = 133;
			_color.b = 133;
			getButton("sbtn_button")->setSkelAnimation("normal_boff");
			break;
		case ENABLE :
			_color.r = 255;
			_color.g = 216;
			_color.b = 133;
			getButton("sbtn_button")->setSkelAnimation("normal_stay");
			break;
		case HIGHLIGHT1 :
			_color.r = 255;
			_color.g = 240;
			_color.b = 159;
			getButton("sbtn_button")->setSkelAnimation("normal_gon");
			break;
		case HIGHLIGHT2 :
			_color.r = 255;
			_color.g = 235;
			_color.b = 221;
			getButton("sbtn_button")->setSkelAnimation("normal_ron");
			break;
	}

	getLabel("txt_button_gon")->setColor(_color);

	getLabel("txt_button_gon_under")->setString(_txt.c_str());
	getLabel("txt_button_gon")->setString(_txt.c_str());*/
}

void LobbySurvivalCell::SetTitleString(std::string _txt)
{
	getLabel("txt_tournament_title")->setString(_txt.c_str());
}
