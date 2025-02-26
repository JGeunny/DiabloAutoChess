#include "stdafx.h"
#include "Stun.h"

IMPLEMENT_CREATE(CStun)
CStun::CStun()
{
}


CStun::~CStun()
{
	Release();
}

HRESULT CStun::Initialize()
{
	CSoundMgr::GetInstance()->MyPlaySound(L"stun1.wav", CSoundMgr::CHANNELID::HIT);
	SetDelayTime(ENUM::LiveTime::LIVE, 3000);
	//m_pTextureMgr->LoadTexture(L"Stun|Stun", L"../Image/Effect/Stun/%d.png", 12,1,1,INIT_COLOR_BLACK);
	LoadGameImage();
	m_tDraw.vSize = { 120.f, 80.f, 0.f };
	m_tFrame.iFrameKey = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.uFrameSpeed = 30;

	m_pTarget = CObserver::Create();
	m_tDraw.color = D3DCOLOR_ARGB(255, 255, 255, 255);
	return S_OK;
}

HRESULT CStun::LateInit()
{
	return S_OK;
}

void CStun::Release()
{
	SafeDelete(m_pTarget);
}

int CStun::Update()
{
	CObserver::LiveTime();
	CGameImage::LateInit();
	CObserver* pObj = m_pTarget->GetTarget(ENUM::Target::PARENT);
	if (!pObj) m_eEvent = ENUM::Event::DEAD;
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}
	CGameImage* pUnit = static_cast<CGameImage*>(pObj);

	auto& tDraw = pUnit->GetDrawInfo();
	m_tDraw.vPos = tDraw.vPos;
	m_tDraw.vPos.y = (float)tDraw.GetRect().top - 50;
	//m_tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	//Control();
	return (int)m_eEvent;
}

void CStun::LateUpdate()
{
	CGameImage::MoveFrame();
}

void CStun::Render()
{
	//static RECT rtSize;
	//rtSize = m_tDraw.GetRect();
	//m_pDeviceMgr->DrawRectangle(rtSize);
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::STUN, m_tFrame.iFrameScene, m_tFrame.iFrameStart));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	//	std::cout << _tFrame.iFrameScene << ":" << _tFrame.iFrameStart << std::endl;
	m_pDeviceMgr->DrawImage(m_tDraw, nullptr, CDeviceMgr::DRAWTYPE::ALPHA);
	//m_pDeviceMgr->DrawImage(m_tDraw);

}

void CStun::SetTarget(CObserver * _pTarget)
{
	m_pTarget->SetTarget(ENUM::Target::PARENT, _pTarget);
}


void CStun::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"Stun|Stun", L"../Image/Effect/Stun/%d.png", 12, 1, 1, INIT_COLOR_BLACK);
}