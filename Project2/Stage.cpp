#include<DxLib.h>
#include<functional>
#include<algorithm>
#include "Stage.h"
#include"PlayUnit.h"
#include"input/Keyboard1.h"
#include"input/Pad.h"
#include"input/Mouse.h"
#include"mode/Dorop.h"
#include"mode/Elase.h"
#include"mode/Fall.h"
#include"mode/Munyon.h"
#include"mode/Puyon.h"
#include"mode/Ojamamode.h"

int Stage::_stagecount = 0;

Stage::Stage():_screenID(0), _id(0), _color(0x000000), _blocksize(32), count(0), _stgmode(StgMode::DROP), _maxrensa(0), _rensa(0), _erasenum(0)
{
}

Stage::Stage(Vector2&& offset, Vector2&& size)
{
	_screenID = 0;
	_id = _stagecount;
	_stagecount++;
	_offset = std::move(offset);
	_size = std::move(size);
	_blocksize = 32;
	_stgmode = StgMode::DROP;
	init();
	//puyo = std::make_unique<Puyo>(Vector2{ 64,32 }, PuyoID::Red);
}

Stage::~Stage()
{
}

int Stage::GetStageDraw(void)
{
	return _screenID;
}

void Stage::Draw(void)
{
	if (InstancePuyo())
	{
		puyo->Draw();
	}
}

void Stage::Updata(void)
{
	(*controller)();
	
	Dirpermit dirparmit;
	dirparmit.perBit = { 1,1,1,1 };

	Draw();

	//auto pos = puyo->GetGrid(_blocksize);
	//int offset_y = ((pos.y % _blocksize) != 0);

	//for (auto data : controller->GetCntData())
	//{
	//	if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
	//	{
	//		if (_data[pos.x][pos.y - 1])
	//		{
	//			dirparmit.perBit.up = 0;
	//		}
	//		if (_data[pos.x][pos.y + 1])
	//		{
	//			dirparmit.perBit.down = 0;
	//		}
	//		if (_data[pos.x - 1][pos.y + offset_y])
	//		{
	//			dirparmit.perBit.left = 0;
	//		}
	//		if (_data[pos.x + 1][pos.y + offset_y])
	//		{
	//			dirparmit.perBit.right = 0;
	//		}

	//		puyo->SetDirParmit(dirparmit);
	//		puyo->Move(data.first);

	//	}
	//	if ((data.first == InputID::Down) && data.second[static_cast<int>(Trg::Now)])
	//	{
	//		puyo->SoftDrop();
	//	}
	//}
}

bool Stage::init(void)
{
	_screenID = MakeScreen(_size.x, _size.y, true);
	_color = 0x000033 << (16 * _id);

	controller = std::make_unique<Keyboard1>();
	if (GetJoypadNum() > 0)
	{
		controller = std::make_unique<Pad>();
	}
	controller->Setup(_id);
	return true;
}

bool Stage::InstancePuyo(void)
{
	//auto id = puyo->GetID();
	//auto pos1 = Vector2{ _blocksize / 2 + _blocksize * 3, _blocksize };
	//auto pos2 = Vector2{ _blocksize / 2 + _blocksize * 3, _blocksize + _blocksize / 2 };
	//PuyoVec.emplace(PuyoVec.begin(), std::make_unique<Puyo>(pos1));
	//id = puyo->GetID();
	//PuyoVec.emplace(PuyoVec.begin(), std::make_unique<Puyo>(pos2));

	return true;
}

bool Stage::OjamaInstance(void)
{
	return true;
}

bool Stage::SetWall(void)
{
	return true;
}

bool Stage::EleseData(void)
{
	return false;
}

void Stage::Deletopuyo(void)
{
}
