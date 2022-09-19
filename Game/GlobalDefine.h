#pragma once

#include "TypeDefine.pb.h"

// Version
#define VERSION_MAJOR 1
#define VERSION_MINOR 7028 //2022년 9월 16일 7029 
//#define VERSION_MINOR 7021 //내부서버 클라 버전
#define VERSION_MAINTENANCE 1
#define VERSION_NAME "BETA 3"

// Designed resolution
//#define DESIGN_WIDTH 960
//#define DESIGN_HEIGHT 640
//#define DESIGN_WIDTH 800
//#define DESIGN_HEIGHT 480

// Node tags
#define TAG_BUILDING 1
#define TAG_WAITING_PANEL 0xFF
#define TAG_FOCUS 0x10
#define TAG_POINT 0x11

// Z order
#define ZORDER_WAITING_PANEL 0xFF

// Game constants
#define TROOP_COUNT 9

// User defaults key
#define USER_DEFAULT_AGREEMENTS "user_agreements"

//
#define HelperCardSeqMarker -1

#define GRAB_WAIT 0.5f
#define GRAB_TAG 1

namespace NSGameConfig
{
	const std::string keyPrologue = "prologue";
	const std::string keySoundBgm = "soundBGM";
	const std::string keySoundEffect = "soundEffect";
	const std::string keyBattleAuto = "BattleAuto";
	const std::string keyBattleSpeed = "BattleSpeed";
	const std::string keyTutorial = "DevTutorial";
	const std::string keyDevelopServer = "DevelopServer";
	const std::string keyPushSend = "keyPushSend";
	const std::string keyServerId = "ServerId";
	const std::string keyMenuOpen = "keyMenuOpen";
	const std::string keyIsAgree = "agreement";
	const std::string keyLoginType = "LoginType";
	const std::string keyGameTurnType = "GameTurnType";
	const std::string keyNotiNotification = "Noti_Notifiction";
}