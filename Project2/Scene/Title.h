#pragma once
#include "BaseScene.h"
#include"../Vector2.h"
#include"../input/Controller.h"
class Title :
	public BaseScene
{
public:
	Title();
	~Title();
	void Updata() override;
	void Draw() override;
private:
	int TitleBG;
	int TitleLogo;

	std::unique_ptr<Controller> controller;
	Vector2 pos;
};

