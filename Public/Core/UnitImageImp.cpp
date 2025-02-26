#include "stdafx.h"
#include "UnitImageImp.h"


CUnitImageImp::CUnitImageImp()
	:m_pDeviceMgr(CDeviceMgr::GetInstance())
	, m_pTextureMgr(CTextureMgr::GetInstance())
	, m_vScale({1.f, 1.f, 0.f})
{
}


CUnitImageImp::~CUnitImageImp()
{
}
