#pragma once
#include "Scene.h"
class CTitle :
	public CScene
{
	DECLARE_CREATE_BASE(CTitle)

protected:
	virtual HRESULT		Initialize();
	//virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();
};

