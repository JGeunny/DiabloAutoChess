// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"

#include "ObjFormView.h"

#include "ToolView.h"
#include "Terrain.h"


// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
	, m_fTileX(TILEX)
	, m_fTileY(TILEY)
	, m_fTileCX(TILECX)
	, m_fTileCY(TILECY)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstMap);
	DDX_Control(pDX, ID_PICTURE, m_picMapView);
	DDX_Control(pDX, IDC_COMBO1, m_cboTileType);
	DDX_Text(pDX, IDC_EDIT2, m_fTileX);
	DDX_Text(pDX, IDC_EDIT3, m_fTileY);
	DDX_Text(pDX, IDC_EDIT4, m_fTileCX);
	DDX_Text(pDX, IDC_EDIT5, m_fTileCY);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_PAINT()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangeMapList)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMapTool::OnCbnSelchangeTileID)
	ON_BN_CLICKED(IDC_BUTTON5, &CMapTool::OnBnClickedApply)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.

void CMapTool::CreateHorizontalScroll()
{
	CString strName = L"";
	CDC* pDC = m_lstMap.GetDC();

	CSize size;
	int iCX = 0;

	for (int i = 0; i < m_lstMap.GetCount(); ++i)
	{
		m_lstMap.GetText(i, strName);
		size = pDC->GetTextExtent(strName);
		if (iCX < size.cx)
		{
			iCX = size.cx;
		}
	}

	if (iCX > m_lstMap.GetHorizontalExtent())
		m_lstMap.SetHorizontalExtent(iCX);

	m_lstMap.ReleaseDC(pDC);
}

void CMapTool::InitObjList()
{
	TCHAR szTile[MIN_STR];
	auto& lstObjFormList = CEditMgr::GetInstance()->GetObjFormView()->m_lstObj;
	
	int iTileCount = CTextureMgr::GetInstance()->GetSize(L"Tile");
	lstObjFormList.ResetContent();

	lstrcpy(szTile, L"NONE");
	lstObjFormList.AddString(szTile);
	for (int i = 0; i < iTileCount; ++i)
	{
		ZeroMemory(szTile, sizeof(szTile));
		swprintf_s(szTile, L"Tile%d", i);
		lstObjFormList.AddString(szTile);
	}
}

void CMapTool::DrawPicture()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iSel = m_lstMap.GetCurSel();
	if (-1 == iSel) return;
	m_iMapImageId = iSel;
	
	CDeviceMgr::GetInstance()->Render_Begin();
	if (0 != iSel)
	{
		DRAW_INFO tTile;
		tTile.vPos = { WINCX*0.5f, WINCY*0.5f, 0.f };
		tTile.vSize = { WINCX, WINCY, 0.f };
		tTile.SetTexInfo(CTextureMgr::GetInstance()->GetTexInfo(RZIMAGE::MAP, m_iMapImageId - 1, 0));
		tTile.matCurrent = tTile.GetMatrixWorld();
		
		CDeviceMgr::GetInstance()->DrawImage(tTile);
	}
	CDeviceMgr::GetInstance()->Render_End(m_picMapView.m_hWnd);
	CEditMgr::GetInstance()->GetTerrain()->SetMapImageID(m_iMapImageId - 1);	
}

OBJ_INFO CMapTool::GetData()
{
	this->UpdateData(TRUE);
	static OBJ_INFO tObjData;
	tObjData.tDraw.vSize.x = m_fTileCX;
	tObjData.tDraw.vSize.y = m_fTileCY;
	m_eTileID = (ENUM::Tile)m_cboTileType.GetCurSel();
	return tObjData;
}


BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	InitObjList();

	m_lstMap.AddString(L"NONE");
	m_lstMap.AddString(L"Map_Boss");
	m_lstMap.AddString(L"Map_Dun1");
	m_lstMap.AddString(L"Map_Dun2");
	m_lstMap.AddString(L"Map_Field");
	m_lstMap.AddString(L"Map_Store");
	m_lstMap.AddString(L"Map_Town");
	m_lstMap.AddString(L"Map_WorldMap");
	m_lstMap.AddString(L"Map_BattleField");
	m_lstMap.SetCurSel(0);

	m_cboTileType.AddString(L"BLANK");
	m_cboTileType.SetItemData(0, (int)ENUM::Tile::BLANK);
	m_cboTileType.AddString(L"BLOCK");
	m_cboTileType.SetItemData(1, (int)ENUM::Tile::BLOCK);
	m_cboTileType.AddString(L"ALLY_STACK");
	m_cboTileType.SetItemData(2, (int)ENUM::Tile::ALLY_STACK);
	m_cboTileType.AddString(L"ALLY_FIELD");
	m_cboTileType.SetItemData(3, (int)ENUM::Tile::ALLY_FIELD);
	m_cboTileType.AddString(L"ENEMY_FIELD");
	m_cboTileType.SetItemData(4, (int)ENUM::Tile::ENEMY_FIELD);
	m_cboTileType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMapTool::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	DrawPicture();
}


void CMapTool::OnLbnSelchangeMapList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	this->Invalidate(FALSE);
}


void CMapTool::OnCbnSelchangeTileID()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_eTileID = (ENUM::Tile)m_cboTileType.GetCurSel();
}


void CMapTool::OnBnClickedApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	this->UpdateData(TRUE);
	auto pToolView = CEditMgr::GetInstance()->GetToolView();
	auto pTerrain = CEditMgr::GetInstance()->GetTerrain();
	pTerrain->CreateTile((int)m_fTileX, (int)m_fTileY, (int)m_fTileCX, (int)m_fTileCY);
	pToolView->CScrollView::SetScrollSizes(MM_TEXT, CSize(pTerrain->GetMapCX(), pTerrain->GetMapCY()));
	//pTerrain->Refresh();
	this->UpdateData(FALSE);
}
