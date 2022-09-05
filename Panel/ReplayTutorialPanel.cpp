#include "pch.h"
#include "ReplayTutorialPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"

ReplayTutorialPanel::ReplayTutorialPanel()
{
	m_TutorialTime = 0;
	m_TutorialStep = 0;
	m_pageIndex = 0;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);
}

ReplayTutorialPanel::~ReplayTutorialPanel()
{
	//destruct();
	removeFromParentAndCleanup(true);
}

void ReplayTutorialPanel::InitPanel()
{
	construct(getMxmlPath() + "tutorial_replay.mxml");
}

void ReplayTutorialPanel::InitImage()
{
	m_page1.push_back(getSkel("skel_1replay_blackpoint_r1"));
	m_page1.push_back(getSkel("skel_1replay_diamond1"));
	m_page1.push_back(getSkel("skel_1replay_diamond2"));
	m_page1Label.push_back(getLabel("txt_1replay_touch"));

	m_page2.push_back(getSkel("skel_2replay_blackpoint_re2_1"));
	m_page2.push_back(getSkel("skel_2replay_blackpoint_re2_2"));
	m_page2.push_back(getSkel("skel_2replay_black_bcenter_releft"));
	m_page2.push_back(getSkel("skel_2replay_black_bcenter_reright"));
	m_page2.push_back(getSkel("skel_2replay_light_toprightend1"));
	m_page2.push_back(getSkel("skel_2replay_light_topleftend1"));
	m_page2.push_back(getSkel("skel_2replay_light_topcenter_1"));
	m_page2.push_back(getSkel("skel_2replay_light_toprightend2"));
	m_page2.push_back(getSkel("skel_2replay_light_topleftend2"));
	m_page2.push_back(getSkel("skel_2replay_light_topcenter_2"));
	m_page2.push_back(getSkel("skel_2replay_light_toprightend3"));
	m_page2.push_back(getSkel("skel_2replay_light_topleftend3"));
	m_page2.push_back(getSkel("skel_2replay_light_topcenter_3"));
	m_page2.push_back(getSkel("skel_2replay_light_toprightend4"));
	m_page2.push_back(getSkel("skel_2replay_light_topleftend4"));
	m_page2.push_back(getSkel("skel_2replay_light_topcenter_4"));
	m_page2.push_back(getSkel("skel_2replay_arrow_point_bottom"));
	m_page2.push_back(getSkel("skel_2replay_arrow_point_top1"));
	m_page2.push_back(getSkel("skel_2replay_arrow_point_top2"));
	m_page2.push_back(getSkel("skel_2replay_arrow_point_top3"));
	m_page2.push_back(getSkel("skel_2replay_arrow_line_top21"));
	m_page2.push_back(getSkel("skel_2replay_arrow_line_top22"));
	m_page2.push_back(getSkel("skel_2replay_arrow_line_top3"));
	m_page2.push_back(getSkel("skel_2replay_arrow_line_top1"));
	m_page2.push_back(getSkel("skel_2replay_diamond1"));
	m_page2.push_back(getSkel("skel_2replay_diamond2"));

	m_page2Label.push_back(getLabel("txt_2replay_guide1"));
	m_page2Label.push_back(getLabel("txt_2replay_guide2"));
	m_page2Label.push_back(getLabel("txt_2replay_guide3"));
	m_page2Label.push_back(getLabel("txt_2replay_guide4"));
	m_page2Label.push_back(getLabel("txt_2replay_touch"));

	m_page3.push_back(getSkel("skel_3replay_blackpoint_re3_1"));
	m_page3.push_back(getSkel("skel_3replay_blackpoint_re3_2"));
	m_page3.push_back(getSkel("skel_3replay_black_bcenter_4right"));
	m_page3.push_back(getSkel("skel_3replay_black_bcenter_4left"));
	m_page3.push_back(getSkel("skel_3replay_light_center_v41"));
	m_page3.push_back(getSkel("skel_3replay_light_center_h41"));
	m_page3.push_back(getSkel("skel_3replay_light_center_v42"));
	m_page3.push_back(getSkel("skel_3replay_light_center_h42"));
	m_page3.push_back(getSkel("skel_3replay_light_corner_ru"));
	m_page3.push_back(getSkel("skel_3replay_light_corner_lu"));
	m_page3.push_back(getSkel("skel_3replay_light_corner_rd"));
	m_page3.push_back(getSkel("skel_3replay_light_corner_ld"));
	m_page3.push_back(getSkel("skel_3replay_arrow_point_top"));
	m_page3.push_back(getSkel("skel_3replay_arrow_line_top1"));
	m_page3.push_back(getSkel("skel_3replay_diamond1"));
	m_page3.push_back(getSkel("skel_3replay_diamond2"));

	m_page3Label.push_back(getLabel("txt_3replay_guide2"));
	m_page3Label.push_back(getLabel("txt_3replay_touch"));

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

void ReplayTutorialPanel::initButton()
{
	getButton("sbtn_touch_size")->setVisible(false);
}


bool ReplayTutorialPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}

void ReplayTutorialPanel::resume()
{
}

void ReplayTutorialPanel::onClicked(const string& name)
{
}

void ReplayTutorialPanel::update(float dt)
{
	UpdateTutorialStep(dt);
}

bool ReplayTutorialPanel::handling(STCMD &stCmd)
{
	return false;
}

void ReplayTutorialPanel::ShowPage(int _page)
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

void ReplayTutorialPanel::ShowText(int _page)
{
	string _text = GameStringDepot::getSingletonPtr()->getString("TXT_REPLAY_TUTORIAL_" + StringConverter::toString(_page+1));
	m_DialogeTxt->setString(_text.c_str());
}


void ReplayTutorialPanel::UpdateTutorialStep(float _dt)
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

void ReplayTutorialPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}