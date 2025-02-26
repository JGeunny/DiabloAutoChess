// ObjListView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjListView.h"


// CObjListView

IMPLEMENT_DYNCREATE(CObjListView, CView)

CObjListView::CObjListView()
{

}

CObjListView::~CObjListView()
{
}

BEGIN_MESSAGE_MAP(CObjListView, CView)
END_MESSAGE_MAP()


// CObjListView 그리기입니다.

void CObjListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CObjListView 진단입니다.

#ifdef _DEBUG
void CObjListView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CObjListView 메시지 처리기입니다.


void CObjListView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CEditMgr::GetInstance()->SetObjListView(this);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
