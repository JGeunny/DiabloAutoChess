#include "stdafx.h"
//#include "../../Client/stdafx.h"
#include "Astar.h"
#include "Terrain.h"
#include "Tile.h"

IMPLEMENT_CREATE_BASE(CAstar)
CAstar::CAstar()
	:m_iStartIndex(-1)
{
}

CAstar::~CAstar()
{
	Release();
}

bool CAstar::Initialize()
{
	return true;
}

int CAstar::Update(float _fDelTime)
{
	return 0;
}

void CAstar::LateUpdate()
{
}

void CAstar::Render()
{
}

void CAstar::Release()
{
	m_BestPath.clear();
}


void CAstar::StartAstar(D3DXVECTOR3 _vStartPoint, D3DXVECTOR3 _vGoalPoint)
{
	m_pTerrain = dynamic_cast<CTerrain*>(
		CObjMgr::GetInstance()->GetObjectList(ENUM::MapType::TERRAIN).front());
	NULL_CHECK(m_pTerrain);

	auto& vecTile = m_pTerrain->GetTileVec();

	int iStartIndex = m_pTerrain->GetTileIndex(_vStartPoint);
	int iGoalIndex = m_pTerrain->GetTileIndex(_vGoalPoint);

	m_iStartIndex = iStartIndex;
	if (-1 == iStartIndex || -1 == iGoalIndex)
		return;

	// 목적지와 출발지가 같다면
	if (iStartIndex == iGoalIndex)
		return;

	// 목적지가 갈 수 없는 곳이라면 
	if (ENUM::Tile::BLOCK == vecTile[iGoalIndex]->GetTileInfo().eTileID)
		return;

	//초기화
	m_OpenLst.clear();
	m_CloseLst.clear();

	//갈수없는 유닛이 올라가 있는곳 등록
	for (int i = 0; i < (int)vecTile.size(); ++i)
	{
		if (iGoalIndex == i) continue;
		if (vecTile[i]->GetExistUnitOnTile())
		{
			m_CloseLst.emplace_back(i);
		}
	}

	for (auto& pTile : vecTile)
	{
		pTile->GetTileInfo().iParentIndex = 0;
	}
	if (true == FindPath(iStartIndex, iGoalIndex))
		MakePath(iStartIndex, iGoalIndex);
}

bool CAstar::FindPath(int _iStartIndex, int _iGoalIndex)
{
	auto& vecTile = m_pTerrain->GetTileVec();
	auto& vecGraph = m_pTerrain->GetTileGraphVec();

	if (!m_OpenLst.empty())
		m_OpenLst.pop_front(); // Queue

	m_CloseLst.push_back(_iStartIndex);

	for (auto& pTile : vecGraph[_iStartIndex])
	{
		auto& tTileInfo = pTile->GetTileInfo();
		// 인접한 타일이 목적지라면 true (탐색 종료)
		if (tTileInfo.iIndex == _iGoalIndex)
		{
			tTileInfo.iParentIndex = _iStartIndex;
			return true;
		}
		
		// 인접타일이 open과 close에 존재하지 않는다면 open에 넣는다.
		if (false == FindIndexInList(m_OpenLst, tTileInfo.iIndex)
			&& false == FindIndexInList(m_CloseLst, tTileInfo.iIndex))
		{
			tTileInfo.iParentIndex = _iStartIndex;
   			m_OpenLst.emplace_back(tTileInfo.iIndex);
		}
	}

	// 더이상 탐색할 수 없다면 false (탐색 종료)
	if (m_OpenLst.empty())
	{
		return false;
	}

	auto& vStartPos = vecTile[m_iStartIndex]->GetDrawInfo().vPos;
	auto& vGoalPos = vecTile[_iGoalIndex]->GetDrawInfo().vPos;
	D3DXVECTOR3 vCurPos = {};
	float fHeuristics[2] = {};
	// 휴리스틱 비용 조사 후 OpenLst 정렬
	// 휴리스틱 = 출발지와의 거리 + 도착지와의 거리

	m_OpenLst.sort([&](auto& iPrevIndex, auto& iNextIndex)
	{
		vCurPos = vecTile[iPrevIndex]->GetDrawInfo().vPos;
		fHeuristics[0] = D3DXVec3Length(&(vCurPos - vStartPos)) + D3DXVec3Length(&(vGoalPos - vCurPos));
		vCurPos = vecTile[iNextIndex]->GetDrawInfo().vPos;
		fHeuristics[1] = D3DXVec3Length(&(vCurPos - vStartPos)) + D3DXVec3Length(&(vGoalPos - vCurPos));
		return fHeuristics[0] < fHeuristics[1];
	});

	// 재귀
	return FindPath(m_OpenLst.front(), _iGoalIndex);
}

void CAstar::MakePath(int _iStartIndex, int _iGoalIndex)
{
	//초기화
	m_BestPath.clear();

	if (-1 == _iStartIndex || -1 == _iGoalIndex)
		return;

	auto& vecTile = m_pTerrain->GetTileVec();

	int index = _iGoalIndex;
	while (_iStartIndex != index)
	{
		m_BestPath.emplace_front(vecTile[index]);
		index = vecTile[index]->GetTileInfo().iParentIndex;
	}
}

bool CAstar::FindIndexInList(std::list<int>& _CurList, int _iIndex)
{
	// <algorithm>에서 제공.
	auto iter_find = find(_CurList.begin(), _CurList.end(), _iIndex);

	if (_CurList.end() == iter_find)
		return false;

	// 존재한다면 true
	return true;
}
