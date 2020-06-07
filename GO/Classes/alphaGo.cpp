#include "stdafx.h"

Scene* alphaGo::createScene()
{
    //!< 씬을 Auto Release 가능하도록 Create 메소드로 만듬
	//!< 씬을 Retain 메소드와 Auto Release 메소드에 등록
    auto scene = Scene::create();
    
    //!< 씬에 Layer를 생성해서 등록시킴
	auto layer = alphaGo::create();

    //!< 현재 씬 리스트에 등록
    scene->addChild(layer);

    //!< 이 씬에 대한 정보를 반환
    return scene;
}

/**
 @brief : 초기화 하는 구문
 @param : 없음
*/
bool alphaGo::init()
{
	//!< 최상위 레이어에서 초기화를 시행하고 초기화가 정상적으로 되었는지 확인
	//!< 만약 false 를 하게 되면 정상적이지 않은걸로 판단하고 이하의 구문 실행 안함
	if ( !Layer::init() )
		return false;
  
	//!< 화면 사이즈 알아오는 구문
    
	
	auto board = Sprite::create("Go_board.png");
	board->setAnchorPoint(Vec2(0, 0));
	this->addChild(board);

	isGameOver = false;

	Omok = new cOmok;

	Omok->init(this);

	schedule(schedule_selector(alphaGo::Update) , 0.0f);

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(alphaGo::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(alphaGo::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(alphaGo::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void alphaGo::Update(float dt)
{

}


bool alphaGo::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (!isGameOver)
		Omok->putTheStone(touch->getLocation());

	return true;
}

void alphaGo::onTouchMoved(Touch* touch, Event* unused_event)
{
	
}

void alphaGo::onTouchEnded(Touch* touch, Event* unused_event)
{
	Size size = Director::getInstance()->getVisibleSize();
	
	if (Omok->isGameOver)
	{
		auto gameover = Sprite::create("GAMEOVER.png");
		gameover->setPosition(size / 2);

		this->addChild(gameover);

		isGameOver = true;
	}
}