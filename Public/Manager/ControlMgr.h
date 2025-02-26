#pragma once

class CMouse;
class CAstar;
class CObserver;
class CGameObject;
class CScrollMgr;
class CControlMgr
{
	DECLARE_SINGLETON(CControlMgr)
public:
	explicit CControlMgr();
	virtual ~CControlMgr();

public:
	HRESULT	Initialize();
	void	Update();
	void	Rander();

public:
	void	ChangeTarget();
	void	CameraFocus(bool _bCameraFocus = false);

private:
	void	Release();
	void	Control(CGameObject* _pUnit);

public:
	void			SetTarget(CGameObject* _pObj);

public:
	CMouse*			GetMouse() { return m_pMouse; }
	CObserver*		GetTarget();

public:
	void			SetControlState(ENUM::ControlState _eControlState) { m_eControlState = _eControlState; }
public:
	ENUM::ControlState& GetControlState() { return m_eControlState; }

public:
	void			AddCloseTarget(CObserver* _pCloseTarget);
public:
	bool			IsPassTarget(CObserver* _pCloseTarget);

private:
	CKeyMgr*	m_pKeyMgr;
	//CObjMgr*	m_pObjMgr;
	CTimeMgr*	m_pTimeMgr;
	CScrollMgr*	m_pScrollMgr;

private:
	CMouse*		m_pMouse;
	CObserver*	m_pTarget;
	CAstar*		m_pAstar;
	D3DXVECTOR3	m_vTargetPos;

private:
	bool		m_bCameraFocus;
	ENUM::ControlState m_eControlState;

	DRAW_INFO	m_tDrawSelect;


private:
	std::list<CObserver*> m_lstCloseTargetAstar; //못가는 타겟은 한프레임 동안은 계속 못가도록 하자
};

