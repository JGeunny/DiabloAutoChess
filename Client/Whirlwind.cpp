#include "stdafx.h"
#include "Whirlwind.h"
#include "Bavarian.h"

IMPLEMENT_CREATE(CWhirlwind)
CWhirlwind::CWhirlwind()
{
}


CWhirlwind::~CWhirlwind()
{
	CObserver* pObj = m_pTarget[(int)ENUM::Target::PARENT];
	if (pObj)
	{
		CBavarian* pUnit = static_cast<CBavarian*>(m_pTarget[(int)ENUM::Target::PARENT]);
		pUnit->SetState(ENUM::State::IDLE);
		pUnit->FSM();
	}
}

HRESULT CWhirlwind::Initialize()
{
	CSoundMgr::GetInstance()->MyPlaySound(L"whirlwind.wav", CSoundMgr::CHANNELID::HIT);
	SetDelayTime(ENUM::LiveTime::LIVE, 2000);
	//m_tDraw.vSize = { 200.f, 200.f, 0.f };
	m_tDraw.vSize = { 180.f, 160.f, 0.f };
	m_tDraw.vPosFit = { 0.f, -50.f, 0.f };
	m_tDraw.fSpeed = INIT_SPEED_FAST;
	m_tDraw.color = INIT_COLOR_OPACITY;

	LoadGameImage();
	//m_pTextureMgr->LoadTexture(L"Skill|Whirlwind", L"../Image/Skill/whirlwind/%d.png", 8);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.uFrameSpeed = 60;

	m_uValidityTime = 500;//맞은 놈은 0.5초후에 또맞을수있다.

	m_tStatus.iHp = 99999;
	return S_OK;
}

HRESULT CWhirlwind::LateInit()
{
	return S_OK;
}

void CWhirlwind::Release()
{
}

int CWhirlwind::Update()
{
	//부모가 없다면 죽임
	if (!m_pTarget[(int)ENUM::Target::PARENT]) return (int)(m_eEvent = ENUM::Event::DEAD);
	CObserver::LiveTime();
	CGameImage::LateInit();
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}
	CObserver* pObj = m_pTarget[(int)ENUM::Target::PARENT];
	if (!pObj) return (int)ENUM::Event::DEAD;

	CBavarian* pUnit = static_cast<CBavarian*>(pObj);
	auto& tDrawInfo = pUnit->GetDrawInfo();
	m_tDraw.vPos = tDrawInfo.vPos;
	//m_tDraw.vPosFit = tDrawInfo.vPosFit;
	pUnit->SetWhirlwind();

	//m_tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	//Control();
	return (int)m_eEvent;
}

void CWhirlwind::LateUpdate()
{
	CGameImage::MoveFrame();
}

void CWhirlwind::Render()
{
	//static float fAngle;
	//fAngle = m_tDraw.vAngle.z;
	//m_tDraw.vAngle.z += 90;
	
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(L"Skill|Whirlwind", m_tFrame.iFrameStart));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();
	m_pDeviceMgr->DrawImage(m_tDraw);
	//m_tDraw.vAngle.z = fAngle;
}

void CWhirlwind::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;
	CTextureMgr::GetInstance()->LoadTexture(L"Skill|Whirlwind", L"../Image/Skill/whirlwind/%d.png", 8);
}