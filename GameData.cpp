#include "GameData.h"
#include "Audio.h"
static GameData* _instance = NULL;

GameData* GameData::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new GameData();
		_instance->init();
	}
	return _instance;
}

bool GameData::init()
{
	mCurEquip = 0;
	for (int i = 0; i < 5; i++)
	{
		mEquip[i] = 0;
	}
	reloadData();
	return true;
}

int GameData::getCurEquip()
{
	return mCurEquip;
}

void GameData::setCurEquip(int index)
{
	mCurEquip = index;
}

int GameData::getOnEquip(int index)
{
	return mEquip[index - 1];
}

void GameData::setOnEquip(int index,int id)
{
	mEquip[index - 1] = id;
	sprintf(buf, "EQUIP%d", index);
	UserDefault::getInstance()->setIntegerForKey(buf, mEquip[index - 1]);
}

int GameData::getMaxCharater()
{
	return mMaxCharater;
}

void GameData::setMaxCharater(int id)
{
	if (id > mMaxCharater)
	{
		charaterUp = true;
		mMaxCharater = id;
		UserDefault::getInstance()->setIntegerForKey("MAXCHARATER", mMaxCharater);
	}
}

int GameData::getMaxLevel()
{
	return mMaxLevel;
}

void GameData::setMaxLevel(int id)
{
	if (id > mMaxLevel || charaterUp)
	{
		charaterUp = false;
		mMaxLevel = id;
		UserDefault::getInstance()->setIntegerForKey("MAXLEVEL", mMaxLevel);
	}
}

bool GameData::getHaveEquip(int id)
{
	return mHaveEquip[id - 1];
}

void GameData::updateHaveEquip(int id)
{
	sprintf(buf, "HAVEEQUIP%d", id);
	mHaveEquip[id - 1] = true;
	UserDefault::getInstance()->setBoolForKey(buf, true);
}

bool GameData::getAudioState()
{
	return mAudio;
}
void GameData::setAudioState(bool bl)
{
	mAudio = bl;
	Audio::getInstance()->setAudioState(mAudio);
	UserDefault::getInstance()->setBoolForKey("AUDIOSTATE", mAudio);
}

int GameData::getCurDiamond()
{
	return mDiamond;
}

void GameData::updateCurDiamond(int num)
{
	mDiamond += num;
	if (mDiamond < 0)
	{
		mDiamond = 0;
	}
	UserDefault::getInstance()->setIntegerForKey("DIAMOND", mDiamond);
}

int GameData::getDaZhaoNum()
{
	return mDaZhao;
}

void GameData::updateDaZhaoNum(int num)
{
	mDaZhao += num;
	if (mDaZhao < 0)
	{
		mDaZhao = 0;
	}
	UserDefault::getInstance()->setIntegerForKey("DAZHAO", mDaZhao);
}

int GameData::getDunNum()
{
	return mDun;
}

void GameData::updateDunNum(int num)
{
	mDun += num;
	if (mDun < 0)
	{
		mDun = 0;
	}
	UserDefault::getInstance()->setIntegerForKey("DUN", mDun);
}


int GameData::getGiftBuy(int index)
{
	return mGift[index - 1];
}

void GameData::updateGiftBuy(int index)
{
	mGift[index - 1] = true;
	sprintf(buf, "GIFT%d", index);
	UserDefault::getInstance()->setBoolForKey(buf, true);
}

bool GameData::isFirstLogin()
{
	return mIsFirst;
}

void GameData::updateFirstLogin()
{
	mIsFirst = false;
	UserDefault::getInstance()->setBoolForKey("FIRST", mIsFirst);
}

void GameData::reloadData()
{
	mCurEquip = UserDefault::getInstance()->getIntegerForKey("CUREQUIP",1);
	for (int i = 0; i < 5; i++)
	{
		sprintf(buf, "EQUIP%d", i+1);
		mEquip[i] = UserDefault::getInstance()->getIntegerForKey(buf, 0);
	}
	if (mEquip[0] == 0)
	{
		mEquip[0] = UserDefault::getInstance()->getIntegerForKey("EQUIP0", 3);
	}
	
	for (size_t i = 0; i < 13; i++)
	{
		sprintf(buf, "HAVEEQUIP%d", i+1);
		mHaveEquip[i] = UserDefault::getInstance()->getBoolForKey(buf, false);
	}
	mGift[0] = UserDefault::getInstance()->getBoolForKey("GIFT1", false);
	mGift[1] = UserDefault::getInstance()->getBoolForKey("GIFT2", false);
	mGift[2] = UserDefault::getInstance()->getBoolForKey("GIFT3", false);
	mHaveEquip[2] = UserDefault::getInstance()->getBoolForKey("HAVEEQUIP3", true);
	mDiamond =  UserDefault::getInstance()->getIntegerForKey("DIAMOND", 0);
	mDaZhao = UserDefault::getInstance()->getIntegerForKey("DAZHAO", 3);
	mDun = UserDefault::getInstance()->getIntegerForKey("DAZHAO", 3);
	mAudio = UserDefault::getInstance()->getBoolForKey("AUDIOSTATE", true);
	mMaxCharater = UserDefault::getInstance()->getIntegerForKey("MAXCHARATER", 1);
	mMaxLevel = UserDefault::getInstance()->getIntegerForKey("MAXLEVEL", 1);
	charaterUp = false;
	mIsFirst = UserDefault::getInstance()->getBoolForKey("FIRST", true);
	/*mEquip[0] = UserDefault::getInstance()->getIntegerForKey(buf, 8);
	mEquip[1] = UserDefault::getInstance()->getIntegerForKey(buf, 14);
	mEquip[2] = UserDefault::getInstance()->getIntegerForKey(buf, 12);*/
}

int GameData::getCurMapId()
{
	return mCurMapId;
}

void GameData::setCurMapId(int id)
{
	mCurMapId = id;
}