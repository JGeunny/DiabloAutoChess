#include "stdafx.h"
#include "MainApp.h"


CMainApp::CMainApp()
	: m_pTimeMgr(CTimeMgr::GetInstance())
	, m_pFrameMgr(CFrameMgr::GetInstance())
	, m_pDeviceMgr(CDeviceMgr::GetInstance())
	, m_pTextureMgr(CTextureMgr::GetInstance())
	, m_pKeyMgr(CKeyMgr::GetInstance())
	, m_pControlMgr(CControlMgr::GetInstance())
	, m_pSceneMgr(CSceneMgr::GetInstance())
{
}


CMainApp::~CMainApp()
{
	Release();
}

void CMainApp::Update()
{
	m_pTimeMgr->UpdateTime();
	m_pKeyMgr->Update();
	m_pSceneMgr->Update();
}

void CMainApp::LateUpdate()
{
	m_pSceneMgr->LateUpdate();
}

void CMainApp::Render()
{
	m_pDeviceMgr->Render_Begin();

	m_pSceneMgr->Render();
	m_pFrameMgr->RenderFPS();

	m_pDeviceMgr->Render_End();
}

HRESULT CMainApp::Initialize()
{
	m_pTimeMgr->InitTime();
	m_pFrameMgr->InitTime();

	HRESULT hr = m_pDeviceMgr->InitDevice(
		//WINCX, WINCY, CDeviceMgr::MODE_WIN);
		WINCX, WINCY, CDeviceMgr::MODE_FULL);
	FAILED_CHECK_MSG_RETURN(hr, L"InitDevice Failed", E_FAIL);

	hr = m_pControlMgr->Initialize();
	FAILED_CHECK_MSG_RETURN(hr, L"ControlMgr Initialize Failed", E_FAIL);
	//hr = m_pTextureMgr->LoadTextureFromImgPathFile(L"../Data/ImgPath.txt");
	//FAILED_CHECK_MSG_RETURN(hr, L"LoadTextureFromImgPathFile Failed", E_FAIL);

	m_pSceneMgr->SceneChange(ENUM::Scene::LOADING);
	//m_pSceneMgr->SceneChange(ENUM::Scene::ENDING);

	return S_OK;
}

void CMainApp::Release()
{
	m_pControlMgr->DestroyInstance();
	m_pSceneMgr->DestroyInstance();
	m_pKeyMgr->DestroyInstance();
	m_pTextureMgr->DestroyInstance();
	m_pDeviceMgr->DestroyInstance();
	m_pFrameMgr->DestroyInstance();
	m_pTimeMgr->DestroyInstance();
	CBulletPoolMgr::GetInstance()->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

