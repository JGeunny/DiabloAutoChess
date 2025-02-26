#include "stdafx.h"
//#include "../../Tool/stdafx.h"
#include "MultiTexture.h"

CMultiTexture::CMultiTexture()
{
}

CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEXTURE_INFO* CMultiTexture::GetTexInfo(
	const int & _iIndex)
{
	return m_vecImage[_iIndex];
}

HRESULT CMultiTexture::LoadTexture(const std::wstring & _wstrFilePath, const int & _iCount, const int & _iCountX, const int & _iCountY, const D3DCOLOR& _color)
{
	if(!m_vecImage.empty()) return E_FAIL; //이미 있는 이미지
	TEXTURE_INFO* pTexInfo = nullptr;	
	TCHAR szPath[MAX_STR] = L"";
	HRESULT hr = 0;

	for (int i = 0; i < _iCount; ++i)
	{
		pTexInfo = new TEXTURE_INFO;
		ZeroMemory(pTexInfo, sizeof(TEXTURE_INFO));
		pTexInfo->iCountX = _iCountX;
		pTexInfo->iCountY = _iCountY;
		m_vecImage.emplace_back(pTexInfo);

		swprintf_s(szPath, _wstrFilePath.c_str(), i);

		hr = D3DXGetImageInfoFromFile(szPath, &pTexInfo->tImgInfo);
		FAILED_CHECK_MSG_RETURN(hr, szPath, E_FAIL);

		// IDIRECT3DTEXTURE9 생성
		hr = D3DXCreateTextureFromFileEx(
			CDeviceMgr::GetInstance()->GetDevice(), // 장치
			szPath,									// 이미지 경로
			pTexInfo->tImgInfo.Width,				// 이미지 가로크기
			pTexInfo->tImgInfo.Height,				// 이미지 세로크기
			pTexInfo->tImgInfo.MipLevels,			// mip level
			0,
			pTexInfo->tImgInfo.Format,				// 이미지 픽셀 포맷
			D3DPOOL_MANAGED,						// 메모리 사용방식
			D3DX_DEFAULT,							// 이미지 테두리 표현(필터)
			D3DX_DEFAULT,							// Mip Filter
			_color,									// Color key 제거할 색상
			nullptr,								// D3DXIMAGE_INFO의 포인터
			nullptr,								// 이미지 팔레트
			&pTexInfo->pTexture);
		FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateTextureFromFileEx Failed", E_FAIL);
	}
	//백터로 변환 후 맵에 저장 끝//=============================================

	return S_OK;
}

void CMultiTexture::Release()
{
	for (auto& pInfo : m_vecImage)
	{
		SafeRelease(pInfo->pTexture);
		SafeDelete(pInfo);
	}
	m_vecImage.clear();
	m_vecImage.shrink_to_fit();
}

const int CMultiTexture::GetSize()
{
	return m_vecImage.size();
}