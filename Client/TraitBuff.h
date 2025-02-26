#pragma once
#include "GameImage.h"
class CTraitBuff :
	public CGameImage
{
	DECLARE_CREATE(CTraitBuff)
protected:
	virtual HRESULT	Initialize();
	virtual HRESULT	LateInit();
	virtual void	Release();

public:
	virtual int		Update();
	virtual void	LateUpdate();
	virtual void	Render();

public:
	void			SetTarget(CObserver* _pTarget);

	static void LoadGameImage();

public:
	CObserver*		m_pTarget;
};

