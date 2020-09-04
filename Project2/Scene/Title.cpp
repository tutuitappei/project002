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

	if (CheckHitKey(KEY_INPUT_0))
	{
		lpScene._endfrag = true;
	}
	if (lpScene.colortimer < 510)
	{
		lpScene.colortimer++;
	}
}

void Title::Draw()
{
	DrawGraph(0,0, TitleBG,true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, lpScene.colortimer/2);
	DrawGraph(pos.x, pos.y-(lpScene.colortimer/10), TitleLogo, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	DrawFormatString(400, 400, 0xffffff, "START SPACE GAME");
}
