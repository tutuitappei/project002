#include<DxLib.h>
#include "main.h"
#include"Scene/Scenemanager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		SetGraphMode(960, 480, 16);								// 640*480�ޯāA65536�FӰ�ނɐݒ�
		ChangeWindowMode(true);									// true:window false:�ٽ�ذ�

		SetWindowText("PUYOPUYO���Ȃ���`��");
		if (DxLib_Init() == -1)									// DXײ���؂̏���������
		{
			return false;
		}
		lpScene.Run();
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

