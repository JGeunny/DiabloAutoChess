#pragma once
#include "GameObject.h"
class CBone :
	public CGameObject
{
	DECLARE_CREATE(CBone);

protected:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

	static void			LoadGameImage();

private:
	bool				m_bComeOut;
};

