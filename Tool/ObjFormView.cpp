// ObjFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjFormView.h"
#include "EditFormView.h"
#include "MapTool.h"
#include "ObjTool.h"
#include "ObjView.h"
#include "ToolView.h"
#include "Tile.h"

#include "Terrain.h"

// CObjFormView

IMPLEMENT_DYNCREATE(CObjFormView, CFormView)

CObjFormView::CObjFormView()
	: CFormView(IDD_OBJFORMVIEW)
	, m_strTitle(_T(""))
	, m_strSaveFileName(_T("Map0.dat"))
{

}

CObjFormView::~CObjFormView()
{
}

void CObjFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_lstObj);
	DDX_Control(pDX, IDC_BUTTON1, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON4, m_btnLoad);
	DDX_Control(pDX, IDC_STEXT, m_txtTitle);
	DDX_Text(pDX, IDC_STEXT, m_strTitle);
}

BEGIN_MESSAGE_MAP(CObjFormView, CFormView)
	ON_LBN_SELCHANGE(IDC_LIST3, &CObjFormView::OnLbnSelchangeList)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjFormView::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CObjFormView::OnBnClickedLoad)
END_MESSAGE_MAP()


// CObjFormView �����Դϴ�.

#ifdef _DEBUG
void CObjFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CObjFormView �޽��� ó�����Դϴ�.


void CObjFormView::InitDataLoad()
{
	HRESULT hr;
	TCHAR szCurDir[MAX_STR] = L"";
	CString strPathName;

	GetCurrentDirectory(MAX_STR, szCurDir);
	PathRemoveFileSpec(szCurDir);
	lstrcat(szCurDir, L"\\Data\\");

	strPathName = szCurDir;
	strPathName += L"Map0.dat";
	hr = CEditMgr::GetInstance()->GetTerrain()->LoadData(strPathName);
	FAILED_CHECK_MSG(hr, L"Map Data Load Failed");
	//m_pBottomView->m_MapTool.InitObjList();

	strPathName = szCurDir;
	strPathName += L"Obj0.dat";
	hr = CEditMgr::GetInstance()->GetEditFormView()->m_pObjTool->LoadData(strPathName);
	FAILED_CHECK_MSG(hr, L"Object Data Load Failed");
}

void CObjFormView::InitControlSize()
{
	static CFont font;
	font.CreatePointFont(160, L"����ü");
	GetDlgItem(IDC_STEXT)->SetFont(&font);
	GetDlgItem(IDC_BUTTON1)->SetFont(&font);
	GetDlgItem(IDC_BUTTON4)->SetFont(&font);

	CRect rtObjForm;
	CObjFormView::GetWindowRect(rtObjForm);
	m_txtTitle.MoveWindow(0, 0, rtObjForm.Width(), 30);
	m_lstObj.MoveWindow(0, 30, rtObjForm.Width(), 405);
	m_btnSave.MoveWindow(0, 435, int(rtObjForm.Width() * 0.5), 50);
	m_btnLoad.MoveWindow(int(rtObjForm.Width() * 0.5), 435, int(rtObjForm.Width() * 0.5), 50);
}

void CObjFormView::SetTitleName(LPWSTR _pTitleName)
{
	UpdateData(TRUE);
	m_strTitle = _pTitleName;
	UpdateData(FALSE);
}

void CObjFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CEditMgr::GetInstance()->SetObjFormView(this);
	CScrollView::SetScrollSizes(MM_TEXT, CSize(0, 0));
	InitControlSize();
	//InitDataLoad();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CObjFormView::OnLbnSelchangeList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iSel = m_lstObj.GetCurSel();
	if (iSel < 0) {
		return;
	}
	CString strSel;
	auto eState = CEditMgr::GetInstance()->GetEditState();
	auto pEditFormView = CEditMgr::GetInstance()->GetEditFormView();
	auto pObjView = CEditMgr::GetInstance()->GetObjView();
	auto pToolView = CEditMgr::GetInstance()->GetToolView();

	switch (eState)
	{
	case CEditMgr::EditState::MAPTOOL:
	{
		auto iTileID = pEditFormView->m_pMapTool->m_cboTileType.GetCurSel();
		if (iTileID < 0) iTileID = 0;
		auto& tTile = pObjView->m_pTile->GetTileInfo();
		tTile.eTileID = (ENUM::Tile)iTileID;
		tTile.iImageID = iSel - 1;
		pObjView->m_pTile->SetLineWidth(10.f);
		pObjView->m_pTile->Update();
	}
		break;
	case CEditMgr::EditState::UNITTOOL:
		m_lstObj.GetText(iSel, strSel);
		pEditFormView->m_pObjTool->SetData(strSel);
		pEditFormView->m_pObjTool->Refresh();
		pObjView->SetData(pEditFormView->m_pObjTool->GetData());
		pToolView->SetData(pEditFormView->m_pObjTool->GetData());
		//m_pObjView->SetData(pEditFormView->m_pObjTool->GetData());
		//m_pObjView->m_pImageKey = pEditFormView->m_pObjTool->m_mapObjData[strSel].szFrameKey;
		//pEditFormView->m_UnitTool.GetMapData(m_pToolView->m_tObjData);
		break;
	case CEditMgr::EditState::MIXTOOL:
		break;
	case CEditMgr::EditState::END:
		break;
	default:
		break;
	}
	//m_pObjView->Invalidate(FALSE);
}


void CObjFormView::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ���� �Ǵ� ���⿡ �ʿ��� ��ȭ���ڸ� �����ϴ� MFC Ŭ����.
	CFileDialog Dlg(
		FALSE,	/* ���� TRUE, ���� FALSE */
		L"dat", /* ����Ʈ Ȯ���� */
		m_strSaveFileName, /* ����Ʈ �����̸� */
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", /* ���� ���� */
		this /* �θ� ������ */);

	TCHAR szCurDir[MAX_STR] = L"";

	// ���� �۾� ��θ� ������ �Լ�.
	GetCurrentDirectory(MAX_STR, szCurDir);
	//AfxMessageBox(szCurDir);

	// ��� �� ���ϸ��� �����ϴ� �Լ�. ������ ���ϸ��� ���ٸ� ���� �������� ������.
	PathRemoveFileSpec(szCurDir);
	//AfxMessageBox(szCurDir);

	lstrcat(szCurDir, L"\\Data");

	// ��ȭ���ڸ� ������ �� �ʱ� ��� ����.
	Dlg.m_ofn.lpstrInitialDir = szCurDir; // ������

										  // ��޸���: ���� â �Ӹ� �ƴ϶� �ٸ� â���� ������� ����. (Create)
										  // ���: ������� ���� â���� ����. (DoModal)
	HRESULT hr;
	if (IDOK == Dlg.DoModal())
	{
		switch (CEditMgr::GetInstance()->GetEditState())
		{
		case CEditMgr::EditState::MAPTOOL:
			hr = CEditMgr::GetInstance()->GetTerrain()->SaveData(Dlg.GetPathName());
			FAILED_CHECK_MSG(hr, L"Map Data Save Failed");
			break;
		case CEditMgr::EditState::UNITTOOL:
			hr = CEditMgr::GetInstance()->GetEditFormView()->
				m_pObjTool->SaveData(Dlg.GetPathName());
			FAILED_CHECK_MSG(hr, L"Unit Data Save Failed");
			break;
		case CEditMgr::EditState::MIXTOOL:
			break;
		case CEditMgr::EditState::END:
			break;
		default:
			break;
		}
	}
}


void CObjFormView::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.	
	CFileDialog Dlg(
		TRUE,	/* ���� TRUE, ���� FALSE */
		L"dat", /* ����Ʈ Ȯ���� */
		m_strSaveFileName, /* ����Ʈ �����̸� */
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"All Files(*.*)|*.*|Data Files(*.dat)|*.dat||", /* ���� ���� */
		this /* �θ� ������ */);

	TCHAR szCurDir[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szCurDir);
	PathRemoveFileSpec(szCurDir);
	lstrcat(szCurDir, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szCurDir;

	HRESULT hr;
	if (IDOK == Dlg.DoModal())
	{
		switch (CEditMgr::GetInstance()->GetEditState())
		{
		case CEditMgr::EditState::MAPTOOL:
			hr = CEditMgr::GetInstance()->GetTerrain()->LoadData(Dlg.GetPathName());
			FAILED_CHECK_MSG(hr, L"Map Data Load Failed");
			break;
		case CEditMgr::EditState::UNITTOOL:
			hr = CEditMgr::GetInstance()->GetEditFormView()->
				m_pObjTool->LoadData(Dlg.GetPathName());
			FAILED_CHECK_MSG(hr, L"Unit Data Load Failed");
			break;
		case CEditMgr::EditState::MIXTOOL:
			break;
		case CEditMgr::EditState::END:
			break;
		default:
			break;
		}
	}
}
