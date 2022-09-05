#include "pch.h"
#include "RpBarPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "PokerResourceHelper.h"

RpBarPanel::RpBarPanel()
{
	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

RpBarPanel::~RpBarPanel()
{
	//destruct();
}

void RpBarPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_rp_bar.mxml");
	setButtonListener(this);
	mNoRankLabel = getLabel("txt_number_rank");
	mNoRankUnderLabel = getLabel("txt_number_rank_under");
	mGameIcon = getSkel("skel_symbol");
}

void RpBarPanel::InitImage()
{
	CCSize _contentSize = getDummy("dmy_rp_bar").size;	
	m_RankImage = getSkel("skel_rank_1");
	getLabel("txt_savedate")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_replaytitle")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_recommend_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_recommend")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	CCPoint _ButtonPos = getDummy("dmy_button_slot").origin;
	_ButtonPos.y = -_ButtonPos.y;
	m_pPlayButton = new SlotButtonPanel();
	m_pPlayButton->setPosition(_ButtonPos);
	addChild(m_pPlayButton);
	m_pPlayButton->release();
	m_pPlayButton->SetBtnText(GameStringDepot::getSingletonPtr()->getString("TXT_REPLAY_PLAY_BUTTON").c_str());
	m_pPlayButton->SetButtonListener(this);

	CCPoint _ScorePos = getDummy("dmy_number_score").origin;
	CCSize _ScoreSize = getDummy("dmy_number_score").size;

	_ScorePos.y = DESIGN_HEIGHT - _ScorePos.y - (_ScoreSize.height / 2);
	m_ScoreLabel = CCLabelBMFont::create("", "fonts/number_score.fnt");
	m_ScoreLabel->setContentSize(_ScoreSize);
	m_ScoreLabel->retain();
	m_ScoreLabel->setAnchorPoint(ccp(0.f, 0.5f));
	m_ScoreLabel->setScale(1.f);
	m_ScoreLabel->setPosition(_ScorePos);
	addChild(m_ScoreLabel);
	m_ScoreLabel->release();

	CCPoint _RankPos = getDummy("dmy_number_rank").origin;
	CCSize _RankSize = getDummy("dmy_number_rank").size;
	_RankPos.y = DESIGN_HEIGHT - _RankPos.y - (_RankSize.height / 2);
	m_RankingLabel = CCLabelBMFont::create("", "fonts/number_rank.fnt");
	m_RankingLabel->setContentSize(_RankSize);
	m_RankingLabel->retain();
	m_RankingLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	m_RankingLabel->setScale(1.f);
	m_RankingLabel->setPosition(_RankPos);
	addChild(m_RankingLabel);
	m_RankingLabel->release();
	m_RankingLabel->setVisible(false);
}

void RpBarPanel::initButton()
{
	getButton("sbtn_usertouch")->setVisible(false);
	//getButton("sbtn_usertouch")->setPaused(true);
}

void RpBarPanel::onClicked(const string& name)
{
	if (name == "sbtn_button") {
		fireMessage("ReplayButton" + StringConverter::toString(getTag()));
	}
	else if (name == "sbtn_usertouch") {
		fireMessage("ShowInfoBtn" + StringConverter::toString(getTag()));
	}
}

void RpBarPanel::SetRank(int _rank, bool _visible /*= true*/)
{
	mNoRankLabel->setVisible(_rank == 0);
	mNoRankUnderLabel->setVisible(_rank == 0);
	if (_rank < 1)
		return;

	if (_rank <= 3)	{
		string _aniName = "rank_" + StringConverter::toString(_rank);
		if (m_RankImage)
		{
			m_RankImage->playAnimation(_aniName);
			m_RankImage->setVisible(_visible);
			m_RankingLabel->setVisible(false);
		}
	}
	else {
		m_RankImage->setVisible(false);
		m_RankingLabel->setVisible(true);
		m_RankingLabel->setString(StringConverter::toString(_rank).c_str());
	}
}

void RpBarPanel::SetString(string _date, string _title, string _recommend)
{
	getLabel("txt_savedate")->setString(_date.c_str());
	getLabel("txt_replaytitle")->setString(_title.c_str());
	getLabel("txt_recommend_under")->setString(_recommend.c_str());
	getLabel("txt_recommend")->setString(_recommend.c_str());
}

void RpBarPanel::SetScore(int32 _score)
{
	m_ScoreLabel->setString(StringConverter::toString(_score).c_str());
}

void RpBarPanel::setGameType(GameKind gameKind)
{
	mGameIcon->playAnimation(PokerResourceHelper::getGameKindIcon(gameKind));
}

