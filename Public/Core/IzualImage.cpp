#include "stdafx.h"
#include "IzualImage.h"

IMPLEMENT_CREATE_BASE(CIzualImage)
CIzualImage::CIzualImage()
{
}


CIzualImage::~CIzualImage()
{
}

HRESULT CIzualImage::Initialize()
{
	//m_pTextureMgr->LoadTexture(L"Izual|Idle", L"../Image/Unit/Izual/IzualIdle.png", -1, 8, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Izual|Walk", L"../Image/Unit/Izual/IzualMove.png", -1, 8, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Izual|Attack", L"../Image/Unit/Izual/IzualAttack.png", -1, 16, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Izual|Die", L"../Image/Unit/Izual/IzualDie.png", -1, 20, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	LoadGameImage();

	m_vecOrderType.resize(8);
	for (int i = 0; i <= 6; ++i)
		m_vecOrderType[i] = 6 - i;
	m_vecOrderType[7] = 7;

	m_vecOrderType2.resize(8);
	for (int i = 0; i <= 7; ++i)
		m_vecOrderType2[i] = 7 - i;
	return S_OK;
}

void CIzualImage::ChangeState(ENUM::State & _eState, FRAME& _tFrame)
{
	switch (_eState)
	{
	case ENUM::State::IDLE:
		m_vScale = { 1.f, 1.f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 0;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 7;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 120;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::WALK:
		m_vScale = { 1.f, 1.f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 1;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 7;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 75;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::ATTACK:
		m_vScale = { 1.2f, 1.3f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 2;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 15;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 30;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::DEAD:
		m_vScale = { 1.4f, 1.4f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 3;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 19;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 1;
		_tFrame.uFrameSpeed = 80;
		_tFrame.pListSceneOrder = &m_vecOrderType2;
		break;
	default:
		break;
	}
}

void CIzualImage::Render(DRAW_INFO & _tDraw, FRAME& _tFrame, D3DXMATRIX * _pMatrix)
{
	static D3DXVECTOR3 vScaleTemp = _tDraw.vScale;
	static D3DXVECTOR3 vPosFitTemp = _tDraw.vPosFit;
	vScaleTemp = _tDraw.vScale;
	vPosFitTemp = _tDraw.vPosFit;
	_tDraw.vPosFit += m_vPosFit;
	_tDraw.vScale = FUNC::GET::D3DXVec3Multiply(_tDraw.vScale, m_vScale);

	_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::IZUAL, _tFrame.iFrameKey, 0));

	if (_pMatrix)
		_tDraw.matCurrent = *_pMatrix;
	else
		_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

	_tFrame.SetScene(_tDraw.vAngle.z);
//	std::cout << _tFrame.iFrameStart << ":" << _tFrame.iFrameScene << std::endl;
	m_pDeviceMgr->DrawImage(_tDraw, &_tDraw.GetRectSprite(_tFrame.iFrameStart, _tFrame.iFrameScene));
	_tDraw.vScale = vScaleTemp;
	_tDraw.vPosFit = vPosFitTemp;
}

void CIzualImage::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"Izual|Idle", L"../Image/Unit/Izual/IzualIdle.png", -1, 8, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Izual|Walk", L"../Image/Unit/Izual/IzualMove.png", -1, 8, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Izual|Attack", L"../Image/Unit/Izual/IzualAttack.png", -1, 16, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Izual|Die", L"../Image/Unit/Izual/IzualDie.png", -1, 20, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
}