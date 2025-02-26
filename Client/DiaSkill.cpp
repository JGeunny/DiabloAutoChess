#include "stdafx.h"
#include "DiaSkill.h"
#include "Dia.h"
#include "Laser.h"

IMPLEMENT_CREATE(CDiaSkill)
CDiaSkill::CDiaSkill()
	:m_fSkillRecogDist(0)
	, m_doSkill(true)
{
}

CDiaSkill::~CDiaSkill()
{
	CObserver* pObj = m_pTarget[(int)ENUM::Target::PARENT];
	if (pObj)
	{
		CDia* pUnit = static_cast<CDia*>(m_pTarget[(int)ENUM::Target::PARENT]);
		auto& tStatusInfo = pUnit->GetStatusInfo();
		tStatusInfo.fRecogDist = m_fSkillRecogDist;
		pUnit->SetState(ENUM::State::IDLE);
		pUnit->FSM();
	}
}

HRESULT CDiaSkill::Initialize()
{
	SetDelayTime(ENUM::LiveTime::LIVE, 5500);
	SetDelayTime(ENUM::LiveTime::BASE, 5000);
	SetDelayTime(ENUM::LiveTime::SKILL, 100);
	//m_tDraw.vSize = { 200.f, 200.f, 0.f };
	//m_tDraw.vSize = { 180.f, 160.f, 0.f };
	//m_tDraw.vPosFit = { 0.f, -50.f, 0.f };
	//m_tDraw.fSpeed = INIT_SPEED_FAST;
	//m_tDraw.color = INIT_COLOR_OPACITY;

	return S_OK;
}

HRESULT CDiaSkill::LateInit()
{
	CObserver* pObj = m_pTarget[(int)ENUM::Target::PARENT];
	if (!pObj) return S_FALSE;
	CDia* pUnit = static_cast<CDia*>(pObj);
	
	if (pUnit)
	{
		auto& tStatusInfo = pUnit->GetStatusInfo();
		pUnit->SetDiaSkill();
		m_fSkillRecogDist = tStatusInfo.fRecogDist;
		tStatusInfo.fRecogDist = 500;
	}
	return S_OK;
}

void CDiaSkill::Release()
{
}

int CDiaSkill::Update()
{
	//부모가 없다면 죽임
	if (!m_pTarget[(int)ENUM::Target::PARENT]) return (int)(m_eEvent = ENUM::Event::DEAD);
	CObserver::LiveTime();
	CGameImage::LateInit();
	if (ENUM::Event::DEAD == m_eEvent)
	{
		return (int)m_eEvent;
	}
	CObserver* pObj = m_pTarget[(int)ENUM::Target::PARENT];
	if (!pObj) return (int)ENUM::Event::DEAD;
	CDia* pUnit = static_cast<CDia*>(pObj);
	if(ENUM::State::ATTACK != pUnit->GetState())  return (int)ENUM::Event::DEAD;

	static D3DXVECTOR3 vAngle;
	static D3DXVECTOR3 vPos;
	static D3DXVECTOR3 vDir;

	auto& tDrawInfo = pUnit->GetDrawInfo();
	auto& tFrame = pUnit->GetFrame();
	//////////////////////////////
	//디아 스킬 모션이 아니라면 다시 세팅
	if(tFrame.iFrameKey < 4)
		pUnit->SetDiaSkill();
	//////////////////////////////
	m_tDraw.vPos = tDrawInfo.vPos;
	m_tDraw.vAngle = tDrawInfo.vAngle;

	if (IsActivateTime(ENUM::LiveTime::BASE))
	{
		m_doSkill = false;
	}
	if (m_doSkill)
	{
		if (tFrame.iFrameStart >= 13)
			tFrame.iFrameStart = 9;
		if (tFrame.iFrameStart >= 9 && tFrame.iFrameStart <= 13)
		{
			if (IsActivateTime(ENUM::LiveTime::SKILL))
			{
				if(0 == GetDelayTime(ENUM::LiveTime::BUFF))
					SetDelayTime(ENUM::LiveTime::BUFF, 2000);
				if(IsActivateTime(ENUM::LiveTime::BUFF))
					CSoundMgr::GetInstance()->MyPlaySound(L"lazer.wav", CSoundMgr::CHANNELID::EFFECT);
				vAngle = m_tDraw.vAngle;
				vPos = m_tDraw.vPos;
				vDir = FUNC::GET::Dir(vAngle);
				vDir *= 40;
				vPos += vDir;

				CGameObject* pSkill = CBulletPoolMgr::GetInstance()->GetBullet(CBulletPoolMgr::eLaser);
				if (pSkill)
				{
					pSkill->SetPos(vPos);
					pSkill->SetAngle(vAngle.z);
				}
				else
				{
					pSkill = CLaser::Create(vPos.x, vPos.y, vAngle.z);
				}
				pSkill->SetTeam(m_tStatus.eTeam);
				pSkill->GetStatusInfo().iAtt = int(m_tStatus.iAtt * 0.5f);
				m_pObjMgr->AddObject(ENUM::ObjType::SKILL,
					pSkill);
			}
		}
	}
	//m_tDraw.vPosFit = tDrawInfo.vPosFit;
	//m_tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	//Control();
	return (int)m_eEvent;
}

void CDiaSkill::LateUpdate()
{
	CGameImage::MoveFrame();
}

void CDiaSkill::Render()
{

}
