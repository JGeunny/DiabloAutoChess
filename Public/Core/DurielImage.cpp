#include "stdafx.h"
#include "DurielImage.h"

IMPLEMENT_CREATE_BASE(CDurielImage)
CDurielImage::CDurielImage()
{
}


CDurielImage::~CDurielImage()
{
}

HRESULT	CDurielImage::Initialize()
{
	//m_pTextureMgr->LoadTexture(L"Duriel|Idle", L"../Image/Unit/Duriel/DurielIdle.png", -1, 12, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Duriel|Walk", L"../Image/Unit/Duriel/DurielMove.png", -1, 16, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Duriel|Attack", L"../Image/Unit/Duriel/DurielAttack.png", -1, 10, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Duriel|Die", L"../Image/Unit/Duriel/DurielDie.png", -1, 25, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	LoadGameImage();

	m_vecOrderType.resize(8);
	for (int i = 0; i <= 2; ++i)
		m_vecOrderType[i] = 2 - i;
	for (int i = 3; i <= 7; ++i)
		m_vecOrderType[i] = 7 - (i-3);
	return S_OK;
}

void CDurielImage::ChangeState(ENUM::State & _eState, FRAME & _tFrame)
{
	switch (_eState)
	{
	case ENUM::State::IDLE:
		m_vScale = { 1.f, 1.f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 0;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 11;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 120;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::WALK:
		m_vScale = { 1.2f, 1.2f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 1;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 15;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 120;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::ATTACK:
		m_vScale = { 1.4f, 1.2f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 2;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 9;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 60;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::DEAD:
		m_vScale = { 1.2f, 1.2f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 3;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 24;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 80;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	default:
		break;
	}
}

void CDurielImage::Render(DRAW_INFO & _tDraw, FRAME & _tFrame, D3DXMATRIX * _pMatrix)
{
	static D3DXVECTOR3 vScaleTemp = _tDraw.vScale;
	static D3DXVECTOR3 vPosFitTemp = _tDraw.vPosFit;
	vScaleTemp = _tDraw.vScale;
	vPosFitTemp = _tDraw.vPosFit;
	_tDraw.vPosFit += m_vPosFit;
	_tDraw.vScale = FUNC::GET::D3DXVec3Multiply(_tDraw.vScale, m_vScale);

	_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::DURIEL, _tFrame.iFrameKey, 0));

	if (_pMatrix)
		_tDraw.matCurrent = *_pMatrix;
	else
		_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

	_tFrame.SetScene(_tDraw.vAngle.z);

	m_pDeviceMgr->DrawImage(_tDraw, &_tDraw.GetRectSprite(_tFrame.iFrameStart, _tFrame.iFrameScene));
	_tDraw.vScale = vScaleTemp;
	_tDraw.vPosFit = vPosFitTemp;
}

void CDurielImage::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"Duriel|Idle", L"../Image/Unit/Duriel/DurielIdle.png", -1, 12, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Duriel|Walk", L"../Image/Unit/Duriel/DurielMove.png", -1, 16, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Duriel|Attack", L"../Image/Unit/Duriel/DurielAttack.png", -1, 10, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Duriel|Die", L"../Image/Unit/Duriel/DurielDie.png", -1, 25, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
}