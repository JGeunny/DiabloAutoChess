#pragma once
#include "GameObject.h"
class CDiaSkill :
	public CGameObject
{
	DECLARE_CREATE(CDiaSkill);

protected:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

private:
	float				m_fSkillRecogDist;
	bool				m_doSkill;
};

