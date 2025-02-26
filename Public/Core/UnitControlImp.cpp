#include "stdafx.h"
#include "UnitControlImp.h"

CUnitControlImp::CUnitControlImp()
	:m_pTimeMgr(CTimeMgr::GetInstance())
	, m_pKeyMgr(CKeyMgr::GetInstance())
	, m_pControlMgr(CControlMgr::GetInstance())
	, m_pScrollMgr(CScrollMgr::GetInstance())
	, m_pAstar(nullptr)
	, m_vTargetPos({0.f,0.f,0.f})
{
	m_pAstar = CAstar::Create();
}


CUnitControlImp::~CUnitControlImp()
{
	SafeDelete(m_pAstar);
}
