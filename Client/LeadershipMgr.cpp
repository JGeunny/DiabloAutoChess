#include "stdafx.h"
#include "LeadershipMgr.h"
//#include "Observer.h"
#include "GameObject.h"
#include "Vs.h"
#include "Terrain.h"
#include "Tile.h"

#include "Trait.h"
#include "TraitCard.h"

IMPLEMENT_SINGLETON(CLeadershipMgr)
CLeadershipMgr::CLeadershipMgr()
	:m_bGotoBattleField(false)
	, m_pBlueTeamList(nullptr)
	, m_pRedTeamList(nullptr)
	, m_pAllyLeader(nullptr)
{
	Initialize();
}


CLeadershipMgr::~CLeadershipMgr()
{
	Release();
}

HRESULT CLeadershipMgr::Initialize()
{
	m_pTargetVs = CObserver::Create();
	m_pBlueLeader = CObserver::Create();
	m_pRedLeader = CObserver::Create();
	return S_OK;
}

void CLeadershipMgr::Release()
{
	SafeDelete(m_pTargetVs);
	SafeDelete(m_pBlueLeader);
	SafeDelete(m_pRedLeader);
	for (auto& pair : m_mapLeadership)
	{
		auto& lstObj = pair.second;
		for (auto& pObj : lstObj)
		{
			if (pair.first == pObj) continue;//리더 뺴고 나머지 다 정리
			SafeDelete(pObj);
		}
	}
}

int CLeadershipMgr::Update()
{
	return 0;
}

void CLeadershipMgr::LateUpdate()
{
	ExecuteGotoBattleField();
}

void CLeadershipMgr::Render()
{
}

void CLeadershipMgr::ExecuteGotoBattleField()
{
	auto pVs = m_pTargetVs->GetTarget(ENUM::Target::FOCUS);
	if (!pVs && m_bGotoBattleField)//대결이 이펙트가 끝났다면 배틀필드로 넘어가기
	{
		m_bGotoBattleField = false;
		CObjMgr::GetInstance()->BackupList();
		CSceneMgr::GetInstance()->SceneChange(ENUM::Scene::BATTLEFIELD);
	}
}

void CLeadershipMgr::GetLeaderObject()
{
	if (m_pBlueTeamList)
	{
		auto& lstTile = GetTileList(ENUM::Tile::ALLY_STACK);
		auto& iter = lstTile.begin();
		for (auto& pObj : *m_pBlueTeamList)
		{
			CGameObject* pThisObj = CObjMgr::GetInstance()->CreateObject((RZIMAGE::ID)pObj->GetClassId());
			if (!pThisObj) continue;
			pThisObj->GetDrawInfo().SetData(pObj->GetDrawInfo());
			pThisObj->GetStatusInfo().SetData(pObj->GetStatusInfo());
			pThisObj->SetLeadershipKey(pObj);
			CObjMgr::GetInstance()->AddObject(ENUM::ObjType::UNIT, pThisObj);

			if (pObj->GetBeOnTheLand())
			{
				pThisObj->SetPos(pObj->GetLandPos());
				pThisObj->SetLandPos(pObj->GetLandPos());
				pThisObj->SetBeOnTheLand(pObj->GetBeOnTheLand());
			}
			else
			{
				if (iter != lstTile.end())
				{
					auto vPos = (*iter)->GetPos();
					pThisObj->SetPos((*iter)->GetPos());
					++iter;
				}
				else
					break;
			}
		}
		m_pBlueTeamList = nullptr;
	}

	if (m_pRedTeamList)
	{
		auto& lstTile = GetTileList(ENUM::Tile::ENEMY_FIELD);
		FUNC::SORT::RandomList(lstTile);
		auto& iter = lstTile.begin();
		for (auto& pObj : *m_pRedTeamList)
		{
			CGameObject* pThisObj = CObjMgr::GetInstance()->CreateObject((RZIMAGE::ID)pObj->GetClassId());
			if (!pThisObj) continue;
			pThisObj->GetDrawInfo().SetData(pObj->GetDrawInfo());
			pThisObj->GetStatusInfo().SetData(pObj->GetStatusInfo());
			pThisObj->SetLeadershipKey(pObj);
			CObjMgr::GetInstance()->AddObject(ENUM::ObjType::UNIT, pThisObj);

			if (iter != lstTile.end())
			{
				auto vPos = (*iter)->GetPos();
				pThisObj->SetPos((*iter)->GetPos());
				++iter;
			}
			else
				break;
		}

		m_pRedTeamList = nullptr;
	}
}

void CLeadershipMgr::UpdateFieldData()
{
	bool bBuff_Knight = false, bBuff_Scout = false,
		bBuff_Wizard = false, bBuff_Assassin = false;

	//트레잇 업데이트
	auto pTraitList = CObjMgr::GetInstance()->GetObjectList(ENUM::UIType::TRAIT);
	if (pTraitList.size() > 0)
	{
		auto pTrait = static_cast<CTrait*>(pTraitList.front());
		auto& vecCradList = pTrait->GetTraitCardVec();
		for (auto& pCard : vecCradList)
		{
			switch (pCard->GetTrait())
			{
			case ENUM::Job::NONE:
				break;
			case ENUM::Job::KNIGHT:
				bBuff_Knight = pCard->IsBuff();
				break;
			case ENUM::Job::SCOUT:
				bBuff_Scout = pCard->IsBuff();
				break;
			case ENUM::Job::WIZARD:
				bBuff_Wizard = pCard->IsBuff();
				break;
			case ENUM::Job::ASSASSIN:
				bBuff_Assassin = pCard->IsBuff();
				break;
			case ENUM::Job::END:
				break;
			default:
				break;
			}
		}
	}


	auto pBlueLeader = GetBlueLeader();
	auto pRedLeader = GetRedLeader();
	if (!pBlueLeader) return;
	if (!pRedLeader) return;
	auto pairBlue = m_mapLeadership.find(pBlueLeader);
	auto pairRed = m_mapLeadership.find(pRedLeader);
	if (pairBlue == m_mapLeadership.end()) return;
	if (pairRed == m_mapLeadership.end()) return;

	auto& lstUnit = CObjMgr::GetInstance()->GetObjectList(ENUM::ObjType::UNIT);

	for (auto& pUnit : lstUnit)
	{
		for (auto& pBlueUnit : pairBlue->second)
		{
			if (pBlueUnit == pUnit->GetLeadershipKey())
			{
				pBlueUnit->SetBeOnTheLand(pUnit->GetBeOnTheLand());
				pBlueUnit->SetLandPos(pUnit->GetPos());

				switch (pBlueUnit->GetStatusInfo().eJob)
				{
				case ENUM::Job::NONE:
					break;
				case ENUM::Job::KNIGHT:
					pUnit->SetBuff(bBuff_Knight);
					if (bBuff_Knight)
					{
						pUnit->GetStatusInfo().iMaxHp += 500;
						pUnit->GetStatusInfo().FnRecoveryHp();
					}
					break;
				case ENUM::Job::SCOUT:
					pUnit->SetBuff(bBuff_Scout);
					if (bBuff_Scout)
						pUnit->GetStatusInfo().iAtt += 50;
					break;
				case ENUM::Job::WIZARD:
					pUnit->SetBuff(bBuff_Wizard);
					if (bBuff_Wizard)
						pUnit->GetStatusInfo().iMaxMp -= 50;
					break;
				case ENUM::Job::ASSASSIN:
					pUnit->SetBuff(bBuff_Assassin);
					if (bBuff_Knight)
					{
						pUnit->GetStatusInfo().iAtt += 20;
						pUnit->GetStatusInfo().iMaxMp -= 20;
					}
					break;
				case ENUM::Job::END:
					break;
				default:
					break;
				}
			}
		}
		for (auto& pRedUnit : pairRed->second)
		{
			if (pRedUnit == pUnit->GetLeadershipKey())
			{
				pRedUnit->SetBeOnTheLand(pUnit->GetBeOnTheLand());
				pRedUnit->SetLandPos(pUnit->GetPos());
			}
		}
	}
	
}

HRESULT CLeadershipMgr::AddObject(CGameObject * _pLeader, CGameObject * _pObj)
{
	if (!_pLeader) return S_FALSE;
	if (!_pObj) return S_FALSE;
	if(ENUM::Team::ONE == _pLeader->GetTeam())
		m_pAllyLeader = _pLeader;
	
	auto& iter = m_mapLeadership.find(_pLeader);
	if (iter == m_mapLeadership.end())
	{
		m_mapLeadership[_pLeader].emplace_back(_pObj);
	}
	else
	{
		auto& lstObj = m_mapLeadership[_pLeader];
		auto& iter_find_obj = find_if(lstObj.begin(), lstObj.end(), [&](auto& pObj) {
			return (pObj == _pObj);
		});
		if (iter_find_obj == lstObj.end())
			lstObj.emplace_back(_pObj);
	}	
	return S_OK;
}

HRESULT CLeadershipMgr::GoToBattleField(int _iMap, CGameObject * _pLeader1, CGameObject * _pLeader2)
{
	auto& iter_find_L1 = m_mapLeadership.find(_pLeader1);
	auto& iter_find_L2 = m_mapLeadership.find(_pLeader2);
	if (iter_find_L1 == m_mapLeadership.end()) return S_FALSE;
	if (iter_find_L2 == m_mapLeadership.end()) return S_FALSE;
	if (m_bGotoBattleField) return S_FALSE;
	m_pBlueLeader->SetTarget(ENUM::Target::FOCUS, _pLeader1);
	m_pRedLeader->SetTarget(ENUM::Target::FOCUS, _pLeader2);

	m_pBlueTeamList = &iter_find_L1->second;
	m_pRedTeamList = &iter_find_L2->second;

	CVs* pVs = CVs::Create();
	pVs->InitTarget(_pLeader1, _pLeader2);
	m_pTargetVs->SetTarget(ENUM::Target::FOCUS, pVs);

	CObjMgr::GetInstance()->AddObject(ENUM::UIType::SCENE, pVs);
	m_bGotoBattleField = true;
	return S_OK;
}

std::list<CTile*> CLeadershipMgr::GetTileList(ENUM::Tile _eTileType)
{
	return CObjMgr::GetInstance()->GetTerrain()->GetTileList(_eTileType);
}

CGameObject * CLeadershipMgr::GetBlueLeader()
{
	CObserver* pOsv = m_pBlueLeader->GetTarget(ENUM::Target::FOCUS);
	if (pOsv)
	{
		return static_cast<CGameObject*>(pOsv);
	}
	return nullptr;
}

CGameObject * CLeadershipMgr::GetRedLeader()
{
	CObserver* pOsv = m_pRedLeader->GetTarget(ENUM::Target::FOCUS);
	if (pOsv)
	{
		return static_cast<CGameObject*>(pOsv);
	}
	return nullptr;
}

CGameObject * CLeadershipMgr::GetAllyLeader()
{
	return m_pAllyLeader;
}

std::list<CGameObject*>* CLeadershipMgr::GetAllyLeaderList()
{
	auto& pairUnit = m_mapLeadership.find(m_pAllyLeader);
	if (pairUnit != m_mapLeadership.end())
		return &pairUnit->second;
	return nullptr;
}
