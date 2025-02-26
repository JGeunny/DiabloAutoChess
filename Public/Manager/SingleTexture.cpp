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
	if (m_pImage) // 이미 있는 이미지
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

	// IDIRECT3DTEXTURE9 생성
	hr = D3DXCreateTextureFromFileEx(
		CDeviceMgr::GetInstance()->GetDevice(), // 장치
		_wstrFilePath.c_str(),					// 이미지 경로
		m_pImage->tImgInfo.Width,				// 이미지 가로크기
		m_pImage->tImgInfo.Height,				// 이미지 세로크기
		m_pImage->tImgInfo.MipLevels,			// mip level
		0,
		m_pImage->tImgInfo.Format,				// 이미지 픽셀 포맷
		D3DPOOL_MANAGED,						// 메모리 사용방식
		D3DX_DEFAULT,							// 이미지 테두리 표현(필터)
		D3DX_DEFAULT,							// Mip Filter
		_color,									// Color key 제거할 색상
		nullptr,								// D3DXIMAGE_INFO의 포인터
		nullptr,								// 이미지 팔레트
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
