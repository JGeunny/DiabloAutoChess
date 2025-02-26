#include "stdafx.h"
#include "GameObject.h"
#include "GameString.h"

#ifdef CLIENT
#include "Stun.h"
#include "TraitBuff.h"
#endif

CGameObject::CGameObject()
	:m_eCurState(ENUM::State::NONE)
	, m_eNextState(ENUM::State::IDLE)
	, m_uValidityTime(0)
	, m_bControlFocus(false)
	, m_bCollisionLand(true)
	, m_iCheckHp(0)
	, m_bReStartAstar(false)
	, m_bStun(false)
	, m_bBeOnTheLand(false)
	, m_bBuff(false)
{
	m_tStatus = STATUS_INFO();

#ifdef CLIENT
	m_pTextureMgr->LoadTexture(L"HpBar", L"../Image/UI/HpBar/HpBar.png");
	m_pTextureMgr->LoadTexture(L"HpBarEmpty", L"../Image/UI/HpBar/HpBarEmpty.png");
	m_pTextureMgr->LoadTexture(L"MpBar", L"../Image/UI/MpBar/MpBar.png");
	m_pTextureMgr->LoadTexture(L"MpBarEmpty", L"../Image/UI/MpBar/MpBarEmpty.png");
#endif

	SetDelayTime(ENUM::LiveTime::FSM_INIT_ASTAR, 1500);
}

CGameObject::~CGameObject()
{
}

HRESULT CGameObject::LateInit()
{
	return S_OK;
}

void CGameObject::RenderInfo()
{
#ifdef CLIENT
	static D3DXVECTOR3 vPos;
	static int		iDamage;
	static WCHAR	szDamage[MID_STR];
	static DRAW_INFO tHpBar;
	static DRAW_INFO tMpBar;
	static D3DCOLOR	 dwFontColor;
	if (m_tStatus.iMaxHp <= 0) return;	//피가 있다면 출력
	if (m_tStatus.iMaxMp <= 0) return;	//마나가 있다면 출력

	dwFontColor = INIT_COLOR;

	tHpBar = DRAW_INFO();
	tMpBar = DRAW_INFO();
	vPos = m_tDraw.vPos;
	vPos.y = (float)m_tDraw.GetRect().top - 10;

	tMpBar.vPos = vPos;

	tMpBar.vSize = { 80.f, 5.f, 0.f };
	tMpBar.SetTexInfo(m_pTextureMgr->GetTexInfo(L"MpBarEmpty"));
	tMpBar.matCurrent = tMpBar.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	tMpBar.color = INIT_COLOR;
	m_pDeviceMgr->DrawImage(tMpBar);
	tMpBar.vSize = { 80.f * m_tStatus.iMp / m_tStatus.iMaxMp, 4.f, 0.f };
	tMpBar.vPos.x -= (80.f - tMpBar.vSize.x) * 0.5f;
	tMpBar.SetTexInfo(m_pTextureMgr->GetTexInfo(L"MpBar"));
	tMpBar.matCurrent = tMpBar.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	m_pDeviceMgr->DrawImage(tMpBar);
	
	vPos.y -= 5.f;
	tHpBar.vPos = vPos;

	tHpBar.vSize = { 80.f, 8.f, 0.f };
	tHpBar.SetTexInfo(m_pTextureMgr->GetTexInfo(L"HpBarEmpty"));
	tHpBar.matCurrent = tHpBar.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	tHpBar.color = INIT_COLOR;
	m_pDeviceMgr->DrawImage(tHpBar);
	tHpBar.vSize = { 80.f * m_tStatus.iHp / m_tStatus.iMaxHp, 6.f, 0.f };
	tHpBar.vPos.x -= (80.f - tHpBar.vSize.x) * 0.5f;
	tHpBar.SetTexInfo(m_pTextureMgr->GetTexInfo(L"HpBar"));
	tHpBar.matCurrent = tHpBar.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	if (m_tStatus.eTeam == ENUM::Team::ONE || m_tStatus.eTeam == ENUM::Team::NONE)
		tHpBar.color = INIT_COLOR_YELLOW;
	else
	{
		tHpBar.color = INIT_COLOR_RED;
		dwFontColor = INIT_COLOR_RED;
	}
	m_pDeviceMgr->DrawImage(tHpBar);

	vPos.y -= 15.f;
	m_pDeviceMgr->DrawString(m_tStatus.szName, lstrlen(m_tStatus.szName), vPos, 5UL, dwFontColor, ENUM::FONT::FONT16);

	if (0 >= m_tStatus.iHp)
	{
		m_eEvent = ENUM::Event::DEAD;
	}
	vPos += m_pScrollMgr->GetScroll();

	if (m_iCheckHp == 0)
		m_iCheckHp = m_tStatus.iHp;
	if (m_iCheckHp != m_tStatus.iHp)
	{
		iDamage = m_tStatus.iHp - m_iCheckHp;
		m_iCheckHp = m_tStatus.iHp;
		if (iDamage > 0) // 기본 체력이 이전(checkhp) 보다 높으면 회복이므로 초록색
		{
			dwFontColor = (GetTeam() == ENUM::Team::ONE) ? INIT_COLOR_GREEN : INIT_COLOR_YELLOW;
		}
		else
		{
			dwFontColor = (GetTeam() == ENUM::Team::ONE) ? INIT_COLOR_RED : INIT_COLOR;
		}
		iDamage = abs(iDamage);
		_itow_s(iDamage, szDamage, 10);
		
		m_pObjMgr->AddObject(ENUM::UIType::EFFECT, CGameString::Create(vPos.x, vPos.y, 80.f, 30.f, szDamage, dwFontColor));
	}

	if (m_bStun && 0 == GetDelayTime(ENUM::LiveTime::STUN))
	{
		SetDelayTime(ENUM::LiveTime::STUN, 3000);
		CStun* pStun = CStun::Create();
		pStun->SetTarget(this);
		m_pObjMgr->AddObject(ENUM::UIType::EFFECT, pStun);
		m_eNextState = ENUM::State::IDLE;
	}
	if (IsActivateTime(ENUM::LiveTime::STUN))
	{
		SetDelayTime(ENUM::LiveTime::STUN, 0);
		m_bStun = false;
	}

	if (m_bBuff && 0 == GetDelayTime(ENUM::LiveTime::BUFF))
	{
		SetDelayTime(ENUM::LiveTime::BUFF, 2000);
		CTraitBuff* pBuff = CTraitBuff::Create();
		pBuff->SetTarget(this);
		m_pObjMgr->AddObject(ENUM::UIType::EFFECT, pBuff);
	}
	if (IsActivateTime(ENUM::LiveTime::BUFF))
	{
		SetDelayTime(ENUM::LiveTime::BUFF, 0);
		m_bBuff = false;
	}
#endif
}

void CGameObject::FSM()
{
	if (m_vMoveCheckPos != m_tDraw.vPos)
	{
		m_vMoveCheckPos = m_tDraw.vPos;
		if (m_bCollisionLand)
		{
			if (m_eNextState == ENUM::State::WALK)
			{
				//if (m_pObjMgr->CollisionExUnit(this))
				//{
				//	m_bReStartAstar = true;
				//}
				//else
				//{
				//	if (m_bReStartAstar)
				//	{
				//		m_bReStartAstar = false;
				//		if (IsActivateTime(ENUM::LiveTime::FSM_INIT_ASTAR))
				//		{
				//			m_eNextState = ENUM::State::IDLE;
				//		}
				//	}
				//}
				if (m_pObjMgr->CollisionExUnit(this))
				{
					if (IsActivateTime(ENUM::LiveTime::FSM_INIT_ASTAR))
					{
						m_eNextState = ENUM::State::IDLE;
					}
				}
			}
		}
	}
	if (m_eCurState != m_eNextState)
	{
		FSM();
		m_eCurState = m_eNextState;
	}
}

bool CGameObject::ReceiveAttack(int _iAtt)
{
	//if (m_bInfoRender)//데미지 효과 넣기
	//{
	//	m_tDraw.color = INIT_COLOR_RED;
	//}

	m_tStatus.iHp -= _iAtt;
	if (m_tStatus.iHp <= 0)
	{
		m_tStatus.iHp = 0;
		return true;
	}
	return false;
}

bool CGameObject::IsHit(CGameObject * _pObj)
{
	if (0 == m_uValidityTime) return true;
	bool IsHit = false;
	if (m_mapAttackTime.find(_pObj) != m_mapAttackTime.end())
	{
		if (m_mapAttackTime[_pObj] + m_uValidityTime > m_pTimeMgr->GetNowTime())
		{
			IsHit = false;
		}
		else
		{
			m_mapAttackTime[_pObj] = m_pTimeMgr->GetNowTime();
			IsHit = true;
		}
	}
	else
	{
		m_mapAttackTime.insert({ _pObj, m_pTimeMgr->GetNowTime() });
		IsHit = true;
	}
	return IsHit;
}

bool CGameObject::IsRecogDist(CGameObject * _pObj)
{
	return IsRecogDist(m_tDraw.GetDist(_pObj->GetPos()));
}

