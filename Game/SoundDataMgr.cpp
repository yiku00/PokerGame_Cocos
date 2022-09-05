#include "pch.h"
#include "SoundDataMgr.h"
#include "HeroUtil.h"

#define COMMON_SCENE "Common"
//#define COMMON_SCENE "BattleScene"

template<> SoundDataMgr* Singleton<SoundDataMgr>::msSingleton = 0;

SoundDataMgr::~SoundDataMgr()
{

}

SoundDataMgr::SoundDataMgr()
{

}

void SoundDataMgr::loadData()
{
	pugi::xml_document doc;
	if (false == loadXMLDocReal("xml/gamesound_data.xml", &doc))
		return;

	pugi::xml_node stringNode = doc.child("GAMESOUNDDATA");
	for (pugi::xml_node node = stringNode.first_child(); node != nullptr; node = node.next_sibling())
	{
		// SCENE 별로 따로 관리
		string strScene = node.child_value("SCENE"); 

		SoundDatumPtr pstSoundData = std::make_shared<SoundDatum>();
		pstSoundData->key = node.child_value("KEY");
		pstSoundData->path = node.child_value("VALUE");
		pstSoundData->bgm = atoi(node.child_value("BGM")) == 1;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		if (pstSoundData->path.find(".wav") != string::npos) {
			//pstSoundData->path = nxReplace(pstSoundData->path, ".wav", ".ogg");
		}
		else if (pstSoundData->path.find(".mp3") != string::npos) {
			pstSoundData->path = nxReplace(pstSoundData->path, ".mp3", ".ogg");
		}
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		if (pstSoundData->path.find(".wav") != string::npos) {
			pstSoundData->path = nxReplace(pstSoundData->path, ".wav", ".ogg");
		}
		else if (pstSoundData->path.find(".mp3") != string::npos) {
			pstSoundData->path = nxReplace(pstSoundData->path, ".mp3", ".ogg");
		}
#endif

		auto fit = mSoundTable.find(strScene);
		if (fit == mSoundTable.end()) {
			SoundDataPtr pSoundDataMap(new SoundData());
			fit = mSoundTable.insert(std::make_pair(strScene, pSoundDataMap)).first;
		}

		NXASSERT(fit->second->find(pstSoundData->key) == fit->second->end(),
			"Duplicated Sound key (%s) has found.", pstSoundData->key.c_str());
		fit->second->insert(std::make_pair(pstSoundData->key, pstSoundData));
	}
}

std::string SoundDataMgr::getSoundPath(const std::string& strScene ,const std::string& strKey)
{
	auto fitTable = mSoundTable.find(strScene);
	if (fitTable == mSoundTable.end() )
		return "";

	auto fitData = fitTable->second->find(strKey);
	if (fitData == fitTable->second->end())
		return "";

	return fitData->second->path;
}


void SoundDataMgr::loadSceneSound(const std::string& strScene)
{
	auto fit = mSoundTable.find(strScene);
	if (fit == mSoundTable.end() ||
		find(mSceneTable.begin(), mSceneTable.end(), strScene) != mSceneTable.end())
		return;


	// Load bgms & effects.
	for (auto bit = fit->second->begin(), eit = fit->second->end(); bit != eit; ++bit )
	{
		if (bit->second->bgm) {
			SoundManager::getSingleton().addBGM(bit->first);
		}
		else {
			SoundManager::getSingleton().addEffect(bit->first);
		}
	}

	mSceneTable.push_back(strScene);
	CCLOG("%s sounds loaded.", strScene.c_str());
}

void SoundDataMgr::unloadSceneSound(const std::string& strScene)
{
	auto fit = mSoundTable.find(strScene);
	auto it = find(mSceneTable.begin(), mSceneTable.end(), strScene);
	if (fit == mSoundTable.end() ||
		it == mSceneTable.end())
		return;

	SoundManager::getSingleton().removeAll();
	// Unload banks.

	mSceneTable.erase(it);
	CCLOG("%s sounds unloaded.", strScene.c_str());
}

void SoundDataMgr::loadSounds(const std::string& strScene, const list<string>& sounds)
{
	auto tableIt = mSoundTable.find(strScene);
	if (tableIt == mSoundTable.end())
		return;


	// Load bgms & effects.
	for_each(sounds.begin(), sounds.end(), [&tableIt, &strScene](const string& key) {
		auto it = tableIt->second->find(key);
		if (it != tableIt->second->end()) {
			if (it->second->bgm) {
				SoundManager::getSingleton().addBGM(it->first);
			}
			else {
				SoundManager::getSingleton().addEffect(it->first);
			}
		}
		else {
			NXASSERT(false, "Sound (%s), of %s is not found.", key.c_str(), strScene.c_str());
		}

	});

	if (find(mSceneTable.begin(), mSceneTable.end(), strScene) == mSceneTable.end()) {
		mSceneTable.push_back(strScene);
		CCLOG("%s dynamic sounds loading...", strScene.c_str());
	}
}

void SoundDataMgr::unloadSounds(const std::string& strScene)
{
	auto fit = mSoundTable.find(strScene);
	auto it = find(mSceneTable.begin(), mSceneTable.end(), strScene);
	if (fit == mSoundTable.end() ||
		it == mSceneTable.end())
		return;

	// Unload BGMs & effects.
	for (auto bit = fit->second->begin(), eit = fit->second->end(); bit != eit; ++bit )
	{
		if (bit->second->bgm) {
			SoundManager::getSingleton().subBGM(bit->first, true);
		}
		else {
			SoundManager::getSingleton().subEffect(bit->first, true);
		}
	}

	mSceneTable.erase(it);
	CCLOG("%s dynamic sounds unloaded.", strScene.c_str());
}

void SoundDataMgr::reload()
{
	mSoundTable.clear();
	loadData();
}
