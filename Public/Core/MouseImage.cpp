#include "stdafx.h"
#include "MouseImage.h"
#include "MouseImageImp.h"

CMouseImage::CMouseImage()
	:m_pImageImp(nullptr)
{
}


CMouseImage::~CMouseImage()
{
	Release();
}

HRESULT CMouseImage::Initialize(CMouseImageImp * _pImageImp)
{
	NULL_CHECK_MSG_RETURN(_pImageImp, L"MouseImage Initialize::Not Exists CMouseImageImp", S_FALSE);
	m_pImageImp = _pImageImp;
	return S_OK;
}

void CMouseImage::Release()
{
	SafeDelete(m_pImageImp);
}

CMouseImage * CMouseImage::Create(CMouseImageImp * _pImageImp)
{
	CMouseImage* pInstance = new CMouseImage();
	if (FAILED(pInstance->Initialize(_pImageImp)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CMouseImage::ChangeState(ENUM::MouseState & _eState, FRAME & _tFrame)
{
	m_pImageImp->ChangeState(_eState, _tFrame);
}

void CMouseImage::Render(DRAW_INFO & _tDraw, FRAME & _tFrame, D3DXMATRIX * _pMatrix)
{
	m_pImageImp->Render(_tDraw, _tFrame, _pMatrix);
}
