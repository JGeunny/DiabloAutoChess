#include "stdafx.h"
#include "ArrangementMgr.h"
#include "ControlMgr.h"
#include "GameObject.h"
#include "Mouse.h"
#include "Terrain.h"
#include "Tile.h"

#ifdef CLIENT
#include "Trait.h"
#include "TraitCard.h"
#endif

IMPLEMENT_SINGLETON(CArrangementMgr)
CArrangementMgr::CArrangementMgr()
	:m_pControlMgr(CControlMgr::GetInstance())
	, m_pKeyMgr(CKeyMgr::GetInstance())
	, m_eMode(Mode::NORMAL)
{	 
	//m_eMode = Mode::ARRANGE;
	Initialize();
}


CArrangementMgr::~CArrangementMgr()
{
	Release();
}

HRESULT CArrangementMgr::Initialize()
{
	return S_OK;
}

int CArrangementMgr::Update()
{

	return 0;
}

void CArrangementMgr::LateUpdate()
{
#ifdef CLIENT
	if (m_eMode == Mode::ARRANGE)
	{
		auto pTerrain = CObjMgr::GetInstance()->GetTerrain();
		if (!pTerrain) return;
		auto vMousePos = m_pControlMgr->GetMouse()->GetPosScroll();
		auto pTile = pTerrain->GetTileInVec(vMousePos);
		if (!pTile) return;

		if (m_pKeyMgr->KeyDown(KEY::LBUTTON))
		{
			auto pObj = CObjMgr::GetInstance()->GetObjectInList(vMousePos);
			if (pObj)
			{
				if( ENUM::Team::ONE== pObj->GetTeam())
					pObj->SetSelect(true);
			}
		}
		if (m_pKeyMgr->KeyUp(KEY::LBUTTON))
		{
			CObjMgr::GetInstance()->DeselectObjectList();
		}
		//놓을수 있는 타일만 놓기
		if ((pTile->GetTileInfo().eTileID == ENUM::Tile::ALLY_STACK
			|| pTile->GetTileInfo().eTileID == ENUM::Tile::ALLY_FIELD) && !pTile->GetExistUnitOnTile())
		{
			CObjMgr::GetInstance()->SelectedObjectFollowToPos(pTile);
		}
		//트레잇 업데이트
		auto pTraitList = CObjMgr::GetInstance()->GetObjectList(ENUM::UIType::TRAIT);
		if (pTraitList.size() > 0)
		{
			int iCount_Knight = 0;
			int iCount_Scout = 0;
			int iCount_Wizard = 0;
			int iCount_Assassin = 0;
			//땅위에 올라가있는 타입을 계산해서 카드에 넣어준다.
			auto lstUnit = CObjMgr::GetInstance()->GetObjectList(ENUM::ObjType::UNIT);
			for (auto& pUnit : lstUnit)
			{
				if (!pUnit->GetBeOnTheLand()) continue;
				switch (pUnit->GetStatusInfo().eJob)
				{
				case ENUM::Job::NONE:
					break;
				case ENUM::Job::KNIGHT:
					++iCount_Knight;
					break;
				case ENUM::Job::SCOUT:
					++iCount_Scout;
					break;
				case ENUM::Job::WIZARD:
					++iCount_Wizard;
					break;
				case ENUM::Job::ASSASSIN:
					++iCount_Assassin;
					break;
				case ENUM::Job::END:
					break;
				default:
					break;
				}
			}
			auto pTrait = static_cast<CTrait*>(pTraitList.front());
			auto& vecCradList = pTrait->GetTraitCardVec();
			for (auto& pCard : vecCradList)
			{
				switch (pCard->GetTrait())
				{
				case ENUM::Job::NONE:
					break;
				case ENUM::Job::KNIGHT:
					pCard->SetTraitCount(iCount_Knight);
					break;
				case ENUM::Job::SCOUT:
					pCard->SetTraitCount(iCount_Scout);
					break;
				case ENUM::Job::WIZARD:
					pCard->SetTraitCount(iCount_Wizard);
					break;
				case ENUM::Job::ASSASSIN:
					pCard->SetTraitCount(iCount_Assassin);
					break;
				case ENUM::Job::END:
					break;
				default:
					break;
				}
			}
		}
	}
#endif
}

void CArrangementMgr::Render()
{
}

void CArrangementMgr::Release()
{
}
