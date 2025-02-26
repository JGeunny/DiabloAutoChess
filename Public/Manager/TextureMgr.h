#pragma once

#include "Texture.h"
//class CTexture;
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	explicit CTextureMgr();
	virtual ~CTextureMgr();

public:
	const TEXTURE_INFO* GetTexInfo(
		const std::wstring&		_wstrImageKey,
		const int&				_iIndex = 0);
	HRESULT LoadTexture(
		const std::wstring&		_wstrImageKey,
		const std::wstring&		_wstrFilePath,		//텍스처 경로
		const int&			_iCount = -1,
		const int &			_iCountX = 1,
		const int &			_iCountY = 1,
		const D3DCOLOR&		_dwColor = INIT_COLOR_DEL);

public:
	const int GetSize(
		const std::wstring&		_wstrImageKey);
	
	CTexture* GetTexture(
		const std::wstring&		_wstrImageKey);

public:
	void Release();

public:
	const TEXTURE_INFO* GetTexInfo(
		RZIMAGE::ID _eID
		, int _iKey
		, int _iIndex);

private:
	void SetImageVec(std::wstring _strImageKey, CTexture* _pTexture);

private:
	std::unordered_map<std::wstring, CTexture*> m_mapImage;
	std::vector<CTexture*>		m_vecImage[RZIMAGE::END];
};

