#pragma once
#include"Vector2.h"
#include"Stage.h"

class PlayUnit
{
public:
	PlayUnit();
	PlayUnit(Stage& stage);
	~PlayUnit();
	void Updata(Vector2 vec1, Vector2 vec2, bool RightFlag);
private:
	void Init(void);

	int _targetID;
	Stage _stage;
	Vector2 _rotPos;
};

