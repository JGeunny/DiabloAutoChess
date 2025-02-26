#include "stdafx.h"
#include "Ending.h"


IMPLEMENT_CREATE_BASE(CEnding)
CEnding::CEnding()
{
}

CEnding::~CEnding()
{
	Release();
}

HRESULT CEnding::Initialize()
{
	//CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNELID::BGM);
	CSoundMgr::GetInstance()->StopAll();
	CSoundMgr::GetInstance()->PlayBGM(L"ending.mp3");
	m_pObjMgr->InitNextScene();
	m_tDraw.vPos = { WINCX * 0.5f, WINCY * 0.5f, 0.f };
	m_tDraw.vSize = { WINCX, WINCY, 0.f };
	m_pTextureMgr->LoadTexture(L"Ending", L"../Image/Ending/Ending.png");
	m_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(L"Ending"));
	m_tDraw.matCurrent = m_tDraw.GetMatrixWorld();

	m_vPos = { WINCX * 0.5f , WINCY , 0.f };
	m_lstText.emplace_back(L"♥감사합니다♥");
	m_lstText.emplace_back(L"정근영");

	SetDelayTime(ENUM::LiveTime::BASE, 10);
	return S_OK;
}

void CEnding::Release()
{
}

int CEnding::Update()
{
	CObserver::LiveTime();
	if(IsActivateTime(ENUM::LiveTime::BASE))
		m_vPos.y -= 1;
	return m_pObjMgr->Update();
}

void CEnding::LateUpdate()
{
	m_pObjMgr->LateUpdate();
	//버튼에서 씬 체인지가 있을 경우 요 메니저를 타면 터진다
	if (m_pKeyMgr->KeyDown(KEY::SPACE))
	{
		m_pSceneMgr->SceneChange(ENUM::Scene::TITLE);
	}
}

void CEnding::Render()
{
	static D3DXVECTOR3 vCurPos;
	static D3DXVECTOR3 vSize = {WINCX, 50.f, 0.f};
	static RECT rtRect;

	m_pDeviceMgr->DrawImage(m_tDraw);
	m_pObjMgr->Render();

	vCurPos = m_vPos;
	for (auto& strText : m_lstText)
	{
		rtRect = FUNC::GET::Rect(vCurPos, vSize);
		m_pDeviceMgr->DrawString(strText.c_str(), strText.size(), &rtRect, 5UL, INIT_COLOR, ENUM::FONT::FONT48);
		vCurPos.y += 100;
	}
	if (vCurPos.y <= WINCY * 0.5f + 100)
		SetDelayTime(ENUM::LiveTime::BASE, 0);

}