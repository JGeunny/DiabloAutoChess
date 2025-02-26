// ObjTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjTool.h"
#include "afxdialogex.h"

#include "ObjFormView.h"
#include "VirtualObject.h"

#include "Terrain.h"
// CObjTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjTool, CDialog)

CObjTool::CObjTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJTOOL, pParent)
	, m_fSizeX(UNITCX)
	, m_fSizeY(UNITCY)
	, m_fColSizeX(-1.f)
	, m_fColSizeY(-1.f)
	, m_fLandSizeX(TILECX)
	, m_fLandSizeY(TILECY)
	, m_fPosFitX(0)
	, m_fPosFitY(0)
	, m_strObjName(_T(""))
	, m_fAtt(100)
	, m_fRecogDist(100)
	, m_iHp(100)
	, m_iMp(100)
	, m_iLevel(1)
	, m_iCritical(100)
	, m_iLeaderShip(0)
	, m_iGold(0)
	, m_pVirtualObject(nullptr)
{
	m_pVirtualObject = CVirtualObject::Create();
}

CObjTool::~CObjTool()
{
	SafeDelete(m_pVirtualObject);
}

void CObjTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, m_fSizeX);
	DDX_Text(pDX, IDC_EDIT5, m_fSizeY);
	DDX_Text(pDX, IDC_EDIT14, m_fColSizeX);
	DDX_Text(pDX, IDC_EDIT20, m_fColSizeY);
	DDX_Text(pDX, IDC_EDIT21, m_fLandSizeX);
	DDX_Text(pDX, IDC_EDIT22, m_fLandSizeY);
	DDX_Text(pDX, IDC_EDIT23, m_fPosFitX);
	DDX_Text(pDX, IDC_EDIT16, m_fPosFitY);
	DDX_Text(pDX, IDC_EDIT6, m_strObjName);
	DDX_Text(pDX, IDC_EDIT7, m_fAtt);
	DDX_Text(pDX, IDC_EDIT13, m_fRecogDist);
	DDX_Text(pDX, IDC_EDIT8, m_iHp);
	DDX_Text(pDX, IDC_EDIT9, m_iMp);
	DDX_Text(pDX, IDC_EDIT10, m_iLevel);
	DDX_Text(pDX, IDC_EDIT11, m_iCritical);
	DDX_Text(pDX, IDC_EDIT15, m_iLeaderShip);
	DDX_Text(pDX, IDC_EDIT12, m_iGold);
	DDX_Control(pDX, ID_PICTURE, m_picObjImage);
	DDX_Control(pDX, IDC_LIST1, m_lstObjImageList);
	DDX_Control(pDX, IDC_COMBO1, m_cboObjType);
	DDX_Control(pDX, IDC_COMBO3, m_cboTeam);
	DDX_Control(pDX, IDC_COMBO5, m_cboJob);
}

void CObjTool::InitObjList()
{
	auto pObjFormView = CEditMgr::GetInstance()->GetObjFormView();

	pObjFormView->m_lstObj.ResetContent();
	for (auto& pair : m_mapObjData)
	{
		pObjFormView->m_lstObj.AddString(pair.first);
	}

}

void CObjTool::DrawPicture()
{
	int iSel = m_lstObjImageList.GetCurSel();
	if (0 > iSel) return;

	m_lstObjImageList.GetText(iSel, m_strObjImage);
	m_pVirtualObject->SetImage((LPWSTR)m_strObjImage.GetString());
	m_pVirtualObject->SetPos(D3DXVECTOR3( WINCX*0.5f, WINCY*0.5f, 0.f ));
	m_pVirtualObject->SetSize(D3DXVECTOR3(WINCX, WINCY, 0.f));
	m_pVirtualObject->Update();
	m_pVirtualObject->LateUpdate();
	m_pVirtualObject->ChangeState(ENUM::State::IDLE);
	CDeviceMgr::GetInstance()->Render_Begin();
	m_pVirtualObject->Render();
	CDeviceMgr::GetInstance()->Render_End(m_picObjImage.m_hWnd);
}

void CObjTool::AddData()
{
	UpdateData(TRUE);
	if (m_strObjName == L"") return;
	auto& iter = m_mapObjData.find(m_strObjName);
	if (iter != m_mapObjData.end())
		m_mapObjData[m_strObjName] = GetData();
	else
		m_mapObjData.insert({ m_strObjName, GetData() });
	UpdateData(FALSE);
}

void CObjTool::DelData()
{
	UpdateData(TRUE);
	if (m_strObjName == L"") return;
	auto& iter = m_mapObjData.find(m_strObjName);
	if (iter != m_mapObjData.end())
		m_mapObjData.erase(iter);
	UpdateData(FALSE);
}

OBJ_INFO CObjTool::GetData()
{
	UpdateData(TRUE);

	int iSelImg = m_lstObjImageList.GetCurSel();
	int iSelTeam = m_cboTeam.GetCurSel();
	int iSelJob = m_cboJob.GetCurSel();
	int iSelClassID = m_cboObjType.GetCurSel();

	if (iSelImg < 0 || iSelTeam < 0 || iSelClassID < 0 || iSelJob < 0) return OBJ_INFO();
	OBJ_INFO tObjData = {};
	m_lstObjImageList.GetText(iSelImg, tObjData.szFrameKey);
	tObjData.tDraw.vSize.x = m_fSizeX;
	tObjData.tDraw.vSize.y = m_fSizeY;

	tObjData.tDraw.vSizeCollision.x = m_fColSizeX;
	tObjData.tDraw.vSizeCollision.y = m_fColSizeY;
	tObjData.tDraw.vSizeLand.x = m_fLandSizeX;
	tObjData.tDraw.vSizeLand.y = m_fLandSizeY;
	tObjData.tDraw.vPosFit.x = m_fPosFitX;
	tObjData.tDraw.vPosFit.y = m_fPosFitY;
	
	tObjData.tStatus.eJob = (ENUM::Job)iSelJob;
	tObjData.tStatus.eTeam = (ENUM::Team)iSelTeam;
	tObjData.tStatus.fRecogDist = m_fRecogDist;
	tObjData.tStatus.iClassID = iSelClassID;
	lstrcpy(tObjData.tStatus.szName, m_strObjName.GetString());
	tObjData.tStatus.iAtt = int(m_fAtt);
	tObjData.tStatus.iMaxHp = m_iHp;
	tObjData.tStatus.iMaxMp = m_iMp;
	tObjData.tStatus.iLevel = m_iLevel;
	tObjData.tStatus.iCritical = m_iCritical;
	tObjData.tStatus.iGold = m_iGold;
	return tObjData;
}

bool CObjTool::GetMapData(OBJ_INFO & _tObjData)
{
	auto pFormView = CEditMgr::GetInstance()->GetObjFormView();
	int iSel = pFormView->m_lstObj.GetCurSel();
	if (iSel < 0)
		return false;
	CString strKey;
	pFormView->m_lstObj.GetText(iSel, strKey);
	auto& iter = m_mapObjData.find(strKey);
	if (iter == m_mapObjData.end())
		return false;
	_tObjData = iter->second;
	return true;
}

void CObjTool::SetData(CString & _strObjName)
{
	auto& iter = m_mapObjData.find(_strObjName);
	if (iter != m_mapObjData.end())
		SetData(iter->second);
}

void CObjTool::SetData(OBJ_INFO & _tObjData)
{
	int iSel = m_lstObjImageList.FindString(-1, _tObjData.szFrameKey);
	if (iSel < 0) return;
	m_lstObjImageList.SetCurSel(iSel);
	m_fSizeX = _tObjData.tDraw.vSize.x;
	m_fSizeY = _tObjData.tDraw.vSize.y;

	m_fColSizeX = _tObjData.tDraw.vSizeCollision.x;
	m_fColSizeY = _tObjData.tDraw.vSizeCollision.y;
	m_fLandSizeX = _tObjData.tDraw.vSizeLand.x;
	m_fLandSizeY = _tObjData.tDraw.vSizeLand.y;
	m_fPosFitX = _tObjData.tDraw.vPosFit.x;
	m_fPosFitY = _tObjData.tDraw.vPosFit.y;

	m_cboTeam.SetCurSel((int)_tObjData.tStatus.eTeam);
	m_cboJob.SetCurSel((int)_tObjData.tStatus.eJob);
	m_cboObjType.SetCurSel((int)_tObjData.tStatus.iClassID);

	m_fRecogDist = _tObjData.tStatus.fRecogDist;

	m_strObjName = _tObjData.tStatus.szName;
	m_fAtt = (float)_tObjData.tStatus.iAtt;
	m_iHp = _tObjData.tStatus.iMaxHp;
	m_iMp = _tObjData.tStatus.iMaxMp;
	m_iLevel = _tObjData.tStatus.iLevel;
	m_iCritical = _tObjData.tStatus.iCritical;
	m_iGold = _tObjData.tStatus.iGold;
	UpdateData(FALSE);
	Invalidate(FALSE);
}

void CObjTool::Release()
{
	m_mapObjData.clear();
}

void CObjTool::Refresh()
{
	this->Invalidate(FALSE);
}

HRESULT CObjTool::SaveData(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"오브젝트 저장 실패");
		return S_FALSE;
	}

	DWORD dwBytes = 0;
	for (auto& tObjInfo : m_mapObjData)
	{
		//데이터 저장
		WriteFile(hFile, &tObjInfo.second, sizeof(OBJ_INFO), &dwBytes, nullptr);
	}
	CloseHandle(hFile);
	return S_OK;
}

HRESULT CObjTool::LoadData(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"오브젝트 불러오기 실패");
		return S_FALSE;
	}

	if (!m_mapObjData.empty())
		m_mapObjData.clear();
	

	DWORD dwBytes = 0;
	OBJ_INFO	tLoadData;
	while (true)
	{
		//데이터 가져오기
		ReadFile(hFile, &tLoadData, sizeof(OBJ_INFO), &dwBytes, nullptr);
		if (0 == dwBytes)
		{
			break;
		}
		m_mapObjData.insert({ tLoadData.tStatus.szName, tLoadData });
	}
	CloseHandle(hFile);
	InitObjList();
	return S_OK;
}


BEGIN_MESSAGE_MAP(CObjTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjTool::OnLbnSelchangeObjImageList)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON5, &CObjTool::OnBnClickedAddData)
	ON_BN_CLICKED(IDC_BUTTON7, &CObjTool::OnBnClickedDelData)
END_MESSAGE_MAP()


// CObjTool 메시지 처리기입니다.


BOOL CObjTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_lstObjImageList.InsertString(0, L"NONE");
	m_lstObjImageList.InsertString(1, L"Amazon");
	m_lstObjImageList.InsertString(2, L"Duriel");
	m_lstObjImageList.InsertString(3, L"Bavarian");
	m_lstObjImageList.InsertString(4, L"Andariel");
	m_lstObjImageList.InsertString(5, L"Dia");
	m_lstObjImageList.InsertString(6, L"Izual");
	m_lstObjImageList.InsertString(7, L"Barlog");
	m_lstObjImageList.SetCurSel(0);

	m_cboObjType.InsertString(0, L"유닛");
	m_cboObjType.InsertString(1, L"건물");
	m_cboObjType.InsertString(2, L"아이템");
	m_cboObjType.SetCurSel(0);

	m_cboTeam.InsertString(0, L"NONE");
	m_cboTeam.InsertString(1, L"ONE");
	m_cboTeam.InsertString(2, L"TWO");
	m_cboTeam.InsertString(3, L"THREE");
	m_cboTeam.InsertString(4, L"FOUR");
	m_cboTeam.InsertString(5, L"FIVE");
	m_cboTeam.InsertString(6, L"SIX");
	m_cboTeam.InsertString(7, L"SEVEN");
	m_cboTeam.InsertString(8, L"EIGHT");
	m_cboTeam.SetCurSel(0);

	m_cboJob.InsertString(0, L"NONE");
	m_cboJob.InsertString(1, L"KNIGHT");
	m_cboJob.InsertString(2, L"SCOUT");
	m_cboJob.InsertString(3, L"WIZARD");
	m_cboJob.InsertString(4, L"ASSASSIN");
	m_cboJob.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CObjTool::OnLbnSelchangeObjImageList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->Invalidate(FALSE);
}


void CObjTool::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	DrawPicture();
}


void CObjTool::OnBnClickedAddData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AddData();
	InitObjList();
}


void CObjTool::OnBnClickedDelData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DelData();
	InitObjList();
}
