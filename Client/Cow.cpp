#include "stdafx.h"
#include "Cow.h"
#include "ControlMgr.h"
#include "Mouse.h"

IMPLEMENT_CREATE(CCow)
CCow::CCow()
{
}


CCow::~CCow()
{
}

HRESULT CCow::Initialize()
{
	m_bInfoRender = true;
	//SetDelayTime(ENUM::LiveTime::LIVE, 3000);
	m_pTextureMgr->LoadTexture(L"Cow|Cow", L"../Image/Unit/NPC/Cow/%d.png", 10);

	m_tDraw.vSize = { 400.f, 400.f, 0.f };
	m_tDraw.vSizeCollision = {120.f, 200.f, 0.f};
	m_tFrame.iFrameKey = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.uFrameSpeed = 50;

	lstrcpy(m_tStatus.szName, L"상점주인");
	m_tStatus.iMaxHp = 100;
	m_tStatus.iMaxMp = 100;
	m_tStatus.FnRecovery();

	return S_OK;
}

HRESULT CCow::LateInit()
{
	return S_OK;
}

void CCow::Release()
{
}

int CCow::Update()
{
	CObserver::LiveTime();
	CGameImage::LateInit();
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}

	auto pMouse = CControlMgr::GetInstance()->GetMouse();

	if (FUNC::CHECK::PosInRect(m_tDraw.GetRect(), pMouse->GetPosScroll()))
	{
		if (m_pKeyMgr->KeyDown(KEY::LBUTTON))
		{
			CSoundMgr::GetInstance()->MyPlaySound(L"store.wav", CSoundMgr::CHANNELID::UI);
			auto pObj = GetTarget(ENUM::Target::FOCUS);
			auto pObj2 = GetTarget(ENUM::Target::PARENT);
			if (pObj)
			{
				static_cast<CGameObject*>(pObj)->SetActivate(true);
			}
			if (pObj2)
			{
				static_cast<CGameObject*>(pObj2)->SetActivate(true);
			}
		}
	}
	return (int)m_eEvent;
}

void CCow::LateUpdate()
{
	CGameImage::MoveFrame();
}

void CCow::Render()
{
	static RECT rtCollisionRect;
	rtCollisionRect = m_tDraw.GetRect();

	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::COW, m_tFrame.iFrameScene, m_tFrame.iFrameStart));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	//m_pDeviceMgr->DrawImage(m_tDraw, nullptr, CDeviceMgr::DRAWTYPE::ALPHA);
	m_pDeviceMgr->DrawImage(m_tDraw);

	//m_pDeviceMgr->DrawRectangle(rtCollisionRect);
}
