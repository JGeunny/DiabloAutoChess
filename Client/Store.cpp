#include "stdafx.h"
#include "Store.h"
#include "Panel.h"
#include "UnitCard.h"
#include "LeadershipMgr.h"

#include "Archer.h"
#include "Bavarian.h"
#include "Andariel.h"
#include "Duriel.h"
#include "Dia.h"
#include "Izual.h"
#include "Barlog.h"

IMPLEMENT_CREATE(CStore)
CStore::CStore()
	:m_pPanel(nullptr)
{
}


CStore::~CStore()
{
	Release();
}

HRESULT CStore::Initialize()
{
	m_pPanel = CPanel::Create(WINCX*0.5f, WINCY*0.5f, 250, 350, L"상점");
	for (int i = 0; i < 9; ++i)
		m_lstUnitCard.emplace_back(CUnitCard::Create());
	return S_OK;
}
HRESULT CStore::LateInit()
{
	m_pPanel->SetPos(m_tDraw.vPos);
	m_tDraw.vSize = m_pPanel->GetSize();
	UpdateList();

	return S_OK;
}

void CStore::Release()
{
	SafeDelete(m_pPanel);
	ReleaseList();
}

int CStore::Update()
{
	CGameImage::LateInit();
	static D3DXVECTOR3 vCardPos;

	auto pLeadershipMgr = CLeadershipMgr::GetInstance();
	auto pLeader = pLeadershipMgr->GetAllyLeader();
	if (!pLeader) return 0;
	auto plstUnit = pLeadershipMgr->GetAllyLeaderList();
	if (!plstUnit) return 0;

	m_pPanel->SetActivate(m_bActivate);
	m_pPanel->Update();
	m_bActivate = m_pPanel->GetActivate();
	m_tDraw.vPos = m_pPanel->GetPos();
	vCardPos = m_tDraw.vPos;
	vCardPos.y += -m_tDraw.vSize.y*0.5f + 38;

	for (auto& iter_card = m_lstUnitCard.begin(); iter_card != m_lstUnitCard.end();)
		//for (auto& pCard : m_lstUnitCard)
	{
		auto& pCard = *iter_card;
		pCard->SetActivate(m_bActivate);
		pCard->SetPos(vCardPos);
		if (ENUM::Event::CLICK == (ENUM::Event)pCard->Update())
		{
			CGameObject* pGameObject = nullptr;
			switch (pCard->GetClassTypeData())
			{
			case RZIMAGE::AMAZONE:
				pGameObject = CArcher::Create();
				break;
			case RZIMAGE::DURIEL:
				pGameObject = CDuriel::Create();
				break;
			case RZIMAGE::BAVARIAN:
				pGameObject = CBavarian::Create();
				break;
			case RZIMAGE::ANDARIEL:
				pGameObject = CAndariel::Create();
				break;
			case RZIMAGE::DIA:
				pGameObject = CDia::Create();
				break;
			case RZIMAGE::IZUAL:
				pGameObject = CIzual::Create();
				break;
			case RZIMAGE::BARLOG:
				pGameObject = CBarlog::Create();
				break;
			}
			pGameObject->SetTeam(ENUM::Team::ONE);
			plstUnit->emplace_back(pGameObject);
		}

		++iter_card;
		vCardPos.y += 36;
	}
	return 0;
}

void CStore::LateUpdate()
{
	m_pPanel->LateUpdate();
	for (auto& pCard : m_lstUnitCard)
	{
		pCard->LateUpdate();
	}
}

void CStore::Render()
{
	m_pPanel->Render();
	for (auto& pCard : m_lstUnitCard)
	{
		pCard->Render();
	}
}

void CStore::ReleaseList()
{
	for_each(m_lstUnitCard.begin(), m_lstUnitCard.end(), SafeDelete<CUnitCard*>);
	m_lstUnitCard.clear();
}

void CStore::UpdateList()
{
	ReleaseList();
	std::list<CGameObject*> lstUnit;
	lstUnit.emplace_back(CArcher::Create());
	lstUnit.emplace_back(CBavarian::Create());
	lstUnit.emplace_back(CAndariel::Create());
	lstUnit.emplace_back(CDuriel::Create());
	lstUnit.emplace_back(CDia::Create());
	lstUnit.emplace_back(CIzual::Create());
	lstUnit.emplace_back(CBarlog::Create());

	for (auto& pUnit : lstUnit)
	{
		auto& iter_card = find_if(m_lstUnitCard.begin(), m_lstUnitCard.end(), [&](auto& pCard) {//카드가 있다면 카운트를 올려주고 없다면 생성해서 넣어줌
			return (pUnit->GetStatusInfo().iClassID == pCard->GetClassTypeData());
		});
		if (iter_card == m_lstUnitCard.end())
		{
			CUnitCard* pUnitCard = CUnitCard::Create();
			pUnitCard->SetUnitData(pUnit);
			m_lstUnitCard.emplace_back(pUnitCard);
		}
		else
		{
			(*iter_card)->AddCount();
		}
	}

	for_each(lstUnit.begin(), lstUnit.end(), SafeDelete<CGameObject*>);
	lstUnit.clear();
}
