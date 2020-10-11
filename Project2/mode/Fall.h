#pragma once
#include"../Stage.h"


struct Fall
{
	bool operator ()(Stage& stage)
	{
		std::for_each(stage.puyoVec.rbegin(), stage.puyoVec.rend(), [&](Sharepuyo& puyo) {
			stage.Movepuyo(puyo);
			}
		);
		bool eraseFlag = true;
		std::for_each(stage.puyoVec.rbegin(), stage.puyoVec.rend(), [&](Sharepuyo& puyo) {
			if (!puyo->Updata())
			{
				eraseFlag = false;
			}
			});
		if (eraseFlag)
		{
			stage._stgmode = StgMode::PUYON;
		}
		for (auto puyo : stage.puyoVec)
		{
			if (!puyo->Downnow())
			{
				continue;
			}
			auto pos = puyo->GetGrid(stage._blocksize);
			int cnt = 0;
			for (int y = pos.y; y < 14; y++)
			{
				if (stage._data[y][pos.x])
				{
					if (stage._data[y][pos.x]->ReturnID() == PuyoID::Wall|| stage._data[y][pos.x]->ReturnID() == PuyoID::Ojama)
					{

							break;
					}
					//else
					//{
					//	if (!stage._data[y][pos.x]->SetPuyonCnt())
					//	{
					//	break;

					//	}
					//}
				}
				if (++cnt >= 3)
				{
					break;
				}
			}
		}
		return true;
	}
};
