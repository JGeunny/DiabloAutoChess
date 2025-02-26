#pragma once
class CTexture
{
public:
	explicit CTexture();
	virtual ~CTexture();
	
public:
	virtual const TEXTURE_INFO* GetTexInfo(
		const int&		_iIndex = 0) PURE;

public:
	virtual HRESULT LoadTexture(
		const std::wstring&	_wstrFilePath,						//텍스처 경로
		const int&		_iCount = 0,						//멀티 텍스처일때만 사용 그림의 Tile0~ 까지의 그림을 불러온다.	0이면 1개임
		const int&		_iCountX = 0,
		const int&		_iCountY = 0,
		const D3DCOLOR&	_color = INIT_COLOR_DEL) PURE;		//불러올 이미지 개수, 텍스처일 때만 사용

public:
	virtual const int GetSize() PURE;
	virtual void Release() PURE;
};

