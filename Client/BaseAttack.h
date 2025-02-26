#pragma once
#include "GameObject.h"
class CBaseAttack :
	public CGameObject
{
	DECLARE_CREATE(CBaseAttack);

protected:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();
};

