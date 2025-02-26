#pragma once
#include "GameImage.h"

class CPanel;
class CUnitCard;
class CInven :
	public CGameImage
{
	DECLARE_CREATE(CInven)
public:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	void				ReleaseList();
private:
	void				UpdateList();


private:
	CPanel*				 m_pPanel;
	std::list<CUnitCard*> m_lstUnitCard;
};

