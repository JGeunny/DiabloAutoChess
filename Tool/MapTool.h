#pragma once
#include "afxwin.h"


// CMapTool 대화 상자입니다.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected://Virtual Funtion
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

public://Message Function
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLbnSelchangeMapList();
	afx_msg void OnCbnSelchangeTileID();
	afx_msg void OnBnClickedApply();

public:
	void		CreateHorizontalScroll();
	void		InitObjList();
	void		DrawPicture();
	OBJ_INFO	GetData();
	
public:
	CListBox	m_lstMap;
	CComboBox	m_cboTileType;
	CStatic		m_picMapView;

public:
	int			m_iMapImageId;
	ENUM::Tile	m_eTileID;
	float		m_fTileX;
	float		m_fTileY;
	float		m_fTileCX;
	float		m_fTileCY;

	

};
