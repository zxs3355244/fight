#include "FoxMonster.h"
#include "MonsterAi.h"
#include "Hero.h"
#include "ArmBullet.h"
#include "GameLayer.h"
#include "GameData.h"
FoxMonster::FoxMonster()
{
	mCurId = 0;
	mCurState = 0;
	mName = "";
	bigName = "monster";
	mSpeed = 80;
	mHurt = 0;
	mCurDir = 2;
	mTime = 0;
	mCurLife = 0;
	mLastLife = 0;
	isDie = false;
	mTimeNum = 0;

}

FoxMonster::~FoxMonster()
{

}

FoxMonster* FoxMonster::create(string name, int id, bool isBoss, int wave,bool showEff)
{
	FoxMonster* monster = new FoxMonster();
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

bool FoxMonster::init()
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
	armatureAtr->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(FoxMonster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	armatureOut = Armature::create("chuxian");
	this->addChild(armatureOut, 3);
	armatureHead->getBone("body")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("xiong")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("qianqiantui1")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("qianqiantui2")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("qianqianjiao")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("tou")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("qianer")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("eye")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("ya")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("houer")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("houqiantui1")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("houqiantui2")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("houqianjiao")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("kao")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("qianhoutui1")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("qianhoutui2")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("qianhoutui3")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("qianhoujiao")->changeDisplayWithIndex(mCurId - 1, true);

	//armatureHead->getBone("weiba")->changeDisplayWithIndex(0, true);
	if (mCurId == 1)
	{
		//armatureHead->getBone("weiba")->setLocalZOrder(10);
		armatureHead->getBone("weiba2")->removeFromParent();

		armatureHead->getBone("weiba3")->removeFromParent();
	}
	else if (mCurId == 2)
	{
		armatureHead->getBone("weiba")->removeFromParent();
		armatureHead->getBone("weiba3")->removeFromParent();
	}
	else if (mCurId == 3)
	{
		armatureHead->getBone("weiba")->removeFromParent();
		armatureHead->getBone("weiba2")->removeFromParent();
	}
	armatureHead->getBone("houhoutui1")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("houhoutui2")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("houhoujiao")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("Layer5")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("Layer4")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("Layer1")->changeDisplayWithIndex(mCurId - 1, true);

	armatureHead->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(FoxMonster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	armatureHead->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(FoxMonster::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

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
		armatureOut->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(FoxMonster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}
	return true;
}

void FoxMonster::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
	if (evt == "jump_start")
	{
		ccBezierConfig con;
		con.controlPoint_1 = this->getPosition();

		con.endPosition = this->targetPos;
		if (this->mCurDir == 1)
		{
			con.controlPoint_2 = Vec2(this->getPositionX() + abs(this->targetPos.x - this->getPositionX()), this->getPositionY() + 100);
		}
		else
		{
			con.controlPoint_2 = Vec2(this->getPositionX() - abs(this->targetPos.x - this->getPositionX()), this->getPositionY() + 100);
		}


		this->runAction(Sequence::create(CCBezierTo::create(1.0f, con), CallFunc::create([this](){

			Hero* hero = Hero::getInstance();
			Vec2 heropos = hero->getPosition();
			if ((heropos - this->getPosition()).length() < 10)
			{
				this->stateHandler(MonsterState::uAttack1, true);
				this->mMoveTime = 0;
				this->mAiState = aAttacking;
			}
			else
			{
				this->mAiState = aStand;
				this->mMoveTime = 0;
				this->stateHandler(MonsterState::uStand, true);
			}
		}), nullptr));

	}
	else if (evt == "fox_attack_atk")
	{
		heroHurt();
	}
}

void FoxMonster::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
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
		else if (movementID == "attack2")//Ìø¹¥»÷
		{
			ActionFinish();
		}
		else if (movementID == "attack3")//ÈÓ¸«×Ó¹¥»÷
		{
			ActionFinish();
		}
		else if (movementID == "back")
		{
			ActionFinish();
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

void FoxMonster::heroHurt()
{
	Vec2 pos = this->getPosition();
	Vec2 heroPos = Hero::getInstance()->getPosition();
	Rect rect = this->armatureHead->getBoundingBox();
	if (this->mCurDir == 1)
	{
		rect.origin.x = pos.x;
		rect.origin.y = pos.y;
		rect.size.width = rect.size.width * 2 / 5;
		rect.size.height = rect.size.height * 3 / 5;
	}
	else
	{
		rect.origin.x = pos.x;
		rect.origin.y = pos.y;
		rect.size.width = rect.size.width * 2 / 5;
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

void FoxMonster::ActionFinish()
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
	//   this->mAiState = aAttackEnd;

	}
		break;
	case MonsterState::uAttack1:
	{
		//¹¥»÷Íê³É
	//   this->mAiState = aAttackEnd;

	}
		break;
	case MonsterState::uBack:
	{
		//¹¥»÷Íê³É
		this->mAiState = aStand;

	}
		break;
	case MonsterState::uDie:
	{
		//ËÀÍö
		this->mAiState = aDieEnd;
		isDie = true;
	}
		break;
	case MonsterState::uDie2:
	{
		this->mAiState = aDieEnd;
		isDie = true;
		//ËÀÍö
	}
		break;
	case MonsterState::uFly:
	{

	}
		break;
	case MonsterState::uHurt:
	{

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

void FoxMonster::handlerDir()
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

void FoxMonster::setAction(string name, bool loop)
{
	armatureHead->getAnimation()->play(name, 0, loop);
}


void FoxMonster::showHitNum()
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

void FoxMonster::daoZhaoEnd()
{
	if (mCurLife < 0)
	{
		return;
	}

	mLastLife = mCurLife;
	mCurLife -= 1200;

	showHitNum();

	if (mCurLife <= 0 && !isDie)
	{
		mCurLife = -1;
		//isDie = true;
		showBloodBar();

		stateHandler(MonsterState::uFly, 1);
		Vec2 pos = this->getPosition();
		Vec2 pos1;
		ccBezierConfig con;
		con.controlPoint_1 = pos;

		if (Hero::getInstance()->mCurDir == 1)
		{
			pos.x += 100;
			pos1.x = (pos.x + 140);
		}
		else
		{
			pos.x -= 100;
			pos1.x = (pos.x - 140);
		}
		pos.y += 200;

		pos1.y = (pos.y - 200);
		con.controlPoint_2 = pos;
		con.endPosition = pos1;
		this->runAction(Sequence::create(CCBezierTo::create(1.0f, con), CallFunc::create([=]{
			char buf[50];
			for (size_t i = 0; i < 6; i++)
			{
				Armature* armatureDie = Armature::create("xin_texiao");
				this->addChild(armatureDie, 4);

				armatureDie->getAnimation()->play("Animation0", 0, false);
				armatureDie->setPosition(Vec2(random(-50, 50), random(-50, 50)));
				armatureDie->runAction(Sequence::create(MoveBy::create(1.0f, Vec2(random(-200, 200), 0)), nullptr));
			}
			stateHandler(MonsterState::uDie2,false);
		}), nullptr));
	}
	else if (!isDie)
	{
		showBloodBar();
		this->mAiState = aHurt;
		stateHandler(MonsterState::uHurt, false);
	}
}
void FoxMonster::BulletHit(Uint* uint)
{
	if (Hero::getInstance()->mCurRoleEqu == RoleEquip::eDao ||
		Hero::getInstance()->mCurRoleEqu == RoleEquip::eDao1 ||
		Hero::getInstance()->mCurRoleEqu == RoleEquip::eXianDan ||
		Hero::getInstance()->mCurRoleEqu == RoleEquip::eXianDan1)
	{
		if (mCurLife < 0)
		{
			mCurLife = -1;
			mLastLife = 0;
			return;
		}
		mLastLife = mCurLife;
		mCurLife -= Hero::getInstance()->mHurt;
		int rand = random(1, 4);
		if (rand == 1)
		{
			showHitNum();
		}

		if (mCurLife <= 0 && !isDie)
		{
			mCurLife = -1;
			//isDie = true;
			showBloodBar();

			stateHandler(MonsterState::uDie, false);
			char buf[50];
			for (size_t i = 0; i < 6; i++)
			{
				Armature* armatureDie = Armature::create("xin_texiao");
				this->addChild(armatureDie, 4);

				armatureDie->getAnimation()->play("Animation0", 0, false);
				armatureDie->setPosition(Vec2(random(-50, 50), random(-50, 50)));
				armatureDie->runAction(Sequence::create(MoveBy::create(1.0f, Vec2(random(-200, 200), 0)), nullptr));
			}
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
		if (mCurLife < 0)
		{
			mCurLife = -1;
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
		if (mCurLife <= 0 && !isDie)
		{
			mCurLife = -1;
			//isDie = true;
			showBloodBar();
			if (Hero::getInstance()->mCurRoleEqu == RoleEquip::eXianDan1 ||
				Hero::getInstance()->mCurRoleEqu == RoleEquip::ePao ||
				Hero::getInstance()->mCurRoleEqu == RoleEquip::ePao1 ||
				Hero::getInstance()->mCurRoleEqu == RoleEquip::eXianDan)
			{
				stateHandler(MonsterState::uFly, 1);
				Vec2 pos = this->getPosition();
				Vec2 pos1;
				ccBezierConfig con;
				con.controlPoint_1 = pos;

				if (Hero::getInstance()->mCurDir == 1)
				{
					pos.x += 100;
					pos1.x = (pos.x + 140);
				}
				else
				{
					pos.x -= 100;
					pos1.x = (pos.x - 140);
				}
				pos.y += 200;

				pos1.y = (pos.y - 200);
				con.controlPoint_2 = pos;
				con.endPosition = pos1;
				this->runAction(Sequence::create(CCBezierTo::create(1.0f, con), CallFunc::create([=]{
					char buf[50];
					for (size_t i = 0; i < 6; i++)
					{
						Armature* armatureDie = Armature::create("xin_texiao");
						this->addChild(armatureDie, 4);

						armatureDie->getAnimation()->play("Animation0", 0, false);
						armatureDie->setPosition(Vec2(random(-50, 50), random(-50, 50)));
						armatureDie->runAction(Sequence::create(MoveBy::create(1.0f, Vec2(random(-200, 200), 0)), nullptr));
					}
					stateHandler(MonsterState::uDie2, false);
				}), nullptr));
			}
			else
			{
				stateHandler(MonsterState::uDie, false);
				char buf[50];
				for (size_t i = 0; i < 6; i++)
				{
					Armature* armatureDie = Armature::create("xin_texiao");
					this->addChild(armatureDie, 4);

					armatureDie->getAnimation()->play("Animation0", 0, false);
					armatureDie->setPosition(Vec2(random(-50, 50), random(-50, 50)));
					armatureDie->runAction(Sequence::create(MoveBy::create(1.0f, Vec2(random(-200, 200), 0)), nullptr));
				}
			}
		}
		else if (!isDie)
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

void FoxMonster::stateHandler(int state, bool loop)
{
	if (mCurState == state)
	{
		return;
	}
	mCurState = state;
	switch (mCurState)
	{
	case MonsterState::uAttack:
	{
		handlerDir();
		setAction("attack", loop);
	}
		break;
	case MonsterState::uAttack2:
	{
		handlerDir();
		setAction("jump", loop);
		
	}
		break;
	case MonsterState::uAttack1:
	{
		handlerDir();
		setAction("jumpattack", loop);
	}
		break;
	case MonsterState::uBack:
	{
		setAction("back", loop);
	}
		break;
		
	case MonsterState::uDie:
	{
		setAction("die", loop);
	}
		break;
	case MonsterState::uDie2:
	{
		setAction("die2", loop);
	}
		break;
	case MonsterState::uFly:
	{
		setAction("fly", loop);
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
		setAction("stun", loop);
	}
		break;

	default:
		break;
	}
}

void FoxMonster::showBloodBar()
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


void FoxMonster::updateLogic(float dt)
{
	if (isDie || mCurLife < 0)
	{
		return;
	}
	mTime += dt;
	mTimeNum += dt;
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
void FoxMonster::move(Vec2 dir, float dt)
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

void FoxMonster::setProper(MonsterOneData* data)
{
	mSpeed = data->speed;
	mHurt = data->atk;
	mLife = data->life;
	mCurLife = mLastLife = mLife;
}

