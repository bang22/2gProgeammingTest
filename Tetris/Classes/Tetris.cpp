#include "stdafx.h"

const int blocks[7][4][4][4] = {
	{ { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0 } },
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 } },
	{ { 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0 } },
	{ { 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0 } },
	{ { 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0 } },
	{ { 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0 } },
	{ { 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0 } }
}; //테트로미노모양 저장 4*4공간에 테트로미노을 표현 blcoks[b_type][b_rotation][i][j]로 사용


void cTetris::init(Node* base)
{
	this->base = base;

	blockType = NULL;
	MovingBlocksPositionY = NULL;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arrMovingBlock[i][j] = NULL;
			arrNextBlock[i][j] = NULL;
		}
	}

	vBoard.clear();
	dir = NULL;
	next = 0;
	isGayOver = false;
}


void cTetris::create(bool make)
{
	gayover();

	if (!isGayOver)
	{
		blockType = next;
		rotateType = 0;

		if (make)
		{
			MovingBlocksPositionX = 4;
			MovingBlocksPositionY = 20;
		}
		else {
			MovingBlocksPositionX = 100;
			MovingBlocksPositionY = -20;
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blocks[blockType][rotateType][i][j])
				{
					auto block = new Block;
					block->init(base, MovingBlocksPositionX + i, MovingBlocksPositionY + j);

					arrMovingBlock[i][j] = block;
					vBoard.push_back(block);
				}
				else { arrMovingBlock[i][j] = NULL; }
			}
		}
		nextBlock();
	}
}

void cTetris::nextBlock()
{
	next = rand()%7;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arrNextBlock[i][j] != NULL)
			{
				base->removeChild(arrNextBlock[i][j]->sprBlock, true);

				delete arrNextBlock[i][j];
			}
			arrNextBlock[i][j] = NULL;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (blocks[next][0][i][j])
			{
				auto block = new Block;
				block->init(base, 13 + i, 15 + j);

				arrNextBlock[i][j] = block;
			}
			else { arrNextBlock[i][j] = NULL; }
		}
	}
}

bool cTetris::check(int x,int y)
{

	for (auto block : vBoard)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (arrMovingBlock[i][j] == block)
				{
					goto BREAK;
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (arrMovingBlock[i][j] != NULL)
				{
					if (y == 0)
					{
						//벽 체크
						if (arrMovingBlock[i][j]->x + x <= 0 || arrMovingBlock[i][j]->x + x > 10){ return true; }
					}
						//바닥 체크
					if (arrMovingBlock[i][j]->y + y <= 0){ return true; }
					//다른 블럭 체크
					if (block->x == arrMovingBlock[i][j]->x+x && block->y == arrMovingBlock[i][j]->y + y){return true;}
				}
			}
		}

	BREAK:;
	}

	return false;
}

void cTetris::down()
{
	if (isGayOver) return;

	if (!check(0, -1))
	{
		MovingBlocksPositionY--;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (arrMovingBlock[i][j] != NULL)
				{
					arrMovingBlock[i][j]->move(0, -1);
				}
			}
		}

	}
	else { lineCheck(); create(true); }

}

void cTetris::lineCheck()
{
	vector<Block*>vErease;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < vBoard.size(); j++)
		{
			auto block = vBoard.at(j);

			if (block->y == i) { vErease.push_back(block); }
		}
		
		if (vErease.size() >= 10)
		{

			for (auto block : vErease)
			{
				vFinalSelect.push_back(block);
			}
		}

		vErease.clear();
	}
	deleteLine();
}

void cTetris::deleteLine()
{
	int size = 0;
	if (!vFinalSelect.empty())
	{

		for (auto block : vBoard)
		{
			int blockX = block->x;
			int blockY = block->y;

			for (auto selblock : vFinalSelect)
			{
				int selX = selblock->x;
				int selY = selblock->y;

				if (blockX == selX && blockY > selY)
				{
					block->downNum++;
				}
			}
			block->down();
		}


	RESTART:;
		for (int i = 0; i < vBoard.size(); i++)
		{
			auto block = vBoard.at(i);
			for (int j = 0; j < vFinalSelect.size(); j++)
			{
				auto block2 = vFinalSelect.at(j);
				if (block == block2)
				{
					vBoard.erase(vBoard.begin() + i);
					vFinalSelect.erase(vFinalSelect.begin() + j);

					base->removeChild(block->sprBlock, true);
					delete block;

					goto RESTART;
				}
			}
		}
		
		vFinalSelect.clear();
	}

}

void cTetris::Left()
{
	if (isGayOver) return;

	dir = 0;
	if (!check(-1, 0))
	{
		MovingBlocksPositionX--;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (arrMovingBlock[i][j] != NULL)
				{
					arrMovingBlock[i][j]->move(-1, 0);
				}
			}
		}
	}
}

void cTetris::Right()
{
	if (isGayOver) return;

	dir = 1;
	if (!check(+1, 0))
	{
		MovingBlocksPositionX++;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (arrMovingBlock[i][j] != NULL)
				{
					arrMovingBlock[i][j]->move(1, 0);
				}
			}
		}
	}
}

void cTetris::Rotate()
{
	if (isGayOver) return;


	for (int i = 0; i < 4; i++)//지우고 
	{
		for (int j = 0; j < 4; j++)
		{
			if (arrMovingBlock[i][j] != NULL)
			{
				for (int v = 0; v < vBoard.size(); v++)
				{
					if (vBoard.at(v) == arrMovingBlock[i][j])
					{
						vBoard.erase(vBoard.begin() + v);
					}
				}

				base->removeChild(arrMovingBlock[i][j]->sprBlock, true);

				delete arrMovingBlock[i][j];
			}
			arrMovingBlock[i][j] = NULL;
		}
	}

	rotateType++;

	if (rotateType >= 4) rotateType = 0;

	for (int i = 0; i < 4; i++)//다시만들기 ㄷㄷ
	{
		for (int j = 0; j < 4; j++)
		{
			if (blocks[blockType][rotateType][i][j])
			{
				auto block = new Block;
				block->init(base, MovingBlocksPositionX + i, MovingBlocksPositionY + j);

				arrMovingBlock[i][j] = block;
				vBoard.push_back(block);
			}
			else { arrMovingBlock[i][j] = NULL; }
		}
	}

	if (rot)
	{
		if (check(0, 0))
		{

			if (!dir)
			{
				MovingBlocksPositionX++;
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (arrMovingBlock[i][j] != NULL)
							arrMovingBlock[i][j]->move(1, 0);
					}
				}
				log("checks");
			}

			if (dir)
			{
				MovingBlocksPositionX--;
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (arrMovingBlock[i][j] != NULL)
							arrMovingBlock[i][j]->move(-1, 0);
					}
				}

				log("checks");
			}
		}

		if (check(0, 0))
		{
			if (!dir)
			{
				MovingBlocksPositionX--;
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (arrMovingBlock[i][j] != NULL)
							arrMovingBlock[i][j]->move(-1, 0);
					}
				}
				log("checks");
			}

			if (dir)
			{
				MovingBlocksPositionX++;
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (arrMovingBlock[i][j] != NULL)
							arrMovingBlock[i][j]->move(1, 0);
					}
				}

				log("checks");
			}

			rotateType -= 2;
			Rotate();
			rot = false;
		}
	}
	rot = true;
}

void cTetris::gayover()
{
	for (auto block : vBoard)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (arrMovingBlock[i][j] == block)
				{
					goto BREAK;
				}
			}
		}

		if (block->y > 19)
		{
			isGayOver = true;

			auto gameover = Sprite::create("gameover.png");
			gameover->setPosition(Vec2(438,300));
			base->addChild(gameover);
		}

	BREAK:;
	}
}