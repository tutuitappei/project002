#include<DxLib.h>
#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		SetGraphMode(960, 480, 16);								// 640*480ÄŞ¯ÄA65536FÓ°ÄŞ‚Éİ’è
		ChangeWindowMode(true);									// true:window false:ÌÙ½¸Ø°İ

		SetWindowText("PUYOPUYO");
		if (DxLib_Init() == -1)									// DX×²ÌŞ×Ø‚Ì‰Šú‰»ˆ—
		{
			return false;
		}
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

