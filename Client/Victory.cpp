#include "stdafx.h"
#include "Victory.h"

IMPLEMENT_CREATE_BASE(CVictory)
CVictory::CVictory()
	:m_bVictory(true)
{
}


CVictory::~CVictory()
{
}

HRESULT	CVictory::Initialize()
{
	m_pTextureMgr->LoadTexture(L"Victory|Win", L"../Image/UI/Victory/Win/UI%d.png", 12, 1, 1, D3DCOLOR_ARGB(255, 212, 192, 212));
	m_pTextureMgr->LoadTexture(L"Victory|Lose", L"../Image/UI/Victory/Lose/UI%d.png", 12, 1, 1, D3DCOLOR_ARGB(255, 212, 192, 212));
	m_pTextureMgr->LoadTexture(L"Victory|BackGround", L"../Image/UI/Victory/BackGround.png");
	m_tDraw.vPos = { WINCX * 0.5f, WINCY*0.5f, 0.f };
	m_tDraw.vSize = { 250, 92, 0.f };

	m_tDrawBackGround.vPos = { WINCX * 0.5f, WINCY*0.5f, 0.f };
	m_tDrawBackGround.vSize = { WINCX, WINCY, 0.f };
	m_tDrawBackGround.color = D3DCOLOR_ARGB(100, 0, 0, 0);
	m_tDrawBackGround.SetTexInfo(m_pTextureMgr->GetTexInfo(L"Victory|BackGround"));

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.uFrameSpeed = 80;
	
	return S_OK;
}

HRESULT CVictory::LateInit()
{
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNELID::BGM);
	if (m_bVictory)
	{
		lstrcpy(m_szFrameKey, L"Victory|Win");
		CSoundMgr::GetInstance()->MyPlaySound(L"Win.wav", CSoundMgr::CHANNELID::UI);
	}
	else
	{
		lstrcpy(m_szFrameKey, L"Victory|Lose");
		CSoundMgr::GetInstance()->MyPlaySound(L"Lose.wav", CSoundMgr::CHANNELID::UI);
	}
	return S_OK;
}

void CVictory::Release()
{
}

int CVictory::Update()
{
	CGameImage::LateInit();
	CObserver::LiveTime();
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		if (GetDelayTime(ENUM::LiveTime::LIVE) == 0)
			SetDelayTime(ENUM::LiveTime::LIVE, 7000);
	}
	if (m_eEvent == ENUM::Event::DEAD)
		return (int)m_eEvent;

	return (int)m_eEvent;
}

void CVictory::LateUpdate()
{
	if (GetDelayTime(ENUM::LiveTime::LIVE) == 0)
		MoveFrame();
}

void CVictory::Render()
{
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(m_szFrameKey, m_tFrame.iFrameStart));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	m_tDrawBackGround.matCurrent = m_tDrawBackGround.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	m_pDeviceMgr->DrawImage(m_tDrawBackGround);
	m_pDeviceMgr->DrawImage(m_tDraw);
}
