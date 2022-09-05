#pragma once

#include "NXFramework.h"

struct SoundDatum
{
	std::string key;
	std::string path;
	bool bgm;
};

// 사운드 관련 타입들
typedef std::shared_ptr<SoundDatum> SoundDatumPtr;
typedef std::map<std::string, SoundDatumPtr> SoundData;
typedef std::shared_ptr<SoundData> SoundDataPtr;
typedef std::map<string, SoundDataPtr> SoundTable;
typedef std::list<string> SoundSceneTable;

class SoundDataMgr : public Singleton<SoundDataMgr>
{
public:
	~SoundDataMgr();
	SoundDataMgr();

	void loadData();
	void reload();

	void loadSceneSound(const std::string& strScene);
	void unloadSceneSound(const std::string& strScene);

	void loadSounds(const std::string& strScene, const std::list<string>& sounds);
	void unloadSounds(const std::string& strScene);

	string getSoundPath(const std::string& strScene ,const std::string& strKey);

private:
	SoundTable mSoundTable;
	SoundSceneTable mSceneTable;
};
