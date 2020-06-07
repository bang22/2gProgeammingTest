#include "stdafx.h"

void cCandyManager::init(Node* base)
{

	this->base = base;

	SelectedCandy1 = NULL;
	SelectedCandy2 = NULL;

	initCandy();

	crash();

	isChange = true;

	set = false;

	isEnd = true;
}

void cCandyManager::initCandy()
{
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			createCandy(i, j);
		}
	}
}

void cCandyManager::createCandy(int x, int y)
{
	int num;
	auto candy = new cCandy;

	num = rand() % 6 + 1;
	candy->sprCandy = Sprite::create(StringUtils::format("%d.png", num));
	candy->sprCandy->setPosition(Vec2(x*TAG_TILE_SIZE + 50, y*TAG_TILE_SIZE + 50));
	candy->type = num;
	candy->index_x = x;
	candy->index_y = y;
	candy->moveDown = 0;
	base->addChild(candy->sprCandy);
	vCandy.push_back(candy);
}

void cCandyManager::touchBegan(Vec2 tp)
{
	if (!isChange) return;

	for (auto candy : vCandy)
	{
		if (candy->sprCandy->getBoundingBox().containsPoint(tp))
		{
			SelectedCandy1 = candy;
			break;
		}
	}

	for (auto candy : vSpecialCandy)
	{
		if (candy->sprCandy->getBoundingBox().containsPoint(tp))
		{
			boom(candy->index_x, candy->index_y, candy);
			break;
		}
	}
}

void cCandyManager::touchMoved(Vec2 tp)
{
	if (SelectedCandy1 == NULL) return;
	if (!isChange) return;

	for (auto candy : vCandy)
	{

		if (candy->sprCandy->getBoundingBox().containsPoint(tp))
		{
			int x = candy->index_x;
			int y = candy->index_y;

			int sx = SelectedCandy1->index_x;
			int sy = SelectedCandy1->index_y;
			if (x == sx + 1 && y == sy){
				SelectedCandy2 = candy;

				SelectedCandy1->change(+1, 0);
				SelectedCandy2->change(-1, 0);

				isChange = false;
				break;
			}
			if (x == sx - 1 && y == sy){
				SelectedCandy2 = candy;

				SelectedCandy1->change(-1, 0);
				SelectedCandy2->change(+1, 0);

				isChange = false;
				break;
			}
			if (x == sx && y == sy + 1){
				SelectedCandy2 = candy;

				SelectedCandy1->change(0, +1);
				SelectedCandy2->change(0, -1);

				isChange = false;
				break;
			}
			if (x == sx && y == sy - 1){
				SelectedCandy2 = candy;

				SelectedCandy1->change(0, -1);
				SelectedCandy2->change(0, +1);

				isChange = false;
				break;
			}
		}
	}
}

void cCandyManager::touchEnded(Vec2 tp)
{

	crash();

	isEnd = false;

	SelectedCandy1 = NULL;
	SelectedCandy2 = NULL;
}

void cCandyManager::crash()
{
	check();

	if (vFinSelectedCandy.empty()) { reChange(); }

	if (set)
	{

		for (int i = 0; i < vFinSelectedCandy.size(); i++)
		{
			if (SelectedCandy1 == NULL && SelectedCandy2 == NULL) break;

			auto candy = vFinSelectedCandy.at(i);

			int sel1X = SelectedCandy1->index_x;
			int sel1Y = SelectedCandy1->index_y;
			int sel1Type = SelectedCandy1->type;


			int sel2X = SelectedCandy2->index_x;
			int sel2Y = SelectedCandy2->index_y;
			int sel2Type = SelectedCandy2->type;

			if (sel1X == candy->index_x && sel1Y == candy->index_y)
			{
				candy->makeBoom();
				vSpecialCandy.push_back(candy);
				vFinSelectedCandy.erase(vFinSelectedCandy.begin() + i);

				break;
			}
			if (sel2X == candy->index_x && sel2Y == candy->index_y)
			{
				candy->makeBoom();
				vSpecialCandy.push_back(candy);
				vFinSelectedCandy.erase(vFinSelectedCandy.begin() + i);
				break;
			}
		}
	}
	set = false;

	//////////////절////////취/////////선///////////////

	for (auto candy : vFinSelectedCandy)
	{
		base->removeChild(candy->sprCandy, true);

		for (int i = 0; i < vCandy.size(); i++)
			if (vCandy.at(i) == candy){
				vCandy.erase(vCandy.begin() + i);
			}
	}

	vSelectedCandyX.clear();
	vSelectedCandyY.clear();

	base->runAction(Sequence::create(DelayTime::create(.2f), CallFunc::create(CC_CALLBACK_0(cCandyManager::down, this)), NULL));
}

void cCandyManager::check()
{
	int lastType = NULL;
	int NextType = NULL;
	int count = 1;

	int candyX;
	int candyY;

	bool samecheck = false;

	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			for (int i = 0; i < vCandy.size(); i++)
			{
				auto candy = vCandy.at(i);

				candyX = candy->index_x;
				candyY = candy->index_y;

				if (candyX == x&& candyY == y)
				{
					if (lastType == candy->type)
					{
						if (count == 1){
							for (auto candy : vCandy){
								if (candy->index_x == x && candy->index_y + 1 == y){ vSelectedCandyY.push_back(candy); break; }
							}
						}

						vSelectedCandyY.push_back(candy);

						count++;

						if (count >= 3)
						{
							for (auto candy : vSelectedCandyY)
							{
								for (auto c : vFinSelectedCandy)
								{
									if (c == candy){ samecheck = true; }
								}
								if (!samecheck)vFinSelectedCandy.push_back(candy);

								samecheck = false;
							}
						}
						if (count >= 4 && !set) set = true;
					}
					else {
						if (count < 3)vSelectedCandyY.clear();
						lastType = candy->type;
						count = 1;
					}
					if (candy->type==99){
						if (count < 3)vSelectedCandyY.clear();
						lastType = candy->type;
						count = 1;
					}
				}
			}
		}
		lastType = NULL;
		vSelectedCandyY.clear();
	}
	lastType = NULL;
	count = 1;
	samecheck = false;
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			for (int i = 0; i < vCandy.size(); i++)
			{
				auto candy = vCandy.at(i);
				candyX = candy->index_x;
				candyY = candy->index_y;
				if (candyX == x&& candyY == y)
				{
					if (lastType == candy->type)
					{
						if (count == 1){
							for (auto candy : vCandy){
								if (candy->index_x == x - 1 && candy->index_y == y){ vSelectedCandyX.push_back(candy); break; }
							}
						}
						vSelectedCandyX.push_back(candy);
						count++;
						if (count >= 3)
						{
							for (auto candy : vSelectedCandyX)
							{
								for (auto c : vFinSelectedCandy)
								{
									if (c == candy){ samecheck = true; }
								}
								if (!samecheck)vFinSelectedCandy.push_back(candy);

								samecheck = false;
							}
						}
						if (count >= 4 && !set) set = true;
					}
					else {
						if (count < 3)vSelectedCandyX.clear();
						lastType = candy->type;
						count = 1;
					}
					if (candy->type == 99){
						if (count < 3)vSelectedCandyY.clear();
						lastType = candy->type;
						count = 1;
					}
				}
			}
		}
		lastType = NULL;
		vSelectedCandyX.clear();
	}
}

void cCandyManager::down()
{

	//새로운 캔디 생성
	int makenum[7] = { 0, };

	vector<cCandy*> check;

	for (auto sel : vFinSelectedCandy)
	{
		int x = sel->index_x;
		int y = 7;

		y += makenum[x];
		createCandy(x, y);
		makenum[x]++;

		check.push_back(sel);
	}
	for (auto candy : vCandy)
	{
		int candyX = candy->index_x;
		int candyY = candy->index_y;

		for (auto Selcandy : vFinSelectedCandy)
		{
			int selX = Selcandy->index_x;
			int selY = Selcandy->index_y;

			if (candyX == selX && candyY > selY)
			{
				candy->moveDown++;
			}
		}

		candy->down();
	}
	vSelectedCandyX.clear();
	vSelectedCandyY.clear();

	if (vFinSelectedCandy.empty()) {

		base->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create(CC_CALLBACK_0(cCandyManager::go, this)), NULL));
	}
	else
	{
		vFinSelectedCandy.clear();
		base->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create(CC_CALLBACK_0(cCandyManager::crash, this)), NULL));
	}
}

void cCandyManager::reChange()
{
	if (SelectedCandy1 != NULL &&SelectedCandy2 != NULL)
	{
		int sel1X = SelectedCandy1->index_x;
		int sel1Y = SelectedCandy1->index_y;
		int sel2X = SelectedCandy2->index_x;
		int sel2Y = SelectedCandy2->index_y;


		if (sel2X == sel1X + 1 && sel2Y == sel1Y){
			SelectedCandy1->change(+1, 0);
			SelectedCandy2->change(-1, 0);
		}
		if (sel2X == sel1X - 1 && sel2Y == sel1Y){
			SelectedCandy1->change(-1, 0);
			SelectedCandy2->change(+1, 0);
		}
		if (sel2X == sel1X && sel2Y == sel1Y + 1) {
			SelectedCandy1->change(0, +1);
			SelectedCandy2->change(0, -1);
		}
		if (sel2X == sel1X && sel2Y == sel1Y - 1) {
			SelectedCandy1->change(0, -1);
			SelectedCandy2->change(0, +1);
		}
	}
}

void cCandyManager::boom(int x, int y, cCandy* boomer)
{

	if (!isChange) return;

	isChange = false;

	for (int i = 0; i < vCandy.size(); i++)
	{
		auto candy = vCandy.at(i);

		if (!(candy->type == 99))
		{
			if (candy->index_x == x || candy->index_y == y)
			{
				vFinSelectedCandy.push_back(candy);
			}
		}
	}

	for (int i = 0; i < vCandy.size(); i++)
	{
		if (vCandy.at(i) == boomer){

			vCandy.erase(vCandy.begin() + i);
		}
	}

	for (int i = 0; i < vSpecialCandy.size(); i++)
	{
		if (vSpecialCandy.at(i) == boomer){

			vSpecialCandy.erase(vSpecialCandy.begin() + i);
		}
	}
	vFinSelectedCandy.push_back(boomer);

	crash();
	set = false;

	SelectedCandy1 = NULL;
	SelectedCandy2 = NULL;
}


void cCandyManager::go()
{
	isEnd = true;
	isChange = true;
	set = false;
}