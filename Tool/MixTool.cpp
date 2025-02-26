// MixTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MixTool.h"
#include "afxdialogex.h"

#include "ObjFormView.h"

// CMixTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMixTool, CDialog)

CMixTool::CMixTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MIXTOOL, pParent)
{

}

CMixTool::~CMixTool()
{
}

void CMixTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CMixTool::InitObjList()
{
	CEditMgr::GetInstance()->GetObjFormView()->m_lstObj.ResetContent();
}


BEGIN_MESSAGE_MAP(CMixTool, CDialog)
END_MESSAGE_MAP()


// CMixTool 메시지 처리기입니다.
