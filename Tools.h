#ifndef _TOOLS_H
#define _TOOLS_H
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

int getMapType();
string getMapName(int charater);
int getMapNum(int charater);
int getMapCharaterById(int id);
int getMapLevelById(int id);
#endif