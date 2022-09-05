/********************************************************************
file name:	emoticonPanel.h

purpose:	감정 표시 버튼 누르는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "HeroUtil.h"

class sButton : public Button
{
public:
	SkelObject* getSkelObject() { return mSkel; }
	bool setSkelSkin(const string& skinName) { return mSkel->setSkin(skinName); }
};

class emoticonPanel : public Panel, SkelObject::Listener, Button::Listener
{
public:
	emoticonPanel();
	~emoticonPanel();
	void Init();
	void InitImage();

	void SetVisiebleEmotiWindow(bool _visible);

	virtual void onAnimationStarted(const string& ani);
	virtual void onAnimationEnded(const string& ani);

	virtual void onClicked(const string& buttonName);

	SkelObject* m_pEmoticonBG;
	Button* m_pButton[10];

	Button* m_pEmticonButton;
private:
	void onCloseAction();
	void setVisibleButtonLabel(bool visible);
public:
	Panel* mParentPanel;
	Panel* mMainPanel;

	bool _isVisible;

};