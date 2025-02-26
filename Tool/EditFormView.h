#pragma once
#include "afxcmn.h"



// CEditFormView 폼 뷰입니다.
class CMapTool;
class CObjTool;
class CMixTool;

class CEditFormView : public CFormView
{
	DECLARE_DYNCREATE(CEditFormView)

protected:
	CEditFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CEditFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITFORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	enum class TabState { MAPTOOL, OBJTOOL, MIXTOOL };

protected://Virtual Funtion
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	
public://Message Function
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

private:
	HRESULT			Initialize();
	void			Release();
	void			Refresh();

private:
	void			ChangeTab();

public:
	CMapTool*		m_pMapTool;
	CObjTool*		m_pObjTool;
	CMixTool*		m_pMixTool;

public:
	CTabCtrl		m_tabSelect;
	TabState		m_eTabState;
};


