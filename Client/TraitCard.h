#pragma once
#include "GameImage.h"
class CTraitCard :
	public CGameImage
{
	DECLARE_CREATE(CTraitCard)

public:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	bool				IsBuff() { return m_iTraitCount >= m_iTraitCountMax; }

public:
	void				SetTrait(ENUM::Job _eTrait);
	void				SetTraitCount(int _iTraitCount) { m_iTraitCount = _iTraitCount; }
public:
	ENUM::Job			GetTrait() { return m_eTrait; }
	int					GetTraitCount() { return m_iTraitCount; }

protected:
	ENUM::Job			m_eTrait;
	DRAW_INFO			m_tDrawTrait;		//���� ���� ������
	DRAW_INFO			m_tDrawForm;		//���� ��
	DRAW_INFO			m_tDrawString;		//�۾�

	int					m_iTraitCount;		//������ ����
	int					m_iTraitCountMax;	//������ ���� �ִ�

	const TEXTURE_INFO* m_pCardTexture = nullptr;
	const TEXTURE_INFO* m_pFormTexture = nullptr;
	const TEXTURE_INFO* m_pTraitTexture = nullptr;
};

