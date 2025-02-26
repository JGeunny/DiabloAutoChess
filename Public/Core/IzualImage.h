#pragma once
#include "UnitImageImp.h"
class CIzualImage :
	public CUnitImageImp
{
	DECLARE_CREATE_BASE(CIzualImage);

public:
	HRESULT			Initialize();
public:
	virtual void	ChangeState(ENUM::State&, FRAME&);
	virtual void	Render(DRAW_INFO&, FRAME&, D3DXMATRIX* _pMatrix = nullptr);

	static void LoadGameImage();

private:
	std::vector<int> m_vecOrderType;
	std::vector<int> m_vecOrderType2;
};

