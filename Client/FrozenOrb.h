#pragma once
#include "GameObject.h"
class CFrozenOrb :
	public CGameObject
{
	DECLARE_CREATE(CFrozenOrb);

protected:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();
	static void LoadGameImage();
};

