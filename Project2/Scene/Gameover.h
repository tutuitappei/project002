#pragma once
#include "BaseScene.h"
#include"../Vector2.h"
#include"../input/Controller.h"
class Gameover :
	public BaseScene
{
public:
	void Updata() override;
	void Draw() override;
private:
	std::unique_ptr<Controller> controller;
	Vector2 pos;
};

