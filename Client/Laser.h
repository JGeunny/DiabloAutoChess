#pragma once
#include "GameObject.h"
class CLaser :
	public CGameObject
{
	DECLARE_CREATE(CLaser);

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
	std::vector<int> m_vecOrderType;
};

