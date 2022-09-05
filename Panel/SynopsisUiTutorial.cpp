#include "pch.h"
#include "SynopsisUiTutorial.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
//#include "SimplePopupPanel.h"
//#include "HeroApp.h"

#include "Web/WebService.h"
#include "SynopsisMainPanel.h"
#include "SynopsisCharacterInfoPanel.h"
#include "SynopsisDialogPanel.h"
#include "AccountPopupPanel.h"
#include "GameStringDepot.h"
#include "PokerRankHelper.h"

SynopsisUiTutorial::SynopsisUiTutorial()
{
	m_Process = false;
	m_PageIndex = 0;
	m_BlockTime = 0.f;

	InitPanel();
	InitImage();
	InitButton();
	
	setButtonListener(this);
}

SynopsisUiTutorial::~SynopsisUiTutorial()
{
	//destruct();
}

void SynopsisUiTutorial::InitPanel()
{
	construct(getMxmlPath() + "tutorial.mxml");
	setVisible(false);
}

void SynopsisUiTutorial::InitImage()
{
	//Page1
	m_page1.push_back(getSkel("skel_1page_blackpoint_1"));
	m_page1.push_back(getSkel("skel_1page_light_topleftend1"));
	m_page1.push_back(getSkel("skel_1page_light_toprightend1"));
	m_page1.push_back(getSkel("skel_1page_light_topleftend2"));
	m_page1.push_back(getSkel("skel_1page_light_toprightend2"));
	m_page1.push_back(getSkel("skel_1page_light_topleftend3"));
	m_page1.push_back(getSkel("skel_1page_light_toprightend3"));
	m_page1.push_back(getSkel("skel_1page_light_topleftend4"));
	m_page1.push_back(getSkel("skel_1page_light_toprightend4"));
	m_page1.push_back(getSkel("skel_1page_light_topleftend5"));
	m_page1.push_back(getSkel("skel_1page_light_toprightend5"));
	m_page1.push_back(getSkel("skel_1page_light_topcenter_1"));
	m_page1.push_back(getSkel("skel_1page_light_topcenter_2"));
	m_page1.push_back(getSkel("skel_1page_light_topcenter_3_1"));
	m_page1.push_back(getSkel("skel_1page_light_topcenter_3_2"));
	m_page1.push_back(getSkel("skel_1page_light_topcenter_4"));
	m_page1.push_back(getSkel("skel_1page_arrow_point1_top"));
	m_page1.push_back(getSkel("skel_1page_arrow_point2_top"));
	m_page1.push_back(getSkel("skel_1page_arrow_point3_top"));
	m_page1.push_back(getSkel("skel_1page_arrow_point4_top"));
	m_page1.push_back(getSkel("skel_1page_arrow_point5_top"));
	m_page1.push_back(getSkel("skel_1page_arrow_line_top1_1"));
	m_page1.push_back(getSkel("skel_1page_arrow_line_top1_2"));
	m_page1.push_back(getSkel("skel_1page_arrow_line_top2_1"));
	m_page1.push_back(getSkel("skel_1page_arrow_line_top2_2"));
	m_page1.push_back(getSkel("skel_1page_arrow_line_top3"));
	m_page1Label.push_back(getLabel("txt_1page_guide1"));
	m_page1Label.push_back(getLabel("txt_1page_guide2"));
	m_page1Label.push_back(getLabel("txt_1page_guide3"));
	m_page1Label.push_back(getLabel("txt_1page_guide4"));
	m_page1Label.push_back(getLabel("txt_1page_guide5"));

	//Page2
	m_page2.push_back(getSkel("skel_2page_blackpoint_2"));
	m_page2.push_back(getSkel("skel_2page_blackpoint_3"));
	m_page2.push_back(getSkel("skel_2page_black_corner_ld"));
	m_page2.push_back(getSkel("skel_2page_black_corner_lu"));
	m_page2.push_back(getSkel("skel_2page_black_corner_rd"));
	m_page2.push_back(getSkel("skel_2page_black_corner_ru"));
	m_page2.push_back(getSkel("skel_2page_black_bcenter_1right"));
	m_page2.push_back(getSkel("skel_2page_black_bcenter_1left"));
	m_page2.push_back(getSkel("skel_2page_blackpoint_2_bottom"));
	m_page2.push_back(getSkel("skel_2page_black_hcenter_bottom"));
	m_page2.push_back(getSkel("skel_2page_black_hcenter_up"));
	m_page2.push_back(getSkel("skel_2page_light_leftbutton1"));
	m_page2.push_back(getSkel("skel_2page_light_leftbutton2"));
	m_page2.push_back(getSkel("skel_2page_light_leftbutton3"));
	m_page2.push_back(getSkel("skel_2page_light_leftbutton4"));
	m_page2.push_back(getSkel("skel_2page_light_leftbutton5"));
	m_page2.push_back(getSkel("skel_2page_arrow_point_left1"));
	m_page2.push_back(getSkel("skel_2page_arrow_point_left2"));
	m_page2.push_back(getSkel("skel_2page_arrow_point_left3"));
	m_page2.push_back(getSkel("skel_2page_arrow_point_left4"));
	m_page2.push_back(getSkel("skel_2page_arrow_point_left5"));
	m_page2.push_back(getSkel("skel_2page_arrow_line_left1"));
	m_page2.push_back(getSkel("skel_2page_arrow_line_left2"));
	m_page2.push_back(getSkel("skel_2page_arrow_line_left3"));
	m_page2.push_back(getSkel("skel_2page_arrow_line_left4"));
	m_page2.push_back(getSkel("skel_2page_arrow_line_left5"));
	m_page2.push_back(getSkel("skel_2page_diamond1"));
	m_page2.push_back(getSkel("skel_2page_diamond2"));
	
	m_page2Label.push_back(getLabel("txt_2page_guide1"));
	m_page2Label.push_back(getLabel("txt_2page_guide2"));
	m_page2Label.push_back(getLabel("txt_2page_guide3"));
	m_page2Label.push_back(getLabel("txt_2page_guide4"));
	m_page2Label.push_back(getLabel("txt_2page_guide5"));
	m_page2Label.push_back(getLabel("txt_2page_touch"));

	//Page3
	m_page3.push_back(getSkel("skel_3page_blackpoint_4"));
	m_page3.push_back(getSkel("skel_3page_blackpoint_3"));
	m_page3.push_back(getSkel("skel_3page_black_corner_ld"));
	m_page3.push_back(getSkel("skel_3page_black_corner_lu"));
	m_page3.push_back(getSkel("skel_3page_black_corner_rd"));
	m_page3.push_back(getSkel("skel_3page_black_corner_ru"));
	m_page3.push_back(getSkel("skel_3page_black_bcenter_1right"));
	m_page3.push_back(getSkel("skel_3page_black_bcenter_1left"));
	m_page3.push_back(getSkel("skel_3page_black_hcenter_2up"));
	m_page3.push_back(getSkel("skel_3page_black_hcenter_2bottom"));
	m_page3.push_back(getSkel("skel_3page_arrow_point_right4"));//<mx:Image id = "skel_3page_arrow_line_left4.synopsis_and_tutorial_8888.arrow_line_left" source = "skel_3page_arrow_line_left4.synopsis_and_tutorial_8888.arrow_line_left.png" x = "610" y = "492" width = "48" height = "6" / >
	m_page3.push_back(getSkel("skel_3page_arrow_line_left4"));	//<mx:Image id = "skel_3page_arrow_line_left4.synopsis_and_tutorial_8888.arrow_line_left" source = "skel_3page_arrow_line_left4.synopsis_and_tutorial_8888.arrow_line_left.png" x = "610" y = "492" width = "48" height = "6" / >
	m_page3.push_back(getSkel("skel_3page_arrow_point_right3"));	//<mx:Image id = "skel_3page_arrow_point_right3.synopsis_and_tutorial_8888.arrow_point_right" source = "skel_3page_arrow_point_right3.synopsis_and_tutorial_8888.arrow_point_right.png" x = "656" y = "383" width = "14" height = "18" / >
	m_page3.push_back(getSkel("skel_3page_arrow_line_left3"));	//<mx:Image id = "skel_3page_arrow_line_left3.synopsis_and_tutorial_8888.arrow_line_left" source = "skel_3page_arrow_line_left3.synopsis_and_tutorial_8888.arrow_line_left.png" x = "610" y = "389" width = "48" height = "6" / >
	m_page3.push_back(getSkel("skel_3page_arrow_point_right2"));	//<mx : Image id = "skel_3page_arrow_point_right2.synopsis_and_tutorial_8888.arrow_point_right" source = "skel_3page_arrow_point_right2.synopsis_and_tutorial_8888.arrow_point_right.png" x = "656" y = "268" width = "14" height = "18" / >
	m_page3.push_back(getSkel("skel_3page_arrow_line_left2"));	//<mx : Image id = "skel_3page_arrow_line_left2.synopsis_and_tutorial_8888.arrow_line_left" source = "skel_3page_arrow_line_left2.synopsis_and_tutorial_8888.arrow_line_left.png" x = "610" y = "274" width = "48" height = "6" / >
	m_page3.push_back(getSkel("skel_3page_arrow_point_right1"));//<mx:Image id = "skel_3page_arrow_point_right1.synopsis_and_tutorial_8888.arrow_point_right" source = "skel_3page_arrow_point_right1.synopsis_and_tutorial_8888.arrow_point_right.png" x = "656" y = "162" width = "14" height = "18" / >
	m_page3.push_back(getSkel("skel_3page_arrow_line_left1"));//<mx:Image id = "skel_3page_arrow_line_left1.synopsis_and_tutorial_8888.arrow_line_left" source = "skel_3page_arrow_line_left1.synopsis_and_tutorial_8888.arrow_line_left.png" x = "610" y = "168" width = "48" height = "6" / >
	//m_page3.push_back(getSkel("skel_3page_light_corner_ld1"));
	//m_page3.push_back(getSkel("skel_3page_light_corner_ld2"));
	//m_page3.push_back(getSkel("skel_3page_light_corner_lu1"));
	//m_page3.push_back(getSkel("skel_3page_light_corner_lu2"));
	//m_page3.push_back(getSkel("skel_3page_light_corner_rd1"));
	//m_page3.push_back(getSkel("skel_3page_light_corner_rd2"));
	//m_page3.push_back(getSkel("skel_3page_light_corner_ru1"));
	//m_page3.push_back(getSkel("skel_3page_light_corner_ru2"));
	//m_page3.push_back(getSkel("skel_3page_light_center_h1"));
	//m_page3.push_back(getSkel("skel_3page_light_center_h2"));
	//m_page3.push_back(getSkel("skel_3page_light_center_h3"));
	//m_page3.push_back(getSkel("skel_3page_light_center_h4"));
	//m_page3.push_back(getSkel("skel_3page_light_center_v1_1"));
	//m_page3.push_back(getSkel("skel_3page_light_center_v1_2"));
	//m_page3.push_back(getSkel("skel_3page_light_center_v2_1"));
	//m_page3.push_back(getSkel("skel_3page_light_center_v2_2"));
	//m_page3.push_back(getSkel("skel_3page_arrow_point_right1"));
	//m_page3.push_back(getSkel("skel_3page_arrow_point_right2"));
	//m_page3.push_back(getSkel("skel_3page_arrow_line_left1"));
	//m_page3.push_back(getSkel("skel_3page_arrow_line_left2"));
	m_page3.push_back(getSkel("skel_3page_diamond1"));
	m_page3.push_back(getSkel("skel_3page_diamond2"));

	m_page3Label.push_back(getLabel("txt_3page_guide4"));	//<mx:Text id = "txt_3page_guide4.r.t.29" styleName = "textStyle2" x = "118" y = "482" width = "482" text = "칩이 충분하다면 미니게임에서 잭팟을 노려보세요!" / >
	m_page3Label.push_back(getLabel("txt_3page_guide3"));	//< mx:Text id = "txt_3page_guide3.r.t.74" styleName = "textStyle2" x = "118" y = "370" width = "482" text = "최후의 1인을 뽑는 대규모 토너먼트입니다. //정해진 시간에만 참가할 수 있습니다."/>
	m_page3Label.push_back(getLabel("txt_3page_guide2"));	//<mx : Text id = "txt_3page_guide2.r.t.29" styleName = "textStyle2" x = "118" y = "265" width = "482" text = "시즌 기간동안 진행되는 짧은 토너먼트입니다." / >
	m_page3Label.push_back(getLabel("txt_3page_guide1"));	//<mx:Text id = "txt_3page_guide1.r.t.29" styleName = "textStyle2" x = "118" y = "159" width = "482" text = "게임 종류와 규모를 자유롭게 선택할 수 있는 기본 모드입니다." / >

	m_page3Label.push_back(getLabel("txt_3page_touch"));

	//Page4
	m_page4.push_back(getSkel("skel_4page_blackpoint_5_2"));
	m_page4.push_back(getSkel("skel_4page_blackpoint_5_1"));
	m_page4.push_back(getSkel("skel_4page_black_corner_ld"));
	m_page4.push_back(getSkel("skel_4page_black_corner_lu"));
	m_page4.push_back(getSkel("skel_4page_black_corner_rd"));
	m_page4.push_back(getSkel("skel_4page_black_corner_ru"));
	m_page4.push_back(getSkel("skel_4page_black_bcenter_3left"));
	m_page4.push_back(getSkel("skel_4page_black_bcenter_3right"));
	m_page4.push_back(getSkel("skel_4page_black_hcenter_3bottom"));
	m_page4.push_back(getSkel("skel_4page_black_hcenter_3up"));
	m_page4.push_back(getSkel("skel_4page_light_bottombutton1"));
	m_page4.push_back(getSkel("skel_4page_arrow_point_bottom1"));
	m_page4.push_back(getSkel("skel_4page_light_bottombutton2"));
	m_page4.push_back(getSkel("skel_4page_arrow_point_bottom2"));
	m_page4.push_back(getSkel("skel_4page_light_bottombutton3"));
	m_page4.push_back(getSkel("skel_4page_arrow_point_bottom3"));
	m_page4.push_back(getSkel("skel_4page_arrow_line_top1_1"));
	m_page4.push_back(getSkel("skel_4page_arrow_line_top2_1"));
	m_page4.push_back(getSkel("skel_4page_arrow_line_top3"));
	m_page4.push_back(getSkel("skel_4page_diamond1"));
	m_page4.push_back(getSkel("skel_4page_diamond2"));

	m_page4Label.push_back(getLabel("txt_4page_guide1"));
	m_page4Label.push_back(getLabel("txt_4page_guide2"));
	m_page4Label.push_back(getLabel("txt_4page_guide3"));
	m_page4Label.push_back(getLabel("txt_4page_touch"));

	//init
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
	for (SkelObject* _pObj : m_page4)
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
	for (Nx::Label* _pObj : m_page4Label)
	{
		_pObj->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		_pObj->setVisible(false);
	}
}

void SynopsisUiTutorial::InitButton()
{
	m_BlockButton = getButton("sbtn_touch_size");
	m_BlockButton->setVisible(false);
	m_BlockButton->setType(Button::NoPressImg);
	m_BlockButton->setListener(this);
}

void SynopsisUiTutorial::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void SynopsisUiTutorial::onClicked(const string& name)
{
	if (m_BlockTime != 0.f)
		return;

	if (m_Process)
		return;

	if (name == "sbtn_touch_size")
	{
		ShowPage(m_PageIndex);
		if (m_PageIndex == 4)
		{
			EndTutorial();
			return;
		}
		m_PageIndex++;
	}
}

void SynopsisUiTutorial::update(float dt)
{
	if (m_BlockTime == 0.f)
		return;

	m_BlockTime -= dt;
	if (m_BlockTime < 0.f)
	{
		if (m_PageIndex <= 0)
		{
			ShowPage(m_PageIndex);
			m_PageIndex = 1;
		}
		m_BlockTime = 0.f;
	}
}

bool SynopsisUiTutorial::handling(STCMD &stCmd)
{
	if (!m_Process)
		return false;

	return false;
}

void SynopsisUiTutorial::ShowPage(int _page)
{
	bool _visible[4];
	
	_visible[0] = (_page == 0);
	_visible[1] = (_page == 1);
	_visible[2] = (_page == 2);
	_visible[3] = (_page == 3);

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

	for (SkelObject* _pObj : m_page4)
	{
		_pObj->setVisible(_visible[3]);
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
	for (Nx::Label* _pObj : m_page4Label)
	{
		_pObj->setVisible(_visible[3]);
	}
}

void SynopsisUiTutorial::SetMainUiPanel()
{
	m_UiPanel = new Panel();
	addChild(m_UiPanel, -1);
	m_UiPanel->release();

	m_UiPanel->construct(getMxmlPath() + "lobby_ui.mxml");

	m_UiPanel->getSkel("skel_backcolor")->setVisible(false);

	//InitLeftUiPanel();
	InitTopUiPanel();
	
	//m_UiPanel->getLabel("txt_gold")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//m_UiPanel->getLabel("txt_chip")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//m_UiPanel->getLabel("txt_rubby")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	//m_UiPanel->getLabel("str_userlevel")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//m_UiPanel->getLabel("txt_username")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//m_UiPanel->getLabel("txt_usernameshadow")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//m_UiPanel->getLabel("txt_vipsum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));


	//m_UiPanel->getSkel("skel_rubby_light")->playAnimation("rubby_light");
	//m_UiPanel->getSkel("skel_chip_light")->playAnimation("gold_light");
	//m_UiPanel->getSkel("skel_gold_light")->playAnimation("gold_light");
	//m_UiPanel->getSkel("skel_pagemark1")->playAnimation("pagemark_off_stay");
	//m_UiPanel->getSkel("skel_pagemark2")->playAnimation("pagemark_on_stay");
	//m_UiPanel->getSkel("skel_pagemark3")->playAnimation("pagemark_off_stay");

	for (int _i = 0; _i < 5; _i++)
	{
		m_UiPanel->getSkel("skel_left_back" + StringConverter::toString(_i + 1))->setVisible(false);
	}

	for (int _i = 0; _i < 2; _i++)
	{
		m_UiPanel->getSkel("skel_right_back" + StringConverter::toString(_i + 1))->setVisible(false);
	}

	m_pTopPanel->getSkel("skel_vip_mark")->setVisible(false);

	//m_pTopPanel->getButton("sbtn_userphoto")->setEnable(false);
	//m_pTopPanel->getButton("sbtn_userpanal")->setEnable(false);
	////m_pTopPanel->getButton("sbtn_usertouch")->setEnable(false);
	//m_pTopPanel->getButton("sbtn_option_button")->setEnable(false);
	//m_pTopPanel->getButton("sbtn_rubby_button")->setEnable(false);
	//m_pTopPanel->getButton("sbtn_bank_button")->setEnable(false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1")->setEnable(false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2")->setEnable(false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3")->setEnable(false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4")->setEnable(false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button5")->setEnable(false);
	m_UiPanel->getButton("sbtn_usertouch")->setEnable(false);
	m_UiPanel->getButton("sbtn_sevenpoker")->setEnable(false);
	m_UiPanel->getButton("sbtn_highlow")->setEnable(false);
	m_UiPanel->getButton("sbtn_minigame")->setEnable(false);
	m_UiPanel->getButton("sbtn_badugi")->setEnable(false);

	//m_pTopPanel->getButton("sbtn_userphoto")->setType(Button::NoPressImg);
	//m_pTopPanel->getButton("sbtn_userpanal")->setType(Button::NoPressImg);
	m_UiPanel->getButton("sbtn_usertouch")->setVisible(false);

	//m_pTopPanel->getButton("sbtn_option_button")->setType(Button::NoPressImg);
	//m_pTopPanel->getButton("sbtn_rubby_button")->setType(Button::NoPressImg);
	//m_pTopPanel->getButton("sbtn_bank_button")->setType(Button::NoPressImg);

	////option&back
	//m_pTopPanel->getButton("sbtn_option_button");
	////left menu
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1")->setType(Button::NoPressImg);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2")->setType(Button::NoPressImg);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3")->setType(Button::NoPressImg);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4")->setType(Button::NoPressImg);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button5")->setType(Button::NoPressImg);

	//right menu
	m_UiPanel->getButton("sbtn_sevenpoker")->setType(Button::ButtonType::NoPressImg);
	m_UiPanel->getButton("sbtn_highlow")->setType(Button::ButtonType::NoPressImg);
	m_UiPanel->getButton("sbtn_minigame")->setType(Button::ButtonType::NoPressImg);
	m_UiPanel->getButton("sbtn_sevenpoker")->getButtonSkelObject()->playAnimation("sevenpoker_stay");
	m_UiPanel->getButton("sbtn_highlow")->getButtonSkelObject()->playAnimation("highlow_stay");
	m_UiPanel->getButton("sbtn_minigame")->getButtonSkelObject()->playAnimation("minigame_stay");

	m_UiPanel->getButton("sbtn_badugi")->setType(Button::ButtonType::NoPressImg);
	m_UiPanel->getButton("sbtn_badugi")->getButtonSkelObject()->playAnimation("badugi_stay");

	//m_UiPanel->getButton("sbtn_texasholdem")->setType(Button::ButtonType::NoPressImg);
	//m_UiPanel->getButton("sbtn_texasholdem")->getButtonSkelObject()->playAnimation("texasholdem_stay");

	//m_pMyHomeButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1");
	//m_pLetterButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2");
	//m_pFriendButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3");
	//m_pMissionButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4");
	//m_pShopButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button5");
	m_p7PokerButton = m_UiPanel->getButton("sbtn_sevenpoker");
	m_pHighLowButton = m_UiPanel->getButton("sbtn_highlow");
	m_pBadugiButton = m_UiPanel->getButton("sbtn_badugi");
	//m_pHoldemButton = m_UiPanel->getButton("sbtn_texasholdem");
	m_pMiniGameButton = m_UiPanel->getButton("sbtn_minigame");

	m_pMyHomeButton->getButtonSkelObject()->setSkin("myroom");
	m_pLetterButton->getButtonSkelObject()->setSkin("letter");
	m_pFriendButton->getButtonSkelObject()->setSkin("friend");
	m_pMissionButton->getButtonSkelObject()->setSkin("mission");
	m_pShopButton->getButtonSkelObject()->setSkin("shop");

	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1")->setSkelAnimation("lobbyleft_off_stay");
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2")->setSkelAnimation("lobbyleft_off_stay");
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3")->setSkelAnimation("lobbyleft_off_stay");
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4")->setSkelAnimation("lobbyleft_off_stay");
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button5")->setSkelAnimation("lobbyleft_off_stay");

	//bottom menu
	m_pDailyCheckButton = m_UiPanel->getButton("sbtn_lobbybottom_button1");
	m_pRankingButton = m_UiPanel->getButton("sbtn_lobbybottom_button2");
	m_pReplayButton = m_UiPanel->getButton("sbtn_lobbybottom_button3");

	m_pDailyCheckButton->setType(Button::ButtonType::NoPressImg);
	m_pRankingButton->setType(Button::ButtonType::NoPressImg);
	m_pReplayButton->setType(Button::ButtonType::NoPressImg);

	m_pDailyCheckButton->setZOrder(2);
	m_pRankingButton->setZOrder(2);
	m_pReplayButton->setZOrder(2);

	m_pDailyCheckButton->getButtonSkelObject()->setSkin("attendance");
	m_pRankingButton->getButtonSkelObject()->setSkin("ranking");
	m_pReplayButton->getButtonSkelObject()->setSkin("replay");

	m_pDailyCheckButton->getButtonSkelObject()->playAnimation("lobbybottom_off_stay");
	m_pRankingButton->getButtonSkelObject()->playAnimation("lobbybottom_off_stay");
	m_pReplayButton->getButtonSkelObject()->playAnimation("lobbybottom_off_stay");

	//m_UiPanel->getSkel("skel_leftback")->setVisible(false);
	//m_UiPanel->getSkel("skel_emphasis1")->setVisible(false);
	//m_UiPanel->getSkel("skel_emphasis2")->setVisible(false);
	//m_UiPanel->getSkel("skel_emphasis3")->setVisible(false);
	//m_UiPanel->getSkel("skel_emphasis4")->setVisible(false);
	//m_UiPanel->getSkel("skel_emphasis5")->setVisible(false);

	m_pTopPanel->getSkel("skel_class_gold")->setVisible(false);

	applyUserData();
	ReadyAppear();
}

void SynopsisUiTutorial::applyUserData()
{
	UpdateUserMoney();
	UpdateUserLevel();
	UpdateUserNickName();
	UpdateUserChip();
	UpdateUserCash();
	UpdateUserVip();
	//m_pLeftUiPanel->UpdateNotiData();
}

void SynopsisUiTutorial::UpdateUserVip()
{
	int _vipLevel = 0;
	ccColor3B _color = ccc3(167, 169, 169);
	m_pTopPanel->getSkel("skel_vip_mark")->setVisible(true);

	int _vipColorID = 1;
	switch (_vipLevel)
	{
	case 0:
		_vipColorID = 1;
		_color = ccc3(113, 66, 18);
		break;
	case 1:
	case 2:
		_vipColorID = 2;
		_color = ccc3(249, 223, 202);
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		_vipColorID = 3;
		_color = ccc3(217, 224, 224);
		break;
	case 7:
	case 8:
	case 9:
		_vipColorID = 4;
		_color = ccc3(238, 218, 178);
		break;
	case 10:
	case 11:
	case 12:
		_vipColorID = 5;
		_color = ccc3(255, 255, 255);
		break;
	case 13:
	case 14:
	case 15:
		_vipColorID = 6;
		_color = ccc3(253, 236, 179);
		break;
	}

	string _frameName = "vip_" + StringConverter::toString(_vipColorID);

	m_pTopPanel->getSkel("skel_vip_mark")->playAnimation(_frameName);
	m_pTopPanel->getLabel("txt_vipsum")->setColor(_color);
	m_pTopPanel->getLabel("txt_vipsum")->setString(StringConverter::toString(_vipLevel).c_str());

}

void SynopsisUiTutorial::UpdateUserMoney()
{
	int64 _money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
	string _strMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_money), 3);
	m_pTopPanel->getLabel("txt_gold")->setString(_strMoney.c_str());
}

void SynopsisUiTutorial::UpdateUserLevel()
{
	int _level = PokerRankHelper::getLevel();
	string _strLevel = StringConverter::toString(_level);
	m_pTopPanel->getLabel("str_userlevel")->setString(_strLevel.c_str());
	m_pTopPanel->getLabel("str_userlevel")->setStroke(1, Color4B::BLACK, 76);

	int32 _exp = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Exp;
	int32 _accumExp = GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata(_level - 1).accumexp();
	int32 _needExp = GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata(_level - 1).needexp();

	int32 _leftExp = _accumExp - _exp;
	if (_leftExp < 0)
		_leftExp = 0;
	int _ExpPer = (_needExp - _leftExp) * 100 / _needExp;

	if (_ExpPer >= 100)
		_ExpPer = 100;

	float _width = 142.f;
	float _startPos = m_pTopPanel->m_ExpStartPos.x;
	float _barWidth = m_pTopPanel->getSkel("skel_expbar_center")->getBounding().size.width;
	float _scaleX = _width / _barWidth;

	if (_scaleX > 71.f)
		_scaleX = 71.f;

	m_pTopPanel->getSkel("skel_expbar_center")->setPositionX(_startPos + (_width * ((float)_ExpPer / 200.f)));
	m_pTopPanel->getSkel("skel_expbar_center")->setScaleX(_scaleX * ((float)_ExpPer / 100.f));
}

void SynopsisUiTutorial::UpdateUserNickName()
{
	string _strName = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName;
	m_pTopPanel->getLabel("txt_username")->setString(_strName.c_str());
	m_pTopPanel->getLabel("txt_usernameshadow")->setString(_strName.c_str());
}

void SynopsisUiTutorial::UpdateUserChip()
{
	int64 _chip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	string _strChip = StringConverter::toString(_chip);
	m_pTopPanel->getLabel("txt_chip")->setString(_strChip.c_str());

}

void SynopsisUiTutorial::UpdateUserCash()
{
	int32 _ruby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
	string _strRuby = StringConverter::toString(_ruby);
	m_pTopPanel->getLabel("txt_rubby")->setString(_strRuby.c_str());
}

void SynopsisUiTutorial::ReadyAppear()
{
	m_pMyHomeButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1");
	m_pLetterButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2");
	m_pFriendButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3");
	m_pMissionButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4");
	m_pShopButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button5");

	m_pLeftLabel[0] = m_pLeftUiPanel->getLabel("txt_myroom");
	m_pLeftLabel[1] = m_pLeftUiPanel->getLabel("txt_letter");
	m_pLeftLabel[2] = m_pLeftUiPanel->getLabel("txt_friend");
	m_pLeftLabel[3] = m_pLeftUiPanel->getLabel("txt_mission");
	m_pLeftLabel[4] = m_pLeftUiPanel->getLabel("txt_shop");
	m_pLeftLabelBack[0] = m_pLeftUiPanel->getLabel("txt_myroom_back");
	m_pLeftLabelBack[1] = m_pLeftUiPanel->getLabel("txt_letter_back");
	m_pLeftLabelBack[2] = m_pLeftUiPanel->getLabel("txt_friend_back");
	m_pLeftLabelBack[3] = m_pLeftUiPanel->getLabel("txt_mission_back");
	m_pLeftLabelBack[4] = m_pLeftUiPanel->getLabel("txt_shop_back");

	for (int _i = 0; _i < 5; _i++)
	{
		m_LeftLabelShowPos[_i] = m_pLeftLabel[_i]->getPosition();
		m_LeftLabelHidePos[_i] = m_pLeftLabel[_i]->getPosition() - ccp(300.f, 0.f);

		m_LeftLabelBackShowPos[_i] = m_pLeftLabelBack[_i]->getPosition();
		m_LeftLabelBackHidePos[_i] = m_pLeftLabelBack[_i]->getPosition() - ccp(300.f, 0.f);

		m_pLeftLabel[_i]->setVisible(false);
		m_pLeftLabel[_i]->setPosition(m_LeftLabelHidePos[_i]);
		m_pLeftLabelBack[_i]->setVisible(false);
		m_pLeftLabelBack[_i]->setPosition(m_LeftLabelBackHidePos[_i]);

	}

	m_MyHomeposHide = m_pMyHomeButton->getPosition() - ccp(300.f, 0.f);
	m_MyHomeposSHow = m_pMyHomeButton->getPosition();
	m_LetterposHide = m_pLetterButton->getPosition() - ccp(300.f, 0.f);
	m_LetterposSHow = m_pLetterButton->getPosition();
	m_FriendposHide = m_pFriendButton->getPosition() - ccp(300.f, 0.f);
	m_FriendposSHow = m_pFriendButton->getPosition();
	m_MissionposHide = m_pMissionButton->getPosition() - ccp(300.f, 0.f);
	m_MissionposSHow = m_pMissionButton->getPosition();
	m_ShopposHide = m_pShopButton->getPosition() - ccp(300.f, 0.f);
	m_ShopposSHow = m_pShopButton->getPosition();
	m_pos7PokerHide = m_p7PokerButton->getPosition() + ccp(600.f, 0.f);
	m_pos7PokerSHow = m_p7PokerButton->getPosition();
	m_posHighLowHide = m_pHighLowButton->getPosition() + ccp(600.f, 0.f);
	m_posHighLowShow = m_pHighLowButton->getPosition();
	m_posBadugiHide = m_pBadugiButton->getPosition() + ccp(600.f, 0.f);
	m_posBadugiShow = m_pBadugiButton->getPosition();
	//m_posHoldemHide = m_pHoldemButton->getPosition() + ccp(600.f, 0.f);
	//m_posHoldemShow = m_pHoldemButton->getPosition();
	m_posMiniGameHide = m_pMiniGameButton->getPosition() + ccp(600.f, 0.f);
	m_posMiniGameShow = m_pMiniGameButton->getPosition();

	m_posDailyCheckHide = m_pDailyCheckButton->getPosition() - ccp(0.f, 300.f);
	m_posDailyCheckShow = m_pDailyCheckButton->getPosition();
	m_posRankingHide = m_pRankingButton->getPosition() - ccp(0.f, 300.f);
	m_posRankingShow = m_pRankingButton->getPosition();
	m_posReplayHide = m_pReplayButton->getPosition() - ccp(0.f, 300.f);
	m_posReplayShow = m_pReplayButton->getPosition();

	m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1")->setPosition(m_MyHomeposHide);
	m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2")->setPosition(m_LetterposHide);
	m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3")->setPosition(m_FriendposHide);
	m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4")->setPosition(m_MissionposHide);
	m_pLeftUiPanel->getButton("sbtn_lobbyleft_button5")->setPosition(m_ShopposHide);
	m_p7PokerButton->setPosition(m_pos7PokerHide);
	m_pHighLowButton->setPosition(m_posHighLowHide);
	m_pBadugiButton->setPosition(m_posBadugiHide);
	//m_pHoldemButton->setPosition(m_posHoldemHide);
	m_pMiniGameButton->setPosition(m_posMiniGameHide);
	m_pDailyCheckButton->setPosition(m_posDailyCheckHide);
	m_pRankingButton->setPosition(m_posRankingHide);
	m_pReplayButton->setPosition(m_posReplayHide);
}

void SynopsisUiTutorial::AppearUi()
{
	setVisible(true);
	//left
	CCPoint _lastPos = m_pMyHomeButton->getPosition() + ccp(300, 0);
	m_pMyHomeButton->runAction(CCSequence::create(
		CCDelayTime::create(0.6f),
		CCMoveTo::create(0.4f, _lastPos),
		NULL));

	_lastPos = m_pLetterButton->getPosition() + ccp(300, 0);
	m_pLetterButton->runAction(CCSequence::create(
		CCDelayTime::create(0.7f),
		CCMoveTo::create(0.4f, _lastPos),
		NULL));

	_lastPos = m_pFriendButton->getPosition() + ccp(300, 0);
	m_pFriendButton->runAction(CCSequence::create(
		CCDelayTime::create(0.8f),
		CCMoveTo::create(0.4f, _lastPos),
		NULL));

	_lastPos = m_pMissionButton->getPosition() + ccp(300, 0);
	m_pMissionButton->runAction(CCSequence::create(
		CCDelayTime::create(0.9f),
		CCMoveTo::create(0.4f, _lastPos),
		NULL));

	_lastPos = m_pShopButton->getPosition() + ccp(300, 0);
	m_pShopButton->runAction(CCSequence::create(
		CCDelayTime::create(1.f),
		CCMoveTo::create(0.4f, _lastPos),
		NULL));

	for (int _i = 0; _i < 5; _i++)
	{
		m_pLeftLabel[_i]->setVisible(true);
		m_pLeftLabelBack[_i]->setVisible(true);

		m_pLeftLabel[_i]->runAction(CCSequence::create(
			CCDelayTime::create(0.6f + (0.1f *(_i))),
			CCMoveTo::create(0.4f, m_LeftLabelShowPos[_i]),
			NULL));

		m_pLeftLabelBack[_i]->runAction(CCSequence::create(
			CCDelayTime::create(0.6f + (0.1f *(_i))),
			CCMoveTo::create(0.4f, m_LeftLabelBackShowPos[_i]),
			NULL));
	}

	//right
	m_p7PokerButton->runAction(CCSequence::create(
		CCDelayTime::create(0.6f),
		CCMoveTo::create(0.4f, m_pos7PokerSHow),
		NULL));

	m_pHighLowButton->runAction(CCSequence::create(
		CCDelayTime::create(0.7f),
		CCMoveTo::create(0.4f, m_posHighLowShow),
		NULL));

	m_pBadugiButton->runAction(CCSequence::create(
		CCDelayTime::create(0.8f),
		CCMoveTo::create(0.4f, m_posBadugiShow),
		NULL));

	//m_pHoldemButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.9f),
	//	CCMoveTo::create(0.4f, m_posHoldemShow),
	//	NULL));

	m_pMiniGameButton->runAction(CCSequence::create(
		CCDelayTime::create(1.f),
		CCMoveTo::create(0.4f, m_posMiniGameShow),
		NULL));

	m_pDailyCheckButton->runAction(CCSequence::create(
		CCDelayTime::create(0.8f),
		CCMoveTo::create(0.4f, m_posDailyCheckShow),
		NULL));

	m_pRankingButton->runAction(CCSequence::create(
		CCDelayTime::create(0.7f),
		CCMoveTo::create(0.4f, m_posRankingShow),
		NULL));

	m_pReplayButton->runAction(CCSequence::create(
		CCDelayTime::create(0.6f),
		CCMoveTo::create(0.4f, m_posReplayShow),
		NULL));

	m_BlockTime = 1.4f;
}

void SynopsisUiTutorial::EndTutorial()
{
	if (LayerManager::getSingletonPtr()->hasLayer("Main") &&
		LayerManager::getSingletonPtr()->hasLayer("Information") &&
		LayerManager::getSingletonPtr()->hasLayer("Dialog"))
	{
		SynopsisMainPanel* _pMainPanel = dynamic_cast<SynopsisMainPanel*>(LayerManager::getSingletonPtr()->getLayer("Main"));
		SynopsisCharacterInfoPanel* _pInfoPanel = dynamic_cast<SynopsisCharacterInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("Information"));
		SynopsisDialogPanel* _pDialogPanel = dynamic_cast<SynopsisDialogPanel*>(LayerManager::getSingletonPtr()->getLayer("Dialog"));

		setTouchable(false);
		m_BlockButton->setEnable(false);

		_pMainPanel->ShowDealer(true);
		_pMainPanel->ShowCharacter(false);
		_pInfoPanel->ShowInfo(false);
		_pDialogPanel->setTouchable(true);
		_pDialogPanel->ShowDialog(true);
		_pDialogPanel->ShowText(7);
		_pDialogPanel->m_TextIdx = 8;
	}
}

void SynopsisUiTutorial::InitTopUiPanel()
{
	//m_pTopPanel = new LobbyTopUiPanel();
	//CCPoint _TopUiPos = m_UiPanel->getDummy("dmy_top_panel").origin;
	//_TopUiPos.y = -_TopUiPos.y;
	//m_pTopPanel->setPosition(_TopUiPos);

	//LayerManager::getSingleton().addLayer("LobbyTopUI", m_pTopPanel);
	//LayerManager::getSingleton().pushLayer("LobbyTopUI", 200);

	//m_pOptionBackButtion = m_pTopPanel->getButton("sbtn_option_button");
}

void SynopsisUiTutorial::InitLeftUiPanel()
{
	//m_pLeftUiPanel = new LobbyLeftUiPanel();
	//CCPoint _LeftUiPos = m_UiPanel->getDummy("dmy_lobby_left_button").origin;
	//_LeftUiPos.y = -_LeftUiPos.y;
	//m_pLeftUiPanel->setPosition(_LeftUiPos);

	//LayerManager::getSingleton().addLayer("LobbyLeftUI", m_pLeftUiPanel);
	//LayerManager::getSingleton().pushLayer("LobbyLeftUI");
}

void SynopsisUiTutorial::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}