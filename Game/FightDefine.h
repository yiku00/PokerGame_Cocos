/********************************************************************
	filename: 	FightDefine.h
	
	purpose:	
*********************************************************************/
#pragma once

struct STAT_INFO
{
	int str;
	int intel;
	int dex;
};

struct SKILL_INFO
{
	int index;
	int type;
	int range;
	int damage;
	int speed;
	int rage;
	string model;
	string hit_model;
	string hit_label;
	string particle;
};

struct CHARACTER_INFO
{
	int index;
	int speed;
	int hp;
	int mp;
	int mpa;
	int critical;
	int evade;
	float cooltime;
	string model;
	STAT_INFO stat;
	vector<SKILL_INFO> skills;
};

struct CharacterLocation
{
	CCPoint position;
	CCRect rect;
	int zorder;
};

#define TROOP_COUNT 6
#define ZORDER_HIT_EFFECT 99
#define ZORDER_BULLET 100

enum BattleTurnInfo_DamageType {
	BattleTurnInfo_DamageType_NoDamage = 0,
	BattleTurnInfo_DamageType_Normal = 1,
	BattleTurnInfo_DamageType_Heal = 2,
	BattleTurnInfo_DamageType_Deadly = 3,
	BattleTurnInfo_DamageType_Dodge = 4,
	BattleTurnInfo_DamageType_Invalid = 5,
	BattleTurnInfo_DamageType_Defense = 6,
	BattleTurnInfo_DamageType_Weaken = 7,
	BattleTurnInfo_DamageType_Resist = 8,
	BattleTurnInfo_DamageType_DeadlyAndDefence = 9
};
