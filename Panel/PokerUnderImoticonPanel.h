/********************************************************************
file name:	PokerUnderImoticonPanel.h

purpose:	게임중 하단에 감정 표시하는 버튼 나열된 창 ( 슬픔 분노 사과 등)
*********************************************************************/
#pragma once
#include "NxFramework.h"
enum ImoticonType
{
	EMOTI_SAD = 0,
	EMOTI_ANGRY,
	EMOTI_SORRY,
	EMOTI_COMPLI,
	EMOTI_SURPRISE,
	EMOTI_THANK,
};

class PokerUnderImoticonPanel : public Panel, public Button::Listener
{
public:
	PokerUnderImoticonPanel();
	virtual ~PokerUnderImoticonPanel();
	void InitPanel();
	void InitImage();
	void InitButton();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);
	virtual void onEnter() override;
	void update(float dt);
	void SetCharacterEmotion(int _imotiType);
	void ShowResultImoticon(bool _visible);
public:
	Button* m_imotiButton[6];
};
