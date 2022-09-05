#include "pch.h"
#include "LobbyRecordRankContentPanel.h"

#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "PokerRankHelper.h"
#include "FriendHelper.h"
#include "CmdList.h"
#include "GameDataManager.h"
#include "PokerResourceHelper.h"


LobbyRecordRankContentPanel::LobbyRecordRankContentPanel()
{
	_init();
}

LobbyRecordRankContentPanel::~LobbyRecordRankContentPanel()
{

}

void LobbyRecordRankContentPanel::_init()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_r_bar.mxml");
	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);	
	mUserName = mMainPanel->getLabel("txt_username");
	mTrophy = mMainPanel->getSkel("skel_rank_1");
	mRankIcon = mMainPanel->getSkel("skel_rank");
	mBg = mMainPanel->getSkel("skel_bar");
	mNoRankLabel = mMainPanel->getLabel("txt_number_rank");
	mNoRankUnderLabel = mMainPanel->getLabel("txt_number_rank_under");

	mNoRankLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordRankContentPanel_NoRank").c_str());
	mNoRankUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyRecordRankContentPanel_NoRank").c_str());

	mUserPhoto = mMainPanel->getImage("dmy_photo");
	mPointBg = mMainPanel->getImage("skel_intable");

	{
		CCPoint _RankPos = mMainPanel->getDummy("dmy_number_rank").origin;
		CCSize _RankSize = mMainPanel->getDummy("dmy_number_rank").size;
		_RankPos.y = DESIGN_HEIGHT - _RankPos.y - (_RankSize.height / 2);
		mRankBmp = CCLabelBMFont::create("", "fonts/number_rank.fnt");
		mRankBmp->setContentSize(_RankSize);
		mRankBmp->setAnchorPoint(ccp(0.5f, 0.5f));
		mRankBmp->setPosition(_RankPos);
		mMainPanel->addChild(mRankBmp);
	}

	{
		CCPoint _RankPos = mMainPanel->getDummy("dmy_number_score").origin;
		CCSize _RankSize = mMainPanel->getDummy("dmy_number_score").size;
		_RankPos.y = DESIGN_HEIGHT - _RankPos.y - (_RankSize.height / 2);
		mReputeBmp = CCLabelBMFont::create("", "fonts/number_score.fnt");
		mReputeBmp->setContentSize(_RankSize);
		mReputeBmp->setAnchorPoint(ccp(0.5f, 0.5f));
		mReputeBmp->setPosition(_RankPos);
		mMainPanel->addChild(mReputeBmp);
	}
	setType(BG_TYPE_MY);
}

void LobbyRecordRankContentPanel::onClicked(const string& buttonName)
{
	
}

void LobbyRecordRankContentPanel::setReputeRankInfo(W_ReputeRankInfo rankInfo)
{
	mReputeRankInfo.CopyFrom(rankInfo);
	//랭킹
	setRank(rankInfo.rank());
	//등급
	setVipIcon(rankInfo.rating());
	//Lv + 유저 아이디
	setUserName(rankInfo.level() , rankInfo.name());	
	//명성
	setRepute(rankInfo.repute());
	
	//사진 적용
	initFriendPhoto(true);
}

void LobbyRecordRankContentPanel::setRank(int rank)
{
	mNoRankLabel->setVisible(rank == 0);
	mNoRankUnderLabel->setVisible(rank == 0);
	if (rank > 0 && rank < 4) {
		mTrophy->playAnimation("rank_" + StringConverter::toString(rank));
		mTrophy->setVisible(true);
		mRankBmp->setVisible(false);
	}
	else if (rank == 0) {
		mRankBmp->setVisible(false);
		mTrophy->setVisible(false);
	}
	else {
		mTrophy->setVisible(false);
		mRankBmp->setString(StringConverter::toString(rank).c_str());
		mRankBmp->setVisible(true);
	}
}

void LobbyRecordRankContentPanel::setUserName(int lv , string name)
{
	string displayStr = NxGetFormatString(GameStringDepot::getSingleton().getString("LEVEL_STYLE"), lv) + " " + name;
	mUserName->setString(displayStr.c_str());
}

void LobbyRecordRankContentPanel::setVipIcon(int vip)
{
	PokerRankHelper::setRankIcon(mRankIcon, vip);
}

void LobbyRecordRankContentPanel::setRepute(int repute)
{
	mReputeBmp->setString(StringConverter::toString(repute).c_str());
}

void LobbyRecordRankContentPanel::setType(BG_TYPE type)
{
	if (type == BG_TYPE_MY) {
		mBg->playAnimation("bar_rlongmy");
	}
	else if (type == BG_TYPE_ODD) {
		mBg->playAnimation("bar_rlonga");
	}
	else if (type == BG_TYPE_EVENT) {
		mBg->playAnimation("bar_rlongb");
	}
}

void LobbyRecordRankContentPanel::initFriendPhoto(bool down)
{
	bool _ret;
	DOWNLOAD_FILE_TYPE _type = DOWNLOAD_FILE_TYPE::RANKING_PHOTO;
	//기덕 default 이미지
	mUserPhoto->setSpriteFrameWithFile(FriendHelper::getDefaultImg());
	if (mReputeRankInfo.has_imageurl() && mReputeRankInfo.imageurl() != "")
	{
		_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
			mReputeRankInfo.name(),
			mReputeRankInfo.imageurl(),
			_type,
			mUserPhoto,
			down,
			STATIC_PHOTO_FOLDER,
			mIdx
			);		
	}
	else
	{
		mUserPhoto->setSpriteFrameWithFile(PokerResourceHelper::getCharacterPhotoImg(mReputeRankInfo.characterid()));
	}

	mUserPhoto->fit(mMainPanel->getDummy("dmy_photo").size);
}

void LobbyRecordRankContentPanel::initMyPhoto()
{
	mUserPhoto->setSpriteFrameWithFile(FriendHelper::getDefaultImg());
	bool _ret;
	//디폴트 이미지로 설정
	mUserPhoto->setSpriteFrameWithFile(FriendHelper::getDefaultImg());
	if (GameDataManager::getSingletonPtr()->m_FacebookUserId != "")
	{
		_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
			GameDataManager::getSingletonPtr()->m_FacebookUserId,
			GameDataManager::getSingletonPtr()->m_FacebookUserPhotoUrl,
			DOWNLOAD_FILE_TYPE::MY_PHOTO,
			mUserPhoto,
			false,
			STATIC_PHOTO_FOLDER
			);

		// 로딩되었으면 이미지를 교체한다.
		if (_ret)
		{
			mUserPhoto->fit(mMainPanel->getDummy("dmy_photo").size);
		}
	}
	else if (GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_thumbnailUrl != "")
	{
		_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
			GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName,
			GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_thumbnailUrl,
			DOWNLOAD_FILE_TYPE::MY_PHOTO,
			mUserPhoto,
			false,
			STATIC_PHOTO_FOLDER
			);

		// 로딩되었으면 이미지를 교체한다.
		if (_ret)
		{
			mUserPhoto->fit(mMainPanel->getDummy("dmy_photo").size);
		}
	}
	else
	{
		mUserPhoto->setSpriteFrameWithFile(FriendHelper::getMycharacterImg());		
	}
	mUserPhoto->fit(mMainPanel->getDummy("dmy_photo").size);
}

void LobbyRecordRankContentPanel::setMyRankType()
{
	mPointBg->setVisible(false);
}
