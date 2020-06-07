#include "stdafx.h"


class cCandy
{
public:
	Sprite* sprCandy;

	int type;

	int index_x;
	int index_y;

	int moveDown;

	bool isBoom;

	void change(int x, int y);
	void down();

	void Michael_Bay();
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

	int one;
	int one2;

	bool isEnd;

public:
	void init(Node* base);

	void initCandy();
	void createCandy(int x, int y);

	void touchBegan(Vec2 tp);
	void touchMoved(Vec2 tp);
	void touchEnded(Vec2 tp);
	
	//전체 체크
	void check(); 

	void crash();//뿌쒏뿕쒏

	void reChange();

	void down();//내려갈지어다

	void boom(int x, int y, cCandy* boomer);//드디어!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	void dddd();
};