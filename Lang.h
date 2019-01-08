
#ifndef __QMDDZ_LANG_h__
#define __QMDDZ_LANG_h__

#include <cocos2d.h>
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


static ValueVector txt_vec;
static ValueVector txtMap_vec;
void initLangWord();
string GetWord(const char* wordId);
string GetWordMap(const char* wordId);
#endif // __QMDDZ_LANG_h__