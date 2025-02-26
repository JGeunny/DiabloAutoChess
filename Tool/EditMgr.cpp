#include "stdafx.h"
#include "EditMgr.h"

#include "Terrain.h"

#include "EditFormView.h"
#include "MapTool.h"
#include "ObjTool.h"
#include "MixTool.h"

#include "ToolView.h"
#include "ObjView.h"
#include "VirtualObject.h"
#include "ObjFormView.h"

IMPLEMENT_SINGLETON(CEditMgr)
CEditMgr::CEditMgr()
	: m_pObjMgr(CObjMgr::GetInstance())
	, m_pMainFrame(nullptr)
	, m_pMiniView(nullptr)
	, m_pObjView(nullptr)
	, m_pObjFormView(nullptr)
	, m_pToolView(nullptr)
	, m_pEditFormView(nullptr)
	, m_pTerrain(nullptr)
	, m_eCurEditState(EditState::END)
	, m_eNextEditState(EditState::END)
{
}


CEditMgr::~CEditMgr()
{
	Release();
}

HRESULT CEditMgr::Initialize()
{
	static bool isCreate = false;
	if (isCreate) return S_FALSE;
	isCreate = true;

	m_pTerrain = CTerrain::Create();
	NULL_CHECK_MSG_RETURN(m_pTerrain, L"Terrain Create Failed", S_FALSE);
	return S_OK;
}

void CEditMgr::Release()
{
	SafeDelete(m_pTerrain);
	m_pObjMgr->DestroyInstance();
}

void CEditMgr::Update()
{
	CTimeMgr::GetInstance()->UpdateTime();
	m_pTerrain->Update();
	m_pTerrain->LateUpdate();
	m_pObjMgr->Update();
	m_pObjMgr->LateUpdate();
	

	m_pObjView->m_pVirtualObject->Update();
	m_pObjView->m_pVirtualObject->LateUpdate();

	m_pToolView->m_pVirtualObject->Update();
	m_pToolView->m_pVirtualObject->LateUpdate();

	if (m_pToolView->GetSafeHwnd())
		m_pToolView->Refresh();
}

void CEditMgr::Render(bool _bMiniView)
{
	m_pTerrain->SetMiniView(_bMiniView);
	m_pObjMgr->Render();
}

void CEditMgr::ChangeEditState()
{
	if (!m_pEditFormView->GetSafeHwnd()) return;
	if (!m_pEditFormView->m_pMapTool->GetSafeHwnd()) return;
	if (!m_pEditFormView->m_pObjTool->GetSafeHwnd()) return;
	if (!m_pEditFormView->m_pMixTool->GetSafeHwnd()) return;

	if (m_eCurEditState != m_eNextEditState)
	{
		m_pToolView->m_pVirtualObject->SetVisible(false);
		m_eCurEditState = m_eNextEditState;
		switch (m_eNextEditState)
		{
		case CEditMgr::EditState::MAPTOOL:
			m_pEditFormView->m_pMapTool->InitObjList();
			m_pObjFormView->SetTitleName(L"맵 툴");
			m_pObjFormView->m_strSaveFileName = L"Map0.dat";
			break;
		case CEditMgr::EditState::UNITTOOL:
			m_pEditFormView->m_pObjTool->InitObjList();
			m_pObjFormView->SetTitleName(L"오브젝트 툴");
			m_pObjFormView->m_strSaveFileName = L"Obj0.dat";
			break;
		case CEditMgr::EditState::MIXTOOL:
			m_pEditFormView->m_pMixTool->InitObjList();
			break;
		default:
			break;
		}
	}
}
