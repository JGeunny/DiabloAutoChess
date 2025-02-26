#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Loading.h"
#include "Title.h"
#include "WorldMap.h"
#include "BattleField.h"
#include "LeadershipMgr.h"
#include "Ending.h"
/*#include "MyMenu.h"
#include "MyEdit.h"
#include "Stage1.h"
#include "Stage2.h"*/

IMPLEMENT_SINGLETON(CSceneMgr)
CSceneMgr::CSceneMgr()
	:m_pScrollMgr(CScrollMgr::GetInstance())
	, m_pScene(nullptr)
	, m_eCurScene(ENUM::Scene::NONE)
	, m_eNextScene(ENUM::Scene::NONE)
{
	Initialize();
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(ENUM::Scene _eScene)
{
	m_eNextScene = _eScene;
}

HRESULT CSceneMgr::ExecuteSceneChange()
{
	if (m_eCurScene != m_eNextScene)
	{
		SafeDelete(m_pScene);
		m_pScrollMgr->InitScroll(0, 0);
		switch (m_eNextScene)
		{
		case ENUM::Scene::LOADING:
			m_pScene = CLoading::Create();
			break;
		case ENUM::Scene::TITLE:
			m_pScene = CTitle::Create();
			break;
		case ENUM::Scene::WORLDMAP:
			m_pScene = CWorldMap::Create();
			break;
		case ENUM::Scene::BATTLEFIELD:
			m_pScene = CBattleField::Create();
			break;
		case ENUM::Scene::STAGE1:
			//m_pScene = CStage1::Create();
			break;
		case ENUM::Scene::STAGE2:
			//m_pScene = CStage2::Create();
			break;
		case ENUM::Scene::EDIT:
			//m_pScene = CMyEdit::Create();
			break;
		case ENUM::Scene::ENDING:
			m_pScene = CEnding::Create();
			break;
		default:
			break;
		}
		m_eCurScene = m_eNextScene;
	}
	NULL_CHECK_RETURN(m_pScene, E_FAIL);
	return S_OK;
}

bool CSceneMgr::Initialize()
{
	
	return true;
}

void CSceneMgr::Update()
{
	if (!m_pScene) return;
	m_pScene->Update();
	CLeadershipMgr::GetInstance()->Update();
}

void CSceneMgr::LateUpdate()
{
	HRESULT hr = ExecuteSceneChange();
	FAILED_CHECK_MSG(hr, L"Scene Change Failed");
	if (!m_pScene) return;
	m_pScene->LateUpdate();
	CLeadershipMgr::GetInstance()->LateUpdate();
}

void CSceneMgr::Render()
{
	if (!m_pScene) return;
	m_pScene->Render();
	CLeadershipMgr::GetInstance()->Render();
}

void CSceneMgr::Release()
{
	SafeDelete(m_pScene);
	m_pScrollMgr->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CLeadershipMgr::GetInstance()->DestroyInstance();
}
