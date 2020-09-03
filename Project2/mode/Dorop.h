#pragma once
#include"../Stage.h"
#include"Fall.h"

struct Dorop
{
	bool operator() (Stage& stage)
	{
		stage._stagetype[StgMode::MOVE](stage);
		stage._playunit->Updata();
		return true;
	};
};
