#include "stdafx.h"

class cDoll
{
public:
	Sprite* sprDoll;

	int dolnum;//2=╟к 3=го╬А 

	int pointX;
	int pointY;

	void init(char* name,int dolnum, Node* base, int x, int y, float RealX, float RealY);
};

class cOmok
{
private:
	Node* base;

	bool turn;//0=╟к 1=го╬А

	cDoll* dolls[19][19];

public:
	bool isGameOver;

	void init(Node* base);

	bool putTheStone(Vec2 pos);

	bool check(int x,int y);

	int count(int x, int y, int px, int py, int result, int dolnum);

	~cOmok();

};