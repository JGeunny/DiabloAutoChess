#include "stdafx.h"
#include "Izual.h"


#include "UnitImage.h"
#include "IzualImage.h"

#include "UnitControl.h"
#include "ArcherControl.h"

OBJ_INFO CIzual::m_tObjInfo = {};
IMPLEMENT_CREATE(CIzual)
CIzual::CIzual()
	: m_pUnitImage(nullptr)
	, m_pUnitControl(nullptr)
	, m_bCanAttack(false)
{
}


CIzual::~CIzual()
{
	Release();
}

HRESULT CIzual::Initialize()
{
	m_bInfoRender = true;

	//m_tDraw.vSize.x = 250;
	//m_tDraw.vSize.y = 200;
	//m_tDraw.vPosFit = { 0.f, -60.f, 0.f };
	//m_tDraw.vSizeCollision = { 80.f, 140.f, 0.f };
	//m_tDraw.vSizeLand = { TILECX, TILECY, 0.f };
	m_tDraw.SetData(m_tObjInfo.tDraw);
	m_tStatus.SetData(m_tObjInfo.tStatus);

	m_tDraw.vAngle.z = 270.f;
	m_tDraw.fSpeed = INIT_SPEED;

	m_pUnitImage = CUnitImage::Create(CIzualImage::Create());

	SetDelayTime(ENUM::LiveTime::SKILL, 400);

	lstrcpy(m_tStatus.szName, L"ÀÌÁê¾ó");
	//m_tStatus.iAtt = 50;
	//m_tStatus.iMaxHp = 800;
	//m_tStatus.iMaxMp = 100;
	m_tStatus.FnRecovery();
	m_tStatus.iMp = 0;

	m_pUnitControl = CUnitControl::Create(CArcherControl::Create());

	return S_OK;
}

HRESULT CIzual::LateInit()
{
	return S_OK;
}

void CIzual::Release()
{
	SafeDelete(m_pUnitImage);
	SafeDelete(m_pUnitControl);
}

int CIzual::Update()
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

void CIzual::LateUpdate()
{
	CGameImage::MoveFrame();
	CGameObject::FSM();
}

void CIzual::Render()
{
	if (m_bControlFocus)
		m_pDeviceMgr->DrawHexagon(m_tDraw.GetHexagon(0.f, true, ENUM::DrawRect::LAND), 2.5f, INIT_COLOR_GREEN);
	m_pUnitImage->Render(m_tDraw, m_tFrame);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(), 1.f, INIT_COLOR_RECT_COLLITION);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::IMAGE), 1.f, INIT_COLOR_RECT_IMAGE);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::LAND), 1.f, INIT_COLOR_RECT_LAND);
}

void CIzual::Control()
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
			CSoundMgr::GetInstance()->MyPlaySound(L"IzualAttack.wav", CSoundMgr::CHANNELID::EFFECT);
			if (m_tStatus.iMp == m_tStatus.iMaxMp)
			{
				CSoundMgr::GetInstance()->MyPlaySound(L"izualfadein.wav", CSoundMgr::CHANNELID::EFFECT);
				SetDelayTime(ENUM::LiveTime::SKILL, 3000);
				m_tStatus.iMp = 0;
			}
			if (IsActivateTime(ENUM::LiveTime::SKILL))
			{
				SetDelayTime(ENUM::LiveTime::SKILL, 0);
				m_eNextState = ENUM::State::IDLE;
				m_tDraw.color = INIT_COLOR;
			}

			if (0 != GetDelayTime(ENUM::LiveTime::SKILL))
			{
				m_tDraw.color = INIT_COLOR_OPACITY;
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

void CIzual::FSM()
{
	if (m_eNextState == ENUM::State::DEAD)
	{
		CSoundMgr::GetInstance()->MyPlaySound(L"izualdeath.wav", CSoundMgr::CHANNELID::EFFECT);
	}
	m_pUnitImage->ChangeState(m_eNextState, m_tFrame);
}
