#include<DxLib.h>
#include"puyo/Puyo.h"
#include "NextPuyo.h"

NextPuyo::NextPuyo(Vector2& pos, int data, int drawnum)
{
	_screenID = MakeScreen(97, 129);
	_pos = pos;
	_drawCount = drawnum;
	Add(data);
}

NextPuyo::~NextPuyo()
{
}

nextPair NextPuyo::PickUp(void)
{
	auto nextdata = *(_nextPuyoList.begin());
	_nextPuyoList.erase(_nextPuyoList.begin());
	Add(1);
	return nextdata;

}

bool NextPuyo::Add(int no)
{
	while (no)
	{
		_nextPuyoList.emplace_back(
			nextPair{
				std::make_shared<Puyo>(Vector2{ 0,0 }, static_cast<PuyoID>((rand() % (static_cast<int>(PuyoID::MAX) - 4)) + 1)),
				std::make_shared<Puyo>(Vector2{ 0,0 }, static_cast<PuyoID>((rand() % (static_cast<int>(PuyoID::MAX) - 4)) + 1))
			}
		);
		no--;
	}
	Vector2 offset = { 64,32 };
	Vector2 pos1 = {16,16 };
	Vector2 pos2 = { 16,32 };
	for (auto data : _nextPuyoList)
	{
		data.first->pos(pos1);
		data.second->pos(pos2);
		pos1 += offset;
		pos2 += offset;
	}
	return true;
}

void NextPuyo::Draw(void)
{
}
