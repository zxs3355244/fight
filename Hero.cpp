#include "Hero.h"
#include "Config.h"
#include "Bullet.h"
#include "GameLayer.h"
#include "Map.h"
#include "Audio.h"
static Hero* mHero = NULL;

Hero* Hero::getInstance()
{
	if (mHero == NULL)
	{
		mHero = new Hero();
		mHero->init();
		mHero->autorelease();
		return mHero;
	}
	return mHero;
}

bool Hero::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isFootMoveing = false;
	armatureFoot = Armature::create("hero2");
	this->addChild(armatureFoot,1);

	armatureHead = Armature::create("hero");
	this->addChild(armatureHead,2);

	armatureFoot->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Hero::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	armatureFoot->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Hero::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

	armatureAtr = Armature::create("hero_atk");
	this->addChild(armatureAtr, 4);
	armatureAtr->setVisible(false);

	armatureHead->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Hero::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	armatureHead->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Hero::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

	armatureAtr->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Hero::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	armatureAtr->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Hero::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	this->setScale(1.2);
	return true;
}

void Hero::showAniByEquipId(int id)
{
	mCurRoleEqu = id;
	Bone* penghuo1 = armatureFoot->getBone("penghuo1");
	Bone* penghuo2 = armatureFoot->getBone("penghuo2");
	
	switch (id)
	{
	case RoleEquip::eDao:
	{

		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("dao")->changeDisplayWithIndex(0,true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_dao", 0, true);
	}
		break;
	case RoleEquip::eDao1:
	{

		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("dao")->changeDisplayWithIndex(1, true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_dao", 0, true);
	}
		break;
	case RoleEquip::eJiQiang:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("jiqiang")->changeDisplayWithIndex(0, true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_jiqiang", 0, true);
	}
		break;
	case RoleEquip::eJiQiang1:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("jiqiang")->changeDisplayWithIndex(1, true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_jiqiang", 0, true);
	}
		break;
	case RoleEquip::eJuJi:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("juji")->changeDisplayWithIndex(0, true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_juji", 0, true);
	}
		break;
	case RoleEquip::eJuJi1:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("juji")->changeDisplayWithIndex(1, true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_juji", 0, true);
	}
		break;
	case RoleEquip::eXianDan:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("xiandan")->changeDisplayWithIndex(0, true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_xiandan", 0, true);

	}
		break;
	case RoleEquip::eXianDan1:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("xiandan")->changeDisplayWithIndex(1, true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_xiandan", 0, true);

	}
		break;
	case RoleEquip::ePao:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("jupao")->changeDisplayWithIndex(0, true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_pao", 0, true);
	}
		break;
	case RoleEquip::ePao1:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureHead->getBone("jupao")->changeDisplayWithIndex(1, true);
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_pao", 0, true);
	}
		break;
	case RoleEquip::eGeLin:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_gelin", 0, true);
	}
		break;
	case RoleEquip::ePengHuoQi1:
	{
		armatureFoot->removeFromParent();
		armatureFoot = Armature::create("hero2");
		this->addChild(armatureFoot,1);
		armatureFoot->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Hero::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		armatureFoot->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Hero::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		if (penghuo2)
		{
			armatureFoot->getBone("penghuo2")->removeFromParent(true);
		}
		
		armatureFoot->getAnimation()->play("stand", 0, true);
		armatureHead->getBone("penghuoqi")->changeDisplayWithIndex(0,true);
		armatureHead->getAnimation()->play("stand_penghuoqi", 0, true);
	}
		break;
	case RoleEquip::ePengHuoQi2:
	{
			armatureFoot->removeFromParent();
			armatureFoot = Armature::create("hero2");
			this->addChild(armatureFoot,1);
			armatureFoot->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Hero::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			armatureFoot->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Hero::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
			if (penghuo1)
			{
				armatureFoot->getBone("penghuo1")->removeFromParent(true);
			}
			
			armatureFoot->getAnimation()->play("stand", 0, true);
			armatureHead->getBone("penghuoqi")->changeDisplayWithIndex(1, true);
			armatureHead->getAnimation()->play("stand_penghuoqi", 0, true);
	}
		break;
	case RoleEquip::eShouQiang:
	{
		if (penghuo1)
		{
			penghuo1->removeFromParent(true);
		}
		if (penghuo2)
		{
			penghuo2->removeFromParent(true);
		}
		armatureFoot->getAnimation()->play("stand", 0, true);

		armatureHead->getAnimation()->play("stand_shouqiang", 0, true);
	}
		break;

	default:
		break;
	}
	mEquipData = CvsFile::getInstance()->getEquipData(mCurRoleEqu);
	mHurt = mEquipData->mHurt;
}


void Hero::BulletHit(Uint* uint)
{
	if (haveDun)
	{
		return;
	}

	if (mCurLife < 0)
	{
		return;
	}
	
	mCurLife -= uint->mHurt;
	
	if (mCurLife < 0)
	{
		
		//die
		mCurLife = 0;
		GameLayer::getInstance()->BarHp->setPercent(0);
		stateHandler(RoleAction::die, 0);
		mCurLife = -1;
	}
	else
	{
		//hurt
		GameLayer::getInstance()->mXue->setVisible(true);
		GameLayer::getInstance()->mXue->runAction(Sequence::create( FadeIn::create(0.3),FadeOut::create(0.5),nullptr));
		GameLayer::getInstance()->BarHp->setPercent(100*mCurLife/mLife);
		stateHandler(RoleAction::hurt, 0);
	}
}

void Hero::shootBullet()
{
	switch (mCurRoleEqu)
	{
	case RoleEquip::eDao:
	{
							
	}
		break;
	case RoleEquip::eGeLin:
	{
		Bullet* bl = Bullet::create(RoleEquip::eGeLin);
		GameLayer::getInstance()->addObj(bl);
		Vec2 pos = this->getPosition();
		if (mCurDir == 2)
		{
			bl->armature->setScaleX(-1);
			pos.x -= this->armatureHead->getBoundingBox().size.width * 2;
		}

		bl->setPosition(Vec2(pos.x + bl->armature->getContentSize().width + 20, pos.y + 10));
		setAtrAction(false);
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
	
		schedule(CC_SCHEDULE_SELECTOR(Hero::shootBulletSched), 0.1f, 1, 0);
	}
		break;
	case RoleEquip::eJiQiang:
	case RoleEquip::eJiQiang1:
	{
		Bullet* bl = Bullet::create(mCurRoleEqu);
		GameLayer::getInstance()->addObj(bl);
		Vec2 pos = this->getPosition();
		if (mCurDir == 2)
		{
			pos.x -= this->armatureHead->getBoundingBox().size.width*2;
		} 

		bl->setPosition(Vec2(pos.x + bl->armature->getContentSize().width+20, pos.y+ 10));
		Bullet* bl1 = Bullet::create(mCurRoleEqu);
		GameLayer::getInstance()->addObj(bl1);
		bl1->setPosition(Vec2(pos.x + 20, pos.y + 10));
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
		schedule(CC_SCHEDULE_SELECTOR(Hero::shootBulletSched), 0.1f, 1, 0);
	}
		break;
	case RoleEquip::eJuJi:
	case RoleEquip::eJuJi1:
	{
		Bullet* bl = Bullet::create(mCurRoleEqu);
		GameLayer::getInstance()->addObj(bl);
		Vec2 pos = this->getPosition();
		if (mCurDir == 2)
		{
			bl->armature->setScaleX(-1);
			pos.x -= this->armatureHead->getBoundingBox().size.width * 2;
		}

		bl->setPosition(Vec2(pos.x + bl->armature->getContentSize().width + 20, pos.y + 10));
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
	}
		break;
	case RoleEquip::ePao:
	case RoleEquip::ePao1:
	{
		Bullet* bl = Bullet::create(mCurRoleEqu);
		GameLayer::getInstance()->addObj(bl);
		Vec2 pos = this->getPosition();
		if (mCurDir == 2)
		{
			bl->armature->setScaleX(-1);
			pos.x -= this->armatureHead->getBoundingBox().size.width * 2;
		}

		bl->setPosition(Vec2(pos.x + bl->armature->getContentSize().width + 20, pos.y + 10));
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
	}
		break;
	case RoleEquip::ePengHuoQi1:
	{
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
	}
		break;
	case RoleEquip::ePengHuoQi2:
	{
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
	}
		break;
	case RoleEquip::eShouQiang:
	{
		Bullet* bl = Bullet::create(RoleEquip::eShouQiang);
		GameLayer::getInstance()->addObj(bl);
		Vec2 pos = this->getPosition();
		if (mCurDir == 2)
		{
			bl->armature->setScaleX(-1);
			pos.x -= this->armatureHead->getBoundingBox().size.width * 2;
		}

		bl->setPosition(Vec2(pos.x + bl->armature->getContentSize().width + 20, pos.y + 10));
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
	}
		break;
	case RoleEquip::eXianDan:
	{
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
	}
		break;
	default:
		break;
	}
}

void Hero::shootBulletSched(float dt)
{
	switch (mCurRoleEqu)
	{
	case RoleEquip::eDao:
	{

	}
		break;
	case RoleEquip::eGeLin:
	{
		Bullet* bl = Bullet::create(RoleEquip::eGeLin);
		GameLayer::getInstance()->addObj(bl);
		Vec2 pos = this->getPosition();
		if (mCurDir == 2)
		{
			bl->armature->setScaleX(-1);
			pos.x -= this->armatureHead->getBoundingBox().size.width * 2;
		}

		bl->setPosition(Vec2(pos.x + bl->armature->getContentSize().width + 20, pos.y + 10));
		setAtrAction(false);
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
	
	}
		break;
	case RoleEquip::eJiQiang:
	case RoleEquip::eJiQiang1:
	{
		Bullet* bl = Bullet::create(mCurRoleEqu);
		GameLayer::getInstance()->addObj(bl);
		Vec2 pos = this->getPosition();
		if (mCurDir == 2)
		{
			pos.x -= this->armatureHead->getBoundingBox().size.width * 2;
		}
		bl->setPosition(Vec2(pos.x + bl->armature->getContentSize().width + 20, pos.y + 10));
		Bullet* bl1 = Bullet::create(mCurRoleEqu);
		GameLayer::getInstance()->addObj(bl1);
		bl1->setPosition(Vec2(pos.x +20, pos.y + 10));
		Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
		
	}
		break;
	case RoleEquip::eJuJi:
	{

	}
		break;
	case RoleEquip::ePao:
	{

	}
		break;
	case RoleEquip::ePengHuoQi1:
	{
		Bullet* bl = Bullet::create(RoleEquip::ePengHuoQi1);
		GameLayer::getInstance()->addObj(bl);
		Vec2 pos = this->getPosition();
		if (mCurDir == 2)
		{
			bl->armature->setScaleX(-1);
			pos.x -= this->armatureHead->getBoundingBox().size.width;
		}

		bl->setPosition(Vec2(pos.x + bl->armature->getContentSize().width + 20, pos.y + 10));

	}
		break;
	case RoleEquip::ePengHuoQi2:
	{
		Bullet* bl = Bullet::create(RoleEquip::ePengHuoQi2);
		GameLayer::getInstance()->addObj(bl);
		Vec2 pos = this->getPosition();
		if (mCurDir == 2)
		{
			bl->armature->setScaleX(-1);
			pos.x -= this->armatureHead->getBoundingBox().size.width;
		}

		bl->setPosition(Vec2(pos.x + bl->armature->getContentSize().width + 20, pos.y + 10));

	}
		break;
	case RoleEquip::eShouQiang:
	{

	}
		break;
	case RoleEquip::eXianDan:
	{

	}
		break;
	default:
		break;
	}
	mEquipData = CvsFile::getInstance()->getEquipData(mCurRoleEqu);
	mHurt = mEquipData->mHurt;
}
void Hero::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	
}

void Hero::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
	{
		if (armature == armatureAtr)
		{
			armature->setVisible(false);
			return;
		}
		if (movementID == "kaihuo")
		{
			//setHeadAction("stand_" + actEquipName[mCurRoleEqu - 1], true);
			//setFootAction("stand", true);
		}
		else if (movementID == "chongci")
		{
			mCurRoleAct = RoleAction::stand;
			setHeadAction("stand_" + actEquipName[mCurRoleEqu - 1], true);
			setFootAction("stand", true);
		}
		else if (movementID == "move")
		{
			mCurRoleAct = RoleAction::stand;
			setHeadAction("stand_" + actEquipName[mCurRoleEqu - 1], true);
			setFootAction("stand", true);
		}
		else if (movementID == "stand")
		{
			/*setHeadAction("stand_" + actEquipName[mCurRoleEqu - 1], false);
			setFootAction("stand", true);*/
		}
		else if (movementID == "die")
		{
			/*mCurRoleAct = RoleAction::stand;
			setHeadAction("die_" + actEquipName[mCurRoleEqu - 1], false);
			setFootAction("die", false);*/

			//ËÀÍö

			GameLayer::getInstance()->gameOver(false);
		}

		else if (movementID == "stun")
		{
			mCurRoleAct = RoleAction::stand;
			setHeadAction("stand_" + actEquipName[mCurRoleEqu - 1], true);
			setFootAction("stand", true);
		}
		else if (movementID == "kaipao")
		{
			mCurRoleAct = RoleAction::stand;
			setHeadAction("stand_" + actEquipName[mCurRoleEqu - 1], true);
			setFootAction("stand", true);
		}
		else if (movementID.find("hurt_", 0) == 0)
		{
			if (!GameLayer::getInstance()->mRocker->isTouch())
			{
				stateHandler(RoleAction::stand, 0);
			}
			else
			{
				stateHandler(RoleAction::move, 0);
			}
		}
		if (movementID.find("kaiqiang_",0) == 0)
		{
			if (movementID == "kaiqiang_juji")
			{
				mJuJiTime = 0;
				mCurAimAct = JuJiAction::kaihuoBegin;
				setHeadAction("juji_xunhuan", false);
				setFootAction("kaihuo", false);
				if (btnTouch == false)
				{
					btnTouch = false;
					mCurAimAct = 0;
					stateHandler(RoleAction::stand, 0);
				}
			}
			else
			{
				if (movementID == "kaiqiang_dao" || movementID == "kaiqiang_dao2")
				{
					daoHit();
				}
				else if (movementID == "kaiqiang_xiandan")
				{
					SanDanHit();
				}
				if (!GameLayer::getInstance()->mRocker->isTouch())
				{
					stateHandler(RoleAction::stand, 0);
				}
				else
				{
					stateHandler(RoleAction::move, 0);
				}
			}
		}
		else if (movementID == "juji_xunhuan")
		{
			if (btnTouch == false)
			{
				mCurAimAct = 0;
				stateHandler(RoleAction::stand, 0);
				return;
			}
			mJuJiTime++;
			if (mJuJiTime >= 2)
			{
				mJuJiTime = 0;
				mCurAimAct = JuJiAction::kaihuoAim1;
				setHeadAction("juji_xunhuan2", false);
				setFootAction("kaihuo", false);
				return;
			}
			setHeadAction("juji_xunhuan", false);
			setFootAction("kaihuo", false);
		}
		else if (movementID == "juji_xunhuan2")
		{
			if (btnTouch == false)
			{
				mCurAimAct = 0;
				stateHandler(RoleAction::stand, 0);
				return;
			}
			mJuJiTime++;
			if (mJuJiTime >= 2)
			{
				mJuJiTime = 0;
				mCurAimAct = JuJiAction::kaihuoAim2;
				setHeadAction("juji_xunhuan3", true);
				setFootAction("kaihuo", true);
				return;
			}
			setHeadAction("juji_xunhuan2", false);
			setFootAction("kaihuo", false);
		}
		else if (movementID == "juji_kaihuo")
		{
			mJuJiTime= 0;
			mCurAimAct = 0;
			mCurRoleAct = RoleAction::stand;
			setHeadAction("stand_" + actEquipName[mCurRoleEqu - 1], true);
			setFootAction("stand", true);
		}
		for (int i = 0; i < 14; i++)
		{
			if (movementID != "" && movementID == actEffName[i])
			{
				armatureAtr->setVisible(false);
			}
		}
	}
}


void Hero::SanDanHit()
{
	Vec2 pos = this->getPosition();
	for (int i = 0; i < GameLayer::getInstance()->ObjVec.size(); i++)
	{
		Uint* uint = GameLayer::getInstance()->ObjVec[i];
		if (uint->bigName == "monster")
		{
			if (uint->mCurDir == this->mCurDir)
			{
				continue;
			}
			Vec2 posmonster = uint->getPosition();

			Rect rect = armatureHead->getBoundingBox();
			rect.origin.x = pos.x;
			rect.origin.y = pos.y;
			rect.size.width = rect.size.width;
			rect.size.height = rect.size.height * 4 / 5;
			if (mCurDir == 2)
			{
				rect.origin.x -= rect.size.width;
			}
			Rect rectmon = uint->armatureHead->getBoundingBox();
			rectmon.origin.x = posmonster.x;
			rectmon.origin.y = posmonster.y;
			rectmon.size.width = rect.size.width;
			rectmon.size.height = rect.size.height * 4 / 5;
			if (uint->mCurDir == 2)
			{
				rectmon.origin.x -= rectmon.size.width;
			}

			bool isIn = false;
			if (rect.intersectsRect(rectmon))
			{
				isIn = true;
			}
			if (isIn)
			{
				if (uint->mName == "goblin")
				{
					Monster* monster = dynamic_cast<Monster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "bee")
				{
					BeeMonster* monster = dynamic_cast<BeeMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "fox")
				{
					FoxMonster* monster = dynamic_cast<FoxMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "buff")
				{
					BuffMonster* monster = dynamic_cast<BuffMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "pig")
				{
					PigMonster* monster = dynamic_cast<PigMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "dragon")
				{
					DragonMonster* monster = dynamic_cast<DragonMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "bomb")
				{
					Bomb* monster = dynamic_cast<Bomb*>(uint);
					monster->BulletHit(NULL);
				}
			}


		}
	}
}

void Hero::daoHit()
{
	Vec2 pos = this->getPosition();
	for (int i = 0; i < GameLayer::getInstance()->ObjVec.size(); i++)
	{
		Uint* uint = GameLayer::getInstance()->ObjVec[i];
		if (uint->bigName == "monster")
		{
			Vec2 posmonster = uint->getPosition();

			Rect rect = armatureHead->getBoundingBox();
			rect.origin.x = pos.x;
			rect.origin.y = pos.y;
			rect.size.width = rect.size.width * 3 / 5;
			rect.size.height = rect.size.height * 3 / 5;
			if (mCurDir == 2)
			{
				rect.origin.x -= rect.size.width;
			}
			Rect rectmon = uint->armatureHead->getBoundingBox();
			rectmon.origin.x = posmonster.x;
			rectmon.origin.y = posmonster.y;
			rectmon.size.width = rect.size.width * 3 / 5;
			rectmon.size.height = rect.size.height * 3 / 5;
			if (uint->mCurDir == 2)
			{
				rectmon.origin.x -= rectmon.size.width;
			}

			bool isIn = false;
			if (rect.intersectsRect(rectmon))
			{
				isIn = true;
			}
			if (isIn)
			{
				if (uint->mName == "goblin")
				{
					Monster* monster = dynamic_cast<Monster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "bee")
				{
					BeeMonster* monster = dynamic_cast<BeeMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "fox")
				{
					FoxMonster* monster = dynamic_cast<FoxMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "buff")
				{
					BuffMonster* monster = dynamic_cast<BuffMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "pig")
				{
					PigMonster* monster = dynamic_cast<PigMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "dragon")
				{
					DragonMonster* monster = dynamic_cast<DragonMonster*>(uint);
					monster->BulletHit(NULL);
				}
				else if (uint->mName == "bomb")
				{
					Bomb* monster = dynamic_cast<Bomb*>(uint);
					monster->BulletHit(NULL);
				}
			}
			
			
		}
	}
}

void Hero::actTouch()
{
	if (mCurLife < 0)
	{
		return;
	}
	if (btnTouch == false)
	{
		curBulletTick = 0;

		return;
	}
	if (mCurRoleEqu == RoleEquip::eJiQiang || mCurRoleEqu == RoleEquip::eJiQiang1 || mCurRoleEqu == RoleEquip::eXianDan ||
		mCurRoleEqu == RoleEquip::eXianDan1 || mCurRoleEqu == RoleEquip::ePao || mCurRoleEqu == RoleEquip::ePao1 || mCurRoleEqu == RoleEquip::eGeLin
		|| mCurRoleEqu == RoleEquip::eShouQiang )
	{
		if (curBulletTick > bulletTick)
		{
			curBulletTick = 0;
			
			Hero::getInstance()->stateHandler(RoleAction::kaihuo, 0);
		}
	}
	else if (mCurRoleEqu == RoleEquip::ePengHuoQi1
		|| mCurRoleEqu == RoleEquip::ePengHuoQi2)
	{
		if (curBulletTick > bulletTick)
		{
			curBulletTick = 0;
			Hero::getInstance()->stateHandler(RoleAction::kaihuo, 0);
			Hero::getInstance()->shootBulletSched(curBulletTick);
			
		}
	}
	else if (mCurRoleEqu == RoleEquip::eDao
		|| mCurRoleEqu == RoleEquip::eDao1)
	{
		if (curBulletTick > 0.7)
		{
			curBulletTick = 0;
			Audio::getInstance()->playEffMusic(bulSoundName[mCurRoleEqu - 1].c_str());
			Hero::getInstance()->stateHandler(RoleAction::kaihuo, 0);
			Hero::getInstance()->shootBulletSched(curBulletTick);

		}
	}
}

void Hero::actRelease()
{
	btnTouch = false;
	isFootMoveing = false;
	if (RoleEquip::eJuJi == mCurRoleEqu || RoleEquip::eJuJi1 == mCurRoleEqu)
	{
		if (mCurAimAct != 0)
		{
			//if (mCurAimAct == JuJiAction::kaihuoAim1)
			{
				setAtrAction(false);
				setHeadAction("juji_kaihuo", false);
				setFootAction("kaihuo", false);
				shootBullet();
			}
			/*else if (mCurAimAct == JuJiAction::kaihuoAim2)
			{
				setAtrAction(false);
				setHeadAction("juji_kaihuo", false);
				setFootAction("kaihuo", false);
			}*/
		}
		else
		{
			
		}
		mCurAimAct = 0;
	}
	else
	{
		//stateHandler(RoleAction::stand, 0);
	}
}

void Hero::showAniAction(int id)
{
	
	switch (id)
	{
	case RoleAction::chongci:
	{
		setHeadAction("chongci_" + actEquipName[mCurRoleEqu - 1], false);
		setFootAction("chongci", false);
	}break;
	case RoleAction::die:
	{
		setHeadAction("die_" + actEquipName[mCurRoleEqu - 1], false);
		setFootAction("die", false);
	}break;
	case RoleAction::hurt:
	{
		setHeadAction("hurt_" + actEquipName[mCurRoleEqu - 1], false);
		
		if (GameLayer::getInstance()->mRocker->isTouch())
		{

			//if (!isFootMoveing)
			{
				setFootAction("move", true);
			}
			isFootMoveing = true;

		}
		else
		{
			setFootAction("stand", true);
		}
	}break;
	case RoleAction::kaihuo:
	{
		

		setHeadAction("kaiqiang_" + actEquipName[mCurRoleEqu - 1], false);
		if (GameLayer::getInstance()->mRocker->isTouch())
		{
			
			//if (!isFootMoveing)
			{
				setFootAction("move", true);
			}
			isFootMoveing = true;
			
		}
		else
		{
			setFootAction("kaihuo", false);
		}
		if (mCurRoleEqu != RoleEquip::eJuJi && mCurRoleEqu != RoleEquip::eJuJi1)
		{
			setAtrAction(false);
			shootBullet();
		}
		
		
	}break;
	case RoleAction::kaipao:
	{
		/*setHeadAction("hurt_" + actEquipName[mCurRoleEqu - 1], false);
		setFootAction("hurt", false);*/
	}break;
	case RoleAction::move:
	{
		setHeadAction("move_" + actEquipName[mCurRoleEqu - 1], true);
		
		setFootAction("move", true);
	}break;
	case RoleAction::stand:
	{
		setHeadAction("stand_" + actEquipName[mCurRoleEqu - 1], true);
		setFootAction("stand", true);
	}break;
	case RoleAction::stun:
	{
		setHeadAction("stun_" + actEquipName[mCurRoleEqu - 1], false);
		setFootAction("stun", false);
	}break;
	
	default:
		break;
	}

}

void Hero::stateHandler(int state,float dt)
{
	if (mCurLife < 0)
	{
		return;
	}
	if (state == mCurRoleAct)
	{
		return;
	}
	if (state == RoleAction::stand && (RoleEquip::eJuJi == mCurRoleEqu || RoleEquip::eJuJi1 == mCurRoleEqu))
	{
		if (mCurAimAct != 0)
		{
			return;
		}
	}
	mCurRoleAct = state;
	switch (state)
	{
		case RoleAction::kaihuo:
			{
				
				showAniAction(state);
			}
			break;
		case RoleAction::chongci:
		{
			showAniAction(state);
		}
			break;
		case RoleAction::move:
			{
				showAniAction(state);
			}
				break;
		case RoleAction::stand:
			{
				showAniAction(state);
			}
				break;
		case RoleAction::die:
			{
				showAniAction(state);
			}
				break;
		case RoleAction::stun:
			{
				showAniAction(state);
			}
				break;
		case RoleAction::hurt:
			{
			 showAniAction(state);
			}
				break;
		case RoleAction::kaipao:
			{
			 showAniAction(state);
			}
				break;
		
	default:
		break;
	}
}

void Hero::updateLogic(float dt)
{
	if (mCurLife < 0)
	{
		return;
	}
	if (haveDun)
	{
		dunTime += dt;
		if (dunTime > 10)
		{
			dunTime = 0;
			haveDun = false;
			armatureDun->removeFromParent();
			armatureDun = NULL;
		}
	}

}

void Hero::setAtrAction(bool loop)
{
	string name = actEffName[mCurRoleEqu-1];
	if (name != "")
	{
		armatureAtr->setVisible(true);
		armatureAtr->getAnimation()->play(name, 0, loop);
	}
		
}
void Hero::setHeadAction(string name, bool loop)
{
	armatureHead->getAnimation()->play(name, 0, loop);
}

void Hero::setFootAction(string name, bool loop)
{
	
	armatureFoot->getAnimation()->play(name, 0, loop);
}

Hero::Hero()
{
	mSpeed = SPEEDHERO;
	mCurAimAct = 0;
	mCurRoleAct = 0;
	mCurRoleEqu = 0;
	mCurDir = 1;
	bulletTick = 0.06;
	curBulletTick = 0;
	btnTouch = false;
	haveDun = false;
	bigName = "hero";
	armatureDun = NULL;
	mCurLife = mLife = 3200;
}

Hero::~Hero()
{
	mHero = NULL;
}

void Hero::showDun()
{
	haveDun = true;
	dunTime = 0;
	armatureDun = Armature::create("hero_fh");
	this->addChild(armatureDun, 10);
	armatureDun->getAnimation()->play("hudun", 0, 1);
}

void Hero::destory()
{
	mHero->removeFromParent();
	mHero = NULL;
}

void Hero::reLive()
{
	mCurLife = mLife = 3200;
}


void Hero::fastmove(Vec2 dir, float dt)
{
	if (mCurLife < 0)
	{
		return;
	}
	if (mCurDir == 2)
	{
		armatureHead->setScaleX(-1);
		armatureFoot->setScaleX(-1);
		armatureAtr->setScaleX(-1);
	}
	else
	{
		armatureHead->setScaleX(1);
		armatureFoot->setScaleX(1);
		armatureAtr->setScaleX(1);
	}

}

void Hero::move(Vec2 dir,float dt)
{
	if (mCurLife < 0)
	{
		return;
	}
	if (dir.x < 0)
	{
		armatureHead->setScaleX(-1);
		armatureFoot->setScaleX(-1);
		armatureAtr->setScaleX(-1);
		mCurDir = 2;
	}
	else
	{
		armatureHead->setScaleX(1);
		armatureFoot->setScaleX(1);
		armatureAtr->setScaleX(1);
		mCurDir = 1;
	}
	if (Hero::getInstance()->btnTouch || GameLayer::getInstance()->ackTime < 0.3)
	{
		return;
	}
	if (mCurRoleAct != RoleAction::move)
	{
		stateHandler(RoleAction::move,true);
		return;
	}
	
	
}