#include "BeeMonster.h"
#include "MonsterAi.h"
#include "Hero.h"
#include "ArmBullet.h"
#include "GameLayer.h"
#include "GameData.h"
BeeMonster::BeeMonster()
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

BeeMonster::~BeeMonster()
{

}

BeeMonster* BeeMonster::create(string name, int id, bool isBoss, int wave,bool showEff)
{
	BeeMonster* monster = new BeeMonster();
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

bool BeeMonster::init()
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
	armatureAtr->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BeeMonster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	armatureOut = Armature::create("chuxian");
	this->addChild(armatureOut, 3);
	armatureHead->getBone("fashe")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("jiguang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("ci")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("body")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("zheng")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("xiong")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("waizhi1shang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("waizhi2shang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("waizhi3shang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("tou")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("yan")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("waichujiaoxia")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("lichujiaoxia")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("lizhi3shang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("lizhi2shang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("lizhi1shang")->changeDisplayWithIndex(mCurId - 1, true);
	//armatureHead->getBone("wingwai")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("wingwaishang")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("wingwaixia")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("wingneixia")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("wingneishang")->changeDisplayWithIndex(mCurId - 1, true);


	armatureHead->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BeeMonster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	armatureHead->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BeeMonster::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

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
		armatureOut->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BeeMonster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	}
	

	return true;
}

void BeeMonster::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
	if (evt == "atk2_frame")
	{
		ArmBullet* bullet = ArmBullet::create(ArmBulletType::mBee);
		bullet->setDir(this->mCurDir);

		GameLayer::getInstance()->ObjVec.push_back(bullet);
		GameLayer::getInstance()->mGameLayer->addChild(bullet);
		bullet->setPosition(Vec2(this->getPosition().x + (this->mCurDir == 1 ? 30 : -30), this->getPosition().y + 10));
		if (this->mCurDir == 1)
		{
			bullet->setAngel(180);
		}
		else
		{
			bullet->setAngel(0);
		}
		
		ArmBullet* bullet1 = ArmBullet::create(ArmBulletType::mBee);
		bullet1->setDir(this->mCurDir);
		
		GameLayer::getInstance()->ObjVec.push_back(bullet1);
		GameLayer::getInstance()->mGameLayer->addChild(bullet1);
		bullet1->setPosition(Vec2(this->getPosition().x + (this->mCurDir == 1 ? 30 : -30), this->getPosition().y + 10));
		if (this->mCurDir == 1)
		{
			bullet1->setAngel(135);
		}
		else
		{
			bullet1->setAngel(45);
		}
		 
		ArmBullet* bullet2 = ArmBullet::create(ArmBulletType::mBee);
		bullet2->setDir(this->mCurDir);
		GameLayer::getInstance()->ObjVec.push_back(bullet2);
		GameLayer::getInstance()->mGameLayer->addChild(bullet2);
		bullet2->setPosition(Vec2(this->getPosition().x + (this->mCurDir == 1 ? 30 : -30), this->getPosition().y + 10));
		if (this->mCurDir == 1)
		{
			bullet2->setAngel(225);
		}
		else
		{
			bullet2->setAngel(-45);
		}
	}
	else if (evt == "frame_atk")
	{

		heroHurt();
	}
	//float p = bone->getDisplayRenderNode()->getBoundingBox().size.width;
	//CCLOG("%f", armatureHead->getBoundingBox().size.width);

}

void BeeMonster::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
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
		else if (movementID == "attack2")//¹¥»÷
		{
			ActionFinish();
		}
		else if (movementID == "attack3")//ÈÓ¸«×Ó¹¥»÷
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

void BeeMonster::heroHurt()
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

void BeeMonster::ActionFinish()
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
								   this->mAiState = aAttackEnd;

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

void BeeMonster::handlerDir()
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

void BeeMonster::setAction(string name, bool loop)
{
	armatureHead->getAnimation()->play(name, 0, loop);
}


void BeeMonster::showHitNum()
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

void BeeMonster::daoZhaoEnd()
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
			stateHandler(MonsterState::uDie2, false);
		}), nullptr));
	}
	else if (!isDie)
	{
		showBloodBar();
		this->mAiState = aHurt;
		stateHandler(MonsterState::uHurt, false);
	}
}

void BeeMonster::BulletHit(Uint* uint)
{
	if (Hero::getInstance()->mCurRoleEqu == RoleEquip::eDao ||
		Hero::getInstance()->mCurRoleEqu == RoleEquip::eDao1 ||
		Hero::getInstance()->mCurRoleEqu == RoleEquip::eXianDan ||
		Hero::getInstance()->mCurRoleEqu == RoleEquip::eXianDan1)
	{
		if (mCurLife < 0)
		{
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

void BeeMonster::stateHandler(int state, bool loop)
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
		/*handlerDir();
		setAction("attack3", loop);*/

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

void BeeMonster::showBloodBar()
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


void BeeMonster::updateLogic(float dt)
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
void BeeMonster::move(Vec2 dir, float dt)
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

void BeeMonster::setProper(MonsterOneData* data)
{
	mSpeed = data->speed;
	mHurt = data->atk;
	mLife = data->life;
	mCurLife = mLastLife = mLife;
}
