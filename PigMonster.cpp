#include "PigMonster.h"
#include "MonsterAi.h"
#include "Hero.h"
#include "ArmBullet.h"
#include "GameLayer.h"
#include "GameData.h"
PigMonster::PigMonster()
{
	mCurId = 0;
	mCurState = 0;
	mName = "";
	bigName = "monster";
	mSpeed = 80;
	mHurt = 0;
	isChange = false;
	mCurDir = 2;
	mTime = 0;
	mCurLife = 0;
	mLastLife = 0;
	isDie = false;
	mTimeNum = 0;

}

PigMonster::~PigMonster()
{

}

PigMonster* PigMonster::create(string name, int id, bool isBoss, int wave, bool showEff)
{
	PigMonster* monster = new PigMonster();
	monster->retain();
	monster->autorelease();
	monster->mName = name;
	monster->mCurId = id;
	monster->mIsBoss = isBoss;
	monster->mWave = wave;
	monster->showEff = showEff;
	if (monster && monster->init())
	{
		return monster;
	}

	return NULL;
}

bool PigMonster::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	armatureHead = Armature::create(mName);
	this->addChild(armatureHead, 2);

	armatureAtr = Armature::create("zidantexiao");
	this->addChild(armatureAtr, 3);
	armatureAtr->setVisible(false);
	armatureAtr->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(PigMonster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	armatureOut = Armature::create("chuxian");
	this->addChild(armatureOut, 3);
	armatureHead->getBone("body")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("rbody")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("rzuoshoushang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("rzuoshouxia")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("rtou")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("rzui")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("ryoushoushang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("ryoushouxia")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("wuqi")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("zuohoushang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("zuohouxia")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("zuoqianshang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("tou")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("zuoer")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("bizi")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("youer")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("pigu")->changeDisplayWithIndex(mCurId - 1, true);

	armatureHead->getBone("weiba")->changeDisplayWithIndex(mCurId - 1, true);

	armatureHead->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(PigMonster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	armatureHead->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(PigMonster::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

	mBar = Node::create();
	this->addChild(mBar);
	mBar->setVisible(false);
	mBarBg = Sprite::create("monstr_btm.png");
	mBar->addChild(mBarBg);
	mBar->setPosition(Vec2(0, -10));
	mBloodBar1 = ProgressTimer::create(Sprite::create("monstr_bar2.png"));
	mBloodBar1->setType(ProgressTimer::Type::BAR);
	mBloodBar2 = ProgressTimer::create(Sprite::create("monstr_bar.png"));
	mBloodBar2->setType(ProgressTimer::Type::BAR);
	mBloodBar2->setMidpoint(Vec2(0, 1));
	mBloodBar1->setMidpoint(Vec2(0, 1));
	mBloodBar2->setBarChangeRate(Vec2(1, 0));
	mBloodBar1->setBarChangeRate(Vec2(1, 0));
	mBar->addChild(mBloodBar1);
	mBar->addChild(mBloodBar2);
	mBloodBar1->setPercentage(100);
	mBloodBar2->setPercentage(100);
	this->setScale(1.2);
	if (mIsBoss)
	{
		this->setScale(1.5);
	}

	if (mCurDir == 2)
	{

		armatureHead->setScaleX(1);
	}
	else
	{
		armatureHead->setScaleX(-1);
	}
	if (showEff)
	{
		armatureOut->getAnimation()->play("effects_chuxian_top", 0, false);
		armatureOut->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(PigMonster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}
	


	return true;
}

void PigMonster::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
	if (evt == "fly_arm")
	{
		ArmBullet* bullet = ArmBullet::create(ArmBulletType::mFuZi);
		bullet->setDir(this->mCurDir);

		GameLayer::getInstance()->ObjVec.push_back(bullet);
		GameLayer::getInstance()->mGameLayer->addChild(bullet);
		bullet->setPosition(Vec2(this->getPosition().x + (this->mCurDir == 1 ? 150 : -150), this->getPosition().y + 30));

	}
	else if (evt == "frame_atk" || evt == "frame_atk_1")
	{

		heroHurt();
	}
	//float p = bone->getDisplayRenderNode()->getBoundingBox().size.width;
	//CCLOG("%f", armatureHead->getBoundingBox().size.width);

}

void PigMonster::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
	{
		if (movementID == "attack")
		{
			ActionFinish();
		}
		else if (movementID == "move")
		{
			ActionFinish();
		}
		else if (movementID == "hurt")
		{
			ActionFinish();
		}
		else if (movementID == "stun")
		{
			ActionFinish();
		}
		else if (movementID == "stand")
		{
			ActionFinish();
		}
		else if (movementID == "die")
		{
			isDie = true;
			ActionFinish();
		}
		else if (movementID == "attack_pre")//¹¥»÷Ç°×à
		{
			//setAction("attack", 1);
		}
		else if (movementID == "fly")
		{
			setAction("liedown", 0);

		}
		else if (movementID == "liedown")
		{

			stateHandler(MonsterState::uDie2, 0);
		}
		else if (movementID == "die2")
		{
			isDie = true;
			ActionFinish();
		}
		if (movementID.find("tx") == movementID.length() - 2)
		{
			txOver = false;
			armatureAtr->setVisible(false);
		}
	}
}

void PigMonster::heroHurt()
{
	Vec2 pos = this->getPosition();
	Vec2 heroPos = Hero::getInstance()->getPosition();
	
	Rect rect = this->armatureHead->getBoundingBox();
	if (this->mCurDir == 1)
	{
		rect.origin.x = pos.x;
		rect.origin.y = pos.y;
		rect.size.width = rect.size.width;
		rect.size.height = rect.size.height * 3 / 5;
	}
	else
	{
		rect.origin.x = pos.x;
		rect.origin.y = pos.y;
		rect.size.width = rect.size.width;
		rect.size.height = rect.size.height * 3 / 5;
		rect.origin.x = pos.x - rect.size.width;
	}
	Rect recthero;
	recthero.origin.x = heroPos.x;
	recthero.origin.y = heroPos.y;
	recthero.size.width = 84;
	recthero.size.height = 84;
	if (rect.intersectsRect(recthero))
	{
		//Ö÷½ÇÊÜÉË
		Hero::getInstance()->BulletHit(this);
	}
}

void PigMonster::ActionFinish()
{
	switch (mCurState)
	{
	case MonsterState::uAttack:
	{
								  //¹¥»÷Íê³É
								  this->mAiState = aAttackEnd;
	}
		break;
	case MonsterState::uAttack2:
	{
								   //¹¥»÷Íê³É//ÈÓ¸«×Ó
								  // this->mAiState = aAttackEnd;

	}
		break;
	case MonsterState::uAttack1:
	{
								   //¹¥»÷Íê³É
								   this->mAiState = aAttackEnd;

	}
		break;
	case MonsterState::uDie:
	{
		//ËÀÍö
		isDie = true;
		Monster* monster = Monster::create("goblin", this->mCurId, mIsBoss, 1,false);
		GameManager::getInstance()->monsterVec.push_back(monster);
		GameLayer::getInstance()->ObjVec.push_back(monster);
		GameLayer::getInstance()->mGameLayer->addChild(monster);
		monster->setPosition(this->getPosition());
		monster->setAction("stand", true);
		
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
		monster->setProper(CvsFile::getInstance()->getMonsterData(ids, "goblin", false));
	}
		break;
	case MonsterState::uDie2:
	{
		/*isDie = true;
		Monster* monster = Monster::create("goblin", this->mCurId, mIsBoss, 1,false);
		GameManager::getInstance()->monsterVec.push_back(monster);
		GameLayer::getInstance()->ObjVec.push_back(monster);
		GameLayer::getInstance()->mGameLayer->addChild(monster);
		monster->setPosition(this->getPosition());
		monster->setAction("stand", true);		*/				//ËÀÍö
	}
		break;
	case MonsterState::uFly:
	{

	}
		break;
	case MonsterState::uHurt:
	{
								//ËÀÍö
		stateHandler(MonsterState::uStand, true);
		this->mAiState = aStand;

	}
		break;
	case MonsterState::uMove:
	{
								//ÒÆ¶¯
	}
		break;
	case MonsterState::uStand:
	{
								 //Õ¾Á¢
	}
		break;
	case MonsterState::uStun:
	{
								//Ñ£ÔÎ
	}
		break;
	default:
		break;
	}
	mCurState = 0;

}

void PigMonster::handlerDir()
{
	if (abs(Hero::getInstance()->getPosition().x - this->getPosition().x) < 40)
	{

	}
	if (Hero::getInstance()->getPosition().x - this->getPosition().x < -40)
	{
		if (mCurDir != 2)
		{
			mCurDir = 2;
			armatureHead->setScaleX(1);
		}
	}
	else
	{
		if (mCurDir != 1)
		{
			mCurDir = 1;
			armatureHead->setScaleX(-1);
		}
	}
}

void PigMonster::setAction(string name, bool loop)
{
	armatureHead->getAnimation()->play(name, 0, loop);
}


void PigMonster::showHitNum()
{
	if (mTimeNum < 1)
	{
		return;
	}
	mTimeNum = 0;
	int num = random(600, 1000 + GameData::getInstance()->getCurMapId() * 100);
	Label* label = Label::createWithCharMap("num/num_damage.png", 33, 45, 48);
	this->addChild(label, 10);
	char buf[50];
	sprintf(buf, "%d", num);
	label->setString(buf);
	label->setPositionY(80);
	label->setPositionX(random(-70, 70));
	label->setScale(0.8);
	label->runAction(Sequence::create(EaseBackOut::create(ScaleTo::create(0.2, 1.1)), MoveBy::create(0.5, Vec2(0, 300)), RemoveSelf::create(), nullptr));
	label->runAction(Sequence::create(DelayTime::create(0.2), FadeOut::create(0.5), nullptr));
}

void PigMonster::daoZhaoEnd()
{
	if (mCurLife == mLife / 2 && isChange)
	{
		mLastLife = mLife / 2;
		return;
	}
	mLastLife = mCurLife;
	mCurLife -= 1200;

	showHitNum();


	if (mCurLife <= mLife / 2 && !isDie)
	{
		mCurLife = mLife / 2;
		isChange = true;
		showBloodBar();

		stateHandler(MonsterState::uDie, false);
		//char buf[50];

	}
	else if (!isDie)
	{
		showBloodBar();
		this->mAiState = aHurt;
		showHitNum();
		stateHandler(MonsterState::uHurt, false);
	}
}

void PigMonster::BulletHit(Uint* uint)
{
	if (Hero::getInstance()->mCurRoleEqu == RoleEquip::eDao ||
		Hero::getInstance()->mCurRoleEqu == RoleEquip::eDao1 ||
		Hero::getInstance()->mCurRoleEqu == RoleEquip::eXianDan ||
		Hero::getInstance()->mCurRoleEqu == RoleEquip::eXianDan1)
	{
		if (mCurLife == mLife / 2 && isChange)
		{
			mLastLife = mLife / 2;
			return;
		}
		mLastLife = mCurLife;
		mCurLife -= Hero::getInstance()->mHurt;
		int rand = random(1, 4);
		if (rand == 1)
		{
			showHitNum();
		}

		if (mCurLife <= mLife/2 && !isDie)
		{
			mCurLife = mLife / 2;
			isChange = true;
			showBloodBar();

			stateHandler(MonsterState::uDie, false);

		}
		else if (!isDie)
		{
			showBloodBar();
			showHitNum();
			int rand = random(0, 4);
			if (rand == 4)
			{
				this->mAiState = aHurt;
				stateHandler(MonsterState::uHurt, false);
			}
		}

		return;
	}
	Bullet* bl = dynamic_cast<Bullet*> (uint);
	string name = "";
	switch (bl->mCurId)
	{
	case eJiQiang:
	case eJiQiang1:
	case eShouQiang:
	case eJuJi:
	case eJuJi1:
	case ePao:
	case ePao1:
	case eGeLin:
	case ePengHuoQi1:
	case ePengHuoQi2:
	{
		if (mCurLife == mLife / 2 && isChange)
		{
			break;
		}
		name = bulEffName[bl->mCurId - 1];
		mLastLife = mCurLife;
		mCurLife -= bl->mHurt;
		int rand = random(1, 4);
		if (rand == 1)
		{
			showHitNum();
		}
		if (mCurLife <= mLife / 2 && !isDie)
		{
			isChange = true;
			mCurLife = mLife / 2;
			//isDie = true;
			showBloodBar();
							
			stateHandler(MonsterState::uDie, false);

		}
		else if (!isDie && !isChange)
		{
			if (name != ""&& txOver == false)
			{
				txOver = true;
				armatureAtr->setVisible(true);
				armatureAtr->setPositionY(30);
				armatureAtr->getAnimation()->play(name, 0, false);
			}
			showBloodBar();
			
			int rand = random(0, 4);
			if (rand == 4)
			{
				this->mAiState = aHurt;
				stateHandler(MonsterState::uHurt, false);
			}
			
		}
	}
		break;
	default:
		break;
	}
}

void PigMonster::stateHandler(int state, bool loop)
{
	if (mCurState == state || mCurState == MonsterState::uDie)
	{
		return;
	}
	mCurState = state;
	switch (mCurState)
	{
	case MonsterState::uAttack:
	{
		handlerDir();

		setAction("attack", true);
	}
		break;
	case MonsterState::uAttack2:
	{
		handlerDir();
		setAction("attack_pre", false);

	}
		break;
	case MonsterState::uAttack1:
	{
		handlerDir();
		setAction("attack2", loop);
	}
		break;
	case MonsterState::uDie:
	{
							   setAction("die", loop);
	}
		break;
	case MonsterState::uDie2:
	{
		//						setAction("die2", loop);
	}
		break;
	case MonsterState::uFly:
	{
		//					   setAction("fly", loop);
	}
		break;
	case MonsterState::uHurt:
	{

								setAction("hurt", loop);
								//mBar->setVisible(true);
	}
		break;
	case MonsterState::uMove:
	{
		setAction("move", loop);
	}
		break;
	case MonsterState::uStand:
	{
		setAction("stand", loop);
	}
		break;
	case MonsterState::uStun:
	{
		//						setAction("stun", loop);
	}
		break;

	default:
		break;
	}
}

void PigMonster::showBloodBar()
{
	if (mIsBoss)
	{
		GameLayer::getInstance()->updateBossHp(100 * mCurLife / mLife);
		return;
	}
	mBar->setVisible(true);
	mTime = 0;
	mBloodBar2->setPercentage(100 * mCurLife / mLife);
	mBloodBar1->setPercentage(100 * mLastLife / mLife);

}


void PigMonster::updateLogic(float dt)
{
	if (isDie || mCurLife < 0)
	{
		return;
	}
	mTime += dt;
	mTimeNum += dt;
	Vec2 pos = this->getPosition();
	Vec2 heroPos = Hero::getInstance()->getPosition();
	if (this->mCurState == MonsterState::uAttack)
	{
		if (abs(heroPos.x - pos.x) < 10 && abs(heroPos.y - pos.y) < 20)
		{
			Hero::getInstance()->BulletHit(this);
		}
		
	}
	if (mTime > 5)
	{
		mBar->setVisible(false);
	}
	if (mBar->isVisible())
	{
		if (mBloodBar1->getPercentage() <= mBloodBar2->getPercentage())
		{
			mBloodBar1->setPercentage(mBloodBar2->getPercentage());
			return;
		}
		mBloodBar1->setPercentage(mBloodBar1->getPercentage() - 2);
	}
}
void PigMonster::move(Vec2 dir, float dt)
{
	if (dir.x < 0)
	{
		if (mCurDir != 2)
		{
			mCurDir = 2;
			armatureHead->setScaleX(1);
		}
	}
	else
	{
		if (mCurDir != 1)
		{
			mCurDir = 1;
			armatureHead->setScaleX(-1);
		}
	}

	if (mCurState != MonsterState::uMove)
	{
		stateHandler(MonsterState::uMove, 1);
	}
	Vec2 pos = this->getPosition();
	float offsetx = mSpeed*dt*cos(dir.getAngle());
	float offsety = mSpeed*dt*sin(dir.getAngle());

	pos.x += offsetx;

	pos.y += offsety;

	this->setPosition(pos);

}

void PigMonster::setProper(MonsterOneData* data)
{
	mSpeed = data->speed;
	mHurt = data->atk;
	mLife = data->life;
	mCurLife = mLastLife = mLife;
}

void PigMonster::moveAttack(Vec2 dir, float dt)
{
	if (dir.x < 0)
	{
		if (mCurDir != 2)
		{
			mCurDir = 2;
			armatureHead->setScaleX(1);
		}
	}
	else
	{
		if (mCurDir != 1)
		{
			mCurDir = 1;
			armatureHead->setScaleX(-1);
		}
	}

	if (mCurState != MonsterState::uMove)
	{
		stateHandler(MonsterState::uAttack, 1);
	}
	Vec2 pos = this->getPosition();
	pos.x += mSpeed*dt*cos(dir.getAngle());

	pos.y += mSpeed*dt*sin(dir.getAngle());

	this->setPosition(pos);
}
