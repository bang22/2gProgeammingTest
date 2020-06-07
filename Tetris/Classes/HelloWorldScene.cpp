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
  
	srand(time(NULL));

	auto side1 = Sprite::create("side.png");
	side1->setAnchorPoint(Vec2(0.5f, 0));
	this->addChild(side1);

	auto side2 = Sprite::create("side.png");
	side2->setPositionX(TAG_TILE_SIZE * 11);
	side2->setAnchorPoint(Vec2(0.5f, 0));
	this->addChild(side2);

	auto bot = Sprite::create("bot.png");
	bot->setPositionX(TAG_TILE_SIZE/2);
	bot->setAnchorPoint(Vec2(0, 0.5f));
	this->addChild(bot);

	speedUp = false;

	tetris = new cTetris;
	tetris->init(this);
	tetris->create(false);
	tetris->create(true);

    Size visibleSize = Director::getInstance()->getVisibleSize();
	
	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(HelloWorld::update), 0.5f);
	this->schedule(schedule_selector(HelloWorld::update2), 0.1f);

    return true;
}

void HelloWorld::update(float dt)
{
	if (!speedUp)
	{
		tetris->down();
	}
}

void HelloWorld::update2(float dt)
{
	if (speedUp)
	{
		tetris->down();
	}
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		tetris->Rotate();
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		speedUp = true;
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		tetris->Left();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		tetris->Right();
		break;
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_DOWN_ARROW == keyCode)
	{
		speedUp = false;
	}
}