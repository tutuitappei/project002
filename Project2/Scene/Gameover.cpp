#include<DxLib.h>
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Stage.h"
#include "Title.h"
#include"Gameover.h"

void Gameover::Updata()
{
	if (CheckHitKey(KEY_INPUT_0))
	{
		lpScene.ChangeScene(SCENE::TITLE);
		lpScene._endfrag = true;
	}
	if (lpScene.colortimer != 0)
	{
		lpScene.colortimer = 0;
	}
	
}

void Gameover::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "KEY_INPUT_0 Å® GAME END");
}
