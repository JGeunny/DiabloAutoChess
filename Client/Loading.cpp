#include "stdafx.h"
#include "Loading.h"

#include "Arrow.h"
#include "IceBolt.h"
#include "FrozenOrb.h"
#include "Whirlwind.h"
#include "Laser.h"
#include "Bone.h"

#include "Vs.h"
#include "Stun.h"
#include "TraitBuff.h"

#include "AmazonImage.h"
#include "DurielImage.h"
#include "BavarianImage.h"
#include "AndarielImage.h"
#include "DiaImage.h"
#include "IzualImage.h"
#include "BarlogImage.h"

IMPLEMENT_CREATE_BASE(CLoading)
CLoading::CLoading()
{
}


CLoading::~CLoading()
{
}

HRESULT CLoading::Initialize()
{
	//CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNELID::BGM);
	CSoundMgr::GetInstance()->StopAll();
	CSoundMgr::GetInstance()->PlayBGM(L"Loading.wav");
	SetDelayTime(ENUM::LiveTime::BASE, 300);
	m_tDraw.vPos = { WINCX * 0.5f, WINCY * 0.5f, 0.f };
	m_tDraw.vSize = { 400, 400, 0.f };
	m_pTextureMgr->LoadTexture(L"Loading", L"../Image/Loading/%d.png", 10);
	return S_OK;
}

void CLoading::Release()
{
}

int CLoading::Update()
{
	switch (m_tFrame.iFrameStart)
	{
	case 0:
		CArrow::LoadGameImage();
		CIceBolt::LoadGameImage();
		CFrozenOrb::LoadGameImage();
		CWhirlwind::LoadGameImage();
		CLaser::LoadGameImage();
		CBone::LoadGameImage();
		break;
	case 1:
		CVs::LoadGameImage();
		CStun::LoadGameImage();
		CTraitBuff::LoadGameImage();
		break;
	case 2:
		CAmazonImage::LoadGameImage();
		break;
	case 3:
		CDurielImage::LoadGameImage();
		break;
	case 4:
		CBavarianImage::LoadGameImage();
		break;
	case 5:
		CAndarielImage::LoadGameImage();
		break;
	case 6:
		CDiaImage::LoadGameImage();
		break;
	case 7:
		CIzualImage::LoadGameImage();
		break;
	case 8:
		CBarlogImage::LoadGameImage();
		break;
	}
	if (IsActivateTime(ENUM::LiveTime::BASE))
		++m_tFrame.iFrameStart;
	return (int)ENUM::Event::NOEVENT;
}

void CLoading::LateUpdate()
{
	if (m_tFrame.iFrameStart >= 9)
	{
		m_pSceneMgr->SceneChange(ENUM::Scene::TITLE);
	}
}

void CLoading::Render()
{
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(L"Loading", m_tFrame.iFrameStart));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();
	m_pDeviceMgr->DrawImage(m_tDraw);
}
