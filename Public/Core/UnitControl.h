#pragma once

class CUnitControlImp;
class CUnitControl
{
protected:
	explicit CUnitControl();

public:
	virtual ~CUnitControl();

private:
	HRESULT	Initialize(CUnitControlImp* _pControlImp);
	void	Release();

public:
	static CUnitControl*	Create(CUnitControlImp* _pControlImp);

public:
	void	Control(CGameObject* _pUnit);

private:
	CUnitControlImp*	m_pControlImp;
};

