#include "stdafx.h"
//#include "../../Client/stdafx.h"
#include "FrameMgr.h"

IMPLEMENT_SINGLETON(CFrameMgr)

CFrameMgr::CFrameMgr()
{
}


CFrameMgr::~CFrameMgr()
{
}

void CFrameMgr::InitTime()
{
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceFrequency(&m_CPUTick);
}

bool CFrameMgr::LimitFrame(float fLimit)
{
	if (fLimit == -1.f) true;
	QueryPerformanceCounter(&m_CurTime);

	if (m_CurTime.QuadPart - m_OldTime.QuadPart > m_CPUTick.QuadPart)
	{
		QueryPerformanceCounter(&m_OldTime);
		QueryPerformanceCounter(&m_CurTime);
		QueryPerformanceFrequency(&m_CPUTick);
	}

	m_fLimitCount += float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CPUTick.QuadPart;
	m_fTimeCount += float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CPUTick.QuadPart;
	m_OldTime = m_CurTime;

	if ( 1.f / fLimit <= m_fLimitCount)
	{
		++m_iFPS_Count;
		m_fLimitCount = 0.f;
		return true;
	}	

	return false;
}

void CFrameMgr::RenderFPS()
{
	if (1.f <= m_fTimeCount)
	{				
		swprintf_s(m_szBuf, L"FPS: %d", m_iFPS_Count);
		m_fTimeCount = 0.f;
		m_iFPS_Count = 0;
	}

	/*CDeviceMgr::GetInstance()->DrawString(
		m_szBuf, lstrlen(m_szBuf), &FUNC::MATRIX::MatrixTranslation(D3DXVECTOR3(600.f, 100.f, 0.f))
	);*/
	CDeviceMgr::GetInstance()->DrawString(
		m_szBuf, lstrlen(m_szBuf), D3DXVECTOR3(150.f, 30.f, 0.f), DT_VCENTER
	);
}
