#include "stdafx.h"
#include "Barlog.h"

#include "UnitImage.h"
#include "BarlogImage.h"

#include "UnitControl.h"
#include "ArcherControl.h"

OBJ_INFO CBarlog::m_tObjInfo = {};
IMPLEMENT_CREATE(CBarlog)
CBarlog::CBarlog()
	: m_pUnitImage(nullptr)
	, m_pUnitControl(nullptr)
	, m_bCanAttack(false)
{
}


CBarlog::~CBarlog()
{
	Release();
}

HRESULT CBarlog::Initialize()
{
	m_bInfoRender = true;

	//m_tDraw.vSize.x = 350;
	//m_tDraw.vSize.y = 250;
	//m_tDraw.vPosFit = { 0.f, -60.f, 0.f };
	//m_tDraw.vSizeCollision = { 80.f, 140.f, 0.f };
	//m_tDraw.vSizeLand = { TILECX, TILECY, 0.f };
	m_tDraw.SetData(m_tObjInfo.tDraw);
	m_tStatus.SetData(m_tObjInfo.tStatus);

	m_tDraw.vAngle.z = 270.f;
	m_tDraw.fSpeed = INIT_SPEED;

	m_pUnitImage = CUnitImage::Create(CBarlogImage::Create());

	SetDelayTime(ENUM::LiveTime::SKILL, 400);

	lstrcpy(m_tStatus.szName, L"¹ß·Î±×");
	//m_tStatus.iAtt = 50;
	//m_tStatus.iMaxHp = 800;
	//m_tStatus.iMaxMp = 100;
	m_tStatus.FnRecovery();
	m_tStatus.iMp = 0;

	m_pUnitControl = CUnitControl::Create(CArcherControl::Create());

	return S_OK;
}

HRESULT CBarlog::LateInit()
{
	return S_OK;
}

void CBarlog::Release()
{
	SafeDelete(m_pUnitImage);
	SafeDelete(m_pUnitControl);
}

int CBarlog::Update()
{
	CObserver::LiveTime();
	CGameImage::LateInit();

	if (m_eCurState == ENUM::State::DEAD
		&& m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		return (int)m_eEvent;
	if (ENUM::Event::DEAD == m_eEvent)
	{
		m_eNextState = ENUM::State::DEAD;
		return (int)ENUM::Event::NOEVENT;
	}
	if (m_bStun) return (int)m_eEvent;

	Control();
	return (int)m_eEvent;
}

void CBarlog::LateUpdate()
{
	CGameImage::MoveFrame();
	CGameObject::FSM();
}

void CBarlog::Render()
{
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::LAND), 1.f, INIT_COLOR_RECT_LAND);
	if (m_bControlFocus)
		m_pDeviceMgr->DrawHexagon(m_tDraw.GetHexagon(0.f, true, ENUM::DrawRect::LAND), 2.5f, INIT_COLOR_GREEN);
	m_pUnitImage->Render(m_tDraw, m_tFrame);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(), 1.f, INIT_COLOR_RECT_COLLITION);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::IMAGE), 1.f, INIT_COLOR_RECT_IMAGE);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::LAND), 1.f, INIT_COLOR_RECT_LAND);
}

void CBarlog::Control()
{
	static D3DXVECTOR3 vPos;
	static D3DXVECTOR3 vDir;
	static D3DXVECTOR3 vAngle;
	m_pUnitControl->Control(this);

	switch (m_eNextState)
	{
	case ENUM::State::NONE:
		break;
	case ENUM::State::IDLE:
		break;
	case ENUM::State::WALK:
		break;
	case ENUM::State::ATTACK:
	{
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			if (!m_bCanAttack) break;
			CSoundMgr::GetInstance()->MyPlaySound(L"Barlog.wav", CSoundMgr::CHANNELID::EFFECT);

			if (m_tStatus.iMp == m_tStatus.iMaxMp)
			{
				SetDelayTime(ENUM::LiveTime::SKILL, 2000);
				m_tStatus.iMp = 0;
			}
			if (IsActivateTime(ENUM::LiveTime::SKILL))
			{
				SetDelayTime(ENUM::LiveTime::SKILL, 0);
				m_eNextState = ENUM::State::IDLE;
				m_tDraw.color = INIT_COLOR;
				m_tDraw.vScale = { 1.0f, 1.0f, 0.f };
			}

			if (0 != GetDelayTime(ENUM::LiveTime::SKILL))
			{
				m_tDraw.vScale = {1.4f, 1.4f, 0.f};
				m_tFrame.uFrameSpeed = 15;
				m_tDraw.color = INIT_COLOR_RED;
				auto pEnemy = CObserver::GetTarget(ENUM::Target::ENEMY);
				if (pEnemy)
				{
					auto& tStatus = static_cast<CGameObject*>(pEnemy)->GetStatusInfo();
					tStatus.iHp -= m_tStatus.iAtt;
					if (tStatus.iHp < 0)
						tStatus.iHp = 0;
				}
			}
			else
			{
				m_tStatus.iMp += 20;
				auto pEnemy = CObserver::GetTarget(ENUM::Target::ENEMY);
				if (pEnemy)
				{
					auto& tStatus = static_cast<CGameObject*>(pEnemy)->GetStatusInfo();
					tStatus.iHp -= m_tStatus.iAtt;
					if (tStatus.iHp < 0)
						tStatus.iHp = 0;
				}
			}
			m_bCanAttack = false;
		}
		if (m_tFrame.iFrameStart != m_tFrame.iFrameEnd)
			m_bCanAttack = true;
	}
	break;
	case ENUM::State::DEAD:
		break;
	default:
		break;
	}

	//m_eNextState = ENUM::State::DEAD;
}

void CBarlog::FSM()
{
	if (m_eNextState == ENUM::State::DEAD)
	{
		CSoundMgr::GetInstance()->MyPlaySound(L"barlogdead.wav", CSoundMgr::CHANNELID::EFFECT);
	}
	m_pUnitImage->ChangeState(m_eNextState, m_tFrame);
}
