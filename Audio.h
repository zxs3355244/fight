
#ifndef _AUDIO_H_
#define _AUDIO_H_

class Audio
{
public:
	static Audio* getInstance();

	void playGameBGM();
	void playLoginBGM();
	void stopLoginBGM();
	void setAudioState(bool flag);
	void playEffMusic(const char* effectName);

private:
	void init();
	bool mAuidoState;
	static Audio* _instance;
};

#endif