#include "MonsterAi.h"
#include "Hero.h"
#include "GameLayer.h"
static MonsterAi* _instance = NULL;

MonsterAi::MonsterAi()
{

}

MonsterAi::~MonsterAi()
{
	
	_instance = NULL;
}

MonsterAi* MonsterAi::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new MonsterAi();

	}
	return _instance;
}

void MonsterAi::destory()
{
	delete _instance;
	_instance = NULL;
}
void MonsterAi::monsterAiLogic(Uint* uint, float dt)
{
	if (uint->mName == "goblin")
	{
		goblinAiLogic(dynamic_cast<Monster*>(uint), dt);
	}
	else if (uint->mName == "bee")
	{
		beeAiLogic(dynamic_cast<BeeMonster*>(uint), dt);
	}
	else if (uint->mName == "fox")
	{
		foxAiLogic(dynamic_cast<FoxMonster*>(uint), dt);
	}
	else if (uint->mName == "buff")
	{
		buffAiLogic(dynamic_cast<BuffMonster*>(uint), dt);
	}
	else if (uint->mName == "pig")
	{
		pigAiLogic(dynamic_cast<PigMonster*>(uint), dt);
	}
	else if (uint->mName == "dragon")
	{
		dragonAiLogic(dynamic_cast<DragonMonster*>(uint), dt);
	}
	else if (uint->mName == "bomb")
	{
		bombAiLogic(dynamic_cast<Bomb*>(uint), dt);
	}
}

void MonsterAi::bombAiLogic(Bomb* uint, float dt)
{
	if (uint->mCurLife < 0)
	{
		return;
	}
	switch (uint->mAiState)
	{
	case MonsterAiState::aStand:
	{
		int rand = random(1, 7);
		if (GameLayer::getInstance()->isShowDaZhao)
		{
			rand = 1;
		}
		if (rand == 1)
		{
			uint->mAiState = aStanding;
			uint->stateHandler(MonsterState::uStand, true);
			uint->mMoveTime = 0;
		}
		else if (rand == 2)
		{
			//扔球
			uint->mAiState = aAttack;
			uint->stateHandler(MonsterState::uAttack2, false);
			uint->mMoveTime = 0;
		}
		else if (rand == 3)
		{
			//扔炸弹
			uint->mAiState = aAttack;
			uint->stateHandler(MonsterState::uAttack1, false);
			uint->mMoveTime = 0;
		}
		else if (rand == 4)
		{
			uint->mAiState = aAttack;
			uint->stateHandler(MonsterState::uAttackPre, false);
			uint->mMoveTime = 0;
		}
		else
		{
			//移动
			uint->mAiState = aGetAim;
			uint->stateHandler(MonsterState::uMove, false);
			uint->mMoveTime = 0;

		}

	}
		break;

	case MonsterAiState::aStanding:
	{
		uint->mMoveTime += dt;
		if (uint->mMoveTime>0.5)
		{
			uint->mMoveTime = 0;
			uint->mAiState = aStand;
		}
	}
		break;
	case MonsterAiState::aAttack:
	{
		if (uint->mCurState == MonsterState::uAttackPre)//喷火
		{
			uint->mMoveTime = 0;
			
		}
		uint->mAiState = aAttacking;
		
		
	}
		break;
	case MonsterAiState::aAttacking:
	{
		if (uint->mCurState == MonsterState::uAttack)//喷火
		{
			uint->mMoveTime += dt;
			if (uint->mMoveTime > 1)
			{
				uint->mAiState = aStanding;
				uint->stateHandler(MonsterState::uStand, true);
				uint->mMoveTime = 0;
			}
		}
	}
		break;
	case MonsterAiState::aAttackEnd:
	{
		uint->mAiState = aStanding;
		uint->stateHandler(MonsterState::uStand, true);
		uint->mMoveTime = 0;
	}
		break;
	case MonsterAiState::aDie:
	{
								 uint->stateHandler(MonsterState::uDie, false);
								 uint->mAiState = aDieing;
	}
		break;
	case MonsterAiState::aDieing:
	{

	}
		break;
	case MonsterAiState::aDieEnd:
	{

	}
		break;
	case MonsterAiState::aGetAim:
	{

		Vec2 uintpos = uint->getPosition();
		Vec2 temppos;
		Vec2 heropos = Hero::getInstance()->getPosition();
		temppos = Vec2(random(heropos.x - 300, heropos.x + 300), random(heropos.y - 60, heropos.y + 60));


		uint->mMoveTime = 0;
		uint->mAiState = aMoveAim;
		uint->targetPos = temppos;

	}
		break;
	case MonsterAiState::aHurt:
	{

	}
		break;
	case MonsterAiState::aHurting:
	{

	}
		break;
	case MonsterAiState::aHurtEnd:
	{
									 uint->mMoveTime = 0;
									 uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aMoveAim:
	{
	uint->mMoveTime += dt;
	if (uint->mMoveTime > 3)
	{
		uint->mMoveTime = 0;
		uint->mAiState = aStand;
		return;
	}
	if ((uint->targetPos - uint->getPosition()).length() < 5)
	{
		uint->mAiState = aStand;
		return;
	}
	uint->move((uint->targetPos - uint->getPosition()).getNormalized(), dt);
}
		break;
	case MonsterAiState::aReadyAttack:
	{
										 uint->mMoveTime += dt;
										 if (uint->mMoveTime > 0.5)
										 {
											 uint->mMoveTime = 0;
											 uint->mAiState = aAttacking;
											 return;
										 }
	}
		break;
	default:
		break;
	}
}

void MonsterAi::pigAiLogic(PigMonster* uint, float dt)
{
	if (uint->mCurLife == uint->mLife / 2 && uint->isChange)
	{
		return;
	}
	switch (uint->mAiState)
	{
	case MonsterAiState::aStand:
	{
		int rand = random(1, 2);
		if (GameLayer::getInstance()->isShowDaZhao)
		{
			rand = 1;
		}
		if (rand == 1)
		{
			uint->mAiState = aStanding;
			uint->stateHandler(MonsterState::uStand, true);
			uint->mMoveTime = 0;
		}
		else
		{
			Hero* hero = Hero::getInstance();
			Vec2 heropos = hero->getPosition();
			Vec2 uintpos = uint->getPosition();

			if (abs(heropos.y - uintpos.y) < 20)
			{
				//
				uint->mAiState = aAttack;
			}
			else
			{
				uint->mAiState = aGetAim;
			}
			
		}

	}
		break;

	case MonsterAiState::aStanding:
	{
		uint->mMoveTime += dt;
		if (uint->mMoveTime>0.5)
		{
			uint->mMoveTime = 0;
			uint->mAiState = aStand;
		}
	}
		break;
	case MonsterAiState::aAttack:
	{
		Vec2 uintpos = uint->getPosition();
		Vec2 heropos = Hero::getInstance()->getPosition();
		Vec2 temppos;
		if (heropos.x < uintpos.x)
		{
			temppos = Vec2(heropos.x - random(200,400), uintpos.y);
		}
		else
		{
			temppos = Vec2(heropos.x + random(200, 400), uintpos.y);
		}

		uint->mMoveTime = 0;
		uint->targetPos = temppos;
		uint->stateHandler(MonsterState::uAttack2, 0);
		uint->mAiState = aReadyAttack;
	}
		break;
	case MonsterAiState::aAttacking:
	{
		if ((uint->targetPos - uint->getPosition()).length() < 5)
		{
			uint->mAiState = aStand;
			return;
		}
		uint->moveAttack((uint->targetPos - uint->getPosition()).getNormalized(), dt);
	}
		break;
	case MonsterAiState::aAttackEnd:
	{
		   uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aDie:
	{
		uint->stateHandler(MonsterState::uDie, false);
		uint->mAiState = aDieing;
	}
		break;
	case MonsterAiState::aDieing:
	{

	}
		break;
	case MonsterAiState::aDieEnd:
	{

	}
		break;
	case MonsterAiState::aGetAim:
	{
		
		Vec2 uintpos = uint->getPosition();
		Vec2 temppos;
		Vec2 heropos = Hero::getInstance()->getPosition();
		temppos = Vec2(random(uintpos.x - 10,uintpos.x + 10), random(heropos.y - 20, heropos.y + 20));

		
		uint->mMoveTime = 0;
		uint->mAiState = aMoveAim;
		uint->targetPos = temppos;
		
	}
		break;
	case MonsterAiState::aHurt:
	{

	}
		break;
	case MonsterAiState::aHurting:
	{

	}
		break;
	case MonsterAiState::aHurtEnd:
	{
		uint->mMoveTime = 0;
		uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aMoveAim:
	{
		uint->mMoveTime += dt;
		if (uint->mMoveTime > 3)
		{
			uint->mMoveTime = 0;
			uint->mAiState = aStand;
			return;
		}
		if ((uint->targetPos - uint->getPosition()).length() < 5)
		{
			uint->mAiState = aStand;
			return;
		}
		uint->move((uint->targetPos - uint->getPosition()).getNormalized(), dt);
	}
		break;
	case MonsterAiState::aReadyAttack:
	{
			uint->mMoveTime += dt;
			if (uint->mMoveTime > 0.5)
			{
				uint->mMoveTime = 0;
				uint->mAiState = aAttacking;
				return;
			}
	}
		break;
	default:
		break;
	}
}

void MonsterAi::goblinAiLogic(Monster* uint, float dt)
{
	//站着
	//1//寻找目标 移动
	//2//到目标位置
	//3.//1.在攻击范围内 开始攻击
	//2。不在范围内 dao1
	//开始攻击 循环


	//受到伤害，停止播放受伤害，结束
	//1.活着继续之前的，
	//2.死亡。播放死亡动画，删除怪
	if (uint->mCurLife < 0)
	{
		return;
	}
	switch (uint->mAiState)
	{
		case MonsterAiState::aStand:
		{
			int id = uint->mCurId;
			
			int rand = random(1, 2);
			if (GameLayer::getInstance()->isShowDaZhao)
			{
				rand = 1;
			}
			if (rand == 1)
			{
				uint->mAiState = aStanding;
				uint->stateHandler(MonsterState::uStand, true);
				uint->mMoveTime = 0;
			}
			else
			{
				if (id == 1)
				{
					Hero* hero = Hero::getInstance();
					Vec2 heropos = hero->getPosition();
					Vec2 uintpos = uint->getPosition();
					if (abs(heropos.y - uintpos.y) < 20 && (heropos - uintpos).length() > 300 && (heropos - uintpos).length() < 500)
					{
						uint->mAiState = aAttack;
						
					}
					else
					{
						if (canAttack(uint))
						{
							uint->mAiState = aAttack;
						}
						else
						{
							uint->mAiState = aGetAim;

						}
					}
				}
				else
				{
					if (canAttack(uint))
					{
						uint->mAiState = aAttack;
					}
					else
					{
						uint->mAiState = aGetAim;

					}
					
				}
				
			}
		}
			break;
			
		case MonsterAiState::aStanding:
			{
				uint->mMoveTime += dt;
				if (uint->mMoveTime>0.5)
				{
					uint->mMoveTime = 0;
					uint->mAiState = aStand;
				}
			}
			break;
		case MonsterAiState::aAttack:
		{
			Hero* hero = Hero::getInstance();
			Vec2 heropos = hero->getPosition();
			Vec2 uintpos = uint->getPosition();
			if (abs(heropos.y - uintpos.y) < 20 && (heropos - uintpos).length() > 300 && (heropos - uintpos).length() < 500)
			{
				if (uint->mCurId == 1)
				{
					uint->stateHandler(MonsterState::uAttack2, false);
				}
			}
			else
			{
		
				int rand = random(1, 4);
				if (rand == 4)
				{
					uint->stateHandler(MonsterState::uAttack1, false);
				}
				else
				{
					uint->stateHandler(MonsterState::uAttack, false);
				}
			}
			uint->mAiState = aAttacking;
		}
			break;
		case MonsterAiState::aAttacking:
		{

		}
			break;
		case MonsterAiState::aAttackEnd:
		{
			uint->mAiState = aStand;
		}
			break;
		case MonsterAiState::aDie:
		{
			//uint->stateHandler(MonsterState::uDie, false);
			uint->mAiState = aDieing;
		}
			break;
		case MonsterAiState::aDieing:
		{

		}
			break;
		case MonsterAiState::aDieEnd:
		{
			
		}
			break;
		case MonsterAiState::aGetAim:
		{
			Hero* hero = Hero::getInstance();
			Vec2 heropos = hero->getPosition();
			Vec2 uintpos = uint->getPosition();
			Vec2 temppos;
			if (uintpos.x < heropos.x)
			{
				 temppos = Vec2(heropos.x - 50,  random(heropos.y - 20, heropos.y + 20));
				
			}
			else
			{
				 temppos = Vec2(heropos.x + 50, random(heropos.y - 20, heropos.y + 20));
				
			}
			uint->mMoveTime = 0;
			uint->mAiState = aMoveAim;
			uint->targetPos = temppos;
			//uint->move((temppos - uintpos).getNormalized(), true);
		}
			break;
		case MonsterAiState::aHurt:
		{

		}
			break;
		case MonsterAiState::aHurting:
		{

		}
			break;
		case MonsterAiState::aHurtEnd:
		{
			uint->mMoveTime = 0;
			uint->mAiState = aStand;
		}
			break;
		case MonsterAiState::aMoveAim:
		{
			uint->mMoveTime += dt;
			if (uint->mMoveTime > 1)
			{
				uint->mMoveTime = 0;
				uint->mAiState = aStand;
				return;
			}
			if ((uint->targetPos - uint->getPosition()).length() < 5)
			{
				return;
			}
			uint->move((uint->targetPos - uint->getPosition()).getNormalized(), dt);
		}
			break;
		case MonsterAiState::aReadyAttack:
		{

		}
			break;
	default:
		break;
	}
}

void MonsterAi::foxAiLogic(FoxMonster* uint, float dt)
{
	if (uint->mCurLife < 0)
	{
		return;
	}
	switch (uint->mAiState)
	{
	case MonsterAiState::aStand:
	{
		int id = uint->mCurId;

		int rand = random(1, 2);
		if (GameLayer::getInstance()->isShowDaZhao)
		{
			rand = 1;
		}
		if (rand == 1)
		{
			uint->mAiState = aStanding;
			uint->stateHandler(MonsterState::uStand, true);
			uint->mMoveTime = 0;
		}
		else
		{
			if (id == 3)
			{
				Hero* hero = Hero::getInstance();
				Vec2 heropos = hero->getPosition();
				Vec2 uintpos = uint->getPosition();
				if ( random( 1,3) == 3 && abs(heropos.y - uintpos.y) < 20 && (heropos - uintpos).length() > 200 && (heropos - uintpos).length() < 400)
				{
					uint->mAiState = aReadyAttack;
					
					Vec2 temppos;
					if (uintpos.x < heropos.x)
					{
						temppos = Vec2(heropos.x, random(heropos.y - 20, heropos.y - 5));

					}
					else
					{
						temppos = Vec2(heropos.x, random(heropos.y - 20, heropos.y - 5));

					}
					uint->mMoveTime = 0;
					uint->targetPos = temppos;
					uint->stateHandler(MonsterState::uAttack2, false);
				}
				else
				{
					if (canAttack(uint))
					{
						uint->mAiState = aAttack;
					}
					else
					{
						uint->mAiState = aGetAim;

					}
				}
			}
			else
			{
				if (canAttack(uint))
				{
					uint->mAiState = aAttack;
				}
				else
				{
					uint->mAiState = aGetAim;

				}

			}

		}
	}
		break;

	case MonsterAiState::aStanding:
	{
		uint->mMoveTime += dt;
		if (uint->mMoveTime>0.5)
		{
			uint->mMoveTime = 0;
			uint->mAiState = aStand;
		}
	}
		break;
	case MonsterAiState::aAttack:
	{
		
		
			uint->stateHandler(MonsterState::uAttack, false);

		
		uint->mAiState = aAttacking;
	}
		break;
	case MonsterAiState::aAttacking:
	{
		if (uint->mCurState == MonsterState::uAttack1)
		{
			uint->mMoveTime += dt;
			uint->mTick += dt;
			if (uint->mTick > 0.4)
			{
				uint->mTick = 0;
				Hero::getInstance()->BulletHit(uint);
			}
			
			if (uint->mMoveTime > 1.5)
			{
				uint->mTick = 0;
				uint->mMoveTime = 0;
				uint->mAiState = aAttackEnd;
				uint->stateHandler(MonsterState::uBack, false);
				uint->mMoveTime = 0;
				return;
			}
		}
		
	}
		break;
	case MonsterAiState::aAttackEnd:
	{
		uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aDie:
	{
		//uint->stateHandler(MonsterState::uDie, false);
		uint->mAiState = aDieing;
	}
		break;
	case MonsterAiState::aDieing:
	{

	}
		break;
	case MonsterAiState::aDieEnd:
	{

	}
		break;
	case MonsterAiState::aGetAim:
	{
		Hero* hero = Hero::getInstance();
		Vec2 heropos = hero->getPosition();
		Vec2 uintpos = uint->getPosition();
		Vec2 temppos;
		if (uintpos.x < heropos.x)
		{
			temppos = Vec2(heropos.x - 50, random(heropos.y - 20, heropos.y + 20));

		}
		else
		{
			temppos = Vec2(heropos.x + 50, random(heropos.y - 20, heropos.y + 20));

		}
		uint->mMoveTime = 0;
		uint->mAiState = aMoveAim;
		uint->targetPos = temppos;
		//uint->move((temppos - uintpos).getNormalized(), true);
	}
		break;
	case MonsterAiState::aHurt:
	{

	}
		break;
	case MonsterAiState::aHurting:
	{

	}
		break;
	case MonsterAiState::aHurtEnd:
	{
		uint->mMoveTime = 0;
		uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aMoveAim:
	{
			uint->mMoveTime += dt;
			if (uint->mMoveTime > 1)
			{
				uint->mMoveTime = 0;
				uint->mAiState = aStand;
				return;
			}
			if ((uint->targetPos - uint->getPosition()).length() < 5)
			{
				return;
			}
			uint->move((uint->targetPos - uint->getPosition()).getNormalized(), dt);
	}
		break;
	case MonsterAiState::aReadyAttack:
	{
		
		/*Vec2 targetpos = uint->targetPos;
		Vec2 uintpos = uint->getPosition();
		if ((targetpos - uintpos).length() < 5)
		{
			Hero* hero = Hero::getInstance();
			Vec2 heropos = hero->getPosition();
			if ((heropos - uintpos).length() < 20)
			{
				uint->stateHandler(MonsterState::uAttack1, true);
				uint->mMoveTime = 0;
				uint->mAiState = aAttacking;
			}
			else
			{
				uint->mAiState = aStand;
			}
			
		}*/
	
	}
		break;
	default:
		break;
	}
}

void MonsterAi::beeAiLogic(BeeMonster* uint, float dt)
{
	if (uint->mCurLife < 0)
	{
		return;
	}
	switch (uint->mAiState)
	{
	case MonsterAiState::aStand:
	{
		int id = uint->mCurId;

		int rand = random(1, 2);
		if (GameLayer::getInstance()->isShowDaZhao)
		{
			rand = 1;
		}
		if (rand == 1)
		{
			uint->mAiState = aStanding;
			uint->stateHandler(MonsterState::uStand, true);
			uint->mMoveTime = 0;
		}
		else
		{
			if (id == 3)
			{
				Hero* hero = Hero::getInstance();
				Vec2 heropos = hero->getPosition();
				Vec2 uintpos = uint->getPosition();
				if (abs(heropos.y - uintpos.y) < 80 && (heropos - uintpos).length() > 300 && (heropos - uintpos).length() < 500)
				{
					uint->mAiState = aAttack;

				}
				else
				{
					if (canAttack(uint))
					{
						uint->mAiState = aAttack;
					}
					else
					{
						uint->mAiState = aGetAim;

					}
				}
			}
			else
			{
				if (canAttack(uint))
				{
					uint->mAiState = aAttack;
				}
				else
				{
					uint->mAiState = aGetAim;

				}

			}

		}
	}
		break;

	case MonsterAiState::aStanding:
	{
		uint->mMoveTime += dt;
		if (uint->mMoveTime>0.5)
		{
			uint->mMoveTime = 0;
			uint->mAiState = aStand;
		}
	}
		break;
	case MonsterAiState::aAttack:
	{
		Hero* hero = Hero::getInstance();
		Vec2 heropos = hero->getPosition();
		Vec2 uintpos = uint->getPosition();
		if (abs(heropos.y - uintpos.y) < 80 && (heropos - uintpos).length() > 300 && (heropos - uintpos).length() < 500)
		{
			if (uint->mCurId == 3)
			{
				uint->stateHandler(MonsterState::uAttack1, false);
			}
		}
		else
		{
			uint->stateHandler(MonsterState::uAttack, false);
			
		}
		uint->mAiState = aAttacking;
	}
		break;
	case MonsterAiState::aAttacking:
	{

	}
		break;
	case MonsterAiState::aAttackEnd:
	{
		uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aDie:
	{
								 //uint->stateHandler(MonsterState::uDie, false);
		uint->mAiState = aDieing;
	}
		break;
	case MonsterAiState::aDieing:
	{

	}
		break;
	case MonsterAiState::aDieEnd:
	{

	}
		break;
	case MonsterAiState::aGetAim:
	{
		Hero* hero = Hero::getInstance();
		Vec2 heropos = hero->getPosition();
		Vec2 uintpos = uint->getPosition();
		Vec2 temppos;
		if (uintpos.x < heropos.x)
		{
			temppos = Vec2(heropos.x - 50, random(heropos.y - 20, heropos.y + 20));

		}
		else
		{
			temppos = Vec2(heropos.x + 50, random(heropos.y - 20, heropos.y + 20));

		}
		uint->mMoveTime = 0;
		uint->mAiState = aMoveAim;
		uint->targetPos = temppos;
									//uint->move((temppos - uintpos).getNormalized(), true);
	}
		break;
	case MonsterAiState::aHurt:
	{

	}
		break;
	case MonsterAiState::aHurting:
	{

	}
		break;
	case MonsterAiState::aHurtEnd:
	{
		uint->mMoveTime = 0;
		uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aMoveAim:
	{
		uint->mMoveTime += dt;
		if (uint->mMoveTime > 1)
		{
			uint->mMoveTime = 0;
			uint->mAiState = aStand;
			return;
		}
		if ((uint->targetPos - uint->getPosition()).length() < 5)
		{
			return;
		}
		uint->move((uint->targetPos - uint->getPosition()).getNormalized(), dt);
	}
		break;
	case MonsterAiState::aReadyAttack:
	{

	}
		break;
	default:
		break;
	}
}

void MonsterAi::buffAiLogic(BuffMonster* uint, float dt)
{
	if (uint->mCurLife < 0)
	{
		return;
	}
	switch (uint->mAiState)
	{
	case MonsterAiState::aStand:
	{
		int id = uint->mCurId;

		int rand = random(1, 2);
		if (GameLayer::getInstance()->isShowDaZhao)
		{
			rand = 1;
		}
		if (rand == 1)
		{
			uint->mAiState = aStanding;
			uint->stateHandler(MonsterState::uStand, true);
			uint->mMoveTime = 0;
		}
		else
		{
			rand = random(1, 2);
			Hero* hero = Hero::getInstance();
			Vec2 heropos = hero->getPosition();
			Vec2 uintpos = uint->getPosition();
			if ((heropos - uintpos).length() < 500)
			{
				if (rand == 1)
				{
					uint->mAiState = aAttack;
				}
				else
				{
					uint->mAiState = aGetAim;

				}
			}
			else
			{
				uint->mAiState = aGetAim;
			}

		}
	}
		break;

	case MonsterAiState::aStanding:
	{
		uint->mMoveTime += dt;
		if (uint->mMoveTime>0.5)
		{
			uint->mMoveTime = 0;
			uint->mAiState = aStand;
		}
	}
		break;
	case MonsterAiState::aAttack:
	{
		Hero* hero = Hero::getInstance();
		Vec2 heropos = hero->getPosition();
		Vec2 uintpos = uint->getPosition();
		
		uint->stateHandler(MonsterState::uAttack, false);

		uint->targetPos = heropos;
		uint->mAiState = aAttacking;
	}
		break;
	case MonsterAiState::aAttacking:
	{

	}
		break;
	case MonsterAiState::aAttackEnd:
	{
		uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aDie:
	{
		//uint->stateHandler(MonsterState::uDie, false);
		uint->mAiState = aDieing;
	}
		break;
	case MonsterAiState::aDieing:
	{

	}
		break;
	case MonsterAiState::aDieEnd:
	{

	}
		break;
	case MonsterAiState::aGetAim:
	{
		Hero* hero = Hero::getInstance();
		Vec2 heropos = hero->getPosition();
		Vec2 uintpos = uint->getPosition();
		Vec2 temppos;

		temppos = Vec2(random(heropos.x - 300, heropos.x + 300), random(20, 180));

		
		uint->mMoveTime = 0;
		uint->mAiState = aMoveAim;
		uint->targetPos = temppos;
		//uint->move((temppos - uintpos).getNormalized(), true);
	}
		break;
	case MonsterAiState::aHurt:
	{

	}
		break;
	case MonsterAiState::aHurting:
	{

	}
		break;
	case MonsterAiState::aHurtEnd:
	{
		uint->mMoveTime = 0;
		uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aMoveAim:
	{
		uint->mMoveTime += dt;
		if (uint->mMoveTime > 1)
		{
			uint->mMoveTime = 0;
			uint->mAiState = aStand;
			return;
		}
		if ((uint->targetPos - uint->getPosition()).length() < 5)
		{
			return;
		}
		uint->move((uint->targetPos - uint->getPosition()).getNormalized(), dt);
	}
		break;
	case MonsterAiState::aReadyAttack:
	{

	}
		break;
	default:
		break;
	}
}

void MonsterAi::dragonAiLogic(DragonMonster* uint, float dt)
{
	if (uint->mCurLife < 0)
	{
		return;
	}
	switch (uint->mAiState)
	{
		case MonsterAiState::aStand:
		{
			int id = uint->mCurId;
			int rand = random(1, 2);
			if (GameLayer::getInstance()->isShowDaZhao)
			{
				rand = 1;
			}
			if (rand == 1)
			{
				uint->mAiState = aStanding;
				uint->stateHandler(MonsterState::uStand, true);
				uint->mMoveTime = 0;
			}
			else
			{
				uint->mAiState = aAttack;
			}
		}
		break;

		case MonsterAiState::aStanding:
		{
			uint->mMoveTime += dt;
			if (uint->mMoveTime>0.5)
			{
				uint->mMoveTime = 0;
				uint->mAiState = aStand;
			}
		}
		break;
	case MonsterAiState::aAttack:
	{
		
		uint->stateHandler(MonsterState::uAttack, false);
		uint->mAiState = aAttacking;
	}
		break;
	case MonsterAiState::aAttacking:
	{

	}
		break;
	case MonsterAiState::aAttackEnd:
	{
	   uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aDie:
	{
		//uint->stateHandler(MonsterState::uDie, false);
		uint->mAiState = aDieing;
	}
		break;
	case MonsterAiState::aDieing:
	{

	}
		break;
	case MonsterAiState::aDieEnd:
	{

	}
		break;
	case MonsterAiState::aGetAim:
	{
		
	}
		break;
	case MonsterAiState::aHurt:
	{

	}
		break;
	case MonsterAiState::aHurting:
	{

	}
		break;
	case MonsterAiState::aHurtEnd:
	{
		uint->mMoveTime = 0;
		uint->mAiState = aStand;
	}
		break;
	case MonsterAiState::aMoveAim:
	{
		
	}
		break;
	case MonsterAiState::aReadyAttack:
	{

	}
		break;
	default:
		break;
	}
}

bool MonsterAi::canAttack(Uint* uint)
{
	Hero* hero = Hero::getInstance();
	Vec2 heropos = hero->getPosition();
	Vec2 uintpos = uint->getPosition();
	if (uint->mName == "goblin")
	{
		if (abs(heropos.y -uintpos.y)<30 && (uint->armatureHead->getBoundingBox().size.width / 2 + hero->armatureHead->getBoundingBox().size.width / 2 + 20) > abs(heropos.x - uintpos.x) &&
			abs(heropos.x - uintpos.x) > 40)
		{
			return true;
		}
	}
	else if (uint->mName == "bee")
	{
		if (abs(heropos.y - uintpos.y)<30 && (uint->armatureHead->getBoundingBox().size.width / 2 + hero->armatureHead->getBoundingBox().size.width / 2 + 20) > abs(heropos.x - uintpos.x) &&
			abs(heropos.x - uintpos.x) > 40)
		{
			return true;
		}
	}
	else if (uint->mName == "fox")
	{
		if (abs(heropos.y - uintpos.y)<30 && (uint->armatureHead->getBoundingBox().size.width / 2 + hero->armatureHead->getBoundingBox().size.width / 2 + 20) > abs(heropos.x - uintpos.x) &&
			abs(heropos.x - uintpos.x) > 40)
		{
			return true;
		}
	}
	else if (uint->mName == "buff")
	{
		if (abs(heropos.y - uintpos.y)<30 && (uint->armatureHead->getBoundingBox().size.width / 2 + hero->armatureHead->getBoundingBox().size.width / 2 + 20) > abs(heropos.x - uintpos.x) &&
			abs(heropos.x - uintpos.x) > 40)
		{
			return true;
		}
	}
	else if (uint->mName == "pig")
	{
		if (abs(heropos.y - uintpos.y)<30 && (uint->armatureHead->getBoundingBox().size.width / 2 + hero->armatureHead->getBoundingBox().size.width / 2 + 20) > abs(heropos.x - uintpos.x) &&
			abs(heropos.x - uintpos.x) > 40)
		{
			return true;
		}
	}
	else if (uint->mName == "dragon")
	{
		if (abs(heropos.y - uintpos.y)<50 && (uint->armatureHead->getBoundingBox().size.width / 2 + hero->armatureHead->getBoundingBox().size.width / 2 + 50) > abs(heropos.x - uintpos.x) &&
			abs(heropos.x - uintpos.x) > 40)
		{
			return true;
		}
	}
	return false;
}