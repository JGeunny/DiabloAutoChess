#pragma once


// CMixTool 대화 상자입니다.

class CMixTool : public CDialog
{
	DECLARE_DYNAMIC(CMixTool)

public:
	CMixTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMixTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MIXTOOL };
#endif

protected://Virtual Funtion
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public://Message Function
	DECLARE_MESSAGE_MAP()

public:
	void	InitObjList();
};
