#include "stdafx.h"
#include "Title.h"
#include "GameButton.h"

#include "Trait.h"
#include "Inven.h"

IMPLEMENT_CREATE_BASE(CTitle)
CTitle::CTitle()
{
}

CTitle::~CTitle()
{
	Release();
}

HRESULT CTitle::Initialize()
{
	//CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNELID::BGM);
	CSoundMgr::GetInstance()->StopAll();
	CSoundMgr::GetInstance()->PlayBGM(L"Title.wav");
	m_pObjMgr->InitNextScene();
	m_tDraw.vPos = { WINCX * 0.5f, WINCY * 0.5f, 0.f };
	m_tDraw.vSize = { WINCX, WINCY, 0.f};
	m_pTextureMgr->LoadTexture(L"Title", L"../Image/Menu/Title.png");
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(L"Title"));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();

	CGameButton * pButton = CGameButton::Create(WINCX*0.5f, 300.f + 150, 200, 70, L"GameStart");
	CObjMgr::GetInstance()->AddObject(ENUM::UIType::BUTTON, pButton);

	pButton = CGameButton::Create(WINCX*0.5f, 300.f + 250, 200, 70, L"Exit");
	CObjMgr::GetInstance()->AddObject(ENUM::UIType::BUTTON, pButton);


	//pButton = CMyButton::Create(842 + 210, 552);
	//pButton->SetFrameKey(L"Exit");
	//CObjMgr::GetInstance()->AddObject(OBJ::UI, pButton);	

	return S_OK;
}

void CTitle::Release()
{
}

int CTitle::Update()
{
	return m_pObjMgr->Update();
}

void CTitle::LateUpdate()
{
	m_pObjMgr->LateUpdate();
	//버튼에서 씬 체인지가 있을 경우 요 메니저를 타면 터진다
	if (m_pKeyMgr->KeyDown(KEY::SPACE))
	{	
		m_pSceneMgr->SceneChange(ENUM::Scene::WORLDMAP);
	}
}

void CTitle::Render()
{	
	m_pDeviceMgr->DrawImage(m_tDraw);
	m_pObjMgr->Render();
}


