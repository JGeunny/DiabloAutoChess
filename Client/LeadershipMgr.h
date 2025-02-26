#pragma once

class CObserver;
class CTile;
class CLeadershipMgr
{
	DECLARE_SINGLETON(CLeadershipMgr)
private:
	explicit CLeadershipMgr();
public:
	virtual ~CLeadershipMgr();

private:
	HRESULT Initialize();
	void	Release();

public:
	int Update();
	void LateUpdate();

	void Render();

private:
	void ExecuteGotoBattleField();

public:
	void GetLeaderObject();

public:
	void UpdateFieldData();

public:
	HRESULT AddObject(CGameObject* _pLeader, CGameObject* _pObj);
	HRESULT	GoToBattleField(int _iMap, CGameObject* _pLeader1, CGameObject* _pLeader2);

	std::list<CTile*>	GetTileList(ENUM::Tile _eTileType);

public:
	CGameObject* GetBlueLeader();
	CGameObject* GetRedLeader();

public:
	CGameObject*				GetAllyLeader();
	std::list<CGameObject*>*	GetAllyLeaderList();

private:
	std::unordered_map<CGameObject*, std::list<CGameObject*>> m_mapLeadership;
	CObserver*		m_pTargetVs;
	bool			m_bGotoBattleField;

	std::list<CGameObject*>* m_pBlueTeamList;
	std::list<CGameObject*>* m_pRedTeamList;
	CObserver*		m_pBlueLeader;
	CObserver*		m_pRedLeader;

	CGameObject*	m_pAllyLeader;
};			  

