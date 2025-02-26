#pragma once

class CMouseImageImp;
class CMouseImage
{
protected:
	explicit	CMouseImage();
public:
	virtual		~CMouseImage();

private:
	HRESULT		Initialize(CMouseImageImp* _pImageImp);
	void		Release();

public:
	static CMouseImage* Create(CMouseImageImp* _pImageImp);

public:
	void		ChangeState(ENUM::MouseState& _eState, FRAME& _tFrame);
	void		Render(DRAW_INFO& _tDraw, FRAME& _tFrame, D3DXMATRIX* _pMatrix = nullptr);

private:
	CMouseImageImp* m_pImageImp;
};

