#ifndef _GAMEDATA_H
#define _GAMEDATA_H
#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>
using std::vector;
using std::string;
using std::map;
USING_NS_CC;

class GameData{
public:
	static GameData* getInstance();
	bool init();
	void reloadData();
	int getCurEquip();
	void setCurEquip(int index);
	int getOnEquip(int index);
	void setOnEquip(int index, int id);
	int getCurMapId();
	void setCurMapId(int id);
	int getMaxCharater();
	void setMaxCharater(int id);
	int getMaxLevel();
	void setMaxLevel(int id);
	bool getHaveEquip(int id);
	void updateHaveEquip(int id);

	bool getAudioState();
	void setAudioState(bool);

	int getCurDiamond();
	void updateCurDiamond(int num);

	int getDaZhaoNum();
	void updateDaZhaoNum(int num);

	int getDunNum();
	void updateDunNum(int num);
	int getGiftBuy(int index);
	void updateGiftBuy(int index);
	bool isFirstLogin();
	void updateFirstLogin();
private:
	int mCurEquip;
	int mEquip[5];
	char buf[50];
	int mCurMapId;
	int mMaxCharater;
	int mMaxLevel;
	int mDiamond;
	int mDun;
	int mDaZhao;
	bool mHaveEquip[13];
	bool mAudio;
	bool charaterUp;
	bool mGift[3];
	bool mIsFirst;
};
#endif