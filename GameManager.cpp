#include "GameManager.h"
#include "CvsFile.h"
#include "MonsterManager.h"
#include "GameLayer.h"
#include "Hero.h"
#include "Map.h"
#include "GameData.h"
#include "MonsterAi.h"
#include "GiftLayer.h"
static GameManager* _instance = NULL;
GameManager::GameManager()
{
	monsterVec.resize(0);
	monsterSaveVec[0].resize(0);
	monsterSaveVec[1].resize(0);
	monsterSaveVec[2].resize(0);
	monsterSaveBossVec.resize(0);

	mLeftX = 0;
	mChange = 0;
	monsterTime = 0;
	isChange = false;
	isShowBoss = false;
	haveDragon = false;
	mState = GameState::ENULL;
}

GameManager::~GameManager()
{
	for (size_t j = 0; j < 3; j++)
	{
		for (int i = 0; i < monsterSaveVec[j].size(); i++)
		{
			monsterSaveVec[j][i]->release();

		}
		monsterSaveVec[j].clear();
	}
	if (monsterSaveBossVec.size() > 0)
	{
		monsterSaveBossVec[0]->release();
	}
		monsterSaveBossVec.clear();
	
	for (int i = 0; i < monsterVec.size(); i++)
	{
		monsterVec[i]->release();

	}
	monsterVec.clear();
}

GameManager* GameManager::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new GameManager();
	}
	return _instance;
}

void GameManager::destory()
{
	delete	_instance;
	MonsterAi::getInstance()->destory();
	MonsterManager::getInstance()->destory();
	_instance = NULL;
}

void GameManager::createMonster(int id)
{
	curMapId = id;
	curWave = 1;
	isShowMon = false;
	outBossTime = 0;
	monsterTime = 0;
	haveDragon = false;
	waveMonster[0] = 0;
	waveMonster[1] = 0;
	waveMonster[2] = 0;
	dieOne = false;
	isShow = false;
	mData = CvsFile::getInstance()->getMapData(id);
	maxWave = mData->wave;
	for (int i = 0; i < mData->mMonster.size(); i++)
	{
		for (int t = 0; t < mData->mMonster[i]->monsterCount; t++)
		{
			Uint* uint = MonsterManager::getInstance()->createMonster(mData->mMonster[i]->monsterName, mData->mMonster[i]->monsterId, false, mData->mMonster[i]->roomId);
			if (mData->mMonster[i]->roomId == 1)
			{
				monsterSaveVec[0].push_back(uint);
				waveMonster[0]++;
			}
			else if(mData->mMonster[i]->roomId == 2)
			{
				monsterSaveVec[1].push_back(uint);
				waveMonster[1]++;
			}
			else if (mData->mMonster[i]->roomId == 3)
			{
				monsterSaveVec[2].push_back(uint);
				waveMonster[2]++;
			}
			int ids = 0;
			if (id <= 6)
			{
				ids = id-1;
			}
			else if (id <= 22)
			{
				ids = (id-6)%9-1;
				if (ids > 7)
				{
					ids = 7;
				}
			}
			else
			{
				ids = (id - 22) % 10-1;
				if (ids > 7)
				{
					ids = 7;
				}
			}
			uint->setProper(CvsFile::getInstance()->getMonsterData(ids, mData->mMonster[i]->monsterName, false));
		}
	}
	if (mData->mBoss)
	{
		Uint* uint = MonsterManager::getInstance()->createMonster(mData->mBoss->bossName, mData->mBoss->bossId, true, mData->mBoss->roomId);
		monsterSaveBossVec.push_back(uint);
		uint->setProper(CvsFile::getInstance()->getMonsterData(id, mData->mBoss->bossName, true));
	}
}

void GameManager::outMonster(float dt)
{
	if (curWave > maxWave)
	{
		return;
	}
	Uint* mons = NULL;
	if (curWave == 1)
	{
		Vec2 pos = Hero::getInstance()->getPosition();
		monsterTime += dt;
		if (monsterSaveVec[0].size() == 0)
		{
			mState = GameState::EWaitNext;
			curWave = 2;
		}
	
		if (monsterTime > 1 && (monsterSaveVec[0].size()> 0 || monsterSaveBossVec.size() > 0))
		{
			monsterTime = 0;
			if (monsterSaveVec[0].size() >0 && pos.x > 400 && pos.x < 800 && monsterSaveVec[0].size() > (int)waveMonster[0] / 2)
			{
				int t = random(0, (int)monsterSaveVec[0].size()-1);
				mons = monsterSaveVec[0][t];
				monsterSaveVec[0].erase(monsterSaveVec[curWave - 1].begin() + t);
			
				monsterVec.push_back(mons);
				GameLayer::getInstance()->ObjVec.push_back(mons);
				GameLayer::getInstance()->mGameLayer->addChild(mons);
				mons->setPosition(Vec2(random(mLeftX + 50, mLeftX + 800), random(50, 260)));
				mons->stateHandler(MonsterState::uStand, true);
			}
			if (monsterSaveVec[0].size() >0 && pos.x > 1200 && pos.x < 1600 && monsterSaveVec[0].size() <= (int)waveMonster[0] / 2)
			{
				int t = random(0, (int)monsterSaveVec[0].size() - 1);
				mons = monsterSaveVec[0][t];
				monsterSaveVec[0].erase(monsterSaveVec[curWave - 1].begin() + t);

				monsterVec.push_back(mons);
				GameLayer::getInstance()->ObjVec.push_back(mons);
				GameLayer::getInstance()->mGameLayer->addChild(mons);
				mons->setPosition(Vec2(random(mLeftX + 1200, mLeftX + 1600), random(50, 260)));
				mons->stateHandler(MonsterState::uStand, true);
			}
			
		}
	}
	else if (curWave == 2)
	{
		Vec2 pos = Hero::getInstance()->getPosition();
		monsterTime += dt;
		if (monsterSaveVec[1].size() == 0 &&  maxWave >= 3)
		{
			mState = GameState::EWaitNext;
			curWave = 3;
		}
		if (monsterTime > 1 && (monsterSaveVec[1].size()> 0 || monsterSaveBossVec.size() > 0))
		{
			monsterTime = 0;
			if (monsterSaveVec[1].size() >0 && pos.x > 2000 && pos.x < 2400 && monsterSaveVec[1].size() > (int)waveMonster[1] / 2)
			{
				int t = random(0, (int)monsterSaveVec[1].size() - 1);
				mons = monsterSaveVec[1][t];
				monsterSaveVec[1].erase(monsterSaveVec[curWave - 1].begin() + t);

				monsterVec.push_back(mons);
				GameLayer::getInstance()->ObjVec.push_back(mons);
				GameLayer::getInstance()->mGameLayer->addChild(mons);
				mons->setPosition(Vec2(random(mLeftX + 50, mLeftX + 800), random(50, 260)));
				mons->stateHandler(MonsterState::uStand, true);
			}
			if (monsterSaveVec[1].size() >0 && pos.x > 2800 && pos.x < 3200 && monsterSaveVec[1].size() <= (int)waveMonster[1] / 2)
			{
				int t = random(0, (int)monsterSaveVec[1].size() - 1);
				mons = monsterSaveVec[1][t];
				monsterSaveVec[1].erase(monsterSaveVec[curWave - 1].begin() + t);

				monsterVec.push_back(mons);
				GameLayer::getInstance()->ObjVec.push_back(mons);
				GameLayer::getInstance()->mGameLayer->addChild(mons);
				mons->setPosition(Vec2(random(mLeftX + 1200, mLeftX + 1600), random(50, 260)));
				mons->stateHandler(MonsterState::uStand, true);
				if (canOutBoss() && !isShowBoss)
				{
					isShowBoss = true;
					GameLayer::getInstance()->showOutBoss();
				}
			}

		}
	}
	else if (curWave == 3 &&  maxWave >= 3)
	{
		Vec2 pos = Hero::getInstance()->getPosition();
		monsterTime += dt;
		if (monsterTime > 1 && (monsterSaveVec[2].size()> 0 || monsterSaveBossVec.size() > 0))
		{
			monsterTime = 0;
			if (monsterSaveVec[2].size() >0 && pos.x > 3600 && pos.x < 4000 && monsterSaveVec[2].size() > (int)waveMonster[2] / 2)
			{
				int t = random(0, (int)monsterSaveVec[2].size() - 1);
				mons = monsterSaveVec[2][t];
				monsterSaveVec[2].erase(monsterSaveVec[curWave - 1].begin() + t);

				monsterVec.push_back(mons);
				GameLayer::getInstance()->ObjVec.push_back(mons);
				GameLayer::getInstance()->mGameLayer->addChild(mons);
				mons->setPosition(Vec2(random(mLeftX + 50, mLeftX + 800), random(50, 260)));
				mons->stateHandler(MonsterState::uStand, true);
			}
			if (monsterSaveVec[2].size() >0 && pos.x > 4400 && pos.x < 4800 && monsterSaveVec[2].size() <= (int)waveMonster[2] / 2)
			{
				int t = random(0, (int)monsterSaveVec[2].size() - 1);
				mons = monsterSaveVec[2][t];
				monsterSaveVec[2].erase(monsterSaveVec[curWave - 1].begin() + t);

				monsterVec.push_back(mons);
				GameLayer::getInstance()->ObjVec.push_back(mons);
				GameLayer::getInstance()->mGameLayer->addChild(mons);
				mons->setPosition(Vec2(random(mLeftX + 1200, mLeftX + 1600), random(50, 260)));
				mons->stateHandler(MonsterState::uStand, true);
				if (canOutBoss() && !isShowBoss)
				{
					isShowBoss = true;
					GameLayer::getInstance()->showOutBoss();
				}
			}

		}
	}
	if (monsterTime > 1)
		monsterTime = 0;

}

bool GameManager::canOutBoss()
{
	if (curWave == mData->wave && monsterSaveBossVec.size() > 0 && monsterSaveVec[curWave-1].size() == 0)
	{
		return true;
	}
	return false;
}

void GameManager::OutBoss()
{
	if (monsterSaveBossVec.size() > 0 )
	{
		Uint* mons;
		mons = monsterSaveBossVec[0];
		monsterSaveBossVec.clear();

		monsterVec.push_back(mons);
		GameLayer::getInstance()->ObjVec.push_back(mons);
		GameLayer::getInstance()->mGameLayer->addChild(mons);
		haveDragon = false;
		if (mons->mName == "dragon")
		{
			haveDragon = true;
			mons->setPosition(Vec2(mLeftX + 1400, 160));
		}
		else
		{
			mons->setPosition(Vec2(random(mLeftX + 800, mLeftX + 1600), random(50, 260)));
		}
		
		mons->stateHandler(MonsterState::uStand, true);
	}
	
}

bool GameManager::showMonster()
{
	if (curWave <= mData->wave)
	{
		Uint* monster = getMonsterByWave();
		if (monster)
		{
			monsterVec.push_back(monster);
			GameLayer::getInstance()->ObjVec.push_back(monster);
			GameLayer::getInstance()->mGameLayer->addChild(monster);
			monster->setPosition(Vec2(random(mLeftX + 50, mLeftX+1500), random(50, 260)));
			monster->stateHandler(MonsterState::uStand,true);
			return true;
		}
	}
	return false;
}

void GameManager::transformPosition(Vec2 dir, float dt)
{
	Size size = Director::getInstance()->getVisibleSize();
	float speed = Hero::getInstance()->mSpeed;
	Vec2 offsetpos = Vec2(cos(dir.getAngle()) * dt*speed, sin(dir.getAngle())* dt*speed);
	Vec2 pos = GameLayer::getInstance()->mGameLayer->getPosition();
	Vec2 heroPos = Hero::getInstance()->getPosition();
	heroPos = Hero::getInstance()->getParent()->convertToWorldSpace(heroPos);
	Layer* mGameLayer = GameLayer::getInstance()->mGameLayer;
	if (heroPos.x < 430 && heroPos.x > 370)
	{
		mGameLayer->setPositionX(pos.x - offsetpos.x);
	}
	if (heroPos.y > 180 && heroPos.y < 220)
	{
		mGameLayer->setPositionY(pos.y - offsetpos.y);
	}

	pos = mGameLayer->getPosition();
	if (pos.x > -mLeftX)
	{
		pos.x = -mLeftX;
	}
	if (haveDragon)
	{
		if (pos.x + mGameLayer->getContentSize().width < size.width -300)
		{
			pos.x = size.width - mGameLayer->getContentSize().width -300;
		}
	}
	else if (pos.x + mGameLayer->getContentSize().width < size.width)
	{
		pos.x = size.width - mGameLayer->getContentSize().width;
	}
	if (pos.y > 0)
	{
		pos.y = 0;
	}
	if (pos.y + mGameLayer->getContentSize().height < size.height)
	{
		pos.y = size.height - mGameLayer->getContentSize().height;
	}
	mGameLayer->setPosition(pos);

	Hero::getInstance()->setPosition(Hero::getInstance()->getPosition() + offsetpos);
	heroPos = Hero::getInstance()->getPosition();
	if (heroPos.x < mLeftX+10)
	{
		heroPos.x = mLeftX+10;
	}
	if (heroPos.x  > mGameLayer->getContentSize().width - 10)
	{
		heroPos.x = mGameLayer->getContentSize().width - 10;
	}
	if (heroPos.y < 10)
	{
		heroPos.y = 10;
	}
	if (heroPos.y > MOVEHEIGHT)
	{
		heroPos.y = MOVEHEIGHT;
	}
	Hero::getInstance()->setPosition(heroPos);
}

Uint* GameManager::getMonsterByWave()
{
	Uint* mons = NULL;
	for (int i = 0; i < monsterSaveVec[curWave-1].size(); i++)
	{
		if (curWave == monsterSaveVec[curWave - 1][i]->mWave)
		{
			mons = monsterSaveVec[curWave - 1][i];
			monsterSaveVec[curWave - 1].erase(monsterSaveVec[curWave - 1].begin() + i);
			return mons;
		}
	}
	return NULL;
}

void GameManager::gameLogic(float dt)
{
	outMonster(dt);
	switch (mState)
	{
	case GameState::ENULL:
	{
	/*	Vec2 pos = Hero::getInstance()->getPosition();
		if (pos.x > mLeftX + 400)
		{
			
			mState = GameState::EShowMon;
		}*/
	}
		break;
	case GameState::EShowMon:
		{
		/*	monsterTime += dt;
			if (monsterTime > 1)
			{
				monsterTime = 0;
				if (!showMonster())
				{
					mState = GameState::EWaitNext;
				}
			}
			*/
		}
		break;
	case GameState::EWaitNext:
	{
		if (monsterVec.size() == 0)
		{
			Vec2 pos = GameLayer::getInstance()->mGameLayer->getPosition();
			Vec2 heroPos = Hero::getInstance()->getPosition();
			heroPos = Hero::getInstance()->getParent()->convertToWorldSpace(heroPos);
		
			if (mChange == 0 && heroPos.x > 450)
			{
				GameLayer::getInstance()->showTishiIcon(2);
			}
			if (pos.x <= -mLeftX - 800 && (heroPos.x < 430 && heroPos.x > 370))
			{
				if (mChange == 0)
				{
					mChange = 1;
					isChange = true;
				}
				else if (mChange == 1)
				{
					isChange = true;
					mChange = 2;
				}
				
			}
			if (mChange == 1 && isChange)
			{
				mLeftX += 800;
				isChange = false;
				Size size = GameLayer::getInstance()->mGameLayer->getContentSize();
				GameLayer::getInstance()->mGameLayer->setContentSize(Size(size.width + 800, size.height));
				MapLayer::getInstance()->ChangeLeftMap();
				GameLayer::getInstance()->showTishiIcon(1);
			}
			else if (mChange == 2)
			{
				mLeftX += 800;
				isChange = false;
				MapLayer::getInstance()->ChangeLeftMap();
				Size size = GameLayer::getInstance()->mGameLayer->getContentSize();
				GameLayer::getInstance()->mGameLayer->setContentSize(Size(size.width + 800, size.height));
				mChange = 0;
				GameLayer::getInstance()->showTishiIcon(1);
				if (curWave > mData->wave)
				{
					mState = GameState::EAllEnd;
					return;
				}
				mState = GameState::ENULL;
			}
			
		}
	}
		break;
	case GameState::EAllEnd:
	{

		//gameOver

	}
		break;
	default:
		break;
	}
	for (int i = 0; i < monsterVec.size(); i++)
	{
		if (monsterVec[i]->isDie)
		{
			monsterVec.erase(monsterVec.begin() + i);
			i++;
			dieOne = true;
			continue;
		}
		MonsterAi::getInstance()->monsterAiLogic(monsterVec[i],dt);
	}
	if (GameData::getInstance()->getCurMapId() == 2 && dieOne && isShow == false)
	{
		isShow = true;
		GameLayer::getInstance()->pause();
		GameLayer::getInstance()->unscheduleUpdate();
		if (GameData::getInstance()->getGiftBuy(3) == false)
		{
			GiftLayer::getInstance()->show(GiftLayer::GiftType::eFinal, [this](int state){
				GameLayer::getInstance()->resume();
				GameLayer::getInstance()->scheduleUpdate();
				if (state == 0)
				{
					GameData::getInstance()->updateGiftBuy(3);
					GameLayer::getInstance()->updateText();
				}
			});
		}
		else
		{
			GiftLayer::getInstance()->show(GiftLayer::GiftType::eDiamond, [this](int state){
				GameLayer::getInstance()->resume();
				GameLayer::getInstance()->scheduleUpdate();
				if (state == 0)
				{
					GameLayer::getInstance()->updateText();
				}
			});
		}
	}
	if (monsterVec.size() == 0 && monsterSaveVec[0].size() == 0 &&
		monsterSaveVec[1].size() == 0 && monsterSaveVec[2].size() == 0 &&
		monsterSaveBossVec.size() == 0)
	{
		GameLayer::getInstance()->gameOver(true);
		return;
	}
	else if (isShowBoss && monsterSaveBossVec.size() == 0 && monsterVec.size() <= 3)
	{
		outBossTime += dt;
		if (outBossTime > 20)
		{
			outBossTime = 0;
			Vec2 heropos =  Hero::getInstance()->getPosition();
			for (size_t i = 0; i < 5; i++)
			{
				string monsname[4] = { "goblin", "pig", "fox", "bee" };
				string name = "";
				int id = GameData::getInstance()->getCurMapId();
				int ids = 0;
				if (id <= 6)
				{
					ids = id - 1;
				}
				else if (id <= 22)
				{
					ids = (id - 6) % 9 - 1;
					if (ids > 7)
					{
						ids = 7;
					}
				}
				else
				{
					ids = (id - 22) % 10 - 1;
					if (ids > 7)
					{
						ids = 7;
					}
				}
				if (ids <= 2)
				{
					name = "goblin";
				}
				else if (ids > 2 && ids <= 4)
				{
					name = monsname[random(0, 1)];
				}
				else
				{
					name = monsname[random(0, 3)];
				}
				Uint* monster;
				if (name == "goblin")
				{
					monster = Monster::create(name, 2, false, 1, false);
				}
				else if (name == "pig")
				{
					monster = PigMonster::create(name, 2, false, 1, false);
				}
				else if (name == "fox")
				{
					monster = FoxMonster::create(name, 2, false, 1, false);
				}
				else if (name == "bee")
				{
					monster = BeeMonster::create(name, 2, false, 1, false);
				}
				
				GameManager::getInstance()->monsterVec.push_back(monster);
				GameLayer::getInstance()->ObjVec.push_back(monster);
				GameLayer::getInstance()->mGameLayer->addChild(monster);
				monster->setPosition(random(heropos.x - 300, heropos.x - 100), random(heropos.y - 50, heropos.y + 50));
				monster->setAction("stand", true);

				
				monster->setProper(CvsFile::getInstance()->getMonsterData(ids, name, false));
			}
			
		}
	}
}

void GameManager::addNextMap()
{
	GameLayer::getInstance()->mGameLayer->getPosition();
}