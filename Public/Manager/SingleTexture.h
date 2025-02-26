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
		const std::wstring&	_wstrFilePath,						//�ؽ�ó ���
		const int&		_iCount = 1,						//��Ƽ �ؽ�ó�϶��� ��� �׸��� Tile0~ ������ �׸��� �ҷ��´�.	0�̸� 1����
		const int &		_iCountX = 1,
		const int &		_iCountY = 1,
		const D3DCOLOR&	_color = INIT_COLOR_DEL) override;	//�ҷ��� �̹��� ����, ��Ƽ �ؽ�ó�� ���� ���

	virtual void Release() override;

public:
	virtual const int GetSize() override;
//private:
//	TEXTURE_INFO* m_pTexInfo;
private:
	TEXTURE_INFO* m_pImage;
};

