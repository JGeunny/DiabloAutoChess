                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"

#include "MainFrm.h"
#include "ObjFormView.h"
#include "MiniView.h"

#include "EditFormView.h"
#include "MapTool.h"

#include "Terrain.h"
#include "VirtualObject.h"
#include "ObjView.h"
#include "Tile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
	:m_pTerrain(nullptr)
	, m_pVirtualObject(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pVirtualObject = CVirtualObject::Create();

}

CToolView::~CToolView()
{
	SafeDelete(m_pVirtualObject);
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	SynchronizationScroll();

	//DRAW_INFO tVirtualObj;
	//tVirtualObj.SetData(m_tObjData.tDraw);
	//tVirtualObj.SetTexInfo(CTextureMgr::GetInstance()->GetTexInfo(m_tObjData.szFrameKey));
	//tVirtualObj.vPos -= CScrollMgr::AlterScroll();
	//tVirtualObj.color = D3DCOLOR_ARGB(180, 255, 255, 255);
	//tVirtualObj.matCurrent = tVirtualObj.GetMatrixWorld();

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CDeviceMgr::GetInstance()->Render_Begin();

	CEditMgr::GetInstance()->Render();

	//CDeviceMgr::GetInstance()->DrawImage(tVirtualObj);
	m_pVirtualObject->Render_Scroll();
	CDeviceMgr::GetInstance()->Render_End(m_hWnd);

}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CScrollView::SetScrollSizes(MM_TEXT, CSize(0, 0));
	g_hWnd = m_hWnd;
	CEditMgr::GetInstance()->SetToolView(this);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// GetWindowRect함수: 테두리를 포함한 전체 윈도우 렉트를 얻어옴. 이 때 좌표는 스크린 좌표 기준.
	// GetClientRect함수: 테두리를 미포함한 클라이언트 영역을 얻어옴. 이 때 좌표는 클라이언트 좌표 기준.
	CMainFrame* pFrameWnd = CEditMgr::GetInstance()->GetMainFrame();
	RECT rcFrame = {};	
	pFrameWnd->GetWindowRect(&rcFrame);
	::SetRect(&rcFrame, 0, 0, rcFrame.right - rcFrame.left, rcFrame.bottom - rcFrame.top);

	RECT rcView = {};
	GetClientRect(&rcView);

	// 현재 프레임윈도우와 뷰의 x, y 간격.
	int iCX = int(rcFrame.right - rcView.right);
	int iCY = int(rcFrame.bottom - rcView.bottom + 400.f / WINCX * WINCY);

	// FrameWnd 위치, 크기 재조정.
	pFrameWnd->SetWindowPos(nullptr, 0, 0, WINCX + iCX, WINCY + iCY, SWP_NOZORDER);


	HRESULT hr = CDeviceMgr::GetInstance()->InitDevice(
		WINCX, WINCY, CDeviceMgr::MODE_WIN);
	FAILED_CHECK_MSG(hr, L"InitDevice Failed");

	hr = CEditMgr::GetInstance()->Initialize();
	FAILED_CHECK(hr);
	
	m_pTerrain = CEditMgr::GetInstance()->GetTerrain();
	CScrollView::SetScrollSizes(MM_TEXT, CSize(m_pTerrain->GetMapCX(), m_pTerrain->GetMapCY()));
	CObjMgr::GetInstance()->AddObject(ENUM::MapType::TERRAIN, m_pTerrain);
	CGameObject* pObj = CVirtualObject::Create(500, 500, 270);
	CObjMgr::GetInstance()->AddObject(ENUM::ObjType::UNIT, pObj);

}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonDown(nFlags, point);
	SynchronizationScroll();
	SynchronizationMouse(point);
	int iSel = -1;
	auto eState = CEditMgr::GetInstance()->GetEditState();
	auto pMapTool = CEditMgr::GetInstance()->GetEditFormView()->m_pMapTool;
	switch (eState)
	{
	case CEditMgr::EditState::MAPTOOL:
		iSel = CEditMgr::GetInstance()->GetObjFormView()->m_lstObj.GetCurSel();
		if (-1 == iSel) return;
		CEditMgr::GetInstance()->GetTerrain()->TileChange(m_vMouse, iSel - 1, pMapTool->m_eTileID);
		break;
	case CEditMgr::EditState::UNITTOOL:
		if (m_pVirtualObject->GetVisible()) //유닛 놓을수 있는 상태
		{
			CVirtualObject* pObj = CreateObj();
			pObj->GetStatusInfo().FnRecovery();
			CEditMgr::GetInstance()->GetTerrain()->AddObject(pObj);
		}
		else //아닐 경우 맵위에 있는 유닛 편집
		{
			int idx = m_pTerrain->GetObjIndex(m_vMouse);
			if (idx > -1) {
				m_pTerrain->GetVirtualObjVec()[idx]->SetSelect(true);
			}
		}
		break;
	case CEditMgr::EditState::MIXTOOL:
		break;
	case CEditMgr::EditState::END:
		break;
	default:
		break;
	}
	Refresh();
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnMouseMove(nFlags, point);
	SynchronizationScroll();
	SynchronizationMouse(point);
	
	auto eState = CEditMgr::GetInstance()->GetEditState();
	auto pMapTool = CEditMgr::GetInstance()->GetEditFormView()->m_pMapTool;

	//타일위에 유닛 놓기
	int iSel = m_pTerrain->GetTileIndex(m_vMouse);
	if (iSel > -1)
	{
		m_vMouse = m_pTerrain->GetTileVec()[iSel]->GetPos();
	}
	m_pTerrain->ObjFollowMouse(m_vMouse);
	switch (eState)
	{
	case CEditMgr::EditState::MAPTOOL:
		if (CKeyMgr::GetInstance()->KeyPressing(KEY::LBUTTON))
		{
			int iSel = CEditMgr::GetInstance()->GetObjFormView()->m_lstObj.GetCurSel();
			if (-1 == iSel) return;
			CEditMgr::GetInstance()->GetTerrain()->TileChange(m_vMouse, iSel - 1, pMapTool->m_eTileID);
			Refresh();
		}
		break;
	case CEditMgr::EditState::UNITTOOL:
		m_pVirtualObject->SetPos(m_vMouse);
		break;
	case CEditMgr::EditState::MIXTOOL:
		break;
	case CEditMgr::EditState::END:
		break;
	default:
		break;
	}
}

void CToolView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonUp(nFlags, point);
	SynchronizationScroll();
	SynchronizationMouse(point);

	m_pTerrain->InitObjState();
	auto eState = CEditMgr::GetInstance()->GetEditState();
	switch (eState)
	{
	case CEditMgr::EditState::MAPTOOL:
		break;
	case CEditMgr::EditState::UNITTOOL:
		break;
	case CEditMgr::EditState::MIXTOOL:
		break;
	case CEditMgr::EditState::END:
		break;
	default:
		break;
	}
}

void CToolView::SynchronizationScroll()
{
	CScrollMgr::GetInstance()->SetScroll(D3DXVECTOR3(
		(float)CScrollView::GetScrollPos(0)
		, (float)CScrollView::GetScrollPos(1)
		, 0.f));
}

void CToolView::SynchronizationMouse(CPoint point)
{
	m_vMouse = { (float)point.x, (float)point.y, 0.f };
	m_vMouse += CScrollMgr::GetInstance()->GetScroll();
}

void CToolView::Refresh()
{
	this->Invalidate(FALSE);
	CEditMgr::GetInstance()->GetMiniView()->Invalidate(FALSE);
	CEditMgr::GetInstance()->GetObjView()->Invalidate(FALSE);
}

void CToolView::SetData(OBJ_INFO & _tData)
{
	m_tObjInfo = _tData;
	m_pVirtualObject->GetDrawInfo().SetData(m_tObjInfo.tDraw);
	m_pVirtualObject->GetStatusInfo().SetData(m_tObjInfo.tStatus);
	m_pVirtualObject->SetImage(m_tObjInfo.szFrameKey);
	m_pVirtualObject->ChangeState(ENUM::State::IDLE);
	//m_pVirtualObject->SetScale(D3DXVECTOR3(2.f, 2.f, 2.f));
	m_pVirtualObject->SetPos(0, 0);
	m_pVirtualObject->SetAngle(270);
	m_pVirtualObject->SetVisible(true);
	m_pVirtualObject->SetSelect(true);
	this->Invalidate(FALSE);
}

CVirtualObject * CToolView::CreateObj()
{
	CVirtualObject* pObj = CVirtualObject::Create();
	pObj->GetDrawInfo().SetData(m_tObjInfo.tDraw);
	pObj->GetStatusInfo().SetData(m_tObjInfo.tStatus);
	pObj->SetImage(m_tObjInfo.szFrameKey);
	pObj->SetPos(m_pVirtualObject->GetPos());
	pObj->SetAngle(270);
	return pObj;
}
void CToolView::CancleObj()
{
	m_tObjInfo = OBJ_INFO();
	m_pVirtualObject->SetVisible(false);
}


void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnRButtonDown(nFlags, point);
	SynchronizationScroll();
	SynchronizationMouse(point);
	CancleObj();
}


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
	SynchronizationScroll();

	auto eState = CEditMgr::GetInstance()->GetEditState();

	switch (eState)
	{
	case CEditMgr::EditState::MAPTOOL:
		break;
	case CEditMgr::EditState::UNITTOOL:
	{
		if (nChar == VK_DELETE)
		{
			if (!m_pVirtualObject->GetVisible())
			{
				int idx = m_pTerrain->GetObjIndex(m_vMouse);
				if (idx > -1) {
					auto& vecObj = m_pTerrain->GetVirtualObjVec();
					for (auto& iter = vecObj.begin(); iter != vecObj.end(); ++iter)
					{
						if (vecObj[idx] == *iter)
						{
							SafeDelete(*iter);
							vecObj.erase(iter);
							Refresh();
							break;
						}
					}
				}
			}
		}
	}
		break;
	case CEditMgr::EditState::MIXTOOL:
		break;
	case CEditMgr::EditState::END:
		break;
	default:
		break;
	}
}
