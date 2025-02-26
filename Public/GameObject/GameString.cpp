#include "stdafx.h"
#include "GameString.h"

IMPLEMENT_CREATE_COMPONENT(CGameString)
CGameString::CGameString()
{
}


CGameString::~CGameString()
{
}

HRESULT CGameString::Initialize()
{
	SetDelayTime(ENUM::LiveTime::LIVE, 500);
	return S_OK;
}

HRESULT CGameString::LateInit()
{
	return S_OK;
}

void CGameString::Release()
{
}

int CGameString::Update()
{
	LiveTime();
	if (ENUM::Event::DEAD == m_eEvent)
		return (int)m_eEvent;

	m_tDraw.vPos.y -= INIT_SPEED_SLOW * m_pTimeMgr->GetDeltaTime();
	return (int)m_eEvent;
}

void CGameString::LateUpdate()
{
}

void CGameString::Render()
{
	static RECT rtSize;
	rtSize = m_tDraw.GetRect();
	m_pDeviceMgr->DrawString(m_szStringName, lstrlen(m_szStringName), &rtSize, 5UL, m_tDraw.color);
	//m_pDeviceMgr->DrawRectangle(rtSize);
}
