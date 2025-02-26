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

	for (auto& pDest : rSrc) // Ÿ���� �� ����
	{
		if (pDest->GetTeam() == ENUM::Team::NONE) continue; //�߸����̸� �н�
		if (pDest->IsEvent(ENUM::Event::DEAD)) continue;
		fNearDist = _fRecogDist;
		pTarget = nullptr;
		for (auto& pSource : rSrc) // Ÿ���� ���� ����
		{
			if (pSource->IsEvent(ENUM::Event::DEAD)) continue;
			if (pDest == pSource) continue;//�ڽ��̸� �н�
			if (pDest->GetTeam() == pSource->GetTeam()) continue; //���� ������ �н�
			if (pSource->GetTeam() == ENUM::Team::NONE) continue; //�߸����̸� �н�
			if (pSource->GetDrawInfo().color == INIT_COLOR_OPACITY) continue;//�������̸� �н�

			//pDest�� ��ȿ�Ÿ� �ȿ� �ֵ��� Ÿ���� �ϱ�
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
	for (auto& pDest : rSrc) // �츮��
	{
		if (pDest->GetTeam() == ENUM::Team::NONE) continue; //�߸����̸� �н�
		if (pDest->IsEvent(ENUM::Event::DEAD)) continue;
		if (ENUM::Team::ONE != pDest->GetTeam()) continue;
		for (auto& pSource : rSrc) // ����
		{
			if (pSource->IsEvent(ENUM::Event::DEAD)) continue;
			if (pDest == pSource) continue;//�ڽ��̸� �н�
			if (ENUM::Team::ONE == pSource->GetTeam()) continue;
			if (pSource->GetTeam() == ENUM::Team::NONE) continue; //�߸����̸� �н�
			rcDest = pDest->GetRect();
			rcSrc = pSource->GetRect();
			if (IntersectRect(&rc, &rcDest, &rcSrc))
			{
				//���� �浹�ߴٸ� ��Ʋ�ʵ�� ����������
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
			if (pDest == pSource) continue;//�ڽ��̸� �н�
			if (pSource->GetTeam() == pDest->GetTeam()) continue;
			rcDest = pDest->GetRect();
			rcSrc = pSource->GetRect();
			if (IntersectRect(&rc, &rcDest, &rcSrc))
			{
				//�̳��� �¾Ҵ� ������ üũ pSource��ų pDest����
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
			if (pDest == pSource) continue;//�ڽ��̸� �н�
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
	if (fRadiusSum > fDist)//�浹
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
//		if (pDest->GetTarget(TARGET::ENEMY)) continue;	// Ÿ���� ���� ��� ã��
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
