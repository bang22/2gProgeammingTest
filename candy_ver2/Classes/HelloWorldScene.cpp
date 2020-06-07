#include "stdafx.h"

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
	if ( !Layer::init() )
		return false;
  
    Size size = Director::getInstance()->getVisibleSize();

	srand(time(NULL));

	candy = new cCandyManager;

	candy->init(this);

	auto listener = EventListenerTouchOneByOne::create(); 
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	candy->touchBegan(touch->getLocation());

	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
	candy->touchMoved(touch->getLocation());
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	candy->touchEnded(touch->getLocation());
}