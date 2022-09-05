/********************************************************************
	file name:	SocialInterface.h

	purpose:	소셜 인터페이스
	*********************************************************************/
#pragma once

class SocialInterface
{
public:
	virtual ~SocialInterface() {}

	virtual void initialize() = 0;
	virtual string getMarket() = 0;
	virtual bool isAgreement() = 0;
	virtual void setAgreement(bool agree) = 0;
	virtual void openAgreement() = 0;
	virtual bool isValid() = 0;
	virtual void login() = 0;
	virtual void loginWithToken(bool simple) = 0;
	virtual void loginId(const string& id, const string& pw) = 0;
	virtual void registerId(const string& id, const string& pw) = 0;
	virtual void logout() = 0;
	virtual void unregister() = 0;

	virtual bool isSimpleLogin() = 0;
	virtual string getNickname() = 0;
	virtual string getName() = 0;
	virtual string getId() = 0;
	virtual string getProfileImageUrl() = 0;

	virtual void charge(const string& serverId, const string& productId) = 0;

	virtual void intro() = 0; // 초기 진입시 호출
	virtual void openEvent() = 0;
	virtual void openHomepage() = 0;
	virtual void openHelp() = 0;

	virtual void coupon(const string& number) = 0;

	virtual void getServerList(const string& sort) = 0;
	virtual void getFriendList() = 0;
	virtual void getInviteList() = 0;
	virtual int getInviteCount() = 0;

	virtual void sendPlayerInfo(const string& info) = 0;
	virtual void sendInvite(const string& userId, const string& serverId) = 0;

	virtual void sendPush(const string& username, const string& message) = 0;
	virtual void sendMessage(const string& username, const string& templateId) = 0;
	virtual bool getMessageBlock() = 0;
	virtual void setMessageBlock(bool enable) = 0;
	virtual void sendFaceBookPosting(const string& name, const string& caption, const string& description, const string& link, const string& picture, const string& postingcode) = 0;

	virtual bool isGuest() = 0;
	virtual void loginGuest() = 0;
	virtual bool isGuestVisible() = 0;
	virtual bool isFriendVisible() = 0;
};
