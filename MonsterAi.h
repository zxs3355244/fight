#ifndef _MONSTER_AI_
#define _MONSTER_AI_
#include "cocos2d.h"
#include "Uint.h"
#include "Monster.h"
#include "FoxMonster.h"
#include "BuffMonster.h"
#include "BeeMonster.h"
#include "PigMonster.h"
#include "DragonMonster.h"
#include "Bomb.h"
USING_NS_CC;

enum MonsterAiState
{
	aStand = 1,
	aStanding,
	aGetAim,
	aMoveAim,
	aReadyAttack,
	aAttack,
	aAttacking,
	aAttackEnd,
	aHurt,
	aHurting,
	aHurtEnd,
	aDie,
	aDieing,
	aDieEnd,
};
class MonsterAi 
{
public:
	MonsterAi ();
	~MonsterAi ();
	static MonsterAi* getInstance();
	void monsterAiLogic( Uint* uint,float dt);
	void pigAiLogic(PigMonster* uint, float dt);
	void goblinAiLogic(Monster* uint, float dt);
	void foxAiLogic(FoxMonster* uint, float dt);
	void beeAiLogic(BeeMonster* uint, float dt);
	void buffAiLogic(BuffMonster* uint, float dt);
	void dragonAiLogic(DragonMonster* uint, float dt);
	void bombAiLogic(Bomb* uint, float dt);
	bool canAttack(Uint* uint);
	void destory();
private:

};


#endif