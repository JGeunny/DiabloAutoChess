#include "stdafx.h"
#include "Duriel.h"

#include "UnitImage.h"
#include "DurielImage.h"

#include "UnitControl.h"
#include "ArcherControl.h"
#include "BoneSprite.h"

OBJ_INFO CDuriel::m_tObjInfo = {};
IMPLEMENT_CREATE(CDuriel)
CDuriel::CDuriel()
	: m_pUnitImage(nullptr)
	, m_pUnitControl(nullptr)
	, m_bCanAttack(false)
{
}


CDuriel::~CDuriel()
{
	Release();
}

HRESULT CDuriel::Initialize()
{
	m_bInfoRender = true;

	//m_tDraw.vSize.x = 250;
	//m_tDraw.vSize.y = 250;
	//m_tDraw.vPosFit = { 0.f, -30.f, 0.f };
	//m_tDraw.vSizeCollision = { 140.f, 140.f, 0.f };
	//m_tDraw.vSizeLand = { TILECX, TILECY, 0.f };
	m_tDraw.SetData(m_tObjInfo.tDraw);
	m_tStatus.SetData(m_tObjInfo.tStatus);

	m_tDraw.vAngle.z = 270.f;
	m_tDraw.fSpeed = INIT_SPEED;

	m_pUnitImage = CUnitImage::Create(CDurielImage::Create());

	SetDelayTime(ENUM::LiveTime::SKILL, 400);

	lstrcpy(m_tStatus.szName, L"µà¸®¿¤");
	//m_tStatus.iAtt = 50;
	//m_tStatus.iMaxHp = 800;
	//m_tStatus.iMaxMp = 100;
	m_tStatus.FnRecovery();
	m_tStatus.iMp = 0;

	m_pUnitControl = CUnitControl::Create(CArcherControl::Create());

	return S_OK;
}

HRESULT CDuriel::LateInit()
{
	return S_OK;
}

void CDuriel::Release()
{
	SafeDelete(m_pUnitImage);
	SafeDelete(m_pUnitControl);
}

int CDuriel::Update()
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

void CDuriel::LateUpdate()
{
	CGameImage::MoveFrame();
	CGameObject::FSM();
}

void CDuriel::Render()
{
	if (m_bControlFocus)
		m_pDeviceMgr->DrawHexagon(m_tDraw.GetHexagon(0.f, true, ENUM::DrawRect::LAND), 2.5f, INIT_COLOR_GREEN);
	m_pUnitImage->Render(m_tDraw, m_tFrame);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(), 1.f, INIT_COLOR_RECT_COLLITION);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::IMAGE), 1.f, INIT_COLOR_RECT_IMAGE);
	//m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::LAND), 1.f, INIT_COLOR_RECT_LAND);
}

void CDuriel::Control()
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
			CSoundMgr::GetInstance()->MyPlaySound(L"DurielAttack.wav", CSoundMgr::CHANNELID::EFFECT);
			vAngle = m_tDraw.vAngle;
			vPos = m_tDraw.vPos;
			if (m_tStatus.iMp == m_tStatus.iMaxMp)
			{
				CBoneSprite* pSkill = CBoneSprite::Create(vPos.x, vPos.y, vAngle.z);
				pSkill->SetTeam(m_tStatus.eTeam);
				pSkill->GetStatusInfo().iAtt = int(m_tStatus.iAtt * 0.5f);
				m_pObjMgr->AddObject(ENUM::ObjType::EFFECT,
					pSkill);
				m_tStatus.iMp = 0;
			}

			m_tStatus.iMp += 10;
			auto pEnemy = CObserver::GetTarget(ENUM::Target::ENEMY);
			if (pEnemy)
			{
				auto& tStatus = static_cast<CGameObject*>(pEnemy)->GetStatusInfo();
				tStatus.iHp -= m_tStatus.iAtt;
				if (tStatus.iHp < 0)
					tStatus.iHp = 0;
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
}

void CDuriel::FSM()
{
	if (m_eNextState == ENUM::State::DEAD)
	{
		CSoundMgr::GetInstance()->MyPlaySound(L"durieldeath.wav", CSoundMgr::CHANNELID::EFFECT);
	}
	m_pUnitImage->ChangeState(m_eNextState, m_tFrame);
}
