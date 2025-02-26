#include "stdafx.h"
#include "ArcherControl.h"
#include "GameObject.h"
#include "ControlMgr.h"
#include "Terrain.h"

IMPLEMENT_CREATE_BASE(CArcherControl);
CArcherControl::CArcherControl()
{
}


CArcherControl::~CArcherControl()
{
}

HRESULT CArcherControl::Initialize()
{
	SetDelayTime(ENUM::LiveTime::MOVE, 3000);
	return S_OK;
}

void CArcherControl::Control(CGameObject* _pUnit)
{
	CObserver::LiveTime();
	static float fMoveDist = 200.f;
	static float fAttackDist = 600.f;
	auto& tDraw = _pUnit->GetDrawInfo();
	auto& eState = _pUnit->GetState();
	auto pObserver = _pUnit->GetTarget(ENUM::Target::ENEMY);
	auto& lstPath = m_pAstar->GetListPath();
	float fDist = D3DXVec3Length(&(m_vTargetPos - tDraw.vPos));

	auto pTerrain = CObjMgr::GetInstance()->GetTerrain();

	if (eState == ENUM::State::IDLE)
		m_pAstar->Release();
	if (!lstPath.empty())
	{
		eState = ENUM::State::WALK;
	}
	else
		eState = ENUM::State::IDLE;

	if (pObserver)
	{
		if (ENUM::ControlState::NOATTACK != CControlMgr::GetInstance()->GetControlState())
		{
			auto pEnemy = static_cast<CGameImage*>(pObserver);
			if (_pUnit->GetRecogDist() >= FUNC::MATH::Dist(_pUnit->GetPos(), pEnemy->GetPos()))
			{
				tDraw.SetAngle(pEnemy->GetPos());
				eState = ENUM::State::ATTACK;
				if (!lstPath.empty())
					lstPath.clear();
			}
		}
	}

	switch (eState)
	{
	case ENUM::State::NONE:
		break;
	case ENUM::State::IDLE:
	{
		if (pObserver)
		{
			if (lstPath.empty())
			{
				if (m_pControlMgr->IsPassTarget(pObserver))
				{
					auto pEnemy = static_cast<CGameImage*>(pObserver);
					m_pAstar->StartAstar(tDraw.vPos,
						pEnemy->GetPos());
					eState = ENUM::State::WALK;

					auto& lstThisPath = m_pAstar->GetListPath();
					if (lstThisPath.empty())
					{
						m_pControlMgr->AddCloseTarget(pEnemy);
					}
				}
			}
		}
		else
		{
			if (CObserver::IsActivateTime(ENUM::LiveTime::MOVE))
			{
				tDraw.vAngle.z = (float)(std::rand() * 1000 % 360);
				m_pAstar->StartAstar(tDraw.vPos,
					tDraw.vPos + FUNC::GET::Dir(tDraw.vAngle)*fMoveDist);
				eState = ENUM::State::WALK;
			}
		}
	}
		break;
	case ENUM::State::WALK:
		if (!lstPath.empty())
		{
			m_vTargetPos = lstPath.front()->GetDrawInfo().vPos;
			if (5.f > fDist)
				lstPath.pop_front();

			//static D3DXVECTOR3 vCheckPos;
			//vCheckPos = lstPath.front()->GetDrawInfo().vPos;
			//if (!pTerrain->IsGoable(vCheckPos))
			//{
			//	lstPath.clear();
			//	eState = ENUM::State::IDLE;
			//}
			//else
			//{
			//	m_vTargetPos = vCheckPos;
			//	if (5.f > fDist)
			//		lstPath.pop_front();
			//}
		}
		else
			eState = ENUM::State::IDLE;

		if (5.f <= fDist)
		{
			tDraw.SetAngle(m_vTargetPos);
			tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
		}
		break;
	case ENUM::State::ATTACK:
		break;
	case ENUM::State::DEAD:
		break;
	default:
		break;
	}
}

