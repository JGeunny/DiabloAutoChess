#include "stdafx.h"
#include "Laser.h"

IMPLEMENT_CREATE(CLaser)
CLaser::CLaser()
{
}


CLaser::~CLaser()
{
}

HRESULT CLaser::Initialize()
{
	SetDelayTime(ENUM::LiveTime::LIVE, 1000);
	m_tDraw.vSize = { 252.f, 190.f, 0.f };
	m_tDraw.vSizeCollision = { 60.f, 60.f, 0.f };
	m_tDraw.fSpeed = INIT_SPEED_FAST;
	m_tStatus.iClassID = CLASSID_LASER;

	LoadGameImage();

	m_vecOrderType.resize(8);
	for (int i = 0; i <= 7; ++i)
		m_vecOrderType[i] = i;

	//m_vScale = { 1.f, 1.f, 0.f };
	//m_vPosFit = { 0.f,  0.f, 0.f };
	m_tFrame.iFrameKey = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 14;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 7;
	m_tFrame.uFrameSpeed = 20;
	m_tFrame.pListSceneOrder = &m_vecOrderType;

	m_uValidityTime = 500;//맞은 놈은 0.5초후에 또맞을수있다.

	m_tStatus.iMaxHp = 9999;
	m_tStatus.FnRecovery();

	m_tDraw.color = D3DCOLOR_ARGB(255, 255, 255, 255);
	return S_OK;
}

HRESULT CLaser::LateInit()
{
	return E_NOTIMPL;
}

void CLaser::Release()
{
}

int CLaser::Update()
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

void CLaser::LateUpdate()
{
	CGameImage::MoveFrame();
}

void CLaser::Render()
{
	//m_tFrame.SetScene(m_tDraw.vAngle.z);
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::LASER, m_tFrame.iFrameScene, m_tFrame.iFrameStart));
	//m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();
	//	std::cout << _tFrame.iFrameScene << ":" << _tFrame.iFrameStart << std::endl;
	m_pDeviceMgr->DrawImage(m_tDraw, nullptr, CDeviceMgr::DRAWTYPE::ALPHA);

}

void CLaser::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"Laser|0R", L"../Image/Skill/Laser/0R/%d.png", 15, 1, 1, INIT_COLOR_BLACK);
	//CTextureMgr::GetInstance()->LoadTexture(L"Laser|1UR", L"../Image/Skill/Laser/1UR/%d.png", 15, 1, 1, INIT_COLOR_BLACK);
	//CTextureMgr::GetInstance()->LoadTexture(L"Laser|2U", L"../Image/Skill/Laser/2U/%d.png", 15, 1, 1, INIT_COLOR_BLACK);
	//CTextureMgr::GetInstance()->LoadTexture(L"Laser|3UL", L"../Image/Skill/Laser/3UL/%d.png", 15, 1, 1, INIT_COLOR_BLACK);
	//CTextureMgr::GetInstance()->LoadTexture(L"Laser|4L", L"../Image/Skill/Laser/4L/%d.png", 15, 1, 1, INIT_COLOR_BLACK);
	//CTextureMgr::GetInstance()->LoadTexture(L"Laser|5DL", L"../Image/Skill/Laser/5DL/%d.png", 15, 1, 1, INIT_COLOR_BLACK);
	//CTextureMgr::GetInstance()->LoadTexture(L"Laser|6D", L"../Image/Skill/Laser/6D/%d.png", 15, 1, 1, INIT_COLOR_BLACK);
	//CTextureMgr::GetInstance()->LoadTexture(L"Laser|7DR", L"../Image/Skill/Laser/7DR/%d.png", 15, 1, 1, INIT_COLOR_BLACK);
}
