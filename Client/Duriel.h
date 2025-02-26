#pragma once
#include "GameObject.h"

class CUnitImage;
class CUnitControl;
class CDuriel :
	public CGameObject
{
	DECLARE_CREATE(CDuriel)

protected:
	virtual HRESULT	Initialize();
	virtual HRESULT	LateInit();
	virtual void	Release();

public:
	virtual int		Update();
	virtual void	LateUpdate();
	virtual void	Render();

public:
	void			Control();

public:
	virtual	void FSM() override;// 유한 상태 기계(기본적인 인공지능)

public:
	static void		SetObjInfo(OBJ_INFO& _tObjInfo) { m_tObjInfo = _tObjInfo; }

private:
	static OBJ_INFO m_tObjInfo;

private:
	CUnitImage*		m_pUnitImage;
	CUnitControl*	m_pUnitControl;
	bool			m_bCanAttack;
};

