#ifndef _LOGINSCENE_H
#define _LOGINSCENE_H
#include "cocos2d.h"
USING_NS_CC;

class LoginScene :public Scene
{
public:
	LoginScene();
	~LoginScene();
	CREATE_FUNC(LoginScene);
	virtual bool init();
private:

};


#endif