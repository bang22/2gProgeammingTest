#include "stdafx.h"

void cDoll::init(char* name, int dolnum, Node* base, int x, int y, float RealX, float RealY)
{

	sprDoll = Sprite::create(name);

	sprDoll->setPosition(Vec2(RealX, RealY));

	sprDoll->setAnchorPoint(Vec2(.5f, .5f));

	sprDoll->setScale(0.4f);

	base->addChild(sprDoll);

	pointX = x;
	pointY = y;

	this->dolnum = dolnum;
}

void cOmok::init(Node* base)
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			dolls[i][j] = NULL;
		}
	}

	this->base = base;

	turn = 1;

	isGameOver = false;
}

bool cOmok::putTheStone(Vec2 pos)
{
	float a;

	int x = NULL;
	int y = NULL;

	float realX, realY;
	//16에서 시작 간격은 26.5씩 13.25
	for (int i = 0; i < 19; i++)
	{
		float a = 16 + (26.5 * i);

		if (pos.x > a - 13.25&& pos.x < a + 13.25)
		{
			x = i;
			realX = a;
		}
	}

	for (int i = 0; i < 19; i++)
	{
		float a = 16 + (26.5 * i);

		if (pos.y > a - 13.25&& pos.y < a + 13.25)
		{
			y = i;
			realY = a;
		}
	}

	//바둑판을 넘어가는 바둑돌들
	if (x == NULL)
	{
		if (pos.x < 28.25)
		{
			x = 0;
			realX = 16;
		}
		else
		{
			x = 18;
			realX = 16 + (26.5 * x);
		}
	}
	if (y == NULL)
	{
		if (pos.y < 28.25)
		{
			y = 0;
			realY = 16;
		}
		else
		{
			y = 18;
			realY = 16 + (26.5 * y);
		}
	}
	
	//바둑돌을 놓을려는 위치 확인
	if (dolls[x][y] != NULL)
	{
		return false;
	}

	//턴에 따라 배치
	if (turn)
	{
		cDoll* doll = new cDoll;

		doll->init("Go_b.png", 2, base, x, y, realX, realY);

		dolls[x][y] = doll;

		turn = !turn;

		isGameOver = check(x, y);

		return true;
	}
	else
	{
		cDoll* doll = new cDoll;

		doll->init("Go_w.png", 3, base, x, y, realX, realY);

		dolls[x][y] = doll;

		turn = !turn;

		isGameOver = check(x, y);

		return true;
	}
}

bool cOmok::check(int x, int y)
{
	int num = dolls[x][y]->dolnum;
	
	int arrDollsCount[4] =
	{
		{ count(x, y, 0, 1, 0, num) + count(x, y, 0, -1, 0, num) },
		{ count(x, y, 1, 0, 1, num) + count(x, y, -1, 0, -1, num) },
		{count(x, y, 1, 1, 0, num) + count(x, y, -1, -1, 0, num) },
		{count(x, y, -1, 1, 0, num) + count(x, y, 1, -1, 0, num)},
	};

	for (int i = 0; i < 4; i++)
	{
		if (arrDollsCount[i]-1 == 5) return true;
	}

	return false;
}

int cOmok::count(int x, int y, int px, int py, int result,int dolnum)
{
	//판을 넘어가는 지?
	if (x > 18 || x < 0){ return result; }
	if (y > 18 || y < 0){ return result; }

	//이번 돌이 NULL인지 아니라면 돌의 속성이 다른지 체크
	if (dolls[x][y] == NULL){ return result; }
	else if (dolls[x][y]->dolnum != dolnum){ return result; }

	return count(x + px, y + py, px, py, result+1,dolnum);
}


cOmok::~cOmok()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (dolls[i][j] != NULL)
			{
				delete dolls[i][j];
			}
		}
	}
}