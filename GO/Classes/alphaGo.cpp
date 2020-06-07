#include "stdafx.h"

Scene* alphaGo::createScene()
{
    //!< ���� Auto Release �����ϵ��� Create �޼ҵ�� ����
	//!< ���� Retain �޼ҵ�� Auto Release �޼ҵ忡 ���
    auto scene = Scene::create();
    
    //!< ���� Layer�� �����ؼ� ��Ͻ�Ŵ
	auto layer = alphaGo::create();

    //!< ���� �� ����Ʈ�� ���
    scene->addChild(layer);

    //!< �� ���� ���� ������ ��ȯ
    return scene;
}

/**
 @brief : �ʱ�ȭ �ϴ� ����
 @param : ����
*/
bool alphaGo::init()
{
	//!< �ֻ��� ���̾�� �ʱ�ȭ�� �����ϰ� �ʱ�ȭ�� ���������� �Ǿ����� Ȯ��
	//!< ���� false �� �ϰ� �Ǹ� ���������� �����ɷ� �Ǵ��ϰ� ������ ���� ���� ����
	if ( !Layer::init() )
		return false;
  
	//!< ȭ�� ������ �˾ƿ��� ����
    
	
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