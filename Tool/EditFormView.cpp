// EditFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "EditFormView.h"

#include "MapTool.h"
#include "ObjTool.h"
#include "MixTool.h"

// CEditFormView

IMPLEMENT_DYNCREATE(CEditFormView, CFormView)

CEditFormView::CEditFormView()
	: CFormView(IDD_EDITFORMVIEW)
	, m_pMapTool(nullptr)
	, m_pObjTool(nullptr)
	, m_pMixTool(nullptr)
{

}

CEditFormView::~CEditFormView()
{
	Release();
}

void CEditFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabSelect);
}

BEGIN_MESSAGE_MAP(CEditFormView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CEditFormView::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CEditFormView �����Դϴ�.

#ifdef _DEBUG
void CEditFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CEditFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CEditFormView �޽��� ó�����Դϴ�.


void CEditFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CEditMgr::GetInstance()->SetEditFormView(this);
	CScrollView::SetScrollSizes(MM_TEXT, CSize(0,0));
	Initialize();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

HRESULT CEditFormView::Initialize()
{
	static CFont font;
	font.CreatePointFont(140, L"����ü");
	GetDlgItem(IDC_TAB1)->SetFont(&font);

	CRect rtEditForm;
	CEditFormView::GetWindowRect(rtEditForm);
	m_tabSelect.MoveWindow(0, 0, rtEditForm.Width(), rtEditForm.Height());

	m_pMapTool = new CMapTool;
	m_pObjTool = new CObjTool;
	m_pMixTool = new CMixTool;

	m_tabSelect.InsertItem(0, L"����");
	m_tabSelect.InsertItem(1, L"������Ʈ��");
	m_tabSelect.InsertItem(2, L"������");

	if (nullptr == m_pMapTool->GetSafeHwnd())
		m_pMapTool->Create(IDD_MAPTOOL, &m_tabSelect);
	if (nullptr == m_pObjTool->GetSafeHwnd())
		m_pObjTool->Create(IDD_OBJTOOL, &m_tabSelect);
	if (nullptr == m_pMixTool->GetSafeHwnd())
		m_pMixTool->Create(IDD_MIXTOOL, &m_tabSelect);

	CRect rtTab;
	m_tabSelect.GetWindowRect(&rtTab);
	m_pMapTool->MoveWindow(0, 30, rtTab.Width(), rtTab.Height());
	m_pObjTool->MoveWindow(0, 30, rtTab.Width(), rtTab.Height());
	m_pMixTool->MoveWindow(0, 30, rtTab.Width(), rtTab.Height());

	m_tabSelect.SetCurSel(0);
	m_eTabState = TabState::MAPTOOL;
	ChangeTab();

	return S_OK;
}

void CEditFormView::Release()
{
	SafeDelete(m_pMapTool);
	SafeDelete(m_pObjTool);
	SafeDelete(m_pMixTool);
}

void CEditFormView::Refresh()
{
	this->Invalidate(FALSE);
}

void CEditFormView::ChangeTab()
{
	m_pMapTool->ShowWindow(SW_HIDE);
	m_pObjTool->ShowWindow(SW_HIDE);
	m_pMixTool->ShowWindow(SW_HIDE);
	switch (m_eTabState)
	{
	case CEditFormView::TabState::MAPTOOL:
		m_pMapTool->ShowWindow(SW_SHOW);
		CEditMgr::GetInstance()->SetEditState(CEditMgr::EditState::MAPTOOL);
		break;
	case CEditFormView::TabState::OBJTOOL:
		m_pObjTool->ShowWindow(SW_SHOW);
		CEditMgr::GetInstance()->SetEditState(CEditMgr::EditState::UNITTOOL);
		break;
	case CEditFormView::TabState::MIXTOOL:
		m_pMixTool->ShowWindow(SW_SHOW);
		CEditMgr::GetInstance()->SetEditState(CEditMgr::EditState::MIXTOOL);
		break;
	default:
		break;
	}
	CEditMgr::GetInstance()->ChangeEditState();
}


void CEditFormView::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	m_eTabState = (TabState)m_tabSelect.GetCurSel();
	switch (m_eTabState)
	{
	case CEditFormView::TabState::MAPTOOL:
		break;
	case CEditFormView::TabState::OBJTOOL:
		break;
	case CEditFormView::TabState::MIXTOOL:
		break;
	default:
		break;
	}
	ChangeTab();
	m_tabSelect.UpdateWindow();
}
