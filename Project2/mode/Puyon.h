#pragma once
#include"../Stage.h"

struct Puyon
{
	bool operator() (Stage& stage)
	{
		bool puyonFlag = false;

		for (auto puyo : stage.puyoVec)
		{
			puyonFlag &= puyo->CheckPuyon();
		}

		if (!puyonFlag)
		{
			stage._stgmode = StgMode::ERASE;
		}
		return true;
	};
	
};
