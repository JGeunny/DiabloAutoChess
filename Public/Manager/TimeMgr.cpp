#include "stdafx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
	: m_fDeltaTime(0.f)
	, m_uNowTime(0)
{
}


CTimeMgr::~CTimeMgr()
{
}

float CTimeMgr::GetDeltaTime() const
{
	return m_fDeltaTime;
}

UINT CTimeMgr::GetNowTime() const
{
 	return m_uNowTime;
}

void CTimeMgr::InitTime()
{
	// ���κ���(�ϵ����)�� ���� �ִ� ���ػ� Ÿ�̸� ���� ������ �Լ�.
	// �� Ÿ�̸� ���� CPU�� �������� ���� ����ȴ�. Ÿ�̸� �� = CPU ���� ������
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceCounter(&m_CurTime);

	// CPU�� �ʴ� �������� ������ �Լ�.
	QueryPerformanceFrequency(&m_CpuTick);

	m_uNowTime = UINT((float)m_CurTime.QuadPart / m_CpuTick.QuadPart * 1000);

	std::srand(unsigned(time(NULL)));
}

void CTimeMgr::UpdateTime()
{
	QueryPerformanceCounter(&m_CurTime);

	if(m_CurTime.QuadPart - m_OldTime.QuadPart > m_CpuTick.QuadPart)
		QueryPerformanceFrequency(&m_CpuTick);

	m_fDeltaTime = 
		float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;

	m_OldTime.QuadPart = m_CurTime.QuadPart;
	m_uNowTime = UINT((float)m_CurTime.QuadPart / m_CpuTick.QuadPart * 1000);
}
