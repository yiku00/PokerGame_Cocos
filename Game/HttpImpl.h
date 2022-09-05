/********************************************************************
	filename: 	HttpImpl.h
	
	purpose:	
*********************************************************************/
#pragma once

#include "NxFramework.h"


class HttpImpl : public CCObject, public HttpInterface
{
public:
	HttpImpl();

public:
	void postSend(const HttpMessage& msgSent) override;
	void postReSend(const HttpMessage& msgSent) override;
	void curlError(HttpMessage* msg) override;
	void postStop() override;

	void buildProtocol(HttpMessage* msg, MessageBuffer& sendBuffer) override;
	void parseProtocol(HttpMessage* msg, const MessageBuffer& recvBuffer) override;

	void process() override;
	void timeOut() override;

private:
	void _recv(HttpMessage* msg, HttpMessage* quest = nullptr);
	void _onServerList(const string& msg);
	void _onClose(const string& msg);
	void _onRetry(const string& msg);
	void _clearRetry();
	void _onRelogin(const string& msg);
	void _exit(const string& msg);
	void stopWaitingPanel(bool wait);

private:
	int64 mUID;
	string mSignature;
	int mTicket;
	string checkMsg;
	Mutex mMsgRecvMutex;
	MessageContainer mMsgRecvBuffer;
	MessageContainer mExtraRecvBuffer;

	bool mMsgTransferRetryAuto;
	HttpMessage* mRetryMsg;
	int mRetryCount;
	float mRetryDelay;
	int mRetryMaxCount;	
};