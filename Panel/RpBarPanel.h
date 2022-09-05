#pragma once

#include "NxFramework.h"
#include "SlotButtonPanel.h"
#include "TypeDefine.pb.h"

class RpBarPanel : public Panel, public Button::Listener
{
public:
	RpBarPanel();
	virtual ~RpBarPanel();

	void InitPanel();
	void InitImage();
	void initButton();

	virtual void onClicked(const string& name);

	void SetRank(int _rank, bool _visible = true);
	void SetString(string _date, string _title, string _recommend);
	void SetScore(int32 _score);
	void setGameType(GameKind gameKind);
public:	
	SkelObject* m_RankImage;

	SlotButtonPanel* m_pPlayButton;
	
	CCLabelBMFont* m_ScoreLabel;
	CCLabelBMFont* m_RankingLabel;

private:
	Nx::Label* mNoRankLabel;
	Nx::Label* mNoRankUnderLabel;
	SkelObject* mGameIcon;
};
