#include "stdafx.h"
#include "BaseAttack.h"

IMPLEMENT_CREATE(CBaseAttack)
CBaseAttack::CBaseAttack()
{
}


CBaseAttack::~CBaseAttack()
{
}

HRESULT CBaseAttack::Initialize()
{
	SetDelayTime(ENUM::LiveTime::LIVE, 300);
	m_tDraw.vSize = { 100.f, 100.f, 0.f };
	m_tDraw.fSpeed = INIT_SPEED_FAST;

	m_tStatus.iHp = 1;
	return S_OK;
}

HRESULT CBaseAttack::LateInit()
{
	//m_pTextureMgr->LoadTexture(L"Skill|Arrow", L"../Image/Skill/Arrow/Arrow.png", -1, 1, 1, INIT_COLOR_BLACK);
	return S_OK;
}

void CBaseAttack::Release()
{
}

int CBaseAttack::Update()
{
	CObserver::LiveTime();
	CGameImage::LateInit();
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}

	//m_tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	//Control();
	return (int)m_eEvent;
}

void CBaseAttack::LateUpdate()
{
	CGameImage::MoveFrame();
	//CGameObject::FSM();
}

void CBaseAttack::Render()
{
	//static float fAngle;
	//fAngle = m_tDraw.vAngle.z;
	//m_tDraw.vAngle.z += 90;
	//m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::SKILL, 0, 0));
	//m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();
	//m_pDeviceMgr->DrawImage(m_tDraw);
	//m_tDraw.vAngle.z = fAngle;

	m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(), 1.f, INIT_COLOR_RECT_COLLITION);
}
