#include "MonsterManager.h"
#include "Monster.h"
#include "FoxMonster.h"
#include "BuffMonster.h"
#include "BeeMonster.h"
#include "PigMonster.h"
#include "DragonMonster.h"
#include "Bomb.h"
static MonsterManager* _instance = NULL;

MonsterManager* MonsterManager::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new MonsterManager();
	}
	return _instance;
}

void MonsterManager::destory()
{
	delete _instance;
	_instance = NULL;
}

Uint* MonsterManager::createMonster(string name, int id, bool isBoss,int wave,bool showEff)
{
	Uint* uint = NULL;
	if (name == "goblin")
	{
		uint = Monster::create(name, id, isBoss, wave,showEff);
	}
	else if (name == "bee")
	{
		uint = BeeMonster::create(name, id, isBoss, wave, showEff);
	}
	else if (name == "pig")
	{
		uint = PigMonster::create(name, id, isBoss, wave, showEff);
	}
	else if (name == "buff")
	{
		uint = BuffMonster::create(name, id, isBoss, wave, showEff);
	}
	else if (name == "fox")
	{
		uint = FoxMonster::create(name, id, isBoss, wave, showEff);
	}
	else if (name == "dragon")
	{
		uint = DragonMonster::create(name, id, isBoss, wave, showEff);
	}
	else if (name == "bomb")
	{
		uint = Bomb::create(name, id, isBoss, wave, showEff);
	}
	return uint;
}

MonsterManager::MonsterManager()
{

}

MonsterManager::~MonsterManager()
{

	_instance = NULL;
	
}