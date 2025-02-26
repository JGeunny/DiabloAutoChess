#pragma once
#include "GameImage.h"
class CGameString :
	public CGameImage
{
	DECLARE_CREATE_COMPONENT(CGameString)

private:
	HRESULT		Initialize();
	HRESULT		LateInit();
	void		Release();

public:
	int			Update();
	void		LateUpdate();
	void		Render();

public:
	void		SetName(LPCWSTR _pStringName) { lstrcpy(m_szStringName, _pStringName); }
	void		SetColor(D3DCOLOR	_dwColor) { m_tDraw.color = _dwColor; }

public:
	TCHAR*		GetName() { return m_szStringName; }
	D3DCOLOR	GetColor() { return m_tDraw.color; }

private:
	TCHAR		m_szStringName[MID_STR];
};

