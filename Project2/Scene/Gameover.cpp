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
	}
}

void Gameover::Draw()
{
}
