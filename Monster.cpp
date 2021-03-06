#include "Monster.h"
#include "MonsterAi.h"
#include "Hero.h"
#include "ArmBullet.h"
#include "GameLayer.h"
#include "GameData.h"
Monster::Monster()
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

Monster::~Monster()
{

}

Monster* Monster::create(string name, int id, bool isBoss, int wave, bool showEff)
{
	Monster* monster = new Monster();
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

bool Monster::init()
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
	armatureAtr->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Monster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	
	armatureOut = Armature::create("chuxian");
	this->addChild(armatureOut, 3);
	armatureHead->getBone("body")->changeDisplayWithIndex(mCurId-1, true);
	armatureHead->getBone("arm_l")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("hand_l")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("head")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("mouth")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("arm_r")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("hand_r")->changeDisplayWithIndex(mCurId - 1, true);
	armatureHead->getBone("weapon")->changeDisplayWithIndex(mCurId - 1, true);
	

	armatureHead->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Monster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	armatureHead->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Monster::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	
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
		armatureOut->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Monster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}
	
	return true;
}

void Monster::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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

}

void Monster::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
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
		else if (movementID == "attack2")//������
		{
			ActionFinish();
		}
		else if (movementID == "attack3")//�Ӹ��ӹ���
		{
			ActionFinish();
		}
		else if (movementID == "fly")
		{
			setAction("liedown",0);

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
		
		if (movementID.find("tx") == movementID.length()-2)
		{
			txOver = false;
			armatureAtr->setVisible(false);
		}
	}
}

void Monster::heroHurt()
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
		//��������
		Hero::getInstance()->BulletHit(this);
	}
}

void Monster::ActionFinish()
{
	switch (mCurState)
	{
	case MonsterState::uAttack:
	{
		//�������
		this->mAiState = aAttackEnd;
	}
		break;
	case MonsterState::uAttack2:
	{
		//�������//�Ӹ���
		this->mAiState = aAttackEnd;
	
	}
		break;
	case MonsterState::uAttack1:
	{
		//�������
		this->mAiState = aAttackEnd;
	
	}
		break;
	case MonsterState::uDie:
	{
		//����
		this->mAiState = aDieEnd;
		isDie = true;
	}
		break;
	case MonsterState::uDie2:
	{
		this->mAiState = aDieEnd;
		isDie = true;
		//����
	}
		break;
	case MonsterState::uFly:
	{
						
	}
		break;
	case MonsterState::uHurt:
	{
		//����

		stateHandler(MonsterState::uStand, true);
		this->mAiState = aStand;
	}
		break;
	case MonsterState::uMove:
	{
		//�ƶ�
	}
		break;
	case MonsterState::uStand:
	{
		//վ��
	}
		break;
	case MonsterState::uStun:
	{
		//ѣ��
	}
		break;
	default:
		break;
	}
	mCurState = 0;

}

void Monster::handlerDir()
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

void Monster::setAction(string name, bool loop)
{
	armatureHead->getAnimation()->play(name, 0, loop);
}


void Monster::showHitNum()
{
	if (mTimeNum < 1)
	{
		return;
	}
	mTimeNum = 0;
	int num = random(600, 1000 +GameData::getInstance()->getCurMapId()*100);
	Label* label = Label::createWithCharMap("num/num_damage.png", 33, 45, 48);
	this->addChild(label, 10);
	char buf[50];
	sprintf(buf, "%d", num);
	label->setString(buf);
	label->setPositionY(80); 
	label->setPositionX(random(-70,70));
	label->setScale(0.8);
	label->runAction(Sequence::create(EaseBackOut::create( ScaleTo::create(0.2, 1.1)),MoveBy::create(0.5,Vec2(0,300)),RemoveSelf::create() ,nullptr));
	label->runAction(Sequence::create(DelayTime::create(0.2), FadeOut::create(0.5),nullptr));
}

void Monster::daoZhaoEnd()
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
			for (size_t i = 0; i < 6; i++)
			{
				Armature* armatureDie = Armature::create("xin_texiao");
				this->addChild(armatureDie, 4);

				armatureDie->getAnimation()->play("Animation0", 0, false);
				armatureDie->setPosition(Vec2(random(-50, 50), random(-50, 50)));
				armatureDie->runAction(Sequence::create(MoveBy::create(1.0f, Vec2(random(-200, 200), 0)), nullptr));
			}
			setAction("liedown", 0);
		}), nullptr));
	}
	else if (!isDie)
	{
		showBloodBar();
		
		if (!mIsBoss)
		{
			this->mAiState = aHurt;
			stateHandler(MonsterState::uHurt, false);
		}
		
	}
}

void Monster::BulletHit(Uint* uint)
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
			name = bulEffName[bl->mCurId-1];
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
						
						for (size_t i = 0; i < 6; i++)
						{
							Armature* armatureDie = Armature::create("xin_texiao");
							this->addChild(armatureDie, 4);

							armatureDie->getAnimation()->play("Animation0", 0, false);
							armatureDie->setPosition(Vec2(random(-50, 50), random(-50, 50)));
							armatureDie->runAction(Sequence::create(MoveBy::create(1.0f, Vec2(random(-200, 200), 0)), nullptr));
						}
						setAction("liedown", 0);
					}), nullptr));
				}
				else
				{
					stateHandler(MonsterState::uDie, false);
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
				if (name != "" && txOver == false)
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

void Monster::stateHandler(int state, bool loop)
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
			setAction("attack3", loop);
									 
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

void Monster::showBloodBar()
{
	if (mIsBoss)
	{
		GameLayer::getInstance()->updateBossHp(100 * mCurLife / mLife);
		return;
	}
	mBar->setVisible(true);
	mTime = 0;
	mBloodBar2->setPercentage(100 * mCurLife/mLife);
	mBloodBar1->setPercentage(100 * mLastLife / mLife);

}


void Monster::updateLogic(float dt)
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
		mBloodBar1->setPercentage(mBloodBar1->getPercentage()-2);
	}
}
void Monster::move(Vec2 dir, float dt)
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

void Monster::setProper(MonsterOneData* data)
{
	mSpeed = data->speed;
	mHurt = data->atk;
	mLife = data->life;
	mCurLife = mLastLife = mLife;
}