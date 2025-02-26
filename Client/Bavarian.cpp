#include "stdafx.h"
#include "Bavarian.h"

#include "UnitImage.h"
#include "BavarianImage.h"

#include "UnitControl.h"
#include "ArcherControl.h"

#include "BaseAttack.h"
#include "Whirlwind.h"

OBJ_INFO CBavarian::m_tObjInfo = {};
IMPLEMENT_CREATE(CBavarian)
CBavarian::CBavarian()
	: m_pUnitImage(nullptr)
	, m_pUnitControl(nullptr)
	, m_bCanAttack(false)
	, m_pBavarianImage(nullptr)
{
}


CBavarian::~CBavarian()
{
	Release();
}

HRESULT CBavarian::Initialize()
{
	m_bInfoRender = true;
	////바바리안
	//m_tDraw.vSize.x = 300;
	//m_tDraw.vSize.y = 300;
	//m_tDraw.vPosFit = { 0.f, -40.f, 0.f };
	//m_tDraw.vSizeCollision = { 50.f, 130.f, 0.f };
	//m_tDraw.vSizeLand = { TILECX, TILECY, 0.f };
	m_tDraw.SetData(m_tObjInfo.tDraw);
	m_tStatus.SetData(m_tObjInfo.tStatus);

	m_tDraw.vAngle.z = 270.f;
	m_tDraw.fSpeed = INIT_SPEED;

	m_pBavarianImage = CBavarianImage::Create();
	m_pUnitImage = CUnitImage::Create(m_pBavarianImage);
	m_pUnitControl = CUnitControl::Create(CArcherControl::Create());

	SetDelayTime(ENUM::LiveTime::SKILL, 400);

	lstrcpy(m_tStatus.szName, L"바바리안");
	//m_tStatus.iAtt = 100;
	//m_tStatus.iMaxHp = 500;
	//m_tStatus.iMaxMp = 100;
	m_tStatus.FnRecovery();
	m_tStatus.iMp = 0;

	return S_OK;
}

HRESULT CBavarian::LateInit()
{
	return S_OK;
}

void CBavarian::Release()
{
	SafeDelete(m_pUnitImage);
	SafeDelete(m_pUnitControl);
}

int CBavarian::Update()
{
	CObserver::LiveTime();
	CGameImage::LateInit();
	if (IsActivateTime(ENUM::LiveTime::DEAD))
	{
		return (int)ENUM::Event::DEAD;
	}
	if (m_eCurState == ENUM::State::DEAD
		&& m_tFrame.iFrameStart == m_tFrame.iFrameEnd
		&& m_tFrame.iFrameScene == m_tFrame.iFrameSceneEnd)
	{
		return (int)m_eEvent;
	}
	if (ENUM::Event::DEAD == m_eEvent)
	{
		m_eNextState = ENUM::State::DEAD;
		return (int)ENUM::Event::NOEVENT;
	}
	if (m_bStun) return (int)m_eEvent;

	Control();
	return (int)m_eEvent;
}

void CBavarian::LateUpdate()
{
	CGameImage::MoveFrame();
	CGameObject::FSM();
}

void CBavarian::Render()
{
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::LAND), 1.f, INIT_COLOR_RECT_LAND);
	if (m_bControlFocus)
		m_pDeviceMgr->DrawHexagon(m_tDraw.GetHexagon(0.f, true, ENUM::DrawRect::LAND), 2.5f, INIT_COLOR_GREEN);
	m_pUnitImage->Render(m_tDraw, m_tFrame);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(), 1.f, INIT_COLOR_RECT_COLLITION);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::IMAGE), 1.f, INIT_COLOR_RECT_IMAGE);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::LAND), 1.f, INIT_COLOR_RECT_LAND);
}

void CBavarian::Control()
{
	static D3DXVECTOR3 vPos;
	static D3DXVECTOR3 vDir;
	static D3DXVECTOR3 vAngle;

	if (!m_bControlFocus)
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
				vAngle = m_tDraw.vAngle;
				vPos = m_tDraw.vPos;

				if (m_tStatus.iMp == m_tStatus.iMaxMp)
				{
					SetDelayTime(ENUM::LiveTime::SKILL, 2000);
					m_tStatus.iMp = 0;

					vDir = FUNC::GET::Dir(m_tDraw.vAngle);
					vPos.y -= 60;
					vDir *= 100;
					vPos += vDir;
					CWhirlwind* pSkill = CWhirlwind::Create();
					pSkill->SetTeam(m_tStatus.eTeam);
					pSkill->SetTarget(ENUM::Target::PARENT, this);
					pSkill->GetStatusInfo().iAtt = int(m_tStatus.iAtt * 1.2);
					m_pObjMgr->AddObject(ENUM::ObjType::SKILL,
						pSkill);
				}
				if (IsActivateTime(ENUM::LiveTime::SKILL))
				{
					SetDelayTime(ENUM::LiveTime::SKILL, 0);
				}
				if (0 != GetDelayTime(ENUM::LiveTime::SKILL))
				{
					
				}
				else
				{
					CSoundMgr::GetInstance()->MyPlaySound(L"BavaAttack.wav", CSoundMgr::CHANNELID::EFFECT);
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

void CBavarian::FSM()
{
	if (m_eNextState == ENUM::State::DEAD)
		CSoundMgr::GetInstance()->MyPlaySound(L"dead.wav", CSoundMgr::CHANNELID::EFFECT);
	m_pUnitImage->ChangeState(m_eNextState, m_tFrame);
	if (ENUM::State::DEAD == m_eNextState)
		SetDelayTime(ENUM::LiveTime::DEAD, 3000);
}

void CBavarian::SetWhirlwind()
{
	m_pBavarianImage->SetWhirlwind(m_tFrame);
}
