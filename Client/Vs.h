#pragma once
#include "GameImage.h"
class CVs :
	public CGameImage
{
	DECLARE_CREATE_BASE(CVs)
protected:
	virtual HRESULT		Initialize();
	//virtual HRESULT	LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	void InitTarget(CGameObject* _pBlueTeam, CGameObject* _pRedTeam);
	CObserver* m_pTarget;
	void		ClearTarget();

	static void LoadGameImage();

public:
	D3DXVECTOR3 m_vBluePos;
	D3DXVECTOR3 m_vRedPos;
	
};

