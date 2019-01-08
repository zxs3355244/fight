#include "Bullet.h"
#include "Hero.h"

Bullet::Bullet()
{
	mSpeed = 0;
	mMoveMaxLen = 800;
	mMoveLen = 0;
	isDie = false;
	mName = "mybullet";
	bigName = "mybullet";
}

Bullet::~Bullet()
{

}

Bullet* Bullet::create(int id)
{
	Bullet* bl = new Bullet();
	bl->autorelease();
	bl->mCurId = id;
	bl->init();
	return bl;
}

bool Bullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	mDir = Hero::getInstance()->mCurDir;
	if (mCurId == RoleEquip::ePengHuoQi1 || mCurId == RoleEquip::ePengHuoQi2)
	{
		armature = Armature::create("hero_fire");
	}
	else
	{
		armature = Armature::create("hero_atk");
	}
	mEquipData = CvsFile::getInstance()->getEquipData(mCurId);
	mSpeed = mEquipData->speed;
	mMoveMaxLen = mEquipData->moveLen;
	mMoveLen = 0;
	mHurt = mEquipData->mHurt;
	this->addChild(armature, 1);
	
	Rect rectbl = armature->getBoundingBox();
	
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Bullet::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Bullet::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	shootBullet();
	return true;
}

void Bullet::shootBullet()
{
	switch (mCurId)
	{
	case RoleEquip::eDao:
	{
		armature->getAnimation()->play("zd_daoguang", 0, false);
	}
		break;

	case RoleEquip::eJiQiang:
	{
		armature->getAnimation()->play("zd_jq_1", 0, false);
		
	}
		break;
	case RoleEquip::eJiQiang1:
	{
			armature->getAnimation()->play("zd_jq_2", 0, false);

	}
		break;
	case RoleEquip::eJuJi:
	{
		armature->getAnimation()->play("zd_jjq_2_1", 0, false);
	}
		break;
	case RoleEquip::eJuJi1:
	{
		armature->getAnimation()->play("zd_jjq_2_2", 0, false);
	}
		break;
	case RoleEquip::eXianDan:
	{
		armature->getAnimation()->play("zd_jjq_2_1", 0, false);
	}
		break;
	case RoleEquip::ePao:
	{
		armature->getAnimation()->play("zd_pd_2", 0, false);
	}
		break;
	case RoleEquip::ePao1:
	{
		armature->getAnimation()->play("zd_pd_3", 0, false);
	}
		break;
	case RoleEquip::eGeLin:
	{
		armature->getAnimation()->play("zd_jtl", 0, false);
	}
		break;
	case RoleEquip::ePengHuoQi1:
	{
		armature->setVisible(false);
		//char buf[20];
		int t = 0;
		for (int i = 0; i < 4; i++)
		{
			armature1[i] = Armature::create("hero_fire");
			armature1[i]->getAnimation()->play("zd_phq4_1", 0, 0);
			this->addChild(armature1[i], 1);
			//armature1[i]->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Bullet::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			//armature1[i]->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Bullet::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
			armature1[i]->setPosition(Vec2(20, 20));
		}

	}
		break;
	case RoleEquip::ePengHuoQi2:
	{
		armature->setVisible(false);
		//char buf[20];
		int t = 0;
		for (int i = 0; i < 4; i++)
		{
			//sprintf(buf, "zd_phq4_%d", i % 2 == 0 ? 1 : 2);
			armature1[i] = Armature::create("hero_fire");
			armature1[i]->getAnimation()->play("zd_phq4_2", 0, 0);
			this->addChild(armature1[i], 1);
			//armature1[i]->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Bullet::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			//armature1[i]->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Bullet::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
			armature1[i]->setPosition(Vec2(20, 20));
		}
	}
		break;
	case RoleEquip::eShouQiang:
	{
		 armature->getAnimation()->play("zd_sq_1", 0, false);
	}
		break;
	default:
		break;
	}
}

void Bullet::showAniAction(int id)
{
	
}

void Bullet::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
	{

		if (movementID == "zd_phq1")
		{
		//	armature->getAnimation()->play("zd_phq2", 0, false);
		}
		else if (movementID == "zd_phq2")
		{
			//armature->getAnimation()->play("zd_phq3", 0, false);
		}
		else if (movementID == "zd_phq3")
		{

		}
		else if (movementID == "zd_phq4_2")
		{
			
		}
		else if (movementID == "zd_phq4_1")
		{
			//armature->getAnimation()->play("zd_phq4_2", 0, false);
		}
	}
}

void Bullet:: onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{

}

void Bullet::updateState()
{

}

void Bullet::updatePos(float dt)
{
	if (mCurId == RoleEquip::ePengHuoQi1 || mCurId == RoleEquip::ePengHuoQi2)
	{
		for (int i = 0; i < 4; i++)
		{
			if (this->mDir == 1)
			{

				armature1[i]->setPosition(Vec2(armature1[i]->getPositionX() + random(0, 5), armature1[i]->getPositionY() + random(-5, 5)));
			}
			else if (this->mDir == 2)
			{
				armature1[i]->setPosition(Vec2(armature1[i]->getPositionX() + random(-5, 0), armature1[i]->getPositionY() + random(-5, 5)));
			}
			
		}
	}
	if (this->mDir == 1)
	{
		
		this->setPosition(Vec2(this->getPositionX() + dt*mSpeed, this->getPositionY()));
	}
	else if (this->mDir == 2)
	{
		this->setPosition(Vec2(this->getPositionX() - dt*mSpeed, this->getPositionY()));
	}
	mMoveLen += dt*mSpeed;
	if (mMoveLen > mMoveMaxLen)
	{
		isDie = true;
	}
}