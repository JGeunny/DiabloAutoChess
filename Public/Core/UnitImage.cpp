#include "stdafx.h"
#include "UnitImage.h"
#include "UnitImageImp.h"

CUnitImage::CUnitImage()
	: m_pImageImp(nullptr)
{
}

CUnitImage::~CUnitImage()
{
	Release();
}

HRESULT CUnitImage::Initialize(CUnitImageImp * _pImageImp)
{
	NULL_CHECK_MSG_RETURN(_pImageImp, L"CUnitImage Initialize::Not Exists CUnitImageImp", S_FALSE);
	m_pImageImp = _pImageImp;
	return S_OK;
}

void CUnitImage::Release()
{
	SafeDelete(m_pImageImp);
}

CUnitImage * CUnitImage::Create(CUnitImageImp * _pImageImp)
{
	CUnitImage* pInstance = new CUnitImage;
	if (FAILED(pInstance->Initialize(_pImageImp)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CUnitImage::ChangeState(ENUM::State & _eState, FRAME & _tFrame)
{
	m_pImageImp->ChangeState(_eState, _tFrame);
}

void CUnitImage::Render(DRAW_INFO & _tDrawInfo, FRAME& _tFrame, D3DXMATRIX* _pMatrix)
{
	m_pImageImp->Render(_tDrawInfo, _tFrame, _pMatrix);
}
