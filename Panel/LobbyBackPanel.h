/********************************************************************
file name:	LobbyBackPanel.h

purpose:	로비씬에서 바탕화면 ( 배경 + 캐릭터 위치값 )
*********************************************************************/
#pragma once
#include "NxFramework.h"

class LobbyBackPanel : public Panel
{
public:
	LobbyBackPanel();
	virtual ~LobbyBackPanel();

public:
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onEnter() override;
public:
	void InitPanel();
	void InitImage();
    void resume();
	virtual bool handling(STCMD &stCmd);
	void update(float dt);

	void MakeCharacter(int friendIdx, int _chracterId);
	void CharacterAction(int _idx);
	void CharacterIdleAction(int _idx);

	bool CharacterCollisionCheck(CCPoint _touchPoint);
public:
	SkelObject* m_pLobbyBackGround;	
};