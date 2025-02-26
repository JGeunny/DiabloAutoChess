#pragma once


// CObjView 뷰입니다.
class CVirtualObject;
class CTile;
class CObjView : public CView
{
	DECLARE_DYNCREATE(CObjView)

protected:
	CObjView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CObjView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
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


