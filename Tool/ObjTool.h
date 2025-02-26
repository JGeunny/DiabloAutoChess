#pragma once
#include "afxwin.h"


// CObjTool 대화 상자입니다.
class CVirtualObject;
class CObjTool : public CDialog
{
	DECLARE_DYNAMIC(CObjTool)

public:
	CObjTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJTOOL };
#endif

protected://Virtual Funtion
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	
public://Message Function
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLbnSelchangeObjImageList();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedAddData();
	afx_msg void OnBnClickedDelData();

public:
	void		InitObjList();
	void		DrawPicture();

	void		AddData();
	void		DelData();
	OBJ_INFO	GetData();
	bool		GetMapData(OBJ_INFO&);
	void		SetData(CString& _strObjName);
	void		SetData(OBJ_INFO& _tObjData);
	void		Release();

	void		Refresh();

public:
	HRESULT		SaveData(const TCHAR * pFilePath);
	HRESULT		LoadData(const TCHAR * pFilePath);

public:
	CStatic		m_picObjImage;
	CListBox	m_lstObjImageList;
	CComboBox	m_cboObjType;
	CComboBox	m_cboTeam;
	CComboBox	m_cboJob;

public:
	CString		m_strObjImage;
	float		m_fSizeX;
	float		m_fSizeY;
	float		m_fColSizeX;
	float		m_fColSizeY;
	float		m_fLandSizeX;
	float		m_fLandSizeY;
	float		m_fPosFitX;
	float		m_fPosFitY;
	CString		m_strObjName;
	float		m_fAtt;
	float		m_fRecogDist;
	int			m_iHp;
	int			m_iMp;
	int			m_iLevel;
	int			m_iCritical;
	int			m_iLeaderShip;
	int			m_iGold;

public:
	CVirtualObject*							m_pVirtualObject;
	std::map<CString, OBJ_INFO>				m_mapObjData;
	
};
