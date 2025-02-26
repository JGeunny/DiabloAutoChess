#include "stdafx.h"
#include "BaseButtonImageImp.h"

IMPLEMENT_CREATE_BASE(CBaseButtonImageImp)
CBaseButtonImageImp::CBaseButtonImageImp()
{
}


CBaseButtonImageImp::~CBaseButtonImageImp()
{
}

HRESULT CBaseButtonImageImp::Initialize()
{
	m_pTextureMgr->LoadTexture(L"BaseButton|Normal", L"../Image/UI/Button/Button_Normal.png");
	m_pTextureMgr->LoadTexture(L"BaseButton|Down", L"../Image/UI/Button/Button_Down.png");
	m_pTextureMgr->LoadTexture(L"BaseButton|Selected", L"../Image/UI/Button/Button_Selected.png");

	return S_OK;
}

void CBaseButtonImageImp::ChangeState(ENUM::ButtonState & _eState, FRAME & _tFrame)
{
	switch (_eState)
	{
	case ENUM::ButtonState::NONE:
		_tFrame.iFrameKey = -1;
		break;
	case ENUM::ButtonState::NORMAL:
		_tFrame.iFrameKey = 0;
		break;
	case ENUM::ButtonState::DOWN:
		_tFrame.iFrameKey = 1;
		break;
	case ENUM::ButtonState::SELECTED:
		_tFrame.iFrameKey = 2;
		break;
	default:
		break;
	}
}

void CBaseButtonImageImp::Render(TCHAR _szButtonName[], DRAW_INFO & _tDraw, FRAME & _tFrame, D3DXMATRIX * _pMatrix)
{
	_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::BASEBUTTON, _tFrame.iFrameKey, 0));

	if (_pMatrix)
		_tDraw.matCurrent = *_pMatrix;
	else
		_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

	_tFrame.SetScene(_tDraw.vAngle.z);

	m_pDeviceMgr->DrawImage(_tDraw);
	m_pDeviceMgr->DrawString(_szButtonName, lstrlen(_szButtonName)
		, &_tDraw.GetRect(0.f, true, ENUM::DrawRect::IMAGE)
		, DT_CENTER | DT_VCENTER, _tDraw.color);
}
