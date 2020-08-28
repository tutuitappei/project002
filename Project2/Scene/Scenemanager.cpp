#include<DxLib.h>
#include"../Vector2.h"
#include "SceneManager.h"
#include"Title.h"
#include"Game.h"
#include"Gameover.h"

#define lpScene SceneManager::GetInstance()
BaseScene* SceneManager::m_pScene = NULL;

void SceneManager::Run(void)
{
	//for(auto&& ����:�~�~ )
	//{
	//}

	SetDrawScreen(DX_SCREEN_BACK);							// �`�����ޯ��ޯ̧�ɐݒ�
	ClsDrawScreen();										// ��ʂ̏���

	m_pScene->Draw();
	m_pScene->Updata();
	if (colortimer < 510)
	{
		colortimer++;
	}
	time++;
}

void SceneManager::ChangeScene(SCENE scene)
{
	if (m_pScene != NULL)
	{
		delete m_pScene;
	}
	switch (scene)
	{
	case SCENE::TITLE:
		m_pScene = new Title();
		break;
	case SCENE::GAME:
		m_pScene = new Game();
		break;
	case SCENE::GAMEOVER:
		m_pScene = new Gameover();
		break;
	default:
		break;
	}
}

bool SceneManager::Endflag(void)
{
	return _endfrag;
}

SceneManager::SceneManager() : pos(75, 70), screensize(960, 480), screenOffset(64, 32), time(0), color(0xffffff), colortimer(0)
{
	_endfrag = false;
	m_pScene = new Title();
}

SceneManager::~SceneManager()
{
}
