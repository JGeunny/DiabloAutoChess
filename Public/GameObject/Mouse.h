#pragma once

#include "GameImage.h"
class CMouseImage;
class CMouse :
	public CGameImage
{
	DECLARE_CREATE(CMouse)
private:
	enum class CURSOR_TYPE {POINT, END};

protected:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	D3DXVECTOR3 		GetPosScroll();
	POINT				GetPoint();
	POINT				GetPointScroll();

	void				ChangeState();

public:
	void				SetMouseState(ENUM::MouseState _eState) { m_eNextMouseState = _eState;}

private:
	CMouseImage*		m_pMouseImage;

	ENUM::MouseState	m_eCurMouseState;
	ENUM::MouseState	m_eNextMouseState;
};

