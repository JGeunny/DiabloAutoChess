// BottomView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "BottomView.h"


// CBottomView

IMPLEMENT_DYNCREATE(CBottomView, CView)

CBottomView::CBottomView()
{

}

CBottomView::~CBottomView()
{
}

BEGIN_MESSAGE_MAP(CBottomView, CView)
END_MESSAGE_MAP()


// CBottomView 그리기입니다.

void CBottomView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CBottomView 진단입니다.

#ifdef _DEBUG
void CBottomView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBottomView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBottomView 메시지 처리기입니다.


void CBottomView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CEditMgr::GetInstance()->SetBottomView(this);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
