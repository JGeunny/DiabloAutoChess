#pragma once
#include "UnitControlImp.h"
class CArcherControl :
	public CUnitControlImp
{
	DECLARE_CREATE_BASE(CArcherControl)

public:
	HRESULT		Initialize();

public:
	virtual void Control(CGameObject* _pUnit);

};

