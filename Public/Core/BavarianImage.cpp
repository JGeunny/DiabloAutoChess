#include "stdafx.h"
#include "BavarianImage.h"

IMPLEMENT_CREATE_BASE(CBavarianImage)
CBavarianImage::CBavarianImage()
	:m_bChangeScene(false)
{
}


CBavarianImage::~CBavarianImage()
{
}

HRESULT CBavarianImage::Initialize()
{
	//m_pTextureMgr->LoadTexture(L"Bavarian|Idle_R", L"../Image/Unit/Bavarian/stand_R/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Idle_UR", L"../Image/Unit/Bavarian/stand_UR/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Idle_U", L"../Image/Unit/Bavarian/stand_U/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Idle_UL", L"../Image/Unit/Bavarian/stand_UL/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Idle_L", L"../Image/Unit/Bavarian/stand_L/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Idle_DL", L"../Image/Unit/Bavarian/stand_DL/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Idle_D", L"../Image/Unit/Bavarian/stand_D/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Idle_DR", L"../Image/Unit/Bavarian/stand_DR/%d.png", 8);

	//m_pTextureMgr->LoadTexture(L"Bavarian|Walk_R", L"../Image/Unit/Bavarian/walk_R/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Walk_UR", L"../Image/Unit/Bavarian/walk_UR/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Walk_U", L"../Image/Unit/Bavarian/walk_U/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Walk_UL", L"../Image/Unit/Bavarian/walk_UL/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Walk_L", L"../Image/Unit/Bavarian/walk_L/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Walk_DL", L"../Image/Unit/Bavarian/walk_DL/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Walk_D", L"../Image/Unit/Bavarian/walk_D/%d.png", 8);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Walk_DR", L"../Image/Unit/Bavarian/walk_DR/%d.png", 8);

	//m_pTextureMgr->LoadTexture(L"Bavarian|Attack_R",  L"../Image/Unit/Bavarian/attack_R/%d.png", 16);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Attack_UR", L"../Image/Unit/Bavarian/attack_UR/%d.png", 16);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Attack_U",  L"../Image/Unit/Bavarian/attack_U/%d.png", 16);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Attack_UL", L"../Image/Unit/Bavarian/attack_UL/%d.png", 16);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Attack_L",  L"../Image/Unit/Bavarian/attack_L/%d.png", 16);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Attack_DL", L"../Image/Unit/Bavarian/attack_DL/%d.png", 16);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Attack_D",  L"../Image/Unit/Bavarian/attack_D/%d.png", 16);
	//m_pTextureMgr->LoadTexture(L"Bavarian|Attack_DR", L"../Image/Unit/Bavarian/attack_DR/%d.png", 16);

	//m_pTextureMgr->LoadTexture(L"Bavarian|Death", L"../Image/Unit/Bavarian/Death.png", -1, 5, 5, INIT_COLOR_MAGENTA);

	//m_pTextureMgr->LoadTexture(L"Bavarian|Whirlwind", L"../Image/Unit/Bavarian/whirlwind/%d.png", 8);
	LoadGameImage();

	m_vecOrderType.resize(8);
	for (int i = 0; i < 8; ++i)
		m_vecOrderType[i] = i;
	m_vecOrderType2.resize(1);
	m_vecOrderType2[0] = 0;
	return S_OK;
}

void CBavarianImage::ChangeState(ENUM::State & _eState, FRAME & _tFrame)
{
	switch (_eState)
	{
	case ENUM::State::IDLE:
		m_vScale = { 1.f, 1.f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 0 * 8;
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
		_tFrame.iFrameKey = 1 * 8;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 7;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 120;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::ATTACK:
		m_vScale = { 1.f, 1.f, 0.f };
		m_vPosFit = { 0.f,  0.f, 0.f };
		_tFrame.iFrameKey = 2 * 8;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 15;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 40;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::DEAD:
		m_vScale = { 0.6f, 0.6f, 0.f };
		m_vPosFit = { 0.f,  -50.f, 0.f };
		_tFrame.iFrameKey = 3 * 8;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 4;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 4;
		_tFrame.uFrameSpeed = 50;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	default:
		break;
	}
}

void CBavarianImage::Render(DRAW_INFO & _tDraw, FRAME & _tFrame, D3DXMATRIX * _pMatrix)
{
	static D3DXVECTOR3 vScaleTemp = _tDraw.vScale;
	static D3DXVECTOR3 vPosFitTemp = _tDraw.vPosFit;
	vScaleTemp = _tDraw.vScale;
	vPosFitTemp = _tDraw.vPosFit;
	_tDraw.vPosFit += m_vPosFit;
	_tDraw.vScale = FUNC::GET::D3DXVec3Multiply(_tDraw.vScale, m_vScale);

	if (_tFrame.iFrameKey == 3 * 8)//죽는 이미지일 경우 따로 처리
	{
		_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::BAVARIAN, _tFrame.iFrameKey, 0));

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
			if (_tFrame.iFrameStart == _tFrame.iFrameEnd)
				m_bChangeScene = true;
		}

		m_pDeviceMgr->DrawImage(_tDraw, &_tDraw.GetRectSprite(_tFrame.iFrameStart, _tFrame.iFrameScene));
	}
	else
	{
		_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::BAVARIAN, _tFrame.iFrameKey + _tFrame.iFrameScene, _tFrame.iFrameStart));

		if (_pMatrix)
			_tDraw.matCurrent = *_pMatrix;
		else
			_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

		_tFrame.SetScene(_tDraw.vAngle.z);
		//	std::cout << _tFrame.iFrameScene << ":" << _tFrame.iFrameStart << std::endl;
		m_pDeviceMgr->DrawImage(_tDraw);
	}
	_tDraw.vScale = vScaleTemp;
	_tDraw.vPosFit = vPosFitTemp;
}

void CBavarianImage::SetWhirlwind(FRAME & _tFrame)
{
	//휠윈드
	m_vScale = { 1.f, 1.f, 0.f };
	m_vPosFit = { 0.f,  0.f, 0.f };
	_tFrame.iFrameKey = 3 * 8 + 1;
	//_tFrame.iFrameStart = 0;
	_tFrame.iFrameEnd = 7;
	_tFrame.iFrameScene = 0;
	_tFrame.iFrameSceneEnd = 1;
	_tFrame.uFrameSpeed = 20;
	_tFrame.pListSceneOrder = &m_vecOrderType2;
}

void CBavarianImage::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Idle_R", L"../Image/Unit/Bavarian/stand_R/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Idle_UR", L"../Image/Unit/Bavarian/stand_UR/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Idle_U", L"../Image/Unit/Bavarian/stand_U/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Idle_UL", L"../Image/Unit/Bavarian/stand_UL/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Idle_L", L"../Image/Unit/Bavarian/stand_L/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Idle_DL", L"../Image/Unit/Bavarian/stand_DL/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Idle_D", L"../Image/Unit/Bavarian/stand_D/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Idle_DR", L"../Image/Unit/Bavarian/stand_DR/%d.png", 8);

	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Walk_R", L"../Image/Unit/Bavarian/walk_R/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Walk_UR", L"../Image/Unit/Bavarian/walk_UR/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Walk_U", L"../Image/Unit/Bavarian/walk_U/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Walk_UL", L"../Image/Unit/Bavarian/walk_UL/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Walk_L", L"../Image/Unit/Bavarian/walk_L/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Walk_DL", L"../Image/Unit/Bavarian/walk_DL/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Walk_D", L"../Image/Unit/Bavarian/walk_D/%d.png", 8);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Walk_DR", L"../Image/Unit/Bavarian/walk_DR/%d.png", 8);
	
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Attack_R", L"../Image/Unit/Bavarian/attack_R/%d.png", 16);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Attack_UR", L"../Image/Unit/Bavarian/attack_UR/%d.png", 16);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Attack_U", L"../Image/Unit/Bavarian/attack_U/%d.png", 16);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Attack_UL", L"../Image/Unit/Bavarian/attack_UL/%d.png", 16);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Attack_L", L"../Image/Unit/Bavarian/attack_L/%d.png", 16);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Attack_DL", L"../Image/Unit/Bavarian/attack_DL/%d.png", 16);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Attack_D", L"../Image/Unit/Bavarian/attack_D/%d.png", 16);
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Attack_DR", L"../Image/Unit/Bavarian/attack_DR/%d.png", 16);
	
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Death", L"../Image/Unit/Bavarian/Death.png", -1, 5, 5, INIT_COLOR_MAGENTA);
	
	CTextureMgr::GetInstance()->LoadTexture(L"Bavarian|Whirlwind", L"../Image/Unit/Bavarian/whirlwind/%d.png", 8);

}