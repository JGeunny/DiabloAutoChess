#include "stdafx.h"
#include "GameImage.h"

CGameImage::CGameImage()
	:m_bIsInit(false)
	, m_pDeviceMgr(CDeviceMgr::GetInstance())
	, m_pTextureMgr(CTextureMgr::GetInstance())
	, m_pKeyMgr(CKeyMgr::GetInstance())
	//, m_pSoundMgr(CSoundMgr::GetInstance())
	, m_pScrollMgr(CScrollMgr::GetInstance())
	, m_pObjMgr(CObjMgr::GetInstance())
	, m_bSelect(false)
	, m_bImpossible(false)
	, m_bVisible(true)
	, m_bInfoRender(false)
	, m_bActivate(true)
{
	ZeroMemory(m_szFrameKey, sizeof(m_szFrameKey));
	m_tDraw = DRAW_INFO();
	m_tFrame = FRAME();
}

CGameImage::~CGameImage()
{
}

HRESULT CGameImage::LateInit()
{
	if (!m_bIsInit)
	{
		//for (int i = 0; i < (int)ENUM::LiveTime::END; ++i)
		//{
		//	if (0 != m_iLiveTimeCycle[i])
		//		m_uLiveTime[i] = m_pTimeMgr->GetNowTime();
		//}
		m_bIsInit = true;
		this->LateInit();
	}
	return S_OK;
}

void CGameImage::Render_Scroll()
{
	if (!m_bVisible) return;

	static D3DCOLOR color;
	color = m_tDraw.color;
	if (m_bSelect)
		m_tDraw.color = INIT_COLOR_SELECT;
	if (m_bImpossible)
		m_tDraw.color = INIT_COLOR_IMPOSSIBLE;

	static D3DXVECTOR3 vPos;
	vPos = m_tDraw.vPos;
	m_tDraw.vPos -= m_pScrollMgr->GetScroll();

	if (IsRendering())
	{
		this->Render();
		if(m_bInfoRender)
			RenderInfo();
	}
	m_tDraw.vPos = vPos;
	m_tDraw.color = color;
}

bool CGameImage::IsRendering()
{
	static POINT pt;
	static RECT rtScreen = { -TILECX, -TILECY, WINCX + TILECX, WINCY + TILECY };
	pt = { (LONG)m_tDraw.vPos.x, (LONG)m_tDraw.vPos.y };

	return (1 == PtInRect(&rtScreen, pt));
}

void CGameImage::RenderInfo()
{
}

void CGameImage::MoveFrame()
{
  	if (m_tFrame.uFrameTime + m_tFrame.uFrameSpeed < m_pTimeMgr->GetNowTime())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.uFrameTime = m_pTimeMgr->GetNowTime();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = 0;
}

