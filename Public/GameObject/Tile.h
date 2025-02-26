#pragma once
#include "GameImage.h"

class CTile :
	public CGameImage
{
private:
	explicit CTile();
public:
	virtual ~CTile();

public:
	static CTile* Create();

protected:
	virtual HRESULT		Initialize();
	//virtual void		LateInit();
	virtual void		Release();

public:
	virtual int			Update();
	virtual void		LateUpdate();
	virtual void		Render();

public:
	bool IsPicking(const D3DXVECTOR3& _vPos);

public:
	void		SetLineWidth(float _fLineWidth) { m_fLineWidth = _fLineWidth; }
	void		SetExistUnitOnTile(bool _bExistUnitOnTile) { m_bExistUnitOnTile = _bExistUnitOnTile; }

public:
	static D3DCOLOR GetColor(ENUM::Tile _eTileID);

public:
	TILE_INFO&  GetTileInfo() { return m_tTile; }
	ENUM::Tile	GetTileID() { return m_tTile.eTileID; }

	bool		GetExistUnitOnTile() { return m_bExistUnitOnTile; }

protected:
	TILE_INFO	m_tTile;
	float		m_fLineWidth;

	bool		m_bExistUnitOnTile;
};

