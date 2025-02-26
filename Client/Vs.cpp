#include "stdafx.h"
#include "Vs.h"
#include "GameObject.h"
#include "ArrangementMgr.h"

IMPLEMENT_CREATE_BASE(CVs)
CVs::CVs()
{
}


CVs::~CVs()
{
	Release();
}

HRESULT CVs::Initialize()
{
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNELID::BGM);
	CSoundMgr::GetInstance()->PlayBGM(L"vs.mp3");
	m_pTarget = CObserver::Create();
	LoadGameImage();
	//m_pTextureMgr->LoadTexture(L"Effect|Vs", L"../Image/Effect/Vs/Vs.png");
	m_tDraw.vPos = { WINCX * 0.5f, WINCY*0.5f, 0.f };
	m_tDraw.vSize = { WINCX, WINCY, 0.f };
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(L"Effect|Vs", 0));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	SetDelayTime(ENUM::LiveTime::LIVE, 3000);
	return S_OK;
}

void CVs::Release()
{
	ClearTarget();
	SafeDelete(m_pTarget);
}

int CVs::Update()
{
	CObserver::LiveTime();
	if(ENUM::Event::DEAD == m_eEvent)
		return (int)m_eEvent;
	CGameImage* pBlueTeam = static_cast<CGameImage*>(m_pTarget->GetTarget(ENUM::Target::FOCUS));
	CGameImage* pRedTeam = static_cast<CGameImage*>(m_pTarget->GetTarget(ENUM::Target::ENEMY));

	if (pBlueTeam)
	{
		auto& vPos = pBlueTeam->GetPos();
		vPos.x += 5;
		vPos.y = WINCY*0.7f;
		if (vPos.x > WINCX*0.3f)
			vPos.x = WINCX*0.3f;
	}
	if (pRedTeam)
	{
		auto& vPos = pRedTeam->GetPos();
		vPos.x -= 5;
		vPos.y = WINCY*0.7f;
		if (vPos.x < WINCX*0.7f)
			vPos.x = WINCX*0.7f;
	}
	return (int)m_eEvent;
}

void CVs::LateUpdate()
{
}

void CVs::Render()
{
	m_pDeviceMgr->DrawImage(m_tDraw);
	CGameImage* pBlueTeam = static_cast<CGameImage*>(m_pTarget->GetTarget(ENUM::Target::FOCUS));
	CGameImage* pRedTeam = static_cast<CGameImage*>(m_pTarget->GetTarget(ENUM::Target::ENEMY));
	if (pBlueTeam)
	{
		pBlueTeam->Render();
	}
	if (pRedTeam)
	{
		pRedTeam->Render();
	}
}

void CVs::InitTarget(CGameObject * _pBlueTeam, CGameObject * _pRedTeam)
{
	ClearTarget();
	m_pTarget->SetTarget(ENUM::Target::FOCUS, _pBlueTeam);
	m_pTarget->SetTarget(ENUM::Target::ENEMY, _pRedTeam);
	if (_pBlueTeam)
	{
		m_vBluePos = _pBlueTeam->GetPos();
		_pBlueTeam->SetPos(D3DXVECTOR3(WINCX * 0.f, WINCY*0.75f, 0.f));
		_pBlueTeam->SetScale(D3DXVECTOR3(2.f, 2.f, 2.f));
		_pBlueTeam->SetAngle(270.f);
		_pBlueTeam->SetState(ENUM::State::IDLE);
		_pBlueTeam->FSM();
	}
	if (_pRedTeam)
	{
		m_vRedPos = _pRedTeam->GetPos();
		_pRedTeam->SetPos(D3DXVECTOR3(WINCX * 1.f, WINCY*0.75f, 0.f));
		_pRedTeam->SetScale(D3DXVECTOR3( 2.f, 2.f, 2.f ));
		_pRedTeam->SetAngle(270.f);
		_pRedTeam->SetState(ENUM::State::IDLE);
		_pRedTeam->FSM();
	}
	CControlMgr::GetInstance()->SetTarget(nullptr);
	CArrangementMgr::GetInstance()->SetMode(CArrangementMgr::Mode::ARRANGE);
}

void CVs::ClearTarget()
{
	CGameImage* pBlueTeam = static_cast<CGameImage*>(m_pTarget->GetTarget(ENUM::Target::FOCUS));
	CGameImage* pRedTeam = static_cast<CGameImage*>(m_pTarget->GetTarget(ENUM::Target::ENEMY));
	if (pBlueTeam)
	{
		pBlueTeam->SetPos(m_vBluePos);
		pBlueTeam->SetScale(D3DXVECTOR3( 1.f, 1.f, 1.f ));
	}
	if (pRedTeam)
	{
		pRedTeam->SetPos(m_vRedPos);
		pRedTeam->SetScale(D3DXVECTOR3( 1.f, 1.f, 1.f ));
	}
	m_pTarget->ClearTarget(ENUM::Target::FOCUS);
	m_pTarget->ClearTarget(ENUM::Target::ENEMY);
}

void CVs::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"Effect|Vs", L"../Image/Effect/Vs/Vs.png");
}