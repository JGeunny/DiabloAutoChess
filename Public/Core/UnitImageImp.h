#pragma once
class CUnitImageImp
{
public:
	explicit		CUnitImageImp();
	virtual			~CUnitImageImp();

public:
	virtual void	ChangeState(ENUM::State&, FRAME&) PURE;
	virtual void	Render(DRAW_INFO&, FRAME&, D3DXMATRIX* _pMatrix = nullptr) PURE;

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;

protected:
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vPosFit;
};

