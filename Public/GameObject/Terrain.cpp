#include "stdafx.h"
//#include "../../Client/stdafx.h"
#include "Terrain.h"
#include "Tile.h"
#include "VirtualObject.h"

CTerrain::CTerrain()
	:m_bMiniView(false)
	, m_iTileX(0)
	, m_iTileY(0)
	, m_iTileCX(0)
	, m_iTileCY(0)
{
#ifdef CLIENT
	m_eBattleState = ENUM::BattleState::NORMAL;
#else	
	m_eBattleState = ENUM::BattleState::NONE;
#endif
}

CTerrain::~CTerrain()
{
	Release();
}

void CTerrain::TileChange(D3DXVECTOR3& _vPos, int _iDrawID, ENUM::Tile _eTileID)
{
	int iIndex = GetTileIndex(_vPos);

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	auto& tTileInfo = m_vecTile[iIndex]->GetTileInfo();
	tTileInfo.iImageID = _iDrawID;
	tTileInfo.eTileID = _eTileID;
}

HRESULT CTerrain::Initialize()
{
	//HRESULT hr = m_pTextureMgr->LoadTexture(L"Tile",
	//	L"../Image/Area/Terrain/Tile/Tile%d.png", 38);
	HRESULT hr = m_pTextureMgr->LoadTexture(L"Tile",
		L"../Image/Area/Terrain/settlerstiles/%d.png", 7);
	m_pTextureMgr->LoadTexture(L"Map|Boss", L"../Image/Area/Map/Boss.bmp");
	m_pTextureMgr->LoadTexture(L"Map|Dun1", L"../Image/Area/Map/Dun1.bmp");
	m_pTextureMgr->LoadTexture(L"Map|Dun2", L"../Image/Area/Map/Dun2.bmp");
	m_pTextureMgr->LoadTexture(L"Map|Field", L"../Image/Area/Map/Field.bmp");
	m_pTextureMgr->LoadTexture(L"Map|Store", L"../Image/Area/Map/Store.bmp");
	m_pTextureMgr->LoadTexture(L"Map|Town", L"../Image/Area/Map/Town.bmp");
	m_pTextureMgr->LoadTexture(L"Map|WorldMap", L"../Image/Area/Map/WorldMap.png");
	m_pTextureMgr->LoadTexture(L"Map|BattleField", L"../Image/Area/Map/BattleField.png");
	m_tFrame.iFrameKey = 0;
	//lstrcpy(m_szFrameKey, L"Map_Town");

	SetDelayTime(ENUM::LiveTime::BASE, 300);
	return CreateTile(TILEX, TILEY, TILECX, TILECY);
}

int CTerrain::Update()
{
	LiveTime();
	for (auto& pTile : m_vecTile)
	{
		pTile->Update();
		
	}
	for (auto& pVirtualObj : m_vecVirtualObj)
	{
		pVirtualObj->Update();
	}
	return 0;
}

void CTerrain::LateUpdate()
{
	for (auto& pTile : m_vecTile)
	{
		pTile->LateUpdate();

	}
	for (auto& pVirtualObj : m_vecVirtualObj)
	{
		pVirtualObj->LateUpdate();
	}

	if (IsActivateTime(ENUM::LiveTime::BASE))
	{
		UpdateExistUnitOnTile();
	}
}

void CTerrain::Render()
{
	FUNC::SORT::ObjectVec(m_vecVirtualObj, ENUM::OrderBy::DESC);
	TCHAR szIndex[MIN_STR] = L"";

	static D3DXVECTOR3 vPos, vScale, vPosBG, vSizeBG;

	vScale = { 1.f, 1.f, 1.f };
	vPosBG = m_tDraw.vPos;
	vSizeBG = m_tDraw.vSize;
	if (m_bMiniView)
	{
		vScale = { float(WINCX) / float(m_iTileCX*(m_iTileX - 1)), float(WINCY) / float(m_iTileCY*(m_iTileY - 1)) * 1.33f, 1.f };
		m_tDraw.vPos = { float(WINCX*0.5), float(WINCY*0.5), 0.f };
		m_tDraw.vSize = { (float)WINCX, (float)WINCY, 0.f };
	}
	else
	{	
		m_tDraw.vPos -= m_pScrollMgr->GetScroll();
	}

	if (-1 != m_tFrame.iFrameKey)
	{
		m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::MAP, m_tFrame.iFrameKey, 0));
		m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();
		m_pDeviceMgr->DrawImage(m_tDraw);
	}

	
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->SetScale(vScale);
		vPos = m_vecTile[i]->GetPos();
		auto& vCurPos = m_vecTile[i]->GetPos();
		m_vecTile[i]->SetPos(FUNC::GET::D3DXVec3Multiply(vCurPos, vScale));
		if(m_bMiniView)
			m_vecTile[i]->Render();
		else
		{
			switch (m_eBattleState)
			{
			case ENUM::BattleState::NONE:
				m_vecTile[i]->Render_Scroll();
				break;
			case ENUM::BattleState::NORMAL:
				break;
			case ENUM::BattleState::READY:
				if(ENUM::Tile::ALLY_STACK ==  m_vecTile[i]->GetTileID()
					|| ENUM::Tile::ALLY_FIELD == m_vecTile[i]->GetTileID())
					m_vecTile[i]->Render_Scroll();
				break;
			default:
				break;
			}
		}

		m_vecTile[i]->SetPos(vPos);
	}

	for (int i = (int)m_vecVirtualObj.size() - 1; i >= 0; --i)
	{
		m_vecVirtualObj[i]->SetScale(vScale);
		vPos = m_vecVirtualObj[i]->GetPos();
		m_vecVirtualObj[i]->SetPos(FUNC::GET::D3DXVec3Multiply(m_vecVirtualObj[i]->GetPos(), vScale));

		if (m_bMiniView)
			m_vecVirtualObj[i]->Render();
		else
			m_vecVirtualObj[i]->Render_Scroll();

		m_vecVirtualObj[i]->SetPos(vPos);
	}

	m_tDraw.vPos = vPosBG;
	m_tDraw.vSize = vSizeBG;
}


void CTerrain::Release()
{
	ReleaseObj();
	ReleaseTile();
}

void CTerrain::ReleaseObj()
{
	for (auto& pVirtualObj : m_vecVirtualObj)
		SafeDelete(pVirtualObj);
	m_vecVirtualObj.clear();
	m_vecVirtualObj.shrink_to_fit();
}

void CTerrain::ReleaseTile()
{
	for (auto& pTile : m_vecTile)
		SafeDelete(pTile);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTerrain::InitObjState()
{
	for (auto& pVirtualObj : m_vecVirtualObj)
	{
		pVirtualObj->SetSelect(false);
		pVirtualObj->SetImpossible(false);
	}
}
HRESULT CTerrain::CreateTile(int _iTileX, int _iTileY, int _iTileCX, int _iTileCY)
{
	Release();
	m_vecTile.reserve(_iTileX * _iTileY);

	CTile* pTile = nullptr;

	for (int i = 0; i < _iTileY; ++i)
	{
		for (int j = 0; j < _iTileX; ++j)
		{
			//육각형<세로>
			pTile = CTile::Create();
			auto& tDrawInfo = pTile->GetDrawInfo();
			tDrawInfo.vPos.x = j * _iTileCX + (i % 2) * (_iTileCX * 0.5f);
			tDrawInfo.vPos.y = i * (_iTileCY * 0.75f);
			tDrawInfo.vSize = { (float)_iTileCX, (float)_iTileCY, 0.f };
			auto& tTileInfo = pTile->GetTileInfo();
			tTileInfo.eTileID = ENUM::Tile::BLANK;
			tTileInfo.iImageID = -1;
			tTileInfo.iIndex = i *_iTileX + j;
			m_vecTile.emplace_back(pTile);
		}
	}
	m_iTileX = _iTileX;
	m_iTileY = _iTileY;
	m_iTileCX = _iTileCX;
	m_iTileCY = _iTileCY;

	m_tDraw.vPos = { float(GetMapCX()*0.5), float(GetMapCY()*0.5), 0.f };
	m_tDraw.vSize = { (float)GetMapCX(), (float)GetMapCY(), 0.f };

	SettingGraph();

	return S_OK;
}

int CTerrain::GetTileIndex(D3DXVECTOR3 & _vPos)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (m_vecTile[i]->IsPicking(_vPos))
			return (int)i;
	}
	return -1;
}

CTile * CTerrain::GetTileInVec(D3DXVECTOR3 _vMousePos)
{
	auto index = GetTileIndex(_vMousePos);
	if (-1 != index)
		return m_vecTile[index];
	else
		return nullptr;
}

std::list<CTile*> CTerrain::GetTileList(ENUM::Tile _eTileType)
{
	std::list<CTile*> lstTile;
	for (auto& pTile : m_vecTile)
	{
		if(pTile->GetTileID() == _eTileType)
			lstTile.emplace_back(pTile);
	}
	return lstTile;
}

void CTerrain::ObjFollowMouse(D3DXVECTOR3 _vPos)
{
	for (auto& pVirtualObj : m_vecVirtualObj)
	{
		if(pVirtualObj->GetSelect())
			pVirtualObj->SetPos(_vPos);
	}
}

int CTerrain::GetObjIndex(D3DXVECTOR3 & _vPos)
{
	for (size_t i = 0; i < m_vecVirtualObj.size(); ++i)
	{
		if (PtInRect(&m_vecVirtualObj[i]->GetDrawInfo().GetRect(), { (LONG)_vPos.x, (LONG)_vPos.y }))
		{
			return i;
		}
	}
	return -1;
}

HRESULT CTerrain::SaveData(const TCHAR * pFilePath)
{
	size_t i = 0;
	std::wstring strFilePath = pFilePath;
	if ((i = strFilePath.find(L'.', strFilePath.size() - 5)) != std::wstring::npos)
		strFilePath.replace(i, 1, L"_Terrain.");
	if (FAILED(SaveTile(strFilePath.c_str())))
		return S_FALSE;

	i = 0;
	strFilePath = pFilePath;
	if ((i = strFilePath.find(L'.', strFilePath.size() - 5)) != std::wstring::npos)
		strFilePath.replace(i, 1, L"_Obj.");
	if (FAILED(SaveObj(strFilePath.c_str())))
		return S_FALSE;
	return S_OK;
}

HRESULT CTerrain::LoadData(const TCHAR * pFilePath)
{
	size_t i = 0;
	std::wstring strFilePath = pFilePath;

	if ((i = strFilePath.find(L'.', strFilePath.size() - 5)) != std::wstring::npos)
		strFilePath.replace(i, 1, L"_Terrain.");
	if (FAILED(LoadTile(strFilePath.c_str())))
		return S_FALSE;

	i = 0;
	strFilePath = pFilePath;
	if ((i = strFilePath.find(L'.', strFilePath.size() - 5)) != std::wstring::npos)
		strFilePath.replace(i, 1, L"_Obj.");
	if (FAILED(LoadObj(strFilePath.c_str())))
		return S_FALSE;
	return S_OK;
}

HRESULT CTerrain::SaveTile(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"타일 저장 실패");
		return S_FALSE;
	}

	DWORD dwBytes = 0;

	WriteFile(hFile, &m_szFrameKey, sizeof(m_szFrameKey), &dwBytes, nullptr);
	WriteFile(hFile, &m_tFrame, sizeof(FRAME), &dwBytes, nullptr);
	WriteFile(hFile, &m_iTileX, sizeof(int), &dwBytes, nullptr);
	WriteFile(hFile, &m_iTileY, sizeof(int), &dwBytes, nullptr);
	WriteFile(hFile, &m_iTileCX, sizeof(int), &dwBytes, nullptr);
	WriteFile(hFile, &m_iTileCY, sizeof(int), &dwBytes, nullptr);

	for (auto& pTile : m_vecTile)
	{
		WriteFile(hFile, &(DRAW_DATA)pTile->GetDrawInfo(), sizeof(DRAW_DATA), &dwBytes, nullptr);
		WriteFile(hFile, &pTile->GetTileInfo(), sizeof(TILE_INFO), &dwBytes, nullptr);
	}
	CloseHandle(hFile);

	return S_OK;
}

HRESULT CTerrain::LoadTile(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"타일 불러오기 실패");
		return S_FALSE;
	}

	if(!m_vecTile.empty())
		ReleaseTile();

	DWORD dwBytes = 0;
	DRAW_DATA	tDraw;
	TILE_INFO   tTileInfo;

	ReadFile(hFile, &m_szFrameKey, sizeof(m_szFrameKey), &dwBytes, nullptr);
	ReadFile(hFile, &m_tFrame, sizeof(FRAME), &dwBytes, nullptr);
	ReadFile(hFile, &m_iTileX, sizeof(int), &dwBytes, nullptr);
	ReadFile(hFile, &m_iTileY, sizeof(int), &dwBytes, nullptr);
	ReadFile(hFile, &m_iTileCX, sizeof(int), &dwBytes, nullptr);
	ReadFile(hFile, &m_iTileCY, sizeof(int), &dwBytes, nullptr);
	m_tFrame.pListSceneOrder = nullptr;

	while (true)
	{
		ReadFile(hFile, &tDraw, sizeof(DRAW_DATA), &dwBytes, nullptr);
		ReadFile(hFile, &tTileInfo, sizeof(TILE_INFO), &dwBytes, nullptr);

		if (0 == dwBytes)
		{
			break;
		}
		CTile* pTile = CTile::Create();
		pTile->GetDrawInfo().SetData(tDraw);
		pTile->GetTileInfo() = tTileInfo;
		m_vecTile.emplace_back(pTile);
	}
	CloseHandle(hFile);

	m_tDraw.vPos = { float(GetMapCX()*0.5), float(GetMapCY()*0.5), 0.f };
	m_tDraw.vSize = { (float)GetMapCX(), (float)GetMapCY(), 0.f };

	SettingGraph();

	return S_OK;
}

HRESULT CTerrain::SaveObj(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"오브젝트 저장 실패");
		return S_FALSE;
	}

	DWORD dwBytes = 0;
	OBJ_INFO tSaveData = {};
	for (auto& pObj : m_vecVirtualObj)
	{
		//데이터 가져오기
		tSaveData = {};
		tSaveData.tDraw = (DRAW_DATA)pObj->GetDrawInfo();
		tSaveData.tStatus = (STATUS_DATA)pObj->GetStatusInfo();
		lstrcpy(tSaveData.szFrameKey, pObj->GetFrameKey());

		//데이터 저장
		WriteFile(hFile, &tSaveData, sizeof(OBJ_INFO), &dwBytes, nullptr);
		WriteFile(hFile, &static_cast<CVirtualObject*>(pObj)->GetImageId()
			, sizeof(RZIMAGE::ID), &dwBytes, nullptr);
	}
	CloseHandle(hFile);
	return S_OK;
}

HRESULT CTerrain::LoadObj(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"오브젝트 불러오기 실패");
		return S_FALSE;
	}

	if (!m_vecVirtualObj.empty())
		ReleaseObj();

	DWORD dwBytes = 0;
	OBJ_INFO	tLoadData;
	RZIMAGE::ID eImageId;
	while (true)
	{
		//데이터 가져오기
		ReadFile(hFile, &tLoadData, sizeof(OBJ_INFO), &dwBytes, nullptr);
		ReadFile(hFile, &eImageId, sizeof(RZIMAGE::ID), &dwBytes, nullptr);
		if (0 == dwBytes)
		{
			break;
		}

#ifdef CLIENT
		CGameObject* pObj = m_pObjMgr->CreateObject(eImageId);
		float fSpeed = pObj->GetDrawInfo().fSpeed;
		pObj->GetDrawInfo().SetData(tLoadData.tDraw);
		pObj->GetDrawInfo().fSpeed = fSpeed;
		tLoadData.tStatus.iClassID = eImageId;
		tLoadData.tStatus.iMp = 0;
		pObj->GetStatusInfo().SetData(tLoadData.tStatus);
		pObj->SetFrameKey(tLoadData.szFrameKey);
		m_pObjMgr->AddObject(ENUM::ObjType::UNIT, pObj);
#else
		CVirtualObject* pObj = CVirtualObject::Create();
		pObj->GetDrawInfo().SetData(tLoadData.tDraw);
		pObj->GetStatusInfo().SetData(tLoadData.tStatus);
		pObj->SetFrameKey(tLoadData.szFrameKey);
		pObj->SetImage(eImageId);
		m_vecVirtualObj.emplace_back(pObj);
#endif
	}
	CloseHandle(hFile);
	return S_OK;
}

void CTerrain::UpdateExistUnitOnTile()
{
	auto& lstUnit = m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT);
	for (auto& pTile : m_vecTile)
	{
		pTile->SetExistUnitOnTile(false);
		for (auto& pUnit : lstUnit)
		{
			if (pUnit->IsEvent(ENUM::Event::DEAD)) continue;
			if (pTile->IsPicking(pUnit->GetPos()))
			{
				pTile->SetExistUnitOnTile(true);
				break;
			}
		}
	}
}

bool CTerrain::IsGoable(D3DXVECTOR3 _vPos)
{
	auto pTile = GetTileInVec(_vPos);
	if (!pTile) return false;
	auto lstUnit = m_pObjMgr->GetObjectList(ENUM::ObjType::UNIT);
	auto iter_unit = find_if(lstUnit.begin(), lstUnit.end(), [&](auto& pUnit) {
		return pTile->IsPicking(pUnit->GetPos());
	});	
	if (iter_unit == lstUnit.end())
		return true;
	return false;
}

void CTerrain::SettingGraph()
{
	for (auto& list : m_vecGraph)
		list.clear();
	m_vecGraph.clear();
	m_vecGraph.resize(m_iTileX * m_iTileY);

	int iSelIndex = 0;
	for (int i = 0; i < m_iTileY; ++i)
	{
		for (int j = 0; j < m_iTileX; ++j)
		{
			int iIndex = i * m_iTileX + j;

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			// 좌상
			if ((0 != i) && (0 != iIndex % m_iTileX) 
				&& !(!(i % 2) && (0 == iIndex % m_iTileX)))// 첫번째 원소들의 첫번째 x값는 좌상하가 없음
			{
				iSelIndex = (i % 2) ? iIndex - m_iTileX : iIndex - (m_iTileX + 1);
				if(m_vecTile[iSelIndex]->GetTileInfo().eTileID != ENUM::Tile::BLOCK)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iSelIndex]);
			}

			// 우상
			if ((0 != i) && ((m_iTileX - 1) != iIndex % m_iTileX)
				&& !((i % 2) && (m_iTileX - 1 == iIndex % m_iTileX)))// 두번째 원소들의 마지막 x값는 우상하가 없음
			{
				iSelIndex = (i % 2) ? iIndex - (m_iTileX - 1) : iIndex - m_iTileX;
				if (m_vecTile[iSelIndex]->GetTileInfo().eTileID != ENUM::Tile::BLOCK)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iSelIndex]);
			}

			// 좌하		
			if ((m_iTileY - 1 != i) && (0 != iIndex % m_iTileX)
				&& !(!(i % 2) && (0 == iIndex % m_iTileX)))// 첫번째 원소들의 첫번째 x값는 좌상하가 없음
			{
				iSelIndex = (i % 2) ? iIndex + m_iTileX : iIndex + (m_iTileX - 1);
				if (m_vecTile[iSelIndex]->GetTileInfo().eTileID != ENUM::Tile::BLOCK)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iSelIndex]);
			}

			// 우하
			if ((m_iTileY - 1 != i) && ((m_iTileX - 1) != iIndex % m_iTileX)
				&& !((i % 2) && (m_iTileX - 1 == iIndex % m_iTileX)))// 두번째 원소들의 마지막 x값는 우상하가 없음
			{
				iSelIndex = (i % 2) ? iIndex + (m_iTileX + 1) : iIndex + m_iTileX;
				if (m_vecTile[iSelIndex]->GetTileInfo().eTileID != ENUM::Tile::BLOCK)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iSelIndex]);
			}

			// 좌
			if (0 != iIndex % m_iTileX)
			{
				iSelIndex = iIndex - 1;
				if (m_vecTile[iSelIndex]->GetTileInfo().eTileID != ENUM::Tile::BLOCK)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iSelIndex]);
			}

			// 우
			if ((m_iTileX - 1) != iIndex % m_iTileX)
			{
				iSelIndex = iIndex + 1;
				if (m_vecTile[iSelIndex]->GetTileInfo().eTileID != ENUM::Tile::BLOCK)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iSelIndex]);
			}
		}
	}
}

bool CTerrain::AddObject(CVirtualObject * _Obj)
{
	if (!_Obj) return false;
	m_vecVirtualObj.emplace_back(_Obj);
	return true;
}

CTerrain * CTerrain::Create()
{
	CTerrain* pInstance = new CTerrain;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}