#include "stdafx.h"
#include "Observer.h"

CObserver::CObserver()
	: m_pTimeMgr(CTimeMgr::GetInstance())
{
	InitData();
}

CObserver::~CObserver()
{
	MessageTo(ENUM::Event::DEAD);
}

CObserver * CObserver::Create()
{
	CObserver* pInstance = new CObserver();
	return pInstance;
}

UINT CObserver::LiveTime()
{
	for (int i = 0; i < (int)ENUM::LiveTime::END; ++i)
	{
		if (0 == m_iLiveTimeCycle[i]) continue;
		if (m_uLiveTime[i] + m_iLiveTimeCycle[i] < m_pTimeMgr->GetNowTime())
		{
			switch ((ENUM::LiveTime)i)
			{
			case ENUM::LiveTime::LIVE:
				m_eEvent = ENUM::Event::DEAD;
				break;
			}
		}
			
	}
	return m_pTimeMgr->GetNowTime();
}

void CObserver::InitData()
{
	m_eEvent = ENUM::Event::NOEVENT;
	ZeroMemory(m_pTarget, sizeof(m_pTarget));
	ZeroMemory(m_uLiveTime, sizeof(m_uLiveTime));
	ZeroMemory(m_iLiveTimeCycle, sizeof(m_iLiveTimeCycle));
	for (int i = 0; i < (int)ENUM::LiveTime::END; ++i)
	{
		m_uLiveTime[i] = m_pTimeMgr->GetNowTime();
	}
}

void CObserver::MessageTo(ENUM::Event _eEvent)
{
	if (_eEvent == ENUM::Event::DEAD)
	{
		for (int i = 0; i < (int)ENUM::Target::END; ++i)
		{
			ClearTarget((ENUM::Target)i);
			for (auto& pTargetedAtMe : m_lstTargetedAtMe[i])
			{
				if (pTargetedAtMe)
					pTargetedAtMe->SetTarget((ENUM::Target)i, nullptr);
			}
			m_lstTargetedAtMe[i].clear();
		}
	}
}

void CObserver::SetTarget(ENUM::Target _eTarget, CObserver * _pTarget)
{
	if (m_pTarget[(int)_eTarget] == _pTarget) return;

	ClearTarget(_eTarget);
	if (_pTarget)
	{
		if (!_pTarget->ExistTargetedAtMe(_eTarget, this))
			_pTarget->AddTargetedAtMe(_eTarget, this);
	}
	m_pTarget[(int)_eTarget] = _pTarget;
}

void CObserver::ClearTarget(ENUM::Target _eTarget)
{
	if (m_pTarget[(int)_eTarget])
	{
		m_pTarget[(int)_eTarget]->AlterTargetedAtMe(_eTarget, this, nullptr);
		m_pTarget[(int)_eTarget] = nullptr;
	}
}

bool CObserver::ExistTargetedAtMe(ENUM::Target _eTarget, CObserver * _pFind)
{
	for (auto& pObj : m_lstTargetedAtMe[(int)_eTarget]) {
		if (pObj == _pFind) {
			return true;
		}
	}
	return false;
}

void CObserver::AddTargetedAtMe(ENUM::Target _eTarget, CObserver * _pInput)
{
	m_lstTargetedAtMe[(int)_eTarget].emplace_back(_pInput);
}

bool CObserver::AlterTargetedAtMe(ENUM::Target _eTarget, CObserver * _pFind, CObserver * _pInput)
{
	bool doAlter = false;
	for (auto& pObj : m_lstTargetedAtMe[(int)_eTarget]) {
		if (pObj == _pFind) {
			pObj = _pInput;
			doAlter = true;
		}
	}
	return doAlter;
}

bool CObserver::IsActivateTime(ENUM::LiveTime _eTime)
{
	if (m_iLiveTimeCycle[(int)_eTime] == 0) return false;
	if (m_uLiveTime[(int)_eTime] + m_iLiveTimeCycle[(int)_eTime] < m_pTimeMgr->GetNowTime())
	{
		m_uLiveTime[(int)_eTime] = m_pTimeMgr->GetNowTime();
		return true;
	}
	return false;
}
