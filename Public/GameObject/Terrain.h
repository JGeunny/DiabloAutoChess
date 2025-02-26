#pragma once
#include "GameImage.h"

class CVirtualObject;
class CTile;
class CTerrain
	:public CGameImage
{
private:
	explicit CTerrain();

public:
	virtual ~CTerrain();

public:
	void TileChange(
		D3DXVECTOR3& _vPos,
		int _iDrawID,
		ENUM::Tile _eTileID = ENUM::Tile::BLANK);

	void SetMiniView(bool _bMiniView) {
		m_bMiniView = _bMiniView;
	}

protected:
	virtual HRESULT	Initialize();
	virtual void	Release();

public:
	virtual int		Update();
	virtual void	LateUpdate();
	virtual void	Render();

	virtual void	ReleaseObj();
	virtual void	ReleaseTile();
	virtual void	InitObjState();

public:
	virtual HRESULT CreateTile(int _iTileX, int _iTileY, int _iTileCX, int _iTileCY);

public:
	void			SetTileX(int _iTileX) { m_iTileX = _iTileX; }
	void			SetTileY(int _iTileY) { m_iTileY = _iTileY; }
	void			SetTileCX(int _iTileCX) { m_iTileCX = _iTileCX; }
	void			SetTileCY(int _iTileCY) { m_iTileCY = _iTileCY; }
	void			SetMapImageID(int _iMapImageId) { m_tFrame.iFrameKey = _iMapImageId;}
public:	
	std::vector<CTile*>& GetTileVec() { return m_vecTile; }
	std::vector<CVirtualObject*>&  GetVirtualObjVec() { return m_vecVirtualObj; }

	int&			GetTileX() { return m_iTileX; }
	int&			GetTileY() { return m_iTileY; }
	int&			GetTileCX() { return m_iTileCX; }
	int&			GetTileCY() { return m_iTileCY; }
	int				GetMapCX(){	return int((m_iTileX - 0.5) * m_iTileCX); }
	int				GetMapCY(){return int((m_iTileY - 1) * m_iTileCY * 0.75); }

	std::vector<std::list<CTile*>>& GetTileGraphVec() { return m_vecGraph; }

public:
	std::list<CTile*>	GetTileList(ENUM::Tile _eTileType);

public:
	void ObjFollowMouse(D3DXVECTOR3 _vPos);
	int GetObjIndex(D3DXVECTOR3& _vPos);
	int GetTileIndex(D3DXVECTOR3& _vPos);

	CTile* GetTileInVec(D3DXVECTOR3 _vMousePos);

public:
	HRESULT	SaveData(const TCHAR * pFilePath);
	HRESULT	LoadData(const TCHAR * pFilePath);

	HRESULT	SaveTile(const TCHAR * pFilePath);
	HRESULT	LoadTile(const TCHAR * pFilePath);

	HRESULT	SaveObj(const TCHAR * pFilePath);
	HRESULT	LoadObj(const TCHAR * pFilePath);

public:
	void	UpdateExistUnitOnTile();
public:
	bool	IsGoable(D3DXVECTOR3 _vPos);

public:
	void	SetBattleState(ENUM::BattleState _eBattleState) { m_eBattleState = _eBattleState; }

public:
	ENUM::BattleState&	GetBattleState() { return m_eBattleState; }

public:
	void SettingGraph();

public:
	bool AddObject(CVirtualObject* _Obj);

public:
	static CTerrain* Create();

private:
	int							m_iTileX;
	int							m_iTileY;
	int							m_iTileCX;
	int							m_iTileCY;
	std::vector<CTile*>			m_vecTile;
	std::vector<CVirtualObject*> m_vecVirtualObj;
	bool						m_bMiniView;

private:
	std::vector<std::list<CTile*>>m_vecGraph;

private:
	ENUM::BattleState m_eBattleState;//화면 상태에 따른 타일 보여줄지 말지 결정
};

