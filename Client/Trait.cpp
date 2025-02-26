#include "stdafx.h"
#include "Trait.h"
#include "TraitCard.h"

IMPLEMENT_CREATE(CTrait)
CTrait::CTrait()
{
}


CTrait::~CTrait()
{
	Release();
}

HRESULT CTrait::Initialize()
{
	return S_OK;
}

HRESULT CTrait::LateInit()
{
	m_tDraw.vPos.x = 60;
	m_tDraw.vPos.y = 150;
	for (int i = 0; i < (int)ENUM::Job::END; ++i)
	{
		if (i == (int)ENUM::Job::NONE) continue;
		//vPos.y += 50;
		CTraitCard *pCard = CTraitCard::Create();
		pCard->SetTrait((ENUM::Job)i);
		pCard->SetSize(D3DXVECTOR3(120.f, 50.f, 0.f));
		//pCard->SetTraitCount(1);
		m_vecTraitCard.emplace_back(pCard);
	}
	return S_OK;
}

void CTrait::Release()
{
	for_each(m_vecTraitCard.begin(), m_vecTraitCard.end(), SafeDelete<CTraitCard*>);
}

int CTrait::Update()
{
	CGameImage::LateInit();
	static D3DXVECTOR3 vPos;
	vPos = m_tDraw.vPos;
	for (auto& pCard : m_vecTraitCard)
	{
		if (pCard->GetActivate())
		{
			vPos.y += 50;
			pCard->SetPos(vPos);
		}
		pCard->Update();
	}
	return 0;
}

void CTrait::LateUpdate()
{
	for (auto& pCard : m_vecTraitCard)
	{
		pCard->LateUpdate();
	}
}

void CTrait::Render()
{
	for (auto& pCard : m_vecTraitCard)
	{
		pCard->Render();
	}
}
