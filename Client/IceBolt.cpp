#include "stdafx.h"
#include "IceBolt.h"

IMPLEMENT_CREATE(CIceBolt);
CIceBolt::CIceBolt()
{
}


CIceBolt::~CIceBolt()
{
}

HRESULT CIceBolt::Initialize()
{
	SetDelayTime(ENUM::LiveTime::LIVE, 300);
	m_tDraw.vSize = { 150.f, 75.f, 0.f };
	m_tDraw.vSizeCollision = { 30.f, 30.f, 0.f };
	m_tDraw.fSpeed = INIT_SPEED_FAST;
	m_tStatus.iClassID = CLASSID_ICEBOLT;

	LoadGameImage();

	m_vecOrderType.resize(16);
	for (int i = 0; i <= 4; ++i)
		m_vecOrderType[i] = 4 - i;
	for (int i = 5; i <= 15; ++i)
		m_vecOrderType[i] = 20 - i;

	//m_vScale = { 1.f, 1.f, 0.f };
	//m_vPosFit = { 0.f,  0.f, 0.f };
	m_tFrame.iFrameKey = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 15;
	m_tFrame.uFrameSpeed = 20;
	m_tFrame.pListSceneOrder = &m_vecOrderType;

	m_tStatus.iMaxHp = 1;
	m_tStatus.FnRecovery();

	m_tDraw.color = D3DCOLOR_ARGB(255, 255, 255, 255);
	return S_OK;
}

HRESULT CIceBolt::LateInit()
{
	return E_NOTIMPL;
}

void CIceBolt::Release()
{
}

int CIceBolt::Update()
{
	CObserver::LiveTime();
	CGameImage::LateInit();
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}

	m_tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	//Control();
	return (int)m_eEvent;
}

void CIceBolt::LateUpdate()
{
	CGameImage::MoveFrame();
}

void CIceBolt::Render()
{
	m_tFrame.SetScene(m_tDraw.vAngle.z);
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::ICEBOLT, m_tFrame.iFrameScene, m_tFrame.iFrameStart));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	//	std::cout << _tFrame.iFrameScene << ":" << _tFrame.iFrameStart << std::endl;
	m_pDeviceMgr->DrawImage(m_tDraw, nullptr, CDeviceMgr::DRAWTYPE::ALPHA);

}

void CIceBolt::LoadGameImage()
{	
	static bool isInit = false;
	if (isInit) return;
	isInit = true;
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|0", L"../Image/Skill/IceBolt/0/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|1", L"../Image/Skill/IceBolt/1/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|2", L"../Image/Skill/IceBolt/2/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|3", L"../Image/Skill/IceBolt/3/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|4", L"../Image/Skill/IceBolt/4/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|5", L"../Image/Skill/IceBolt/5/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|6", L"../Image/Skill/IceBolt/6/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|7", L"../Image/Skill/IceBolt/7/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|8", L"../Image/Skill/IceBolt/8/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|9", L"../Image/Skill/IceBolt/9/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|10", L"../Image/Skill/IceBolt/10/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|11", L"../Image/Skill/IceBolt/11/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|12", L"../Image/Skill/IceBolt/12/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|13", L"../Image/Skill/IceBolt/13/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|14", L"../Image/Skill/IceBolt/14/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
	CTextureMgr::GetInstance()->LoadTexture(L"IceBolt|15", L"../Image/Skill/IceBolt/15/%d.png", 6, 1, 1, INIT_COLOR_BLACK);
}
