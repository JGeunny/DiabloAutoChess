#pragma once
#include "GameObject.h"

class CUnitImage;
class CUnitControl;
class CBavarianImage;
class CBavarian :
	public CGameObject
{
	DECLARE_CREATE(CBavarian)

protected:
	virtual HRESULT	Initialize();
	virtual HRESULT	LateInit();
	virtual void	Release();

public:
	virtual int		Update();
	virtual void	LateUpdate();
	virtual void	Render();

public:
	void			Control();

public:
	virtual	void FSM() override;// ���� ���� ���(�⺻���� �ΰ�����)

public:
	static void		SetObjInfo(OBJ_INFO& _tObjInfo) { m_tObjInfo = _tObjInfo; }

public:
	void			SetWhirlwind();

private:
	static OBJ_INFO m_tObjInfo;

private:
	CUnitImage*		m_pUnitImage;
	CUnitControl*	m_pUnitControl;
	bool			m_bCanAttack;
	CBavarianImage* m_pBavarianImage;
};

