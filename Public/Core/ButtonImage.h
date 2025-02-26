#pragma once

class CButtonImageImp;
class CButtonImage
{
protected:
	explicit	CButtonImage();

public:
	virtual		~CButtonImage();

private:
	HRESULT		Initialize(CButtonImageImp* _pImageImp);
	void		Release();

public:
	static CButtonImage* Create(CButtonImageImp* _pImageImp);

public:
	void		ChangeState(ENUM::ButtonState& _eState, FRAME& _tFrame);
	void		Render(TCHAR _szButtonName[], DRAW_INFO& _tDraw, FRAME& _tFrame, D3DXMATRIX* _pMatrix = nullptr);

private:
	CButtonImageImp* m_pImageImp;
};

