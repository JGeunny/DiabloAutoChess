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

	// �������� ������� ���ٸ�
	if (iStartIndex == iGoalIndex)
		return;

	// �������� �� �� ���� ���̶�� 
	if (ENUM::Tile::BLOCK == vecTile[iGoalIndex]->GetTileInfo().eTileID)
		return;

	//�ʱ�ȭ
	m_OpenLst.clear();
	m_CloseLst.clear();

	//�������� ������ �ö� �ִ°� ���
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
		// ������ Ÿ���� ��������� true (Ž�� ����)
		if (tTileInfo.iIndex == _iGoalIndex)
		{
			tTileInfo.iParentIndex = _iStartIndex;
			return true;
		}
		
		// ����Ÿ���� open�� close�� �������� �ʴ´ٸ� open�� �ִ´�.
		if (false == FindIndexInList(m_OpenLst, tTileInfo.iIndex)
			&& false == FindIndexInList(m_CloseLst, tTileInfo.iIndex))
		{
			tTileInfo.iParentIndex = _iStartIndex;
   			m_OpenLst.emplace_back(tTileInfo.iIndex);
		}
	}

	// ���̻� Ž���� �� ���ٸ� false (Ž�� ����)
	if (m_OpenLst.empty())
	{
		return false;
	}

	auto& vStartPos = vecTile[m_iStartIndex]->GetDrawInfo().vPos;
	auto& vGoalPos = vecTile[_iGoalIndex]->GetDrawInfo().vPos;
	D3DXVECTOR3 vCurPos = {};
	float fHeuristics[2] = {};
	// �޸���ƽ ��� ���� �� OpenLst ����
	// �޸���ƽ = ��������� �Ÿ� + ���������� �Ÿ�

	m_OpenLst.sort([&](auto& iPrevIndex, auto& iNextIndex)
	{
		vCurPos = vecTile[iPrevIndex]->GetDrawInfo().vPos;
		fHeuristics[0] = D3DXVec3Length(&(vCurPos - vStartPos)) + D3DXVec3Length(&(vGoalPos - vCurPos));
		vCurPos = vecTile[iNextIndex]->GetDrawInfo().vPos;
		fHeuristics[1] = D3DXVec3Length(&(vCurPos - vStartPos)) + D3DXVec3Length(&(vGoalPos - vCurPos));
		return fHeuristics[0] < fHeuristics[1];
	});

	// ���
	return FindPath(m_OpenLst.front(), _iGoalIndex);
}

void CAstar::MakePath(int _iStartIndex, int _iGoalIndex)
{
	//�ʱ�ȭ
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
	// <algorithm>���� ����.
	auto iter_find = find(_CurList.begin(), _CurList.end(), _iIndex);

	if (_CurList.end() == iter_find)
		return false;

	// �����Ѵٸ� true
	return true;
}
