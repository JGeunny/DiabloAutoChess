#pragma once
#include "GameObject.h"
class CPanel :
	public CGameObject
{
	DECLARE_CREATE_COMPONENT(CPanel)
public:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	void				SetName(LPCWSTR _pButtonName) { lstrcpy(m_szPanelName, _pButtonName); }
	void				SetColor(D3DCOLOR	_dwColor) { m_tDraw.color = _dwColor; }
private:
	DRAW_INFO			m_tDrawTitle;
	TCHAR				m_szPanelName[MID_STR];
	D3DXVECTOR3			m_vClickPos;
	D3DXVECTOR3			m_vDrawPos;
	bool				m_bMovePanel;
};

