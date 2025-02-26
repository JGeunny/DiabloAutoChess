#pragma once
#include "afxwin.h"



// CObjFormView 폼 뷰입니다.

class CObjFormView : public CFormView
{
	DECLARE_DYNCREATE(CObjFormView)

protected:
	CObjFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CObjFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJFORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected://Virtual Funtion
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

public://Message Function
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

public:
	void InitDataLoad();
	void InitControlSize();
	void SetTitleName(LPWSTR _pTitleName);

public:
	CStatic		m_txtTitle;
	CString		m_strTitle;

	CListBox	m_lstObj;
	CButton		m_btnSave;
	CButton		m_btnLoad;

	CString		m_strSaveFileName;// 세이브를 위한 이름
};


