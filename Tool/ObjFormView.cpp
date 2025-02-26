// ObjFormView.cpp : 구현 파일입니다.
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


// CObjFormView 진단입니다.

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


// CObjFormView 메시지 처리기입니다.


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
	font.CreatePointFont(160, L"굴림체");
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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CObjFormView::OnLbnSelchangeList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 저장 또는 열기에 필요한 대화상자를 생성하는 MFC 클래스.
	CFileDialog Dlg(
		FALSE,	/* 열기 TRUE, 저장 FALSE */
		L"dat", /* 디폴트 확장자 */
		m_strSaveFileName, /* 디폴트 파일이름 */
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", /* 파일 형식 */
		this /* 부모 윈도우 */);

	TCHAR szCurDir[MAX_STR] = L"";

	// 현재 작업 경로를 얻어오는 함수.
	GetCurrentDirectory(MAX_STR, szCurDir);
	//AfxMessageBox(szCurDir);

	// 경로 상에 파일명을 제거하는 함수. 제거할 파일명이 없다면 말단 폴더명을 제거함.
	PathRemoveFileSpec(szCurDir);
	//AfxMessageBox(szCurDir);

	lstrcat(szCurDir, L"\\Data");

	// 대화상자를 열었을 때 초기 경로 설정.
	Dlg.m_ofn.lpstrInitialDir = szCurDir; // 절대경로

										  // 모달리스: 현재 창 뿐만 아니라 다른 창에도 제어권이 있음. (Create)
										  // 모달: 제어권이 현재 창에만 있음. (DoModal)
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	CFileDialog Dlg(
		TRUE,	/* 열기 TRUE, 저장 FALSE */
		L"dat", /* 디폴트 확장자 */
		m_strSaveFileName, /* 디폴트 파일이름 */
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"All Files(*.*)|*.*|Data Files(*.dat)|*.dat||", /* 파일 형식 */
		this /* 부모 윈도우 */);

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
