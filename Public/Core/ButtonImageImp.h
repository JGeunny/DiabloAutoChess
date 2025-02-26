#pragma once
class CButtonImageImp
{
public:
	explicit		CButtonImageImp();
	virtual			~CButtonImageImp();

public:
	virtual void	ChangeState(ENUM::ButtonState& _eState, FRAME& _tFrame) PURE;
	virtual void	Render(TCHAR _szButtonName[], DRAW_INFO& _tDraw, FRAME& _tFrame, D3DXMATRIX* _pMatrix = nullptr) PURE;

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
};

