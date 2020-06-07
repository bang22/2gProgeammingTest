#include "stdafx.h"

class cCandy
{
public:
	Sprite* sprCandy;

	int type;

	int index_x;
	int index_y;

	int moveDown;

	bool isboom;

	void change(int x, int y)
	{
		auto move = MoveBy::create(0.1f, Vec2(x*TAG_TILE_SIZE, y*TAG_TILE_SIZE));

		sprCandy->runAction(move);

		index_x += x;
		index_y += y;

		moveDown = 0;
	}
	void down()
	{
		auto move = MoveBy::create(0.2f, Vec2(0, -(moveDown*TAG_TILE_SIZE)));
		sprCandy->runAction(move);
		index_y -= moveDown;

		moveDown = 0;
	}

	void makeBoom()
	{
		sprCandy->setTexture("boom.png");

		type = 99;
		isboom = true;
	}
};


class cCandyManager
{
private:
	Node* base;

	cCandy *SelectedCandy1;
	cCandy *SelectedCandy2;

	vector<cCandy*> vCandy;

	vector<cCandy*> vSelectedCandyX;
	vector<cCandy*> vSelectedCandyY;

	vector<cCandy*> vFinSelectedCandy;

	vector<cCandy*> vSpecialCandy;

	bool isChange;

	bool set;
	bool isEnd;

public:
	void init(Node* base);

	void initCandy();
	void createCandy(int x, int y);

	void touchBegan(Vec2 tp);
	void touchMoved(Vec2 tp);
	void touchEnded(Vec2 tp);

	void check();

	void crash();

	void reChange();

	void down();

	void boom(int x, int y, cCandy* boomer);

	void go();

};