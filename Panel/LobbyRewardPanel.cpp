#include "pch.h"
#include "LobbyRewardPanel.h"

#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

LobbyRewardPanel::LobbyRewardPanel(RewardType type)
{
	m_MiddleButton = nullptr;
	m_Type = type;
	InitPanel();
	InitImage();
	initButton();

	setTouchable(false);
	setButtonListener(this);

	SoundManager::getSingleton().playEffect("result_star");
}

LobbyRewardPanel::~LobbyRewardPanel()
{

}

void LobbyRewardPanel::InitPanel()
{
	addMouseBlockPanel(this, true);

	if(m_Type == RewardType::REWARD_TOURNAMENT)
		construct(getMxmlPath() + "pop_tournament_result.mxml");
	else
		construct(getMxmlPath() + "pop_survival_result.mxml");
}

void LobbyRewardPanel::InitImage()
{
	if (m_Type == RewardType::REWARD_TOURNAMENT) {
		getLabel("txt_getfame")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		getLabel("txt_getfame_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		getLabel("txt_getfame")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GET_FAME_LABEL").c_str());
		getLabel("txt_getfame_sum")->setString("");
	}
	getLabel("txt_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_getmoney")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_getmoney_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	
	getLabel("txt_myrank")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_myrank_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_allrank_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_log")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_DEATHMATCH_LABEL").c_str());
	getLabel("txt_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_DEATHMATCH_LABEL").c_str());

	getLabel("txt_getmoney")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GET_GOLD_LABEL").c_str());
	getLabel("txt_getmoney_sum")->setString("");
	
	getLabel("txt_myrank")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MY_RANK_LABEL").c_str());
	getLabel("txt_myrank_sum")->setString("--");
	getLabel("txt_allrank_sum")->setString("/--");
	getLabel("txt_log")->setString("");
}

void LobbyRewardPanel::initButton()
{
	if (m_MiddleButton == nullptr)
	{
		m_MiddleButton = new Panel();
		m_MiddleButton->construct(getMxmlPath() + "dmy_button_middle.mxml");
		CCPoint _pos = getDummy("dmy_button_middle").origin;
		m_MiddleButton->setPositionX(_pos.x);
		m_MiddleButton->setPositionY(-_pos.y);
		addChild(m_MiddleButton);
		m_MiddleButton->release();

		m_MiddleButton->getButton("sbtn_button")->setListener(this);
		m_MiddleButton->getButton("sbtn_button")->setType(Button::NoPressImg);
		m_MiddleButton->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_MiddleButton->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		string _OkText = GameStringDepot::getSingletonPtr()->getString("TXT_OK_LABEL");
		m_MiddleButton->getLabel("txt_button_under")->setString(_OkText.c_str());
		m_MiddleButton->getLabel("txt_button")->setString(_OkText.c_str());
	}

	getButton("sbtn_cancel")->setListener(this);
	getButton("sbtn_cancel")->setType(Button::NoPressImg);
}


bool LobbyRewardPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	
	return false;
}


void LobbyRewardPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void LobbyRewardPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyRewardPanel::onClicked(const string& name)
{
	if (name == "sbtn_button" || name == "sbtn_cancel")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);	
	}
}

void LobbyRewardPanel::resume()
{
}

bool LobbyRewardPanel::handling(STCMD &stCmd)
{
	return false;
}

void LobbyRewardPanel::update(float dt)
{
}


void LobbyRewardPanel::SetTitleText(std::string _title, GameMode _mode)
{
	getLabel("txt_title")->setString(_title.c_str());
	getLabel("txt_title_under")->setString(_title.c_str());
}

void LobbyRewardPanel::SetRewardGold(int64 _gold)
{
	if (_gold == 0)
	{
		getSkel("skel_gtable1")->playAnimation("table_giftoff");
		getSkel("skel_gold")->playAnimation("image_golds_off");
		getLabel("txt_getmoney_sum")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ZERO_NUM").c_str());

		getLabel("txt_getmoney")->setGrayscale(true);
		getLabel("txt_getmoney_sum")->setGrayscale(true);
	}
	else
	{
		getSkel("skel_gtable1")->playAnimation("table_gifty");
		getSkel("skel_gold")->playAnimation("image_golds");
		string _txt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_gold), 1);
		getLabel("txt_getmoney_sum")->setString(_txt.c_str());
	}
}

void LobbyRewardPanel::SetRewardFame(int _fame)
{
	if (m_Type != RewardType::REWARD_TOURNAMENT)
		return;

	if (_fame == 0)
	{
		getSkel("skel_gtable2")->playAnimation("table_giftoff");
		getSkel("skel_fame")->playAnimation("image_fame_off");
		//getLabel("txt_getfame")->setVisible(false);
		getLabel("txt_getfame_sum")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ZERO_NUM").c_str());
		getLabel("txt_getfame")->setGrayscale(true);
		getLabel("txt_getfame_sum")->setGrayscale(true);
	}
	else
	{
		getSkel("skel_gtable2")->playAnimation("table_giftg");
		getSkel("skel_fame")->playAnimation("image_fame");
		//getLabel("txt_getfame")->setVisible(true);
		getLabel("txt_getfame_sum")->setString(StringConverter::toString(_fame).c_str());
	}
}

void LobbyRewardPanel::SetMyRank(int _my, int _all)
{
	if (_my >= 100000)
	{
		getLabel("txt_myrank")->setVisible(false);
		getLabel("txt_myrank_sum")->setVisible(false);
		getLabel("txt_allrank_sum")->setVisible(false);
	}
	else
	{
		getLabel("txt_myrank")->setVisible(true);
		getLabel("txt_myrank_sum")->setVisible(true);
		getLabel("txt_allrank_sum")->setVisible(true);
	}
	string _myRank = StringConverter::toString(_my);
	string _maxRank = "/" + StringConverter::toString(_all);
	getLabel("txt_myrank_sum")->setString(_myRank.c_str());
	getLabel("txt_allrank_sum")->setString(_maxRank.c_str());
}

void LobbyRewardPanel::SetDesc(std::string _desc)
{
	getLabel("txt_log")->setString(_desc.c_str());
}
