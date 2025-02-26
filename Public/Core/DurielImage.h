#pragma once
#include "UnitImageImp.h"
class CDurielImage :
	public CUnitImageImp
{
	DECLARE_CREATE_BASE(CDurielImage)

public:
	HRESULT	Initialize();

public:
	void	ChangeState(ENUM::State&, FRAME&);
	void	Render(DRAW_INFO&, FRAME&, D3DXMATRIX* _pMatrix = nullptr);

	static void LoadGameImage();

private:
	std::vector<int> m_vecOrderType;
};

