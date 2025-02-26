#include "stdafx.h"
#include "Panel.h"
#include "ControlMgr.h"
#include "Mouse.h"

IMPLEMENT_CREATE_COMPONENT(CPanel)
CPanel::CPanel()
	:m_szPanelName(L"")
	, m_bMovePanel(false)
{
	m_bActivate = false;
}


CPanel::~CPanel()
{
}

HRESULT CPanel::Initialize()
{
	m_pTextureMgr->LoadTexture(L"Panel|Panel", L"../Image/UI/Store/Panel.png");

	m_tDraw.vSize = { 250.f, 350.f, 0.f };
	return S_OK;
}

HRESULT CPanel::LateInit()
{
	return S_OK;
}

void CPanel::Release()
{
}

int CPanel::Update()
{
	if (!m_bActivate) return (int)m_eEvent;
	static RECT rtMoveRect;
	static RECT rtCloseRect;
	CMouse* pMouse = CControlMgr::GetInstance()->GetMouse();
	m_tDrawTitle.vSize = m_tDraw.vSize;
	m_tDrawTitle.vSize.y = 20;
	m_tDrawTitle.vPos = m_tDraw.vPos;
	m_tDrawTitle.vPos.y += -m_tDraw.vSize.y*0.5f + m_tDrawTitle.vSize.y * 0.5f;

	rtMoveRect = m_tDrawTitle.GetRect();
	rtCloseRect = rtMoveRect;
	rtCloseRect.left = rtCloseRect.right - 20;
	//if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)

	if (FUNC::CHECK::PosInRect(rtCloseRect, pMouse->GetPos()))
	{
		if (m_pKeyMgr->KeyDown(KEY::LBUTTON, KeyChannel::UI))
		{
			CSoundMgr::GetInstance()->MyPlaySound(L"button.wav", CSoundMgr::CHANNELID::UI);
			m_bActivate = false;
		}
	}
	else if (FUNC::CHECK::PosInRect(rtMoveRect, pMouse->GetPos()))
	{
		if (m_pKeyMgr->KeyDown(KEY::LBUTTON, KeyChannel::UI))
		{
			m_bMovePanel = true;
			m_vClickPos = pMouse->GetPos();
			m_vDrawPos = m_tDraw.vPos;
		}

		if (m_pKeyMgr->KeyUp(KEY::LBUTTON, KeyChannel::UI))
		{
			m_bMovePanel = false;
		}
	}


	if(m_bMovePanel)
		m_tDraw.vPos = m_vDrawPos - (m_vClickPos - pMouse->GetPos());
	return (int)m_eEvent;
}

void CPanel::LateUpdate()
{
	if (!m_bActivate) return;
}

void CPanel::Render()
{
	if (!m_bActivate) return;
	static RECT rtStringRect;

	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(L"Panel|Panel"));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

	m_pDeviceMgr->DrawImage(m_tDraw);

	rtStringRect = m_tDrawTitle.GetRect();
	m_pDeviceMgr->DrawString(m_szPanelName, lstrlen(m_szPanelName), &rtStringRect, 5UL, INIT_COLOR_IVORY, ENUM::FONT::FONT16);
	//m_pDeviceMgr->DrawRectangle(rtStringRect);

}
