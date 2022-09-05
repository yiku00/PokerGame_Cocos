#pragma once

#include "ThreadLock.h"
#include "NxFramework.h"
#include "CmdList.h"

struct STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ;
struct STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ;
struct STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK;

class CUrlAutoHandler
{
public:
	~CUrlAutoHandler()
	{
		curl_easy_cleanup(h);
	}

	CUrlAutoHandler() : h(curl_easy_init())
	{
	}

	//operator CURL*() const { return h; }

	CURL *h;
};

struct STCurlWriteMemory 
{
	~STCurlWriteMemory()
	{
		if (nullptr != memory)
		{
			free(memory);
			memory = nullptr;
		}
	}
	STCurlWriteMemory()
	{
		memory = nullptr;
		size = 0;
	}
	char *memory;
	size_t size;
};

class CCUrlMgr : public Singleton<CCUrlMgr>
{
public:
	~CCUrlMgr();
	CCUrlMgr();

	void pushBack( STCMD *pstCmd );
	void pushFront( STCMD *pstCmd );
	void clear();

	void threadStart();
	void threadStop();

private:
	bool downloadFileByHttp(const std::string& downloadURL, STCurlWriteMemory *pstCurlWriteMemroy);
	static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

	void handling( STCMD * pstCmd );
	void onSTCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ( const STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ &stCmd);
	void onSTCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ(const STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ &stCmd);

private:
	static void* threadBooter(void *pMe);
	void threadRun();
	void threadUpdate();
	
private:
	CPMutex mQueuePMutex;
	CPCond mPCond;

	pthread_t mPthreadHandler;

	std::deque<STCMD *> mCmdQueue;

	bool mIsRunning;
	bool mIsThreadExit;
};
