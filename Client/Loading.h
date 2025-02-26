#pragma once
#include "Scene.h"
class CLoading :
	public CScene
{
	DECLARE_CREATE_BASE(CLoading)

protected:
	virtual HRESULT		Initialize();
	//virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();
};

