#pragma once


// CMixTool ��ȭ �����Դϴ�.

class CMixTool : public CDialog
{
	DECLARE_DYNAMIC(CMixTool)

public:
	CMixTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMixTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MIXTOOL };
#endif

protected://Virtual Funtion
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

public://Message Function
	DECLARE_MESSAGE_MAP()

public:
	void	InitObjList();
};
