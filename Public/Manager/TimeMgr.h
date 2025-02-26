#pragma once
class CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)

private:
	CTimeMgr();
	~CTimeMgr();

public:
	float GetDeltaTime() const;
	UINT  GetNowTime() const;

public:
	void InitTime();
	void UpdateTime();

private:
	LARGE_INTEGER	m_OldTime;
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_CpuTick;

	UINT			m_uNowTime;
	float			m_fDeltaTime;
};

