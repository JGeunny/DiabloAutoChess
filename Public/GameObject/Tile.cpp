#include "stdafx.h"
//#include "../../Client/stdafx.h"
#include "Tile.h"

CTile::CTile()
	: m_fLineWidth(1.2f)
	, m_bExistUnitOnTile(false)
{

}


CTile::~CTile()
{
	Release();
}

CTile * CTile::Create()
{
	CTile* pInstance = new CTile;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

HRESULT CTile::Initialize()
{
	m_tDraw.vSize.x = float(TILECX);
	m_tDraw.vSize.y = float(TILECY);
	//m_vecTile[i]->AlterDraw().SetTexInfo(m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", TEXTURE::MULTI, m_vecTile[i]->AlterImageID()));
	//m_pTextureMgr->LoadTexture(L"Area", L"Tile", L"../Image/Area/Tile/Tile.png", TEXTURE::SINGLE, 1, 1, INIT_COLOR_PNG);
	lstrcpy(m_szFrameKey, L"Tile");
	
	//m_vecTexture.emplace_back(m_pTextureMgr->GetTexture(m_szFrameKey));
	/*m_vecImage = new vector<vector<const TEXTURE_INFO*>>;
	vector<const TEXTURE_INFO*> vecImage;

	for (int i = 0; i < 38; ++i)
	{
		vecImage.emplace_back(m_pTextureMgr->GetTexInfo(TEXTURE::MULTI, L"Terrain", m_pFrameKey, i));
	}
	m_vecImage->emplace_back(vecImage);*/


	return S_OK;
}

int CTile::Update()
{
	if (ENUM::Event::DEAD == m_eEvent)
		return (int)m_eEvent;

	m_tTile.color = GetColor(m_tTile.eTileID);
	return (int)m_eEvent;
}

void CTile::LateUpdate()
{
}

void CTile::Render()
{
	if (m_bExistUnitOnTile)
		m_tTile.color = INIT_COLOR_RED;
	if (m_tTile.iImageID != -1)
	{
		m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::TILE, 0, m_tTile.iImageID));
		m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();
		m_pDeviceMgr->DrawImage(m_tDraw);
	}	
	m_pDeviceMgr->DrawHexagon(m_tDraw.GetHexagon(1.5f), m_fLineWidth, m_tTile.color);
}

bool CTile::IsPicking(const D3DXVECTOR3 & _vPos)
{
	// 내적을 이용한 픽킹
	D3DXVECTOR3* pHexagon = m_tDraw.GetHexagon(0.f, false);

	// 상좌 상우 우 하우 하좌 좌 6개
	D3DXVECTOR3 vPoint[6] = {};
	memcpy(vPoint, pHexagon, sizeof(vPoint));

	// 시계방향으로 방향벡터 6개
	D3DXVECTOR3 vDir[6] = {};
	int iSize = FUNC::GET::UBound(vDir);
	for (int i = 0; i < iSize; ++i)
	{
		vDir[i] = vPoint[(i + 1) % iSize] - vPoint[i];
		D3DXVec3Normalize(&vDir[i], &vDir[i]);
	}
	// 법선 벡터 6개
	D3DXVECTOR3 vNormal[6] = {};
	iSize = FUNC::GET::UBound(vNormal);
	for (int i = 0; i < iSize; ++i)
	{
		D3DXVec3Cross(&vNormal[i], &vDir[i], &D3DXVECTOR3(0.f, 0.f, 1.f));
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
	}
	// 마우스방향으로 방향벡터 6개
	D3DXVECTOR3 vMouseDir[6] = {};
	iSize = FUNC::GET::UBound(vMouseDir);
	for (int i = 0; i < iSize; ++i)
	{
		vMouseDir[i] = _vPos - vPoint[i];
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
	}
	//마우스 방향 백터와 법선 백터를 내적 했을 경우 예각이 나오면 false
	for (int i = 0; i < iSize; ++i)
	{
		if (0 < D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
			return false;
	}
	return true;
}

void CTile::Release()
{
}

D3DCOLOR CTile::GetColor(ENUM::Tile _eTileID)
{
	static D3DCOLOR color;
	switch (_eTileID)
	{
	case ENUM::Tile::BLANK:
		color = INIT_COLOR_TILE;
		break;
	case ENUM::Tile::BLOCK:
		color = INIT_COLOR_RED;
		break;
	case ENUM::Tile::ALLY_STACK:
		color = D3DCOLOR_ARGB(255, 0, 0, 255);
		break;
	case ENUM::Tile::ALLY_FIELD:
		color = D3DCOLOR_ARGB(255, 0, 255, 0);
		break;
	case ENUM::Tile::ENEMY_FIELD:
		color = D3DCOLOR_ARGB(255, 255, 255, 0);
		break;
	case ENUM::Tile::END:
		break;
	default:
		break;
	}
	return color;
}
