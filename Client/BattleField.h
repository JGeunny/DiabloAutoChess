#pragma once
#include "Scene.h"
class CBattleField :
	public CScene
{
	DECLARE_CREATE_BASE(CBattleField)

protected:
	virtual HRESULT		Initialize();
	//virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

private:
	void				CheckVictory();

private:
	int					m_iReadyCount;
	bool				m_iEffect;
};

