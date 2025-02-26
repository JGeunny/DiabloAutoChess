#include "stdafx.h"
#include "TraitCard.h"

IMPLEMENT_CREATE(CTraitCard)
CTraitCard::CTraitCard()
	:m_eTrait(ENUM::Job::NONE)
	, m_iTraitCount(0)
	, m_pCardTexture(nullptr)
	, m_pFormTexture(nullptr)
	, m_pTraitTexture(nullptr)
{
}


CTraitCard::~CTraitCard()
{
}

HRESULT CTraitCard::Initialize()
{
	m_pTextureMgr->LoadTexture(L"TraitCard|Card", L"../Image/UI/Trait/Card.png");
	m_pTextureMgr->LoadTexture(L"TraitCard|Form", L"../Image/UI/Trait/trait_icon_form.png");
	m_pTextureMgr->LoadTexture(L"TraitCard|Knight", L"../Image/UI/Trait/trait_icon_knight.png");//아이보리색
	m_pTextureMgr->LoadTexture(L"TraitCard|Scout", L"../Image/UI/Trait/trait_icon_ranger.png");//초록색
	m_pTextureMgr->LoadTexture(L"TraitCard|Wizard", L"../Image/UI/Trait/trait_icon_sorcerer.png");//파랑색
	m_pTextureMgr->LoadTexture(L"TraitCard|Assassin", L"../Image/UI/Trait/trait_icon_assassin.png");//보라색

	m_pCardTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Card", 0);
	m_pFormTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Form", 0);
	m_tDraw.color = INIT_COLOR_OPACITY;
	return S_OK;
}

HRESULT CTraitCard::LateInit()
{
	return S_OK;
}

void CTraitCard::Release()
{
}

int CTraitCard::Update()
{
	m_bActivate = (m_iTraitCount > 0) ? true : false;
	if (ENUM::Job::NONE == m_eTrait) m_bActivate = false;
	if (!m_bActivate) return (int)m_eEvent;

	if (m_iTraitCount >= m_iTraitCountMax)
	{
		m_tDrawForm.color = INIT_COLOR_YELLOW;
	}
	else
	{
		m_tDrawForm.color = INIT_COLOR_GREY;
	}
	
	m_tDrawForm.vPos = m_tDraw.vPos;
	m_tDrawForm.vPos.x = m_tDraw.vPos.x  - m_tDraw.vSize.x * 0.25f;
	m_tDrawForm.vSize = { m_tDraw.vSize.y, m_tDraw.vSize.y, 0.f };

	m_tDrawTrait.vPos = m_tDraw.vPos;
	m_tDrawTrait.vPos.x = m_tDraw.vPos.x  - m_tDraw.vSize.x * 0.25f;
	m_tDrawTrait.vSize = { m_tDraw.vSize.y * 0.75f, m_tDraw.vSize.y * 0.75f, 0.f };

	m_tDrawString.vPos = m_tDraw.vPos;
	m_tDrawString.vPos.x = m_tDraw.vPos.x + m_tDraw.vSize.x * 0.2f;
	m_tDrawString.vSize = { m_tDraw.vSize.x * 0.5f, m_tDraw.vSize.y, 0.f };

	return (int)m_eEvent;
}

void CTraitCard::LateUpdate()
{
	if (!m_bActivate) return;
}

void CTraitCard::Render()
{
	if (!m_bActivate) return;
	static WCHAR szTraitCount[MID_STR];
	static RECT rtStringRect;
	ZeroMemory(szTraitCount, sizeof(szTraitCount));

	m_tDraw.SetTexInfo(m_pCardTexture);
	m_tDrawForm.SetTexInfo(m_pFormTexture);
	m_tDrawTrait.SetTexInfo(m_pTraitTexture);

	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	m_tDrawForm.matCurrent = m_tDrawForm.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	m_tDrawTrait.matCurrent = m_tDrawTrait.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

	m_pDeviceMgr->DrawImage(m_tDraw);
	m_pDeviceMgr->DrawImage(m_tDrawForm);
	m_pDeviceMgr->DrawImage(m_tDrawTrait);

	rtStringRect = m_tDrawString.GetRect();
	swprintf_s(szTraitCount, L"%d / %d", m_iTraitCount, m_iTraitCountMax);
	m_pDeviceMgr->DrawString(szTraitCount, lstrlen(szTraitCount), &rtStringRect, 5UL, INIT_COLOR_IVORY, ENUM::FONT::FONT24);
}

void CTraitCard::SetTrait(ENUM::Job _eTrait)
{
	m_eTrait = _eTrait;
	switch (m_eTrait)
	{
	case ENUM::Job::NONE:
		break;
	case ENUM::Job::KNIGHT:
		m_pTraitTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Knight", 0);
		m_tDrawTrait.color = INIT_COLOR_RED;
		m_iTraitCountMax = TRAIT_KNIGHT_MAX;
		break;
	case ENUM::Job::SCOUT:
		m_pTraitTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Scout", 0);
		m_tDrawTrait.color = INIT_COLOR_GREEN;
		m_iTraitCountMax = TRAIT_SCOUT_MAX;
		break;
	case ENUM::Job::WIZARD:
		m_pTraitTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Wizard", 0);
		m_tDrawTrait.color = INIT_COLOR_BLUE;
		m_iTraitCountMax = TRAIT_WIZARD_MAX;
		break;
	case ENUM::Job::ASSASSIN:
		m_pTraitTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Assassin", 0);
		m_tDrawTrait.color = INIT_COLOR_MAGENTA;
		m_iTraitCountMax = TRAIT_ASSASSIN_MAX;
		break;
	case ENUM::Job::END:
		break;
	default:
		break;
	}
}
