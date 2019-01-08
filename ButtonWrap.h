/*!
 * file ButtonWrap.h
 * author DJ
 * date 2015.11.03
 * 
 */

#ifndef ButtonWrap_h__
#define ButtonWrap_h__


#include "cocos2d.h"
#include <functional>


USING_NS_CC;
using std::function;


#define BUTTON_DOWNSTATE Color3B(0x9d, 0x9d, 0x9d)


class ButtonWrap;
typedef std::function<void(ButtonWrap*)> listener;


class ButtonWrap : public Sprite
{
public:

	static ButtonWrap* create(const std::string& filename, const listener& cb, bool swallow = true);
	static ButtonWrap* createWithFrameName(const std::string& framename, const listener& cb, bool swallow = true);

	void setEnable(bool enable);
	void setDownAction(bool enable);
	void setHighType(bool enable);
	void setTouchDownMode(bool enable);
	void setUserDefineRect(const Rect& rect);

protected:
	ButtonWrap();
	virtual ~ButtonWrap();

private:
	bool initButtonWrap(const std::string& filename, const listener& cb, bool swallow);

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);

	void setHighlighted(bool highlight);
	void onConfirmHandle();
	bool hitTest(const Vec2& pt);

	listener _listener;
	Vec2 _touchPosition;
	bool _btnEnable;
	bool _isHighLight;
	bool _swallow;
	bool _downAction;
	bool _highType;
	bool _touchDown;
	bool _bUserDefineRect;
	Rect _userDefineRect;
};


#endif // ButtonWrap_h__
