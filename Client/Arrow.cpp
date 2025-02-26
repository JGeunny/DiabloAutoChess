#include "stdafx.h"
#include "Arrow.h"

IMPLEMENT_CREATE(CArrow)
CArrow::CArrow()
{
}


CArrow::~CArrow()
{
}

HRESULT CArrow::Initialize()
{
	SetDelayTime(ENUM::LiveTime::LIVE, 1000);
	m_tDraw.vSize = { 5.f, 30.f, 0.f };
	m_tDraw.fSpeed = INIT_SPEED_FAST;
	m_tStatus.iClassID = CLASSID_ARROW;

	LoadGameImage();
	//m_pTextureMgr->LoadTexture(L"Skill|Arrow", L"../Image/Skill/Arrow/Arrow.png", -1, 1, 1, INIT_COLOR_BLACK);

	m_tStatus.iMaxHp = 1;
	m_tStatus.FnRecovery();
	return S_OK;
}

HRESULT CArrow::LateInit()
{
	return S_OK;
}

void CArrow::Release()
{
}

int CArrow::Update()
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

void CArrow::LateUpdate()
{
	CGameImage::MoveFrame();
	//CGameObject::FSM();
}

void CArrow::Render()
{
	static float fAngle;
	fAngle = m_tDraw.vAngle.z;
	m_tDraw.vAngle.z += 90;
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::SKILL, 0, 0));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();
	m_pDeviceMgr->DrawImage(m_tDraw);
	m_tDraw.vAngle.z = fAngle;
}

void CArrow::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;
	CTextureMgr::GetInstance()->LoadTexture(L"Skill|Arrow", L"../Image/Skill/Arrow/Arrow.png", -1, 1, 1, INIT_COLOR_BLACK);
}