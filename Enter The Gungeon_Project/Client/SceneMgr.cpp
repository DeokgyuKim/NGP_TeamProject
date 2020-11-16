#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"

#include "KeyMgr.h"

#include "Logo.h"
#include "Intro.h"
#include "ETGMenu.h"
#include "ETGStage.h"
#include "ETGEdit.h"
#include "ETGBoss.h"
#include "Ending.h"

CSceneMgr::CSceneMgr()
	: m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
	, m_pScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}


CSceneMgr*	CSceneMgr::m_pInstance = NULL;
void CSceneMgr::Update()
{
	m_pScene->Update();
}
void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}
void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}
void CSceneMgr::Release()
{
	SAFE_DELETE(m_pScene);
}
void CSceneMgr::SceneChange(SCENEID eNextScene)
{
	m_eNextScene = eNextScene;
	if (m_eNextScene != m_eCurScene)
	{
		SAFE_DELETE(m_pScene);
		switch (m_eNextScene)
		{
		case CSceneMgr::SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case CSceneMgr::SCENE_INTRO:
			m_pScene = new CIntro;
			break;
		case CSceneMgr::SCENE_MENU:
			m_pScene = new CETGMenu;
			break;
		case CSceneMgr::SCENE_STAGE:
			m_pScene = new CETGStage;
			break;
		case CSceneMgr::SCENE_BOSS:
			m_pScene = new CETGBoss;
			break;
		case CSceneMgr::SCENE_ENDING:
			m_pScene = new CEnding;
			break;
		case CSceneMgr::SCENE_EDIT:
			m_pScene = new CETGEdit;
			break;
		case CSceneMgr::SCENE_END:
			break;
		default:
			break;
		}
		m_pScene->Initiailize();
		m_eCurScene = m_eNextScene;
	}
}
