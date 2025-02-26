#include "stdafx.h"
#include "FrozenOrb.h"
#include "IceBolt.h"

IMPLEMENT_CREATE(CFrozenOrb)
CFrozenOrb::CFrozenOrb()
{
}


CFrozenOrb::~CFrozenOrb()
{
}

HRESULT CFrozenOrb::Initialize()
{
	CSoundMgr::GetInstance()->MyPlaySound(L"FrozenOrb.wav", CSoundMgr::CHANNELID::EFFECT);
	SetDelayTime(ENUM::LiveTime::LIVE, 1550);
	m_tDraw.vSize = { 80.f, 80.f, 0.f };
	m_tDraw.fSpeed = INIT_SPEED_SLOW;

	LoadGameImage();
	//m_pTextureMgr->LoadTexture(L"FrozenOrb", L"../Image/Skill/FrozenOrb/%d.png", 16, 1, 1, INIT_COLOR_BLACK);

	m_tStatus.iHp = 1;

	SetDelayTime(ENUM::LiveTime::SKILL, 300);

	m_tFrame.iFrameKey = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 0;
	m_tFrame.uFrameSpeed = 20;

	m_tDraw.color = D3DCOLOR_ARGB(100, 255, 255, 255);
	return S_OK;
}

HRESULT CFrozenOrb::LateInit()
{
	return S_OK;
}

void CFrozenOrb::Release()
{
}

int CFrozenOrb::Update()
{
	CObserver::LiveTime();
	CGameImage::LateInit();
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}

	m_tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	//Control();

	static D3DXVECTOR3 vAngle;
	static D3DXVECTOR3 vPos;
	static D3DXVECTOR3 vDir;
	if (IsActivateTime(ENUM::LiveTime::SKILL))
	{
		vAngle.z = 0;
		for (int i = 0; i < 18; ++i)
		{
			vAngle.z += 20;
			vPos = m_tDraw.vPos;
			vDir = FUNC::GET::Dir(vAngle);
			vDir *= 30;
			vPos += vDir;

			CGameObject* pSkill = CBulletPoolMgr::GetInstance()->GetBullet(CBulletPoolMgr::eIceBolt);
			if (pSkill)
			{
				pSkill->SetPos(vPos);
				pSkill->SetAngle(vAngle.z);
			}
			else
			{
				pSkill = CIceBolt::Create(vPos.x, vPos.y, vAngle.z);
			}
			pSkill->SetTeam(m_tStatus.eTeam);
			pSkill->GetStatusInfo().iAtt = m_tStatus.iAtt;
			m_pObjMgr->AddObject(ENUM::ObjType::SKILL,
				pSkill);
		}
	}

	return (int)m_eEvent;
}

void CFrozenOrb::LateUpdate()
{
	CGameImage::MoveFrame();
	//CGameObject::FSM();
}

void CFrozenOrb::Render()
{
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(L"FrozenOrb", m_tFrame.iFrameStart));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	m_pDeviceMgr->DrawImage(m_tDraw, nullptr, CDeviceMgr::DRAWTYPE::ALPHA);
}

void CFrozenOrb::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;
	CTextureMgr::GetInstance()->LoadTexture(L"FrozenOrb", L"../Image/Skill/FrozenOrb/%d.png", 16, 1, 1, INIT_COLOR_BLACK);
}