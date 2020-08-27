#pragma once
#include "BaseScene.h"
#include"../Vector2.h"
#include"../Stage.h"
#include"../input/Controller.h"
class Game :
	public BaseScene
{
public:
	Game();
	~Game();
	void Updata() override;
	void Draw() override;
private:
	std::unique_ptr<Controller> controller;
	Vector2 pos;
	int BG;

	std::unique_ptr<Stage> stage;
};

