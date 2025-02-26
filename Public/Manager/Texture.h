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
		const std::wstring&	_wstrFilePath,						//�ؽ�ó ���
		const int&		_iCount = 0,						//��Ƽ �ؽ�ó�϶��� ��� �׸��� Tile0~ ������ �׸��� �ҷ��´�.	0�̸� 1����
		const int&		_iCountX = 0,
		const int&		_iCountY = 0,
		const D3DCOLOR&	_color = INIT_COLOR_DEL) PURE;		//�ҷ��� �̹��� ����, �ؽ�ó�� ���� ���

public:
	virtual const int GetSize() PURE;
	virtual void Release() PURE;
};

