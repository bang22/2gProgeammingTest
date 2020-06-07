#include "stdafx.h"


class cTetris
{
private:
	Node* base;

	int movingBlockX;
	int movingBlockY;

	int blockType;
	int rotateType;
	int MovingBlocksPositionX;
	int MovingBlocksPositionY;

	Block* arrNextBlock[4][4];
	
	Block* arrMovingBlock[4][4];
	vector<Block*>vBoard;
	vector<Block*>vFinalSelect;

	bool dir;//0=LEFT , 1=RIGHT

	bool isGayOver;

	int next;

	bool rot;

public:
	void init(Node* base);

	void create(bool make);
 

	void nextBlock();


	bool check(int x, int y);
	void down();

	void lineCheck();
	void deleteLine();

	void Left();
	void Right();
	void Rotate();

	void gayover();
};