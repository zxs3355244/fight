#ifndef _HERO_H
#define _HERO_H
#include "cocos2d.h"
#include "Uint.h"
#include "CvsFile.h"
struct HeroData
{
	int Sp;
	int level;
	int equipId;

};

static HeroData GlobalHeroData;
static string actEquipName[] = { "dao", "dao", "jiqiang", "jiqiang", "juji", "juji", "xiandan", "xiandan", "pao", "pao", "gelin", "penghuoqi", "penghuoqi", "shouqiang" };
static string actEffName[] = { "", "","tx_jq_1", "tx_jq_2", "tx_jjq_1", "tx_jjq_2", "zd_sd1", "zd_sd2", "tx_pao_2", "tx_pao_3", "tx_jtl", "", "", "tx_sq_1" };
static string bulEffName[] = { "", "", "jqtx", "jqtx", "jjqtx", "jjqtx", "sdqtx", "sdqtx", "", "", "jtltx", "phq1tx", "phq3tx", "sqtx" };
static string bulSoundName[] = { "sound/bluntshoot.mp3", "sound/bluntshoot.mp3", "sound/machinegunshoot.mp3", "sound/machinegunshoot.mp3", "sound/AWPshoot.mp3", "sound/AWPshoot.mp3", "sound/fourstarsAWPshoot.mp3", "sound/fourstarsAWPshoot.mp3", "sound/fourstarsbazookashoot.mp3", "sound/fourstarsbazookashoot.mp3", "sound/gatlingshoot.mp3", "sound/firegunshoot.mp3", "sound/firegunshoot.mp3", "sound/handgunshoot.mp3" };
enum RoleEquip
{
	eDao = 1,
	eDao1,
	eJiQiang,
	eJiQiang1,
	eJuJi,
	eJuJi1,
	eXianDan,//É¢µ¯Ç¹
	eXianDan1,//É¢µ¯Ç¹
	ePao,
	ePao1,
	eGeLin,//°Â¶¡µÄÅ­»ð
	ePengHuoQi1,
	ePengHuoQi2,
	eShouQiang,

};

enum JuJiAction
{
	kaihuoBegin = 1,
	kaihuoAim1,
	kaihuoAim2,
	kaihuoJuJi,
};
enum RoleAction
{
	kaihuo = 1,
	chongci,
	move,
	stand,
	die,
	stun,
	hurt,
	kaipao,
};
class Hero :public Uint
{
public:
	static Hero* getInstance();
	virtual bool init();
	Hero();
	~Hero();
	void showAniByEquipId(int id);
	void showAniAction(int id);
	void stateHandler(int state, float dt);
	void actTouch();
	void actRelease();
	void shootBullet();
	void shootBulletSched(float dt);
	void daoHit();
	void SanDanHit(); 
	void destory();
	void reLive();
	void showDun();
	
	virtual void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	virtual void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	void setHeadAction(string name,bool loop);
	void setFootAction(string name, bool loop);
	void setAtrAction( bool loop);
	virtual void updateLogic(float dt);
	void move(Vec2 dir,float dt);
	void fastmove(Vec2 dir, float dt);
	virtual void BulletHit(Uint* uint);
	bool btnTouch;
	float bulletTick;
	float curBulletTick;
	int mCurRoleEqu;
	int mCurRoleAct;
	int mCurAimAct;
	EuipData* mEquipData;
	bool haveDun;
	Armature* armatureDun;
	float dunTime;
private:

	Armature* armatureFir;
	bool isFootMoveing;
	float mJuJiTime;
	
	
};
#endif