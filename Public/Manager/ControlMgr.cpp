#include "stdafx.h"
#include "ControlMgr.h"
#include "Mouse.h"
#include "Astar.h"
#include "Tile.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CControlMgr)
CControlMgr::CControlMgr()
	:m_pKeyMgr(CKeyMgr::GetInstance())
//	, m_pObjMgr(CObjMgr::GetInstance())
	, m_pTimeMgr(CTimeMgr::GetInstance())
	, m_pScrollMgr(CScrollMgr::GetInstance())
	, m_pMouse(nullptr)
	, m_pAstar(nullptr)
	, m_pTarget(nullptr)
	, m_bCameraFocus(false)
	, m_eControlState(ENUM::ControlState::NONE)
{
}

CControlMgr::~CControlMgr()
{
	Release();
}

HRESULT CControlMgr::Initialize()
{
	static bool isCreate = false;
	if (isCreate) return S_FALSE;
	isCreate = true;

	m_pMouse = CMouse::Create();
	CObjMgr::GetInstance()->AddObject(ENUM::UIType::MOUSE, m_pMouse);
	//m_pObjMgr->AddObject(ENUM::UIType::MOUSE, m_pMouse);

	m_pAstar = CAstar::Create();
	m_pTarget = CObserver::Create();

	m_tDrawSelect.vSize = {50.f, 50.f, 0.f};
	CTextureMgr::GetInstance()->LoadTexture(L"Select|Select", L"../Image/UI/Select/Select.png");
	m_tDrawSelect.SetTexInfo(CTextureMgr::GetInstance()->GetTexInfo(L"Select|Select"));

	return S_OK;
}

void CControlMgr::Update()
{
	if (m_pKeyMgr->KeyDown(KEY::Y))
		CameraFocus();
	if(m_pKeyMgr->KeyDown(KEY::TAB))
		ChangeTarget();
	CObserver* pObj = m_pTarget->GetTarget(ENUM::Target::FOCUS);
	if (!pObj) return;
	CGameObject* pUnit = static_cast<CGameObject*>(pObj);
	Control(pUnit);
}

void CControlMgr::Rander()
{
	m_lstCloseTargetAstar.clear();
	if (!GetTarget()) return;

	static D3DXVECTOR3 vPosTemp;
	vPosTemp = m_tDrawSelect.vPos;
	m_tDrawSelect.vPos -= CScrollMgr::GetInstance()->GetScroll();
	m_tDrawSelect.matCurrent = m_tDrawSelect.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	CDeviceMgr::GetInstance()->DrawImage(m_tDrawSelect);
	m_tDrawSelect.vPos = vPosTemp;
}

void CControlMgr::Release()
{
	SafeDelete(m_pAstar);
	SafeDelete(m_pTarget);
}

void CControlMgr::Control(CGameObject* _pUnit)
{
	//auto& tDraw = _pUnit->GetDrawInfo();
	//auto& eState = _pUnit->GetState();
	////Move
	//if (m_pKeyMgr->KeyUp(KEY::RBUTTON))
	//{
	//	m_pAstar->StartAstar(tDraw.vPos,
	//		GetMouse()->GetPosScroll());
	//}
	//auto& lstPath = m_pAstar->GetListPath();
	//float fDist = D3DXVec3Length(&(m_vTargetPos - tDraw.vPos));
	//if (!lstPath.empty())
	//{
	//	eState = ENUM::State::WALK;
	//	m_vTargetPos = lstPath.front()->GetDrawInfo().vPos;
	//	if (5.f > fDist)
	//		lstPath.pop_front();
	//}
	//else
	//	eState = ENUM::State::IDLE;

	//if (eState == ENUM::State::WALK)
	//{
	//	if (5.f <= fDist)
	//	{
	//		tDraw.SetAngle(m_vTargetPos);
	//		tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
	//	}
	//}

	////Attack
	//if (m_eControlState != ENUM::ControlState::NOATTACK)
	//{
	//	if (m_pKeyMgr->KeyPressing(KEY::LBUTTON))
	//	{
	//		tDraw.SetAngle(GetMouse()->GetPosScroll());
	//		eState = ENUM::State::ATTACK;
	//		lstPath.clear();
	//	}
	//	if (m_pKeyMgr->KeyPressing(KEY::Q))
	//	{
	//		tDraw.SetAngle(GetMouse()->GetPosScroll());
	//		eState = ENUM::State::ATTACK;
	//		lstPath.clear();
	//	}
	//}

	//CObserver::LiveTime();
	auto pMouse = GetMouse();
	if (!pMouse) return;
	static float fMoveDist = 200.f;
	static float fAttackDist = 120.f;
	auto& tDraw = _pUnit->GetDrawInfo();
	auto& eState = _pUnit->GetState();
	//auto pObserver = _pUnit->GetTarget(ENUM::Target::ENEMY);
	auto& lstPath = m_pAstar->GetListPath();
	float fDist = D3DXVec3Length(&(m_vTargetPos - tDraw.vPos));

	if (!lstPath.empty())
	{
		eState = ENUM::State::WALK;
	}
	else
		eState = ENUM::State::IDLE;

	if (ENUM::ControlState::NOATTACK != CControlMgr::GetInstance()->GetControlState())
	{
		if (m_pKeyMgr->KeyPressing(KEY::LBUTTON))
		{
			auto pEnemy = CObjMgr::GetInstance()->GetUnit(pMouse->GetPosScroll());//static_cast<CGameImage*>(pObserver);
			if (pEnemy)
			{
				if (fAttackDist >= FUNC::MATH::Dist(_pUnit->GetPos(), pEnemy->GetPos()))
				{
					_pUnit->SetTarget(ENUM::Target::ENEMY, pEnemy);
				}
			}
			eState = ENUM::State::ATTACK;
			if (!lstPath.empty())
				lstPath.clear();
			tDraw.SetAngle(GetMouse()->GetPosScroll());
		}
	}

	switch (eState)
	{
	case ENUM::State::NONE:
		break;
	case ENUM::State::IDLE:
	{
		if (m_pKeyMgr->KeyUp(KEY::RBUTTON))
		{
			if (lstPath.empty())
			{
				m_pAstar->StartAstar(tDraw.vPos,
					pMouse->GetPosScroll());
				eState = ENUM::State::WALK;
			}
		}
		//else
		//{
		//	if (CObserver::IsActivateTime(ENUM::LiveTime::MOVE))
		//	{
		//		tDraw.vAngle.z = (std::rand() * 1000 % 360);
		//		m_pAstar->StartAstar(tDraw.vPos,
		//			tDraw.vPos + FUNC::GET::Dir(tDraw.vAngle)*fMoveDist);
		//		eState = ENUM::State::WALK;
		//	}
		//}
	}
	break;
	case ENUM::State::WALK:
		if (!lstPath.empty())
		{
			m_vTargetPos = lstPath.front()->GetDrawInfo().vPos;
			if (5.f > fDist)
				lstPath.pop_front();
		}
		else
			eState = ENUM::State::IDLE;

		if (5.f <= fDist)
		{
			tDraw.SetAngle(m_vTargetPos);
			tDraw.FnMove(m_pTimeMgr->GetDeltaTime());
		}
		break;
	case ENUM::State::ATTACK:
		break;
	case ENUM::State::DEAD:
		break;
	default:
		break;
	}
	m_tDrawSelect.vPos = tDraw.vPos;
	m_tDrawSelect.vPos.y = float(tDraw.GetRect().top - 80);
}

void CControlMgr::ChangeTarget()
{
	m_pAstar->Release();
	static int iNext = 0;
	auto& lstUnit = CObjMgr::GetInstance()->GetObjectList(ENUM::ObjType::UNIT);
	if (lstUnit.empty()) return;

	CObserver* pObj = m_pTarget->GetTarget(ENUM::Target::FOCUS);
	if (pObj)
	{
		CGameObject* pUnit = static_cast<CGameObject*>(pObj);
		pUnit->SetControlFucus(false);
	}
	int i = -1;
	int iOneTeamCount = count_if(lstUnit.begin(), lstUnit.end(), [&](auto& _pObj) {
		return (ENUM::Team::ONE == _pObj->GetTeam());
	});
	if (iOneTeamCount <= iNext)
		iNext = 0;
	for (auto& pObj : lstUnit)
	{
		if ((ENUM::Team::ONE == pObj->GetTeam()))
			++i;
		if (i >= iNext)
		{
			pObj->SetControlFucus(true);
			m_pTarget->SetTarget(ENUM::Target::FOCUS, pObj);
			iNext = i + 1;
			//카메라 포커싱
			if (m_bCameraFocus)
				m_pScrollMgr->SetTarget(ENUM::Target::FOCUS, pObj);
			break;
		}
	}
}

void CControlMgr::CameraFocus(bool _bCameraFocus)
{
	if (_bCameraFocus)
		m_bCameraFocus = true;
	else
		m_bCameraFocus = !m_bCameraFocus;

	auto& lstUnit = CObjMgr::GetInstance()->GetObjectList(ENUM::ObjType::UNIT);
	auto& iter = find_if(lstUnit.begin(), lstUnit.end(), [&](auto& _pObj) {
		return _pObj->GetControlFucus();
	});
	if (iter != lstUnit.end())
	{
		if (m_bCameraFocus)
			m_pScrollMgr->SetTarget(ENUM::Target::FOCUS, *iter);
		else
			m_pScrollMgr->SetTarget(ENUM::Target::FOCUS, nullptr);
	}
}

void CControlMgr::SetTarget(CGameObject * _pObj)
{
	CObserver* pObj = GetTarget();
	if (pObj)
	{
		static_cast<CGameObject*>(pObj)->SetControlFucus(false);
	}
	m_pTarget->SetTarget(ENUM::Target::FOCUS, _pObj);
	if (_pObj)
		_pObj->SetControlFucus(true);
}

CObserver * CControlMgr::GetTarget()
{
	return m_pTarget->GetTarget(ENUM::Target::FOCUS);
}

void CControlMgr::AddCloseTarget(CObserver * _pCloseTarget)
{
	m_lstCloseTargetAstar.emplace_back(_pCloseTarget);
}

bool CControlMgr::IsPassTarget(CObserver * _pCloseTarget)
{
	auto& iter_target = find_if(m_lstCloseTargetAstar.begin(), m_lstCloseTargetAstar.end(), [&](auto& pTarget)
	{
		return (_pCloseTarget == pTarget);
	});
	if (iter_target == m_lstCloseTargetAstar.end())
		return true;
	return false;
}
