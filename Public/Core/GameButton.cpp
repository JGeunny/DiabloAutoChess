#include "stdafx.h"
#include "GameButton.h"

#include "ButtonImage.h"
#include "BaseButtonImageImp.h"
#include "Mouse.h"

IMPLEMENT_CREATE_COMPONENT(CGameButton)
CGameButton::CGameButton()
	:m_pControlMgr(CControlMgr::GetInstance())
	, m_pButtonImage(nullptr)
	, m_eCurState(ENUM::ButtonState::NONE)
	, m_eNextState(ENUM::ButtonState::NONE)
	, m_szButtonName(L"")
	
{
	m_eNextState = ENUM::ButtonState::NORMAL;
}


CGameButton::~CGameButton()
{
	Release();
}

HRESULT CGameButton::Initialize()
{
	m_pButtonImage = CButtonImage::Create(CBaseButtonImageImp::Create());
	NULL_CHECK_MSG_RETURN(m_pButtonImage, L"Button Initialize Error", S_FALSE);
	m_tDraw.vSize = {100.f, 50.f, 0.f};
	return S_OK;
}

HRESULT CGameButton::LateInit()
{
	ChangeState();
	return S_OK;
}

void CGameButton::Release()
{
	SafeDelete(m_pButtonImage);
}

int CGameButton::Update()
{
	if (0 != PtInRect(&m_tDraw.GetRect(0.f, true, ENUM::DrawRect::COLLISION), m_pControlMgr->GetMouse()->GetPoint()))
	{
		if (m_pKeyMgr->KeyDown(KEY::LBUTTON))
		{
			CSoundMgr::GetInstance()->MyPlaySound(L"button.wav", CSoundMgr::CHANNELID::UI);
		}
		if (m_pKeyMgr->KeyPressing(KEY::LBUTTON))
		{
			m_eNextState = ENUM::ButtonState::DOWN;
		}
		else
		{
			m_eNextState = ENUM::ButtonState::SELECTED;
		}
	}
	else
	{
		m_eNextState = ENUM::ButtonState::NORMAL;
	}
	return 0;
}

void CGameButton::LateUpdate()
{
	ChangeState();
}

void CGameButton::Render()
{
	m_pButtonImage->Render(m_szButtonName, m_tDraw, m_tFrame);
}

void CGameButton::ChangeState()
{
	if (m_eCurState != m_eNextState)
	{
		m_eCurState = m_eNextState;
		m_pButtonImage->ChangeState(m_eNextState, m_tFrame);
		switch (m_eNextState)
		{
		case ENUM::ButtonState::NONE:
			break;
		case ENUM::ButtonState::NORMAL:
			break;
		case ENUM::ButtonState::DOWN:
			if (!lstrcmp(m_szButtonName, L"GameStart"))
				CSceneMgr::GetInstance()->SceneChange(ENUM::Scene::WORLDMAP);
			else if (!lstrcmp(m_szButtonName, L"Exit"))
				PostQuitMessage(0);
			break;
		case ENUM::ButtonState::SELECTED:
			break;
		default:
			break;
		}
	}
}
