#include "stdafx.h"
#include "BattleField.h"
#include "Terrain.h"
#include "Archer.h"
#include "Bavarian.h"
#include "Andariel.h"
#include "Duriel.h"
#include "Dia.h"
#include "Izual.h"
#include "Barlog.h"
#include "ArrangementMgr.h"

#include "GameObject.h"

#include "LeadershipMgr.h"
#include "Tile.h"

#include "Vs.h"

#include "WorldMap.h"
#include "Trait.h"

#include "Victory.h"

IMPLEMENT_CREATE_BASE(CBattleField)
CBattleField::CBattleField()
	:m_iReadyCount(8)
	, m_iEffect(false)
{
}

CBattleField::~CBattleField()
{
	Release();
}

HRESULT CBattleField::Initialize()
{
	//CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNELID::BGM);
	CSoundMgr::GetInstance()->StopAll();
	CSoundMgr::GetInstance()->PlayBGM(L"Battle.mp3");
	CControlMgr::GetInstance()->SetControlState(ENUM::ControlState::NONE);
	m_pObjMgr->InitNextScene();

	CArrangementMgr::GetInstance()->SetMode(CArrangementMgr::Mode::ARRANGE);
	CControlMgr::GetInstance()->SetTarget(nullptr);
	m_pScrollMgr->InitScroll(100.f, 100.f);
	CTerrain* pTerrain = CTerrain::Create();
	pTerrain->SetBattleState(ENUM::BattleState::READY);

	m_pObjMgr->AddObject(ENUM::MapType::TERRAIN, pTerrain);
	pTerrain->LoadData(L"../Data/Map1.dat");
	m_pScrollMgr->Initialize(pTerrain);// , pObj);

	CLeadershipMgr::GetInstance()->GetLeaderObject();

	auto& lstObj = m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT);
	for (auto& pObj : lstObj)
	{
		pObj->SetCollisionLand(true);
	}

	SetDelayTime(ENUM::LiveTime::BASE, 1000);

	CTrait* pTrait = CTrait::Create(100, 100);
	CObjMgr::GetInstance()->AddObject(ENUM::UIType::TRAIT, pTrait);
	return S_OK;
}

void CBattleField::Release()
{
}

int CBattleField::Update()
{
	CObserver::LiveTime();
	CControlMgr::GetInstance()->Update();
	m_pObjMgr->Update();
	m_pScrollMgr->Update();

	if (CObserver::IsActivateTime(ENUM::LiveTime::BASE))
	{
		m_iReadyCount -= 1;
		if (m_iReadyCount < 0)
		{
			CLeadershipMgr::GetInstance()->UpdateFieldData();
			SetDelayTime(ENUM::LiveTime::BASE, 0);
			auto pTerrain = CObjMgr::GetInstance()->GetTerrain();
			pTerrain->SetBattleState(ENUM::BattleState::NORMAL);
			//pTerrain->SetBattleState(ENUM::BattleState::NONE);
			CArrangementMgr::GetInstance()->SetMode(CArrangementMgr::Mode::NORMAL);
			auto& lstUnit = m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT);
			auto& lstTile = pTerrain->GetTileList(ENUM::Tile::ALLY_STACK);
			for (auto& pUnit : lstUnit)
			{
				pUnit->SetSelect(false);
				for (auto& pTile : lstTile)
				{
					if (pTile->IsPicking(pUnit->GetPos()))
					{
						pUnit->SetEvent(ENUM::Event::DEAD);
					}
				}
			}
		}
		else
			CSoundMgr::GetInstance()->MyPlaySound(L"말.wav", CSoundMgr::CHANNELID::EFFECT);
	}
	return 0;
}

void CBattleField::LateUpdate()
{
	m_pObjMgr->LateUpdate();
	m_pScrollMgr->LateUpdate();

	//CCollisionMgr::CollisionRectEx(m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT),
	//	m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT));

	CCollisionMgr::CollisionRect(m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT),
		m_pObjMgr->GetObjectList(ENUM::ObjType::SKILL));

	CCollisionMgr::TargetUnit(m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT), 5000);

	CheckVictory();
}

void CBattleField::Render()
{
	static WCHAR szReadyCount[MID_STR];
	static RECT	 rtScreen = FUNC::GET::Rect(D3DXVECTOR3(WINCX*0.5f, 100.f, 0.f),
		D3DXVECTOR3(WINCX, 60.f, 0.f));

	m_pDeviceMgr->DrawImage(m_tDraw);
	m_pObjMgr->Render();
	CControlMgr::GetInstance()->Rander();
	m_pScrollMgr->Update();

	if (-1 < m_iReadyCount)//준비 시간
	{
		wsprintf(szReadyCount, L"준비 : %d", m_iReadyCount);
		m_pDeviceMgr->DrawString(szReadyCount, lstrlen(szReadyCount), &rtScreen, 5UL, INIT_COLOR_IVORY, ENUM::FONT::FONT48);
	}
}

void CBattleField::CheckVictory()
{
	if (m_iEffect)
	{
		if (!GetTarget(ENUM::Target::FOCUS))
		{
			m_pSceneMgr->SceneChange(ENUM::Scene::WORLDMAP);
		}
		return;
	}

	bool bSurvive_Alley = false;
	bool bSurvive_Enemy = false;
	auto& lstUnit = m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT);
	for (auto& pObj : lstUnit)
	{
		if (ENUM::Team::ONE == pObj->GetTeam())
		{
			bSurvive_Alley = true;
		}
		else
		{
			bSurvive_Enemy = true;
		}
	}
	if (bSurvive_Alley && !bSurvive_Enemy)
	{
		m_iEffect = true;
		//승리!
		CGameObject* pObj = CLeadershipMgr::GetInstance()->GetRedLeader();
		if (pObj)
			pObj->SetEvent(ENUM::Event::DEAD);

		CVictory* pVictory = CVictory::Create();
		SetTarget(ENUM::Target::FOCUS, pVictory);
		m_pObjMgr->AddObject(ENUM::UIType::INFO, pVictory);

		//m_pSceneMgr->SceneChange(ENUM::Scene::WORLDMAP);
	}
	else if (!bSurvive_Alley && bSurvive_Enemy)
	{
		m_iEffect = true;
		//패배!
		CWorldMap::SetInit(false);
		//m_pSceneMgr->SceneChange(ENUM::Scene::WORLDMAP);
		CVictory* pVictory = CVictory::Create();
		SetTarget(ENUM::Target::FOCUS, pVictory);
		pVictory->SetVictory(false);
		m_pObjMgr->AddObject(ENUM::UIType::INFO, pVictory);
	}
	else
	{
		//결판 안남
	}
}
