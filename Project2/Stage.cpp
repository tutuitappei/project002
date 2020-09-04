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

Stage::Stage():_screenID(0), _id(0), _color(0x000000), _blocksize(32), count(0), _stgmode(StgMode::DROP), _maxrensa(0), _rensa(0), _erasenum(0),_gameoverflag(false),_ojamanum(0),_ojamaflag(false), _downFlag(true)
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
	_gameoverflag = false;
	_ojamanum = 0;
	_ojamaflag = false;
	_downFlag = true;
	Init();
}

Stage::~Stage()
{
	_stagecount--;
}

void Stage::GetStageDraw(void)
{
	DrawGraph(_offset.x, _offset.y, GetStageID(), true);
	//DrawRotaGraph(_offset.x + _size.x - _size.x / 4 + 64, _offset.y + _size.y / 2 + 64, 1, 0, GetStageID(), true);
}

void Stage::Draw(void)
{
	//SetDrawScreen(_screenID);
	//ClsDrawScreen();
	DrawBox(_offset.x, _offset.y, _size.x* STAGE_MAP_X, _size.y * (STAGE_MAP_Y-1),0x000000,true);
	//DrawBox(_size.x * STAGE_MAP);
	for (auto&& puyo : puyoVec)
	{
		puyo->Draw();
	}

	//GetStageDraw();
}

void Stage::Updata(void)
{
	(*controller)();
	if (!_stagetype[_stgmode](*this))
	{
		for (auto&& puyo : puyoVec)
		{
			puyo->Updata();
		}
	}
	_gameoverflag = GameOverChack();
}

bool Stage::Init(void)
{
	_stagetype.try_emplace(StgMode::DROP,Dorop());
	_stagetype.try_emplace(StgMode::ERASE,Elase());
	_stagetype.try_emplace(StgMode::MOVE,Fall());
	_stagetype.try_emplace(StgMode::MUNYON, Munyon());
	_stagetype.try_emplace(StgMode::PUYON,Puyon());
	_stagetype.try_emplace(StgMode::OJAMA,Ojamamode());

	_screenID = MakeScreen(_size.x * STAGE_MAP_X , _size.y * STAGE_MAP_Y,true);
	_color = 0x000033 << (16 * _id);

	_dataBase.resize(STAGE_MAP_X * STAGE_MAP_Y);
	for (size_t no = 0; no < STAGE_MAP_Y; no++)
	{
		_data.emplace_back(&_dataBase[no * static_cast<size_t>(STAGE_MAP_X)]);
	}
	for (size_t no = 0; no < STAGE_MAP_X; no++)
	{
		_data.emplace_back(&_dataBase[no * static_cast<size_t>(STAGE_MAP_Y)]);
	}
	_playunit = std::make_unique<PlayUnit>(*this);
	controller = std::make_unique<Keyboard1>();
	if (GetJoypadNum() > 0)
	{
		controller = std::make_unique<Pad>();
	}
	controller->Setup(_id);
	InstancePuyo();
	SetWall();
	return true;
}

bool Stage::InstancePuyo(void)
{
	//auto nextpuyo = _nextpuyo->PickUp();
	auto pos1 = Vector2{_offset.x+16 +_size.x,_offset.y+16 };
	auto pos2 = Vector2{ _offset.x + 16 +_size.x,_offset.y + 16 + _blocksize };
	auto id = puyo->GetID();
	puyoVec.emplace(puyoVec.begin(), std::make_unique<Puyo>(pos1,id));
	id = puyo->GetID();
	puyoVec.emplace(puyoVec.begin()+1, std::make_unique<Puyo>(pos2,id));

	_downFlag = true;
	return true;
}

bool Stage::OjamaInstance(void)
{
	return true;
}

bool Stage::SetWall(void)
{
	for (int i = 0; i < STAGE_MAP_X; i++)
	{
		for (int j = 0; j < STAGE_MAP_Y; j++)
		{
			if ((i == 0 || i == STAGE_MAP_X - 1) || (j==0||j == STAGE_MAP_Y - 1))
			{
				_data[j][i] = std::make_shared<Puyo>(Vector2(_blocksize * i, _blocksize * j),PuyoID::Wall);
			}
		}
	}
	return true;
}

bool Stage::EleseData(PuyoID id, Vector2 vec)
{
	memset(_erasedataBase.data(), 0, _erasedataBase.size() * sizeof(PuyoID));

	std::function<void(PuyoID, Vector2)> chpuyo = [&](PuyoID id, Vector2 vec) {
		if (_erasedata[vec.y][vec.x]->GetID() == PuyoID::Non)
		{
			if (_data[vec.y][vec.x])
			{
				count++;
				_erasenum++;
				_erasedata[vec.y][vec.x] = _data[vec.y][vec.x];
				chpuyo(id, { vec.x,vec.y - 1 });
				chpuyo(id, { vec.x,vec.y + 1 });
				chpuyo(id, { vec.x - 1,vec.y });
				chpuyo(id, { vec.x + 1,vec.y });
			}
		}
	};
	if (count < 4)
	{
		memset(_erasedataBase.data(), 0, _erasedataBase.size() * sizeof(PuyoID));
	}
	else
	{
		for (auto&& puyo : puyoVec)
		{
			auto vec = puyo->GetGrid(_blocksize);
			if (_erasedata[vec.x][vec.y])
			{
				puyo->alive(false);

				_data[vec.x][vec.y].reset();
			}
		}
		//eraseCnt_ += count;
		return true;
	}
	return false;
}

bool Stage::Movepuyo(Sharepuyo& puyo)
{
	Dirpermit dirparmit;
	dirparmit.perBit = { 0,1,1,1 };
	auto pos = puyo->GetGrid(_blocksize);
	int offset_y = ((pos.y % _blocksize) != 0);

	if (_data[pos.y - 1][pos.x])
	{
		dirparmit.perBit.up = 0;
	}
	if (_data[pos.y + offset_y][pos.x - 1])
	{
		dirparmit.perBit.left = 0;
	}
	if (_data[pos.y + offset_y][pos.x + 1])
	{
		dirparmit.perBit.right = 0;
	}
	if (_data[pos.y + 1][pos.x])
	{
		dirparmit.perBit.down = 0;
		_data[pos.x][pos.y] = puyo;
		_downFlag = false;
		return true;
	}
	puyo->SetDirParmit(dirparmit);

	return false;
}

bool Stage::GameOverChack(void)
{
	if (_data[1][2])
	{
		return true;
	}
	return false;
}

bool Stage::GameOver(void)
{
	return _gameoverflag;
}

bool Stage::DownMode(void)
{
	return _downFlag;
}

void Stage::Deletopuyo(void)
{
	auto itr = std::remove_if(puyoVec.begin(), puyoVec.end(), [](auto&& puyo) {return!(puyo->alive()); });
	if (itr != puyoVec.end())
	{
		puyoVec.erase(itr, puyoVec.end());
	}
}

Vector2 Stage::ConvertGrid(Vector2&& pos)
{
	// Žó‚¯Žæ‚Á‚½pos‚ðÏ½–Ú‚Ö
	return Vector2{ pos.x / _blocksize,pos.y / _blocksize };
}

int Stage::GetStageID(void)
{
	return _screenID;
}
