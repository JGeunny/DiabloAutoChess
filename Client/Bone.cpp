#include "stdafx.h"
#include "Bone.h"

IMPLEMENT_CREATE(CBone)
CBone::CBone()
	:m_bComeOut(true)
{
}

CBone::~CBone()
{
}

HRESULT CBone::Initialize()
{
	//m_iLiveTimeCycle[(int)ENUM::LiveTime::LIVE] = 1000;
	m_tDraw.vSize = { 100, 100.f, 0.f };
	m_tDraw.vSizeCollision = { 50.f, 50.f, 0.f };
	m_tDraw.vPosFit = {0.f, -25.f, 0.f};
	m_tDraw.fSpeed = INIT_SPEED_FAST;
	//m_tStatus.iClassID = CLASSID_LASER;

	LoadGameImage();

	//m_vecOrderType.resize(8);
	//for (int i = 0; i <= 7; ++i)
	//	m_vecOrderType[i] = i;

	//m_vScale = { 1.f, 1.f, 0.f };
	//m_vPosFit = { 0.f,  0.f, 0.f };
	m_tFrame.iFrameKey = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 13;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.uFrameSpeed = 20;
	//m_tFrame.pListSceneOrder = &m_vecOrderType;

	m_uValidityTime = 5000;//맞은 놈은 0.5초후에 또맞을수있다.

	m_tStatus.iMaxHp = 9999;
	m_tStatus.FnRecovery();

	m_tDraw.color = D3DCOLOR_ARGB(255, 255, 255, 255);
	return S_OK;
}

HRESULT CBone::LateInit()
{
	return E_NOTIMPL;
}

void CBone::Release()
{
}

int CBone::Update()
{
	CObserver::LiveTime();
	CGameImage::LateInit();
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd - 1 && !m_bComeOut)
		m_eEvent = ENUM::Event::DEAD;
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bComeOut = false;
	}
	//m_tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	//Control();
	return (int)m_eEvent;
}

void CBone::LateUpdate()
{
	CGameImage::MoveFrame();
}

void CBone::Render()
{
	static int iFrameStart = 0;

	if (!m_bComeOut && m_tFrame.iFrameStart != m_tFrame.iFrameEnd)
	{
		iFrameStart = m_tFrame.iFrameEnd - m_tFrame.iFrameStart;
	}
	else
	{
		iFrameStart = m_tFrame.iFrameStart;
	}

	//m_tFrame.SetScene(m_tDraw.vAngle.z);
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::BONE, m_tFrame.iFrameScene, 0));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	//m_pDeviceMgr->DrawImage(m_tDraw, nullptr, CDeviceMgr::DRAWTYPE::ALPHA);
	m_pDeviceMgr->DrawImage(m_tDraw, &m_tDraw.GetRectSprite(iFrameStart, m_tFrame.iFrameScene));
}

void CBone::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"Bone|Bone", L"../Image/Skill/Bone/Bone.png", -1, 14, 1, INIT_COLOR_BLACK);
}

