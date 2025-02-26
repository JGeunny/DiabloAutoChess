#include "stdafx.h"
#include "ButtonImage.h"
#include "ButtonImageImp.h"

CButtonImage::CButtonImage()
	:m_pImageImp(nullptr)
{
}


CButtonImage::~CButtonImage()
{
	Release();
}

HRESULT CButtonImage::Initialize(CButtonImageImp * _pImageImp)
{
	NULL_CHECK_MSG_RETURN(_pImageImp, L"CButtonImage Initialize::Not Exists CButtonImageImp", S_FALSE);
	m_pImageImp = _pImageImp;
	return S_OK;
}

void CButtonImage::Release()
{
	SafeDelete(m_pImageImp);
}

CButtonImage * CButtonImage::Create(CButtonImageImp * _pImageImp)
{
	CButtonImage* pInstance = new CButtonImage();
	if (FAILED(pInstance->Initialize(_pImageImp)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CButtonImage::ChangeState(ENUM::ButtonState & _eState, FRAME & _tFrame)
{
	m_pImageImp->ChangeState(_eState, _tFrame);
}

void CButtonImage::Render(TCHAR _szButtonName[], DRAW_INFO & _tDraw, FRAME & _tFrame, D3DXMATRIX * _pMatrix)
{
	m_pImageImp->Render(_szButtonName, _tDraw, _tFrame, _pMatrix);
}
