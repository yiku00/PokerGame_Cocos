#include "pch.h"
#include "RankingTutorialPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"

RankingTutorialPanel::RankingTutorialPanel()
{
	m_TutorialTime = 0;
	m_TutorialStep = 0;
	m_pageIndex = 0;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);
}

RankingTutorialPanel::~RankingTutorialPanel()
{
	//destruct();
}

void RankingTutorialPanel::InitPanel()
{
	construct(getMxmlPath() + "tutorial_rank.mxml");
}

void RankingTutorialPanel::InitImage()
{
	m_page1.push_back(getSkel("skel_1rank_blackpoint_r1"));
	m_page1.push_back(getSkel("skel_1rank_diamond1"));
	m_page1.push_back(getSkel("skel_1rank_diamond2"));
	m_page1Label.push_back(getLabel("txt_1rank_touch"));

	m_page2.push_back(getSkel("skel_2rank_blackpoint_r2_1"));
	m_page2.push_back(getSkel("skel_2rank_blackpoint_r2_2"));
	m_page2.push_back(getSkel("skel_2rank_black_bcenter_4right"));
	m_page2.push_back(getSkel("skel_2rank_black_bcenter_4left"));
	m_page2.push_back(getSkel("skel_2rank_light_center_v31"));
	m_page2.push_back(getSkel("skel_2rank_light_center_v32"));
	m_page2.push_back(getSkel("skel_2rank_light_center_h31"));
	m_page2.push_back(getSkel("skel_2rank_light_center_h32"));
	m_page2.push_back(getSkel("skel_2rank_arrow_point4_top"));
	m_page2.push_back(getSkel("skel_2rank_arrow_line_top1_2"));
	m_page2.push_back(getSkel("skel_2rank_light_corner_ru"));
	m_page2.push_back(getSkel("skel_2rank_light_corner_lu"));
	m_page2.push_back(getSkel("skel_2rank_light_corner_rd"));
	m_page2.push_back(getSkel("skel_2rank_light_corner_ld"));
	m_page2.push_back(getSkel("skel_2rank_diamond1"));
	m_page2.push_back(getSkel("skel_2rank_diamond2"));

	m_page2Label.push_back(getLabel("txt_2rank_guide4"));
	m_page2Label.push_back(getLabel("txt_2rank_touch"));

	m_page3.push_back(getSkel("skel_3rank_blackpoint_r3_1"));
	m_page3.push_back(getSkel("skel_3rank_blackpoint_r3_1"));
	m_page3.push_back(getSkel("skel_3rank_blackpoint_r3_2"));
	m_page3.push_back(getSkel("skel_3rank_blackpoint_r3_3"));
	m_page3.push_back(getSkel("skel_3rank_blackpoint_r3_4"));
	m_page3.push_back(getSkel("skel_3rank_black_bcenter_rleft"));
	m_page3.push_back(getSkel("skel_3rank_black_bcenter_rright1"));
	m_page3.push_back(getSkel("skel_3rank_black_bcenter_rright2"));
	m_page3.push_back(getSkel("skel_3rank_black_hcenter_rup"));
	m_page3.push_back(getSkel("skel_3rank_black_hcenter_rbottom"));
	m_page3.push_back(getSkel("skel_3rank_black_corner_ld"));
	m_page3.push_back(getSkel("skel_3rank_black_corner_lu"));
	m_page3.push_back(getSkel("skel_3rank_black_corner_rd"));
	m_page3.push_back(getSkel("skel_3rank_black_corner_ru"));
	m_page3.push_back(getSkel("skel_3rank_light_topcenter_5"));
	m_page3.push_back(getSkel("skel_3rank_light_toprightend2"));
	m_page3.push_back(getSkel("skel_3rank_light_topleftend2"));
	m_page3.push_back(getSkel("skel_3rank_light_toprightend1"));
	m_page3.push_back(getSkel("skel_3rank_light_topleftend1"));
	m_page3.push_back(getSkel("skel_3rank_light_topcenter_4"));
	m_page3.push_back(getSkel("skel_3rank_arrow_point4_top"));
	m_page3.push_back(getSkel("skel_3rank_arrow_line_top1_2"));
	m_page3.push_back(getSkel("skel_3rank_arrow_point_left"));
	m_page3.push_back(getSkel("skel_3rank_arrow_line_left"));
	m_page3.push_back(getSkel("skel_3rank_diamond1"));
	m_page3.push_back(getSkel("skel_3rank_diamond2"));

	m_page3Label.push_back(getLabel("txt_3rank_guide1"));
	m_page3Label.push_back(getLabel("txt_3rank_guide2"));
	m_page3Label.push_back(getLabel("txt_3rank_touch"));

	m_Icon = getSkel("skel_portrait_stay");
	m_bubble = getSkel("skel_image_dialogue2_start");
	m_DialogeTxt = getLabel("txt_dialogue_content");

	m_Icon->setVisible(false);
	m_bubble->setVisible(false);
	m_DialogeTxt->setString("");

	for (SkelObject* _pObj : m_page1)
	{
		_pObj->setVisible(false);
	}

	for (SkelObject* _pObj : m_page2)
	{
		_pObj->setVisible(false);
	}

	for (SkelObject* _pObj : m_page3)
	{
		_pObj->setVisible(false);
	}

	for (Nx::Label* _pObj : m_page1Label)
	{
		_pObj->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pObj->setVisible(false);
	}
	for (Nx::Label* _pObj : m_page2Label)
	{
		_pObj->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pObj->setVisible(false);
	}
	for (Nx::Label* _pObj : m_page3Label)
	{
		_pObj->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pObj->setVisible(false);
	}
}

void RankingTutorialPanel::initButton()
{
	getButton("sbtn_touch_size")->setVisible(false);
}


bool RankingTutorialPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}

void RankingTutorialPanel::resume()
{
}

void RankingTutorialPanel::onClicked(const string& name)
{
}

void RankingTutorialPanel::update(float dt)
{
	UpdateTutorialStep(dt);
}

bool RankingTutorialPanel::handling(STCMD &stCmd)
{
	return false;
}

void RankingTutorialPanel::ShowPage(int _page)
{
	bool _visible[3];

	_visible[0] = (_page == 0 || _page == 3);
	_visible[1] = (_page == 1);
	_visible[2] = (_page == 2);

	for (SkelObject* _pObj : m_page1)
	{
		_pObj->setVisible(_visible[0]);
	}
	for (SkelObject* _pObj : m_page2)
	{
		_pObj->setVisible(_visible[1]);
	}
	for (SkelObject* _pObj : m_page3)
	{
		_pObj->setVisible(_visible[2]);
	}

	for (Nx::Label* _pObj : m_page1Label)
	{
		_pObj->setVisible(_visible[0]);
	}
	for (Nx::Label* _pObj : m_page2Label)
	{
		_pObj->setVisible(_visible[1]);
	}
	for (Nx::Label* _pObj : m_page3Label)
	{
		_pObj->setVisible(_visible[2]);
	}
}

void RankingTutorialPanel::ShowText(int _page)
{
	string _text = GameStringDepot::getSingletonPtr()->getString("TXT_RANKING_TUTORIAL_" + StringConverter::toString(_page + 1));
	m_DialogeTxt->setString(_text.c_str());
}

void RankingTutorialPanel::UpdateTutorialStep(float _dt)
{
	switch (m_TutorialStep)
	{
	case 0:
		ShowPage(0);
		m_Icon->setScale(0.f);
		m_Icon->runAction(CCSequence::create(
			CCDelayTime::create(0.2f),
			CCScaleTo::create(0.1f, 1.1f),
			CCScaleTo::create(0.1f, 1.f),
			NULL));
		m_Icon->setVisible(true);
		m_TutorialTime = 0.f;
		m_TutorialStep = 1;
		break;
	case 1:
		m_TutorialTime += _dt;
		if (m_TutorialTime >= 0.4f)
		{
			m_bubble->playAnimation("image_dialogue2_start");
			m_bubble->appendAnimation("image_dialogue2_stay");
			m_DialogeTxt->setString("");
			m_bubble->setVisible(true);
			m_DialogeTxt->setVisible(true);
			m_TutorialTime = 0.f;
			m_TutorialStep = 2;
		}
		break;
	case 2:
		m_TutorialTime += _dt;
		if (m_TutorialTime >= 0.4f)
		{
			ShowText(0);
			m_pageIndex = 1;
			m_TutorialTime = 0.f;
			m_TutorialStep = 3;
		}
		break;
	case 3:

		break;
	case 4:
		m_bubble->playAnimation("image_dialogue2_end");
		m_Icon->runAction(CCSequence::create(
			CCDelayTime::create(0.2f),
			CCScaleTo::create(0.1f, 1.1f),
			CCScaleTo::create(0.1f, 0.f),
			NULL));
		m_TutorialStep = 5;
		break;
	case 5:
		m_TutorialTime += _dt;
		if (m_TutorialTime >= 0.5f)
		{
			m_TutorialTime = 0.f;
			m_TutorialStep = 6;
		}
		break;

	}
}

void RankingTutorialPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}