#include "stdafx.h"
#include "TraitBuff.h"

IMPLEMENT_CREATE(CTraitBuff)
CTraitBuff::CTraitBuff()
{
}


CTraitBuff::~CTraitBuff()
{
	Release();
}

HRESULT CTraitBuff::Initialize()
{
	SetDelayTime(ENUM::LiveTime::LIVE, 2000);
	LoadGameImage();
	//m_pTextureMgr->LoadTexture(L"TraitBuff|TraitBuff", L"../Image/Effect/TraitBuff/%d.png", 16, 1, 1, D3DCOLOR_ARGB(255, 4, 4, 4));

	//m_tDraw.vSize = { 127.f, 148.f, 0.f };
	m_tFrame.iFrameKey = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.uFrameSpeed = 50;

	m_pTarget = CObserver::Create();
	m_tDraw.color = D3DCOLOR_ARGB(255, 255, 255, 255);
	return S_OK;

}
HRESULT CTraitBuff::LateInit()
{
	return S_OK;
}

void CTraitBuff::Release()
{
	SafeDelete(m_pTarget);
}

int CTraitBuff::Update()
{
	CObserver::LiveTime();
	CGameImage::LateInit();
	CObserver* pObj = m_pTarget->GetTarget(ENUM::Target::PARENT);
	if (!pObj) m_eEvent = ENUM::Event::DEAD;
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}
	CGameImage* pUnit = static_cast<CGameImage*>(pObj);

	auto& tDraw = pUnit->GetDrawInfo();
	m_tDraw.vPos = tDraw.GetImagePos();
	m_tDraw.vSize = tDraw.GetSizeCollision();
	m_tDraw.vSize.x = m_tDraw.vSize.y;
	//m_tDraw.vSize.y = 300;
	//m_tDraw.vPos.y = (float)tDraw.GetRect().top - 40;
	//m_tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	//Control();
	return (int)m_eEvent;
}

void CTraitBuff::LateUpdate()
{
	MoveFrame();
}

void CTraitBuff::Render()
{
	//static RECT rtSize;
	//rtSize = m_tDraw.GetRect();
	//m_pDeviceMgr->DrawRectangle(rtSize);
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::TRAITBUFF, m_tFrame.iFrameScene, m_tFrame.iFrameStart));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	//	std::cout << _tFrame.iFrameScene << ":" << _tFrame.iFrameStart << std::endl;
	//m_pDeviceMgr->DrawImage(m_tDraw, nullptr, CDeviceMgr::DRAWTYPE::ALPHA);
	m_pDeviceMgr->DrawImage(m_tDraw);
}

void CTraitBuff::SetTarget(CObserver * _pTarget)
{
	m_pTarget->SetTarget(ENUM::Target::PARENT, _pTarget);
}

void CTraitBuff::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"TraitBuff|TraitBuff", L"../Image/Effect/TraitBuff/%d.png", 16, 1, 1, D3DCOLOR_ARGB(255, 4, 4, 4));
}