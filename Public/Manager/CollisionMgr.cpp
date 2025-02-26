#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"
#include "LeadershipMgr.h"
#include "Bone.h"

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::TargetUnit(std::list<CGameObject*>& rSrc, float _fRecogDist)
{
	static RECT rc, rcDest, rcSrc;
	static CGameObject* pTarget;
	static float		fNearDist, fNearDistTemp;

	for (auto& pDest : rSrc) // 타겟팅 할 유닛
	{
		if (pDest->GetTeam() == ENUM::Team::NONE) continue; //중립국이면 패스
		if (pDest->IsEvent(ENUM::Event::DEAD)) continue;
		fNearDist = _fRecogDist;
		pTarget = nullptr;
		for (auto& pSource : rSrc) // 타겟팅 당할 유닛
		{
			if (pSource->IsEvent(ENUM::Event::DEAD)) continue;
			if (pDest == pSource) continue;//자신이면 패스
			if (pDest->GetTeam() == pSource->GetTeam()) continue; //팀이 같으면 패스
			if (pSource->GetTeam() == ENUM::Team::NONE) continue; //중립국이면 패스
			if (pSource->GetDrawInfo().color == INIT_COLOR_OPACITY) continue;//은신중이면 패스

			//pDest의 유효거리 안에 있따면 타게팅 하기
			fNearDistTemp = FUNC::MATH::Dist(pDest->GetPos(), pSource->GetPos());
			if (fNearDist >= fNearDistTemp)
			{
				fNearDist = fNearDistTemp;
				pTarget = pSource;
			}
		}
		//if (!pDest->GetTarget(ENUM::Target::ENEMY))
		pDest->SetTarget(ENUM::Target::ENEMY, pTarget);
	}
}

bool CCollisionMgr::CollisionGoToBattleField(std::list<CGameObject*>& rSrc)
{
	static RECT rc, rcDest, rcSrc;
	for (auto& pDest : rSrc) // 우리팀
	{
		if (pDest->GetTeam() == ENUM::Team::NONE) continue; //중립국이면 패스
		if (pDest->IsEvent(ENUM::Event::DEAD)) continue;
		if (ENUM::Team::ONE != pDest->GetTeam()) continue;
		for (auto& pSource : rSrc) // 적팀
		{
			if (pSource->IsEvent(ENUM::Event::DEAD)) continue;
			if (pDest == pSource) continue;//자신이면 패스
			if (ENUM::Team::ONE == pSource->GetTeam()) continue;
			if (pSource->GetTeam() == ENUM::Team::NONE) continue; //중립국이면 패스
			rcDest = pDest->GetRect();
			rcSrc = pSource->GetRect();
			if (IntersectRect(&rc, &rcDest, &rcSrc))
			{
				//적과 충돌했다면 배틀필드로 보내버리기
				CLeadershipMgr::GetInstance()->GoToBattleField(0, pDest, pSource);
				return true;
			}
		}
	}
	return false;
}

void CCollisionMgr::CollisionRect(std::list<CGameObject*>& rDst, std::list<CGameObject*>& rSrc)
{
	static RECT rc, rcDest, rcSrc;
	for (auto& pDest : rDst)
	{
		if (pDest->IsEvent(ENUM::Event::DEAD)) continue;
		for (auto& pSource : rSrc)
		{
			if (pSource->IsEvent(ENUM::Event::DEAD)) continue;
			if (pDest == pSource) continue;//자신이면 패스
			if (pSource->GetTeam() == pDest->GetTeam()) continue;
			rcDest = pDest->GetRect();
			rcSrc = pSource->GetRect();
			if (IntersectRect(&rc, &rcDest, &rcSrc))
			{
				//이놈이 맞았던 놈인지 체크 pSource스킬 pDest유닛
				if (!(pSource->IsHit(pDest)))continue;
				if(pSource->ReceiveAttack(1))
					pSource->SetEvent(ENUM::Event::DEAD);
				
				if (pDest->ReceiveAttack(pSource->GetStatusInfo().iAtt))
					pDest->SetEvent(ENUM::Event::DEAD);

				if (dynamic_cast<CBone*>(pSource))
				{
					pDest->SetStun(true);
				}
			}
		}
	}
}
void CCollisionMgr::CollisionRectEx(std::list<CGameObject*>& rDst, std::list<CGameObject*>& rSrc)
{
	RECT rtMove = {};
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{
		if (pDest->IsEvent(ENUM::Event::DEAD)) continue;
		DRAW_INFO& tDst = pDest->GetDrawInfo();

		for (auto& pSource : rSrc)
		{
			if (pSource->IsEvent(ENUM::Event::DEAD)) continue;
			if (pDest == pSource) continue;//자신이면 패스
			DRAW_INFO& tSrc = pSource->GetDrawInfo();
			static RECT rtDest, rtSource;
			rtDest = pDest->GetDrawInfo().GetRect(0.f, true, ENUM::DrawRect::LAND);
			rtSource = pSource->GetDrawInfo().GetRect(0.f, true, ENUM::DrawRect::LAND);
			if (IntersectRect(&rtMove, &rtDest, &rtSource))
			{
				fMoveX = float(rtMove.right - rtMove.left);
				fMoveY = float(rtMove.bottom - rtMove.top);
				if (fMoveX > fMoveY)
				{
					if (tSrc.vPos.y < tDst.vPos.y)
						fMoveY *= -1.f;
					tSrc.vPos.y += fMoveY;
				}
				else
				{
					if (tSrc.vPos.x < tDst.vPos.x)
						fMoveX *= -1.f;
					tSrc.vPos.x += fMoveX;
				}
			}
		}
	}
}

void CCollisionMgr::CollisionRectEx(CGameObject * pDest, CGameObject * pSrc)
{
	RECT rtMove = {};
	float fMoveX = 0.f, fMoveY = 0.f;

	if (pDest->IsEvent(ENUM::Event::DEAD)) return;
	DRAW_INFO& tDst = pDest->GetDrawInfo();

	if (pSrc->IsEvent(ENUM::Event::DEAD)) return;

	DRAW_INFO& tSrc = pSrc->GetDrawInfo();
	static RECT rtDest, rtSource;
	rtDest = pDest->GetDrawInfo().GetRect(0.f, true, ENUM::DrawRect::LAND);
	rtSource = pSrc->GetDrawInfo().GetRect(0.f, true, ENUM::DrawRect::LAND);
	if (IntersectRect(&rtMove, &rtDest, &rtSource))
	{
		fMoveX = float(rtMove.right - rtMove.left);
		fMoveY = float(rtMove.bottom - rtMove.top);
		if (fMoveX > fMoveY)
		{
			if (tSrc.vPos.y < tDst.vPos.y)
				fMoveY *= -1.f;
			tSrc.vPos.y += fMoveY;
		}
		else
		{
			if (tSrc.vPos.x < tDst.vPos.x)
				fMoveX *= -1.f;
			tSrc.vPos.x += fMoveX;
		}
	}
}

void CCollisionMgr::CollisionSphereEx(CGameObject * pDst, CGameObject * pSrc)
{
	if (pDst->IsEvent(ENUM::Event::DEAD)) return;
	if (pSrc->IsEvent(ENUM::Event::DEAD)) return;

	DRAW_INFO& tDst = pDst->GetDrawInfo();
	DRAW_INFO& tSrc = pSrc->GetDrawInfo();
	float fRadiusSum = ((tDst.GetSizeLand().x ) * 0.4f) + ((tSrc.GetSizeLand().x ) * 0.4f);
	
	float fDist = FUNC::MATH::Dist(tDst.vPos, tSrc.vPos);
	if (fRadiusSum > fDist)//충돌
	{
		D3DXVECTOR3 vLook = { 1.f, 0.f, 0.f };
		D3DXVECTOR3 vAngle = FUNC::GET::Angle(tSrc.vPos, tDst.vPos, vLook);
		tSrc.vPos = tDst.vPos + FUNC::GET::Dir(vAngle) * (fRadiusSum + 1);
	}
}

//void CCollisionMgr::CollisionSphere(list<CObj*>& rDst, list<CObj*>& rSrc)
//{
//	for (auto& pDest : rDst)
//	{
//		for (auto& pSource : rSrc)
//		{
//			if (CheckSphere(pDest, pSource))
//			{
//				pDest->AlterEvent() = EVENT::DEAD;
//				pSource->AlterEvent() = EVENT::DEAD;
//			}
//		}
//	}
//}
//
bool CCollisionMgr::CheckSphere(CGameObject * pDst, CGameObject * pSrc)
{

	DRAW_INFO& tDst = pDst->GetDrawInfo();
	DRAW_INFO& tSrc = pSrc->GetDrawInfo();
	float fRadiusSum = ((tDst.GetSizeLand().x) * 0.5f) + ((tSrc.GetSizeLand().x) * 0.5f);

	float fDist = FUNC::MATH::Dist(tDst.vPos, tSrc.vPos);
	return fRadiusSum > fDist;
}
//
//void CCollisionMgr::ObjOnMouse(list<CObj*>& rObj, CObj * pMouse)
//{
//	RECT rc = {};
//	//static_cast<CMouse*>(pMouse)->SetAttack(false);
//	for (auto& pObj : rObj)
//	{
//		if (pObj->IsEvent(EVENT::DEAD)) continue;
//		if (pObj->IsTeam(TEAM::ONE)) continue;
//
//		if (IntersectRect(&rc, &pMouse->GetRect(), &pObj->GetRect()))
//		{
//			//static_cast<CMouse*>(pMouse)->SetAttack(true);
//			break;
//		}
//	}
//}
//
//void CCollisionMgr::TargetEnemy(list<CObj*>& rDst, list<CObj*>& rSrc)
//{
//	CObj*		pTarget = nullptr;
//	float		fShortest = 9999;
//	float		fDist = 0;
//
//	for (auto& pDest : rDst)
//	{
//		if (pDest->IsEvent(EVENT::DEAD)) continue;
//		if (pDest->GetTarget(TARGET::ENEMY)) continue;	// 타겟이 없을 경우 찾기
//
//		fShortest = 9999, fDist = 0;
//		DRAW_INFO& tDst = pDest->AlterDraw();
//		for (auto& pSrc : rSrc)
//		{
//			if (pSrc->IsEvent(EVENT::DEAD)) continue;
//			if (pDest->IsTeam(pSrc->AlterTeam())) continue;
//
//			DRAW_INFO tSrc = pSrc->AlterDraw();
//			fDist = tSrc.GetDist(tDst.vPos);
//			if (pDest->IsRecogDist(fDist))
//			{
//				if (fShortest > fDist)
//				{
//					pTarget = pSrc;
//					fShortest = fDist;
//				}
//			}
//		}
//		if (pTarget)
//		{
//			pDest->SetTarget(TARGET::ENEMY, pTarget);
//		}
//	}
//}
