#include "stdafx.h"
#include "UnitControl.h"
#include "UnitControlImp.h"

CUnitControl::CUnitControl()
{
}


CUnitControl::~CUnitControl()
{
	Release();
}

HRESULT CUnitControl::Initialize(CUnitControlImp * _pControlImp)
{
	if (!_pControlImp) return S_FALSE;
	m_pControlImp = _pControlImp;
	return S_OK;
}

void CUnitControl::Release()
{
	SafeDelete(m_pControlImp);
}

CUnitControl * CUnitControl::Create(CUnitControlImp * _pControlImp)
{
	CUnitControl* pInstance = new CUnitControl;
	if (FAILED(pInstance->Initialize(_pControlImp)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CUnitControl::Control(CGameObject* _pUnit)
{
	m_pControlImp->Control(_pUnit);
}
