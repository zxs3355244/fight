#include "ArmBullet.h"
#include "Hero.h"
#include "Audio.h"
ArmBullet::ArmBullet()
{
	mSpeed = 0;
	mMoveMaxLen = 800;
	mMoveLen = 0;
	isDie = false;
	mName = "armbullet";
	bigName = "armbullet";
	mCurDir = 1;
	isDaoDanFly = false;
}

ArmBullet::~ArmBullet()
{

}

ArmBullet* ArmBullet::create(int id,int index)
{
	ArmBullet* bl = new ArmBullet();
	bl->mCurId = id;
	bl->mCurDir = index;
	bl->autorelease();
	bl->init();
	return bl;
}

bool ArmBullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	
	
	
	mSpeed = 600;
	mMoveMaxLen = 600;
	mMoveLen = 0;
	mHurt = 30;
	if (mCurId == ArmBulletType::mFuZi)
	{
		armature = Armature::create("goblin_bullet");

	}
	else if (mCurId == ArmBulletType::mBee)
	{
		armature = Armature::create("bee_bullet");
	}
	else if (mCurId == ArmBulletType::mBuff)
	{
		armature = Armature::create("buff_bullet");
	}
	else if (mCurId == ArmBulletType::mDaoDan ||
		mCurId == ArmBulletType::mQiu)
	{
		armature = Armature::create("bomb");
	}
	this->addChild(armature, 1);

	Rect rectbl = armature->getBoundingBox();

	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ArmBullet::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(ArmBullet::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	shootBullet();
	return true;
}

void ArmBullet::setDir(int dir)
{
	mCurDir = dir;
}

void ArmBullet::showBullet()
{
	if (mCurId == ArmBulletType::mDaoDan)
	{
		armature->getAnimation()->play("daodan_fly", 0, false);
		isDaoDanFly = true;
		Vec2 pos = this->getPosition();
		if (mCurDir == 1)
		{
			this->armature->setScaleX(-1);
			this->targetPos.x = random(pos.x+200,pos.x + 500);
			this->targetPos.y = random(20,260);
		}
		else
		{
			this->armature->setScaleX(1);
			this->targetPos.x = random(pos.x - 500, pos.x - 200);
			this->targetPos.y = random(20, 260);
		}
		this->runAction(Sequence::create(MoveTo::create(1.0f, this->targetPos), nullptr));

	}
}

void ArmBullet::shootBullet()
{
	switch (mCurId)
	{
	case ArmBulletType::mFuZi:
	{
		armature->getAnimation()->play("arm", 0, true);
	}
		break;
	case ArmBulletType::mBee:
	{
		armature->getAnimation()->play("attack2_zd", 0, true);
	}
		break;
	case ArmBulletType::mBuff:
	{
		char buff[30];
		sprintf(buff, "magic_%d", mCurDir-1);
		armature->getAnimation()->play(buff, 0, false);
	}
		break;
	
	case ArmBulletType::mQiu:
	{
		armature->getAnimation()->play("lightingball_move", 0, true);
	}
		break;
	default:
		break;
	}
}

void ArmBullet::showAniAction(int id)
{

}

void ArmBullet::updateLogic(float dt)
{

}

void ArmBullet::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
	{

		if (movementID == "arm")
		{
			//	armature->getAnimation()->play("zd_phq2", 0, false);
		}
		else if (movementID == "daodan_fly")
		{
			daodantime = 0;
			isDaoDanFly = false;
			this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=](){
				armature->getAnimation()->play("daodan_boom_pre", 0, false);
			}), nullptr));
		}
		else if (movementID == "daodan_boom_pre")
		{
			Audio::getInstance()->playEffMusic("rocketmanskill5.mp3");
			armature->getAnimation()->play("daodan_boom", 0, false);
		}
		else if (movementID == "daodan_boom")
		{
			if ((this->getPosition() - Hero::getInstance()->getPosition()).length() < 50)
			{
				Hero::getInstance()->BulletHit(this);
			}
			this->isDie = true;
		}
	}
}

void ArmBullet::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{

}

void ArmBullet::updateState()
{

}


void ArmBullet::setAngel(float angel)
{
	mAngel = angel;
	this->setRotation(mAngel);
}

void ArmBullet::updatePos(float dt)
{
	if (mCurId == mFuZi)
	{
		if (this->mCurDir == 1)
		{
			this->setPosition(Vec2(this->getPositionX() + dt*mSpeed, this->getPositionY()));
		}
		else if (this->mCurDir == 2)
		{
			this->setPosition(Vec2(this->getPositionX() - dt*mSpeed, this->getPositionY()));
		}
		mMoveLen += dt*mSpeed;
		if (mMoveLen > mMoveMaxLen)
		{
			isDie = true;
		}
	}
	else if (mCurId == mBee)
	{
		if (this->mCurDir == 1)
		{
			this->setPosition(Vec2(this->getPositionX() - cos(CC_DEGREES_TO_RADIANS(mAngel))*dt*mSpeed, this->getPositionY() + sin(CC_DEGREES_TO_RADIANS(mAngel))* dt*mSpeed));
		}
		else
		{
			this->setPosition(Vec2(this->getPositionX() - cos(CC_DEGREES_TO_RADIANS(mAngel))*dt*mSpeed, this->getPositionY() + sin(CC_DEGREES_TO_RADIANS(mAngel))* dt*mSpeed));
		}
		mMoveLen += dt*mSpeed;
		if (mMoveLen > mMoveMaxLen)
		{
			isDie = true;
		}
	}
	else if(mCurId == mQiu)
	{
		if (this->mCurDir == 1)
		{

			this->setPosition(Vec2(this->getPositionX() + dt*300, this->getPositionY()));
		}
		else if (this->mCurDir == 2)
		{
			this->setPosition(Vec2(this->getPositionX() - dt*300, this->getPositionY()));
		}
		mMoveLen += dt*300;
		if (mMoveLen > mMoveMaxLen)
		{
			isDie = true;
		}
	}
}