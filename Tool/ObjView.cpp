// ObjView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjView.h"
#include "VirtualObject.h"
#include "Tile.h"

// CObjView

IMPLEMENT_DYNCREATE(CObjView, CView)

CObjView::CObjView()
	:m_pVirtualObject(nullptr)
	, m_pTile(nullptr)
{
	m_pVirtualObject = CVirtualObject::Create();
	m_pTile = CTile::Create();
	m_pTile->SetPos(WINCX*0.5f, WINCY*0.5f);
	m_pTile->SetSize(WINCX, WINCY);
}

CObjView::~CObjView()
{
	SafeDelete(m_pVirtualObject);
	SafeDelete(m_pTile);
}

BEGIN_MESSAGE_MAP(CObjView, CView)
END_MESSAGE_MAP()


// CObjView 그리기입니다.

void CObjView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	CDeviceMgr::GetInstance()->Render_Begin();
	m_pTile->Render();
	m_pVirtualObject->Render();
	CDeviceMgr::GetInstance()->Render_End(m_hWnd);
}


// CObjView 진단입니다.

#ifdef _DEBUG
void CObjView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CObjView 메시지 처리기입니다.


void CObjView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CEditMgr::GetInstance()->SetObjView(this);
}

void CObjView::SetData(OBJ_INFO& _tData)
{
	m_tObjInfo = _tData;
	m_pVirtualObject->GetDrawInfo().SetData(m_tObjInfo.tDraw);
	m_pVirtualObject->GetStatusInfo().SetData(m_tObjInfo.tStatus);
	m_pVirtualObject->SetImage(m_tObjInfo.szFrameKey);
	m_pVirtualObject->ChangeState(ENUM::State::IDLE);
	m_pVirtualObject->SetScale(D3DXVECTOR3(3.f, 3.f, 3.f));
	m_pVirtualObject->SetPos(WINCX * 0.5f, WINCY * 0.5f);
	//m_pVirtualObject->SetSize(WINCX, WINCY);
	m_pVirtualObject->SetAngle(270);
	this->Invalidate(FALSE);
}

