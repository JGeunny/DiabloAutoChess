#pragma once
#include "GameImage.h"

class CButtonImage;
class CGameButton :
	public CGameImage
{
	DECLARE_CREATE_COMPONENT(CGameButton)
public:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

private:
	void				ChangeState();

public:
	void				SetName(LPCWSTR _pButtonName) {lstrcpy(m_szButtonName, _pButtonName);}
	void				SetColor(D3DCOLOR	_dwColor) { m_tDraw.color = _dwColor;	}

public:
	TCHAR*				GetName() { return m_szButtonName;}
	D3DCOLOR			GetColor() { return m_tDraw.color; }

protected:
	CControlMgr*		m_pControlMgr;

private:
	ENUM::ButtonState	m_eCurState;
	ENUM::ButtonState	m_eNextState;

	CButtonImage*		m_pButtonImage;

private:
	TCHAR				m_szButtonName[MID_STR];
};

