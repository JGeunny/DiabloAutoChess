#include "stdafx.h"
//#include "../../Client/stdafx.h"
#include "Mouse.h"
#include "MouseImage.h"
#include "BaseMouseImageImp.h"

#include "GameObject.h"

IMPLEMENT_CREATE(CMouse)
CMouse::CMouse()
	:m_pMouseImage(nullptr)
	, m_eCurMouseState(ENUM::MouseState::NONE)
	, m_eNextMouseState(ENUM::MouseState::NORMAL)
{
	
}

CMouse::~CMouse()
{
	Release();
}

HRESULT CMouse::Initialize()
{
	ShowCursor(FALSE);
	m_tDraw.vSize.x = 160.f;
	m_tDraw.vSize.y = 160.f;
	//m_tDraw.vAngle.z = -45.f;

	m_pMouseImage = CMouseImage::Create(CBaseMouseImageImp::Create());
	return S_OK;
}

HRESULT CMouse::LateInit()
{
	return S_OK;
}

int CMouse::Update()
{
	if (ENUM::Event::DEAD == m_eEvent)
		return (int)m_eEvent;

	CGameImage::LateInit();
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	
	RECT rt;
	GetClientRect(g_hWnd, &rt);
	
	//최소화 시킬시 화면이 0이 되버려서 0을 나누면 터진다;;
	if (rt.right <= 0 || rt.bottom <= 0) return (int)m_eEvent;

	m_tDraw.vPos.x = float(pt.x*WINCX/rt.right);
	m_tDraw.vPos.y = float(pt.y*WINCY/rt.bottom);

	if (ENUM::MouseState::NORMAL != m_eNextMouseState)
	{
		if(m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_eNextMouseState = ENUM::MouseState::NORMAL;
	}
	if (m_pKeyMgr->KeyDown(KEY::RBUTTON))
	{
		m_eNextMouseState = ENUM::MouseState::CLICK;
	}
	CGameObject* pUnit = m_pObjMgr->GetObjectInList(GetPosScroll());
	if (pUnit)
	{
		if (pUnit->GetTeam() == ENUM::Team::ONE || pUnit->GetTeam() == ENUM::Team::NONE)
		{
			m_eNextMouseState = ENUM::MouseState::MAG_ALLY;
		}
		else
		{
			m_eNextMouseState = ENUM::MouseState::MAG_ENEMY;
		}
	}

	return (int)m_eEvent;
}

void CMouse::LateUpdate()
{
	CGameImage::MoveFrame();
	ChangeState();
}

void CMouse::Render()
{
	//static D3DXVECTOR3 vPosTemp;
	//if (0 != lstrcpy(m_szFrameKey, L""))
	//{
	//	vPosTemp = m_tDraw.vPos;
	//	m_tDraw.vPos.x += m_tDraw.vSize.x * 0.5f;
	//	m_tDraw.vPos.y += m_tDraw.vSize.y * 0.5f;
	//	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(m_szFrameKey));
	//	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();
	//	m_pDeviceMgr->DrawImage(m_tDraw);
	//	m_tDraw.vPos = vPosTemp;
	//}
	m_pMouseImage->Render(m_tDraw, m_tFrame);
}

void CMouse::Release()
{
	SafeDelete(m_pMouseImage);
}

D3DXVECTOR3 CMouse::GetPosScroll()
{
	return m_tDraw.vPos + m_pScrollMgr->GetScroll();
}

POINT CMouse::GetPoint()
{
	return POINT() = {LONG(m_tDraw.vPos.x), LONG(m_tDraw.vPos.y)};
}

POINT CMouse::GetPointScroll()
{
	
	POINT& pt = GetPoint();
	m_pScrollMgr->ClientToScroll(&pt);
	return pt;
}

void CMouse::ChangeState()
{
	if (m_eCurMouseState != m_eNextMouseState)
	{
		m_eCurMouseState = m_eNextMouseState;
		m_pMouseImage->ChangeState(m_eNextMouseState, m_tFrame);
	}
}
