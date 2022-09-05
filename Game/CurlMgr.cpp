#include "pch.h"
#include "CurlMgr.h"
#include "SocialManager.h"
#include "CmdList.h"
#include "CmdQueue.h"


template<> CCUrlMgr* Singleton<CCUrlMgr>::msSingleton = 0;

CCUrlMgr::~CCUrlMgr()
{
	threadStop();
	clear();
}

CCUrlMgr::CCUrlMgr()
{
	mIsRunning = false;
	mIsThreadExit = false;
}


void CCUrlMgr::clear()
{
	CPMutexLocker locker(mQueuePMutex);
	while (false == mCmdQueue.empty())
	{
		STCMD *pstCmd = mCmdQueue.front();
		delete pstCmd;
		pstCmd = NULL;
		mCmdQueue.pop_front();
	}
}


void CCUrlMgr::pushBack( STCMD *pstCmd )
{
	// 락 걸고
	CPMutexLocker locker(mQueuePMutex);

	mCmdQueue.push_back(pstCmd);

	mPCond.signal();
}

void CCUrlMgr::pushFront( STCMD *pstCmd )
{
	// 락 걸고
	CPMutexLocker locker(mQueuePMutex);

	mCmdQueue.push_front(pstCmd);

	mPCond.signal();
}

size_t CCUrlMgr::writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	STCurlWriteMemory *pstCurlWriteMemeory = static_cast<STCurlWriteMemory *>(userp);

	pstCurlWriteMemeory->memory = (char *)realloc(pstCurlWriteMemeory->memory, pstCurlWriteMemeory->size + realsize + 1);
	if(pstCurlWriteMemeory->memory == NULL) 
	{
		return 0;
	}

	memcpy(&(pstCurlWriteMemeory->memory[pstCurlWriteMemeory->size]), contents, realsize);
	pstCurlWriteMemeory->size += realsize;
	pstCurlWriteMemeory->memory[pstCurlWriteMemeory->size] = 0;

	return realsize;
}


bool CCUrlMgr::downloadFileByHttp( const std::string& downloadUrl, STCurlWriteMemory *pstCurlWriteMemroy)
{
	/* init the curl session */
	CUrlAutoHandler CUrlHandler;

	/* will be grown as needed by the realloc above */
	pstCurlWriteMemroy->memory = (char *)malloc(1);  
	pstCurlWriteMemroy->size = 0;    /* no data at this point */

	/* specify URL to get */
	curl_easy_setopt(CUrlHandler.h, CURLOPT_URL, downloadUrl.c_str());

	/* send all data to this function  */
	curl_easy_setopt(CUrlHandler.h, CURLOPT_WRITEFUNCTION, writeMemoryCallback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(CUrlHandler.h, CURLOPT_WRITEDATA, (void *)pstCurlWriteMemroy);

	/* some servers don't like requests that are made without a user-agent
	field, so we provide one */
	curl_easy_setopt(CUrlHandler.h, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	// conenct timeout, 10
	curl_easy_setopt(CUrlHandler.h, CURLOPT_CONNECTTIMEOUT, 10);
	//curl_easy_setopt(CUrlHandler.h, CURLOPT_CONNECTTIMEOUT, 0);

	curl_easy_setopt(CUrlHandler.h, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(CUrlHandler.h, CURLOPT_SSL_VERIFYHOST, 0);

	curl_easy_setopt(CUrlHandler.h, CURLOPT_FOLLOWLOCATION, 1);

	//curl_easy_setopt(CUrlHandler.h, CURLOPT_VERBOSE, 1); 

	/* get it! */
	CURLcode res = curl_easy_perform(CUrlHandler.h);

	/* check for errors */
	if(res != CURLE_OK) 
	{
		CCLOG("curl_easy_perform() failed: %s", curl_easy_strerror(res));
		return false;
	}

	long httpCode = -100;
	if (CURLE_OK == curl_easy_getinfo(CUrlHandler.h, CURLINFO_HTTP_CODE, &httpCode))
	{
		if (200 == httpCode) {

			char *url;
			if (CURLE_OK == curl_easy_getinfo(CUrlHandler.h, CURLINFO_EFFECTIVE_URL, &url) && url) {
				string lastUrl = url;
				if (downloadUrl != lastUrl && lastUrl.find(".jpg") == string::npos)
					return false;
			}

			return true;
		}
	}

	return false;
}


void* CCUrlMgr::threadBooter( void *pMe )
{
	CCUrlMgr *p = static_cast<CCUrlMgr *>(pMe);
	p->threadRun();

	return 0;
}


void CCUrlMgr::threadStart()
{
	if (false == mIsRunning)
	{
		mIsThreadExit = false;
		CPMutexLocker locker(mQueuePMutex);
		pthread_create(&mPthreadHandler, NULL, CCUrlMgr::threadBooter, this);

		mIsRunning = true;
	}
}

void CCUrlMgr::threadStop()
{
	if (true == mIsRunning)
	{
		mIsThreadExit = true;
		mPCond.signal();
		pthread_join(mPthreadHandler, NULL);
	}
}

void CCUrlMgr::threadRun()
{
	for ( ;false == mIsThreadExit; )
	{
		if (0 == mCmdQueue.size())
		{
			CPMutexLocker locker(mQueuePMutex);
			if (0 == mCmdQueue.size())
			{
				mPCond.wait(mQueuePMutex);
			}

			if (true == mIsThreadExit)
				break;
		}

		threadUpdate();
	}

	mIsRunning = false;
}



void CCUrlMgr::threadUpdate()
{
	// 1st check loack
	if (0 == mCmdQueue.size())
		return;

	STCMD *pstCmd = NULL;
	{
		CPMutexLocker locker(mQueuePMutex);

		// 2st check loack
		if (0 == mCmdQueue.size())
			return;

		pstCmd = mCmdQueue.front();
		mCmdQueue.pop_front();	
	}

	handling(pstCmd);

	delete pstCmd;
	pstCmd = NULL;
}

void CCUrlMgr::handling( STCMD * pstCmd )
{
	if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ>(pstCmd))
	{
		onSTCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ(*pstIt);
		return;
	}
	else if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ>(pstCmd))
	{
		onSTCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ(*pstIt);
		return;
	}
}

void CCUrlMgr::onSTCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ( const STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_REQ &stCmd )
{
	if (stCmd.downloadUrl.empty())
		return;

	// 메모리 해제, 반드시 할것
	STCurlWriteMemory stCurlWriteMemory;
	if (false == downloadFileByHttp(stCmd.downloadUrl, &stCurlWriteMemory))
	{
		return;
	}

	string path = SocialManager::getProfileImagePath(stCmd.downloadUrl);

	if (!CCFileUtils::sharedFileUtils()->isFileExist(path)) {
		std::ofstream ofs;
		ofs.open(path, std::ios_base::binary | std::ios_base::out);
		if (true == ofs.is_open())
		{
			ofs.write(stCurlWriteMemory.memory, stCurlWriteMemory.size);
			ofs.flush();
			ofs.close();
		}

		// 알림
		STCMD_CURL_DOWNLOAD_ILOVEGAME_PROFILE_ACK stcmdAck;
		stcmdAck.userId = stCmd.userId;
		stcmdAck.imagePath = path;

		CCmdQueue::getSingleton().pushQueue(stcmdAck);
	}
}

void CCUrlMgr::onSTCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ(const STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ &stCmd)
{
	if (stCmd.downloadUrl.empty())
		return;

	// 메모리 해제, 반드시 할것
	STCurlWriteMemory stCurlWriteMemory;
	if (false == downloadFileByHttp(stCmd.downloadUrl, &stCurlWriteMemory))
	{
		return;
	}

	string _folder = "";
	if (stCmd.param == DOWNLOAD_FILE_TYPE::MY_PHOTO || stCmd.param == DOWNLOAD_FILE_TYPE::FRIEND_PHOTO)
	{
		_folder = STATIC_PHOTO_FOLDER;
	}
	else
	{
		_folder = TEMP_PHOTO_FOLDER;
	}
	string path = SocialManager::getProfileImagePath(stCmd.downloadUrl, _folder);

	if (!CCFileUtils::sharedFileUtils()->isFileExist(path)) {
		std::ofstream ofs;
		ofs.open(path, std::ios_base::binary | std::ios_base::out);
		if (true == ofs.is_open())
		{
			ofs.write(stCurlWriteMemory.memory, stCurlWriteMemory.size);
			ofs.flush();
			ofs.close();
		}

		// 알림
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK stcmdAck;
		stcmdAck.userId = stCmd.userId;
		stcmdAck.imagePath = path;
		stcmdAck.param = stCmd.param;
		stcmdAck.dParam = stCmd.dParam;
		log("InitFriendPhoto _ret imagePath = %s", path.c_str());
		CCmdQueue::getSingleton().pushQueue(stcmdAck);
	}
}
