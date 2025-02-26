#pragma once

#include "Observer.h"
class CTerrain;
class CTile;
class CAstar
	: public CObserver
{
	DECLARE_CREATE_BASE(CAstar)
public:
	bool Initialize();
	virtual int Update(float _fDelTime);
	void LateUpdate();
	void Render();
	void Release();	

public:
	void StartAstar(D3DXVECTOR3 _vStartPoint, D3DXVECTOR3 _vGoalPoint);
	std::list<CTile*>& GetListPath() { return m_BestPath; }
protected:
	bool FindPath(int _iStartIndex, int _iGoalIndex);
	void MakePath(int _iStartIndex, int _iGoalIndex);

protected:
	bool FindIndexInList(std::list<int>& _CurList, int _iIndex);

private:
	std::list<int>		m_OpenLst;
	std::list<int>		m_CloseLst;
	std::list<CTile*>	m_BestPath;

	CTerrain*			m_pTerrain;

	int					m_iStartIndex;
};

