#pragma once
#include "Scene.h"
class CEnding :
	public CScene
{
	DECLARE_CREATE_BASE(CEnding)

protected:
	virtual HRESULT		Initialize();
	//virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	std::list<std::wstring> m_lstText;
	D3DXVECTOR3				m_vPos;
};

