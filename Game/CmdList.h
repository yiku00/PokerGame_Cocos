#pragma once

#include "NxFramework.h"
#include "CmdBase.h"

#define STATIC_PHOTO_FOLDER		"staticPhoto"
#define TEMP_PHOTO_FOLDER		"staticPhoto"

enum DOWNLOAD_FILE_TYPE
{
	MY_PHOTO = 0,
	FRIEND_PHOTO = 1,
	RECOMMEND_PHOTO = 2,
	RANKING_PHOTO = 3,
	TOURNAMENT_PHOTO = 4,
	SURVIVAL_PHOTO = 5,
	GAMEUSER_PHOTO = 6,
	MYROOM_PHOTO = 7,
	SNS_FRIEND_PHOTO = 8,
};


struct STCMD_GAMEVIL_PROFILE_ACK : public STCMD_META<STCMD_GAMEVIL_PROFILE_ACK>
{
	STCMD_GAMEVIL_PROFILE_ACK()
	{

	}
};

struct STCMD_GAMEVIL_SESSION_KEY : public STCMD_META<STCMD_GAMEVIL_SESSION_KEY>
{
	STCMD_GAMEVIL_SESSION_KEY()
	{
	}

	std::string strSessionKey;
};

struct STCMD_GAMEVIL_USER_ACCEPT_C2DM : public STCMD_META<STCMD_GAMEVIL_USER_ACCEPT_C2DM>
{
	STCMD_GAMEVIL_USER_ACCEPT_C2DM()
	{
		bIsAccept = false;
	}

	bool bIsAccept;
};

struct STCMD_GAMEVIL_LOGIN_RESULT : public STCMD_META<STCMD_GAMEVIL_LOGIN_RESULT>
{
	STCMD_GAMEVIL_LOGIN_RESULT()
	{
		success = false;
	}

	bool success;
};

#define LOGIN_SUCCESS_CODE 1000
struct STCMD_ILOVEGAME_LOGIN_RESULT : public STCMD_META<STCMD_ILOVEGAME_LOGIN_RESULT>
{
	bool success;
	int code;
	string result;
};

struct STCMD_ILOVEGAME_LOGINWITHTOKEN_RESULT : public STCMD_META<STCMD_ILOVEGAME_LOGINWITHTOKEN_RESULT>
{
	bool isSimple;
	bool success;
	int code;
	string result;
};

struct STCMD_ILOVEGAME_REGISTER_RESULT : public STCMD_META<STCMD_ILOVEGAME_REGISTER_RESULT>
{
	bool success;
	int code;
	string result;
};

struct STCMD_ILOVEGAME_LOGOUT_RESULT : public STCMD_META<STCMD_ILOVEGAME_LOGOUT_RESULT>
{
	bool success;
	int code;
	string result;
};

struct STCMD_ILOVEGAME_UNREGISTER_RESULT : public STCMD_META<STCMD_ILOVEGAME_UNREGISTER_RESULT>
{
	bool success;
	int code;
	string result;
};

struct STCMD_ILOVEGAME_CHARGE_RESULT : public STCMD_META<STCMD_ILOVEGAME_CHARGE_RESULT>
{
	bool success;
	int code;
	string result;

	string serverId;
	string productId;
};

struct STCMD_ILOVEGAME_COUPON_RESULT : public STCMD_META<STCMD_ILOVEGAME_COUPON_RESULT>
{
	bool success;
	int code;
	string result;

	string number;
};

struct STCMD_ILOVEGAME_SERVER_RESULT : public STCMD_META<STCMD_ILOVEGAME_SERVER_RESULT>
{
	bool success;
	string result;
};

struct STCMD_ILOVEGAME_FRIEND_RESULT : public STCMD_META<STCMD_ILOVEGAME_FRIEND_RESULT>
{
	int count;
	string result;
};

struct STCMD_ILOVEGAME_INVITE_RESULT : public STCMD_META<STCMD_ILOVEGAME_INVITE_RESULT>
{
	int count;
	string result;
};

struct STCMD_ILOVEGAME_SEND_PLAYERINFO_RESULT : public STCMD_META<STCMD_ILOVEGAME_SEND_PLAYERINFO_RESULT>
{
	bool success;
	int code;
	string result;
};

struct STCMD_ILOVEGAME_SEND_INVITE_RESULT : public STCMD_META<STCMD_ILOVEGAME_SEND_INVITE_RESULT>
{
	bool success;
	int code;
	string result;

	string userId;
	string serverId;
};

struct STCMD_ILOVEGAME_SEND_PUSH_RESULT : public STCMD_META<STCMD_ILOVEGAME_SEND_PUSH_RESULT>
{
	bool success;
	int code;
	string result;

	string userName;
	string message;
};

struct STCMD_ILOVEGAME_SEND_MESSAGE_RESULT : public STCMD_META<STCMD_ILOVEGAME_SEND_MESSAGE_RESULT>
{
	bool success;
	int code;
	string result;

	string userName;
	string templateId;
};

struct STCMD_ILOVEGAME_SET_MESSAGE_BLOCK_RESULT : public STCMD_META<STCMD_ILOVEGAME_SET_MESSAGE_BLOCK_RESULT>
{
	bool success;
	int code;
	string result;

	bool enable;
};

struct STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ : public STCMD_META<STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ>
{
	string userId;
	std::string downloadUrl;
};

struct STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_ACK : public STCMD_META<STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_ACK>
{
	string userId;
	string imagePath;
};

struct STCMD_ILOVEGAME_SET_FACEBOOK_POSTING_RESULT : public STCMD_META<STCMD_ILOVEGAME_SET_FACEBOOK_POSTING_RESULT>
{
	bool success;
	int code;
	string result;
};


struct STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ : public STCMD_META < STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ >
{
	string userId;
	std::string downloadUrl;
	DOWNLOAD_FILE_TYPE param;
	int dParam;
};

struct STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK : public STCMD_META < STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK >
{
	string userId;
	string imagePath;
	DOWNLOAD_FILE_TYPE param;
	int dParam;
};

struct STCMD_GOOGLE_LOGIN_RESULT : public STCMD_META < STCMD_GOOGLE_LOGIN_RESULT >
{
	bool isSucess;
	string googleID;
	string googleName;
	string googleEmail;
	string googlePhotoUrl;
};

struct STCMD_GOOGLE_LOGOUT_RESULT : public STCMD_META < STCMD_GOOGLE_LOGOUT_RESULT >
{
	bool isSucess;	
};

struct STCMD_IAP_ONESTORE_REQUEST_RESULT : public STCMD_META < STCMD_IAP_ONESTORE_REQUEST_RESULT >
{
	bool isSucess;
	string errMsg;
	string tid;			//서버에서 주는 유니크값
	string pid;
	string txid;		//영수증 idx
	string receipt;		
};

struct STCMD_IAP_ONESTORE_REMAIN_REQUEST_RESULT : public STCMD_META < STCMD_IAP_ONESTORE_REMAIN_REQUEST_RESULT >
{
	bool isSucess;
	string errMsg;
	string pid;
	string tid;			//서버에서 주는 유니크값
	string txid;		//영수증 idx
	string receipt;
};

struct STCMD_IAP_GOOGLESTORE_REQUEST_RESULT : public STCMD_META < STCMD_IAP_GOOGLESTORE_REQUEST_RESULT >
{
	bool isSucess;
	string errMsg;
	string tid;				//서버에서 주는 유니크값
	string orderId;			
	string purchaseToken;
};

struct STCMD_UNITADS_FINISH : public STCMD_META < STCMD_UNITADS_FINISH >
{
	string zoneId;
};

struct STCMD_VUNGLE_VIDEO_RESULT : public STCMD_META < STCMD_VUNGLE_VIDEO_RESULT >
{
	bool isResult;
};

struct STCMD_ADCOLONY_VIDEO_RESULT : public STCMD_META < STCMD_ADCOLONY_VIDEO_RESULT >
{
	bool isResult;
};

struct STCMD_ADMOB_VIDEO_RESULT : public STCMD_META < STCMD_ADMOB_VIDEO_RESULT >
{
	bool isResult;
	bool isLoaded;
};

struct STCMD_IAP_GOOGLESTORE_CHECK_REQUEST_RESULT : public STCMD_META < STCMD_IAP_GOOGLESTORE_CHECK_REQUEST_RESULT >
{
	bool isSucess;
	string inappId;
	string tid;				//서버에서 주는 유니크값
	string orderId;
	string purchaseToken;
};

struct STCMD_TAPJOY_AWARD_CURRENCY : public STCMD_META < STCMD_TAPJOY_AWARD_CURRENCY >
{
	int  amount;	
};