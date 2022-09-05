#include "pch.h"
#include "IntableSearchPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

IntableSearchPanel::IntableSearchPanel()
{
	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

IntableSearchPanel::~IntableSearchPanel()
{
	//destruct();
}

void IntableSearchPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_intable_search.mxml");
}

void IntableSearchPanel::InitImage()
{
	m_TextField = getTextField("fld_friendname");
}	

void IntableSearchPanel::initButton()
{
	m_inputTouch = getButton("sbtn_friendsearch_touch");
	m_inputTouch->setVisible(false);
	m_inputTouch->setType(Button::NoPressImg);

	m_searchBtn = getButton("sbtn_button");
}

void IntableSearchPanel::onClicked(const string& name)
{
	return;
}
