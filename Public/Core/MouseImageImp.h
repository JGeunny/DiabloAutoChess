#pragma once
class CMouseImageImp
{
public:
	explicit CMouseImageImp();
	virtual ~CMouseImageImp();

public:
	virtual void ChangeState(ENUM::MouseState& _eState, FRAME& _tFrame) PURE;
	virtual void Render(DRAW_INFO& _tDraw, FRAME& _tFrame, D3DXMATRIX* _pMatrix = nullptr) PURE;

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
};

