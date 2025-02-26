#include "stdafx.h"
//#include "../../Client/stdafx.h"
#include "DeviceMgr.h"

D3DCOLOR CDeviceMgr::m_dwFontColor = INIT_COLOR;
D3DCOLOR CDeviceMgr::m_dwLineColor = INIT_COLOR_BLACK;
D3DCOLOR CDeviceMgr::m_dwRectColor = INIT_COLOR;
IMPLEMENT_SINGLETON(CDeviceMgr)
CDeviceMgr::CDeviceMgr()
{
}

CDeviceMgr::~CDeviceMgr()
{
	Release();
}

HRESULT CDeviceMgr::DrawImage(DRAW_INFO & _tDraw, LPRECT _prtArea, DRAWTYPE _eDrawType)
{
	if (!_tDraw.GetTextureInfo()) return E_FAIL;
	if (!_prtArea)
		_prtArea = &(RECT() = { 0, 0, (LONG)_tDraw.GetTextureInfo()->tImgInfo.Width, (LONG)_tDraw.GetTextureInfo()->tImgInfo.Height });

	/*POINTFLOAT ptScale = { (_prtArea->right / _tDraw.vSize.x), (_prtArea->bottom / _tDraw.vSize.y) };
	//��ũ�� ���� Ŭ��� �ٱ� �κ��� ��ο� ���ϱ� ���� �ڵ�
	RECT rt = _tDraw.GetRect();
	if (rt.left < 100)
		_prtArea->left += (100 - rt.left) *ptScale.x;
	if (rt.top < 100)
		_prtArea->top += (100 - rt.top) *ptScale.y;
	if (rt.right > WINCX - 100)
		_prtArea->right -= (rt.right - (WINCX - 100)) *ptScale.x;
	if (rt.bottom > WINCY - 100)
		_prtArea->bottom -= (rt.bottom - (WINCY - 100)) *ptScale.y;

	if (_prtArea->left > _prtArea->right)
		_prtArea->left = _prtArea->right;
	if (_prtArea->top > _prtArea->bottom)
		_prtArea->top = _prtArea->bottom;
	//��ũ�� ���� Ŭ��� �ٱ� �κ��� ��ο� ���ϱ� ���� �ڵ�//*/

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);// | D3DXSPRITE_SORT_TEXTURE);

	switch (_eDrawType)
	{
	case CDeviceMgr::NORMAL:
		break;
	case CDeviceMgr::ALPHA:
		m_pGraphicDev->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
		m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
		m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		break;
	default:
		break;
	}

	m_pSprite->SetTransform(&_tDraw.matCurrent);
	HRESULT hr =  m_pSprite->Draw(
		_tDraw.GetTexture(),					
		// LPDIRECT3DTEXTURE9 
		_prtArea,								// Rect�� ������, �׸� ����
		&_tDraw.GetCenter(),					// ��� �߽��� 
		nullptr,								// ��� ��ġ
		_tDraw.color);
	m_pSprite->End();
	return hr;
}

INT CDeviceMgr::DrawString(LPCWSTR _pString, INT _iCount, D3DXVECTOR3 _vPos, DWORD _dwFormat, D3DCOLOR _dwColor, ENUM::FONT _eID)
{
	float fSize = 0.f;
	switch (_eID)
	{
	case ENUM::FONT::NORMAL:
		fSize = 32.f;
		break;
	case ENUM::FONT::FONT16:
		fSize = 16.f;
		break;
	case ENUM::FONT::FONT24:
		fSize = 24.f;
		break;
	case ENUM::FONT::FONT32:
		fSize = 32.f;
		break;
	case ENUM::FONT::FONT40:
		fSize = 40.f;
		break;
	case ENUM::FONT::FONT48:
		fSize = 48.f;
		break;
	case ENUM::FONT::FONT56:
		fSize = 56.f;
		break;
	case ENUM::FONT::END:
		break;
	default:
		break;
	}
	return m_pFont[(int)_eID]->DrawTextW(nullptr, _pString, _iCount, &FUNC::GET::Rect(_vPos, D3DXVECTOR3(_iCount*fSize, fSize, 0.f)), _dwFormat, _dwColor);
}

INT CDeviceMgr::DrawString(LPCWSTR _pString, INT _iCount, D3DXMATRIX * _Matrix, DWORD _dwFormat, D3DCOLOR _dwColor, ENUM::FONT _eID)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);// | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(_Matrix);
	int iReturn = m_pFont[(int)_eID]->DrawTextW(m_pSprite, _pString, _iCount, nullptr, _dwFormat, _dwColor);
	m_pSprite->End();
	return iReturn;
}

INT CDeviceMgr::DrawString(LPCWSTR _pString, INT _iCount, RECT * _rtSize, DWORD _dwFormat, D3DCOLOR _dwColor, ENUM::FONT _eID)
{
	return m_pFont[(int)_eID]->DrawTextW(nullptr, _pString, _iCount, _rtSize, _dwFormat, _dwColor);
}

BOOL CDeviceMgr::DrawLine(float _fX1, float _fY1, float _fX2, float _fY2, float _fWidth, D3DCOLOR _dwColor)
{
	m_vPointArr[0] = D3DXVECTOR2(_fX1, _fY1);
	m_vPointArr[1] = D3DXVECTOR2(_fX2, _fY2);

	m_pLine->SetWidth(_fWidth);
	m_pLine->Begin();
	m_pLine->Draw(m_vPointArr, 2, _dwColor);
	m_pLine->End();
	return 0;
}

BOOL CDeviceMgr::DrawLine(D3DXVECTOR2 _vpt1, D3DXVECTOR2 _vpt2, float _fWidth, D3DCOLOR _dwColor)
{
	return DrawLine(_vpt1.x, _vpt1.y, _vpt2.x, _vpt2.y, _fWidth, _dwColor);
}

BOOL CDeviceMgr::DrawRectangle(float _fLeft, float _fTop, float _fRight, float _fBottom, float _fWidth, D3DCOLOR _dwColor)
{
	m_vPointArr[0] = { _fLeft, _fTop };
	m_vPointArr[1] = { _fRight, _fTop };
	m_vPointArr[2] = { _fRight, _fBottom };
	m_vPointArr[3] = { _fLeft, _fBottom };
	m_vPointArr[4] = { _fLeft, _fTop };

	m_pLine->SetWidth(_fWidth);
	m_pLine->Begin();
	m_pLine->Draw(m_vPointArr, 5, _dwColor);
	m_pLine->End();
	return 0;
}

BOOL CDeviceMgr::DrawRectangle(RECT & _rt, float _fWidth, D3DCOLOR _dwColor)
{
	return DrawRectangle((float)_rt.left, (float)_rt.top, (float)_rt.right, (float)_rt.bottom, _fWidth, _dwColor);
}

BOOL CDeviceMgr::DrawRhombus(D3DXVECTOR3* _pRhombus, float _fWidth, D3DCOLOR _dwColor)
{
	m_vPointArr[0] = D3DXVECTOR2(_pRhombus[0]);
	m_vPointArr[1] = D3DXVECTOR2(_pRhombus[1]);
	m_vPointArr[2] = D3DXVECTOR2(_pRhombus[2]);
	m_vPointArr[3] = D3DXVECTOR2(_pRhombus[3]);
	m_vPointArr[4] = D3DXVECTOR2(_pRhombus[0]);

	m_pLine->SetWidth(_fWidth);
	m_pLine->Begin();
	m_pLine->Draw(m_vPointArr, 5, _dwColor);
	m_pLine->End();
	return 0;
}
BOOL CDeviceMgr::DrawHexagon(D3DXVECTOR3* _pHexagon, float _fWidth, D3DCOLOR _dwColor)
{
	m_vPointArr[0] = D3DXVECTOR2(_pHexagon[0]);
	m_vPointArr[1] = D3DXVECTOR2(_pHexagon[1]);
	m_vPointArr[2] = D3DXVECTOR2(_pHexagon[2]);
	m_vPointArr[3] = D3DXVECTOR2(_pHexagon[3]);
	m_vPointArr[4] = D3DXVECTOR2(_pHexagon[4]);
	m_vPointArr[5] = D3DXVECTOR2(_pHexagon[5]);
	m_vPointArr[6] = D3DXVECTOR2(_pHexagon[0]);

	m_pLine->SetWidth(_fWidth);
	m_pLine->Begin();
	m_pLine->Draw(m_vPointArr, 7, _dwColor);
	m_pLine->End();
	return 0;
}

HRESULT CDeviceMgr::InitDevice(const DWORD& _dwWinCX, const DWORD& _dwWinCY, MODE _eMode)
{
	HRESULT hr = 0;
	// ��ġ �ʱ�ȭ
	// 1. IDirect3D9 ����
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	// 2. ��ġ ���� (���� �׷��� ī���� ��� ����)
	// HAL (Hardward Abstraction Layer)
	// �ϵ���� �߻�(����� ���� ������� ��) ����
	D3DCAPS9 Caps;
	ZeroMemory(&Caps, sizeof(D3DCAPS9));
	hr = m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps);

	if(FAILED(hr))
	{
		MessageBox(g_hWnd, L"GetDeviceCaps Failed", L"Failed", 0);
		return E_FAIL;
	}

	// ���ؽ� ���μ��� ���� ����.
	// - ���� �׷��� ī�忡�� ���ؽ� ���μ����� �����ϴ°�
	// ���ؽ� ���μ���(������ȯ + ������)�� �������ִ°� ����
	DWORD vp = 0;
	if (Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// 3. IDirect3DDevice9 ����
	D3DPRESENT_PARAMETERS tDevice;
	tDevice.BackBufferWidth = _dwWinCX;
	tDevice.BackBufferHeight = _dwWinCY;
	tDevice.BackBufferFormat = D3DFMT_A8R8G8B8;
	tDevice.BackBufferCount = 1;
	tDevice.MultiSampleType = D3DMULTISAMPLE_NONE;	// ��Ƽ ���ø� �Ⱦ�
	tDevice.MultiSampleQuality = 0;
	tDevice.SwapEffect = D3DSWAPEFFECT_DISCARD;		// ���� ü�� ���
	tDevice.hDeviceWindow = g_hWnd;
	tDevice.Windowed = _eMode;						//TRUE â ���, FALSE ��üȭ�� ���
	tDevice.EnableAutoDepthStencil = true;			//(Depth)���̸� ��� ����, (Stencil)������ �Ͱ� ������ ���ƾ� �Ұ��� �����ϴ� ����, �̰͵��� ����� ���ΰ�?
	tDevice.AutoDepthStencilFormat = D3DFMT_D24S8;	//FMT ������ ����, D24: Depth�� 24��Ʈ, S8: Stencil�� 8��Ʈ ���ڴ�!
	tDevice.Flags = 0;
	// ��üȭ�� ����� �� �ߴ� ������
	tDevice.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ��üȭ�� �϶����� ��ġ���� �ñ�ڴ�!
	tDevice.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// D3DPRESENT_INTERVAL_IMMEDIATE ���͹� ���� ������ �ض�
	//tDevice.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// D3DPRESENT_INTERVAL_IMMEDIATE ���͹� ���� ������ �ض�
	//tDevice.PresentationInterval = D3DPRESENT_INTERVAL_ONE;	// D3DPRESENT_INTERVAL_IMMEDIATE ���͹� ���� ������ �ض�

	hr = m_pSDK->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		g_hWnd, vp, &tDevice, &m_pGraphicDev);
	FAILED_CHECK_MSG_RETURN(hr, L"CreateDevice Failed", E_FAIL);

	// ID3DXSprite ����
	hr = D3DXCreateSprite(m_pGraphicDev, &m_pSprite);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateSprite Failed", E_FAIL);

	// ID3DXLine ����
	hr = D3DXCreateLine(m_pGraphicDev, &m_pLine);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateLine Failed", E_FAIL);

	// ID3DXFont ����
	hr = D3DXCreateFont(m_pGraphicDev, 
		32, 0, FW_NORMAL, 1, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH||FF_DONTCARE,
		L"Arial", &m_pFont[(int)ENUM::FONT::NORMAL]);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFont Failed - NORMAL", E_FAIL);

	hr = D3DXCreateFont(m_pGraphicDev,
		16, 0, FW_NORMAL, 1, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		L"Arial", &m_pFont[(int)ENUM::FONT::FONT16]);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFont Failed - NORMAL", E_FAIL);

	hr = D3DXCreateFont(m_pGraphicDev,
		24, 0, FW_NORMAL, 1, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		L"Arial", &m_pFont[(int)ENUM::FONT::FONT24]);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFont Failed - NORMAL", E_FAIL);

	hr = D3DXCreateFont(m_pGraphicDev,
		32, 0, FW_NORMAL, 1, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		L"Arial", &m_pFont[(int)ENUM::FONT::FONT32]);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFont Failed - NORMAL", E_FAIL);

	hr = D3DXCreateFont(m_pGraphicDev,
		40, 0, FW_NORMAL, 1, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		L"Arial", &m_pFont[(int)ENUM::FONT::FONT40]);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFont Failed - NORMAL", E_FAIL);

	hr = D3DXCreateFont(m_pGraphicDev,
		48, 0, FW_NORMAL, 1, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		L"Arial", &m_pFont[(int)ENUM::FONT::FONT48]);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFont Failed - NORMAL", E_FAIL);

	hr = D3DXCreateFont(m_pGraphicDev,
		56, 0, FW_NORMAL, 1, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		L"Arial", &m_pFont[(int)ENUM::FONT::FONT56]);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFont Failed - NORMAL", E_FAIL);
	
	return S_OK;
}

void CDeviceMgr::Render_Begin()
{
	//������ ����
	// 1. �ĸ���۸� ����
	m_pGraphicDev->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		INIT_COLOR_SCREEN, 1.0f, 0); // ������ ������ 1.0f ���� ���� �ʱ�ȭ, 0 STENCIL ���� �ʱ�ȭ

	// 2. �ĸ���ۿ� �׸��� �����Ѵ�.
	m_pGraphicDev->BeginScene();
	//m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDeviceMgr::Render_End(HWND _hWnd)
{
	// 3. �ĸ���ۿ� �׸��⸦ ����ģ��.
	//m_pSprite->End();
	m_pGraphicDev->EndScene();
	// 4. �ĸ���۸� ������۷� ��ü�Ͽ� ������ �Ѵ�.
	m_pGraphicDev->Present(nullptr, nullptr, _hWnd, nullptr);
	//����ü���� ���ٸ� 1~3��° ���ڴ� ������ nullptr�̴�.
	//3���� ���� ������ �ڵ�, ��� �����쿡 �׸����ΰ�?
	//nullptr�� ��� tDevice.hDeviceWindow = g_hWnd; �� �κп��� �������� �����츦 �ڵ��� ����
}

void CDeviceMgr::Release()
{
	// ���� ����
	for (auto& pFont : m_pFont)
	{
		if (SafeRelease(pFont))
			ERR_MSG(L"m_pSprite Release Failed");
	}
	if (SafeRelease(m_pLine))
		ERR_MSG(L"m_pSprite Release Failed");
	if (SafeRelease(m_pSprite))
		ERR_MSG(L"m_pSprite Release Failed");
	if (SafeRelease(m_pGraphicDev))
		ERR_MSG(L"m_pGraphicDev Release Failed");
	if (SafeRelease(m_pSDK))
		ERR_MSG(L"m_pSDK Release Failed");
}