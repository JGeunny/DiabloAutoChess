#include "stdafx.h"
#include "DiaImage.h"

IMPLEMENT_CREATE_BASE(CDiaImage)
CDiaImage::CDiaImage()
{
}


CDiaImage::~CDiaImage()
{
}

HRESULT CDiaImage::Initialize()
{
	//m_pTextureMgr->LoadTexture(L"Dia|Idle", L"../Image/Unit/Dia/DiaIdle.png", -1, 12, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Dia|Walk", L"../Image/Unit/Dia/DiaMove.png", -1, 22, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Dia|Attack", L"../Image/Unit/Dia/DiaAttack.png", -1, 20, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	//m_pTextureMgr->LoadTexture(L"Dia|Die", L"../Image/Unit/Dia/Die/%d.png", 141);

	//m_pTextureMgr->LoadTexture(L"Dia|skill_DL", L"../Image/Unit/Dia/DiaSkill/skill_DL/%d.png", 17);
	//m_pTextureMgr->LoadTexture(L"Dia|skill_D", L"../Image/Unit/Dia/DiaSkill/skill_D/%d.png", 17);
	//m_pTextureMgr->LoadTexture(L"Dia|skill_L", L"../Image/Unit/Dia/DiaSkill/skill_L/%d.png", 17);
	//m_pTextureMgr->LoadTexture(L"Dia|skill_UL", L"../Image/Unit/Dia/DiaSkill/skill_UL/%d.png", 17);
	//m_pTextureMgr->LoadTexture(L"Dia|skill_U", L"../Image/Unit/Dia/DiaSkill/skill_U/%d.png", 17);
	//m_pTextureMgr->LoadTexture(L"Dia|skill_UR", L"../Image/Unit/Dia/DiaSkill/skill_UR/%d.png", 17);
	//m_pTextureMgr->LoadTexture(L"Dia|skill_R", L"../Image/Unit/Dia/DiaSkill/skill_R/%d.png", 17);
	//m_pTextureMgr->LoadTexture(L"Dia|skill_DR", L"../Image/Unit/Dia/DiaSkill/skill_DR/%d.png", 17);
	//9~13빔쏘는 애니메이션
	LoadGameImage();

	m_vecOrderType.resize(8);
	for (int i = 0; i <= 6; ++i)
		m_vecOrderType[i] = 6 - i;
	m_vecOrderType[7] = 7;

	m_vecOrderType2.resize(1);
	m_vecOrderType2[0] = 0;

	return S_OK;
}

void CDiaImage::ChangeState(ENUM::State & _eState, FRAME& _tFrame)
{
	switch (_eState)
	{
	case ENUM::State::IDLE:
		m_vScale = { 1.f, 1.f, 0.f };
		m_vPosFit = {0.f,  0.f, 0.f};
		_tFrame.iFrameKey = 0;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 11;
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
		_tFrame.iFrameEnd = 21;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 75;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::ATTACK:
		m_vScale = { 1.2f, 1.2f, 0.f };
		m_vPosFit = { 0.f,  -35.f, 0.f };
		_tFrame.iFrameKey = 2;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 19;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 7;
		_tFrame.uFrameSpeed = 30;
		_tFrame.pListSceneOrder = &m_vecOrderType;
		break;
	case ENUM::State::DEAD:
		m_vScale = { 1.2f, 1.2f, 0.f };
		m_vPosFit = { 0.f,  -35.f, 0.f };
		_tFrame.iFrameKey = 3;
		_tFrame.iFrameStart = 0;
		_tFrame.iFrameEnd = 140;
		_tFrame.iFrameScene = 0;
		_tFrame.iFrameSceneEnd = 1;
		_tFrame.uFrameSpeed = 50;
		_tFrame.pListSceneOrder = &m_vecOrderType2;
		break;
	default:
		break;
	}
}

void CDiaImage::Render(DRAW_INFO & _tDraw, FRAME& _tFrame, D3DXMATRIX * _pMatrix)
{
	static D3DXVECTOR3 vScaleTemp = _tDraw.vScale;
	static D3DXVECTOR3 vPosFitTemp = _tDraw.vPosFit;
	vScaleTemp = _tDraw.vScale;
	vPosFitTemp = _tDraw.vPosFit;
	_tDraw.vPosFit += m_vPosFit;
	_tDraw.vScale = FUNC::GET::D3DXVec3Multiply(_tDraw.vScale, m_vScale);


	if (_tFrame.iFrameKey == 3)//멀티 텍스쳐 디아 죽을때
	{
		_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::DIA, _tFrame.iFrameKey, _tFrame.iFrameStart));

		if (_pMatrix)
			_tDraw.matCurrent = *_pMatrix;
		else
			_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

		_tFrame.SetScene(_tDraw.vAngle.z);
		//	std::cout << _tFrame.iFrameStart << ":" << _tFrame.iFrameScene << std::endl;
		m_pDeviceMgr->DrawImage(_tDraw);
	}
	if (_tFrame.iFrameKey > 3)//디아 스킬쓸때
	{
		_tFrame.SetScene(_tDraw.vAngle.z);
		_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::DIA, _tFrame.iFrameKey + _tFrame.iFrameScene, _tFrame.iFrameStart));

		if (_pMatrix)
			_tDraw.matCurrent = *_pMatrix;
		else
			_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

		//	std::cout << _tFrame.iFrameStart << ":" << _tFrame.iFrameScene << std::endl;
		m_pDeviceMgr->DrawImage(_tDraw);
	}
	else
	{
		_tDraw.SetTexInfo(m_pTextureMgr->GetTexInfo(RZIMAGE::DIA, _tFrame.iFrameKey, 0));

		if (_pMatrix)
			_tDraw.matCurrent = *_pMatrix;
		else
			_tDraw.matCurrent = _tDraw.GetMatrixWorld(MATRIX::EXCEPT_ROTATE);

		_tFrame.SetScene(_tDraw.vAngle.z);
		//	std::cout << _tFrame.iFrameStart << ":" << _tFrame.iFrameScene << std::endl;
		m_pDeviceMgr->DrawImage(_tDraw, &_tDraw.GetRectSprite(_tFrame.iFrameStart, _tFrame.iFrameScene));
	}
	_tDraw.vScale = vScaleTemp;
	_tDraw.vPosFit = vPosFitTemp;
}

void CDiaImage::SetDiaSkill(FRAME& _tFrame)
{
	//디아 스킬
	m_vScale = { 1.2f, 1.2f, 0.f };
	m_vPosFit = { 0.f,  0.f, 0.f };
	_tFrame.iFrameKey = 4;
	_tFrame.iFrameStart = 0;
	_tFrame.iFrameEnd = 16;
	_tFrame.iFrameScene = 0;
	_tFrame.iFrameSceneEnd = 7;
	_tFrame.uFrameSpeed = 40;
	_tFrame.pListSceneOrder = &m_vecOrderType;
}

void CDiaImage::LoadGameImage()
{
	static bool isInit = false;
	if (isInit) return;
	isInit = true;

	CTextureMgr::GetInstance()->LoadTexture(L"Dia|Idle", L"../Image/Unit/Dia/DiaIdle.png", -1, 12, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|Walk", L"../Image/Unit/Dia/DiaMove.png", -1, 22, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|Attack", L"../Image/Unit/Dia/DiaAttack.png", -1, 20, 8, D3DCOLOR_ARGB(255, 170, 170, 170));
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|Die", L"../Image/Unit/Dia/Die/%d.png", 141);

	CTextureMgr::GetInstance()->LoadTexture(L"Dia|skill_DL", L"../Image/Unit/Dia/DiaSkill/skill_DL/%d.png", 17);
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|skill_D", L"../Image/Unit/Dia/DiaSkill/skill_D/%d.png", 17);
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|skill_L", L"../Image/Unit/Dia/DiaSkill/skill_L/%d.png", 17);
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|skill_UL", L"../Image/Unit/Dia/DiaSkill/skill_UL/%d.png", 17);
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|skill_U", L"../Image/Unit/Dia/DiaSkill/skill_U/%d.png", 17);
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|skill_UR", L"../Image/Unit/Dia/DiaSkill/skill_UR/%d.png", 17);
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|skill_R", L"../Image/Unit/Dia/DiaSkill/skill_R/%d.png", 17);
	CTextureMgr::GetInstance()->LoadTexture(L"Dia|skill_DR", L"../Image/Unit/Dia/DiaSkill/skill_DR/%d.png", 17);
}