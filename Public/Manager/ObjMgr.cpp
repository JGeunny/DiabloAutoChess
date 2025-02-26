#include "stdafx.h"
#include "ObjMgr.h"
#include "GameObject.h"
#include "Terrain.h"

#include "ArrangementMgr.h"
#include "VirtualObject.h"
#include "Tile.h"

#ifdef CLIENT
#include "Archer.h"
#include "Duriel.h"
#include "Bavarian.h"
#include "Andariel.h"
#include "Dia.h"
#include "Izual.h"
#include "Barlog.h"
#endif

IMPLEMENT_SINGLETON(CObjMgr)
CObjMgr::CObjMgr()
	:m_pArrangementMgr(CArrangementMgr::GetInstance())
{
	Initialize();
}

CObjMgr::~CObjMgr()
{
	Release();
	m_pArrangementMgr->DestroyInstance();
}

HRESULT CObjMgr::Initialize()
{
	LoadUnitInfo();
	return S_OK;
}


int CObjMgr::Update()
{
	m_pArrangementMgr->Update();
	for (auto& lstMap : m_lstMap)
	{
		auto& iter = lstMap.begin();
		while (iter != lstMap.end())
		{
			if ((int)ENUM::Event::DEAD == (*iter)->Update())
			{
				delete *iter;
				*iter = nullptr;
				iter = lstMap.erase(iter);
			}
			else ++iter;
		}
	}

	if (m_pArrangementMgr->GetMode() != CArrangementMgr::Mode::ARRANGE)
	{
		for (auto& lstObject : m_lstObject)
		{
			auto& iter = lstObject.begin();
			while (iter != lstObject.end())
			{
				if ((int)ENUM::Event::DEAD == (*iter)->Update())
				{
#ifdef CLIENT
					if ((*iter)->GetStatusInfo().iClassID == CLASSID_ARROW)
					{
						CBulletPoolMgr::GetInstance()->SetObject(CBulletPoolMgr::eArrow, *iter);
					}
					else if ((*iter)->GetStatusInfo().iClassID == CLASSID_ICEBOLT)
					{
						CBulletPoolMgr::GetInstance()->SetObject(CBulletPoolMgr::eIceBolt, *iter);
					}
					else if ((*iter)->GetStatusInfo().iClassID == CLASSID_LASER)
					{
						CBulletPoolMgr::GetInstance()->SetObject(CBulletPoolMgr::eLaser, *iter);
					}
					else
					{
						delete *iter;
					}
					*iter = nullptr;
					iter = lstObject.erase(iter);
#else
					delete *iter;
					*iter = nullptr;
					iter = lstObject.erase(iter);
#endif

				}
				else ++iter;
			}
		}
	}

	for (auto& lstUI : m_lstUI)
	{
		auto& iter = lstUI.begin();
		while (iter != lstUI.end())
		{
			if ((int)ENUM::Event::DEAD == (*iter)->Update())
			{
				delete *iter;
				*iter = nullptr;
				iter = lstUI.erase(iter);
			}
			else ++iter;
		}
	}
	return 0;
}

void CObjMgr::LateUpdate()
{
	m_pArrangementMgr->LateUpdate();
	for (auto& lstMap : m_lstMap)
	{
		for (auto& pObj : lstMap)
		{
			pObj->LateUpdate();
			if (lstMap.empty())
				break;
		}
	}

	for (auto& lstObject : m_lstObject)
	{
		for (auto& pObj : lstObject)
		{
			pObj->LateUpdate();
			if (lstObject.empty())
				break;
		}
	}

	for (auto& lstUI : m_lstUI)
	{
		for (auto& pObj : lstUI)
		{
			pObj->LateUpdate();
			if (lstUI.empty())
				break;
		}
	}
}

void CObjMgr::Render()
{
	static std::list<CGameObject*> lstObject;
	FUNC::GET::CombinationList(lstObject, m_lstObject, (int)ENUM::ObjType::END);
	FUNC::SORT::ObjectList(lstObject);
	
	m_pArrangementMgr->Render();
	for (auto& lstMap : m_lstMap)
	{
		for (auto& pObj : lstMap)
		{
			pObj->Render();
		}
	}

	for (auto& pObj : lstObject)
	{
		pObj->Render_Scroll();
	}
	//for (auto& lstObject : m_lstObject)
	//{
	//	for (auto& pObj : lstObject)
	//	{
	//		pObj->Render_Scroll();
	//	}
	//}

	for (auto& lstUI : m_lstUI)
	{
		if (lstUI == m_lstUI[(int)ENUM::UIType::EFFECT])
		{
			for (auto& pObj : lstUI)
			{
				pObj->Render_Scroll();
			}
		}
		else
		{
			for (auto& pObj : lstUI)
			{
				pObj->Render();
			}
		}
	}
}

void CObjMgr::Release()
{
	DeleteID(ENUM::MapType::END);
	DeleteID(ENUM::ObjType::END);
	DeleteID(ENUM::UIType::END);

	DeleteBufferID(ENUM::MapType::END);
	DeleteBufferID(ENUM::ObjType::END);
	DeleteBufferID(ENUM::UIType::END);
}

HRESULT CObjMgr::AddObject(ENUM::MapType _eMapType, CGameImage * pObj)
{
	NULL_CHECK_RETURN(pObj, E_FAIL);
	m_lstMap[(int)_eMapType].emplace_back(pObj);

	return S_OK;
}

HRESULT CObjMgr::AddObject(ENUM::ObjType _eObjType, CGameObject * pObj)
{
	NULL_CHECK_RETURN(pObj, E_FAIL);
	m_lstObject[(int)_eObjType].emplace_back(pObj);

	return S_OK;
}

HRESULT CObjMgr::AddObject(ENUM::UIType _eUIType, CGameImage * pObj)
{
	NULL_CHECK_RETURN(pObj, E_FAIL);
	m_lstUI[(int)_eUIType].emplace_back(pObj);

	return S_OK;
}


void CObjMgr::DeleteID(ENUM::MapType _eMapType)
{
	if (ENUM::MapType::END == _eMapType)
	{
		for (auto& lstMap : m_lstMap)
		{
			for (auto& pObj : lstMap)
				SafeDelete(pObj);
			lstMap.clear();
		}
	}
	else
	{
		for (auto& pObj : m_lstMap[(int)_eMapType])
		{
			SafeDelete(pObj);
		}
		m_lstMap[(int)_eMapType].clear();
	}
}

void CObjMgr::DeleteID(ENUM::ObjType _eObjType)
{
	if (ENUM::ObjType::END == _eObjType)
	{
		for (auto& lstObject : m_lstObject)
		{
			for(auto& pObj : lstObject)
				SafeDelete(pObj);
			lstObject.clear();
		}
	}
	else
	{
		for (auto& pObj : m_lstObject[(int)_eObjType])
		{
			SafeDelete(pObj);
		}
		m_lstObject[(int)_eObjType].clear();
	}
}

void CObjMgr::DeleteID(ENUM::UIType _eUIType)
{
	if (ENUM::UIType::END == _eUIType)
	{
		for (auto& lstUI : m_lstUI)
		{
			for (auto& pObj : lstUI)
				SafeDelete(pObj);
			lstUI.clear();
		}
	}
	else
	{
		for (auto& pObj : m_lstUI[(int)_eUIType])
		{
			SafeDelete(pObj);
		}
		m_lstUI[(int)_eUIType].clear();
	}
}

void CObjMgr::DeleteBufferID(ENUM::MapType _eMapType)
{
	if (ENUM::MapType::END == _eMapType)
	{
		for (auto& lstMap : m_lstMapBuffer)
		{
			for (auto& pObj : lstMap)
				SafeDelete(pObj);
			lstMap.clear();
		}
	}
	else
	{
		for (auto& pObj : m_lstMapBuffer[(int)_eMapType])
		{
			SafeDelete(pObj);
		}
		m_lstMapBuffer[(int)_eMapType].clear();
	}
}

void CObjMgr::DeleteBufferID(ENUM::ObjType _eObjType)
{
	if (ENUM::ObjType::END == _eObjType)
	{
		for (auto& lstObject : m_lstObjectBuffer)
		{
			for (auto& pObj : lstObject)
				SafeDelete(pObj);
			lstObject.clear();
		}
	}
	else
	{
		for (auto& pObj : m_lstObjectBuffer[(int)_eObjType])
		{
			SafeDelete(pObj);
		}
		m_lstObjectBuffer[(int)_eObjType].clear();
	}
}

void CObjMgr::DeleteBufferID(ENUM::UIType _eUIType)
{
	if (ENUM::UIType::END == _eUIType)
	{
		for (auto& lstUI : m_lstUIBuffer)
		{
			for (auto& pObj : lstUI)
				SafeDelete(pObj);
			lstUI.clear();
		}
	}
	else
	{
		for (auto& pObj : m_lstUIBuffer[(int)_eUIType])
		{
			SafeDelete(pObj);
		}
		m_lstUIBuffer[(int)_eUIType].clear();
	}
}

void CObjMgr::SelectedObjectFollowToPos(CTile* _pTile)
{
	if (!_pTile) return;
	for (auto& lstObj : m_lstObject)
	{
		for (auto& pObj : lstObj)
		{
			if (pObj->GetSelect())
			{
				pObj->SetPos(_pTile->GetPos());
				if (_pTile->GetTileInfo().eTileID == ENUM::Tile::ALLY_FIELD)
					pObj->SetBeOnTheLand(true);
				else
					pObj->SetBeOnTheLand(false);
			}
		}
	}
}

void CObjMgr::DeselectObjectList()
{
	for (auto& lstObj : m_lstObject)
	{
		for (auto& pObj : lstObj)
		{
			pObj->SetSelect(false);
		}
	}
}

CGameObject * CObjMgr::GetUnit(D3DXVECTOR3 _vPos)
{
	auto& iter_Unit = find_if(
		m_lstObject[(int)ENUM::ObjType::UNIT].begin()
		, m_lstObject[(int)ENUM::ObjType::UNIT].end()
		, [&](auto& pObj){
		return FUNC::CHECK::PosInRect(pObj->GetDrawInfo().GetRect(), _vPos);
		});
	if (iter_Unit != m_lstObject[(int)ENUM::ObjType::UNIT].end())
		return *iter_Unit;
	return nullptr;
}

bool CObjMgr::CollisionExUnit(CGameObject * _pUnit)
{
	static float fRadiusSum, fDist;
	static D3DXVECTOR3 vAngle, vLook(1.f, 0.f, 0.f);
	bool isCrash = false;
	if (_pUnit->IsEvent(ENUM::Event::DEAD)) return isCrash;
	for (auto& pObj : m_lstObject[(int)ENUM::ObjType::UNIT])
	{
		if (pObj->IsEvent(ENUM::Event::DEAD)) continue;
		if (pObj == _pUnit) continue;
		DRAW_INFO& tDst = pObj->GetDrawInfo();
		DRAW_INFO& tSrc = _pUnit->GetDrawInfo();
		fRadiusSum = ((tDst.GetSizeLand().x) * 0.4f) + ((tSrc.GetSizeLand().x) * 0.4f);
		fDist = FUNC::MATH::Dist(tDst.vPos, tSrc.vPos);
		if (fRadiusSum > fDist)
		{
			vAngle = FUNC::GET::Angle(tSrc.vPos, tDst.vPos, vLook);
			tSrc.vPos = tDst.vPos + FUNC::GET::Dir(vAngle) * (fRadiusSum + 1);
			isCrash = true;
		}
	}
	return isCrash;
}

std::list<CGameImage*>& CObjMgr::GetObjectList(ENUM::MapType _eMapType)
{
	return m_lstMap[(int)_eMapType];
}

std::list<CGameObject*>& CObjMgr::GetObjectList(ENUM::ObjType _eObjType)
{
	return m_lstObject[(int)_eObjType];
}

std::list<CGameImage*>& CObjMgr::GetObjectList(ENUM::UIType _eUIType)
{
	return m_lstUI[(int)_eUIType];
}

CGameObject * CObjMgr::GetObjectInList(D3DXVECTOR3 _vMousePos)
{
	for (auto& lstObj : m_lstObject)
	{
		auto& iter = find_if(lstObj.begin(), lstObj.end(), [&](auto& pObj)
		{
			return FUNC::CHECK::PosInRect(pObj->GetRect(), _vMousePos);
		});
		if (iter != lstObj.end())
			return *iter;
	}
	return nullptr;
}

CTerrain * CObjMgr::GetTerrain()
{
	if(m_lstMap[(int)ENUM::MapType::TERRAIN].size() > 0)
		return static_cast<CTerrain*>(m_lstMap[(int)ENUM::MapType::TERRAIN].front());
	else
		return nullptr;
}

void CObjMgr::InitNextScene()
{
	DeleteID(ENUM::MapType::END);
	DeleteID(ENUM::ObjType::END);
	for (int i = 0; i < (int)ENUM::UIType::END; ++i)
	{
		if ((ENUM::UIType)i == ENUM::UIType::MOUSE) continue;
		DeleteID((ENUM::UIType)i);
	}
}

void CObjMgr::LoadUnitInfo()
{
#ifdef CLIENT
	WCHAR* pFilePath = L"../Data/Obj0.dat";
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"오브젝트 불러오기 실패");
		return;
	}

	DWORD dwBytes = 0;
	OBJ_INFO	tLoadData;
	RZIMAGE::ID eType;
	while (true)
	{
		//데이터 가져오기
		ReadFile(hFile, &tLoadData, sizeof(OBJ_INFO), &dwBytes, nullptr);
		if (0 == dwBytes)
		{
			break;
		}
		eType = FUNC::CONVERT::GetImageId(tLoadData.tStatus.szName);
		tLoadData.tStatus.iClassID = eType;
		switch (eType)
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
			CArcher::SetObjInfo(tLoadData);
			break;
		case RZIMAGE::DURIEL:
			CDuriel::SetObjInfo(tLoadData);
			break;
		case RZIMAGE::BAVARIAN:
			CBavarian::SetObjInfo(tLoadData);
			break;
		case RZIMAGE::ANDARIEL:
			CAndariel::SetObjInfo(tLoadData);
			break;
		case RZIMAGE::DIA:
			CDia::SetObjInfo(tLoadData);
			break;
		case RZIMAGE::IZUAL:
			CIzual::SetObjInfo(tLoadData);
			break;
		case RZIMAGE::BARLOG:
			CBarlog::SetObjInfo(tLoadData);
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
	CloseHandle(hFile);
	return;
#endif
}

void CObjMgr::BackupList()
{
	DeleteBufferID(ENUM::MapType::END);
	DeleteBufferID(ENUM::ObjType::END);
	DeleteBufferID(ENUM::UIType::END);
	
	for (int i = 0; i < (int)ENUM::MapType::END; ++i)
	{
		for (auto& pObj : m_lstMap[i])
		{
			m_lstMapBuffer[i].emplace_back(pObj);
		}
		m_lstMap[i].clear();
	}
	for (int i = 0; i < (int)ENUM::ObjType::END; ++i)
	{
		for (auto& pObj : m_lstObject[i])
		{
			m_lstObjectBuffer[i].emplace_back(pObj);
		}
		m_lstObject[i].clear();
	}
	for (int i = 0; i < (int)ENUM::UIType::END; ++i)
	{
		if ((ENUM::UIType)i == ENUM::UIType::MOUSE) continue;
		for (auto& pObj : m_lstUI[i])
		{
			m_lstUIBuffer[i].emplace_back(pObj);
		}
		m_lstUI[i].clear();
	}
}

void CObjMgr::LoadList()
{
	InitNextScene();

	for (int i = 0; i < (int)ENUM::MapType::END; ++i)
	{
		for (auto& pObj : m_lstMapBuffer[i])
		{
			m_lstMap[i].emplace_back(pObj);
		}
		m_lstMapBuffer[i].clear();
	}
	for (int i = 0; i < (int)ENUM::ObjType::END; ++i)
	{
		for (auto& pObj : m_lstObjectBuffer[i])
		{
			m_lstObject[i].emplace_back(pObj);
		}
		m_lstObjectBuffer[i].clear();
	}
	for (int i = 0; i < (int)ENUM::UIType::END; ++i)
	{
		if ((ENUM::UIType)i == ENUM::UIType::MOUSE) continue;
		for (auto& pObj : m_lstUIBuffer[i])
		{
			m_lstUI[i].emplace_back(pObj);
		}
		m_lstUIBuffer[i].clear();
	}
}

CGameObject * CObjMgr::CreateObject(RZIMAGE::ID _eImageId)
{
	CGameObject* pObj = nullptr;
#ifdef CLIENT
	switch (_eImageId)
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
		pObj = CArcher::Create();
		break;
	case RZIMAGE::DURIEL:
		pObj = CDuriel::Create();
		break;
	case RZIMAGE::BAVARIAN:
		pObj = CBavarian::Create();
		break;
	case RZIMAGE::ANDARIEL:
		pObj = CAndariel::Create();
		break;
	case RZIMAGE::DIA:
		pObj = CDia::Create();
		break;
	case RZIMAGE::IZUAL:
		pObj = CIzual::Create();
		break;
	case RZIMAGE::BARLOG:
		pObj = CBarlog::Create();
		break;
	case RZIMAGE::SKILL:
		break;
	case RZIMAGE::BASEBUTTON:
		break;
	case RZIMAGE::END:
		break;
	default:
		break;
	}
#endif
	return pObj;
}
