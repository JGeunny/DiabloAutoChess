#include "stdafx.h"
#include "BoneSprite.h"
#include "Bone.h"

IMPLEMENT_CREATE(CBoneSprite)
CBoneSprite::CBoneSprite()
{
}


CBoneSprite::~CBoneSprite()
{
}

HRESULT CBoneSprite::Initialize()
{
	CSoundMgr::GetInstance()->MyPlaySound(L"DurielSkill.wav", CSoundMgr::CHANNELID::EFFECT);
	SetDelayTime(ENUM::LiveTime::LIVE, 1500);
	SetDelayTime(ENUM::LiveTime::SKILL, 100);
	m_tDraw.vSize = { 100, 100.f, 0.f };
	m_tDraw.vSizeCollision = { 50.f, 50.f, 0.f };
	m_tDraw.vPosFit = { 0.f, -25.f, 0.f };
	m_tDraw.fSpeed = INIT_SPEED_FAST;

	return S_OK;
}

HRESULT CBoneSprite::LateInit()
{
	return E_NOTIMPL;
}

void CBoneSprite::Release()
{
}

int CBoneSprite::Update()
{
	static D3DXVECTOR3 vAngle;
	static D3DXVECTOR3 vPos;
	static D3DXVECTOR3 vDir;

	CObserver::LiveTime();
	CGameImage::LateInit();
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}

	m_tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	if (IsActivateTime(ENUM::LiveTime::SKILL))
	{
		vAngle = m_tDraw.vAngle;
		vPos = m_tDraw.vPos;

		CGameObject* pSkill = CBone::Create(vPos.x, vPos.y, vAngle.z);
		pSkill->SetTeam(m_tStatus.eTeam);
		pSkill->GetStatusInfo().iAtt = m_tStatus.iAtt * 1;
		m_pObjMgr->AddObject(ENUM::ObjType::SKILL,
			pSkill);
	}

	return (int)m_eEvent;
}

void CBoneSprite::LateUpdate()
{
	CGameImage::MoveFrame();
}

void CBoneSprite::Render()
{
}
