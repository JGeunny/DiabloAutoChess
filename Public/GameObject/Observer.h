#pragma once

class CObserver
{
protected:
	explicit CObserver();
public:
	virtual ~CObserver();

public:
	static CObserver* Create();

protected:
	virtual UINT			LiveTime();

public:
	void					InitData();

public:
	//목표 타게팅(옵저버 패턴)
	virtual void			MessageTo(ENUM::Event _eEvent);
	void					SetTarget(ENUM::Target _eTarget, CObserver* _pTarget);
	CObserver*				GetTarget(ENUM::Target _eTarget) { return m_pTarget[(int)_eTarget]; }
	void					ClearTarget(ENUM::Target _eTarget = ENUM::Target::END);

public:
	bool					ExistTargetedAtMe(ENUM::Target _eTarget, CObserver* _pFind);
	void					AddTargetedAtMe(ENUM::Target _eTarget, CObserver* _pInput);
	bool					AlterTargetedAtMe(ENUM::Target _eTarget, CObserver* _pFind, CObserver* _pInput);

public:
	bool					IsEvent(ENUM::Event _eEvent) { return (m_eEvent == _eEvent); }
	bool					IsActivateTime(ENUM::LiveTime _eTime);

public:
	void					SetEvent(ENUM::Event _eEvent) { m_eEvent = _eEvent;}
	void					SetDelayTime(ENUM::LiveTime _eDelayTimeType, int _iDelayTime) {
								m_uLiveTime[(int)_eDelayTimeType] = m_pTimeMgr->GetNowTime();
								m_iLiveTimeCycle[(int)_eDelayTimeType] = _iDelayTime;
							}

public:
	int						GetDelayTime(ENUM::LiveTime _eDelayTimeType) { return m_iLiveTimeCycle[(int)_eDelayTimeType]; }
	
private:
	//시간에 따른 소멸 및 유지시간
	UINT					m_uLiveTime[(int)ENUM::LiveTime::END];
	int						m_iLiveTimeCycle[(int)ENUM::LiveTime::END];

protected:
	//목표 타게팅
	std::list<CObserver*>	m_lstTargetedAtMe[(int)ENUM::Target::END];	//나를 타겟팅한 놈들
	CObserver*				m_pTarget[(int)ENUM::Target::END];			//내가 타겟팅한 놈

protected:
	ENUM::Event				m_eEvent;

protected:
	CTimeMgr*				m_pTimeMgr;
};

