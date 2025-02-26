#pragma once
#include "Texture.h"
class CSingleTexture :
	public CTexture
{
public:
	explicit CSingleTexture();
	virtual ~CSingleTexture();

public:
	virtual const TEXTURE_INFO* GetTexInfo(
		const int& _iIndex = 0) override;

public:
	virtual HRESULT LoadTexture(
		const std::wstring&	_wstrFilePath,						//텍스처 경로
		const int&		_iCount = 1,						//멀티 텍스처일때만 사용 그림의 Tile0~ 까지의 그림을 불러온다.	0이면 1개임
		const int &		_iCountX = 1,
		const int &		_iCountY = 1,
		const D3DCOLOR&	_color = INIT_COLOR_DEL) override;	//불러올 이미지 개수, 멀티 텍스처일 때만 사용

	virtual void Release() override;

public:
	virtual const int GetSize() override;
//private:
//	TEXTURE_INFO* m_pTexInfo;
private:
	TEXTURE_INFO* m_pImage;
};

