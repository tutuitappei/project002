#pragma once
#include<mutex>
#include"../Vector2.h"
#include"BaseScene.h"

#define lpScene SceneManager::GetInstance()

enum class SCENE {
	TITLE,
	GAME,
	GAMEOVER
};

class SceneManager
{
public:
	static SceneManager& GetInstance()
	{
		static SceneManager sta_Instance;
		return sta_Instance;
	}

	void Run(void);
	static void ChangeScene(SCENE scene);     //シーンを引数によって変える関数

	Vector2 pos;
	const Vector2 screensize;
	const Vector2 screenOffset;

	int colortimer;

	bool _endfrag;
	bool Endflag(void);
private:
	SceneManager();
	~SceneManager();

	int time;
	int color;

	static BaseScene* m_pScene;
	static SceneManager* sta_Instance;
};

