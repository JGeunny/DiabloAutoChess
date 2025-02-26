#pragma once
#include "GameObject.h"
class CUnitImage;
class CVirtualObject :
	public CGameObject
{
	DECLARE_CREATE(CVirtualObject)

protected:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	virtual	void		FSM() override;// 유한 상태 기계(기본적인 인공지능)

public:
	void				SetImage(RZIMAGE::ID _eImageId);
	void				SetImage(LPWSTR _pImageName);
	void				ChangeState(ENUM::State _eState);

	RZIMAGE::ID&		GetImageId() { return m_eCurImageId; };

public:
	void				Control();

private:
	CUnitImage*			m_pUnitImage;
	RZIMAGE::ID			m_eCurImageId;
};

