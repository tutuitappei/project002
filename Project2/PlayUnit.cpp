#include"PlayUnit.h"
#include"Stage.h"
#include"puyo/Puyo.h"

PlayUnit::PlayUnit(Stage& stage):_stage(stage)
{
	_targetID = 0;
	Init();
}

PlayUnit::~PlayUnit()
{
}

bool PlayUnit::Updata(void)
{
	// ‘Š•û‚ª’…’n‚µ‚Ä‚¢‚È‚¢‚©Áª¯¸
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
		// ’…’nŽžÀ°¹Þ¯ÄØ¾¯Ä
		_targetID = 0;
		return true;
	}
	// ‘€ì‚µ‚Ä‚¢‚é‚º‚Á
	//playErea_.puyoList_[targetID_]->playPuyo(true);
	// ŽŸ‚Ü‚Å‚É‚Í’¼‚· —ŽG‚È‘€ìØ‚è‘Ö‚¦
	//change_.first = change_.second;
	//change_.second = CheckHitKey(changeKey_[playErea_.playerID()]);
	//if (!change_.first && change_.second)
	//{
	//	++playErea_.inputID_;
	//}
	return true;
}

void PlayUnit::Init(void)
{
	_targetID = 0;
	//change_ = { 0,0 };
	_keyFun.try_emplace(InputID::Up, [&]() {
		});
	// Še“ü—Í—pŠÖ”“o˜^ ‚È‚ñ‚©‚Ü‚Æ‚ß‚ê‚»‚¤Š´–žÚ
	/*_keyFun.try_emplace(InputID::Down, [&]() {
		if ((*_stage.input_[playErea_.inputID_])->GetKeySty(InputID::Down))
		{
			_stage.puyoVec[0]->SoftDrop();
			_stage.puyoVec[1]->SoftDrop();
		}
		});
	_keyFun.try_emplace(InputID::Left, [&]() {
		
		if ((*playErea_.input_[playErea_.inputID_])->GetKeyTrg(InputID::Left))
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
		});
	_keyFun.try_emplace(InputID::Right, [&]() {

		if ((*playErea_.input_[playErea_.inputID_])->GetKeyTrg(InputID::Right))
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
		});
	_keyFun.try_emplace(InputID::Btn1, [&]() {
		if ((*playErea_.input_[playErea_.inputID_])->GetKeyTrg(InputID::Btn1))
		{
			Rota(_stage.puyoVec[_targetID]->pos(), _stage.puyoVec[_targetID ^ 1]->pos(), true);
		}
		});
	_keyFun.try_emplace(InputID::Btn2, [&]() {
		if ((*playErea_.input_[playErea_.inputID_])->GetKeyTrg(InputID::Btn2))
		{
			Rota(_stage.puyoVec[_targetID]->pos(), _stage.puyoVec[_targetID ^ 1]->pos(), false);
		}
		});*/


}

void PlayUnit::Rota(Vector2 vec1, Vector2 vec2, bool RightFlag)
{
	if (_stage._stgmode != StgMode::DROP)
	{
		return;
	}





	if (RightFlag)
	{

	}
	if (vec1.y < vec2.y)
	{

	}
	if (vec1.y > vec2.y)
	{

	}
	if (vec1.x < vec2.x)
	{

	}
	if (vec1.x > vec2.x)
	{

	}


}
