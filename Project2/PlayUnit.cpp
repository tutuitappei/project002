#include"PlayUnit.h"
#include"Stage.h"
#include"puyo/Puyo.h"

PlayUnit::PlayUnit(Stage& stage):_stage(stage)
{
	_targetID = 0;
	_rotPos = { 0,0 };
	Init();
}

PlayUnit::~PlayUnit()
{
}

bool PlayUnit::Updata(void)
{
	auto CheckPair = [&](int tar) {
		if (!_stage.puyoVec[tar ^ 1]->DirPermit().perBit.down)
		{
			// ’…’n‚µ‚Ä‚¢‚½‚ç—Ž‰º‚·‚é‚¾‚¯
			_stage._stgmode = StgMode::MOVE;
			_stage.puyoVec[tar]->SetInterval(1);
			return true;
		}
		return false;
	};
	
	if (_stage._stgmode != StgMode::DROP)
	{
		return false;
	}
	for (auto data : _stage.controller->GetCntData())
	{

			if ((data.first == InputID::Down)&&(data.second[static_cast<int>(Trg::Now)]))
			{
				_stage.puyoVec[0]->SoftDrop();
				_stage.puyoVec[1]->SoftDrop();
				//_stage.puyo->SoftDrop();
			}
			if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
			{

			if ((data.first == InputID::Left))
			{
				auto pos1 = _stage.puyoVec[0]->GetGrid(_stage._blocksize);
				auto pos2 = _stage.puyoVec[1]->GetGrid(_stage._blocksize);
				int offset1 = (_stage.puyoVec[0]->pos().y % _stage._blocksize != 0);
				int offset2 = (_stage.puyoVec[1]->pos().y % _stage._blocksize != 0);
				if (!_stage._data[pos1.y + offset1][pos1.x - 1] && !_stage._data[pos2.y + offset2][pos2.x - 1])
				{
					_stage.puyoVec[0]->Move(InputID::Left);
					_stage.puyoVec[1]->Move(InputID::Left);
				}
			}
			if ((data.first == InputID::Right))
			{
				auto pos1 = _stage.puyoVec[0]->GetGrid(_stage._blocksize);
				auto pos2 = _stage.puyoVec[1]->GetGrid(_stage._blocksize);
				int offset1 = (_stage.puyoVec[0]->pos().y % _stage._blocksize != 0);
				int offset2 = (_stage.puyoVec[1]->pos().y % _stage._blocksize != 0);
				if (!_stage._data[pos1.y + offset1][pos1.x + 1] && !_stage._data[pos2.y + offset2][pos2.x + 1])
				{
					_stage.puyoVec[0]->Move(InputID::Right);
					_stage.puyoVec[1]->Move(InputID::Right);
				}
			}
			if ((data.first == InputID::Btn1))
			{
				Rota(_stage.puyoVec[_targetID]->pos(), _stage.puyoVec[_targetID ^ 1]->pos(), true);
			}
			if ((data.first == InputID::Btn2))
			{
				Rota(_stage.puyoVec[_targetID]->pos(), _stage.puyoVec[_targetID ^ 1]->pos(), false);
			}
		}

	}
	if (CheckPair(0) || CheckPair(1))
	{
		_targetID = 0;
		return true;
	}

	return true;
}

void PlayUnit::Init(void)
{
	_targetID = 0;
	//change_ = { 0,0 };
}

void PlayUnit::Rota(Vector2 vec1, Vector2 vec2, bool RightFlag)
{
	if (_stage._stgmode != StgMode::DROP)
	{
		return;
	}

	auto trun = _stage._blocksize;
	int offset = (_stage.puyoVec[_targetID]->pos().y % _stage._blocksize != 0);
	int tmp = -_stage._blocksize;

	if (!RightFlag)
	{
		trun = -_stage._blocksize;
		tmp = -tmp;
	}
	if (vec1.y < vec2.y)
	{
		_rotPos = Vector2{ vec2.x + trun,vec1.y };
	}
	if (vec1.y > vec2.y)
	{
		_rotPos = Vector2{ vec2.x - trun,vec1.y };
		tmp = -tmp;
	}
	if (vec1.x < vec2.x)
	{
		_rotPos = Vector2{ vec1.x ,vec2.y - trun };
	}
	if (vec1.x > vec2.x)
	{
		_rotPos = Vector2{ vec1.x ,vec2.y + trun };
	}


	auto pos = _stage.ConvertGrid(std::move(_rotPos));
	auto num1 = std::move(_rotPos);

	if (!_stage._data[pos.x][pos.y + offset])
	{
		_stage.puyoVec[_targetID ^ 1]->pos(num1);
	}
	else
	{
		auto _rotPos2 = _rotPos;
		if (pos.y >= 14 - 2)
		{
			_rotPos.y -= abs(tmp);
			_rotPos2.y -= abs(tmp * 2);
		}
		else
		{
			_rotPos.x += tmp;
			_rotPos2.x += tmp + tmp;
		}

		auto num2 = std::move(_rotPos2);
		pos = _stage.ConvertGrid(std::move(_rotPos));
		auto pos2 = _stage.ConvertGrid(std::move(_rotPos2));
		if (!_stage._data[pos.x][pos.y + offset] && !_stage._data[pos2.x][pos2.y + offset])
		{
			_stage.puyoVec[_targetID ^ 1]->pos(num1);
			_stage.puyoVec[_targetID]->pos(num2);
		}
	}
	if (_stage.puyoVec[0]->pos().y > _stage.puyoVec[1]->pos().y)
	{
		std::swap(*_stage.puyoVec[_targetID], *_stage.puyoVec[_targetID ^ 1]);
		_targetID ^= 1;
	}

}
