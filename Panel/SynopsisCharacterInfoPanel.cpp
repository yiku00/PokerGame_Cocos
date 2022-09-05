#include "pch.h"
#include "SynopsisCharacterInfoPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
//#include "SimplePopupPanel.h"
//#include "HeroApp.h"

#include "Web/WebService.h"
#include "SynopsisUiPanel.h"
#include "GameStringDepot.h"

SynopsisCharacterInfoPanel::SynopsisCharacterInfoPanel()
{
	InitPanel();
	InitImage();
	InitButton();

	ShowInfo(false);

	setTouchable(false);
	setButtonListener(this);
}

SynopsisCharacterInfoPanel::~SynopsisCharacterInfoPanel()
{
	//destruct();
}

void SynopsisCharacterInfoPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_synopsis_character_info.mxml");
	getLabel("txt_gender")->setString(GameStringDepot::getSingleton().getString("dmy_synopsis_character_info_GENDER").c_str());
	getLabel("txt_age")->setString(GameStringDepot::getSingleton().getString("dmy_synopsis_character_info_AGE").c_str());
	getLabel("txt_jab")->setString(GameStringDepot::getSingleton().getString("dmy_synopsis_character_info_JOB").c_str());


	m_contentSize = getContentSize();
	if (LayerManager::getSingletonPtr()->hasLayer("MainUi"))
	{
		SynopsisUiPanel* _pPanel = dynamic_cast<SynopsisUiPanel*>(LayerManager::getSingletonPtr()->getLayer("MainUi"));
		setPositionX(_pPanel->m_characterInfoRect.origin.x);
		setPositionY(-_pPanel->m_characterInfoRect.origin.y);		
	}
}

void SynopsisCharacterInfoPanel::InitImage()
{
	//m_AgeLabel = getLabel("txt_age");
	//m_JobLabel = getLabel("txt_job");
	
	m_NameText = getLabel("txt_character_name");
	m_AgeText = getLabel("txt_age_sum");
	m_JobText = getLabel("txt_jab_sum");
	m_StoryText = getLabel("txt_story_content");
	mGenderLabel = getLabel("txt_gender_sum");

	//m_AgeLabel->setString("");
	//m_JobLabel->setString("");
	
	m_NameText->setString("");
	m_AgeText->setString("");
	m_JobText->setString("");
	m_StoryText->setString("");
	mGenderLabel->setString("");

	//m_AgeLabel->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//m_JobLabel->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	
	m_NameText->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_AgeText->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_JobText->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_StoryText->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
}


void SynopsisCharacterInfoPanel::InitButton()
{

}


void SynopsisCharacterInfoPanel::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void SynopsisCharacterInfoPanel::onClicked(const string& name)
{
	return;
	//if (mLoginProcess)
	//	return;

	//if (name == "sbtn_gameout")
	//{
	//	SceneUtil::changeScene(SceneUtil::SceneLobby);
	//}
}

void SynopsisCharacterInfoPanel::update(float dt)
{

}

bool SynopsisCharacterInfoPanel::handling(STCMD &stCmd)
{
	//if (!mLoginProcess)
	//	return false;

	return false;
}

void SynopsisCharacterInfoPanel::ShowInfo(bool _visible, int _infoIdx)
{
	setVisible(_visible);

	if (_infoIdx == -1)
		return;

	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_CharacterData _data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata(_i);
		if (_infoIdx == _data.id())
		{
			string _profile = _data.age();
			string _name = _data.name();
			string _job = _data.job();
			string _desc = _data.desc();
			string gender = _data.gender();

			m_NameText->setString(_name.c_str());
			m_AgeText->setString(_profile.c_str());
			m_JobText->setString(_job.c_str());
			m_StoryText->setString(_desc.c_str());
			mGenderLabel->setString(gender.c_str());
			return;
		}
	}
}
void SynopsisCharacterInfoPanel::onEnter()
{
	Panel::onEnter();

	scheduleUpdate();
}
