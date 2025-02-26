#pragma once

class CUnitImageImp;
class CUnitImage
{
protected:
	explicit	CUnitImage();

public:
	virtual		~CUnitImage();

private:
	HRESULT		Initialize(CUnitImageImp* _pImageImp);
	void		Release();

public:
	static CUnitImage* Create(CUnitImageImp* _pImageImp);

public:
	void		ChangeState(ENUM::State&, FRAME&);
	void		Render(DRAW_INFO&, FRAME&, D3DXMATRIX* _pMatrix = nullptr);

private:
	CUnitImageImp*	m_pImageImp;
};

