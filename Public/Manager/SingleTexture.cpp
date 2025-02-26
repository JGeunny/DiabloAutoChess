#include "stdafx.h"
//#include "../../Tool/stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
	:m_pImage(nullptr)
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

const TEXTURE_INFO* CSingleTexture::GetTexInfo(
	const int & _iIndex)
{
	return m_pImage;
}

HRESULT CSingleTexture::LoadTexture(const std::wstring & _wstrFilePath,
	const int&	_iCount, const int & _iCountX, const int & _iCountY,
	const D3DCOLOR&	_color){
	if (m_pImage) // �̹� �ִ� �̹���
	{
		return E_FAIL;
	}

	m_pImage = new TEXTURE_INFO;
	ZeroMemory(m_pImage, sizeof(TEXTURE_INFO));
	m_pImage->iCountX = _iCountX;
	m_pImage->iCountY = _iCountY;

	HRESULT hr = 0;
	hr = D3DXGetImageInfoFromFile(_wstrFilePath.c_str(), &m_pImage->tImgInfo);
	//FAILED_CHECK_MSG_RETURN(hr, L"D3DXGetImageInfoFromFile Failed", E_FAIL);
	FAILED_CHECK_MSG_RETURN(hr, _wstrFilePath.c_str(), E_FAIL);

	// IDIRECT3DTEXTURE9 ����
	hr = D3DXCreateTextureFromFileEx(
		CDeviceMgr::GetInstance()->GetDevice(), // ��ġ
		_wstrFilePath.c_str(),					// �̹��� ���
		m_pImage->tImgInfo.Width,				// �̹��� ����ũ��
		m_pImage->tImgInfo.Height,				// �̹��� ����ũ��
		m_pImage->tImgInfo.MipLevels,			// mip level
		0,
		m_pImage->tImgInfo.Format,				// �̹��� �ȼ� ����
		D3DPOOL_MANAGED,						// �޸� �����
		D3DX_DEFAULT,							// �̹��� �׵θ� ǥ��(����)
		D3DX_DEFAULT,							// Mip Filter
		_color,									// Color key ������ ����
		nullptr,								// D3DXIMAGE_INFO�� ������
		nullptr,								// �̹��� �ȷ�Ʈ
		&m_pImage->pTexture);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateTextureFromFileEx Failed", E_FAIL);
	return S_OK;
}

void CSingleTexture::Release()
{
	if(m_pImage->pTexture)
		SafeRelease(m_pImage->pTexture);
	SafeDelete(m_pImage);
}

const int CSingleTexture::GetSize()
{
	return 1;
}
