#pragma once
#include <functional>
#include <map>
#include <utility>
#include"Vector2.h"
#include "input/Inputid.h"

class Stage;

class PlayUnit
{
public:
	PlayUnit(Stage& stage);
	~PlayUnit();
	bool Updata(void);
private:
	void Init(void);
	void Rota(Vector2 vec1, Vector2 vec2, bool RightFlag);
	std::map<InputID, std::function<void(void)>> _keyFun;
	int _targetID;
	Stage& _stage;
	Vector2 _rotPos;
};

