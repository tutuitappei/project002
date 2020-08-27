#include<DxLib.h>
#include "Title.h"
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Stage.h"
#include "Game.h"

Title::Title()
{
	TitleBG = LoadGraph("image/T_BG.png");
	TitleLogo = LoadGraph("image/TitleLog.png");
	pos = {192,128};
}

Title::~Title()
{
}

void Title::Updata()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		lpScene.ChangeScene(SCENE::GAME);
	}
	else
	{
		lpScene.ChangeScene(SCENE::TITLE);
	}
}

void Title::Draw()
{
	DrawBox(50, 50, 100, 100, 0xff00ff, true);
	DrawGraph(0,0, TitleBG,true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, lpScene.colortimer);
	DrawGraph(pos.x, pos.y-(lpScene.colortimer/5), TitleLogo, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}
