#pragma once
#include "GameObject.h"
class CWhirlwind :
	public CGameObject
{
	DECLARE_CREATE(CWhirlwind);

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

