#pragma once
#include "MouseImageImp.h"
class CBaseMouseImageImp :
	public CMouseImageImp
{
	DECLARE_CREATE_BASE(CBaseMouseImageImp)

public:
	HRESULT			Initialize();
public:
	virtual void	ChangeState(ENUM::MouseState& _eState, FRAME& _tFrame);
	virtual void	Render(DRAW_INFO& _tDraw, FRAME& _tFrame, D3DXMATRIX* _pMatrix = nullptr);

private:
	D3DXVECTOR3		m_vPosFit;
	D3DXVECTOR3		m_vScale;
};

