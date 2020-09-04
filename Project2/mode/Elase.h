#pragma once
#include"../Stage.h"


struct Elase
{
	bool operator()(Stage& stage)
	{
		bool delFlag = false;
		for (auto&& dropcd : stage.puyoVec)
		{
			delFlag |= stage.EleseData(dropcd->ReturnID(),dropcd->GetGrid(stage._blocksize));
		}
		if (delFlag)
		{
			stage.Deletopuyo();
			for (auto&& puyo : stage.puyoVec)
			{
				puyo->SetInterval(1);
			}
			stage._stgmode = StgMode::MOVE;
		}
		else
		{
			stage.InstancePuyo();
			stage.Movepuyo(stage.puyoVec[0]);
			stage._stgmode = StgMode::DROP;
		}
		
		return true;
	}
};
