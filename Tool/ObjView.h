#pragma once


// CObjView ���Դϴ�.
class CVirtualObject;
class CTile;
class CObjView : public CView
{
	DECLARE_DYNCREATE(CObjView)

protected:
	CObjView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CObjView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected://Virtual Funtion
	virtual void OnInitialUpdate();

public://Message Function
	DECLARE_MESSAGE_MAP()	

public:
	void SetData(OBJ_INFO& _tData);

public:
	OBJ_INFO		m_tObjInfo;
	CVirtualObject*	m_pVirtualObject;
	CTile*			m_pTile;
};


