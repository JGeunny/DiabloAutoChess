#pragma once

#include "Scene.h"
class CWorldMap
	: public CScene
{
	DECLARE_CREATE_BASE(CWorldMap)

protected:
	virtual HRESULT		Initialize();
	//virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	static void			SetInit(bool _bInit) { m_bInit = _bInit; }

public:
	static bool			GetInit() { return m_bInit; }

public:
	static bool			m_bInit;
};

