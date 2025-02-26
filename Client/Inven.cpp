#include "stdafx.h"
#include "Inven.h"
#include "Panel.h"
#include "UnitCard.h"
#include "LeadershipMgr.h"

IMPLEMENT_CREATE(CInven)
CInven::CInven()
	:m_pPanel(nullptr)
{
}


CInven::~CInven()
{
	Release();
}

HRESULT CInven::Initialize()
{
	m_pPanel = CPanel::Create(WINCX*0.5f, WINCY*0.5f, 250, 350, L"인벤");
	for (int i = 0; i < 9; ++i)
		m_lstUnitCard.emplace_back(CUnitCard::Create());
	return S_OK;
}
HRESULT CInven::LateInit()
{
	m_pPanel->SetPos(m_tDraw.vPos);
	m_tDraw.vSize = m_pPanel->GetSize();
	return S_OK;
}

void CInven::Release()
{
	SafeDelete(m_pPanel);
	ReleaseList();
}

int CInven::Update()
{
	CGameImage::LateInit();
	static D3DXVECTOR3 vCardPos;
	UpdateList();
	
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

	for(auto& iter_card = m_lstUnitCard.begin(); iter_card != m_lstUnitCard.end();)
	//for (auto& pCard : m_lstUnitCard)
	{
		auto& pCard = *iter_card;
		pCard->SetActivate(m_bActivate);
		pCard->SetPos(vCardPos);
		if (ENUM::Event::CLICK == (ENUM::Event)pCard->Update())
		{
			auto& iter_unit = find_if(plstUnit->begin(), plstUnit->end(), [&](auto& pUnit) {
				return (pLeader != pUnit) && (pUnit->GetStatusInfo().iClassID == pCard->GetClassTypeData());
			});
			SafeDelete(*iter_unit);
			plstUnit->erase(iter_unit);

			if (pCard->SubCount())
			{
				++iter_card;
			}
			else
			{
				SafeDelete(*iter_card);
				iter_card = m_lstUnitCard.erase(iter_card);
			}
		}
		else
		{ 
			++iter_card;
		}

		vCardPos.y += 36;
	}
	return 0;
}

void CInven::LateUpdate()
{
	m_pPanel->LateUpdate();
	for (auto& pCard : m_lstUnitCard)
	{
		pCard->LateUpdate();
	}
}

void CInven::Render()
{
	m_pPanel->Render();
	for (auto& pCard : m_lstUnitCard)
	{
		pCard->Render();
	}
}

void CInven::ReleaseList()
{
	for_each(m_lstUnitCard.begin(), m_lstUnitCard.end(), SafeDelete<CUnitCard*>);
	m_lstUnitCard.clear();
}

void CInven::UpdateList()
{
	ReleaseList();
	auto pLeadershipMgr = CLeadershipMgr::GetInstance();
	auto pLeader = pLeadershipMgr->GetAllyLeader();
	if (!pLeader) return;
	auto plstUnit = pLeadershipMgr->GetAllyLeaderList();
	if (!plstUnit) return;


	for (auto& pUnit : *plstUnit)
	{
		if (pLeader == pUnit) continue;//리더는 거래하지 않는다
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
}
