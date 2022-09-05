#pragma once

#include "NxFramework.h"

class SynopsisMainPanel : public Panel, public Button::Listener
{
public:
	SynopsisMainPanel();
	virtual ~SynopsisMainPanel();

public:
	void InitPanel();
// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onKeypadKeyPressed(EventKeyboard::KeyCode  keyCode, Event* /*event*/);
	virtual bool handling(STCMD &stCmd);

	void OnMessage(int type, void* _msg, int parm1 = 0, int parm2 = 0);
	void update(float dt);
	virtual void onEnter() override;
	void MakeCharacter();
	void setCharacter(int idx, int _type);
	void setCharacterPositionToDummyPos(int _idx, CCPoint _pos);
	void PlayCharacterAnimation(int _idx, int _kind);
	void setCharacterDepth(int _idx, int _depth);
	float getCharacterScale(int _depth);

	void ShowDealer(bool _visible);
	void ShowCharacter(bool _visible);

	void CharacterLeftMove();
	void CharacterRightMove();
	void CharacterMoveEnd();
	void CharacterMove(float _x);

	void setBackGroundVisible(bool visible);		//배경 쓰냐 안 쓰냐
	void setBackGroundStart();
	void setBackGroundEnd();
public:
	bool m_Process;
	bool m_GamePlaying;

	CCPoint m_dealerPos;

	int m_characterId[5];
	CCPoint m_charaterPos[5];
	SkelObject* m_characterTop[5];
	SkelObject* m_characterUnder[5];
	SkelObject* mShadow[5];

	int m_selectId;
	SkelObject* mBackGround;
};
