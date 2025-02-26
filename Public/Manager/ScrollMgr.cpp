#include "stdafx.h"
//#include "../../Client/stdafx.h"
#include "ScrollMgr.h"
#include "GameObject.h"
#include "Terrain.h"

#include "ControlMgr.h"
#include "Mouse.h"

IMPLEMENT_SINGLETON(CScrollMgr)
CScrollMgr::CScrollMgr()
	:m_pTarget(nullptr)
	, m_pKeyMgr(CKeyMgr::GetInstance())
{
	m_vScroll = { 0.f, 0.f, 0.f };
	m_pTarget = CObserver::Create();
}

CScrollMgr::~CScrollMgr()
{
	SafeDelete(m_pTarget);
}

int CScrollMgr::Initialize(CObserver * _pTerrain, CObserver * _pObject)
{
	SetTarget(ENUM::Target::FOCUS, _pObject);
	SetTarget(ENUM::Target::PARENT, _pTerrain);
	return 0;
}

int CScrollMgr::Update()
{
	MouseLock();
	ScrollTarget();
	ScrollLock();
	return 0;
}

void CScrollMgr::LateUpdate()
{
}

void CScrollMgr::Render()
{
}

void CScrollMgr::Control()
{
	static float fSpeed;
	static POINT ptMouse;
	static ENUM::MouseState eMouseState;

	GetCursorPos(&ptMouse);
	m_iMoveDir = DIR_NONE;
	fSpeed = INIT_SPEED * CTimeMgr::GetInstance()->GetDeltaTime();

	//std::cout << ptMouse.x << " | " << ptMouse.y << std::endl;

	//키보드 컨트롤
	if (m_pKeyMgr->KeyPressing(KEY::UP))
	{
		m_iMoveDir |= DIR_UP;
	}
	if (m_pKeyMgr->KeyPressing(KEY::DOWN))
	{
		m_iMoveDir |= DIR_DOWN;
	}
	if (m_pKeyMgr->KeyPressing(KEY::LEFT))
	{
		m_iMoveDir |= DIR_LEFT;
	}
	if (m_pKeyMgr->KeyPressing(KEY::RIGHT))
	{
		m_iMoveDir |= DIR_RIGHT;
	}

	//마우스 컨트롤
	if (m_rtScreen.left + 20 > ptMouse.x)
		m_iMoveDir |= DIR_LEFT;
	if (m_rtScreen.top + 20 > ptMouse.y)
		m_iMoveDir |= DIR_UP;
	if (m_rtScreen.right - 20 < ptMouse.x)
		m_iMoveDir |= DIR_RIGHT;
	if (m_rtScreen.bottom - 20 < ptMouse.y)
		m_iMoveDir |= DIR_DOWN;

	//스크롤 이동
	if (DIR_UP & m_iMoveDir)
		AddScrollY(-abs(fSpeed));
	if (DIR_DOWN & m_iMoveDir)
		AddScrollY(abs(fSpeed));
	if (DIR_LEFT & m_iMoveDir)
		AddScrollX(-abs(fSpeed));
	if (DIR_RIGHT & m_iMoveDir)
		AddScrollX(abs(fSpeed));

	eMouseState = ENUM::MouseState::NORMAL;
	if (DIR_UP & m_iMoveDir)
		eMouseState = ENUM::MouseState::SCROLL_U;
	if (DIR_DOWN & m_iMoveDir)
		eMouseState = ENUM::MouseState::SCROLL_D;
	if (DIR_LEFT & m_iMoveDir)
		eMouseState = ENUM::MouseState::SCROLL_L;
	if (DIR_RIGHT & m_iMoveDir)
		eMouseState = ENUM::MouseState::SCROLL_R;
	if(eMouseState != ENUM::MouseState::NORMAL)
		CControlMgr::GetInstance()->GetMouse()->SetMouseState(eMouseState);

}

void CScrollMgr::SetTarget(ENUM::Target eID, CObserver * _pObj)
{
	m_pTarget->ClearTarget(eID);
	m_pTarget->SetTarget(eID, _pObj);
}

void CScrollMgr::MouseLock()
{
	static POINT p1, p2;

	GetClientRect(g_hWnd, &m_rtScreen);
	p1 = { m_rtScreen.left, m_rtScreen.top };
	p2 = { m_rtScreen.right, m_rtScreen.bottom };
	ClientToScreen(g_hWnd, &p1);
	ClientToScreen(g_hWnd, &p2);
	m_rtScreen = { p1.x, p1.y, p2.x, p2.y };
	//ClipCursor(&m_rtScreen);
}

CObserver * CScrollMgr::GetTarget()
{
	return m_pTarget->GetTarget(ENUM::Target::FOCUS);
}

void CScrollMgr::ScrollTarget()
{
	static CObserver* pObj;
	static CGameObject* pTarget;
	pObj = m_pTarget->GetTarget(ENUM::Target::FOCUS);
	if (pObj) {
		pTarget = static_cast<CGameObject*>(pObj);
		m_vScroll.x = pTarget->GetPos().x - WINCX * 0.5f;
		m_vScroll.y = pTarget->GetPos().y - WINCY * 0.5f;
		return;
	}
	Control();
}

void CScrollMgr::ScrollLock()
{
	//cout << "X:" << m_ptScroll.x << " Y:" << m_ptScroll.y << endl;
	static CObserver* pObj;
	static CTerrain* pTarget;
	pObj = m_pTarget->GetTarget(ENUM::Target::PARENT);
	if (!pObj)
		return;
	pTarget = static_cast<CTerrain*>(pObj);

	static D3DXVECTOR3 vScrollLock;
	vScrollLock = {
		float(pTarget->GetMapCX() - WINCX),
		float(pTarget->GetMapCY() - WINCY),
		0.f
	};

	if (vScrollLock.x < m_vScroll.x)
	{
		m_vScroll.x = vScrollLock.x;
	}
	if (vScrollLock.y < m_vScroll.y)
	{
		m_vScroll.y = vScrollLock.y;
	}

	if (m_vScroll.x < 0)
		m_vScroll.x = 0;
	if (m_vScroll.y < 0)
		m_vScroll.y = 0;
}
