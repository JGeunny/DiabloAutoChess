#pragma once

#include "Observer.h"
#include "Astar.h"
#include "Mouse.h"
#include "Tile.h"
class CUnitControlImp
	:public CObserver
{
public:
	explicit CUnitControlImp();
	virtual ~CUnitControlImp();

public:
	virtual void Control(CGameObject* _pUnit) PURE;

protected:
	CTimeMgr*		m_pTimeMgr;
	CKeyMgr*		m_pKeyMgr;
	CControlMgr*	m_pControlMgr;
	CScrollMgr*		m_pScrollMgr;
	
protected:
	CAstar*			m_pAstar;
	D3DXVECTOR3		m_vTargetPos;
};

