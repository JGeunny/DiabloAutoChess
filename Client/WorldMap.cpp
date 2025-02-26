#include "stdafx.h"
#include "WorldMap.h"
#include "Terrain.h"
#include "Archer.h"
#include "Bavarian.h"
#include "Andariel.h"
#include "Duriel.h"
#include "Dia.h"
#include "Izual.h"
#include "Barlog.h"

#include "LeadershipMgr.h"
#include "ControlMgr.h"

#include "Cow.h"

#include "Inven.h"
#include "Store.h"

bool CWorldMap::m_bInit = false;
IMPLEMENT_CREATE_BASE(CWorldMap)
CWorldMap::CWorldMap()
{
}

CWorldMap::~CWorldMap()
{
	Release();
}

HRESULT CWorldMap::Initialize()
{
	//CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNELID::BGM);
	CSoundMgr::GetInstance()->StopAll();
	CSoundMgr::GetInstance()->PlayBGM(L"Loading.wav");
	CControlMgr::GetInstance()->SetControlState(ENUM::ControlState::NOATTACK);
	if (!m_bInit)
	{
		m_bInit = true;
		m_pObjMgr->InitNextScene();

		CTerrain* pTerrain = CTerrain::Create();
		m_pObjMgr->AddObject(ENUM::MapType::TERRAIN, pTerrain);
		pTerrain->LoadData(L"../Data/Map0.dat");

		CInven* pInven = CInven::Create(WINCX*0.5f + 150, WINCY*0.5f);
		CObjMgr::GetInstance()->AddObject(ENUM::UIType::INFO, pInven);
		pInven->SetActivate(false);
		CStore* pStore = CStore::Create(WINCX*0.5f - 150, WINCY*0.5f);
		CObjMgr::GetInstance()->AddObject(ENUM::UIType::INFO, pStore);
		pStore->SetActivate(false);

		CCow* pCow = CCow::Create(1300, 1200);
		pCow->SetTarget(ENUM::Target::FOCUS, pInven);
		pCow->SetTarget(ENUM::Target::PARENT, pStore);
		pCow->SetTeam(ENUM::Team::NONE);
		m_pObjMgr->AddObject(ENUM::ObjType::UNIT, pCow);
		m_pScrollMgr->Initialize(pTerrain);// , pObj);


		//pTerrain->SetBattleState(ENUM::BattleState::NONE);
		CControlMgr::GetInstance()->CameraFocus();
		CControlMgr::GetInstance()->ChangeTarget();

		auto& lstObj = m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT);
		for (auto& pObj : lstObj)
		{
			pObj->SetCollisionLand(false);
			pObj->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.f));
			CLeadershipMgr::GetInstance()->AddObject(pObj, pObj);
			RZIMAGE::ID eClassId = (RZIMAGE::ID)pObj->GetClassId();
			CGameObject* pCreateObj;
			switch (eClassId)
			{
			case RZIMAGE::BASE:
				break;
			case RZIMAGE::BACKGROUND:
				break;
			case RZIMAGE::MAP:
				break;
			case RZIMAGE::TILE:
				break;
			case RZIMAGE::AMAZONE:
				break;
			case RZIMAGE::ANDARIEL:
				for (int i = 0; i < 2; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::ANDARIEL);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				for (int i = 0; i < 8; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::BARLOG);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				break;
			case RZIMAGE::DURIEL:
				for (int i = 0; i < 2; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::DURIEL);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				for (int i = 0; i < 5; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::BARLOG);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				for (int i = 0; i < 3; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::IZUAL);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				break;
			case RZIMAGE::DIA:
				for (int i = 0; i < 3; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::DIA);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				for (int i = 0; i < 2; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::ANDARIEL);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				for (int i = 0; i < 2; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::DURIEL);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				for (int i = 0; i < 5; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::IZUAL);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				break;
			case RZIMAGE::IZUAL:
				for (int i = 0; i < 3; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::BARLOG);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				for (int i = 0; i < 1; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::IZUAL);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				break;
			case RZIMAGE::BARLOG:
				for (int i = 0; i < 2; ++i)
				{
					pCreateObj = m_pObjMgr->CreateObject(RZIMAGE::BARLOG);
					pCreateObj->SetTeam(pObj->GetTeam());
					CLeadershipMgr::GetInstance()->AddObject(pObj, pCreateObj);
				}
				break;
			case RZIMAGE::SKILL:
				break;
			case RZIMAGE::BASEBUTTON:
				break;
			case RZIMAGE::BASEMOUSE:
				break;
			case RZIMAGE::END:
				break;
			default:
				break;
			}
		}

	}
	else
	{
		m_pObjMgr->InitNextScene();
		m_pObjMgr->LoadList();
		auto pTerrain = m_pObjMgr->GetTerrain();
		m_pScrollMgr->Initialize(pTerrain);
		auto& lstObj = m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT);
		for (auto& pObj : lstObj)
		{
			pObj->SetCollisionLand(false);
			pObj->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.f));
		}
		CControlMgr::GetInstance()->CameraFocus(true);
		CControlMgr::GetInstance()->ChangeTarget();
	}
	return S_OK;
}

void CWorldMap::Release()
{
}

int CWorldMap::Update()
{
	CControlMgr::GetInstance()->Update();
	m_pObjMgr->Update();
	m_pScrollMgr->Update();
	return 0;
}

void CWorldMap::LateUpdate()
{
	m_pObjMgr->LateUpdate();
	m_pScrollMgr->LateUpdate();
	
	if (!CCollisionMgr::CollisionGoToBattleField(m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT)))
	{
		CCollisionMgr::CollisionRect(m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT),
			m_pObjMgr->GetObjectList(ENUM::ObjType::SKILL));
		CCollisionMgr::TargetUnit(m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT));
	}

	//if (m_pKeyMgr->KeyDown(KEY::SPACE))
	//{
	//	m_pSceneMgr->SceneChange(ENUM::Scene::BATTLEFIELD);
	//}
	auto lstUnit = m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT);
	auto iter_unit = find_if(lstUnit.begin(), lstUnit.end(), [&](auto& pObj) {
		return (pObj->GetTeam() != ENUM::Team::ONE)
			&& (pObj->GetTeam() != ENUM::Team::NONE);
	});
	if (iter_unit == lstUnit.end())
	{
		m_bInit = false;
		m_pSceneMgr->SceneChange(ENUM::Scene::ENDING);
	}
}

void CWorldMap::Render()
{
	m_pDeviceMgr->DrawImage(m_tDraw);
	m_pObjMgr->Render();
	CControlMgr::GetInstance()->Rander();
	m_pScrollMgr->Update();
}