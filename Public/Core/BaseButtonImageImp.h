#pragma once
#include "ButtonImageImp.h"
class CBaseButtonImageImp :
	public CButtonImageImp
{
	DECLARE_CREATE_BASE(CBaseButtonImageImp)

public:
	HRESULT			Initialize();
public:
	virtual void	ChangeState(ENUM::ButtonState& _eState, FRAME& _tFrame);
	virtual void	Render(TCHAR _szButtonName[], DRAW_INFO& _tDraw, FRAME& _tFrame, D3DXMATRIX* _pMatrix = nullptr);

private:
	std::vector<int> m_vecOrderType;
};

