// BottomView.cpp : ���� �����Դϴ�.
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


// CBottomView �׸����Դϴ�.

void CBottomView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CBottomView �����Դϴ�.

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


// CBottomView �޽��� ó�����Դϴ�.


void CBottomView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CEditMgr::GetInstance()->SetBottomView(this);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
