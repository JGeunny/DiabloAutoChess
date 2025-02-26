#pragma once
#include "GameImage.h"
class CVictory :
	public CGameImage
{
	DECLARE_CREATE_BASE(CVictory)
protected:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	void				SetVictory(bool _bVictory) { m_bVictory = _bVictory;}
public:
	bool				GetVictory() { return m_bVictory; }

public:
	bool				m_bVictory;
};

