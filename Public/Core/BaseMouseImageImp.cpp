#include "stdafx.h"
#include "BaseMouseImageImp.h"

IMPLEMENT_CREATE_BASE(CBaseMouseImageImp)
CBaseMouseImageImp::CBaseMouseImageImp()
	:m_vPosFit({ 0.f, 0.f, 0.f })
	, m_vScale({ 1.f, 1.f, 1.f })
{
}


CBaseMouseImageImp::~CBaseMouseImageImp()
{
}

HRESULT	CBaseMouseImageImp::Initialize()
{
	m_pTextureMgr->LoadTexture(L"BaseMouse|Normal", L"../Image/UI/Mouse/Normal/normal_%d.png", 5);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Click", L"../Image/UI/Mouse/Click/Click_%d.png", 5);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Drag", L"../Image/UI/Mouse/Drag/drag_%d.png", 1);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Scroll_D", L"../Image/UI/Mouse/ScrollD/scrolld_%d.png", 2);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Scroll_DL", L"../Image/UI/Mouse/ScrollDL/scrolldl_%d.png", 2);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Scroll_DR", L"../Image/UI/Mouse/ScrollDR/scrolldr_%d.png", 2);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Scroll_L", L"../Image/UI/Mouse/ScrollL/scrolll_%d.png", 2);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Scroll_R", L"../Image/UI/Mouse/ScrollR/scrollr_%d.png", 2);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Scroll_U", L"../Image/UI/Mouse/ScrollU/scrollu_%d.png", 2);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Scroll_UL", L"../Image/UI/Mouse/ScrollUL/scrollul_%d.png", 2);
	m_pTextureMgr->LoadTexture(L"BaseMouse|Scroll_UR", L"../Image/UI/Mouse/ScrollUR/scrollur_%d.png", 2);
	m_pTextureMgr->LoadTexture(L"BaseMouse|MagAlly", L"../Image/UI/Mouse/MagAlly/magally_%d.png", 14);
	m_pTextureMgr->LoadTexture(L"BaseMouse|MagEnemy", L"../Image/UI/Mouse/MagEnemy/magenemy_%d.png", 14);
	m_pTextureMgr->LoadTexture(L"BaseMouse|TargetAlly", L"../Image/UI/Mouse/TargetAlly/targetally_%d.png", 2);
	m_pTextureMgr->LoadTexture(L"BaseMouse|TargetEnermy", L"../Image/UI/Mouse/TargetEnemy/targetenemy_%d.png", 2);

	return S_OK;
}

void CBaseMouseImageImp::ChangeState(ENUM::MouseState & _eState, FRAME & _tFrame)
{
	m_vPosFit = { 0.f, 0.f, 0.f };
	m_vScale = { 1.f, 1.f, 1.f };
	switch (_eState)
	{
	case ENUM::MouseState::NONE:
		_tFrame.iFrameKey = -1;
		break;
	case ENUM::MouseState::NORMAL:
		_tFrame.iFrameKey = 0;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 4;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 100;
		break;
	case ENUM::MouseState::CLICK:
		m_vScale = { 0.3f, 0.2f, 0.3f };
		_tFrame.iFrameKey = 1;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 4;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 100;
		break;
	case ENUM::MouseState::DRAG:
		_tFrame.iFrameKey = 2;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 0;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::SCROLL_D:
		_tFrame.iFrameKey = 3;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::SCROLL_DL:
		_tFrame.iFrameKey = 4;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::SCROLL_DR:
		_tFrame.iFrameKey = 5;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::SCROLL_L:
		_tFrame.iFrameKey = 6;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::SCROLL_R:
		_tFrame.iFrameKey = 7;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::SCROLL_U:
		_tFrame.iFrameKey = 8;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::SCROLL_UL:
		_tFrame.iFrameKey = 9;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::SCROLL_UR:
		_tFrame.iFrameKey = 10;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::MAG_ALLY:
		_tFrame.iFrameKey = 11;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 13;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 100;
		break;
	case ENUM::MouseState::MAG_ENEMY:
		_tFrame.iFrameKey = 12;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 13;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 100;
		break;
	case ENUM::MouseState::TARGET_ALLY:
		_tFrame.iFrameKey = 13;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	case ENUM::MouseState::TARGET_ENEMY:
		_tFrame.iFrameKey = 14;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 1;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 0;
		_tFrame.uFrameSpeed = 200;
		break;
	default:
		break;
	}
}

void CBaseMouseImageImp::Render(DRAW_INFO & _tDraw, FRAME & _tFrame, D3DXMATRIX * _pMatrix)
{
	if (-1 == _tFrame.iFrameKey) return;
	static D3DXVECTOR3 vScaleTemp = _tDraw.vScale;
	static D3DXVECTOR3 vPosFitTemp = _tDraw.vPosFit;
	vScaleTemp = _tDraw.vScale;
	vPosFitTemp = _tDraw.vPosFit;
	_tDraw.vPosFit += m_vPosFit;
	_tDraw.vScale = FUNC::GET::D3DXVec3Multiply(_tDraw.vScale, m_vScale);

	_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::BASEMOUSE, _tFrame.iFrameKey, _tFrame.iFrameStart));

	if (_pMatrix)
		_tDraw.matCurrent = *_pMatrix;
	else
		_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

	//_tFrame.SetScene(_tDraw.vAngle.z);

	m_pDeviceMgr->DrawImage(_tDraw);
	_tDraw.vScale = vScaleTemp;
	_tDraw.vPosFit = vPosFitTemp;
}
