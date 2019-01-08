
#include "ButtonWrap.h"


ButtonWrap::~ButtonWrap()
{

}

ButtonWrap::ButtonWrap()
:_btnEnable(true),
_isHighLight(false),
_touchPosition(Vec2::ZERO),
_swallow(true),
_downAction(true),
_highType(true),
_touchDown(false),
_bUserDefineRect(false)
{
	
}

ButtonWrap* ButtonWrap::create(const std::string& filename, const listener& cb, bool swallow /* = true */)
{
	ButtonWrap *wrap = new (std::nothrow) ButtonWrap();
	if (wrap && wrap->initWithFile(filename) && wrap->initButtonWrap(filename, cb, swallow))
	{
		wrap->autorelease();
		return wrap;
	}
	CC_SAFE_DELETE(wrap);
	return nullptr;
}

ButtonWrap* ButtonWrap::createWithFrameName(const std::string& framename, const listener& cb, bool swallow /* = true */)
{
	ButtonWrap *wrap = new (std::nothrow) ButtonWrap();
	if (wrap && wrap->initWithSpriteFrameName(framename) && wrap->initButtonWrap(framename, cb, swallow))
	{
		wrap->autorelease();
		return wrap;
	}
	CC_SAFE_DELETE(wrap);
	return nullptr;
}

bool ButtonWrap::initButtonWrap(const std::string& filename, const listener& cb, bool swallow)
{
	this->_listener = cb;
	this->_swallow = swallow;

	EventListenerTouchOneByOne* _eventListener = EventListenerTouchOneByOne::create();
	_eventListener->setSwallowTouches(_swallow);
	_eventListener->onTouchBegan = CC_CALLBACK_2(ButtonWrap::onTouchBegan, this);
	_eventListener->onTouchMoved = CC_CALLBACK_2(ButtonWrap::onTouchMoved, this);
	_eventListener->onTouchCancelled = CC_CALLBACK_2(ButtonWrap::onTouchCancelled, this);
	_eventListener->onTouchEnded = CC_CALLBACK_2(ButtonWrap::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_eventListener, this);

	return true;
}

bool ButtonWrap::onTouchBegan(Touch* touch, Event* event)
{
	bool hitted = false;
	if (this->isVisible() && _btnEnable)
	{
		_touchPosition = touch->getLocation();
		if (hitTest(_touchPosition))
		{
			hitted = true;
		}
	}
	if (!hitted)
	{
		return false;
	}
	setHighlighted(true);

	if (_touchDown)
	{
		onConfirmHandle();
	}

	return true;
}

void ButtonWrap::onTouchMoved(Touch* touch, Event* event)
{
	_touchPosition = touch->getLocation();

	setHighlighted(hitTest(_touchPosition));
}

void ButtonWrap::onTouchEnded(Touch* touch, Event* event)
{
	bool highLight = _isHighLight;
 	setHighlighted(false);
	if (highLight && !_touchDown)
	{
		onConfirmHandle();
	}
}

void ButtonWrap::onTouchCancelled(Touch *touch, Event *event)
{
	setHighlighted(false);
}

void ButtonWrap::setHighlighted(bool highlight)
{
	if (_isHighLight == highlight)
	{
		return;
	}
	_isHighLight = highlight;

	if (!_downAction)
	{
		return;
	}

	if (highlight == true)
	{
		if (_highType)
		{
			this->stopAllActions();
			this->runAction(ScaleTo::create(0.1f, 0.95f));
		}
		this->setColor(BUTTON_DOWNSTATE);
	}
	else
	{
		if (_highType)
		{
			this->stopAllActions();
			this->runAction(ScaleTo::create(0.05f, 1.0f));
		}
		this->setColor(Color3B::WHITE);
	}
}

void ButtonWrap::setTouchDownMode(bool enable)
{
	_touchDown = enable;
}

void ButtonWrap::onConfirmHandle()
{
	if (this->_listener)
	{
//		this->_button->retain();
		this->_listener(this);
//		this->_button->release();
	}
}

bool ButtonWrap::hitTest(const Vec2 &pt)
{
	Vec2 nsp = this->convertToNodeSpace(pt);

	if (_bUserDefineRect)
	{
		if (_userDefineRect.containsPoint(nsp))
		{
			return true;
		}
		return false;
	}
	else
	{
		Rect rt;
		rt.size = this->getContentSize();
		if (rt.containsPoint(nsp))
		{
			return true;
		}
		return false;
	}
}

void ButtonWrap::setEnable(bool enable)
{
	_btnEnable = enable;

	if (enable)
	{
		this->setScale(1.0f);
		this->setColor(Color3B::WHITE);
	}
	else
	{
		this->setScale(1.0f);
		this->setColor(Color3B::GRAY);
	}
}

void ButtonWrap::setDownAction(bool enable)
{
	_downAction = enable;
}

void ButtonWrap::setHighType(bool enable)
{
	_highType = enable;
}

void ButtonWrap::setUserDefineRect(const Rect& rect)
{
	_bUserDefineRect = true;
	_userDefineRect = rect;
}
