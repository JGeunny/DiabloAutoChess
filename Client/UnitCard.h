#pragma once
#include "GameImage.h"
class CUnitCard :
	public CGameImage
{
public:
	DECLARE_CREATE(CUnitCard)

public:
	virtual HRESULT		Initialize();
	virtual HRESULT		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	//void SetClassTypeData(int _iClassTypeData);
	void SetUnitData(CGameObject* _pUnit = nullptr);

public:
	int GetClassTypeData() { return m_iClassTypeData; }
	void AddCount() { ++m_iCount; }
	bool SubCount() { 
		--m_iCount; 
		if (0 >= m_iCount)
			return false;
		return true;
	}

private:
	int		m_iClassTypeData;
	WCHAR	m_szUnitName[MIN_STR];
	int		m_iGold;
	int		m_iCount;
	ENUM::Job m_eJob;
	DRAW_INFO m_tDrawTrait;		//Á÷¾÷ Á¾·ù ¾ÆÀÌÄÜ
	DRAW_INFO m_tDrawForm;		//À°°¢ Æû
	DRAW_INFO m_tDrawString;	//À¯´Ö ÀÌ¸§
	DRAW_INFO m_tDrawString_Gold;	//°ñµå

	//const TEXTURE_INFO* m_pCardTexture = nullptr;
	const TEXTURE_INFO* m_pFormTexture = nullptr;
	const TEXTURE_INFO* m_pTraitTexture = nullptr;
};

