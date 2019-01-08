#ifndef _GAME_LAYER_
#define _GAME_LAYER_
#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using std::vector;
using std::string;
using std::map;
USING_NS_CC;
using namespace cocostudio;
using namespace ui;
#include "Rocker.h"
#include "Bullet.h"
#include "Monster.h"
#include "FoxMonster.h"
#include "BuffMonster.h"
#include "BeeMonster.h"
#include "PigMonster.h"
#include "DragonMonster.h"
#include "Bomb.h"
#include "ArmBullet.h"
static int SPEEDHERO = 150;
static int MOVEHEIGHT = 280;
class GameLayer :public Layer
{
public:
	static GameLayer* getInstance();
	virtual bool init();
	GameLayer();
	~GameLayer();
	void initHero();
	void initUi();
	void initMap();
	void setActEquip(int index, int id);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;
	void onActClick(Ref* sender, Widget::TouchEventType type );
	virtual void update(float dt);
	void showAllHurt();
	void showdazhaoEndHurt();
	void addObj(Bullet* bl);
	void bulletHit(Bullet* bl);
	void armBulletHit(ArmBullet* bl);
	virtual void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	virtual void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	/*virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);*/
	void onClickDun(Ref* sender);
	void onClickZhao(Ref* sender);
	void onClickXing(Ref* sender);
	void onClickAtc4(Ref* sender);
	void onClickPause(Ref* sender);
	void showTishiIcon(int dir);
	void gameOver(bool bl);
	void updateText();
	void showOutBoss();
	void showDaZhao();
	void updateBossHp(float hp);
	Layer* mGameLayer;
	Layer* mUILayer;
	Layer* mEffLayer;
	HRocker* mRocker;
	vector<Uint*> ObjVec;
	FoxMonster* monster;
	bool mGameStart;
	Node* mMainCsb;
	Button* btnPause;
	Button* btnAtk[4];
	Sprite* btnContent[4];
	Button* btnDun;
	TextAtlas* mDunNum;
	TextAtlas* mDiamondNum;
	Button* btnDaZhao;
	TextAtlas* mZhaoNum;
	Button* btnXing;
	LoadingBar* BarHp;
	ProgressTimer* mAtkPro;
	ProgressTimer* mXing;
	bool btnAtkChoose[3];
	Sprite* mXue;
	Node* mBossBarNode;
	LoadingBar* mBossBar;
	bool isOver;
	bool isWin;
	int tickNum;
	bool isShowDaZhao;
	float zhaoTime;
	bool isXing;
	float xingTime;
	bool xingPross;
	float ackTime;
	private:
		Vec2 lastDir;
		char buff[100];
		Armature* win;
		Armature* dazhao;
		Armature* dazhao1;
		Armature* dazhao2;
		Sprite* leftIcon;
		Sprite* rightIcon;
		bool isShowIcon;
		
};
#endif