/********************************************************************
	file name:	ILoveGameImpl.h

	purpose:	ILoveGameSDK
	*********************************************************************/
#pragma once

#include "SocialInterface.h"

class ILoveGameImpl : public CCObject, public SocialInterface
{
public:
	ILoveGameImpl() {};
	~ILoveGameImpl() {};

public: // SocialInterface
	void initialize() {}
	string getMarket();
	bool isAgreement();
	void setAgreement(bool agree);
	void openAgreement();
	bool isValid();
	void login();
	void loginWithToken(bool simple);
	void loginId(const string& id, const string& pw);
	void registerId(const string& id, const string& pw);
	void logout();
	void unregister();

	bool isSimpleLogin() { return mIsSimpleLogin; }

	// My entity
	string getNickname();
	string getName();
	string getId();
	string getProfileImageUrl();

	void charge(const string& serverId, const string& productId);

	void intro();
	void openEvent();
	void openHomepage();
	void openHelp();

	void coupon(const string& number);

	void getServerList(const string& sort);
	void getFriendList();
	void getInviteList();
	int getInviteCount();

	void sendPlayerInfo(const string& info);
	void sendInvite(const string& userId, const string& serverId);

	void sendPush(const string& username, const string& message);
	void sendMessage(const string& username, const string& templateId);

	bool getMessageBlock();
	void setMessageBlock(bool enable);

	void sendFaceBookPosting(const string& name, const string& caption, const string& description, const string& link, const string& picture, const string& postingcode);
	bool isGuest() { return false; }
	void loginGuest() {};
	bool isGuestVisible() { return false; }
	bool isFriendVisible() { return true; }

private:
	void _recvFriendTestRes(HttpMessage* msg);
	void _recvInviteTestRes(HttpMessage* msg);
	void _recvServerListRes(HttpMessage* msg);

private:
	bool mIsSimpleLogin;
};
