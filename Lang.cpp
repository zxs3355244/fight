#include "Lang.h"

void initLangWord()
{
	txt_vec = FileUtils::getInstance()->getValueVectorFromFile("language.xml");
	txtMap_vec = FileUtils::getInstance()->getValueVectorFromFile("font/strings.xml");
}

string GetWord(const char* wordId)
{
	auto txt_mapa = txt_vec.at(0).asValueMap();
	string ret1 = txt_mapa.at(wordId).asString();
	return ret1;
}

string GetWordMap(const char* wordId)
{
	auto txt_map = txtMap_vec.at(0).asValueMap();
	string ret = txt_map.at(wordId).asString();
	return ret;
}
