#include "stdafx.h"
#include "UnitCard.h"
#include "GameObject.h"
#include "ControlMgr.h"
#include "Mouse.h"

IMPLEMENT_CREATE(CUnitCard)
CUnitCard::CUnitCard()
	:m_szUnitName(L"")
	, m_iGold(0)
	, m_iCount(0)
	, m_eJob(ENUM::Job::NONE)

{
}


CUnitCard::~CUnitCard()
{
}

HRESULT CUnitCard::Initialize()
{
	m_pTextureMgr->LoadTexture(L"TraitCard|Card", L"../Image/UI/Trait/Card.png");
	m_pTextureMgr->LoadTexture(L"TraitCard|Form", L"../Image/UI/Trait/trait_icon_form.png");
	m_pTextureMgr->LoadTexture(L"TraitCard|Knight", L"../Image/UI/Trait/trait_icon_knight.png");//아이보리색
	m_pTextureMgr->LoadTexture(L"TraitCard|Scout", L"../Image/UI/Trait/trait_icon_ranger.png");//초록색
	m_pTextureMgr->LoadTexture(L"TraitCard|Wizard", L"../Image/UI/Trait/trait_icon_sorcerer.png");//파랑색
	m_pTextureMgr->LoadTexture(L"TraitCard|Assassin", L"../Image/UI/Trait/trait_icon_assassin.png");//보라색

	m_pFormTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Form", 0);
	m_tDrawForm.color = INIT_COLOR_IVORY;

	m_tDraw.vSize = { 240.f, 36.f, 0.f };
	SetUnitData();
	return S_OK;
}

HRESULT CUnitCard::LateInit()
{
	return S_OK;
}

void CUnitCard::Release()
{
}

int CUnitCard::Update()
{
	if (!m_bActivate) return (int)ENUM::Event::NOEVENT;
	m_tDrawForm.vPos = m_tDraw.vPos;
	m_tDrawForm.vPos.x = m_tDraw.vPos.x - m_tDraw.vSize.x * 0.5f + m_tDraw.vSize.y * 0.5f;
	m_tDrawForm.vSize = { m_tDraw.vSize.y, m_tDraw.vSize.y, 0.f };


	m_tDrawTrait.vPos = m_tDraw.vPos;
	m_tDrawTrait.vPos.x = m_tDraw.vPos.x - m_tDraw.vSize.x * 0.5f + m_tDraw.vSize.y * 0.5f;
	m_tDrawTrait.vSize = { m_tDraw.vSize.y * 0.75f, m_tDraw.vSize.y * 0.75f, 0.f };

	m_tDrawString.vPos = m_tDraw.vPos;
	m_tDrawString.vPos.x = m_tDraw.vPos.x + m_tDrawForm.vSize.x * 0.5f;
	m_tDrawString.vPos.y -= m_tDraw.vSize.y * 0.25f;
	m_tDrawString.vSize = m_tDraw.vSize;
	m_tDrawString.vSize.x -= m_tDrawForm.vSize.x;
	m_tDrawString.vSize.y *= 0.5f;

	m_tDrawString_Gold.vPos = m_tDraw.vPos;
	m_tDrawString_Gold.vPos.x = m_tDraw.vPos.x + m_tDrawForm.vSize.x * 0.5f;
	m_tDrawString_Gold.vPos.y += m_tDraw.vSize.y * 0.25f;
	m_tDrawString_Gold.vSize = m_tDraw.vSize;
	m_tDrawString_Gold.vSize.x -= m_tDrawForm.vSize.x;
	m_tDrawString_Gold.vSize.y *= 0.5f;

	m_eEvent = ENUM::Event::NOEVENT;
	RECT rtCrash = m_tDraw.GetRect();
	if (FUNC::CHECK::PosInRect(rtCrash,
		CControlMgr::GetInstance()->GetMouse()->GetPos()))
	{
		if (m_pKeyMgr->KeyDown(KEY::LBUTTON, KeyChannel::UI2))
		{
			CSoundMgr::GetInstance()->MyPlaySound(L"button.wav", CSoundMgr::CHANNELID::UI);
			m_eEvent = ENUM::Event::CLICK;
		}
	}
	
	//if (m_pKeyMgr->KeyDown(KEY::LBUTTON, KeyChannel::UI2))
	//{
	//	RECT rtCrash = m_tDraw.GetRect();
	//	if (FUNC::CHECK::PosInRect(rtCrash,
	//		CControlMgr::GetInstance()->GetMouse()->GetPos()))
	//	{
	//		m_eEvent = ENUM::Event::CLICK;
	//	}
	//}
	//if (m_pKeyMgr->KeyUp(KEY::LBUTTON, KeyChannel::UI2))
	//{
	//	m_eEvent = ENUM::Event::NOEVENT;
	//}
	return (int)m_eEvent;
}

void CUnitCard::LateUpdate()
{
	if (!m_bActivate) return;
}

void CUnitCard::Render()
{
	if (!m_bActivate) return;
	static RECT rtCardRect, rtStringRect, rtGoldRect;
	static WCHAR szUnitInfo[MID_STR];
	static WCHAR szGold[MID_STR];
	ZeroMemory(szUnitInfo, sizeof(szUnitInfo));
	ZeroMemory(szGold, sizeof(szGold));

	rtCardRect = m_tDraw.GetRect();
	//m_pDeviceMgr->DrawRectangle(rtCardRect);

	m_tDrawForm.SetTexInfo(m_pFormTexture);
	m_tDrawTrait.SetTexInfo(m_pTraitTexture);

	m_tDrawForm.matCurrent = m_tDrawForm.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);
	m_tDrawTrait.matCurrent = m_tDrawTrait.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

	m_pDeviceMgr->DrawImage(m_tDrawForm);
	m_pDeviceMgr->DrawImage(m_tDrawTrait);

	rtStringRect = m_tDrawString.GetRect();
	//m_pDeviceMgr->DrawRectangle(rtStringRect);
	swprintf_s(szUnitInfo, L"[%d]%s", m_iCount, m_szUnitName);
	m_pDeviceMgr->DrawString(szUnitInfo, lstrlen(szUnitInfo), &rtStringRect, 5UL, INIT_COLOR_BLACK, ENUM::FONT::FONT16);

	rtGoldRect = m_tDrawString_Gold.GetRect();
	//m_pDeviceMgr->DrawRectangle(rtGoldRect);
	swprintf_s(szGold, L"%d", m_iGold);
	m_pDeviceMgr->DrawString(szGold, lstrlen(szGold), &rtGoldRect, 5UL, INIT_COLOR_BLACK, ENUM::FONT::FONT16);
}

void CUnitCard::SetUnitData(CGameObject * _pUnit)
{
	static STATUS_INFO tStatus;
	if (!_pUnit)
	{
		tStatus.iClassID = RZIMAGE::AMAZONE;
		tStatus.eJob = ENUM::Job::SCOUT;
	}
	else
	{
		tStatus = _pUnit->GetStatusInfo();
	}

	m_iClassTypeData = tStatus.iClassID;
	m_eJob = tStatus.eJob;
	lstrcpy(m_szUnitName,
		FUNC::CONVERT::GetImageName((RZIMAGE::ID)m_iClassTypeData));
	m_iGold = tStatus.iGold;
	m_iCount = 1;


	switch (m_eJob)
	{
	case ENUM::Job::NONE:
		break;
	case ENUM::Job::KNIGHT:
		m_pTraitTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Knight", 0);
		break;
	case ENUM::Job::SCOUT:
		m_pTraitTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Scout", 0);
		break;
	case ENUM::Job::WIZARD:
		m_pTraitTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Wizard", 0);
		break;
	case ENUM::Job::ASSASSIN:
		m_pTraitTexture = m_pTextureMgr->GetTexInfo(L"TraitCard|Assassin", 0);
		break;
	case ENUM::Job::END:
		break;
	default:
		break;
	}

	switch (m_iClassTypeData)
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
		m_tDrawTrait.color = INIT_COLOR_GREEN;
		break;
	case RZIMAGE::DURIEL:
		m_tDrawTrait.color = INIT_COLOR_MAGENTA;
		break;
	case RZIMAGE::BAVARIAN:
		m_tDrawTrait.color = INIT_COLOR_RED;
		break;
	case RZIMAGE::ANDARIEL:
		m_tDrawTrait.color = INIT_COLOR_BLUE;
		break;
	case RZIMAGE::DIA:
		m_tDrawTrait.color = D3DCOLOR_ARGB(255, 255, 100, 100);
		break;
	case RZIMAGE::IZUAL:
		m_tDrawTrait.color = D3DCOLOR_ARGB(255, 255, 100, 255);
		break;
	case RZIMAGE::BARLOG:
		m_tDrawTrait.color = D3DCOLOR_ARGB(255, 255, 100, 100);
		break;
	case RZIMAGE::COW:
		break;
	case RZIMAGE::SKILL:
		break;
	case RZIMAGE::ICEBOLT:
		break;
	case RZIMAGE::LASER:
		break;
	case RZIMAGE::BONE:
		break;
	case RZIMAGE::EFFECT:
		break;
	case RZIMAGE::STUN:
		break;
	case RZIMAGE::TRAITBUFF:
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