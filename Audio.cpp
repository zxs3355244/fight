
#include "Audio.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
using namespace CocosDenshion;
Audio* Audio::_instance = nullptr;

Audio* Audio::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new Audio();
		_instance->init();
	}
	return _instance;
}

void Audio::init()
{
	SimpleAudioEngine::getInstance()->preloadEffect("sound/forestBGM.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/coverBGM.mp3");

}

void Audio::playGameBGM()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/forestBGM.mp3", true);
}

void Audio::playLoginBGM()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/coverBGM.mp3", true);
}

void Audio::stopLoginBGM()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void Audio::setAudioState(bool flag)
{
	mAuidoState = flag;
}

void Audio::playEffMusic(const char* effectName)
{
#if (CC_TARGET_PLATFORM  ==  CC_PLATFORM_ANDROID)
	if (mAuidoState)
	{
		SimpleAudioEngine::getInstance()->playEffect(effectName, false);
	}
#endif
}


