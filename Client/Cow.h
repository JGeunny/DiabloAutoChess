#pragma once
#include "GameObject.h"
class CCow :
	public CGameObject
{
	DECLARE_CREATE(CCow)

protected:
	virtual HRESULT	Initialize();
	virtual HRESULT	LateInit();
	virtual void	Release();

public:
	virtual int		Update();
	virtual void	LateUpdate();
	virtual void	Render();
};

