#pragma once
#include "GameObject.h"
class CArrow :
	public CGameObject
{
	DECLARE_CREATE(CArrow);

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

