// ObjListView.cpp : ���� �����Դϴ�.
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


// CObjListView �׸����Դϴ�.

void CObjListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CObjListView �����Դϴ�.

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


// CObjListView �޽��� ó�����Դϴ�.


void CObjListView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CEditMgr::GetInstance()->SetObjListView(this);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
