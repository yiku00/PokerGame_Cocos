#include "pch.h"
#include "SynopsisMainPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
//#include "SimplePopupPanel.h"
//#include "HeroApp.h"

#include "Web/WebService.h"
#include "SynopsisCharacterInfoPanel.h"
#include "PokerResourceHelper.h"

SynopsisMainPanel::SynopsisMainPanel()
{
	

	m_Process = false;
	m_selectId = 0;

	InitPanel();
	MakeCharacter();
	ShowCharacter(false);
	setTouchable(false);	
	setButtonListener(this);
}

SynopsisMainPanel::~SynopsisMainPanel()
{
	//destruct();
}

void SynopsisMainPanel::InitPanel()
{
	construct(getMxmlPath() + "synopsis_back.mxml");

	m_dealerPos = getDummy("dmy_dealer").origin;
	m_charaterPos[0] = getDummy("dmy_character1").origin;
	m_charaterPos[1] = getDummy("dmy_character2").origin;
	m_charaterPos[2] = getDummy("dmy_character4").origin;
	m_charaterPos[3] = getDummy("dmy_character3").origin;
	m_charaterPos[4] = getDummy("dmy_dealer").origin;
	mBackGround = getSkel("skel_black");	
	mBackGround->setZOrder(7);
	setBackGroundVisible(false);
}

void SynopsisMainPanel::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void SynopsisMainPanel::onClicked(const string& name)
{
	if (m_Process)
		return;

	//if (name == "sbtn_gameout")
	//{
	//	SceneUtil::changeScene(SceneUtil::SceneLobby);
	//}
}

void SynopsisMainPanel::update(float dt)
{

}

bool SynopsisMainPanel::handling(STCMD &stCmd)
{
	if (!m_Process)
		return false;

	return false;
}

void SynopsisMainPanel::onKeypadKeyPressed(EventKeyboard::KeyCode  keyCode, Event* /*event*/)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		HeroApp::getSingleton().exit();
		return;
		if (SceneManager::getSingletonPtr()->isChanging())
			return;

		//SceneUtil::changeScene(SceneUtil::SceneLogo);
	}
}

void SynopsisMainPanel::MakeCharacter()
{
	int _index = 0;
	//int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata_size();
	//for (int _i = 0; _i < _size; _i++)
	//{
	//	W_CharacterData _Info = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata(_i);
	//	if (_Info.isbase())
	//	{
	//		m_characterId[_index] = _Info.id();
	//		_index++;

	//		if (_index > 4)
	//			break;
	//	}
	//}
	m_characterId[0] = CharaterType::SANTIAGO;
	m_characterId[1] = CharaterType::CHRISTINA;
	m_characterId[2] = CharaterType::ALEXANDER;
	m_characterId[3] = CharaterType::BLACKROSE;
	m_characterId[4] = 0;

	for (int _i = 0; _i < 5; _i++)
	{
		setCharacter(_i, m_characterId[_i]);
	}

	setCharacterDepth(0, 4);
	setCharacterDepth(1, 2);
	setCharacterDepth(2, 1);
	setCharacterDepth(3, 2);

	setCharacterDepth(4, 4);

}

float SynopsisMainPanel::getCharacterScale(int _depth)
{
	switch (_depth)
	{
	case 1:
		return 0.4f;
		break;
	case 2:
		return  0.65f;
		break;
	case 3:
		return  1.f;
		break;
	}
	return 1.f;
}

void SynopsisMainPanel::setCharacterDepth(int _idx, int _depth)
{
	int _zOrderTop = (_depth * 2) + 1;
	int _zOrderUnder = _depth * 2;
	
	float _Scale = getCharacterScale(_depth);

	m_characterTop[_idx]->setZOrder(_zOrderTop);
	m_characterUnder[_idx]->setZOrder(_zOrderUnder);

	m_characterTop[_idx]->setScale(_Scale);
	m_characterUnder[_idx]->setScale(_Scale);
}

void SynopsisMainPanel::setCharacterPositionToDummyPos(int _idx, CCPoint _pos)
{
	m_characterTop[_idx]->setPositionX(_pos.x);
	m_characterTop[_idx]->setPositionY(DESIGN_HEIGHT-_pos.y);

	m_characterUnder[_idx]->setPositionX(_pos.x);
	m_characterUnder[_idx]->setPositionY(DESIGN_HEIGHT - _pos.y);

	mShadow[_idx]->setPositionX(_pos.x);
	mShadow[_idx]->setPositionY(DESIGN_HEIGHT - _pos.y);
}

void SynopsisMainPanel::setCharacter(int idx, int _type)
{
	m_characterTop[idx] = new SkelObject();
	m_characterUnder[idx] = new SkelObject();
	mShadow[idx] = new SkelObject();
	mShadow[idx]->setSkelAnim("ui/character_shadow_8888.json");
	mShadow[idx]->playAnimation("height_32");
	if (idx == 4)
	{
		m_characterTop[4]->setSkelAnim(PokerResourceHelper::getDealerOverSpineName());
		m_characterUnder[4]->setSkelAnim(PokerResourceHelper::getDealerUnderSpineName());
		m_characterTop[4]->playAnimation("idle", true);
		m_characterUnder[4]->playAnimation("idle", true);
		setCharacterPositionToDummyPos(4, m_charaterPos[4]);
		addChild(m_characterUnder[4]);
		addChild(m_characterTop[4]);
		m_characterTop[4]->release();
		m_characterUnder[4]->release();
		return;
	}

	m_characterTop[idx]->setSkelAnim(PokerResourceHelper::getCharacterOverSpineName(_type));
	m_characterUnder[idx]->setSkelAnim(PokerResourceHelper::getCharacterUnderSpineName(_type));
	
	PlayCharacterAnimation(idx, IDLE_STAND);
	setCharacterPositionToDummyPos(idx, m_charaterPos[idx]);

	addChild(m_characterUnder[idx]);
	addChild(m_characterTop[idx]);
	addChild(mShadow[idx]);

	m_characterTop[idx]->release();
	m_characterUnder[idx]->release();
	mShadow[idx]->release();
}

void SynopsisMainPanel::PlayCharacterAnimation(int _idx, int _kind)
{
	if (_idx > 3)
		return;

	switch (_kind)
	{
	case RESULT_ALLIN:
		m_characterTop[_idx]->playAnimation("bankrupt_ready");
		m_characterTop[_idx]->appendAnimation("bankrupt_loop", true);
		m_characterUnder[_idx]->playAnimation("bankrupt_ready");
		m_characterUnder[_idx]->appendAnimation("bankrupt_loop", true);
		break;
	case BET_BBING:
		m_characterTop[_idx]->playAnimation("bet_bbing");
		m_characterTop[_idx]->appendAnimation("idle", true);
		m_characterUnder[_idx]->playAnimation("bet_bbing");
		m_characterUnder[_idx]->appendAnimation("idle", true);
		break;
	case BET_BIGFOLD:
		m_characterTop[_idx]->playAnimation("bet_bigfold");
		m_characterTop[_idx]->appendAnimation("idle", true);
		m_characterUnder[_idx]->playAnimation("bet_bigfold");
		m_characterUnder[_idx]->appendAnimation("idle", true);
		break;
	case BET_BIG_RAISE:
		m_characterTop[_idx]->playAnimation("bet_bigraise");
		m_characterTop[_idx]->appendAnimation("idle", true);
		m_characterUnder[_idx]->playAnimation("bet_bigraise");
		m_characterUnder[_idx]->appendAnimation("idle", true);
		break;
	case BET_CHECK:
		m_characterTop[_idx]->playAnimation("bet_check");
		m_characterTop[_idx]->appendAnimation("idle", true);
		m_characterUnder[_idx]->playAnimation("bet_check");
		m_characterUnder[_idx]->appendAnimation("idle", true);
		break;
	case BET_RAISE:
		m_characterTop[_idx]->playAnimation("bet_raise");
		m_characterTop[_idx]->appendAnimation("idle", true);
		m_characterUnder[_idx]->playAnimation("bet_raise");
		m_characterUnder[_idx]->appendAnimation("idle", true);
		break;
	case DIE_ACT:
		m_characterTop[_idx]->playAnimation("die_act");
		m_characterTop[_idx]->appendAnimation("die_idle_loop", true);
		m_characterUnder[_idx]->playAnimation("die_act");
		m_characterUnder[_idx]->appendAnimation("die_idle_loop", true);
		break;
	case DIE_IDLE:
		m_characterTop[_idx]->playAnimation("die_idle_ready");
		m_characterTop[_idx]->appendAnimation("die_idle_loop", true);
		m_characterUnder[_idx]->playAnimation("die_idle_ready");
		m_characterUnder[_idx]->appendAnimation("die_idle_loop", true);
		break;
	case GESTURE_ANGRY:
		m_characterTop[_idx]->playAnimation("gesture_angry");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_angry");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case GESTURE_CELEBRATE:
		m_characterTop[_idx]->playAnimation("gesture_celebrate");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_celebrate");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case GESTURE_GOOD:
		m_characterTop[_idx]->playAnimation("gesture_good");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_good");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case GESTURE_HURRY:
		m_characterTop[_idx]->playAnimation("gesture_hurry");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_hurry");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case GESTURE_LAUGH:
		m_characterTop[_idx]->playAnimation("gesture_laugh");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_laugh");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case GESTURE_PLEASURE:
		m_characterTop[_idx]->playAnimation("gesture_pleasure");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_pleasure");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case GESTURE_SADNESS:
		m_characterTop[_idx]->playAnimation("gesture_sadness");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_sadness");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case GESTURE_SORRY:
		m_characterTop[_idx]->playAnimation("gesture_sorry");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_sorry");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case GESTURE_SURPRIZE:
		m_characterTop[_idx]->playAnimation("gesture_surprize");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_surprize");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case GESTURE_THANKS:
		m_characterTop[_idx]->playAnimation("gesture_thanks");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("gesture_thanks");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case IDLE:
		m_characterTop[_idx]->playAnimation("idle", true);
		m_characterUnder[_idx]->playAnimation("idle", true);
		break;
	case IDLE_ACT1:
		m_characterTop[_idx]->playAnimation("idle1");
		m_characterTop[_idx]->appendAnimation("idle", true);
		m_characterUnder[_idx]->playAnimation("idle1");
		m_characterUnder[_idx]->appendAnimation("idle", true);
		break;
	case IDLE_ACT2:
		m_characterTop[_idx]->playAnimation("idle2");
		m_characterTop[_idx]->appendAnimation("idle", true);
		m_characterUnder[_idx]->playAnimation("idle2");
		m_characterUnder[_idx]->appendAnimation("idle", true);
		break;
	case IDLE_STAND:
		m_characterTop[_idx]->playAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("idle_stand", true);
		break;
	case IDLE_STAND_ACT1:
		m_characterTop[_idx]->playAnimation("idle1");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("idle1");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case IDLE_STAND_ACT2:
		m_characterTop[_idx]->playAnimation("idle2");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("idle2");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case LOSE_BIG:
		m_characterTop[_idx]->playAnimation("lose_big_ready");
		m_characterTop[_idx]->appendAnimation("lose_big_loop", true);
		m_characterUnder[_idx]->playAnimation("lose_big_ready");
		m_characterUnder[_idx]->appendAnimation("lose_big_loop", true);
		break;
	case LOSE_SMALL:
		m_characterTop[_idx]->playAnimation("lose_small_ready");
		m_characterTop[_idx]->appendAnimation("lose_small_loop", true);
		m_characterUnder[_idx]->playAnimation("lose_small_ready");
		m_characterUnder[_idx]->appendAnimation("lose_small_loop", true);
		break;
	case REACT_MADE:
		m_characterTop[_idx]->playAnimation("react_made");
		m_characterTop[_idx]->appendAnimation("idle_stand", true);
		m_characterUnder[_idx]->playAnimation("react_made");
		m_characterUnder[_idx]->appendAnimation("idle_stand", true);
		break;
	case THINK1:
		m_characterTop[_idx]->appendAnimation("think1_ready");
		m_characterTop[_idx]->appendAnimation("think1_loop", true);
		m_characterUnder[_idx]->appendAnimation("think1_ready");
		m_characterUnder[_idx]->appendAnimation("think1_loop", true);
		break;
	case THINK2:
		m_characterTop[_idx]->appendAnimation("think2_ready");
		m_characterTop[_idx]->appendAnimation("think2_loop", true);
		m_characterUnder[_idx]->appendAnimation("think2_ready");
		m_characterUnder[_idx]->appendAnimation("think2_loop", true);
		break;
	case WIN_BIG:
		m_characterTop[_idx]->playAnimation("win_big_ready");
		m_characterTop[_idx]->appendAnimation("win_big_loop", true);
		m_characterUnder[_idx]->playAnimation("win_big_ready");
		m_characterUnder[_idx]->appendAnimation("win_big_loop", true);
		break;
	case WIN_SMALL:
		m_characterTop[_idx]->playAnimation("win_small_ready");
		m_characterTop[_idx]->appendAnimation("win_small_loop", true);
		m_characterUnder[_idx]->playAnimation("win_small_ready");
		m_characterUnder[_idx]->appendAnimation("win_small_loop", true);
		break;
	}
}

void SynopsisMainPanel::ShowDealer(bool _visible)
{
	m_characterTop[4]->setVisible(_visible);
	m_characterUnder[4]->setVisible(_visible);
}

void SynopsisMainPanel::ShowCharacter(bool _visible)
{
	for (int _i = 0; _i < 4; _i++)
	{
		m_characterTop[_i]->setVisible(_visible);
		m_characterUnder[_i]->setVisible(_visible);
	}
}

void SynopsisMainPanel::CharacterLeftMove()
{
	if (m_Process)
		return;

	m_Process = true;

	int _index = m_selectId;
	int _moveIndex = 1;
	for (int _i = 0; _i < 4; _i++)
	{
		if (_moveIndex > 3)
			_moveIndex = 0;
		if (_index > 3)
			_index = 0;

		CCPoint _movePos = m_charaterPos[_moveIndex];
		_movePos.y = DESIGN_HEIGHT - _movePos.y;

		int _depth = 3;
		if (_moveIndex == 1 || _moveIndex == 3)
		{
			_depth = 2;
		}
		else if (_moveIndex == 2)
		{
			_depth = 1;
		}
		int _zOrderTop = (_depth * 2) + 1;
		int _zOrderUnder = _depth * 2;

		float _Scale = getCharacterScale(_depth);

		m_characterTop[_index]->runAction(CCSequence::createWithTwoActions(
			CCMoveTo::create(0.2f, _movePos),
			CCCallFunc::create(this, callfunc_selector(SynopsisMainPanel::CharacterMoveEnd))
			));
		m_characterUnder[_index]->runAction(CCMoveTo::create(0.2f, _movePos));
		mShadow[_index]->runAction(CCMoveTo::create(0.2f, _movePos));

		m_characterTop[_index]->runAction(CCScaleTo::create(0.2f, _Scale));
		m_characterUnder[_index]->runAction(CCScaleTo::create(0.2f, _Scale));
		mShadow[_index]->runAction(CCScaleTo::create(0.2f, _Scale));

		_index++;
		_moveIndex++;
	}

	m_selectId--;
	if (m_selectId < 0)
		m_selectId = 3;

}

void SynopsisMainPanel::CharacterRightMove()
{
	if (m_Process)
		return;

	m_Process = true;

	int _index = m_selectId;
	int _moveIndex = 3;
	for (int _i = 0; _i < 4; _i++)
	{
		if (_moveIndex < 0)
			_moveIndex = 3;
		if (_index < 0)
			_index = 3;

		CCPoint _movePos = m_charaterPos[_moveIndex];
		_movePos.y = DESIGN_HEIGHT - _movePos.y;

		int _depth = 3;
		if (_moveIndex == 1 || _moveIndex == 3)
		{
			_depth = 2;
		}
		else if (_moveIndex == 2)
		{
			_depth = 1;
		}
		int _zOrderTop = (_depth * 2) + 1;
		int _zOrderUnder = _depth * 2;

		float _Scale = getCharacterScale(_depth);

		m_characterTop[_index]->runAction(CCSequence::createWithTwoActions(
			CCMoveTo::create(0.2f, _movePos),
			CCCallFunc::create(this, callfunc_selector(SynopsisMainPanel::CharacterMoveEnd))
			));
		m_characterUnder[_index]->runAction(CCMoveTo::create(0.2f, _movePos));
		mShadow[_index]->runAction(CCMoveTo::create(0.2f, _movePos));

		m_characterTop[_index]->runAction(CCScaleTo::create(0.2f, _Scale));
		m_characterUnder[_index]->runAction(CCScaleTo::create(0.2f, _Scale));
		mShadow[_index]->runAction(CCScaleTo::create(0.2f, _Scale));

		_index--;
		_moveIndex--;
	}

	m_selectId++;
	if (m_selectId > 3)
		m_selectId = 0;
}

void SynopsisMainPanel::CharacterMoveEnd()
{
	m_Process = false;

	int _index = m_selectId;
	setCharacterDepth(_index, 4);
	PlayCharacterAnimation(_index, WIN_SMALL);

	_index++;
	if (_index > 3)
		_index = 0;
	setCharacterDepth(_index, 2);
	PlayCharacterAnimation(_index, IDLE_STAND);

	_index++;
	if (_index > 3)
		_index = 0;
	setCharacterDepth(_index, 1);
	PlayCharacterAnimation(_index, IDLE_STAND);

	_index++;
	if (_index > 3)
		_index = 0;
	setCharacterDepth(_index, 2);
	PlayCharacterAnimation(_index, IDLE_STAND);

	if (LayerManager::getSingletonPtr()->hasLayer("Information"))
	{
		SynopsisCharacterInfoPanel* _pInfoPanel = dynamic_cast<SynopsisCharacterInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("Information"));
		int _id = m_characterId[m_selectId];
		_pInfoPanel->ShowInfo(true, _id);

	}
}

void SynopsisMainPanel::CharacterMove(float _x)
{
	CCPoint _pPos = m_charaterPos[0];
	_pPos.x += _x;
	_pPos.y = DESIGN_HEIGHT - _pPos.y;

	m_characterTop[m_selectId]->setPosition(_pPos);
	m_characterUnder[m_selectId]->setPosition(_pPos);
}

void SynopsisMainPanel::setBackGroundVisible(bool visible)
{
	mBackGround->setVisible(visible);
}

void SynopsisMainPanel::setBackGroundStart()
{
	mBackGround->setVisible(true);
	mBackGround->playAnimation("synopsis_black_start");
	mBackGround->appendAnimation("synopsis_black_stay" , true);
}

void SynopsisMainPanel::setBackGroundEnd()
{
	mBackGround->playAnimation("synopsis_black_end");
}
void SynopsisMainPanel::onEnter()
{
	Panel::onEnter();

	setKeypadEnabled(true);
	scheduleUpdate();
}