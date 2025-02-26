#pragma once
#include "GameImage.h"
class CTraitCard;
class CTrait :
	public CGameImage
{
	DECLARE_CREATE(CTrait)

public:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	std::vector<CTraitCard*>& GetTraitCardVec() { return m_vecTraitCard; }

public:
	std::vector<CTraitCard*> m_vecTraitCard;
};

