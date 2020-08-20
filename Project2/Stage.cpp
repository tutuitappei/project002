#include<functional>
#include<algorithm>
#include "Stage.h"
#include"PlayUnit.h"
#include"input/Keyboard1.h"
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
	return 0;
}

void Stage::Draw(void)
{
}

void Stage::Updata(void)
{
}

bool Stage::init(void)
{
	return false;
}

bool Stage::InstancePuyo(void)
{
	return false;
}

bool Stage::OjamaInstance(void)
{
	return false;
}

bool Stage::SetWall(void)
{
	return false;
}

bool Stage::EleseData(void)
{
	return false;
}

void Stage::Deletopuyo(void)
{
}
