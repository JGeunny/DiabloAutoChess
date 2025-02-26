#pragma once

class CDeviceMgr
{
	DECLARE_SINGLETON(CDeviceMgr)

public:
	enum MODE { MODE_FULL, MODE_WIN };

	enum DRAWTYPE { NORMAL, ALPHA };

private:
	explicit CDeviceMgr();
	virtual ~CDeviceMgr();

public:
	LPDIRECT3DDEVICE9 GetDevice() const { return m_pGraphicDev; }
	LPD3DXSPRITE	  GetSprite() const { return m_pSprite; }

	HRESULT			  DrawImage(DRAW_INFO& _tDraw, LPRECT _prtArea = nullptr, DRAWTYPE _eDrawType = DRAWTYPE::NORMAL);

	INT				  DrawString(LPCWSTR _pString
								, INT _iCount, D3DXVECTOR3 _vPos
								, DWORD _dwFormat = DT_CENTER | DT_VCENTER
								, D3DCOLOR _dwColor = m_dwFontColor
								, ENUM::FONT _eID = ENUM::FONT::NORMAL);
	INT				  DrawString(LPCWSTR _pString
								, INT _iCount, D3DXMATRIX* _Matrix
								, DWORD _dwFormat = DT_CENTER | DT_VCENTER
								, D3DCOLOR _dwColor = m_dwFontColor
								, ENUM::FONT _eID = ENUM::FONT::NORMAL);
	INT				  DrawString(LPCWSTR _pString
								, INT _iCount, RECT* _rtSize
								, DWORD _dwFormat = DT_CENTER | DT_VCENTER
								, D3DCOLOR _dwColor = m_dwFontColor
								, ENUM::FONT _eID = ENUM::FONT::NORMAL);

	BOOL			  DrawLine(float _fX1, float _fY1, float _fX2, float _fY2, float _fWidth = 1.f, D3DCOLOR _dwColor = m_dwLineColor);
	BOOL			  DrawLine(D3DXVECTOR2 _vpt1, D3DXVECTOR2 _vpt2, float _fWidth = 1.f, D3DCOLOR _dwColor = m_dwLineColor);

	BOOL			  DrawRectangle(float _fLeft, float _fTop, float _fRight, float _fBottom, float _fWidth = 1.f, D3DCOLOR _dwColor = m_dwRectColor);
	BOOL			  DrawRectangle(RECT& _rt, float _fWidth = 1.f, D3DCOLOR _dwColor = m_dwRectColor);
	BOOL			  DrawRhombus(D3DXVECTOR3 * _pRhombus, float _fWidth = 1.f, D3DCOLOR _dwColor = m_dwRectColor);
	BOOL			  DrawHexagon(D3DXVECTOR3 * _pHexagon, float _fWidth = 1.f, D3DCOLOR _dwColor = m_dwRectColor);
public:
	//장치 초기화시 지원되는 해상도로만 설정해줘야지 전체화면을 할수있다.
	HRESULT InitDevice(const DWORD& _dwWinCX
					  , const DWORD& _dwWinCY
					  , MODE _eMode);
	void	Render_Begin();
	void	Render_End(HWND _hWnd = nullptr);
	void	Release();

private:
	// 장치 검증에 필요한 Com객체
	// LPDIRECT3DDEVICE9의 생성도 맡는다.
	LPDIRECT3D9			m_pSDK;

	// 그래픽 장치를 제어할 Com객체
	LPDIRECT3DDEVICE9	m_pGraphicDev;

	//이미지 렌더링 Com객체	
	//D2D에서만 사용 I로 시작하는 것들은 COM 객체
	LPD3DXSPRITE		m_pSprite;
	LPD3DXLINE			m_pLine;
	LPD3DXFONT			m_pFont[(int)ENUM::FONT::END];
	// COM(Component(부품) Object Model)

	static D3DCOLOR		m_dwFontColor;
	static D3DCOLOR		m_dwLineColor;
	static D3DCOLOR		m_dwRectColor;

	D3DXVECTOR2			m_vPointArr[7];	//네모, 마름모, 육각형를 그리기 위한 임시 변수
};

