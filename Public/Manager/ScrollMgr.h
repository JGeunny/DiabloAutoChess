#pragma once

class CKeyMgr;
class CObserver;
class CScrollMgr
{
	DECLARE_SINGLETON(CScrollMgr)
private:
	explicit		CScrollMgr();
	virtual			~CScrollMgr();

public:
	int				Initialize(CObserver* _pTerrain = nullptr, CObserver* _pObject = nullptr);
	int				Update();
	void			LateUpdate();
	void			Render();

public:
	void			InitScroll(float fX = 0.f, float fY = 0.f, float fZ = 0.f) { m_vScroll.x = fX; m_vScroll.y = fY; m_vScroll.z = fZ; }

public:
	void			AddScrollX(float _fSpeed) { m_vScroll.x += _fSpeed; }
	void			AddScrollY(float _fSpeed) { m_vScroll.y += _fSpeed; }
	void			AddScrollZ(float _fSpeed) { m_vScroll.z += _fSpeed; }

public:
	void			SetScroll(D3DXVECTOR3& _vScroll) { m_vScroll = _vScroll; }
	void			SetScroll(POINT& _ptScroll) { m_vScroll = { (float)_ptScroll.x, (float)_ptScroll.y, 0.f}; }
	void			SetTarget(ENUM::Target eID, CObserver* _pObj);

public:
	void			MouseLock();

public:
	D3DXVECTOR3&	GetScroll() { return m_vScroll; }
	void			ClientToScroll(LPPOINT lpPoint) {
		lpPoint->x += (LONG)m_vScroll.x;
		lpPoint->y += (LONG)m_vScroll.y;}
	CObserver*		GetTarget();

public:
	void			Control();

public:
	void			ScrollTarget();
	void			ScrollLock();

public:
	D3DXVECTOR3		m_vScroll;

private:
	CObserver*		m_pTarget; //Å¸°Ù ÀâÀº ³ð µû¶ó°¥²¨ÀÓ

private:
	CKeyMgr*		m_pKeyMgr;
	int				m_iMoveDir;
	RECT			m_rtScreen;
};

