#include "stdafx.h"


class Block
{
public:

	int x, y;

	Sprite* sprBlock;
	bool isdown;

	int downNum;

	void init(Node* base,int x,int y)
	{
		this->x = x;
		this->y = y;
		isdown = 0;
		downNum = 0;

		sprBlock = Sprite::create("block.png");
		sprBlock->setPosition(Vec2(x*TAG_TILE_SIZE,y*TAG_TILE_SIZE));
		base->addChild(sprBlock);
	}

	void move(int x,int y)
	{
		auto moveby = MoveBy::create(0, Vec2(x*TAG_TILE_SIZE, y*TAG_TILE_SIZE));
		sprBlock->runAction(moveby);

		this->x += x;
		this->y += y;
	}

	void down()
	{
		move(0, -downNum);
		downNum = 0;
	}
};