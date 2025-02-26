#pragma once
#include "GameImage.h"
class CScene :
	public CGameImage
{
public:
	explicit CScene();
	virtual ~CScene();

protected:
	virtual HRESULT		Initialize() PURE;
	virtual void		Release() PURE;

public:
	virtual int			Update() PURE;
	virtual void		LateUpdate() PURE;
	virtual void		Render() PURE;

protected:
	CSceneMgr*	m_pSceneMgr;
};

