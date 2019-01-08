#include "Uint.h"

Uint* Uint::create(string name, int id, bool isBoss)
{

	Uint* mUint = new Uint();
	mUint->init();
	return mUint;
	
}


void Uint::updateLogic(float dt)
{

}

bool Uint::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}




Uint::Uint()
{
	mWave = 0;
	mAiState = 1;
	mMoveTime = 0;
	bigName = "monster";
	isDie = false;
	dieNum = 0;
	mAngel = 0;
	mTick = 0;
	isHurt = false;
	showEff = true;
	txOver = false;
}

Uint::~Uint()
{

}

void Uint::stateHandler(int state, bool loop)
{

}
void Uint::setProper(MonsterOneData* data)
{

}

void Uint::setAction(string name, bool bl)
{

}
void Uint::BulletHit(Uint* uint)
{

}

void Uint::daoZhaoHit()
{
	this->stateHandler(MonsterState::uHurt,false);
	//if (name != "")
	{
		armatureAtr->setVisible(true);
		armatureAtr->setPositionY(30);
		armatureAtr->getAnimation()->play("jtltx", 0, false);
	}
}


void Uint::daoZhaoEnd()
{

}

void Uint::setAngel(float angel)
{

}