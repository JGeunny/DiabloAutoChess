
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "Tool.h"

#include "MainFrm.h"
//Left
#include "MiniView.h"
#include "ObjView.h"
#include "ObjFormView.h"
//Right
#include "ToolView.h"
#include "EditFormView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
	CEditMgr::GetInstance()->DestroyInstance();
	//CControlMgr::GetInstance()-->DestroyInstance();
	//CScenMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CDeviceMgr::GetInstance()->DestroyInstance();
	//CFrameMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CEditMgr::GetInstance()->SetMainFrame(this);

	SetMenu(NULL);					// �޴��� ���ֱ� 
	//ModifyStyle(WS_CAPTION, NULL); // Ÿ��Ʋ�� ���ֱ�

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("���� ������ ������ ���߽��ϴ�.\n");
	//	return -1;      // ������ ���߽��ϴ�.
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
	//	return -1;      // ������ ���߽��ϴ�.
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_spltMain.CreateStatic(this, 1, 2);
	m_spltLeft.CreateStatic(&m_spltMain, 3, 1,
		WS_CHILD | WS_VISIBLE, m_spltMain.IdFromRowCol(0, 0));
	m_spltRight.CreateStatic(&m_spltMain, 2, 1,
		WS_CHILD | WS_VISIBLE, m_spltMain.IdFromRowCol(0, 1));

	m_spltMain.SetColumnInfo(0, 400, 400);

	m_spltLeft.CreateView(0, 0, RUNTIME_CLASS(CMiniView), CSize(400, int(400.f / WINCX * WINCY)), pContext);
	m_spltLeft.CreateView(1, 0, RUNTIME_CLASS(CObjView), CSize(400, int(400.f / WINCX * WINCY)), pContext);
	m_spltLeft.CreateView(2, 0, RUNTIME_CLASS(CObjFormView), CSize(400, 10), pContext);

	m_spltRight.CreateView(0, 0, RUNTIME_CLASS(CToolView), CSize(WINCX, WINCY), pContext);
	m_spltRight.CreateView(1, 0, RUNTIME_CLASS(CEditFormView), CSize(WINCX, int(400.f / WINCX * WINCY)), pContext);

	return TRUE;
//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}
