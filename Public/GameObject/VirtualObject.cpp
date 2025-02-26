#include "stdafx.h"
#include "VirtualObject.h"
#include "UnitImage.h"
#include "AmazonImage.h"
#include "DurielImage.h"
#include "BavarianImage.h"
#include "AndarielImage.h"
#include "DiaImage.h"
#include "IzualImage.h"
#include "BarlogImage.h"

#include "UnitControl.h"

IMPLEMENT_CREATE(CVirtualObject)
CVirtualObject::CVirtualObject()
	: m_pUnitImage(nullptr)
	, m_eCurImageId(RZIMAGE::END)
{
}


CVirtualObject::~CVirtualObject()
{
	Release();
}

HRESULT CVirtualObject::Initialize()
{
	m_tDraw.vAngle.z = 270;

	//디아블로
	m_tDraw.vSize.x = 300;
	m_tDraw.vSize.y = 300;
	m_tDraw.vPosFit = { 0.f, -30.f, 0.f };
	m_tDraw.vSizeCollision = { 140.f, 140.f, 0.f };
	m_tDraw.vSizeLand = { 50.f, 50.f, 0.f };


	m_tDraw.fSpeed = INIT_SPEED;

	//m_pUnitImage = CUnitImage::Create(CAmazonImage::Create());
	//m_pUnitImage = CUnitImage::Create(CDurielImage::Create());
	//m_pUnitImage = CUnitImage::Create(CBavarianImage::Create());
	//m_pUnitImage = CUnitImage::Create(CAndarielImage::Create());
	//m_pUnitImage = CUnitImage::Create(CDiaImage::Create());
	//m_pUnitImage = CUnitImage::Create(CIzualImage::Create());
	//m_pUnitImage = CUnitImage::Create(CBarlogImage::Create());

	//m_pUnitControl = CUnitControl::Create(CArcherControl::Create());

	m_eNextState = ENUM::State::IDLE;
	return S_OK;
}

HRESULT CVirtualObject::LateInit()
{
	//m_vTargetPos = m_tDraw.vPos;
	return S_OK;
}

void CVirtualObject::Release()
{
	SafeDelete(m_pUnitImage);
}

int CVirtualObject::Update()
{
	CGameImage::LateInit();
	if (ENUM::Event::DEAD == m_eEvent)
		return (int)m_eEvent;

	Control();
	return (int)m_eEvent;
}

void CVirtualObject::LateUpdate()
{
	CGameImage::MoveFrame();
	CGameObject::FSM();
}

void CVirtualObject::Render()
{
	if (m_pUnitImage)
	{
		m_pDeviceMgr->DrawHexagon(m_tDraw.GetHexagon(0.f, true, ENUM::DrawRect::LAND), 2.5f, INIT_COLOR_GREEN);
		m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::IMAGE), 1.f, INIT_COLOR_RECT_IMAGE);
		m_pDeviceMgr->DrawRectangle(m_tDraw.GetRect(0.f, true, ENUM::DrawRect::COLLISION), 1.f, INIT_COLOR_RECT_COLLITION);
		m_pUnitImage->Render(m_tDraw, m_tFrame);
	}
}

void CVirtualObject::SetImage(RZIMAGE::ID _eImageId)
{
	if (m_eCurImageId != _eImageId)
	{
		m_eCurImageId = _eImageId;
		SafeDelete(m_pUnitImage);
		switch (_eImageId)
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
			m_pUnitImage = CUnitImage::Create(CAmazonImage::Create());
			break;
		case RZIMAGE::DURIEL:
			m_pUnitImage = CUnitImage::Create(CDurielImage::Create());
			break;
		case RZIMAGE::BAVARIAN:
			m_pUnitImage = CUnitImage::Create(CBavarianImage::Create());
			break;
		case RZIMAGE::ANDARIEL:
			m_pUnitImage = CUnitImage::Create(CAndarielImage::Create());
			break;
		case RZIMAGE::DIA:
			m_pUnitImage = CUnitImage::Create(CDiaImage::Create());
			break;
		case RZIMAGE::IZUAL:
			m_pUnitImage = CUnitImage::Create(CIzualImage::Create());
			break;
		case RZIMAGE::BARLOG:
			m_pUnitImage = CUnitImage::Create(CBarlogImage::Create());
			break;
		case RZIMAGE::SKILL:
			break;
		case RZIMAGE::BASEBUTTON:
			break;
		case RZIMAGE::END:
			break;
		default:
			break;
		}
	}
}

void CVirtualObject::SetImage(LPWSTR _pImageName)
{
	SetImage(FUNC::CONVERT::GetImageId(_pImageName));
}

void CVirtualObject::ChangeState(ENUM::State _eState)
{
	m_eNextState = _eState;
	if (m_pUnitImage)
	{
		m_pUnitImage->ChangeState(m_eNextState, m_tFrame);
	}
}


void CVirtualObject::Control()
{
	//m_pUnitControl->Control(m_eNextState, m_tDraw);
}

void CVirtualObject::FSM()
{
	if (m_pUnitImage)
	{
		ChangeState(m_eNextState);
	}
}