#pragma once


// CObjListView ���Դϴ�.

class CObjListView : public CView
{
	DECLARE_DYNCREATE(CObjListView)

protected:
	CObjListView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CObjListView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


