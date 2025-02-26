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
	if(!m_vecImage.empty()) return E_FAIL; //�̹� �ִ� �̹���
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

		// IDIRECT3DTEXTURE9 ����
		hr = D3DXCreateTextureFromFileEx(
			CDeviceMgr::GetInstance()->GetDevice(), // ��ġ
			szPath,									// �̹��� ���
			pTexInfo->tImgInfo.Width,				// �̹��� ����ũ��
			pTexInfo->tImgInfo.Height,				// �̹��� ����ũ��
			pTexInfo->tImgInfo.MipLevels,			// mip level
			0,
			pTexInfo->tImgInfo.Format,				// �̹��� �ȼ� ����
			D3DPOOL_MANAGED,						// �޸� �����
			D3DX_DEFAULT,							// �̹��� �׵θ� ǥ��(����)
			D3DX_DEFAULT,							// Mip Filter
			_color,									// Color key ������ ����
			nullptr,								// D3DXIMAGE_INFO�� ������
			nullptr,								// �̹��� �ȷ�Ʈ
			&pTexInfo->pTexture);
		FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateTextureFromFileEx Failed", E_FAIL);
	}
	//���ͷ� ��ȯ �� �ʿ� ���� ��//=============================================

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