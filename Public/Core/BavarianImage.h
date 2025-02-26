#pragma once
#include "UnitImageImp.h"
class CBavarianImage :
	public CUnitImageImp
{
	DECLARE_CREATE_BASE(CBavarianImage)
public:
	HRESULT	Initialize();

public:
	void	ChangeState(ENUM::State&, FRAME&);
	void	Render(DRAW_INFO&, FRAME&, D3DXMATRIX* _pMatrix = nullptr);

public:
	void	SetWhirlwind(FRAME& _tFrame);

	static void LoadGameImage();

private:
	std::vector<int> m_vecOrderType;
	std::vector<int> m_vecOrderType2;
	bool			m_bChangeScene;
};

