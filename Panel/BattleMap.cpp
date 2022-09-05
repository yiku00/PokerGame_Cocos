#include "pch.h"
#include "BattleMap.h"
#include "RefApp.h"

#define BACKGROUND_LAYER_COUNT 4

BattleMap::BattleMap(const string& mapFile, bool bg /*= false*/)
{
	mBackgroundUse = bg;
	if (mapFile.find(".tmx") == string::npos) {
		setMap("maps/" + mapFile + ".tmx");
	}
	else {
		setMap(mapFile);
	}

	mBackgrounds.clear();

	setManualMode(true);
	_setTroopPositions();

	mRepeatScroll = false;
	mRepeatScrollReady = false;
	mScrollPlaying = false;

	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		SuperObject* camera = new SuperObject(true, true);
		camera->setSuperAnim("sam/fx_camera.sam");
		if (!bg)
			camera->attachToSprite("fx_camera");
		camera->readyAnimation("shake1_bg1");
		addChild(camera);
		camera->release();

		mFxCameras.push_back(camera);
	}
}

BattleMap::~BattleMap()
{
	mTroopPositions.clear();	
}

void BattleMap::setBattleBG(const string& groupName)
{
	CCPoint tempRect = getCurrentCenter();

	NXASSERT(mFxCameras.size() == BACKGROUND_LAYER_COUNT);

	//멀리 있는거 먼저
	if (mBackgroundUse) {
		_makeDistanceLayer("background", this);
		//_makeDistanceLayer("bg_move1_2", this);
		//_makeDistanceLayer("bg_move1_3", this);
		//_makeDistanceLayer("bg_move1_4", this);
	}
	else {
		//_makeDistanceLayer("bg_move1_1", mFxCameras[0]);
		//_makeDistanceLayer("bg_move1_2", mFxCameras[1]);
		//_makeDistanceLayer("bg_move1_3", mFxCameras[2]);
		//_makeDistanceLayer("bg_move1_4", mFxCameras[3]);
		_makeDistanceLayer("background", mFxCameras[0]);
		//_makeDistanceLayer("background", mFxCameras[1]);
		//_makeDistanceLayer("background", mFxCameras[2]);
		//_makeDistanceLayer("background", mFxCameras[3]);
	}

	setBackgroundScroll(false);
}

void BattleMap::setBattleBG()
{
	CCPoint tempRect = getCurrentCenter();

	NXASSERT(mFxCameras.size() == BACKGROUND_LAYER_COUNT);

	//멀리 있는거 먼저
	if (mBackgroundUse) {
		_makeDistanceLayer("bg_move1_1", this);
		_makeDistanceLayer("bg_move1_2", this);
		_makeDistanceLayer("bg_move1_3", this);
		_makeDistanceLayer("bg_move1_4", this);
	}
	else {
		_makeDistanceLayer("background", mFxCameras[0]);
	}

	setBackgroundScroll(false);

}

void BattleMap::_makeDistanceLayer(const string& groupName, CCNode* parent)
{
	CCTMXObjectGroup *group = mMap->objectGroupNamed(groupName.c_str());
	NXASSERT(group);
	auto& objects = group->getObjects();
	if (objects.size() > 0)
	{
		for (auto& v : objects)
		{
			auto& dict = v.asValueMap();
			
			string sam = dict.find("sam") != dict.end() ? dict.at("sam").asString() : "";
			string spine = dict.find("spine") != dict.end() ? dict.at("spine").asString() : "";
			string label = dict.find("label") != dict.end() ? dict.at("label").asString() : "";
			int x = dict.find("x") != dict.end() ? dict.at("x").asInt() : 0;
			int y = dict.find("y") != dict.end() ? dict.at("y").asInt() : 0;
			

			// 배경 오브젝트 추가
			if (!sam.empty()) {
				SuperObject* bg = new SuperObject();
				bg->setSuperAnim("maps/" + sam + ".sam");
				bg->playAnimation(label, true);
				bg->setPosition(ccp(x, y));
				parent->addChild(bg);
				bg->release();

				mBackgrounds.push_back(bg);
			}
			else if (!spine.empty()) {
				SkelObject* bg = new SkelObject();
				bg->setSkelAnim("maps/" + spine + ".json");
				bg->playAnimation(label, true);
				bg->setPosition(ccp(x, y));
				parent->addChild(bg);
				bg->release();
			}
		}
	}	
}

void BattleMap::_setTroopPositions()
{
	CCTMXObjectGroup *group = mMap->objectGroupNamed("tile");

	auto& objects = group->getObjects();
	if (objects.size() > 0)
	{
		for (auto& v : objects)
		{
			auto& dict = v.asValueMap();

			std::string key = "x";
			int x = dict.find(key) != dict.end() ? dict.at(key).asInt() : 0;
			key = "y";
			int y = dict.find(key) != dict.end() ? dict.at(key).asInt() : 0;//dynamic_cast<NSNumber*>(dict->objectForKey("y"))->getNumber();
			key = "width";
			int width = dict.find(key) != dict.end() ? dict.at(key).asInt() : 0;//dynamic_cast<NSNumber*>(dict->objectForKey("width"))->getNumber();
			key = "height";
			int height = dict.find(key) != dict.end() ? dict.at(key).asInt() : 0;//dynamic_cast<NSNumber*>(dict->objectForKey("height"))->getNumber();
			key = "type";
			string type = dict.find(key) != dict.end() ? dict.at(key).asString() : "";
			key = "name";
			string name = dict.find(key) != dict.end() ? dict.at(key).asString() : "";

			mTroopPositions.insert(TroopPositionPair(name, ccp(x, y + height/2.f)));
			mTroopRects.insert(TroopRectPair(name, CCRectMake(x, y,width , height)));

			CharacterLocation loc;
			loc.position = ccp(x, y + height / 2.f);
			loc.rect = CCRectMake(x, y, width, height);
			loc.zorder = dict.find("zorder") != dict.end() ? dict.at("zorder").asInt() : 0;
			mTroopLocations.insert(TroopLocationPair(name, loc));
		}
	}
}

const CCPoint& BattleMap::getTroopPosition(const string& name)
{
	NXASSERT(mTroopPositions.find(name) != mTroopPositions.end());
	return mTroopPositions.find(name)->second;
}

const CCRect& BattleMap::getTroopRects(const string& name)
{
	NXASSERT(mTroopRects.find(name) != mTroopRects.end());
	return mTroopRects.find(name)->second;
}

const CharacterLocation& BattleMap::getTroopLocation(const string& name)
{
	NXASSERT(mTroopLocations.find(name) != mTroopLocations.end());
	return mTroopLocations.find(name)->second;

}

void BattleMap::setBackgroundScroll(bool play)
{
	mScrollPlaying = play;
	
	if (play) {
		for (SuperObjectContainer::iterator it = mBackgrounds.begin(); it != mBackgrounds.end(); ++it)
		{
			(*it)->resumeAnimation();				
		}
	}
	else {

		for (SuperObjectContainer::iterator it = mBackgrounds.begin(); it != mBackgrounds.end(); ++it)
		{
			(*it)->pauseAnimation();				
		}
	}
}

bool BattleMap::isScrolling()
{
	return mScrollPlaying;
}

void BattleMap::onEvent(const string& event, const EventParamList* params /*= nullptr*/)
{
	if (event == "Shake") {
		const string& shakeType = _getShakeTypeParam(params);
		for (uint i = 0; i < mFxCameras.size(); ++i)
		{
			string postFix = i % 2 ? "_bg1" : "_bg2";
			mFxCameras[i]->playAnimation("shake"+shakeType+postFix);
		}
	}
	else if (event == "BattleInfo") {
		for (uint i = 0; i < mFxCameras.size(); ++i)
		{
			mFxCameras[i]->setAnimationSpeed(_getSpeedParam(params));
		}
	}
}

float BattleMap::_getSpeedParam(const EventParamList* params)
{
	float speed = 1.f;
	if (params) {
		auto speedIt = params->find("Speed");
		if (speedIt != params->end()) {
			speed = StringConverter::parseFloat(speedIt->second);
		}
	}

	return speed;
}

const string& BattleMap::_getShakeTypeParam(const EventParamList* params)
{
	NXASSERT(params->find("Type") != params->end());
	return params->find("Type")->second;
}
