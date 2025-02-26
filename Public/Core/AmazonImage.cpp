#include "stdafx.h"
#include "AmazonImage.h"

IMPLEMENT_CREATE_BASE(CAmazonImage)
CAmazonImage::CAmazonImage()
	:m_bChangeScene(false)
{
}


CAmazonImage::~CAmazonImage()
{
}

HRESULT CAmazonImage::Initialize()
{
	LoadGameImage();
	//m_pTextureMgr->LoadTexture(L"Amazon|Idle", L"../Image/Unit/Amazon/Idle.png", -1, 16, 16, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Amazon|Walk", L"../Image/Unit/Amazon/Walk.png", -1, 8, 16, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Amazon|Attack", L"../Image/Unit/Amazon/Attack.png", -1, 14, 16, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Amazon|Death", L"../Image/Unit/Amazon/Death.png", -1, 5, 5, INIT_COLOR_MAGENTA);

	m_vecOrderType.resize(16);
	for (int i = 0; i <= 13; ++i)
		m_vecOrderType[i] = 13 - i;
	m_vecOrderType[14] = 15;
	m_vecOrderType[15] = 14;

	return S_OK;
}

void CAmazonImage::ChangeState(ENUM::State & _eState, FRAME& _tFrame)
{
	switch (_eState)
	{
	case ENUM::State::IDLE:
		m_vScale = { 1.f, 1.f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 0;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 15;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 15;
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
		_tFrame.iFrameSceneEnd = 15;
		_tFrame.uFrameSpeed = 120;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::ATTACK:
		m_vScale = { 1.1f, 1.2f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 2;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 13;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 15;
		_tFrame.uFrameSpeed = 40;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::DEAD:
		m_vScale = { 1.1f, 1.2f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 3;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 4;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 4;
		_tFrame.uFrameSpeed = 50;
		_tFrame.pListSceneOrder = nullptr;
		break;
	default:
		break;
	}
}

void CAmazonImage::Render(DRAW_INFO & _tDraw, FRAME& _tFrame, D3DXMATRIX * _pMatrix)
{
	static D3DXVECTOR3 vScaleTemp = _tDraw.vScale;
	static D3DXVECTOR3 vPosFitTemp = _tDraw.vPosFit;
	vScaleTemp = _tDraw.vScale;
	vPosFitTemp = _tDraw.vPosFit;
	_tDraw.vPosFit += m_vPosFit;
	_tDraw.vScale = FUNC::GET::D3DXVec3Multiply(_tDraw.vScale, m_vScale);

	if (_tFrame.iFrameKey == 3)//죽는 이미지일 경우 따로 처리
	{
		_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::AMAZONE, _tFrame.iFrameKey, 0));

		if (_pMatrix)
			_tDraw.matCurrent = *_pMatrix;
		else
			_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

		if (_tFrame.iFrameStart == 0)
		{
			if (m_bChangeScene)
			{
				m_bChangeScene = false;
				++_tFrame.iFrameScene;
				_tFrame.iFrameScene = _tFrame.iFrameScene % (_tFrame.iFrameSceneEnd + 1);
			}
		}
		else
		{
			if(_tFrame.iFrameStart == _tFrame.iFrameEnd)
				m_bChangeScene = true;
		}

		m_pDeviceMgr->DrawImage(_tDraw, &_tDraw.GetRectSprite(_tFrame.iFrameStart, _tFrame.iFrameScene));
	}
	else
	{
		_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::AMAZONE, _tFrame.iFrameKey, 0));

		if (_pMatrix)
			_tDraw.matCurrent = *_pMatrix;
		else
			_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

		_tFrame.SetScene(_tDraw.vAngle.z);

		m_pDeviceMgr->DrawImage(_tDraw, &_tDraw.GetRectSprite(_tFrame.iFrameStart, _tFrame.iFrameScene));
	}
	_tDraw.vScale = vScaleTemp;
	_tDraw.vPosFit = vPosFitTemp;
}


void CAmazonImage::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"Amazon|Idle", L"../Image/Unit/Amazon/Idle.png", -1, 16, 16, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Amazon|Walk", L"../Image/Unit/Amazon/Walk.png", -1, 8, 16, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Amazon|Attack", L"../Image/Unit/Amazon/Attack.png", -1, 14, 16, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Amazon|Death", L"../Image/Unit/Amazon/Death.png", -1, 5, 5, INIT_COLOR_MAGENTA);
}