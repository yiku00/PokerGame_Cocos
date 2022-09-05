/********************************************************************
	file name:	BattleMap.h
	
	purpose:	BattleScene에서 사용하는 맵
*********************************************************************/
#pragma once

#include "MapLayer.h"
#include "FightDefine.h"

class BattleMap : public MapLayer, public Nx::EventDispatcher::Listener 
{
	typedef map<string, CCPoint> TroopPositionContainer;
	typedef map<string, CCRect> TroopRectContainer;
	typedef pair<string, CCPoint> TroopPositionPair;
	typedef pair<string, CCRect> TroopRectPair;

	typedef map<string, CharacterLocation> TroopLocationContainer;
	typedef pair<string, CharacterLocation> TroopLocationPair;

	typedef vector<SuperObject*> SuperObjectContainer;
public:
	BattleMap(const string& mapFile, bool bg = false);
	~BattleMap();

public: // EventDispatcher::Listener
	virtual void onEvent(const string& event, const EventParamList* params = nullptr);

public:
	const CCPoint& getTroopPosition(const string& name);
	const CCRect& getTroopRects(const string& name);
	const CharacterLocation& getTroopLocation(const string& name);

public:

	void setBattleBG(const string& groupName);
	void setBattleBG();

	bool isScrolling();
	
	/*스크롤 관련*/
	void setBackgroundScroll(bool play);

private:
	void _setTroopPositions();
	void _makeDistanceLayer(const string& groupName, CCNode* parent);
	float _getSpeedParam(const EventParamList* params);
	const string& _getShakeTypeParam( const EventParamList* params );


private:
	TroopPositionContainer mTroopPositions;
	TroopRectContainer mTroopRects;

	TroopLocationContainer mTroopLocations;
	
	Layer* mLongDistanceLayer;
	Layer* mMiddleDistaneLayer;
	Layer* mShortDistanceLayer;

	CCPoint mMapLayerStartPoint;

	bool mScrollPlaying;
	bool mRepeatScroll;
	bool mRepeatScrollReady;

	SuperObjectContainer mFxCameras;
	SuperObjectContainer mBackgrounds;

	bool mBackgroundUse;
};
