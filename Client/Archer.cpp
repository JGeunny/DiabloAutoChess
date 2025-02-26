#include "stdafx.h"
#include "Archer.h"
#include "UnitImage.h"
#include "AmazonImage.h"
#include "DurielImage.h"
#include "BavarianImage.h"
#include "AndarielImage.h"
#include "DiaImage.h"
#include "IzualImage.h"
#include "BarlogImage.h"

#include "UnitControl.h"
#include "ArcherControl.h"

#include "Arrow.h"
#include "IceBolt.h"
#include "FrozenOrb.h"
#include "Laser.h"

#include "BoneSprite.h"

OBJ_INFO CArcher::m_tObjInfo = {};
IMPLEMENT_CREATE(CArcher)
CArcher::CArcher()
	: m_pUnitImage(nullptr)
	, m_pUnitControl(nullptr)
	, m_bCanAttack(false)
{
}


CArcher::~CArcher()
{
	Release();
}

HRESULT CArcher::Initialize()
{
	m_bInfoRender = true;
	/*m_tDraw.vSize.x = float(UNITCX);
	m_tDraw.vSize.y = float(UNITCY);*/

	//아마존
	//m_tDraw.vSize.x = UNITCX;
	//m_tDraw.vSize.y = UNITCY;
	//m_tDraw.vPosFit = { 0.f, -50.f, 0.f };
	//m_tDraw.vSizeCollision = { 50.f, 120.f, 0.f };
	//m_tDraw.vSizeLand = { TILECX, TILECY, 0.f };
	//m_tDraw.vAngle.z = 270.f;

	//바바리안
	//m_tDraw.vSize.x = 300;
	//m_tDraw.vSize.y = 300;
	//m_tDraw.vPosFit = { 0.f, -30.f, 0.f };
	//m_tDraw.vSizeCollision = { 50.f, 120.f, 0.f };
	//m_tDraw.vSizeLand = { 50.f, 50.f, 0.f };

	//듀리얼
	//m_tDraw.vSize.x = 250;
	//m_tDraw.vSize.y = 250;
	//m_tDraw.vPosFit = { 0.f, -30.f, 0.f };
	//m_tDraw.vSizeCollision = { 140.f, 140.f, 0.f };
	//m_tDraw.vSizeLand = { 50.f, 50.f, 0.f };

	//디아블로
	//m_tDraw.vSize.x = 300;
	//m_tDraw.vSize.y = 300;
	//m_tDraw.vPosFit = { 0.f, -30.f, 0.f };
	//m_tDraw.vSizeCollision = { 140.f, 140.f, 0.f };
	//m_tDraw.vSizeLand = { 50.f, 50.f, 0.f };

	m_tDraw.SetData(m_tObjInfo.tDraw);
	m_tStatus.SetData(m_tObjInfo.tStatus);

	m_tDraw.vAngle.z = 270.f;
	m_tDraw.fSpeed = INIT_SPEED;

	m_pUnitImage = CUnitImage::Create(CAmazonImage::Create());
	m_pUnitControl = CUnitControl::Create(CArcherControl::Create());

	SetDelayTime(ENUM::LiveTime::SKILL, 400);

	lstrcpy(m_tStatus.szName, L"아마존");
	//m_tStatus.iAtt = 60;
	//m_tStatus.iMaxHp = 300;
	//m_tStatus.iMaxMp = 100;
	m_tStatus.FnRecovery();
	m_tStatus.iMp = 0;

	return S_OK;
}

HRESULT CArcher::LateInit()
{
	//m_vTargetPos = m_tDraw.vPos;
	return S_OK;
}

void CArcher::Release()
{
	SafeDelete(m_pUnitImage);
	SafeDelete(m_pUnitControl);
}

int CArcher::Update()
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

void CArcher::LateUpdate()
{
	CGameImage::MoveFrame();
	CGameObject::FSM();
}

void CArcher::Render()
{
	if(m_bControlFocus)
		m_pDeviceMgr->DrawHexagon(m_tDraw.GetHexagon(0.f, true, ENUM::DrawRect::LAND), 2.5f, INIT_COLOR_GREEN);
	m_pUnitImage->Render(m_tDraw, m_tFrame);
}


void CArcher::Control()
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
			CSoundMgr::GetInstance()->MyPlaySound(L"Arrow.wav", CSoundMgr::CHANNELID::EFFECT);
			vAngle = m_tDraw.vAngle;
			vPos = m_tDraw.vPos;
			if (m_tStatus.iMp == m_tStatus.iMaxMp)
			{
				SetDelayTime(ENUM::LiveTime::SKILL, 2000);
				m_tStatus.iMp = 0;
			}
			if (IsActivateTime(ENUM::LiveTime::SKILL))
			{
				SetDelayTime(ENUM::LiveTime::SKILL, 0);
			}

			if(0 != GetDelayTime(ENUM::LiveTime::SKILL))
			{
				vAngle.z -= 50;
				for (int i = 0; i < 18; ++i)
				{
					vPos = m_tDraw.vPos;
					vAngle.z += 5;
					vDir = FUNC::GET::Dir(vAngle);
					vPos.y -= 60;
					vDir *= 40;
					vPos += vDir;
					CArrow* pSkill = CArrow::Create(vPos.x, vPos.y, vAngle.z);
					pSkill->SetTeam(m_tStatus.eTeam);
					pSkill->GetStatusInfo().iAtt = m_tStatus.iAtt;
					m_pObjMgr->AddObject(ENUM::ObjType::SKILL,
						pSkill);
				}
			}
			else
			{
				m_tStatus.iMp += 20;
				
				vDir = FUNC::GET::Dir(m_tDraw.vAngle);
				vPos.y -= 60;
				vDir *= 40;
				vPos += vDir;
				CGameObject* pSkill = CBulletPoolMgr::GetInstance()->GetBullet(CBulletPoolMgr::eArrow);
				if (pSkill)
				{
					pSkill->SetPos(vPos);
					pSkill->SetAngle(vAngle.z);
				}
				else
				{
					pSkill = CArrow::Create(vPos.x, vPos.y, vAngle.z);
				}
				pSkill->SetTeam(m_tStatus.eTeam);
				pSkill->GetStatusInfo().iAtt = m_tStatus.iAtt;
				m_pObjMgr->AddObject(ENUM::ObjType::SKILL,
					pSkill);
				//CGameObject* pSkill = CLaser::Create(vPos.x, vPos.y, vAngle.z);
				//pSkill->SetTeam(m_tStatus.eTeam);
				//pSkill->GetStatusInfo().iAtt = m_tStatus.iAtt;
				//m_pObjMgr->AddObject(ENUM::ObjType::SKILL,
				//	pSkill);

				//CGameObject* pSkill = CBoneSprite::Create(vPos.x, vPos.y, vAngle.z);
				//pSkill->SetTeam(m_tStatus.eTeam);
				//pSkill->GetStatusInfo().iAtt = m_tStatus.iAtt;
				//m_pObjMgr->AddObject(ENUM::ObjType::EFFECT,
				//	pSkill);
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

void CArcher::FSM()
{
	if (m_eNextState == ENUM::State::DEAD)
		CSoundMgr::GetInstance()->MyPlaySound(L"dead.wav", CSoundMgr::CHANNELID::EFFECT);
	m_pUnitImage->ChangeState(m_eNextState, m_tFrame);
	if(ENUM::State::DEAD == m_eNextState)
		SetDelayTime(ENUM::LiveTime::DEAD, 3000);
}
