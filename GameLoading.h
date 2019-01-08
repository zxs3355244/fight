#ifndef _GAMELOADING_H
#define _GAMELOADING_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using std::string;
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

static string reloadExportJsons[] = {
	"hero2.ExportJson",
	"hero.ExportJson",
	"hero_atk.ExportJson",
	"hero_fire.ExportJson",
	"hero_fh.ExportJson",
	"dazhao_bj.ExportJson",
	"dazhao_bom.ExportJson",
	"goblin.ExportJson",
	"goblin_bullet.ExportJson",
	"pig.ExportJson",
	"bee.ExportJson",
	"bee_bullet.ExportJson",
	"buff.ExportJson",
	"buff_bullet.ExportJson",
	"dragon.ExportJson",
	"fox.ExportJson",
	"fox_bullet.ExportJson",
	"chuxian.ExportJson",
	"zidantexiao.ExportJson",
	"xin_texiao.ExportJson",
	"boos_appear.ExportJson",
	"victory.ExportJson",
	"bomb.ExportJson",
	
};
static int mAllArn = 23;
class GameLoading :public Scene
{
public:
	GameLoading();
	~GameLoading();
	static GameLoading* create();
	virtual bool init();
	void jsonAsyncCallback(float f);
private:
	int curReloadExportJsonNum;
	int mId;
	LoadingBar* mBar;
	
};


#endif