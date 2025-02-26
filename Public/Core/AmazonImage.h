#pragma once
#include "UnitImageImp.h"
class CAmazonImage :
	public CUnitImageImp
{
	DECLARE_CREATE_BASE(CAmazonImage);

public:
	HRESULT			Initialize();
public:
	virtual void	ChangeState(ENUM::State&, FRAME&);
	virtual void	Render(DRAW_INFO&, FRAME&, D3DXMATRIX* _pMatrix = nullptr);

	static void LoadGameImage();

private:
	std::vector<int> m_vecOrderType;
	bool			m_bChangeScene;
};

