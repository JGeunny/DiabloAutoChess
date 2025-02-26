#pragma once
#include "GameObject.h"
class CBoneSprite :
	public CGameObject
{
	DECLARE_CREATE(CBoneSprite);

protected:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();
};

